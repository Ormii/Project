// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseInventoryWidget.h"
#include "BaseEquipWidget.h"
#include "BaseTabUMGWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API UBaseTabUMGWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBaseInventoryWidget *GetInventoryWidget(){return InventoryWidgetRef;}
	UBaseEquipWidget *GetEquipWidget(){return EquipWidgetRef;}

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UBaseInventoryWidget* InventoryWidgetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UBaseEquipWidget* EquipWidgetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UButton *CloseDropDownButtonRef;
};
