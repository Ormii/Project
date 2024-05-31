// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Struct/InventoryItemData.h"
#include "../Actor/BaseItem.h"
#include "../Actor/BaseExamination.h"
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

	ABaseExamination* GetExaminationActor(){return ExaminationActor;}

	bool CheckEmptySlot(int32& outIndex);
	bool CheckForFreeSlot(ABaseItem *Item, int32& Index);

	UFUNCTION(BlueprintCallable)
	bool GetItemDataAtIndex(FInventoryItemData& ItemData, int32 Index);
	
	UFUNCTION(BlueprintCallable)
	bool UpdateInventorySlots(int32 Index);

	UFUNCTION(BlueprintCallable)
	bool UseItem(int32 Index);

	UFUNCTION(BlueprintCallable)
	bool ExamineItem(int32 Index);

	UFUNCTION(BlueprintCallable)
	bool EquipItem(int32 Index);

	UFUNCTION(BlueprintCallable)
	bool UnEquipItem(int32 Index);

	UFUNCTION(BlueprintCallable)
	bool DropItem(int32 Index);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(int32 Index);
	
	bool FindItem(EItemType nItemType, int32& Index, int32& Amount);

	template <class T>
	bool AddItem(T *Item, int32 Amount, int32& Remain);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<FInventoryItemData> InventorySlots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta= (AllowPrivateAccess = "true"))
	int32 MaxInventoryCapacity = 8;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Examine Actor", meta = (AllowPrivateAccess = "true"))
	ABaseExamination* ExaminationActor;
};

template <class T>
inline bool UInventoryComponent::AddItem(T *Item, int32 Amount, int32& Remain)
{
	if(Item == nullptr)
		return false;

	if(Item->IsA(ABaseItem::StaticClass()) == false)
		return false;

	ABaseItem * newBaseItem = NewObject<T>();
	if(newBaseItem == nullptr)
		return false;

	newBaseItem->SetItemData(((ABaseItem*)Item)->GetItemData());
	newBaseItem->SetItemMesh(((ABaseItem*)Item)->GetItemMesh());
	newBaseItem->SetSurvivor(Cast<ASurvivor>(GetOwner()));
	int32 MaxStackAmount = Item->GetItemData().MaxStackAmount;

	bool result = false;
	while(Amount > 0)
	{
		int32 Index = 0;
		if(CheckForFreeSlot(Item, Index) == true)
		{
			ABaseItem *BaseItem = dynamic_cast<ABaseItem*>(Item);

			int32 RemainAmount = Amount - InventorySlots[Index].Amount;

			if(Amount + InventorySlots[Index].Amount > MaxStackAmount)
			{
				Amount -= (MaxStackAmount - InventorySlots[Index].Amount);
				InventorySlots[Index].Amount = MaxStackAmount;
			}
			else
			{
				InventorySlots[Index].Amount += Amount;
				Amount = 0;
			}

			InventorySlots[Index].Item->SetAmount(InventorySlots[Index].Amount);

			UpdateInventorySlots(Index);

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

