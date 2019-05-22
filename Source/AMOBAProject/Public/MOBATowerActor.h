// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "MOBATowerActor.generated.h"

UENUM()
enum TowerRoad { top, mid, down };

UENUM()
enum TowerType { outter, inner, highland, hub };

/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBATowerActor : public AMOBABaseActor
{
	GENERATED_BODY()

public:
	AMOBATowerActor(BaseProperty aBaseProperty, BaseValue aBaseValue, TowerRoad aRoad, TowerType aTowerType);
	AMOBATowerActor();

protected:

	bool bIsBroken;

	TowerRoad road;

	TowerType towerType;

public:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		TowerRoad getRoad();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		TowerType getTowerType();

};
