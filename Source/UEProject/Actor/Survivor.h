// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Survivor.generated.h"

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
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	class IInteractable* FindInteractableActor();
	void Interact();

	UFUNCTION(BlueprintCallable)
	void InventoryActivate();
private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *SpringArm;
	
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent *Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Components", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent *Inventory;

	UPROPERTY(EditAnywhere, Category = "Control", meta = (AllowPrivateAccess = "true"))
	float RotationRate = 30.0f;

	UPROPERTY(EditAnywhere, Category = "Survivor Property", meta = (AllowPrivateAccess = "true"))
	float SearchRange = 500.0f;

	UPROPERTY()
	UClass* InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UUserWidget *InventoryWidget;

	APlayerController *SurvivorPlayerController;
	bool bUseInventory = false;
};
