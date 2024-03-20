// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEProjectGameMode.h"
#include "UEProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUEProjectGameMode::AUEProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
