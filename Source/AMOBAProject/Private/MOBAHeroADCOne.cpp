// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBAHeroADCOne.h"
#include "Components/DecalComponent.h"

AMOBAHeroADCOne::AMOBAHeroADCOne()
{
	baseProperty.bHaveMp = true;
	baseProperty.bIsRemote = true;
	baseProperty.attackRange = 550.0f;
	QAttackingHero = nullptr;

	GetQRange() = 800.0f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMOBAHeroADCOne::ReleaseQ(AMOBAHeroCharacter* Target,float MpCost)
{
	if (this->GetbMayQ() && this->GetbCanQ())
	{
		GetCDofQ() = 10.5f - GetQPoint() * 0.5f;
		if (this->GetCamp() != Target->GetCamp())
		{
			this->GetMp() -= MpCost;

			auto QDamage = 50.0f + this->GetQPoint() * 20.0f + this->GetAttackStrength() * 0.8f;

			Target->ReceiveDamageFromCharacter(Target, DamageType::physical, QDamage, this);
			Target->GetbIsInjured() = true;

			QAttackingHero = Target;

			GetWorldTimerManager().ClearTimer(QTimerHandle);
			GetWorldTimerManager().SetTimer(QTimerHandle, this, &AMOBAHeroADCOne::QTimeHandle, 5.0f);

			this->GetMp() -= MpCost;
			ChangeReleasingSkill(1.0f);
			ResetSkills(1.0f);
		}
	}
}

void AMOBAHeroADCOne::ReleaseW(float MpCost)
{
	if (this->GetbMayW() && this->GetbCanW())
	{
		GetCDofW() = 18.0f - GetWPoint() * 2.0f;

		MyAttackSpeedAddValue = 0.4f + GetWPoint() * 0.2f;
		this->GetFakeAttackSpeed() += MyAttackSpeedAddValue;
		this->GetAttackSpeed() = FMath::Clamp(this->GetFakeAttackSpeed(), 0.0f, this->GetMaxAttackSpeed());

		GetWorldTimerManager().ClearTimer(WTimerHandle);
		GetWorldTimerManager().SetTimer(WTimerHandle, this, &AMOBAHeroADCOne::WTimeHandle, 4.0f);

		this->GetMp() -= MpCost;
		ChangeReleasingSkill(2.0f);
		ResetSkills(2.0f);
	}
}

void AMOBAHeroADCOne::ReleaseE(float MpCost)
{
	if (this->GetbMayE() && this->GetbCanE())
	{
		GetCDofE() = 90.0f - (this->GetEPoint() - 1.0f) * 15.0f;

		this->GetMp() -= MpCost;

		MyLifeStealAddValue= this->GetEPoint() * 0.05f + 0.05f;
		this->GetLifeSteal() += MyLifeStealAddValue;

		MyAttackStrengthAddValue = this->GetEPoint() * 20.0f + 60.0f;
		this->GetAttackStrength() += MyAttackStrengthAddValue;

		this->GetAttackRange() = 1000.0f;

		GetWorldTimerManager().ClearTimer(ETimerHandle);
		GetWorldTimerManager().SetTimer(ETimerHandle, this, &AMOBAHeroADCOne::ETimeHandle, 6.0f);

		this->GetMp() -= MpCost;
		ChangeReleasingSkill(3.0f);
		ResetSkills(3.0f);
	}
}

void AMOBAHeroADCOne::WTimeHandle()
{
	this->GetFakeAttackSpeed() -= MyAttackSpeedAddValue;
}

void AMOBAHeroADCOne::QTimeHandle()
{
	if (QAttackingHero)
	{
		QAttackingHero->GetbIsInjured() = false;
		QAttackingHero = nullptr;
	}
}

void AMOBAHeroADCOne::ETimeHandle()
{
	this->GetLifeSteal() -= MyLifeStealAddValue;
	this->GetAttackStrength() -= MyAttackStrengthAddValue;
	this->GetAttackRange() = 550.0f;
}

void AMOBAHeroADCOne::Tick(float DeltaSeconds)
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

	GetQCost() = GetQPoint() * 10.0f + 50.0f;
	GetWCost() = GetWPoint() * 20.0f + 70.0f;
	GetECost() = GetWPoint() * 10.0f + 90.0f;

}
