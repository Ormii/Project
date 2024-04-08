// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
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
class UEPROJECT_API ASurvivor : public ACharacter
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
	APlayerController* GetSurvivorPlayerController(){return SurvivorPlayerController;}

public:
	UFUNCTION(BlueprintCallable)
	class UInventoryComponent * GetInventoryComponent();

private:
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void CrouchActivate();
	void UnCrouchActivate();

	class IInteractable* FindInteractableActor();
	void Interact();

	UFUNCTION(BlueprintCallable)
	void InventoryActivate();

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


	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext *InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* CrouchInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TabInputAction;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (AllowPrivateAccess = "true"))
	float RotationRate = 30.0f;

	UPROPERTY(EditAnywhere, Category = "Survivor Property", meta = (AllowPrivateAccess = "true"))
	float SearchRange = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control", meta = (AllowPrivateAccess= "true"))
	bool UseTab = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control", meta = (AllowPrivateAccess = "true"))
	bool IsCrouch = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Control", meta = (AllowPrivateAccess = "true"))
	EEquipedType EquipedType;


	APlayerController *SurvivorPlayerController;
};
