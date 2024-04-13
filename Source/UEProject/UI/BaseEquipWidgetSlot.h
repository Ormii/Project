// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseEquipWidgetSlot.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API UBaseEquipWidgetSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InitEquipSlot(class UBaseEquipWidget* EquipWidget);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateSlot();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UImage *SlotImageRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	int32 IndexRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UBaseEquipWidget *EquipWidgetRef;
};
