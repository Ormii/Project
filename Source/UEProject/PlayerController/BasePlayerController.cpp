// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/BasePlayerController.h"
#include "BaseTabUMGWidget.h"
#include "BasePlayerController.h"

void ABasePlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    TabWidget = Cast<UBaseTabUMGWidget>(CreateWidget(this, TabWidgetClass));
    if(TabWidget)
    {
        TabWidget->AddToViewport();
        TabWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void ABasePlayerController::SetPlayerEnableState(bool bPlayerEnabled)
{
    if(bPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
}