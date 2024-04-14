// Fill out your copyright notice in the Description page of Project Settings.


#include "Compo/InventoryComponent.h"
#include "../Struct/InventoryItemData.h"
#include "../Actor/BaseItem.h"
#include "Containers/Array.h"
#include "Kismet/GameplayStatics.h"
#include "BasePlayerController.h"
#include "BaseTabUMGWidget.h"
#include "BaseInventoryWidget.h"
#include "BaseInventorySlotWidget.h"
#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	for(int32 i = 0; i < MaxInventoryCapacity; i++)
		InventorySlots.Add(FInventoryItemData{nullptr,0});

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::CheckEmptySlot(int32& outIndex)
{
	int32 i = 0;
	for(i = 0; i < InventorySlots.Num(); i++)
	{
		FInventoryItemData InventoryItemData = InventorySlots[i];
		if(InventoryItemData.Item == nullptr)
		{
			outIndex = i;
			return true;
		}
	}
    
	outIndex = -1;
	return false;
}

bool UInventoryComponent::CheckForFreeSlot(ABaseItem * Item, int32& Index)
{
	if(Item == nullptr)
		return false;

	int32 i = 0;
	for(i = 0; i < InventorySlots.Num(); i++)
	{
		FInventoryItemData InventoryItemData = InventorySlots[i];
		if(InventoryItemData.Item == nullptr)
			continue;

		if(Item->GetItemData().ItemType != InventoryItemData.Item->GetItemData().ItemType)
			continue;

		if(InventoryItemData.Amount < Item->GetItemData().MaxStackAmount)
		{
			Index = i;
			return true;
		}
	}	

	return false;
}

bool UInventoryComponent::GetItemDataAtIndex(FInventoryItemData &ItemData, int32 Index)
{
	if(Index < 0 || InventorySlots.Num() <= Index)
		return false;

	ItemData = InventorySlots[Index];

    return true;
}

bool UInventoryComponent::UpdateInventorySlots(int32 Index)
{
	if(Index < 0 || Index >= InventorySlots.Num())
		return false;

	ABasePlayerController *PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(PlayerController == nullptr)
		return false;

	UBaseTabUMGWidget *TabWidget = PlayerController->GetTabWidget();
	if(TabWidget == nullptr)
		return false;

	UBaseInventoryWidget *InventoryWidget = TabWidget->GetInventoryWidget();
	if(InventoryWidget == nullptr)
		return false;

	TArray<UBaseInventorySlotWidget*> SlotsArray = InventoryWidget->GetSlotsArray();
	
	if(Index < 0 || Index >= SlotsArray.Num())
		return false;

	UBaseInventorySlotWidget *SlotWidget = SlotsArray[Index];
	SlotWidget->UpdateSlot();

	return true;
}

bool UInventoryComponent::UseItem(int32 Index)
{
	FInventoryItemData InventoryItemData{0,};
	if(GetItemDataAtIndex(InventoryItemData,Index) == true)
	{
		if(InventoryItemData.Item != nullptr)
		{
			if(InventoryItemData.Item->UseItem() == true)
			{
				UE_LOG(LogTemp, Warning, TEXT("Use Item"));
				RemoveItem(Index);
			}
			UpdateInventorySlots(Index);
			return true;
		}
	}

    return false;
}

bool UInventoryComponent::EquipItem(int32 Index)
{
	FInventoryItemData InventoryItemData{0,};
	if(GetItemDataAtIndex(InventoryItemData,Index) == true)
	{
		if(InventoryItemData.Item != nullptr)
		{
			InventoryItemData.Item->EquipItem();
			UpdateInventorySlots(Index);
			return true;
		}
	}
    return false;
}

bool UInventoryComponent::UnEquipItem(int32 Index)
{
	FInventoryItemData InventoryItemData{0,};
	if(GetItemDataAtIndex(InventoryItemData,Index) == true)
	{
		if(InventoryItemData.Item != nullptr)
		{
			InventoryItemData.Item->UnEquipItem();
			UpdateInventorySlots(Index);
			return true;
		}
	}
	return false;
}

bool UInventoryComponent::DropItem(int32 Index)
{
	FInventoryItemData InventoryItemData{};
	if(GetItemDataAtIndex(InventoryItemData, Index) == true)
	{
		ABaseItem* Item = InventoryItemData.Item;
		int32 Amount = InventoryItemData.Amount;

		if(Item == nullptr)
			return false;

		if(Amount > 0)
		{
			while(Amount > 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Remove : %d"), Amount);
				if(RemoveItem(Index) == true)
				{
					Amount--;
					continue;
				}
				break;
			}
			UpdateInventorySlots(Index);

			ABasePlayerController *PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			if(PlayerController == nullptr)
				return false;

			UBaseTabUMGWidget *TabWidget = PlayerController->GetTabWidget();
			if(TabWidget == nullptr)
				return false;

			UBaseInventoryWidget *InventoryWidget = TabWidget->GetInventoryWidget();
			if(InventoryWidget == nullptr)
				return false;


			InventoryWidget->CloseDropDownMenu();
			return true;
		}
	}
    return false;
}

bool UInventoryComponent::RemoveItem(int32 Index)
{
	FInventoryItemData InventoryItemData{0,};
	if(GetItemDataAtIndex(InventoryItemData,Index) == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Remove Item Start"));
		if(InventorySlots[Index].Item == nullptr)
			return false;

		if(InventorySlots[Index].Amount > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Remove Item before Amount : %d"), InventorySlots[Index].Amount);
			InventorySlots[Index].Amount -= 1;
			UE_LOG(LogTemp, Warning, TEXT("Remove Item after Amount : %d"), InventorySlots[Index].Amount);
			if(InventorySlots[Index].Amount <= 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Remove Item and destroy"));
				InventorySlots[Index].Item->ConditionalBeginDestroy();
				InventorySlots[Index].Item = nullptr;
				InventorySlots[Index].Amount = 0;
			}

			return true;
		}
	}
    return false;
}
