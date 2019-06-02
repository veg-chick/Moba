// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBAWildCharacter.h"
#include "Engine/EngineTypes.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"

AMOBAWildCharacter::AMOBAWildCharacter()
{
	
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

void AMOBAWildCharacter::AttackToCharacterOnce(AMOBABaseCharacter * TargetToAttack)
{
	if (this->GetbAbleToAttack())
	{
		auto MyAttackStrength = this->GetAttackStrength();
		TargetToAttack->ReceiveDamageFromCharacter(TargetToAttack, DamageType::physical, MyAttackStrength, this);
		this->GetbAbleToAttack() = false;
		auto MyTimeHandle = this->AttackTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		auto AttackCDTime = 1.0f / GetAttackSpeed();
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAWildCharacter::ResetTimer, AttackCDTime);
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
