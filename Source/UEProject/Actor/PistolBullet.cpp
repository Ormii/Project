// Fill out your copyright notice in the Description page of Project Settings.

#include "PistolBullet.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Hitable.h"

APistolBullet::APistolBullet(): ABaseBullet()
{
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_ImpactEffect(TEXT("/Game/Effect/NS_BloodSplash_High.NS_BloodSplash_High"));
    if(NS_ImpactEffect.Succeeded())
    {
        ImpactEffect = NS_ImpactEffect.Object;
    }

    if(CollisionSphere)
    {
        CollisionSphere->SetNotifyRigidBodyCollision(true);
    }
}

void APistolBullet::BeginPlay()
{
    Super::BeginPlay();

    if(CollisionSphere)
    {
        CollisionSphere->OnComponentHit.AddDynamic(this, &APistolBullet::OnCompHit);
        UE_LOG(LogTemp, Warning, TEXT("등록 완료"));
    }
}

void APistolBullet::OnCompHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("Hit Event"));
    if(OtherActor == GetOwner())
        return;

    UE_LOG(LogTemp, Warning, TEXT("HitCast Start"));
    IHitable* pHitable = Cast<IHitable>(OtherActor);
    if(pHitable == nullptr)
        return;

    UE_LOG(LogTemp, Warning, TEXT("HitCast Success"));
    pHitable->Hit(GetOwner());

    if(ImpactEffect != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Niagara Effect Start"));
        UNiagaraComponent *pNiagaraCompo = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),ImpactEffect, Hit.Location, Hit.Normal.Rotation());
        if(pNiagaraCompo != nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Niagara Spawned"));
            pNiagaraCompo->Activate();
        }
    }

    Destroy();
}

void APistolBullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
