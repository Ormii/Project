// Fill out your copyright notice in the Description page of Project Settings.

#include "KnifeAttackItem.h"
#include "Components/SphereComponent.h"
#include "Hitable.h"
#include "DrawDebugHelpers.h"

AKnifeAttackItem::AKnifeAttackItem(): ABaseAttackItem()
{
    ItemData.ItemType = EItemType::EITEM_TYPE_DEFAULT_KNIFE;
    ItemData.Name = "Knife";
    ItemData.MaxStackAmount = 1;
	ItemData.CanbeUse = false;
	ItemData.CanbeEquiped = true;
	ItemData.CanbeUnEquip = false;

    AttackDamage = 20.0f;

    AttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackSphere"));
    AttackSphere->SetupAttachment(RootComponent);
    AttackSphere->SetGenerateOverlapEvents(false);
}

void AKnifeAttackItem::BeginPlay()
{
    Super::BeginPlay();
    if(AttackSphere)
    {
        AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &AKnifeAttackItem::OnAttackSphereOverlapBegin);
    }
}

void AKnifeAttackItem::OnAttackSphereOverlapBegin(UPrimitiveComponent *newComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("AttackSphere Overlap"));
    if(OtherActor == GetOwner())
        return;

    UE_LOG(LogTemp, Warning, TEXT("HitCast Start"));
    IHitable* pHitable = Cast<IHitable>(OtherActor);
    if(pHitable == nullptr)
        return;

    UE_LOG(LogTemp, Warning, TEXT("HitCast Success"));
    pHitable->Hit(this);
}

void AKnifeAttackItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(AttackSphere->GetGenerateOverlapEvents())
    {
        DrawDebugSphere(GetWorld(),AttackSphere->GetComponentLocation(),8,20,FColor::Green,false,1.0f);
    }
}
