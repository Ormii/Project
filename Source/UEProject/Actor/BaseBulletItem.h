// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/BaseItem.h"
#include "BaseBulletItem.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API ABaseBulletItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	virtual bool Interact(AActor* OtherActor) override;

	virtual bool UseItem();
};
