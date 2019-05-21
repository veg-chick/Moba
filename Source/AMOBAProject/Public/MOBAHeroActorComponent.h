// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActorComponent.h"
#include "MOBAHeroActorComponent.generated.h"

//状态
UENUM()
enum HeroState { alive, dead, silience, imprison, stun };

//背包
struct HeroPackage {

	int packageOne;
	int packageTwo;
	int packageThree;
	int packageFour;
	int packageFive;
	int packageSix;

};


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

// 	virtual void BeginPlay() override;

protected:
	/*
	//接受伤害
	virtual void applyDamage(AActor* damagedActor, DamageType damageType, int damage, AActor* damageCauser)override;

	//死亡
	virtual void deadHandle(AActor* deadActor, int deadTime)override;

	//攻击
	virtual void attack(AActor* damagedActor, DamageType DamageType, int damage, AActor* damageCauser)override;

	//能否进行攻击
	virtual bool canAttack(AActor* damagedActor, DamageType DamageType, int damage, AActor* damageCauser)override;

	*/
protected:
	//人物状态
	HeroState heroState;

};
