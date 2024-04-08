// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseInventorySlotWidget.h"
#include "BaseInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API UBaseInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	TArray<UBaseInventorySlotWidget*> GetSlotsArray(){return SlotsArrayRef;}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class ASurvivor* SurvivorRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TArray<UBaseInventorySlotWidget*> SlotsArrayRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UUniformGridPanel *InventoryGridPanelRef;
};
