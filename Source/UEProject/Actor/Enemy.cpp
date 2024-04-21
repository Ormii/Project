// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Enemy.h"
#include "Camera/CameraComponent.h"
#include "Compo/HealthComponent.h"

AEnemy::AEnemy()
{
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(RootComponent);

    Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}