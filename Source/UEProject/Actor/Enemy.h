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

	void SetIsDead(bool aIsDead){ Dead = aIsDead;}
	bool GetIsDead(){return Dead;}

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* Health;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* DieDecal;

	UPROPERTY(EditAnywhere, Category = "Niagara", meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* KnifeKilledEffect;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float MaxInvincibleRefreshTime = 0.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Combat", meta = (AllowPrivateAccess ="true"))
	bool  Dead = false;

	class UNiagaraComponent *KnifeKilledEffectNSCompo;

	bool  IsInvincible;
	float InvincibleRefreshTime;

	UPROPERTY(EditAnywhere, Category = "Effect", meta = (AllowPrivateAccess = "true"))
	float MaxKnifeKilledEffectScale = 1.0f;

	float KnifeKilledEffectScale = 0.0f;
};
