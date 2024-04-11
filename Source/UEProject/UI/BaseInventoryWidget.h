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

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OpenDropDownMenu(class UBaseInventorySlotWidget* InventorySlotWidget);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CloseDropDownMenu();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InitInventoryWidget(class UBaseTabUMGWidget* TabUMGWidget);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class ASurvivor* SurvivorRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TArray<UBaseInventorySlotWidget*> SlotsArrayRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UBaseTabUMGWidget *TabUMGWidgetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UUniformGridPanel *InventoryGridPanelRef;
};
