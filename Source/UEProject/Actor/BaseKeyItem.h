// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/BaseItem.h"
#include "BaseKeyItem.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API ABaseKeyItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ABaseKeyItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual bool Interact(AActor* OtherActor) override;

	virtual bool UseItem();
};
