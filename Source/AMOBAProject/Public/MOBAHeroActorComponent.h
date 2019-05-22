// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActorComponent.h"
#include "MOBAHeroActorComponent.generated.h"

//״̬
UENUM()
enum HeroState { alive, dead, silience, imprison, stun };

//����
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
	//�����˺�
	virtual void applyDamage(AActor* damagedActor, DamageType damageType, int damage, AActor* damageCauser)override;

	//����
	virtual void deadHandle(AActor* deadActor, int deadTime)override;

	//����
	virtual void attack(AActor* damagedActor, DamageType DamageType, int damage, AActor* damageCauser)override;

	//�ܷ���й���
	virtual bool canAttack(AActor* damagedActor, DamageType DamageType, int damage, AActor* damageCauser)override;

	*/
protected:
	//����״̬
	HeroState heroState;

};
