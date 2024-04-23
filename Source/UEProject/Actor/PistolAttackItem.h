// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/BaseAttackItem.h"
#include "PistolAttackItem.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API APistolAttackItem : public ABaseAttackItem
{
	GENERATED_BODY()

public:
	APistolAttackItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
