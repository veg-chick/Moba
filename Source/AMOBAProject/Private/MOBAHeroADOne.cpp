// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBAHeroADOne.h"
#include "Components/DecalComponent.h"

AMOBAHeroADOne::AMOBAHeroADOne()
{
	baseProperty.bHaveMp = true;
	baseProperty.bIsRemote = false;
	baseProperty.attackRange = 175.0f;

	GetQRange() = 300.0f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMOBAHeroADOne::ReleaseQ(AMOBAHeroCharacter* Target, float MpCost)
{
	if (this->GetbMayQ() && this->GetbCanQ())
	{
		if (Target && Target->GetCamp() != this->GetCamp() && Target->GetbCanBeAttacked())
		{
			auto MyStunTime = 2.5f + this->GetQPoint() * 0.5f;
			Target->ExceptionState(State::Stun, MyStunTime);

			this->GetMp() -= MpCost;
			ChangeReleasingSkill(1.0f);
			ResetSkills(1.0f);
		}
	}
}

void AMOBAHeroADOne::ReleaseW(float MpCost)
{
	if (this->GetbMayQ() && this->GetbCanQ())
	{
		MyAttackStrengthAddValue = (this->GetMaxHp() - this->GetHp()) * (this->GetWPoint() * 0.05f + 0.1f);
		this->GetAttackStrength() += MyAttackStrengthAddValue;

		GetWorldTimerManager().ClearTimer(WTimerHandle);
		GetWorldTimerManager().SetTimer(WTimerHandle, this, &AMOBAHeroADOne::WTimeHandle, 4.0f);

		this->GetMp() -= MpCost;
		ChangeReleasingSkill(2.0f);
		ResetSkills(2.0f);
	}
}

void AMOBAHeroADOne::ReleaseE(float MpCost)
{
	if (this->GetbMayE() && this->GetbCanE())
	{
		this->GetArmor() += 1000.0f;
		this->GetMagicResist() += 1000.0f;

		GetWorldTimerManager().ClearTimer(ETimerHandle);
		GetWorldTimerManager().SetTimer(ETimerHandle, this, &AMOBAHeroADOne::ETimeHandle, 3.0f);


		this->GetMp() -= MpCost;
		ChangeReleasingSkill(3.0f);
		ResetSkills(3.0f);

	}
}

void AMOBAHeroADOne::WTimeHandle()
{
	this->GetAttackStrength() -= MyAttackStrengthAddValue;
}

void AMOBAHeroADOne::ETimeHandle()
{
	this->GetArmor() -= 1000.0f;
	this->GetMagicResist() -= 1000.0f;
}