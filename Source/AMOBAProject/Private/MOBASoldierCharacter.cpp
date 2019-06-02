// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBASoldierCharacter.h"

AMOBASoldierCharacter::AMOBASoldierCharacter()
{

}

SoldierRoad& AMOBASoldierCharacter::GetRoad()
{
	return road;
}

void AMOBASoldierCharacter::assignSoldierValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, SoldierRoad aRoad){

	assignBaseValueForAPI(aBaseProperty, aBaseValue);
	this->road = aRoad;

}

void AMOBASoldierCharacter::AttackToCharacterOnce(AMOBABaseCharacter * TargetToAttack)
{
	//函数功能：对一个character攻击一次 (Soldier,Hero,Tower)
	//不需要判断距离，已经移动到攻击范围内
	//简单a一下就好

}

void AMOBASoldierCharacter::AttackToActorOnce(AMOBABaseActor * TargetToAttack)
{
	//函数功能：对一个actor攻击一次(HubCrystal,Crystal)
	//不需要判断距离，已经移动到攻击范围内
	//简单a一下就好

}



bool AMOBASoldierCharacter::IsEnemyHeroAttackingMyHero(AMOBABaseCharacter * EnemyHero)
{
	//传入一个敌方hero，如果这个敌方hero攻击了我方hero，返回true

	// TODO: 在此处插入 return 语句
}


