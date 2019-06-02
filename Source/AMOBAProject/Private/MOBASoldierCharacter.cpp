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
	//�������ܣ���һ��character����һ�� (Soldier,Hero,Tower)
	//����Ҫ�жϾ��룬�Ѿ��ƶ���������Χ��
	//��aһ�¾ͺ�

}

void AMOBASoldierCharacter::AttackToActorOnce(AMOBABaseActor * TargetToAttack)
{
	//�������ܣ���һ��actor����һ��(HubCrystal,Crystal)
	//����Ҫ�жϾ��룬�Ѿ��ƶ���������Χ��
	//��aһ�¾ͺ�

}



bool AMOBASoldierCharacter::IsEnemyHeroAttackingMyHero(AMOBABaseCharacter * EnemyHero)
{
	//����һ���з�hero���������з�hero�������ҷ�hero������true

	// TODO: �ڴ˴����� return ���
}


