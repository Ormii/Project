// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData.h"
#include "BaseGetItemNotify.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API UBaseGetItemNotify : public UUserWidget
{
	GENERATED_BODY()


public:
	void Init(APawn *pSurvivor);
	void Release(void);
	bool IsItemAlreadySeen(EItemType nItemType);
	bool AddItemAlreadySeen(class ABaseItem* pItem);

public:
	UFUNCTION(BlueprintCallable)
	void NextActionStartEvent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class ASurvivor* SurvivorRef;

	TArray<EItemType> AlreadySeenItemTypes;

	class ABaseItem* pGetItem;
};
