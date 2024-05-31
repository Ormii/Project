// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseTabUMGWidget.h"
#include "BaseTabUMGWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

bool UBaseTabUMGWidget::ResetItemBigImageRef()
{
    if(ItemBigImageRef)
    {
        ItemBigImageRef->SetBrushFromSoftTexture(nullptr);
        ItemBigImageRef->SetVisibility(ESlateVisibility::Hidden);
    }

    return false;
}

bool UBaseTabUMGWidget::ResetItemTextRef()
{
    if(ItemNameTextRef)
    {
        ItemNameTextRef->SetText(FText::FromString(""));
    }

    if(ItemDescriptionTextRef)
    {
        ItemDescriptionTextRef->SetText(FText::FromString(""));
    }

    return false;
}
