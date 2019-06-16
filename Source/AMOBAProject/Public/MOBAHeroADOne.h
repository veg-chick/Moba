// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBAHeroCharacter.h"
#include "MOBAHeroADOne.generated.h"

/**
 * 
 */
UCLASS()
class AMOBAPROJECT_API AMOBAHeroADOne : public AMOBAHeroCharacter
{
	GENERATED_BODY()
	
public:
	AMOBAHeroADOne();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseQ(AMOBAHeroCharacter* Target,float MpCost);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseW(float MpCost);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseE(float MpCost);

protected:

	float MyAttackStrengthAddValue;

	FTimerHandle WTimerHandle;

	FTimerHandle ETimerHandle;

	void WTimeHandle();

	void ETimeHandle();

};
