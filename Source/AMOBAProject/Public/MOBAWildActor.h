// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "MOBAWildActor.generated.h"

struct FTimerHandle;

/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBAWildActor : public AMOBABaseActor
{
	GENERATED_BODY()

public:

	AMOBAWildActor();
	AMOBAWildActor(BaseProperty aBaseProperty, BaseValue aBaseValue);

protected:

	//复活计时器
	FTimerHandle wildResetTimeHanlde;

	//脱离战斗后快速恢复
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void quickRecovery();

	//与TimeHanlde绑定的复活函数
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetWild();


};
