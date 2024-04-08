// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDoor.h"

// Sets default values
ABaseDoor::ABaseDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseDoor::Interact(AActor *OtherActor)
{
    return false;
}