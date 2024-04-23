// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/BaseAttackItem.h"
#include "Components/SphereComponent.h"
#include "KnifeAttackItem.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API AKnifeAttackItem : public ABaseAttackItem
{
	GENERATED_BODY()
public:
	AKnifeAttackItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	virtual void OnAttackSphereOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	USphereComponent* GetSphereComponent(){return AttackSphere;}

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent *AttackSphere;
};
