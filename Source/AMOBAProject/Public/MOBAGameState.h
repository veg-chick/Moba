// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MOBAGameState.generated.h"


enum class Camp : uint8;
/**
 * 
 */
UCLASS()
class AMOBAPROJECT_API AMOBAGameState : public AGameState
{
	GENERATED_BODY()

public:
	UFUNCTION(NetMulticast, Reliable)
	void MultiCastOnGameOver(Camp SuccessCamp);
	
};
