// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MOBAPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MOBAHeroCharacter.h"
#include "Engine/World.h"

AMOBAPlayerController::AMOBAPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMOBAPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AMOBAPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMOBAPlayerController::MoveToMouseCursor);
	InputComponent->BindAction("AttackTarget", IE_Pressed, this, &AMOBAPlayerController::AttackToMouseCursor);

}


void AMOBAPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		AMOBAHeroCharacter* MyCharacter = Cast<AMOBAHeroCharacter>(this->GetCharacter());
		MyCharacter->SetNewMoveDestination(Hit.ImpactPoint, MyCharacter->getMoveSpeed());
	}
}


void AMOBAPlayerController::AttackToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	AActor* HitResult = Hit.GetActor();
	AMOBABaseCharacter* BeAttackedCharacter = Cast<AMOBABaseCharacter>(HitResult);
	AMOBABaseActor* BeAttackedActor = Cast<AMOBABaseActor>(HitResult);

	AMOBAHeroCharacter* MyCharacter = Cast<AMOBAHeroCharacter>(this->GetCharacter());

	if (BeAttackedCharacter && BeAttackedCharacter->getCamp() != MyCharacter->getCamp() && BeAttackedCharacter->getBCanBeAttacked()) {
		MyCharacter->AttackToACharacter(BeAttackedCharacter);
	}
	else if (BeAttackedActor && BeAttackedActor->getCamp() != MyCharacter->getCamp() && BeAttackedActor->getBCanBeAttacked()) {
		MyCharacter->AttackToAActor(BeAttackedActor);
	}

}

