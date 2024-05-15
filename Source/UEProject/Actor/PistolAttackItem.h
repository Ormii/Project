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

public:
	virtual void Fire();
	AController *GetOwnerController() const;

	float GetMaxChargeTime(){return MaxChargeTime;}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float MaxRange = 10000.f;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float MaxChargeTime = 1.0f;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent * ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem *ImpactEffect;

	TSubclassOf<class ABaseBullet> BulletClass;
};
