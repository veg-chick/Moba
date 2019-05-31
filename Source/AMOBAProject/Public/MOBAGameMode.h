// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MOBAGameMode.generated.h"

enum class Camp : uint8;


UCLASS()
class AMOBAPROJECT_API AMOBAGameMode : public AGameMode
{
	GENERATED_BODY()

protected:

	FTimerHandle TimerHandle_SoldierSpawner;

	//The Number of Soldiers To Spawn In Current Wave
	UPROPERTY(BlueprintReadOnly, Category = "GameMode")
		int32 NumberOfSoldierToSpawn;

	//The Time Interval of Spawning Waves
	UPROPERTY(BlueprintReadWrite, Category = "GameMode")
		float TimeBetweenWaves;
	
protected:
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
		void SpawnNewSoldier(int32 SolderType);

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
};
