// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBASoldierCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "Public/MOBAHeroCharacter.h"

AMOBASoldierCharacter::AMOBASoldierCharacter()
{
	this->SetValue();
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
		ServerRPCAttackToCharacterOnce(TargetToAttack);
	}
}

void AMOBASoldierCharacter::ServerRPCAttackToCharacterOnce_Implementation(AMOBABaseCharacter* TargetToAttack)
{
	this->GetbIsAttacking() = true;
	auto MyAttackStrength = this->GetAttackStrength();
	TargetToAttack->ReceiveDamageFromCharacter(TargetToAttack, DamageType::physical, MyAttackStrength, this);
	this->GetbAbleToAttack() = false;
	auto MyTimeHandle = this->AttackTimer;
	GetWorldTimerManager().ClearTimer(MyTimeHandle);
	auto AttackCDTime = 1.0f / GetAttackSpeed();
	GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBASoldierCharacter::ResetTimer, AttackCDTime);
}

bool AMOBASoldierCharacter::ServerRPCAttackToCharacterOnce_Validate(AMOBABaseCharacter* TargetToAttack)
{
	return true;
}

void AMOBASoldierCharacter::AttackToActorOnce(AMOBABaseActor * TargetToAttack)
{
	if (this->GetbAbleToAttack())
	{
		ServerRPCAttackToActorOnce(TargetToAttack);
	}
}



void AMOBASoldierCharacter::ServerRPCAttackToActorOnce_Implementation(AMOBABaseActor* TargetToAttack)
{
	this->GetbIsAttacking() = true;
	auto MyAttackStrength = this->GetAttackStrength();
	TargetToAttack->ReceiveDamageFromCharacter(TargetToAttack, DamageType::physical, MyAttackStrength, this);
	this->GetbAbleToAttack() = false;
	auto MyTimeHandle = this->AttackTimer;
	GetWorldTimerManager().ClearTimer(MyTimeHandle);
	auto AttackCDTime = 1.0f / GetAttackSpeed();
	GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBASoldierCharacter::ResetTimer, AttackCDTime);
}

bool AMOBASoldierCharacter::ServerRPCAttackToActorOnce_Validate(AMOBABaseActor* TargetToAttack)
{
	return true;
}

bool AMOBASoldierCharacter::IsEnemyHeroAttackingMyHero(AMOBAHeroCharacter * EnemyHero)
{
	if (EnemyHero->GetbIsAttackingHero())
		return true;
	return false;
}


void AMOBASoldierCharacter::ResetTimer()
{
	this->GetbIsAttacking() = false;
	this->GetbAbleToAttack() = true;
}

void AMOBASoldierCharacter::SoldierLevelUp()
{
	baseProperty.maxHp += 50.0f;
	baseProperty.hp += 50.0f;
	baseProperty.attackStrength += 10.0f;
}

void AMOBASoldierCharacter::SetValue()
{
	baseProperty.maxHp = 200.0f;
	baseProperty.hp = 200.0f;
	baseProperty.attackStrength = 20.0f;
	baseProperty.attackSpeed = 0.7f;
	baseProperty.moveSpeed = 600.0f;

	baseValue.experienceValue = 15.0f;
	baseValue.goldValue = 20.0f;

	baseProperty.bHaveMp = false;
	baseProperty.bCanBeAttacked = true;
	baseProperty.bCanMove = true;
	baseProperty.bAbleToAttack = true;

}


