// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBAWildCharacter.h"
#include "Engine/EngineTypes.h"
#include "Public/MOBAHeroCharacter.h"
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

void AMOBAWildCharacter::assignWildValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue) 
{
	assignBaseValueForAPI(aBaseProperty, aBaseValue);
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
	baseProperty.attackRange = 200.0f;
	baseProperty.moveSpeed = 700.0f;
	baseProperty.baseCamp = Camp::other;

	baseProperty.bAbleToAttack = true;
	baseProperty.bCanBeAttacked = true;
	baseProperty.bCanMove = true;

	baseValue.experienceValue = 30.0f;
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

void AMOBAWildCharacter::SetWildLevel(float level)
{
	SetLevel(level);
	for (int i = 1; i < level; i++)
	{
		WildLevelUp();
	}
}

void AMOBAWildCharacter::ResetBlueBuffValue()
{
	BuffedHero->GetMpRecovery() -= 12.0f;
	BuffedHero->AddCDReduction(-0.1f);
	BuffedHero = nullptr;
}

void AMOBAWildCharacter::ResetRedBuffValue()
{
	BuffedHero->GetHpRecovery() -= 18.0f;
	BuffedHero->GetAttackStrength() -= 30.0f;
	BuffedHero = nullptr;
}

void AMOBAWildCharacter::ResetNashBuffValue()
{
	BuffedHero->GetAttackStrength() -= 80.0f;
	BuffedHero->GetPowerStrength() -= 80.0f;
	BuffedHero = nullptr;
}

void AMOBAWildCharacter::AttackToCharacterOnce(AMOBABaseCharacter* TargetToAttack)
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

void AMOBAWildCharacter::KillValueForHero(AMOBAHeroCharacter* AHero)
{
	BuffedHero = AHero;
	if (WildType == AWildType::BlueBuff)
	{
		if (BuffedHero)
		{
			BuffedHero->GetMpRecovery() += 12.0f;
			BuffedHero->AddCDReduction(0.1f);

			FTimerHandle& MyTimeHandle = BlueBuffTimer;
			GetWorldTimerManager().ClearTimer(MyTimeHandle);
			GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAWildCharacter::ResetBlueBuffValue, 100.0f);
		}
	}
	if (WildType == AWildType::RedBuff)
	{
		if (BuffedHero)
		{
			BuffedHero->GetHpRecovery() += 18.0f;
			BuffedHero->GetAttackStrength() += 30.0f;

			FTimerHandle& MyTimeHandle = RedBuffTimer;
			GetWorldTimerManager().ClearTimer(MyTimeHandle);
			GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAWildCharacter::ResetRedBuffValue, 100.0f);
		}
	}
	if (WildType == AWildType::Nash)
	{
		if (BuffedHero)
		{
			BuffedHero->GetAttackStrength() += 80.0f;
			BuffedHero->GetPowerStrength() += 80.0f;

			FTimerHandle& MyTimeHandle = NashTimer;
			GetWorldTimerManager().ClearTimer(MyTimeHandle);
			GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAWildCharacter::ResetNashBuffValue, 120.0f);
		}
	}
}
