// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseInventoryWidget.h"
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

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UBaseInventoryWidget* InventoryWidgetRef;
};
