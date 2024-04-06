// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Actor/BaseItem.h"
#include "CoreMinimal.h"
#include "BaseAttackItem.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API ABaseAttackItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	virtual bool Interact(AActor* OtherActor) override;

	virtual bool UseItem();
};
