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
