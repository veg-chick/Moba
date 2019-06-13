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

void AMOBAHeroADOne::Tick(float DeltaSeconds)
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

	
	GetQCost() = GetQPoint() * 10.0f + 30.0f;
	GetWCost() = GetWPoint() * 10.0f + 70.0f;
	GetECost() = GetEPoint() * 20.0f + 150.0f;
	
}

void AMOBAHeroADOne::ReleaseQ(AMOBAHeroCharacter* Target, float MpCost)
{
	if (this->GetbMayQ() && this->GetbCanQ())
	{
		GetCDofQ() = 15.5f - GetQPoint() * 0.5f;
		if (Target&&Target->GetCamp()!=this->GetCamp())
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
		GetCDofW() = 18.5f - GetWPoint() * 1.5f;
		
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
		GetCDofE() = 200.0f - this->GetEPoint() * 20.0f;

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