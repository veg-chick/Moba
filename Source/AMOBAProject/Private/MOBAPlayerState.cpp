// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBAPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "MOBAHeroCharacter.h"

void AMOBAPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMOBAPlayerState, ScoreBoard);
}

void AMOBAPlayerState::AddCombKillNumber()
{
	ScoreBoard.CombKillNumber += 1.0f;
	if (GetCombKillNumber() <= 8.0f)
	{
		AMOBAHeroCharacter* MyCharacter = Cast<AMOBAHeroCharacter>(this->GetPawn());
		if (MyCharacter)
		{
			MyCharacter->GetGoldValue() += 50.0f;
		}
	}
}

void AMOBAPlayerState::ClearCombKillNumber()
{
	AMOBAHeroCharacter* MyCharacter = Cast<AMOBAHeroCharacter>(this->GetPawn());
	if (MyCharacter)
	{
		MyCharacter->GetGoldValue() -= 50.0f * (ScoreBoard.CombKillNumber > 8.0f ? 8.0f : ScoreBoard.CombKillNumber);
	}
	ScoreBoard.CombKillNumber = 0.0f;

}
