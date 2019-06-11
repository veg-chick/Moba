// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBAHeroTankOne.h"
#include "Components/DecalComponent.h"

AMOBAHeroTankOne::AMOBAHeroTankOne()
{
	baseProperty.bIsRemote = false;
	baseProperty.bHaveMp = false;
	baseProperty.attackRange = 125.0f;

	GetQRange() = 400.0f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
};

void AMOBAHeroTankOne::ReleaseQ(AMOBAHeroCharacter* TargetHero,float MpCost)
{
	this->GetCDofQ() = 12.0f - this->GetQPoint();
	if (this->GetbMayQ() && this->GetbCanQ() && TargetHero)
	{
		if (TargetHero->GetCamp() == this->GetCamp())
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
	this->GetCDofW() = 21.0f - this->GetWPoint();
	if (this->GetbMayW() && this->GetbCanW())
	{
		this->GetArmor() += 15.0f + GetWPoint() * 6.0f;
		this->GetMagicResist() += 15.0f + GetWPoint() * 6.0f;

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
	this->GetCDofE() = 130.0f - this->GetEPoint() * 10.0f;
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
	this->GetArmor() -= 15.0f + GetWPoint() * 6.0f;
	this->GetMagicResist() -= 15.0f + GetWPoint() * 6.0f;
}

void AMOBAHeroTankOne::ETimeHandle()
{
	this->GetHpRecovery() -= RecoveryValue;
}

void AMOBAHeroTankOne::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (APlayerController * PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}

	if (GetbCanReleaseSkills())
	{
		if ((GetQPoint() != 0.0f) && (GetMp() >= GetQCost()))
			GetbMayQ() = true;
		else GetbMayQ() = false;
		if ((GetWPoint() != 0.0f) && (GetMp() >= GetWCost()))
			GetbMayW() = true;
		else GetbMayW() = false;
		if ((GetEPoint() != 0.0f) && (GetMp() >= GetECost()))
			GetbMayE() = true;
		else GetbMayE() = false;
	}

}
