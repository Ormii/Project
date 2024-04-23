// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/BaseCharacter.h"
#include "Hitable.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API AEnemy : public ABaseCharacter, public IHitable
{
	GENERATED_BODY()

public:
	AEnemy();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Hit(AActor* OtherActor) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* Health;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float MaxInvincibleRefreshTime = 0.5f;

	bool  IsInvincible;
	float InvincibleRefreshTime;
};
