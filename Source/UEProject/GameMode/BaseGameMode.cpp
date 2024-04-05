// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BaseGameMode.h"
#include "BaseGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Actor/Survivor.h"
#include "../PlayerController/BasePlayerController.h"

void ABaseGameMode::BeginPlay()
{
    Survivor = Cast<ASurvivor>(UGameplayStatics::GetPlayerPawn(this,0));
    BasePlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}