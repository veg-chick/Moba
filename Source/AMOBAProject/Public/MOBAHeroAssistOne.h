// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBAHeroCharacter.h"
#include "MOBAHeroAssistOne.generated.h"

/**
 * 
 */
UCLASS()
class AMOBAPROJECT_API AMOBAHeroAssistOne : public AMOBAHeroCharacter
{
	GENERATED_BODY()
	
public:
	AMOBAHeroAssistOne();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseQ(AMOBAHeroCharacter* Target,float MpCost);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseW(AMOBAHeroCharacter* Target,float MpCost);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReleaseE(AMOBAHeroCharacter* Target,float MpCost);

protected:

};
