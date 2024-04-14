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

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool Interact(AActor* OtherActor) override;

	UFUNCTION(BlueprintCallable)
	virtual bool UseItem();

	UFUNCTION(BlueprintCallable)
	virtual bool EquipItem();

	UFUNCTION(BlueprintCallable)
	virtual bool UnEquipItem();

	void SetItemData(FItemData aItemData) {ItemData = aItemData;}
	void SetSurvivor(class ASurvivor* aSurvivor){Survivor = aSurvivor;}

	UFUNCTION(BlueprintPure)
	FItemData GetItemData(){return ItemData;}

	void 	SetAmount(int32 aAmount){ this->Amount = aAmount;}

	UFUNCTION(BlueprintPure)
	int32	GetAmount(){return Amount;}

protected:
	UPROPERTY(EditAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	float IsInVisibleRange = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	float IsInInteractRange = 150.0f;

	UPROPERTY(EditAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	FItemData ItemData;

	UPROPERTY(EditAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	int32 Amount;

	class ASurvivor *Survivor;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *ItemMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USphereComponent *DetectSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent *InteractWidget;

	UPROPERTY(VisibleInstanceOnly)
	UMaterialInterface* OutlineMaterial = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool UpdateWidget = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool RegisterCandiArray = false;
	
};
