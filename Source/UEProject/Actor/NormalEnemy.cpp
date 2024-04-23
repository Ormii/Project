// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/NormalEnemy.h"

ANormalEnemy::ANormalEnemy() : AEnemy()
{

}

void ANormalEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ANormalEnemy::Hit(AActor* OtherActor)
{
    Super::Hit(OtherActor);
}