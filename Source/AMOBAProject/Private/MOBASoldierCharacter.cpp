// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBASoldierCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "Public/MOBAHeroCharacter.h"

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

void AMOBASoldierCharacter::AttackToCharacterOnce(AMOBABaseCharacter* TargetToAttack)
{
	if (this->GetbAbleToAttack())
	{
		auto MyAttackStrength = this->GetAttackStrength();
		TargetToAttack->ReceiveDamageFromCharacter(TargetToAttack, DamageType::physical, MyAttackStrength, this);
		this->GetbAbleToAttack() = false;
		auto MyTimeHandle = this->AttackTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		auto AttackCDTime = 1.0f / GetAttackSpeed();
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBASoldierCharacter::ResetTimer, AttackCDTime);
	}
}

void AMOBASoldierCharacter::AttackToActorOnce(AMOBABaseActor * TargetToAttack)
{
	if (this->GetbAbleToAttack())
	{
		auto MyAttackStrength = this->GetAttackStrength();
		TargetToAttack->ReceiveDamageFromCharacter(TargetToAttack, DamageType::physical, MyAttackStrength, this);
		this->GetbAbleToAttack() = false;
		auto MyTimeHandle = this->AttackTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		auto AttackCDTime = 1.0f / GetAttackSpeed();
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBASoldierCharacter::ResetTimer, AttackCDTime);
	}
}



bool AMOBASoldierCharacter::IsEnemyHeroAttackingMyHero(AMOBAHeroCharacter * EnemyHero)
{
	if (EnemyHero->GetbIsAttackingHero())
		return true;
	return false;
}

void AMOBASoldierCharacter::ResetTimer()
{
	this->GetbAbleToAttack() = true;
}


