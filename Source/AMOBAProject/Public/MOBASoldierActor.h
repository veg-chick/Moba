// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "MOBASoldierActor.generated.h"

UENUM()
enum SoldierRoad { top, mid, down };

/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBASoldierActor : public AMOBABaseActor
{
	GENERATED_BODY()

public:
	AMOBASoldierActor();
	AMOBASoldierActor(BaseProperty aBaseProperty, BaseValue aBaseValue, SoldierRoad aRoad);

protected:
<<<<<<< HEAD
	//��·
	SoldierRoad road;

public:
	//��ȡ��·
=======
	SoldierRoad road;

public:
>>>>>>> c83824acd38368cd963a7467f290283660d3ff5a
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		SoldierRoad getRoad();


};
