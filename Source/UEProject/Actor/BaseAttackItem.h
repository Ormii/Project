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
	ABaseAttackItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual bool Interact(AActor* OtherActor) override;

	virtual bool EquipItem() override;
	virtual bool UnEquipItem() override;

	float GetAttackDamage(){return AttackDamage;}
protected:

	UPROPERTY(EditAnywhere, Category = "Combet", meta = (AllowPrivateAccess = "true"))
	float AttackDamage = 10.0f;
};
