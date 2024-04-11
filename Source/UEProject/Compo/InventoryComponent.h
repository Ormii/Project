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
	bool CheckForFreeSlot(ABaseItem *Item, int32& Index);

	UFUNCTION(BlueprintCallable)
	bool GetItemDataAtIndex(FInventoryItemData& ItemData, int32 Index);
	
	UFUNCTION(BlueprintCallable)
	bool UpdateInventorySlots(int32 Index);

	template <class T>
	bool AddItem(T *Item, int32 Amount, int32& Remain);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<FInventoryItemData> InventorySlots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta= (AllowPrivateAccess = "true"))
	int32 MaxInventoryCapacity = 8;
};

template <class T>
inline bool UInventoryComponent::AddItem(T *Item, int32 Amount, int32& Remain)
{
	if(Item == nullptr)
		return false;

	if(Item->IsA(ABaseItem::StaticClass()) == false)
		return false;

	ABaseItem * newBaseItem = NewObject<T>(Item, T::StaticClass(), *Item->GetItemData().Name);
	if(newBaseItem == nullptr)
		return false;

	newBaseItem->SetItemData(((ABaseItem*)Item)->GetItemData());
	int32 MaxStackAmount = Item->GetItemData().MaxStackAmount;

	bool result = false;
	while(Amount > 0)
	{
		int32 Index = 0;
		if(CheckForFreeSlot(Item, Index) == true)
		{
			ABaseItem *BaseItem = dynamic_cast<ABaseItem*>(Item);
			InventorySlots[Index].Amount += Amount;
			UpdateInventorySlots(Index);
			Amount = (InventorySlots[Index].Amount - MaxStackAmount);

			if(InventorySlots[Index].Amount > MaxStackAmount)
				InventorySlots[Index].Amount = MaxStackAmount;

			InventorySlots[Index].Item->SetAmount(InventorySlots[Index].Amount);

			if(Amount < 0)
				Amount = 0;
			
			Remain = Amount;
			result = true;
			continue;
		}
		else
		{
			int32 EmptyIndex = 0;			
			bool IsEmptySlotExist = CheckEmptySlot(EmptyIndex);
			if(IsEmptySlotExist == true)
			{
				int32 newAmount = (Amount - MaxStackAmount < 0) ? Amount : MaxStackAmount; 
				newBaseItem->SetAmount(newAmount);
				InventorySlots[EmptyIndex] = FInventoryItemData{newBaseItem,newAmount};
				UpdateInventorySlots(EmptyIndex);
				Amount -= newAmount;
				if(Amount < 0)
					Amount = 0;
				
				Remain = Amount;
				result = true;
				continue;
			}
		}

		break;
	}

	return result;
}

