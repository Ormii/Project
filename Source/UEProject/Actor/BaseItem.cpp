// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BaseItem.h"
#include "BaseItem.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Survivor.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = ItemMesh;

	DetectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectSphere"));
	DetectSphere->SetupAttachment(RootComponent);
	DetectSphere->SetGenerateOverlapEvents(true);
	
	DetectSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	InteractWidget->SetupAttachment(RootComponent);
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


	if(Survivor)
	{
		FVector WidgetLocation = InteractWidget->GetComponentLocation();
		FVector SurvivorLocation = Survivor->GetCameraLocation();

		FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(WidgetLocation,SurvivorLocation);
		InteractWidget->SetWorldRotation(newRotation);
	}

}

bool ABaseItem::Interact(AActor *OtherActor)
{
    return true;
}

bool ABaseItem::UseItem()
{
    return true;
}
