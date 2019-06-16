// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBAHeroAssassinOne.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

AMOBAHeroAssassinOne::AMOBAHeroAssassinOne()
{
	baseProperty.bHaveMp = true;
	baseProperty.bIsRemote = false;
	baseProperty.attackRange = 125.0f;

	GetQRange() = 150.0f;
	GetERange() = 500.0f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMOBAHeroAssassinOne::ReleaseQ(AMOBAHeroCharacter* Target, float MpCost)
{
	if (this->GetbMayQ() && this->GetbCanQ())
	{
		if (Target && Target->GetCamp() != this->GetCamp() && Target->GetbCanBeAttacked())
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, QFX, Target->GetActorLocation());
			auto QDamage = this->GetAttackStrength() * 0.8f + 30.0f + this->GetQPoint() * 30.0f;
			Target->ReceiveDamageFromCharacter(Target, DamageType::physical, QDamage, this);

			this->GetMp() -= MpCost;
			ChangeReleasingSkill(1.0f);
			ResetSkills(1.0f);
		}
	}
}

void AMOBAHeroAssassinOne::ReleaseW(float MpCost)
{
	if (this->GetbMayW() && this->GetbCanW())
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, WFX, this->GetActorLocation());
		MyStrikeRateAddValue = this->GetWPoint() * 0.05f;
		this->GetStrikeRate() += MyStrikeRateAddValue;

		GetWorldTimerManager().ClearTimer(WTimerHandle);
		GetWorldTimerManager().SetTimer(WTimerHandle, this, &AMOBAHeroAssassinOne::WTimeHandle, 6.0f);

		this->GetMp() -= MpCost;
		ChangeReleasingSkill(2.0f);
		ResetSkills(2.0f);
	}
}

void AMOBAHeroAssassinOne::ReleaseE(AMOBAHeroCharacter* Target, float MpCost)
{
	if (this->GetbMayE() && this->GetbCanE())
	{
		if (Target && Target->GetCamp() != this->GetCamp() && Target->GetbCanBeAttacked())
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, EFX, Target->GetActorLocation());
			FVector TargetLocation = Target->GetActorLocation();
			TargetLocation.X += 10.0f;
			TargetLocation.Y += 10.0f;
			this->SetActorLocation(TargetLocation, true);

			MyStrikeDamageAddValue = this->GetEPoint() * 0.1f;
			this->GetStrikeDamage() += MyStrikeDamageAddValue;
			GetWorldTimerManager().ClearTimer(ETimerHandle);
			GetWorldTimerManager().SetTimer(WTimerHandle, this, &AMOBAHeroAssassinOne::ETimeHandle, 3.0f);

			this->GetMp() -= MpCost;
			ChangeReleasingSkill(3.0f);
			ResetSkills(3.0f);
		}
	}
}

void AMOBAHeroAssassinOne::WTimeHandle()
{
	this->GetStrikeRate() -= MyStrikeRateAddValue;
}

void AMOBAHeroAssassinOne::ETimeHandle()
{
	this->GetStrikeDamage() -= MyStrikeDamageAddValue;
}


