// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBAHeroAPOne.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

AMOBAHeroAPOne::AMOBAHeroAPOne()
{
	baseProperty.bHaveMp = true;
	baseProperty.bIsRemote = true;
	baseProperty.attackRange = 500.0f;

	GetQRange() = 600.0f;
	GetERange() = 300.0f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMOBAHeroAPOne::ReleaseQ(AMOBABaseCharacter* Target, float MpCost)
{
	if (this->GetbMayQ() && this->GetbCanQ())
	{
		if (Target && Target->GetCamp() != this->GetCamp() && Target->GetbCanBeAttacked())
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, QFX, Target->GetActorLocation());

			auto QDamage = 40.0f + this->GetQPoint() * 20.0f + this->GetPowerStrength() * 0.2f;
			Target->ReceiveDamageFromCharacter(Target, DamageType::magic, QDamage, this);

			this->GetMp() -= MpCost;
			ChangeReleasingSkill(1.0f);
			ResetSkills(1.0f);
		}
	}

}

void AMOBAHeroAPOne::ReleaseW(float MpCost)
{
	if (this->GetbMayE() && this->GetbCanE())
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, WFX, this->GetActorLocation());
		this->GetbCanBeAttacked() = false;
		this->GetbCanReleaseSkills() = false;
		this->GetbAbleToAttack() = false;
		this->GetbCanMove() = false;

		GetWorldTimerManager().ClearTimer(WTimerHandle);
		GetWorldTimerManager().SetTimer(WTimerHandle, this, &AMOBAHeroAPOne::WTimeHandle, 2.5f);

		this->GetMp() -= MpCost;
		ChangeReleasingSkill(2.0f);
		ResetSkills(2.0f);
	}
}

void AMOBAHeroAPOne::ReleaseE(AMOBAHeroCharacter* Target, float MpCost)
{
	if (this->GetbMayE() && this->GetbCanE())
	{
		if (Target->GetCamp() != this->GetCamp())
		{
			if (Target->GetHp() <= (Target->GetMaxHp() * 0.15f))
				Target->ReceiveDamageFromCharacter(Target, DamageType::real, Target->GetMaxHp(), this);
			else
			{
				auto EDamage = 200.0f + this->GetEPoint() * 60.0f + this->GetPowerStrength() * 0.7f;
				Target->ReceiveDamageFromCharacter(Target, DamageType::magic, EDamage, this);
			}
			UGameplayStatics::SpawnEmitterAtLocation(this, EFX, Target->GetActorLocation());
		}

		this->GetMp() -= MpCost;
		ChangeReleasingSkill(3.0f);
		ResetSkills(3.0f);
	}
}


void AMOBAHeroAPOne::WTimeHandle()
{
	this->GetbCanBeAttacked() = true;
	this->GetbCanMove() = true;
	this->GetbCanReleaseSkills() = true;
	this->GetbAbleToAttack() = true;
}
