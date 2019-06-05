// Fill out your copyright notice in the Description page of Project Settings.

#include "MOBABaseActor.h"
#include "Math/UnrealMathUtility.h"
#include "Public/MOBAHubCrystalActor.h"
#include "Public/MOBAHeroCharacter.h"
#include "Public/MOBASoldierCharacter.h"
#include "Public/MOBACrystalActor.h"
#include "Public/MOBABaseCharacter.h"

// Sets default values
AMOBABaseActor::AMOBABaseActor(){
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMOBABaseActor::AMOBABaseActor(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue) :baseProperty(aBaseProperty), baseValue(aBaseValue) {

}

bool& AMOBABaseActor::GetbCanBeAttacked()
{
	return this->baseProperty.bCanBeAttacked;
}

Camp& AMOBABaseActor::GetCamp(){
	return this->baseProperty.baseCamp;
}

void AMOBABaseActor::assignBaseValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue){

	this->baseProperty = aBaseProperty;
	this->baseValue = aBaseValue;

}

// Called when the game starts or when spawned
void AMOBABaseActor::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void AMOBABaseActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}


void AMOBABaseActor::ReceiveDamageFromCharacter(AMOBABaseActor* DamagedActor, DamageType Type, float Damage, AMOBABaseCharacter* DamageCauser)
{
	if (DamagedActor)
	{
		auto& myHp = DamagedActor->baseProperty.hp;

		auto myMaxHp = DamagedActor->baseProperty.maxHp;
		auto myArmor = DamagedActor->baseProperty.armor;
		auto myMagicResist = DamagedActor->baseProperty.magicResist;

		float physicalPercent = 1.0f - (myArmor / (100.0f + myArmor));
		float magicPercent = 1.0f - (myMagicResist / (100.0f + myMagicResist));

		if (Type == DamageType::real) 
		{
			myHp = FMath::Clamp(myHp - Damage, 0.0f, myMaxHp);
		}

		if (Type == DamageType::physical) 
		{

			float tDamage = Damage * physicalPercent;

			myHp = FMath::Clamp(myHp - tDamage, 0.0f, myMaxHp);

		}

		if (Type == DamageType::magic) 
		{

			float tDamage = Damage * magicPercent;

			myHp = FMath::Clamp(myHp - tDamage, 0.0f, myMaxHp);

		}

		if (Type == DamageType::treat)
		{
			myHp = FMath::Clamp(myHp + Damage, 0.0f, myMaxHp);
		}

		if (myHp == 0.0f)
		{
			auto MayBeAHero = Cast<AMOBAHeroCharacter>(DamageCauser);
			if (MayBeAHero)
			{
				auto MayBeSoldier = Cast<AMOBASoldierCharacter>(DamagedActor);
				if (DamagedActor)
				{
					MayBeAHero->GetSoldierKillNumber() += 1.0f;
				}
				MayBeAHero->GetGold() += DamagedActor->GetGoldValue();
				MayBeAHero->AddExperienceToHero(DamagedActor->GetExperienceValue());
			}
			DeadHandle(DamagedActor);
		}
	}
}

void AMOBABaseActor::DeadHandle(AMOBABaseActor* DeadActor) {
	if (DeadActor) 
	{
		this->GetbIsBroken()= true;
		this->GetbCanBeAttacked() = false;

		auto MayBeCrystal = Cast<AMOBACrystalActor>(DeadActor);
		if (MayBeCrystal)
		{
			MayBeCrystal->CrystalDeadHandle();
			return;
		}


		auto MayBeHub = Cast<AMOBAHubCrystalActor>(DeadActor);
		if (MayBeHub)
		{
			auto Loser = MayBeHub->GetCamp();
			if (Loser == Camp::blue)
			{
				MayBeHub->EndTheGame(Camp::red);
				return;
			}
			else
			{
				MayBeHub->EndTheGame(Camp::blue);
				return;
			}
		}

	}
}

/*
void AMOBABaseActor::attack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser) 
{

		auto otherActor = Cast<AMOBABaseActor>(damagedActor);

		if (otherActor) 
		{

			otherActor->applyDamage(damagedActor, damageType, damage, damageCauser);

		}

		auto otherCharacter = Cast<AMOBABaseCharacter>(damagedActor);

		if (otherCharacter) 
		{

			otherCharacter->applyDamage(damagedActor,damageType, damage, damageCauser);

		}


}
*/

bool AMOBABaseActor::canAttack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser) {

	auto myActor = Cast<AMOBABaseActor>(damageCauser);

	auto otherActor = Cast<AMOBABaseActor>(damagedActor);
	if (otherActor) {
		bool can = myActor->baseProperty.bAbleToAttack;
		bool canBe = otherActor->baseProperty.bCanBeAttacked;

		auto causerCamp = myActor->baseProperty.baseCamp;
		auto damagedCamp = otherActor->baseProperty.baseCamp;

		if (causerCamp != damagedCamp) {
			if (can && canBe) {
				return true;
			}
		}
	}

	auto otherCharacter = Cast<AMOBABaseCharacter>(damagedActor);
	if (otherCharacter) {
		bool can = myActor->baseProperty.bAbleToAttack;
		bool canBe = otherCharacter->GetbCanBeAttacked();

		auto causerCamp = myActor->baseProperty.baseCamp;
		auto damagedCamp = otherCharacter->GetCamp();

		if (causerCamp != damagedCamp) {
			if (can && canBe) {
				return true;
			}
		}


	}

	return false;

}

