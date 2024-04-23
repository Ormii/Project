// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Enemy.h"
#include "NormalEnemy.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API ANormalEnemy : public AEnemy
{
	GENERATED_BODY()
	
public:
	ANormalEnemy();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Hit(AActor* OtherActor) override;
};
