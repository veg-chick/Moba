// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "MOBACrystalActor.generated.h"

UENUM()
enum CrystalRoad { top, mid, down };

/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBACrystalActor : public AMOBABaseActor
{
	GENERATED_BODY()

public:
	AMOBACrystalActor();

	AMOBACrystalActor(BaseProperty ABaseProperty, BaseValue aBaseValue, CrystalRoad aRoad);

protected:
	bool bIsBroken;

	CrystalRoad road;

public:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool isBroken();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		CrystalRoad getRoad();


};
