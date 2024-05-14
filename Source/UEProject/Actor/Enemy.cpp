// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Enemy.h"
#include "Camera/CameraComponent.h"
#include "Compo/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "BaseAttackItem.h"
#include "Enemy.h"

AEnemy::AEnemy()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(RootComponent);

    Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

    DieDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("DieDecal"));
    DieDecal->Deactivate();

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

    if(KnifeKilledEffectNSCompo != nullptr && KnifeKilledEffectScale > 0)
    {
        KnifeKilledEffectScale -= DeltaTime/3.0f;
        if(KnifeKilledEffectScale <= 0.0f)
        {
            KnifeKilledEffectNSCompo->Deactivate();
            KnifeKilledEffectNSCompo = nullptr;
            
            if(DieDecal != nullptr)
            {
                DieDecal->Activate();
                FVector DecalLocation = GetMesh()->GetSocketLocation("KnifeKilledEffectSpawnPoint");
                DieDecal->SetWorldLocation(DecalLocation);
            }
        }
        else
        {
            KnifeKilledEffectNSCompo->SetRelativeScale3D(FVector(KnifeKilledEffectScale));
        }
    }
    
    if(DieDecal != nullptr)
    {
        if(DieDecal->IsActive() && DieDecal->FadeScreenSize > 0.01f)
        {
            float fFadeScreenSize = DieDecal->FadeScreenSize;
            DieDecal->SetFadeScreenSize(fFadeScreenSize - DeltaTime/50.0f);
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

        if(Health->GetHealthRatio() <= 0.0f)
        {
            SetIsDead(true);
            DetachFromControllerPendingDestroy();
		    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

            switch(pAttackItem->GetItemData().ItemType)
            {
                case EItemType::EITEM_TYPE_DEFAULT_KNIFE:
                case EItemType::EITEM_TYPE_DEFAULT_PISTOL:
                {
                    if(KnifeKilledEffect != nullptr)
                    {
                        KnifeKilledEffectNSCompo = UNiagaraFunctionLibrary::SpawnSystemAttached(KnifeKilledEffect,GetMesh(),FName("KnifeKilledEffectSpawnPoint"),FVector::ZeroVector, FRotator::ZeroRotator,EAttachLocation::KeepRelativeOffset,true);
                        KnifeKilledEffectScale = MaxKnifeKilledEffectScale;

                    }
                }
                    break;
                default:
                    break;
            }
        }
    }
}
