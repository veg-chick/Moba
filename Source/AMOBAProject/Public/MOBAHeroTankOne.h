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
