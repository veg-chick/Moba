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

protected:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		virtual void ReleaseQ() override;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		virtual void ReleaseW() override;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		virtual void ReleaseE() override;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		virtual void ReleaseR() override;

	
};
