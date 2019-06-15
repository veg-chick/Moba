// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBAHeroTankOne.h"
#include "Components/DecalComponent.h"

AMOBAHeroTankOne::AMOBAHeroTankOne()
{
	baseProperty.bIsRemote = false;
	baseProperty.bHaveMp = false;
	baseProperty.maxMp = 0.0f;
	baseProperty.mp = 0.0f;
	baseProperty.attackRange = 125.0f;

	GetQRange() = 400.0f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
};

void AMOBAHeroTankOne::ReleaseQ(AMOBAHeroCharacter* TargetHero,float MpCost)
{
	if (this->GetbMayQ() && this->GetbCanQ() && TargetHero)
	{
		if (TargetHero&&TargetHero->GetCamp() == this->GetCamp()&&TargetHero->GetbCanBeAttacked())
		{
			auto MyTreat = 50.0f + this->GetQPoint() * 50.0f;
			TargetHero->ReceiveDamageFromCharacter(TargetHero, DamageType::treat, MyTreat, this);
		}
		else
		{
			auto MyDamage = 50.0f + this->GetQPoint() * 50.0f + this->GetAttackStrength() * 0.8f;
			TargetHero->ReceiveDamageFromCharacter(TargetHero, DamageType::physical, MyDamage, this);
		}
		this->GetbCanQ() = false;
		ChangeReleasingSkill(1.0f);
		ResetSkills(1.0f);
	}
}

void AMOBAHeroTankOne::ReleaseW(float MpCost)
{
	if (this->GetbMayW() && this->GetbCanW())
	{
		float WPoint = GetWPoint();
		float Armor = GetArmor();
		float MagicResist = GetMagicResist();
		this->SetArmor(Armor + 15.0f + WPoint * 6.0f);
		this->SetMagicResist(MagicResist + 15.0f + WPoint * 6.0f);

		auto WTime = GetWPoint() + 5.0f;
		GetWorldTimerManager().ClearTimer(WTimerHandle);
		GetWorldTimerManager().SetTimer(WTimerHandle, this, &AMOBAHeroTankOne::WTimeHandle, WTime);

		this->GetbCanW() = false;
		ChangeReleasingSkill(2.0f);
		ResetSkills(2.0f);
	}
}

void AMOBAHeroTankOne::ReleaseE(float MpCost)
{
	if (this->GetbMayE() && this->GetbCanE())
	{
		RecoveryValue = this->GetMaxHp() * (this->GetEPoint() * 0.05f + 0.35f) / 8.0f;
		this->GetHpRecovery() += RecoveryValue;

		GetWorldTimerManager().ClearTimer(ETimerHandle);
		GetWorldTimerManager().SetTimer(ETimerHandle, this, &AMOBAHeroTankOne::ETimeHandle, 8.0f);

		this->GetbCanE() = false;
		ChangeReleasingSkill(3.0f);
		ResetSkills(3.0f);
	}

}

void AMOBAHeroTankOne::WTimeHandle()
{
	float WPoint = GetWPoint();
	float Armor = GetArmor();
	float MagicResist = GetMagicResist();
	this->SetArmor(Armor - 15.0f - WPoint * 6.0f);
	this->SetMagicResist(MagicResist - 15.0f - WPoint * 6.0f);
}

void AMOBAHeroTankOne::ETimeHandle()
{
	this->GetHpRecovery() -= RecoveryValue;
}

