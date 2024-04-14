// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Compo/InventoryComponent.h"
#include "Survivor.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = ItemMesh;
	
	DetectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectSphere"));
	DetectSphere->SetupAttachment(RootComponent);
	DetectSphere->SetGenerateOverlapEvents(true);
	
	DetectSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);


	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	InteractWidget->SetupAttachment(RootComponent);



/*
	FString OutlineMaterialName = "/Game/Materials/M_Outline.M_Outline";
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> OutlineMaterialAsset(*OutlineMaterialName);
	if(OutlineMaterialAsset.Succeeded())
	{
		OutlineMaterial = OutlineMaterialAsset.Object;
	}
*/

}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

	Survivor = Cast<ASurvivor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if(DetectSphere)
	{
		DetectSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnOverlapBegin);
	   // DetectSphere->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnOverlapEnd); <- 엔진에서 오류로 동작하지 않음
	}

	if(InteractWidget)
	{
		UpdateWidget = false;
		InteractWidget->SetVisibility(false);
	}
}

void ABaseItem::OnOverlapBegin(UPrimitiveComponent *newComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("%s : Begin Overlaped"), *GetItemData().Name);
	if(Survivor != Cast<ASurvivor>(OtherActor))
		return;

	UE_LOG(LogTemp, Warning, TEXT("%s : Survivor Begin Overlaped"), *GetItemData().Name);
	UpdateWidget = true;
}

void ABaseItem::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("%s : End Overlaped"), *GetItemData().Name);
	if(Survivor != Cast<ASurvivor>(OtherActor))
		return;
	
	UE_LOG(LogTemp, Warning, TEXT("%s : Survivor End Overlaped"), *GetItemData().Name);
	UpdateWidget = false;
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(InteractWidget == nullptr)
		return;

	if(Survivor)
	{
		FVector ActorLocation = GetActorLocation();
		FVector Direction = Survivor->GetCameraLocation() - ActorLocation;
		FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation,Survivor->GetCameraLocation());
		
		InteractWidget->SetWorldRotation(newRotation);
		InteractWidget->SetWorldLocation(ActorLocation + Direction.Normalize()*10);
	}

	if(UpdateWidget)
	{
		FVector ActorLocation = GetActorLocation() + FVector{0.0f,0.0f,5.0f};
		FVector CameraLocation = Survivor->GetCameraLocation();
		
		FHitResult HitResult{};
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		DrawDebugLine(GetWorld(), ActorLocation, ActorLocation + (CameraLocation - ActorLocation),FColor::Red,false, 1.0f);
		if(GetWorld()->LineTraceSingleByChannel(HitResult, ActorLocation, CameraLocation, ECollisionChannel::ECC_Visibility,Params) == false)
		{
			InteractWidget->SetVisibility(true);
			if(RegisterCandiArray == false)
			{
				Survivor->AddInteractItemCandiArray(this);
				RegisterCandiArray = true;
			}
		}
		else
		{
			InteractWidget->SetVisibility(false);
			if(RegisterCandiArray == true)
			{
				Survivor->RemoveInteractItemCandiArray(this);
				RegisterCandiArray = false;
			}
		}
	}
}

bool ABaseItem::Interact(AActor *OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact %s"), *GetName());

    return true;
}

bool ABaseItem::UseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Use : %s"), *ItemData.Name);
    return true;
}

bool ABaseItem::EquipItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Equiped : %s"), *ItemData.Name);
    return false;
}

bool ABaseItem::UnEquipItem()
{
	UE_LOG(LogTemp, Warning, TEXT("UnEquiped : %s"), *ItemData.Name);
    return false;
}
