// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "MOBASoldierActor.generated.h"
/*
UENUM()
enum SoldierRoad { top, mid, down };
*/
/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBASoldierActor : public AMOBABaseActor
{
	GENERATED_BODY()

public:
	AMOBASoldierActor();
	/*
protected:
	SoldierRoad road;

public:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		SoldierRoad getRoad();
		*/

};
