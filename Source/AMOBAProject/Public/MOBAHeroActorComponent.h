// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActorComponent.h"
#include "MOBAHeroActorComponent.generated.h"

/**
 * 
 */
UCLASS()
class AMOBAPROJECT_API UMOBAHeroActorComponent : public UMOBABaseActorComponent
{
	GENERATED_BODY()
	

public:

	UMOBAHeroActorComponent();

protected:
	HeroState heroState;

};
