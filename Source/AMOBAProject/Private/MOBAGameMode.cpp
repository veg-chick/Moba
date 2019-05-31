// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBAGameMode.h"
#include "TimerManager.h"
#include "MOBAPlayerController.h"
#include "MOBAPlayerState.h"
#include "MOBAHeroCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MOBABaseActor.h"
#include "GameFramework/GameModeBase.h"
#include "MOBAGameState.h"
#include "MOBACrystalActor.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"


AMOBAGameMode::AMOBAGameMode()
{

	PlayerControllerClass = AMOBAPlayerController::StaticClass();
	PlayerStateClass = AMOBAPlayerState::StaticClass();
	GameStateClass = AMOBAGameState::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/PushContent/Blueprint/BP_MOBAHeroCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMOBAGameMode::StartWave()
{
	NumberOfSoldierToSpawn = 7;

	GetWorldTimerManager().SetTimer(TimerHandle_SoldierSpawner, this, &AMOBAGameMode::SpawnSoldierTimerElapsed, 1.0f, true, 0.0f);
}

void AMOBAGameMode::SpawnSoldierTimerElapsed()
{
	
	int32 Soldiertype;

	if (NumberOfSoldierToSpawn > 4) Soldiertype = 0;
	else if (NumberOfSoldierToSpawn == 4) Soldiertype = 2;
	else Soldiertype = 1;


	NumberOfSoldierToSpawn--;

// 	FVector Location;
// 	for (TActorIterator<AMOBACrystalActor>It(GetWorld()); It; It++) 
// 	{
// 		SpawnNewSoldier(Soldiertype, It->GetActorLocation(), It->GetCamp());
// 	}

	SpawnNewSoldier(Soldiertype);

	if (NumberOfSoldierToSpawn <= 0) {
		EndWave();
	}
}

void AMOBAGameMode::EndWave()
{
	
	GetWorldTimerManager().ClearTimer(TimerHandle_SoldierSpawner);

	TimeBetweenWaves = 15.0f;

	PrepareForNextWave();
}

void AMOBAGameMode::PrepareForNextWave()
{
	FTimerHandle TimerHandle_NextWaveStart;

	GetWorldTimerManager().SetTimer(TimerHandle_NextWaveStart, this, &AMOBAGameMode::StartWave, TimeBetweenWaves, false);
}


void AMOBAGameMode::StartPlay()
{
	Super::StartPlay();

	TimeBetweenWaves = 30.0f;

	PrepareForNextWave();
}

void AMOBAGameMode::GameOver(Camp SuccessCamp)
{
	AMOBAGameState* GS = GetGameState<AMOBAGameState>();
	if (GS)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
		GS->MultiCastOnGameOver(SuccessCamp);
	}
}
