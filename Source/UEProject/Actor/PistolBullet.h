// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/BaseBullet.h"
#include "PistolBullet.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API APistolBullet : public ABaseBullet
{
	GENERATED_BODY()

public:
	APistolBullet();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

protected:
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem *ImpactEffect;
};
