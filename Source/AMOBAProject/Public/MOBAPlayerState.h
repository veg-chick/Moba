// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MOBAPlayerState.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FScoreBoard
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float KillNumber = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float DeathNumber = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float CombKillNumber = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float SoldierKillNumber = 0.0f;
};


UCLASS()
class AMOBAPROJECT_API AMOBAPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "MOBA")
		FScoreBoard ScoreBoard;
	
public:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float GetKillNumber() { return ScoreBoard.KillNumber; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float GetDeathNumber() { return ScoreBoard.DeathNumber; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float GetCombKillNumber() { return ScoreBoard.CombKillNumber; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float GetSoldierKillNumber() { return ScoreBoard.SoldierKillNumber; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AddKillNumber() { ScoreBoard.KillNumber+= 1.0f; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AddDeathNumber() {  ScoreBoard.DeathNumber+= 1.0f; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AddSoldierKillNumber() {  ScoreBoard.SoldierKillNumber+= 1.0f; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AddCombKillNumber();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ClearCombKillNumber();
};

