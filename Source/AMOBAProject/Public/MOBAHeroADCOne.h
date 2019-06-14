// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBAHeroCharacter.h"
#include "MOBAHeroADCOne.generated.h"

/**
 * 
 */
UCLASS()
class AMOBAPROJECT_API AMOBAHeroADCOne : public AMOBAHeroCharacter
{
	GENERATED_BODY()

public:
	AMOBAHeroADCOne();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseQ(AMOBAHeroCharacter* Target,float MpCost);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseW(float MpCost);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseE(float MpCost);

protected:
	FTimerHandle WTimerHandle;

	FTimerHandle QTimerHandle;

	FTimerHandle ETimerHandle;

	AMOBAHeroCharacter* QAttackingHero;

	void WTimeHandle();

	void QTimeHandle();

	void ETimeHandle();
	
	float MyAttackSpeedAddValue;

	float MyLifeStealAddValue;

	float MyAttackStrengthAddValue;

};
