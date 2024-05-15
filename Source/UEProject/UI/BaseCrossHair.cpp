// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseCrossHair.h"
#include "BaseCrossHair.h"

void UBaseCrossHair::Init(float fMaxChargeTime)
{
    MaxChargeTime = fMaxChargeTime;
    ChargeTime = MaxChargeTime;
}




void UBaseCrossHair::Release(void)
{
    MaxChargeTime = 0.0f;
    ChargeTime = 0.0f;
}
