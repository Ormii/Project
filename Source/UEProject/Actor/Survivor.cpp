// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../PlayerController/BasePlayerController.h"
#include "../Interface/Interactable.h"
#include "../Compo/InventoryComponent.h"
#include "BaseTabUMGWidget.h"
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
}

// Called when the game starts or when spawned
void ASurvivor::BeginPlay()
{
	Super::BeginPlay();

	SurvivorPlayerController = Cast<ABasePlayerController>(GetController());

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	if(SurvivorPlayerController)
	{
		SurvivorPlayerController->PlayerCameraManager->ViewPitchMin = -45;
		SurvivorPlayerController->PlayerCameraManager->ViewPitchMax = 45;
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

	if(UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ASurvivor::Move);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ASurvivor::Look);
		EnhancedInputComponent->BindAction(InteractInputAction, ETriggerEvent::Started, this, &ASurvivor::Interact);
		EnhancedInputComponent->BindAction(CrouchInputAction, ETriggerEvent::Started, this, &ASurvivor::CrouchActivate);
		EnhancedInputComponent->BindAction(CrouchInputAction, ETriggerEvent::Completed, this, &ASurvivor::UnCrouchActivate);
		EnhancedInputComponent->BindAction(TabInputAction, ETriggerEvent::Started, this, &ASurvivor::InventoryActivate);
	}
}

FVector ASurvivor::GetCameraLocation(void)
{
    return (Camera != nullptr) ? Camera->GetComponentLocation() : FVector::ZeroVector;
}

UInventoryComponent *ASurvivor::GetInventoryComponent()
{
    return Inventory;
}


void ASurvivor::Move(const FInputActionValue &value)
{
	const FVector2D MoveVector2D = value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MoveVector2D.Y);
	AddMovementInput(GetActorRightVector(), MoveVector2D.X);
}

void ASurvivor::Look(const FInputActionValue &value)
{
	const FVector2D LookVector2D = value.Get<FVector2D>();
	AddControllerPitchInput(LookVector2D.Y * RotationRate * GetWorld()->GetDeltaSeconds());
	AddControllerYawInput(LookVector2D.X * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ASurvivor::CrouchActivate()
{
	IsCrouch = true;
	UE_LOG(LogTemp, Warning, TEXT("Crouch!"));
	GetCharacterMovement()->Crouch();
	AnimationCrouchCamera();
}

void ASurvivor::UnCrouchActivate()
{
	IsCrouch = false;
	UE_LOG(LogTemp, Warning, TEXT("UnCrouch!"));
	GetCharacterMovement()->UnCrouch();
	AnimationUnCrouchCamera();
}

IInteractable *ASurvivor::FindInteractableActor()
{
	if(Camera == nullptr)
		return nullptr;

	if(UseTab == true)
		return nullptr;

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
	ABasePlayerController *PlayerController = Cast<ABasePlayerController>(GetController());
	if(PlayerController == nullptr)
		return;

	UBaseTabUMGWidget* TabWidget = PlayerController->GetTabWidget();
	if(TabWidget == nullptr)
		return;

	UseTab = !UseTab;

	if(UseTab)
	{
		UE_LOG(LogTemp, Warning, TEXT("Activate :%d"), UseTab);	
		TabWidget->SetVisibility(ESlateVisibility::Visible);
		GetController()->SetIgnoreLookInput(true);
		GetCharacterMovement()->DisableMovement();
		
		SurvivorPlayerController->bShowMouseCursor = true;
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Activate :%d"), UseTab);	
		TabWidget->SetVisibility(ESlateVisibility::Hidden);
		GetController()->SetIgnoreLookInput(false);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

		SurvivorPlayerController->bShowMouseCursor = false;
	}
}
