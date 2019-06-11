// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBAHeroAPOne.h"
#include "Components/DecalComponent.h"

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
		GetCDofQ() = 3.5f;

		if (Target->GetCamp() != this->GetCamp())
		{

			auto QDamage = 40.0f + this->GetQPoint() * 20.0f + this->GetPowerStrength() * 0.2f;
			Target->ReceiveDamageFromCharacter(Target, DamageType::magic, QDamage, this);


			ChangeReleasingSkill(1.0f);
			ResetSkills(1.0f);
		}
	}

}

void AMOBAHeroAPOne::ReleaseW(float MpCost)
{
	if (this->GetbMayE() && this->GetbCanE())
	{
		GetCDofW() = 100.0f - GetWPoint() * 5.0f;

		this->GetbCanBeAttacked() = false;
		this->GetbCanReleaseSkills() = false;
		this->GetbAbleToAttack() = false;
		this->GetbCanMove() = false;

		GetWorldTimerManager().ClearTimer(WTimerHandle);
		GetWorldTimerManager().SetTimer(WTimerHandle, this, &AMOBAHeroAPOne::WTimeHandle, 2.5f);

		ChangeReleasingSkill(2.0f);
		ResetSkills(2.0f);
	}
}

void AMOBAHeroAPOne::ReleaseE(AMOBAHeroCharacter* Target, float MpCost)
{
	if (this->GetbMayE() && this->GetbCanE())
	{
		GetCDofE() = 130.0f - GetEPoint() * 10.0f;
		if (Target->GetCamp() != this->GetCamp())
		{
			if (Target->GetHp() <= (Target->GetMaxHp() * 0.15f))
				Target->ReceiveDamageFromCharacter(Target, DamageType::real, Target->GetMaxHp(), this);
			else
			{
				auto EDamage = 200.0f + this->GetEPoint() * 60.0f + this->GetPowerStrength() * 0.7f;
				Target->ReceiveDamageFromCharacter(Target, DamageType::magic, EDamage, this);
			}
		}

		ChangeReleasingSkill(3.0f);
		ResetSkills(3.0f);
	}
}

void AMOBAHeroAPOne::Tick(float DeltaSeconds)
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

	GetQCost() = GetQPoint() * 5.0f + 10.0f;
	GetWCost() = GetWPoint() * 10.0f + 70.0f;
	GetECost() = GetWPoint() * 10.0f + 120.0f;

}

void AMOBAHeroAPOne::WTimeHandle()
{
	this->GetbCanBeAttacked() = true;
	this->GetbCanMove() = true;
	this->GetbCanReleaseSkills() = true;
	this->GetbAbleToAttack() = true;
}
