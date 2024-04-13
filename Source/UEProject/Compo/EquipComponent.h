// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseAttackItem.h"
#include "EquipComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEPROJECT_API UEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	ABaseAttackItem* GetEquipItemAtIndex(int32 Index);

	UFUNCTION(BlueprintCallable)
	bool UpdateEquipSlots(int32 Index);

	bool CheckEmptySlot(int32& Index);
	void SetEquipSlot(ABaseAttackItem* Item, int32 Index);
	void RemoveEquipSlot(int32 Index);

	TArray<ABaseAttackItem*> &GetEquipArray() {return EquipArray;}
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equip", meta = (AllowPrivateAccess = "true"))
	TArray<ABaseAttackItem*> EquipArray;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta= (AllowPrivateAccess = "true"))
	int32 MaxEquipArrayCapacity = 4;


};
