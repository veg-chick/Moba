// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBASoldierCharacterController.h"
#include "MOBASoldierCharacter.h"

void AMOBASoldierCharacterController::OnPossess(APawn * Pawn)
{
	Super::Possess(Pawn);

	AMOBASoldierCharacter* SoldierCharacter = Cast<AMOBASoldierCharacter>(Pawn);

	if (SoldierCharacter) 
	{
		if (SoldierCharacter->BehaviorTree->BlackboardAsset) 
		{
			BlackboardComp->InitializeBlackboard(*(SoldierCharacter->BehaviorTree->BlackboardAsset));
		}

		BehaviorComp->StartTree(*SoldierCharacter->BehaviorTree);
	}

}

AMOBASoldierCharacterController::AMOBASoldierCharacterController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	LocationToGoKey = "LocationToGo";
	SoldierLocation = "CurSoldierLocation";

}
