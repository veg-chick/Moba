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

	//�����ʱ��
	FTimerHandle wildResetTimeHanlde;

	//����ս������ٻָ�
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void quickRecovery();

	//��TimeHanlde�󶨵ĸ����
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetWild();


};
