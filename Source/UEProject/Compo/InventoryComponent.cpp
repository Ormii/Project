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
	UE_LOG(LogTemp, Warning, TEXT("Inventory Num : %d"), InventorySlots.Num());

	if(Index < 0 || InventorySlots.Num() <= Index)
		return false;

	ItemData = InventorySlots[Index];

    return true;
}

bool UInventoryComponent::UpdateInventorySlots(int32 Index)
{
	UE_LOG(LogTemp, Warning, TEXT("Index : %d"), Index);
	UE_LOG(LogTemp, Warning, TEXT("InventorySlots Num : %d"), InventorySlots.Num());
	if(Index < 0 || Index >= InventorySlots.Num())
		return false;
	UE_LOG(LogTemp, Warning, TEXT("1"));

	ABasePlayerController *PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(PlayerController == nullptr)
		return false;
	UE_LOG(LogTemp, Warning, TEXT("2"));	

	UBaseTabUMGWidget *TabWidget = PlayerController->GetTabWidget();
	if(TabWidget == nullptr)
		return false;
	UE_LOG(LogTemp, Warning, TEXT("3"));
	UBaseInventoryWidget *InventoryWidget = TabWidget->GetInventoryWidget();
	if(InventoryWidget == nullptr)
		return false;
	UE_LOG(LogTemp, Warning, TEXT("4"));
	TArray<UBaseInventorySlotWidget*> SlotsArray = InventoryWidget->GetSlotsArray();
	
	if(Index < 0 || Index >= SlotsArray.Num())
		return false;

	UBaseInventorySlotWidget *SlotWidget = SlotsArray[Index];
	UE_LOG(LogTemp, Warning, TEXT("Update Slot Start"));
	SlotWidget->UpdateSlot();

	return true;
}
