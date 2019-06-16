// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MOBAGameMode.generated.h"

enum class Camp : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActorKilled, AMOBABaseActor*, VictimActor, AMOBABaseCharacter*, KillerCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterKilled, AMOBABaseCharacter*, VictimCharacter, AMOBABaseCharacter*, KillerCharacter);

UCLASS()
class AMOBAPROJECT_API AMOBAGameMode : public AGameMode
{
	GENERATED_BODY()

protected:

	FTimerHandle TimerHandle_SoldierSpawner;

	int32 WaveCnt;

	UPROPERTY(BlueprintReadOnly, Category = "GameMode")
		int32 SoldierLevel;

	//The Number of Soldiers To Spawn In Current Wave
	UPROPERTY(BlueprintReadOnly, Category = "GameMode")
		int32 NumberOfSoldierToSpawn;

	//The Time Interval of Spawning Waves
	UPROPERTY(BlueprintReadWrite, Category = "GameMode")
		float TimeBetweenWaves;
	
protected:
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
		void SpawnNewSoldier(int32 SolderType);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
		void SpawnStartWild();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
		void SpawnStartDragon();

	void SpawnSoldierTimerElapsed();

	// Start Spawning Soldier
	void StartWave();

	// Stop Spawning Soldier
	void EndWave();

	// Set Timer For Next Wave
	void PrepareForNextWave(); 

public:

	AMOBAGameMode();

	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void GameOver(Camp SuccessCamp);

	UPROPERTY(BlueprintAssignable, Category = "GameMode")
		FOnActorKilled OnActorKilled;

	UPROPERTY(BlueprintAssignable, Category = "GameMode")
		FOnCharacterKilled OnCharacterKilled;
};
