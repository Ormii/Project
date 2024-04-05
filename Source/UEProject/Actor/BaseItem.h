// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/Interactable.h"
#include "../Struct/ItemData.h"
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

	bool GetIsVisibleRange(){return IsVisibleRange;}
	bool GetIsInteractRange(){return IsInteractRange;}

	FItemData GetItemData(){return ItemData;}

protected:
	UPROPERTY(EditAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	float IsInVisibleRange = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	float IsInInteractRange = 150.0f;

	UPROPERTY(EditAnywhere, Category = "Item Data", meta = (AllowPrivateAccess = "true"))
	FItemData ItemData;

	class ASurvivor *Survivor;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *ItemMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USphereComponent *DetectSphere;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent *InteractWidget;


	UPROPERTY(VisibleInstanceOnly)
	UMaterialInterface* OutlineMaterial = nullptr;
	

	bool IsInteractRange = false;
	bool IsVisibleRange = false;
	
};
