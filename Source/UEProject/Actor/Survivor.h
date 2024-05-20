// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseAttackItem.h"
#include "Hitable.h"
#include "Survivor.generated.h"


UENUM(BlueprintType)
enum class EEquipedType : uint8
{
	EQUIPED_TYPE_UNARMED UMETA(DisplayName = "Unarmed"),
	EQUIPED_TYPE_KNIFE UMETA(DisplayName = "Knife"),
	EQUIPED_TYPE_PISTOL UMETA(DisplayName = "Pistol"),
};

class UInputMappingContext;
class UInputAction;

UCLASS()
class UEPROJECT_API ASurvivor : public ACharacter, public IHitable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASurvivor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector GetCameraLocation(void);
	class ABasePlayerController* GetSurvivorPlayerController(){return SurvivorPlayerController;}

public:
	UFUNCTION(BlueprintCallable)
	class UInventoryComponent * GetInventoryComponent();

	UFUNCTION(BlueprintCallable)
	class UEquipComponent * GetEquipComponent();

	void SetEquipedType(EEquipedType aEquipedType) {EquipedType = aEquipedType;}
	void SetCurrentAttackItem(ABaseAttackItem *Item);

	void SetIsAttacking(bool bIsAttacking){IsAttacking = bIsAttacking;}
	ABaseAttackItem *GetCurrentAttackItem(){return CurrentAttackItem;}

	UFUNCTION(BlueprintCallable)
	void AddInteractItemCandiArray(class ABaseItem* Item);
	
	UFUNCTION(BlueprintCallable)
	void RemoveInteractItemCandiArray(class ABaseItem* Item);

	virtual void Hit(AActor* OtherActor) override;

	UFUNCTION(BlueprintCallable)
	void InventoryActivate();

private:
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void EquipSlot1();
	void EquipSlot2();
	void EquipSlot3();
	void EquipSlot4();
	void CrouchActivate();
	void CrouchUnActivate();
	void SprintActivate();
	void SprintUnActivate();
	void ZoomIn();
	void ZoomOut();
	void Attack();
	void Reload();

	void PossessPistolAttackMontage();
	void PossessKnifeAttackMontage();
	void PossessPistolReloadMontage();

	class IInteractable* FindInteractItemActor();
	void Interact();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void AnimationCrouchCamera();

	UFUNCTION(BlueprintImplementableEvent)
	void AnimationUnCrouchCamera();
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent *Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent *Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UEquipComponent* Equipped;


	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext *InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* CrouchInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ReloadInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TabInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ZoomInInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EquipSlot1InputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EquipSlot2InputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EquipSlot3InputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EquipSlot4InputAction;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (AllowPrivateAccess = "true"))
	float RotationRate = 30.0f;

	UPROPERTY(EditAnywhere, Category = "Survivor Property", meta = (AllowPrivateAccess = "true"))
	float SearchRange = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control", meta = (AllowPrivateAccess= "true"))
	bool UseTab = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control", meta = (AllowPrivateAccess = "true"))
	bool IsCrouch = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control", meta = (AllowPrivateAccess = "true"))
	bool IsSprint = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control", meta = (AllowPrivateAccess = "true"))
	bool IsZoomIn = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control", meta = (AllowPrivateAccess = "true"))
	bool IsAttackReady = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control", meta = (AllowPrivateAccess = "true"))
	bool IsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Control", meta = (AllowPrivateAccess = "true"))
	EEquipedType EquipedType = EEquipedType::EQUIPED_TYPE_UNARMED;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interact", meta = (AllowPrivateAccess ="true"))
	TArray<ABaseItem*> InteractItemCandiArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> PistolAttackActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> PistolAttackCrouchActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> KnifeAttackActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> KnifeAttackCrouchActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> PistolReloadActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> PistolReloadCrouchActionMontage;
	
	class ABasePlayerController *SurvivorPlayerController;
	ABaseAttackItem *CurrentAttackItem = nullptr;
};
