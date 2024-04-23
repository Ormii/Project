// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Enemy.h"
#include "Camera/CameraComponent.h"
#include "Compo/HealthComponent.h"
#include "BaseAttackItem.h"
#include "Enemy.h"

AEnemy::AEnemy()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(RootComponent);

    Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

    InvincibleRefreshTime = MaxInvincibleRefreshTime;
}
void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(IsInvincible)
    {
        InvincibleRefreshTime -= DeltaTime;
        if(InvincibleRefreshTime <= 0)
        {
            InvincibleRefreshTime = MaxInvincibleRefreshTime;
            IsInvincible = false;
            UE_LOG(LogTemp, Warning, TEXT("%s Invincible unactivate"), *GetName());
        }
    }
    
}

void AEnemy::Hit(AActor *OtherActor)
{
    ABaseAttackItem *pAttackItem = Cast<ABaseAttackItem>(OtherActor);
    if(pAttackItem == nullptr)
        return;

    if(IsInvincible)
        return;

    if(Health)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s receive damage %lf"), *GetName(), pAttackItem->GetAttackDamage());
        Health->DamageHealth(pAttackItem->GetAttackDamage());
        IsInvincible = true;
        UE_LOG(LogTemp, Warning, TEXT("%s Invincible activate"), *GetName());
    }
}
