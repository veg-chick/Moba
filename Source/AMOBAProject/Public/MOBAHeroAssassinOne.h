// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBAHeroCharacter.h"
#include "MOBAHeroAssassinOne.generated.h"

/**
 * 
 */
UCLASS()
class AMOBAPROJECT_API AMOBAHeroAssassinOne : public AMOBAHeroCharacter
{
	GENERATED_BODY()

public:
	AMOBAHeroAssassinOne();

	virtual void Tick(float DeltaSeconds) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseQ(AMOBAHeroCharacter* Target,float MpCost);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseW(float MpCost);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseE(AMOBAHeroCharacter* Target,float MpCost);

protected:

	FTimerHandle WTimerHandle;

	FTimerHandle ETimerHandle;
	
	void WTimeHandle();

	void ETimeHandle();

	float MyStrikeRateAddValue;

	float MyStrikeDamageAddValue;
};
