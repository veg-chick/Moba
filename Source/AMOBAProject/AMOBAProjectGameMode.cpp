// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AMOBAProjectGameMode.h"
#include "AMOBAProjectPlayerController.h"
#include "AMOBAProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAMOBAProjectGameMode::AAMOBAProjectGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AAMOBAProjectPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}