// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "MOBAHubCrystalActor.generated.h"

/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBAHubCrystalActor : public AMOBABaseActor
{
	GENERATED_BODY()

public:
	AMOBAHubCrystalActor();
	AMOBAHubCrystalActor(BaseProperty aBaseProperty, BaseValue aBaseValue);

};
