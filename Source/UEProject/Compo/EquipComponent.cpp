// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/BaseAttackItem.h"
#include "Kismet/GameplayStatics.h"
#include "BasePlayerController.h"
#include "../UI/BaseTabUMGWidget.h"
#include "../UI/BaseEquipWidget.h"
#include "EquipComponent.h"

// Sets default values for this component's properties
UEquipComponent::UEquipComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	for(int32 i = 0; i < MaxEquipArrayCapacity; i++)
		EquipArray.Add(nullptr);
	// ...
}


// Called when the game starts
void UEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ABaseAttackItem *UEquipComponent::GetEquipItemAtIndex(int32 Index)
{
	if(Index < 0 || Index >= EquipArray.Num())
		return nullptr;

    return EquipArray[Index];
}

bool UEquipComponent::UpdateEquipSlots(int32 Index)
{
	ABasePlayerController *PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(PlayerController == nullptr)
		return false;

	UE_LOG(LogTemp, Warning, TEXT("1"));
	UBaseTabUMGWidget *TabWidget = PlayerController->GetTabWidget();
	if(TabWidget == nullptr)
		return false;

	UE_LOG(LogTemp, Warning, TEXT("2"));
	UBaseEquipWidget *EquipWidget = TabWidget->GetEquipWidget();
	if(EquipWidget == nullptr)
		return false;
	
	UE_LOG(LogTemp, Warning, TEXT("3"));
	auto SlotArray = EquipWidget->GetSlotsArray();
	if(Index < 0 || Index >= SlotArray.Num())
		return false;

	UE_LOG(LogTemp, Warning, TEXT("4"));
	UBaseEquipWidgetSlot *EquipSlotWidget = SlotArray[Index];
	if(EquipSlotWidget == nullptr)
		return false;
	
	UE_LOG(LogTemp, Warning, TEXT("Update SlotStart"));
	EquipSlotWidget->UpdateSlot();

	return true;
}

bool UEquipComponent::CheckEmptySlot(int32 &Index)
{
	for(int i = 0; i < MaxEquipArrayCapacity; ++i)
	{
		if(EquipArray[i] == nullptr)
		{
			Index = i;
			return true;
		}
	}

    return false;
}

void UEquipComponent::SetEquipSlot(ABaseAttackItem *Item, int32 Index)
{
	if(Item == nullptr)
		return;

	if(EquipArray[Index] != nullptr)
		return;
	
	EquipArray[Index] = Item;
	UpdateEquipSlots(Index);
}

void UEquipComponent::RemoveEquipSlot(int32 Index)
{
	if(Index < 0 || Index >= EquipArray.Num())
		return;

	EquipArray[Index] = nullptr;
	UpdateEquipSlots(Index);
}
