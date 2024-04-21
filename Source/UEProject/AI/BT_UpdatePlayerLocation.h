// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BT_UpdatePlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API UBT_UpdatePlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBT_UpdatePlayerLocation();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
