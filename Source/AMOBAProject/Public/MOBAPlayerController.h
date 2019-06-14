// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MOBAPlayerController.generated.h"
enum class Camp : uint8;

UCLASS()
class AMOBAPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMOBAPlayerController();

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerController")
		void OnGameOver(Camp SuccessCamp);

protected:

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();
	
	void AttackToMouseCursor();

	void StopMove();

	void Recall();
};


