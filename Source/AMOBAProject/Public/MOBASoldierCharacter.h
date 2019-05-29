// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseCharacter.h"
#include "MOBASoldierCharacter.generated.h"

UENUM(BlueprintType)
enum class SoldierRoad : uint8
{
	soldierTop UMETA(DisplayName = "soldierTop"),
	soldierMid UMETA(DisplayName = "soldierMid"),
	soldierDown UMETA(DisplayName = "soldierDown")
};


/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBASoldierCharacter : public AMOBABaseCharacter
{
	GENERATED_BODY()

public:
	AMOBASoldierCharacter();

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		SoldierRoad road;

	


public:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		SoldierRoad& GetRoad();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignSoldierValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, SoldierRoad aRoad);

};
