// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseCharacter.h"
#include "MOBAHeroCharacter.generated.h"

//计时器声明
struct FTimerHandle;

//英雄属性
USTRUCT()
struct FHeroProperty {

	GENERATED_BODY()

		//复活时间
		int resetTime;

	//暴击率及暴击伤害
	float strikeRate;
	float strikeDamage;

	//重伤
	bool bIsInjured;

	//相对穿透
	float relativeArmorPenetration;
	float relativeMagicResistPenetration;

	//绝对穿透
	int absoluteMagicResistPenetration;
	int absoluteArmorPentration;

	//生命偷取
	float lifeSteal;

};

//成长属性
USTRUCT()
struct FHeroGrowth {

	GENERATED_BODY()

		//生命成长，法力成长
		int hpGrowth;
	int mpGrowth;

	//恢复成长
	float hpRecoveryGrowth;
	float mpRecoveryGrowth;

	//护甲魔抗成长
	int armorGrowth;
	int magicResistGrowth;

	//攻击力攻击速度成长
	int attackGrowth;
	float attackSpeedGrowth;

	//所携带经验值成长
	int experienceCarriedGrowth;

	//复活时间成长
	int resetTimeGrowth;
};

//击杀奖励
USTRUCT()
struct FHeroValue {

	GENERATED_BODY()

		//金钱奖励
		int goldValue;

	//经验奖励
	int experienceValue;

	//...

};

//技能冷却时间和复活时间处理
USTRUCT()
struct FTimerHandles {

	GENERATED_BODY()

		//技能冷却时间:Q,W,E,R
		FTimerHandle skillQTimer;
	FTimerHandle skillWTimer;
	FTimerHandle skillETimer;
	FTimerHandle skillRTimer;

	//复活时间
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
