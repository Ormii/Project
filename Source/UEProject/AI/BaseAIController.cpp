// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "NetworkingDistanceConstants.h"
#include "BaseAttackItem.h"
#include "BaseAIController.h"
#include "Enemy.h"
#include "Survivor.h"

void ABaseAIController::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsObject(TEXT("Self"),this);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
    }
}

void ABaseAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	AEnemy *pEnemy = Cast<AEnemy>(GetPawn());
	if(pEnemy != nullptr)
	{
		GetBlackboardComponent()->SetValueAsBool("Dead", pEnemy->GetIsDead());
	}
}

bool ABaseAIController::LineOfSightToWithIgnoreParams(const AActor *Other, TArray<AActor*>& IgnoreParam, FVector ViewPoint, bool bAlternateChecks)
{
	if (Other == nullptr)
	{
		return false;
	}

	if (ViewPoint.IsZero())
	{
		FRotator ViewRotation;
		GetActorEyesViewPoint(ViewPoint, ViewRotation);

		// if we still don't have a view point we simply fail
		if (ViewPoint.IsZero())
		{
			return false;
		}
	}

	FVector TargetLocation = Other->GetTargetLocation(GetPawn());

	FCollisionQueryParams CollisionParams(SCENE_QUERY_STAT(LineOfSight), true, this->GetPawn());
	CollisionParams.AddIgnoredActor(Other);

	for(int i = 0; i < IgnoreParam.Num(); ++i)
	{
		CollisionParams.AddIgnoredActor(IgnoreParam[i]);
	}

	bool bHit = GetWorld()->LineTraceTestByChannel(ViewPoint, TargetLocation, ECC_Visibility, CollisionParams);
	if (!bHit)
	{
		return true;
	}

	// if other isn't using a cylinder for collision and isn't a Pawn (which already requires an accurate cylinder for AI)
	// then don't go any further as it likely will not be tracing to the correct location
	const APawn * OtherPawn = Cast<const APawn>(Other);
	if (!OtherPawn && Cast<UCapsuleComponent>(Other->GetRootComponent()) == NULL)
	{
		return false;
	}

	const FVector OtherActorLocation = Other->GetActorLocation();
	const FVector::FReal DistSq = (OtherActorLocation - ViewPoint).SizeSquared();
	if (DistSq > FARSIGHTTHRESHOLDSQUARED)
	{
		return false;
	}

	if (!OtherPawn && (DistSq > NEARSIGHTTHRESHOLDSQUARED))
	{
		return false;
	}

	float OtherRadius, OtherHeight;
	Other->GetSimpleCollisionCylinder(OtherRadius, OtherHeight);

	if (!bAlternateChecks || !bLOSflag)
	{
		//try viewpoint to head
		bHit = GetWorld()->LineTraceTestByChannel(ViewPoint, OtherActorLocation + FVector(0.f, 0.f, OtherHeight), ECC_Visibility, CollisionParams);
		if (!bHit)
		{
			return true;
		}
	}

	if (!bSkipExtraLOSChecks && (!bAlternateChecks || bLOSflag))
	{
		// only check sides if width of other is significant compared to distance
		if (OtherRadius * OtherRadius / (OtherActorLocation - ViewPoint).SizeSquared() < 0.0001f)
		{
			return false;
		}
		//try checking sides - look at dist to four side points, and cull furthest and closest
		FVector Points[4];
		Points[0] = OtherActorLocation - FVector(OtherRadius, -1 * OtherRadius, 0);
		Points[1] = OtherActorLocation + FVector(OtherRadius, OtherRadius, 0);
		Points[2] = OtherActorLocation - FVector(OtherRadius, OtherRadius, 0);
		Points[3] = OtherActorLocation + FVector(OtherRadius, -1 * OtherRadius, 0);
		int32 IndexMin = 0;
		int32 IndexMax = 0;
		FVector::FReal CurrentMax = (Points[0] - ViewPoint).SizeSquared();
		FVector::FReal CurrentMin = CurrentMax;
		for (int32 PointIndex = 1; PointIndex<4; PointIndex++)
		{
			const FVector::FReal NextSize = (Points[PointIndex] - ViewPoint).SizeSquared();
			if (NextSize > CurrentMin)
			{
				CurrentMin = NextSize;
				IndexMax = PointIndex;
			}
			else if (NextSize < CurrentMax)
			{
				CurrentMax = NextSize;
				IndexMin = PointIndex;
			}
		}

		for (int32 PointIndex = 0; PointIndex<4; PointIndex++)
		{
			if ((PointIndex != IndexMin) && (PointIndex != IndexMax))
			{
				bHit = GetWorld()->LineTraceTestByChannel(ViewPoint, Points[PointIndex], ECC_Visibility, CollisionParams);
				if (!bHit)
				{
					return true;
				}
			}
		}
	}
	return false;
}