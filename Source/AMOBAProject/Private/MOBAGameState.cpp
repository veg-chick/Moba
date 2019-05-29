// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBAGameState.h"
#include "MOBAHeroCharacter.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "MOBABaseActor.h"
#include "MOBAPlayerController.h"

void AMOBAGameState::MultiCastOnGameOver_Implementation(Camp SuccessCamp)
{
	for (auto It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AMOBAPlayerController* PC = Cast<AMOBAPlayerController>(It->Get());
		if (PC && PC->IsLocalController())
		{
			PC->OnGameOver(SuccessCamp);
			AMOBAHeroCharacter* MyCharacter = Cast<AMOBAHeroCharacter>(PC->GetCharacter());
			if (MyCharacter) 
			{
				UE_LOG(LogTemp, Warning, TEXT("MultiGame Over!"));
				MyCharacter->DisableInput(PC);
				MyCharacter->InputComponent = nullptr;
			}
		}
	}
}
