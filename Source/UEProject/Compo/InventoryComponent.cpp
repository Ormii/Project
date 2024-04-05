// Fill out your copyright notice in the Description page of Project Settings.


#include "Compo/InventoryComponent.h"
#include "../Struct/InventoryItemData.h"
#include "../Actor/BaseItem.h"
#include "Containers/Array.h"
#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	for(int32 i = 0; i < MaxInventoryCapacity; i++)
		InventorySlots.Add(FInventoryItemData{});

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