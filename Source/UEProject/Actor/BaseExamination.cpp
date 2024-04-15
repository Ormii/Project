// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BaseExamination.h"

// Sets default values
ABaseExamination::ABaseExamination()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABaseExamination::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseExamination::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

