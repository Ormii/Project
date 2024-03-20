// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/Interactable.h"
#include "BaseDoor.generated.h"

UCLASS()
class UEPROJECT_API ABaseDoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool Interact(AActor* OtherActor) override;

	void SetDoorOpen(bool Open) {DoorOpen = Open;}
	bool GetDoorOpen() {return DoorOpen;}
private:
	bool DoorOpen;

};
