// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "MOBATowerActor.generated.h"

//分路:上路，中路，下路
UENUM()
enum TowerRoad { top, mid, down };

//类型:一塔，二塔，高地塔，门牙塔
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
	//获取防御塔分路
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		TowerRoad getRoad();

	//获取防御塔类型
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		TowerType getTowerType();

};
