// Fill out your copyright notice in the Description page of Project Settings.


#include "PistolAttackItem.h"
#include "GameFramework/Controller.h"
#include "BaseBullet.h"
#include "PistolBullet.h"
#include "Survivor.h"
#include "DrawDebugHelpers.h"

APistolAttackItem ::APistolAttackItem() : ABaseAttackItem()
{
    ItemData.ItemType = EItemType::EITEM_TYPE_DEFAULT_PISTOL;
    ItemData.Name = "Pistol";
    ItemData.MaxStackAmount = 1;
	ItemData.CanbeUse = false;
	ItemData.CanbeEquiped = true;
	ItemData.CanbeUnEquip = false;

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
    ProjectileSpawnPoint->SetupAttachment(RootComponent);
    ProjectileSpawnPoint->SetRelativeRotation(FRotator(0.0f,0.0f,90.0f));
    ProjectileSpawnPoint->SetRelativeLocation(FVector(0.0f, 26.0f, 7.5f));

    static ConstructorHelpers::FObjectFinder<UBlueprint> BP_Bullet(TEXT("/Game/Blueprints/Actor/BP_PistolBullet.BP_PistolBullet"));
	if (BP_Bullet.Object){
		BulletClass = (UClass*)BP_Bullet.Object->GeneratedClass;
	}
}
void APistolAttackItem::BeginPlay()
{
    Super::BeginPlay();
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

    UE_LOG(LogTemp, Warning, TEXT("Line Cast Start"));
    if(GetWorld()->LineTraceSingleByChannel(Hit,Location, End, ECollisionChannel::ECC_GameTraceChannel1,Params))
    {

        UE_LOG(LogTemp, Warning, TEXT("Line Cast Success"));
        End = Hit.Location;
    }
    
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
        APistolBullet* pPistolBullet = Cast<APistolBullet>(GetWorld()->SpawnActor<APistolBullet>(BulletClass));
        if(pPistolBullet != nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Bullet Class Spawn Success"));
            pPistolBullet->SetActorLocation(ProjectileSpawnPoint->GetComponentLocation());
            pPistolBullet->SetActorRotation(ProjectileSpawnPoint->GetComponentRotation());
            pPistolBullet->InitBullet(FVector(0.0f,1.0f,0.0));
        }
    }
}

AController *APistolAttackItem::GetOwnerController() const
{
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return nullptr;
	AController* OwnerController = OwnerPawn->GetController();
	return OwnerController;
}
