// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseCrossHair.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API UBaseCrossHair : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init(float fMaxChargeTime);
	void Release(void);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	float ChargeTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	float MaxChargeTime;
};
