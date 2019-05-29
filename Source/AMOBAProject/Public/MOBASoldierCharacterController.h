// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MOBASoldierCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MOBASoldierCharacterController.generated.h"
/**
 * 
 */
UCLASS()
class AMOBAPROJECT_API AMOBASoldierCharacterController : public AAIController
{
	GENERATED_BODY()

	UBehaviorTreeComponent* BehaviorComp;

	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName LocationToGoKey;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName SoldierLocation;

	



public:
	virtual void OnPossess(APawn* Pawn) override;
	// DEPRECATED(4.22, "Posssess is marked virtual final as you should now be overriding OnPossess instead")

	AMOBASoldierCharacterController();

	UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

};
