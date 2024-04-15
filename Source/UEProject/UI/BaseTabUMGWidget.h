// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseInventoryWidget.h"
#include "BaseEquipWidget.h"
#include "BaseExaminationWidget.h"
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
	UBaseExaminationWidget *GetExaminationWidget(){return ExaminationWidgetRef;}

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UBaseInventoryWidget* InventoryWidgetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UBaseEquipWidget* EquipWidgetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UBaseExaminationWidget *ExaminationWidgetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UButton *CloseDropDownButtonRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UImage *ItemBigImageRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UTextBlock *ItemNameTextRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UTextBlock *ItemDescriptionTextRef;
};
