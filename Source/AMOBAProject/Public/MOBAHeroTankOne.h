// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBAHeroCharacter.h"
#include "MOBAHeroTankOne.generated.h"

/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBAHeroTankOne : public AMOBAHeroCharacter
{
	GENERATED_BODY()

public:
	AMOBAHeroTankOne();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseQ(AMOBAHeroCharacter* TargetHero, float MpCost = 0.0f);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseW(float MpCost = 0.0f);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseE(float MpCost = 0.0f);

protected:
	FTimerHandle WTimerHandle;

	FTimerHandle ETimerHandle;

	void WTimeHandle();

	void ETimeHandle();

	float RecoveryValue;

	
};
