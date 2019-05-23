// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseCharacter.h"
#include "MOBAHeroCharacter.generated.h"

//��ʱ������
struct FTimerHandle;

//Ӣ������
USTRUCT()
struct FHeroProperty {

	GENERATED_BODY()

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
USTRUCT()
struct FHeroGrowth {

	GENERATED_BODY()

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
USTRUCT()
struct FHeroValue {

	GENERATED_BODY()

		//��Ǯ����
		int goldValue;

	//���齱��
	int experienceValue;

	//...

};

//������ȴʱ��͸���ʱ�䴦��
USTRUCT()
struct FTimerHandles {

	GENERATED_BODY()

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
class AMOBAPROJECT_API AMOBAHeroCharacter : public AMOBABaseCharacter
{
	GENERATED_BODY()
	
public:
	AMOBAHeroCharacter();

protected:

	FHeroProperty heroProperty;

	FHeroGrowth heroGrowth;

	FHeroValue heroValue;

	FTimerHandles timeHandles;

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
