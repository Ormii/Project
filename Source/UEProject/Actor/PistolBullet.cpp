// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PistolBullet.h"
#include "PistolBullet.h"

APistolBullet::APistolBullet(): ABaseBullet()
{
    
}

void APistolBullet::BeginPlay()
{
    Super::BeginPlay();
}

void APistolBullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
