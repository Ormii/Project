// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Struct/InventoryItemData.h"
#include "../Actor/BaseItem.h"
#include "InventoryComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CheckEmptySlot(int32& outIndex);

	UFUNCTION(BlueprintCallable)
	bool GetItemDataAtIndex(FInventoryItemData& ItemData, int32 Index);
	
	UFUNCTION(BlueprintCallable)
	bool UpdateInventorySlots(int32 Index);

	template <class T>
	void AddItem(T *Item, int32 Amount);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<FInventoryItemData> InventorySlots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta= (AllowPrivateAccess = "true"))
	int32 MaxInventoryCapacity = 8;		
};

template <class T>
inline void UInventoryComponent::AddItem(T *Item, int32 Amount)
{
	if(Item == nullptr)
		return;

	if(Item->IsA(ABaseItem::StaticClass()) == false)
		return;

	ABaseItem * newBaseItem = NewObject<T>(Item, T::StaticClass(), *Item->GetItemData().Name);
	if(newBaseItem == nullptr)
		return;

	newBaseItem->SetItemData(((ABaseItem*)Item)->GetItemData());
	int32 MaxStackAmount = Item->GetItemData().MaxStackAmount;

	int32 EmptyIndex = 0;
	
	bool IsEmptySlotExist = CheckEmptySlot(EmptyIndex);
	if(IsEmptySlotExist == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Find Empty Slot"));
		InventorySlots[EmptyIndex] = FInventoryItemData{newBaseItem,Amount};
		UpdateInventorySlots(EmptyIndex);
	}
}
