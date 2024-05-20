// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DrawDebugHelpers.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../PlayerController/BasePlayerController.h"
#include "../Interface/Interactable.h"
#include "../Compo/InventoryComponent.h"
#include "../Compo/HealthComponent.h"
#include "../Compo/EquipComponent.h"
#include "BaseTabUMGWidget.h"
#include "BaseExaminationWidget.h"
#include "UI/BaseGetItemNotify.h"
#include "BaseCrossHair.h"
#include "BaseItem.h"
#include "KnifeAttackItem.h"
#include "PistolAttackItem.h"
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
	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	Equipped = CreateDefaultSubobject<UEquipComponent>(TEXT("Equipped"));

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

	EquipedType = EEquipedType::EQUIPED_TYPE_UNARMED;
}

// Called every frame
void ASurvivor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if(Camera)
	{
		switch(EquipedType)
		{
			case EEquipedType::EQUIPED_TYPE_PISTOL:
			{
				if(IsZoomIn)
				{
					float FOV = Camera->FieldOfView;
					Camera->FieldOfView = UKismetMathLibrary::FInterpTo(Camera->FieldOfView,45.f,GetWorld()->DeltaTimeSeconds,3.0f);
					if(FMath::Abs(Camera->FieldOfView - 45.0f)<=5.0f && IsAttacking == false)
						IsAttackReady = true;
				}
				else
				{
					Camera->FieldOfView = UKismetMathLibrary::FInterpTo(Camera->FieldOfView,90.f,GetWorld()->DeltaTimeSeconds,3.0f);
					IsAttackReady = false;
				}
			}
				break;
			case EEquipedType::EQUIPED_TYPE_KNIFE:
				IsAttackReady = !IsAttacking;
				break;
			default:
				break;
		}
	}
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
		EnhancedInputComponent->BindAction(CrouchInputAction, ETriggerEvent::Completed, this, &ASurvivor::CrouchUnActivate);
		EnhancedInputComponent->BindAction(SprintInputAction,ETriggerEvent::Started,this, &ASurvivor::SprintActivate);
		EnhancedInputComponent->BindAction(SprintInputAction,ETriggerEvent::Completed,this,&ASurvivor::SprintUnActivate);
		EnhancedInputComponent->BindAction(ReloadInputAction,ETriggerEvent::Completed, this, &ASurvivor::Reload);
		EnhancedInputComponent->BindAction(TabInputAction, ETriggerEvent::Started, this, &ASurvivor::InventoryActivate);
		EnhancedInputComponent->BindAction(ZoomInInputAction, ETriggerEvent::Started, this, &ASurvivor::ZoomIn);
		EnhancedInputComponent->BindAction(ZoomInInputAction, ETriggerEvent::Completed, this, &ASurvivor::ZoomOut);
		EnhancedInputComponent->BindAction(EquipSlot1InputAction, ETriggerEvent::Triggered, this, &ASurvivor::EquipSlot1);
		EnhancedInputComponent->BindAction(EquipSlot2InputAction, ETriggerEvent::Triggered, this, &ASurvivor::EquipSlot2);
		EnhancedInputComponent->BindAction(EquipSlot3InputAction, ETriggerEvent::Triggered, this, &ASurvivor::EquipSlot3);
		EnhancedInputComponent->BindAction(EquipSlot4InputAction, ETriggerEvent::Triggered, this, &ASurvivor::EquipSlot4);
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

UEquipComponent *ASurvivor::GetEquipComponent()
{
    return Equipped;
}

void ASurvivor::SetCurrentAttackItem(ABaseAttackItem *Item)
{
	if(CurrentAttackItem)
	{
		CurrentAttackItem->Destroy();
	}

	CurrentAttackItem = nullptr;
	if(Item == nullptr)
	{
		EquipedType = EEquipedType::EQUIPED_TYPE_UNARMED;
		return;
	}

	switch(Item->GetItemData().ItemType)
	{
		case EItemType::EITEM_TYPE_DEFAULT_KNIFE:
			CurrentAttackItem = Cast<ABaseAttackItem>(GetWorld()->SpawnActor<AKnifeAttackItem>(AKnifeAttackItem::StaticClass()));
			break;
		case EItemType::EITEM_TYPE_DEFAULT_PISTOL:
			CurrentAttackItem = Cast<ABaseAttackItem>(GetWorld()->SpawnActor<APistolAttackItem>(APistolAttackItem::StaticClass()));
			break;
		default:
			return;
	}

	CurrentAttackItem->SetDetectSphereEnable(false);
	CurrentAttackItem->SetItemData(Item->GetItemData());
	CurrentAttackItem->SetItemMesh(Item->GetItemMesh());

	switch(CurrentAttackItem->GetItemData().ItemType)
	{
		case EItemType::EITEM_TYPE_DEFAULT_KNIFE:
			EquipedType = EEquipedType::EQUIPED_TYPE_KNIFE;
			CurrentAttackItem->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, TEXT("KnifeSocket"));
			CurrentAttackItem->SetOwner(this);
			break;
		case EItemType::EITEM_TYPE_DEFAULT_PISTOL:
			EquipedType = EEquipedType::EQUIPED_TYPE_PISTOL;
			CurrentAttackItem->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, TEXT("PistolSocket"));
			CurrentAttackItem->SetOwner(this);
			break;
		default:
			break;
	}
}

void ASurvivor::AddInteractItemCandiArray(ABaseItem * Item)
{
	InteractItemCandiArray.Add(Item);
}

void ASurvivor::RemoveInteractItemCandiArray(ABaseItem *Item)
{
	InteractItemCandiArray.Remove(Item);
}

void ASurvivor::Hit(AActor *OtherActor)
{
	
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

void ASurvivor::EquipSlot1()
{
	if(UseTab)
		return;

	if(Equipped)
	{
		ABaseAttackItem *AttackItem = Equipped->GetEquipItemAtIndex(0);
		SetCurrentAttackItem(AttackItem);
	}
}

void ASurvivor::EquipSlot2()
{
	if(UseTab)
		return;

	if(Equipped)
	{
		ABaseAttackItem *AttackItem = Equipped->GetEquipItemAtIndex(1);
		SetCurrentAttackItem(AttackItem);
	}
}

void ASurvivor::EquipSlot3()
{
	if(UseTab)
		return;
		
	if(Equipped)
	{
		ABaseAttackItem *AttackItem = Equipped->GetEquipItemAtIndex(2);
		SetCurrentAttackItem(AttackItem);
	}
}

void ASurvivor::EquipSlot4()
{
	if(Equipped)
	{
		ABaseAttackItem *AttackItem = Equipped->GetEquipItemAtIndex(3);
		SetCurrentAttackItem(AttackItem);
	}
}

void ASurvivor::CrouchActivate()
{
	if(UseTab)
		return;
	if(IsSprint)
		return;

	IsCrouch = true;
	UE_LOG(LogTemp, Warning, TEXT("Crouch!"));
	GetCharacterMovement()->Crouch();
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
	AnimationCrouchCamera();
}

void ASurvivor::CrouchUnActivate()
{
	if(IsCrouch == false)
		return;

	IsCrouch = false;
	UE_LOG(LogTemp, Warning, TEXT("Crouch Release!"));
	GetCharacterMovement()->UnCrouch();
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	AnimationUnCrouchCamera();
}

void ASurvivor::SprintActivate()
{
	if(UseTab)
		return;
	if(IsCrouch)
		return;
	
	IsSprint = true;
	UE_LOG(LogTemp, Warning, TEXT("Sprint!"));
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
}

void ASurvivor::SprintUnActivate()
{
	if(IsSprint == false)
		return;
	
	IsSprint = false;

	UE_LOG(LogTemp, Warning, TEXT("Sprint Release!"));
	GetCharacterMovement()->MaxWalkSpeed = 200.f;

}

void ASurvivor::ZoomIn()
{
	if(CurrentAttackItem == nullptr)
		return;

	switch(EquipedType)
	{
		case EEquipedType::EQUIPED_TYPE_PISTOL:
		{
			APistolAttackItem *pPistolAtkItem = Cast<APistolAttackItem>(CurrentAttackItem);
			if(SurvivorPlayerController && pPistolAtkItem)
			{
				SurvivorPlayerController->GetCrossHairWidget()->Init(pPistolAtkItem->GetMaxChargeTime());
				SurvivorPlayerController->GetCrossHairWidget()->SetVisibility(ESlateVisibility::Visible);
			}
		}
			break;
		default:
			return;
			break;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("ZoomIn Start"));
	IsZoomIn = true;
}

void ASurvivor::ZoomOut()
{
	UE_LOG(LogTemp, Warning, TEXT("ZoomOut Start"));

	if(SurvivorPlayerController)
	{
		SurvivorPlayerController->GetCrossHairWidget()->Release();
		SurvivorPlayerController->GetCrossHairWidget()->SetVisibility(ESlateVisibility::Hidden);
	}

	IsZoomIn = false;
}

void ASurvivor::Attack()
{
	if(CurrentAttackItem == nullptr)
		return;

	UE_LOG(LogTemp, Warning, TEXT("AttackStart"));
	if(IsAttacking == true || IsAttackReady == false)
		return;

	switch(EquipedType)
	{
		case EEquipedType::EQUIPED_TYPE_PISTOL:
		{
			UE_LOG(LogTemp, Warning, TEXT("PistolAttackStart"));
			if(IsZoomIn == false)
				return;

			APistolAttackItem *pPistolAttackItem = Cast<APistolAttackItem>(CurrentAttackItem);
			if(pPistolAttackItem != nullptr)
			{
				if(pPistolAttackItem->GetCurChargedBullet() <= 0)
					return;

				UE_LOG(LogTemp, Warning, TEXT("Bullet Fire"));
				PossessPistolAttackMontage();
				pPistolAttackItem->Fire();
			}
		}
			break;
		case EEquipedType::EQUIPED_TYPE_KNIFE:
			UE_LOG(LogTemp, Warning, TEXT("KnifeAttackStart"));
			PossessKnifeAttackMontage();
			break;
		default:
			break;
	}
	
	IsAttacking = true;
	IsAttackReady = false;
	UE_LOG(LogTemp, Warning, TEXT("Attack!"));
}

void ASurvivor::Reload()
{
	if(CurrentAttackItem == nullptr)
		return;

	switch(CurrentAttackItem->GetItemData().ItemType)
	{
		case EItemType::EITEM_TYPE_DEFAULT_PISTOL:
		{
			APistolAttackItem *pPistolAtkItem = Cast<APistolAttackItem>(CurrentAttackItem);
			if(pPistolAtkItem == nullptr)
				return;
			
			if(pPistolAtkItem->GetCurChargedBullet() < pPistolAtkItem->GetMaxChargedBullet())
			{
				UE_LOG(LogTemp, Warning, TEXT("Reload Action Start!!!"));
				PossessPistolReloadMontage();
			}
		}
			break;
		default:
			return;
	}
}

void ASurvivor::PossessPistolAttackMontage()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if(IsCrouch)
	{
		animInstance->Montage_Play(PistolAttackCrouchActionMontage);
	}
	else
	{
		animInstance->Montage_Play(PistolAttackActionMontage);
	}
}

void ASurvivor::PossessKnifeAttackMontage()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if(IsCrouch)
	{
		animInstance->Montage_Play(KnifeAttackCrouchActionMontage);
	}
	else
	{
		animInstance->Montage_Play(KnifeAttackActionMontage);
	}
}

void ASurvivor::PossessPistolReloadMontage()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if(IsCrouch)
	{
		UE_LOG(LogTemp, Warning, TEXT("Reload Crouch Play"));
		animInstance->Montage_Play(PistolReloadCrouchActionMontage);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Reload Play"));
		animInstance->Montage_Play(PistolReloadActionMontage);
	}
}

IInteractable *ASurvivor::FindInteractItemActor()
{
	if(Camera == nullptr)
		return nullptr;

	IInteractable *InteractableActor = nullptr;
	for(int i = 0; i < InteractItemCandiArray.Num(); ++i)
	{
		ABaseItem* Item = InteractItemCandiArray[i];
		if(Item == nullptr)
			continue;
		
		InteractableActor = Item;
		break;
	}

	return InteractableActor;
}

void ASurvivor::Interact()
{
	if(UseTab == true)
		return;

	if(IsZoomIn == true)
	{
		Attack();
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Interact key Action"));

	IInteractable *InteractableActor = FindInteractItemActor();

	if(InteractableActor == nullptr)
	{
		Attack();
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Interact key Action after"));
	RemoveInteractItemCandiArray(Cast<ABaseItem>(InteractableActor));

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

	if(PlayerController->GetItemNotifyWidgetFunc()->GetVisibility() == ESlateVisibility::Visible)
		return;

	UseTab = !UseTab;

	if(UseTab)
	{
		UE_LOG(LogTemp, Warning, TEXT("Activate :%d"), UseTab);	
		TabWidget->SetVisibility(ESlateVisibility::Visible);

		UBaseExaminationWidget *ExaminationWidget = TabWidget->GetExaminationWidget();
        if(ExaminationWidget)
        {
            ExaminationWidget->SetVisibility(ESlateVisibility::Collapsed);
        }

		GetSurvivorPlayerController()->SetIgnoreLookInput(true);
		GetCharacterMovement()->DisableMovement();
		
		SurvivorPlayerController->bShowMouseCursor = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Activate :%d"), UseTab);	
		TabWidget->SetVisibility(ESlateVisibility::Hidden);

		UBaseExaminationWidget *ExaminationWidget = TabWidget->GetExaminationWidget();
        if(ExaminationWidget)
        {
            ExaminationWidget->SetVisibility(ESlateVisibility::Collapsed);
        }

		GetSurvivorPlayerController()->SetIgnoreLookInput(false);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

		SurvivorPlayerController->bShowMouseCursor = false;
	}
}
