// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBAHeroAssistOne.h"
#include "Components/DecalComponent.h"

AMOBAHeroAssistOne::AMOBAHeroAssistOne()
{
	baseProperty.bIsRemote = true;
	baseProperty.bHaveMp = true;
	baseProperty.attackRange = 500.0f;

	GetQRange() = 800.0f;
	GetWRange() = 600.0f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMOBAHeroAssistOne::ReleaseQ(AMOBAHeroCharacter* Target, float MpCost)
{
	if (this->GetbMayQ() && this->GetbCanQ())
	{
		if (Target && Target != this && Target->GetCamp() == this->GetCamp())
		{

			auto TreatValue = 50.0f + this->GetQPoint() * 50.0f + this->GetPowerStrength() * 0.3f;
			if (this->GetHp() > TreatValue)
			{
				Target->ReceiveDamageFromCharacter(Target, DamageType::treat, TreatValue, this);
				this->ReceiveDamageFromCharacter(this, DamageType::real, TreatValue * 0.8f, this);

				this->GetMp() -= MpCost;
				ChangeReleasingSkill(1.0f);
				ResetSkills(1.0f);
			}
		}
	}
}

void AMOBAHeroAssistOne::ReleaseW(AMOBAHeroCharacter* Target, float MpCost)
{
	if (this->GetbMayW() && this->GetbCanW())
	{
		if (Target && this->GetCamp() != Target->GetCamp() && Target->GetbCanBeAttacked())
		{
			Target->ExceptionState(State::Silence, 2.5f);

			this->GetMp() -= MpCost;
			ChangeReleasingSkill(2.0f);
			ResetSkills(2.0f);
		}
	}
}

void AMOBAHeroAssistOne::ReleaseE(AMOBAHeroCharacter* Target, float MpCost)
{
	if (this->GetbMayE() && this->GetbCanE())
	{
		if (Target && Target != this && this->GetCamp() == Target->GetCamp())
		{
			auto MpRecoveryValue = 30.0f + this->GetEPoint() * 50.0f + this->GetPowerStrength() * 0.5f;
			Target->GetMp() = FMath::Clamp(Target->GetMp() + MpRecoveryValue, 0.0f, Target->GetMaxMp());

			this->GetMp() -= MpCost;
			ChangeReleasingSkill(3.0f);
			ResetSkills(3.0f);
		}
	}
}
