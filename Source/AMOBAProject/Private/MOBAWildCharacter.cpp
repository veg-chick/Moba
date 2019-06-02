// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBAWildCharacter.h"
#include "Engine/EngineTypes.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"

AMOBAWildCharacter::AMOBAWildCharacter()
{
	
}

void AMOBAWildCharacter::quickRecovery()
{

	auto myMaxHp = this->baseProperty.maxHp;
	auto& myHp = this->baseProperty.hp;

	myHp = FMath::Clamp(myMaxHp, 0.0f, myMaxHp);

}

void AMOBAWildCharacter::resetWild()
{
	//Move Back To Birth Location 

	quickRecovery();
}

void AMOBAWildCharacter::assignWildValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue){

	assignBaseValueForAPI(aBaseProperty, aBaseValue);

}

void AMOBAWildCharacter::BeginPlay()
{
	Super::BeginPlay();

	birthLocation = GetActorLocation();
}

void AMOBAWildCharacter::AttackToCharacterOnce(AMOBABaseCharacter * TargetToAttack)
{
	//函数功能：对一个character攻击一次 (Soldier,Hero)
	//不需要判断距离，已经移动到攻击范围内
	//简单a一下就好
}



AMOBABaseCharacter & AMOBAWildCharacter::GetAttacker()
{

	//函数功能：先判断自身是否被攻击，若自身被攻击，则返回攻击者
	// TODO: 在此处插入 return 语句
}
