// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBAWildCharacter.h"
#include "Engine/EngineTypes.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"

AMOBAWildCharacter::AMOBAWildCharacter()
{
	this->SetValue();
}

void AMOBAWildCharacter::QuickRecovery()
{
	this->GetbIsBeingAttacked() = false;

	auto myMaxHp = this->baseProperty.maxHp;
	auto& myHp = this->baseProperty.hp;

	myHp = FMath::Clamp(myMaxHp, 0.0f, myMaxHp);

}

void AMOBAWildCharacter::resetWild()
{
	//Move Back To Birth Location 

	QuickRecovery();

	this->GetbIsBeingAttacked() = false;

}

void AMOBAWildCharacter::assignWildValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue){

	assignBaseValueForAPI(aBaseProperty, aBaseValue);

}

void AMOBAWildCharacter::BeginPlay()
{
	Super::BeginPlay();

	birthLocation = GetActorLocation();
}

void AMOBAWildCharacter::ResetTimer()
{
	this->GetbAbleToAttack() = true;
}

void AMOBAWildCharacter::SetValue()
{
	baseProperty.hp = 800.0f;
	baseProperty.maxHp = 800.0f;
	baseProperty.armor = 50.0f;
	baseProperty.magicResist = 50.0f;
	baseProperty.attackSpeed = 1.0f;
	baseProperty.attackStrength = 80.0f;
	baseProperty.attackRange = 100.0f;
	baseProperty.moveSpeed = 800.0f;

	baseProperty.bAbleToAttack = true;
	baseProperty.bCanBeAttacked = true;
	baseProperty.bCanMove = true;

	baseValue.experienceValue = 3.0f;
	baseValue.goldValue = 50.0f;
}

void AMOBAWildCharacter::WildLevelUp()
{
	baseProperty.hp += 400.0f;
	baseProperty.maxHp += 400.0f;
	baseProperty.armor += 10.0f;
	baseProperty.magicResist += 10.0f;
	baseProperty.attackStrength = 40.0f;
	baseValue.goldValue += 40.0f;
}

void AMOBAWildCharacter::AttackToCharacterOnce(AMOBABaseCharacter * TargetToAttack)
{
	if (this->GetbAbleToAttack())
	{
		this->GetbIsAttacking() = true;
		auto MyAttackStrength = this->GetAttackStrength();
		TargetToAttack->ReceiveDamageFromCharacter(TargetToAttack, DamageType::physical, MyAttackStrength, this);
		this->GetbAbleToAttack() = false;
		auto MyTimeHandle = this->AttackTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		auto AttackCDTime = 1.0f / GetAttackSpeed();
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAWildCharacter::ResetTimer, AttackCDTime); 
		this->GetbIsAttacking() = false;
	}
}



AMOBABaseCharacter* AMOBAWildCharacter::GetAttacker()
{
	if (GetbIsBeingAttacked())
	{
		return Attacker;
	}
	return nullptr;
}
