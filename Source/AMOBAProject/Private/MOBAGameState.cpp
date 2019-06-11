// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBAGameState.h"
#include "MOBAHeroCharacter.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "MOBABaseActor.h"
#include "MOBAPlayerController.h"

void AMOBAGameState::MultiCastOnGameOver_Implementation(Camp SuccessCamp)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AMOBAPlayerController* PC = Cast<AMOBAPlayerController>(It->Get());
		if (PC && PC->IsLocalController())
		{
			PC->OnGameOver(SuccessCamp);
			APlayerController* APC = Cast<APlayerController>(PC);
			if (APC)
			{
				PC->DisableInput(APC);
			}
		}
	}
}
