// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseEquipWidgetSlot.h"
#include "BaseEquipWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API UBaseEquipWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateEquipWidget();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InitEquipWidget(class UBaseTabUMGWidget* TabUMGWidget);

	TArray<UBaseEquipWidgetSlot*> GetSlotsArray(){return SlotsArrayRef;}

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TArray<UBaseEquipWidgetSlot*> SlotsArrayRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class ASurvivor *SurvivorRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UBaseTabUMGWidget* TabUMGWidgetRef;
};
