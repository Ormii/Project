// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
private:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual bool LineOfSightToWithIgnoreParams(const AActor* Other, TArray<AActor*>& IgnoreParams,FVector ViewPoint = FVector(ForceInit), bool bAlternateChecks = false);

public:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
};
