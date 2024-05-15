// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;	

public:
	void SetPlayerEnableState(bool bPlayerEnabled);

	UFUNCTION(BlueprintPure)
	class UBaseTabUMGWidget *GetTabWidget() const {return TabWidget;}

	class UBaseCrossHair* GetCrossHairWidget() const {return CrossHairWidget;}

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UBaseTabUMGWidget> TabWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UBaseTabUMGWidget *TabWidget;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UBaseCrossHair> CrossHairClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess= "true"))
	class UBaseCrossHair *CrossHairWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UBaseGetItemNotify> GetItemNotifyClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess= "true"))
	class UBaseGetItemNotify *GetItemNotifyWidget;
};
