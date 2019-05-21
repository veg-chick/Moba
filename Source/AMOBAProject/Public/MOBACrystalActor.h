// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "MOBACrystalActor.generated.h"

//分路:上路，中路，下路
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
	//是否被摧毁
	bool bIsBroken;

	//分路
	CrystalRoad road;

public:
	//是否被摧毁
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool isBroken();

	//获取分路
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		CrystalRoad getRoad();


};
