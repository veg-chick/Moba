// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBABaseActor.h"
#include "Math/UnrealMathUtility.h"
#include "Public/MOBABaseCharacter.h"

void AMOBABaseActor::setValue() {


}

// Sets default values
AMOBABaseActor::AMOBABaseActor(){
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMOBABaseActor::AMOBABaseActor(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue) :baseProperty(aBaseProperty), baseValue(aBaseValue) {

}

bool AMOBABaseActor::canBeAttacked()
{
	return this->baseProperty.bCanBeAttacked;
}

Camp AMOBABaseActor::getCamp(){
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

void AMOBABaseActor::applyDamage(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser) {

	auto myActor = Cast<AMOBABaseActor>(damagedActor);

	//auto mayBeHero = Cast<AMOBAHeroActor>(damageCauser);

	if (myActor) {

		auto& myHp = myActor->baseProperty.hp;

		auto myMaxHp = myActor->baseProperty.maxHp;
		auto myArmor = myActor->baseProperty.armor;
		auto myMagicResist = myActor->baseProperty.magicResist;

		float physicalPercent = 1.0f - (myArmor / (100.0f + myArmor));
		float magicPercent = 1.0f - (myMagicResist / (100.0f + myMagicResist));

		if (damageType == real) {
			myHp = FMath::Clamp(myHp - damage, 0.0f, myMaxHp);
		}

		if (damageType == physical) {

			float tDamage = damage * physicalPercent;

			myHp = FMath::Clamp(myHp - tDamage, 0.0f, myMaxHp);

		}

		if (damageType == magic) {

			float tDamage = damage * magicPercent;

			myHp = FMath::Clamp(myHp - tDamage, 0.0f, myMaxHp);

		}

		if (damage == treat) {
			myHp = FMath::Clamp(myHp + damage, 0.0f, myMaxHp);
		}

		if (myHp == 0.0f) {
			deadHandle(damagedActor, damageCauser);
		}

	}

}

 void AMOBABaseActor::deadHandle(AActor* deadActor, AActor* deadCauser) {

	auto myActor = Cast<AMOBABaseActor>(deadActor);
	if (myActor) {
		this->bIsBroken = true;
	}
}

void AMOBABaseActor::attack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser) {

	if (canAttack(damagedActor, damageType, damage, damageCauser)) {

		auto otherActor = Cast<AMOBABaseActor>(damagedActor);

		if (otherActor) {

			otherActor->applyDamage(damagedActor, damageType, damage, damageCauser);

		}

		auto otherCharacter = Cast<AMOBABaseCharacter>(damagedActor);

		if (otherCharacter) {

			otherCharacter->applyDamage(damagedActor,damageType, damage, damageCauser);

		}


	}

}

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
		bool canBe = otherCharacter->canBeAttacked();

		auto causerCamp = myActor->baseProperty.baseCamp;
		auto damagedCamp = otherCharacter->getCamp();

		if (causerCamp != damagedCamp) {
			if (can && canBe) {
				return true;
			}
		}


	}

	return false;

}

