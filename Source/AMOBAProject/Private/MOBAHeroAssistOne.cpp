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

void AMOBAHeroAssistOne::Tick(float DeltaSeconds)
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
		{
			if(50.0f + this->GetQPoint() * 50.0f)
				GetbMayW() = true;
		}
		else GetbMayW() = false;
		if ((GetEPoint() != 0.0f) && (GetMp() >= GetECost()))
			GetbMayE() = true;
		else GetbMayE() = false;
	}

	
	GetQCost() = GetQPoint() * 30.0f + 50.0f;
	GetWCost() = 110.0f - GetWPoint() * 10.0f;
	GetECost() = GetWPoint() * 10.0f + 70.0f;
	
}

void AMOBAHeroAssistOne::ReleaseQ(AMOBAHeroCharacter* Target, float MpCost)
{
	if (this->GetbMayQ() && this->GetbCanQ())
	{
		GetCDofQ() = 21.5f - this->GetQPoint() * 0.5f;
		if (Target != this && Target->GetCamp() == this->GetCamp())
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
		GetCDofW() = 18.5f - this->GetWPoint() * 1.5f;
		if (this->GetCamp() != Target->GetCamp())
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
		GetCDofE() = 21.5f - this->GetEPoint() * 1.5f;
		if (Target != this && this->GetCamp() == Target->GetCamp())
		{
			auto MpRecoveryValue = 30.0f + this->GetEPoint() * 50.0f + this->GetPowerStrength() * 0.5f;
			Target->GetMp() = FMath::Clamp(Target->GetMp() + MpRecoveryValue, 0.0f, Target->GetMaxMp());

			this->GetMp() -= MpCost;
			ChangeReleasingSkill(3.0f);
			ResetSkills(3.0f);
		}
	}
}
