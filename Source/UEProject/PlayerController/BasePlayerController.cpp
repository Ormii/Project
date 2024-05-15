// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/BasePlayerController.h"
#include "BaseTabUMGWidget.h"
#include "BaseExaminationWidget.h"
#include "BaseCrossHair.h"
#include "BaseGetItemNotify.h"
#include "BasePlayerController.h"

void ABasePlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    TabWidget = Cast<UBaseTabUMGWidget>(CreateWidget(this, TabWidgetClass));
    if(TabWidget)
    {
        TabWidget->AddToViewport();
        TabWidget->SetVisibility(ESlateVisibility::Hidden);

        UBaseExaminationWidget *ExaminationWidget = TabWidget->GetExaminationWidget();
        if(ExaminationWidget)
        {
            ExaminationWidget->SetVisibility(ESlateVisibility::Collapsed);
        }
    }

    CrossHairWidget = Cast<UBaseCrossHair>(CreateWidget(this, CrossHairClass));
    if(CrossHairWidget)
    {
        CrossHairWidget->AddToViewport();
        CrossHairWidget->SetVisibility(ESlateVisibility::Hidden);
        CrossHairWidget->Init(0);
    }

    GetItemNotifyWidget = Cast<UBaseGetItemNotify>(CreateWidget(this, GetItemNotifyClass));
    if(GetItemNotifyWidget)
    {
        GetItemNotifyWidget->AddToViewport();
        GetItemNotifyWidget->SetVisibility(ESlateVisibility::Hidden);
        GetItemNotifyWidget->Init(GetPawn());
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