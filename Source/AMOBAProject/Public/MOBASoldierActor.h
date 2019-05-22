// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "MOBASoldierActor.generated.h"

//分路:上路，中路，下路
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
	//分路
	SoldierRoad road;

public:
	//获取分路
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		SoldierRoad getRoad();


};
