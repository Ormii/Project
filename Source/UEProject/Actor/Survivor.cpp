// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Survivor.h"
#include "Survivor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "DrawDebugHelpers.h"
#include "../PlayerController/BasePlayerController.h"
#include "../Interface/Interactable.h"
#include "../Compo/InventoryComponent.h"
#include "BaseItem.h"
#include "BaseDoor.h"
#include "BasePuzzle.h"

// Sets default values
ASurvivor::ASurvivor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	SpringArm->bUsePawnControlRotation = true;
	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryWidgetFinder(TEXT("/Game/Blueprints/Widget/WBP_TabUMG"));
	if(InventoryWidgetFinder.Class != nullptr)
	{
		InventoryWidgetClass = InventoryWidgetFinder.Class;
	}
}

// Called when the game starts or when spawned
void ASurvivor::BeginPlay()
{
	Super::BeginPlay();

	SurvivorPlayerController = Cast<ABasePlayerController>(GetController());

	if(SurvivorPlayerController)
	{
		SurvivorPlayerController->PlayerCameraManager->ViewPitchMin = -45;
		SurvivorPlayerController->PlayerCameraManager->ViewPitchMax = 45;
	}
	
	if(InventoryWidgetClass)
	{
		if(!InventoryWidget)
			InventoryWidget = CreateWidget(GetWorld(), InventoryWidgetClass, FName("Inventory Widget"));
		
		if(InventoryWidget == nullptr)
			return;

		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

// Called every frame
void ASurvivor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASurvivor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASurvivor::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASurvivor::MoveRight);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASurvivor::LookUpRate);
	PlayerInputComponent->BindAxis("LookRightRate", this, &ASurvivor::LookRightRate);

	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &ASurvivor::Interact);
}

FVector ASurvivor::GetCameraLocation(void)
{
    return (Camera != nullptr) ? Camera->GetComponentLocation() : FVector::ZeroVector;
}

UInventoryComponent *ASurvivor::GetInventoryComponent()
{
    return Inventory;
}

void ASurvivor::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ASurvivor::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void ASurvivor::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ASurvivor::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

IInteractable *ASurvivor::FindInteractableActor()
{
	IInteractable *InteractableActor = nullptr;
	FVector CameraLocation = Camera->GetComponentLocation();
	FRotator CameraRotation = Camera->GetComponentRotation();
	FVector CameraDirection = CameraRotation.Vector();

	FHitResult Hit;
	FVector Start = CameraLocation;
	FVector End = CameraLocation + CameraDirection * SearchRange;

	FCollisionQueryParams Param;
	Param.AddIgnoredActor(this);
	
	InteractableActor = nullptr;

	bool Succeed = GetWorld()->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(40),Param);
	if(Succeed)
	{
		ABaseItem *BaseItemClass = Cast<ABaseItem>(Hit.GetActor());
		if(BaseItemClass != nullptr)
		{
			InteractableActor = Cast<IInteractable>(BaseItemClass);
			UE_LOG(LogTemp, Warning, TEXT("Target : %s"), *Hit.GetActor()->GetName());
		}

		ABaseDoor *BaseDoorClass = Cast<ABaseDoor>(Hit.GetActor());
		if(BaseDoorClass != nullptr)
		{
			InteractableActor = Cast<IInteractable>(BaseDoorClass);
			UE_LOG(LogTemp, Warning, TEXT("Target : %s"), *Hit.GetActor()->GetName());
		}

		ABasePuzzle *BasePuzzleClass = Cast<ABasePuzzle>(Hit.GetActor());
		if(BasePuzzleClass != nullptr)
		{
			InteractableActor = Cast<IInteractable>(BasePuzzleClass);
			UE_LOG(LogTemp, Warning, TEXT("Target : %s"), *Hit.GetActor()->GetName());
		}
	}
    return InteractableActor;
}

void ASurvivor::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact key Action"));

	IInteractable *InteractableActor = FindInteractableActor();

	if(InteractableActor == nullptr)
		return;

	UE_LOG(LogTemp, Warning, TEXT("Interact key Action after"));

	InteractableActor->Interact(this);
}

void ASurvivor::InventoryActivate()
{
	if(InventoryWidget == nullptr)
		return;

	bUseInventory = !bUseInventory;
	
	if(bUseInventory)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		DisableInput(SurvivorPlayerController);
		SurvivorPlayerController->bShowMouseCursor = true;
	}
	else
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		EnableInput(SurvivorPlayerController);
		SurvivorPlayerController->bShowMouseCursor = false;
	}
}
