// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BaseItem.h"
#include "BaseItem.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
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
	ItemMesh->SetupAttachment(RootComponent);

	DetectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectSphere"));
	DetectSphere->SetupAttachment(RootComponent);
	DetectSphere->SetGenerateOverlapEvents(true);
	
	DetectSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	InteractWidget->SetupAttachment(RootComponent);

	FString OutlineMaterialName = "/Game/Materials/M_Outline.M_Outline";
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> OutlineMaterialAsset(*OutlineMaterialName);
	if(OutlineMaterialAsset.Succeeded())
	{
		OutlineMaterial = OutlineMaterialAsset.Object;
	}
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();


	Survivor = Cast<ASurvivor>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	IsVisibleRange = false;
	IsInteractRange = false;

	if(InteractWidget == nullptr)
		return;
	if(Survivor)
	{
		FVector ActorLocation = GetActorLocation();
		FVector WidgetLocation = InteractWidget->GetComponentLocation();
	
		FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(WidgetLocation,Survivor->GetCameraLocation());
		InteractWidget->SetWorldRotation(newRotation);

		float Dist = FVector::Dist(Survivor->GetActorLocation(), ActorLocation);
		if(Dist <= IsInVisibleRange)
			IsVisibleRange = true;

		if(Dist <= IsInInteractRange)
			IsInteractRange = true;
		
	}
	
	if(IsVisibleRange)
	{
		ItemMesh->SetOverlayMaterial(OutlineMaterial);
	}
	else
	{
		ItemMesh->SetOverlayMaterial(nullptr);
	}

	if(IsInteractRange)
	{
		InteractWidget->SetVisibility(true);
	}
	else
	{
		InteractWidget->SetVisibility(false);
	}
}

bool ABaseItem::Interact(AActor *OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact %s"), *GetName());

    return true;
}

bool ABaseItem::UseItem()
{
    return true;
}
