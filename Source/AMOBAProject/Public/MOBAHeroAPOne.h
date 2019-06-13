// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBAHeroCharacter.h"
#include "MOBAHeroAPOne.generated.h"

/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBAHeroAPOne : public AMOBAHeroCharacter
{
	GENERATED_BODY()

public:
	AMOBAHeroAPOne();

	virtual void Tick(float DeltaSeconds) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseQ(AMOBABaseCharacter* Target, float MpCost);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseW(float MpCost);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseE(AMOBAHeroCharacter* Target, float MpCost);

protected:
	bool bSkillIsStrengthed;

	FTimerHandle WTimerHandle;

	void WTimeHandle();

};
