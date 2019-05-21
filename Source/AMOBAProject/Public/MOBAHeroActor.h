// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "MOBAHeroActor.generated.h"

//��ʱ������
struct FTimerHandle;

//Ӣ������
struct HeroProperty {
	//����ʱ��
	int resetTime;

	//�����ʼ������˺�
	float strikeRate;
	float strikeDamage;

	//����
	bool bIsInjured;

	//��Դ�͸
	float relativeArmorPenetration;
	float relativeMagicResistPenetration;

	//���Դ�͸
	int absoluteMagicResistPenetration;
	int absoluteArmorPentration;

	//����͵ȡ
	float lifeSteal;

};

//�ɳ�����
struct HeroGrowth {
	//�����ɳ��������ɳ�
	int hpGrowth;
	int mpGrowth;

	//�ָ��ɳ�
	float hpRecoveryGrowth;
	float mpRecoveryGrowth;

	//����ħ���ɳ�
	int armorGrowth;
	int magicResistGrowth;

	//�����������ٶȳɳ�
	int attackGrowth;
	float attackSpeedGrowth;

	//��Я������ֵ�ɳ�
	int experienceCarriedGrowth;

	//����ʱ��ɳ�
	int resetTimeGrowth;
};

//��ɱ����
struct HeroValue {
	//��Ǯ����
	int goldValue;

	//���齱��
	int experienceValue;

	//...

};

//������ȴʱ��͸���ʱ�䴦��
struct TimerHandles {
	//������ȴʱ��:Q,W,E,R
	FTimerHandle skillQTimer;
	FTimerHandle skillWTimer;
	FTimerHandle skillETimer;
	FTimerHandle skillRTimer;

	//����ʱ��
	FTimerHandle resetTimer;
};


/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBAHeroActor : public AMOBABaseActor
{
	GENERATED_BODY()

public:

	AMOBAHeroActor();
	AMOBAHeroActor(BaseProperty bP, BaseValue bV, HeroProperty hP, HeroGrowth hG, HeroValue hV);

protected:

	HeroProperty heroProperty;

	HeroGrowth heroGrowth;

	HeroValue heroValue;

	TimerHandles timeHandles;

protected:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetHero();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetQSkill();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetWSkill();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetESkill();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetRSkill();

};
