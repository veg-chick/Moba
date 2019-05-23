// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseCharacter.h"
#include "MOBAWildCharacter.generated.h"

struct FTimerHandle;


/**
 * 
 */
UCLASS()
class AMOBAPROJECT_API AMOBAWildCharacter : public AMOBABaseCharacter
{
	GENERATED_BODY()
	
public:

	AMOBAWildCharacter();


protected:

	FTimerHandle wildResetTimeHanlde;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void quickRecovery();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetWild();

	//UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignWildValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue);


};
