// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseCharacter.h"
#include "MOBASoldierCharacter.generated.h"

UENUM()
enum SoldierRoad { top, mid, down };


/**
 * 
 */
UCLASS()
class AMOBAPROJECT_API AMOBASoldierCharacter : public AMOBABaseCharacter
{
	GENERATED_BODY()
	
public:
	AMOBASoldierCharacter();

protected:
	SoldierRoad road;

public:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		SoldierRoad getRoad();



};
