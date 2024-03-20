// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/Interactable.h"
#include "BaseItem.generated.h"

UCLASS()
class UEPROJECT_API ABaseItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool Interact(AActor* OtherActor) override;

	virtual bool UseItem();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *ItemMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USphereComponent *DetectSphere;

	UPROPERTY(VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = "ture"))
	class UWidgetComponent *InteractWidget;
};
