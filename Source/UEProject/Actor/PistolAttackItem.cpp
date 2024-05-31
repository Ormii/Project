// Fill out your copyright notice in the Description page of Project Settings.


#include "PistolAttackItem.h"
#include "GameFramework/Controller.h"
#include "BaseBullet.h"
#include "PistolBullet.h"
#include "Survivor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Hitable.h"
#include "Compo/InventoryComponent.h"


APistolAttackItem ::APistolAttackItem() : ABaseAttackItem()
{
    ItemData.ItemType = EItemType::EITEM_TYPE_DEFAULT_PISTOL;
    ItemData.Name = "Pistol";
    ItemData.MaxStackAmount = 1;
	ItemData.CanbeUse = false;
	ItemData.CanbeEquiped = true;
	ItemData.CanbeUnEquip = false;

    AttackDamage = 30.0f;
    CurChargedBullet = 0;
    MaxChargedBullet = 8;

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
    ProjectileSpawnPoint->SetupAttachment(RootComponent);
    ProjectileSpawnPoint->SetRelativeRotation(FRotator(0.0f,0.0f,90.0f));
    ProjectileSpawnPoint->SetRelativeLocation(FVector(0.0f, 26.0f, 7.5f));

    static ConstructorHelpers::FObjectFinder<UBlueprint> BP_Bullet(TEXT("/Game/Blueprints/Actor/BP_PistolBullet.BP_PistolBullet"));
	if (BP_Bullet.Object){
		BulletClass = (UClass*)BP_Bullet.Object->GeneratedClass;
	}

    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_ImpactEffect(TEXT("/Game/Effect/NS_BloodSplash_High.NS_BloodSplash_High"));
    if(NS_ImpactEffect.Succeeded())
    {
        ImpactEffect = NS_ImpactEffect.Object;
    }
}
void APistolAttackItem::BeginPlay()
{
    Super::BeginPlay();
}

void APistolAttackItem::Reload()
{
    Super::Reload();
    
    ASurvivor *pSurvivor = Cast<ASurvivor>(GetOwner());
    if(pSurvivor)
    {
        UInventoryComponent* pInventoryCompo = pSurvivor->GetInventoryComponent();
        int32 nIndex = 0, nAmount = 0;
        if(pInventoryCompo != nullptr && pInventoryCompo->FindItem(EItemType::EITEM_TYPE_DEFAULT_BULLET, nIndex, nAmount) == true)
        {
            if((MaxChargedBullet - CurChargedBullet) - nAmount < 0)
            {
                int32 nCount = (MaxChargedBullet - CurChargedBullet);
                while(nCount > 0)
                {
                    if(pInventoryCompo->RemoveItem(nIndex))
                        CurChargedBullet++;

                    nCount--;
                }

                pInventoryCompo->UpdateInventorySlots(nIndex);

            }
            else if((MaxChargedBullet - CurChargedBullet) - nAmount == 0)
            {
                int32 nCount = nAmount;
                while(nCount > 0)
                {
                    if(pInventoryCompo->RemoveItem(nIndex))
                        CurChargedBullet++;
                    
                    nCount--;
                }

                pInventoryCompo->UpdateInventorySlots(nIndex);
            }
            else
            {
                int32 nCount = nAmount;
                while(nCount > 0)
                {
                    if(pInventoryCompo->RemoveItem(nIndex))
                        CurChargedBullet++;

                    nCount--;
                }
                
                pInventoryCompo->UpdateInventorySlots(nIndex);
                
                Reload();
            }
        }
    }
}

void APistolAttackItem::Fire()
{
    UE_LOG(LogTemp, Warning, TEXT("Fire function start"));
	AController *OwnerController = GetOwnerController();
	if(OwnerController == nullptr) return;

    UE_LOG(LogTemp, Warning, TEXT("Controller Cast Complete"));

	FVector Location = FVector::ZeroVector;
	FRotator Rotation = FRotator::ZeroRotator;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	FVector End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
    FHitResult Hit{};
     
    CurChargedBullet--;

    UE_LOG(LogTemp, Warning, TEXT("Line Cast Start"));
    //DrawDebugLine(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), End, FColor::Red,false,1.0f);
    if(GetWorld()->LineTraceSingleByChannel(Hit,Location, End, ECollisionChannel::ECC_GameTraceChannel1,Params))
    {
        IHitable* pHitable = Cast<IHitable>(Hit.GetActor());
        if(pHitable == nullptr)
            return;

        UE_LOG(LogTemp, Warning, TEXT("HitCast Success"));
        pHitable->Hit(this);

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
    }

    /*
        UE_LOG(LogTemp, Warning, TEXT("SpawnPoint : %f, %f, %f"), ProjectileSpawnPoint->GetComponentLocation().X, ProjectileSpawnPoint->GetComponentLocation().Y, ProjectileSpawnPoint->GetComponentLocation().Z);
        FVector ShotDirection = End - ProjectileSpawnPoint->GetComponentLocation();
        DrawDebugLine(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), End, FColor::Red,false,1.0f);

        UE_LOG(LogTemp, Warning, TEXT("Bullet Class Spawn Start"));
        if(BulletClass != nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Bullet Class Exist"));
            FActorSpawnParameters SpawnParams;
            SpawnParams.bDeferConstruction = true;
            SpawnParams.Owner = GetOwner();
            SpawnParams.Instigator = GetOwner()->GetInstigator();
            FVector BulletLocation = ProjectileSpawnPoint->GetComponentLocation();
            FRotator BulletRotation = (-ShotDirection).Rotation();
            APistolBullet* pPistolBullet = Cast<APistolBullet>(GetWorld()->SpawnActor<APistolBullet>(BulletClass, BulletLocation, BulletRotation));
            if(pPistolBullet != nullptr)
            {
                UE_LOG(LogTemp, Warning, TEXT("Bullet Class Spawn Success"));
                UE_LOG(LogTemp, Warning, TEXT("Bullet Rotation : %f, %f, %f"), pPistolBullet->GetActorRotation().Pitch, pPistolBullet->GetActorRotation().Yaw, pPistolBullet->GetActorRotation().Roll);
                pPistolBullet->SetOwner(this);
            }
        }
    */
}

AController *APistolAttackItem::GetOwnerController() const
{
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return nullptr;
	AController* OwnerController = OwnerPawn->GetController();
	return OwnerController;
}
