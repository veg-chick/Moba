// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBABaseCharacter.h"

// Sets default values
AMOBABaseCharacter::AMOBABaseCharacter(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMOBABaseCharacter::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void AMOBABaseCharacter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMOBABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMOBABaseCharacter::applyDamage(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser){

	auto myActor = Cast<AMOBABaseCharacter>(damagedActor);

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

void AMOBABaseCharacter::deadHandle(AActor* deadActor, AActor* deadCauser){

}

void AMOBABaseCharacter::attack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser){

	if (canAttack(damagedActor, damageType, damage, damageCauser)) {

		auto otherActor = Cast<AMOBABaseActor>(damagedActor);

		if (otherActor) {

			otherActor->applyDamage(damagedActor, damageType, damage, damageCauser);

		}

		auto otherCharacter = Cast<AMOBABaseCharacter>(damagedActor);

		if (otherCharacter) {

			otherCharacter->applyDamage(damagedActor, damageType, damage, damageCauser);

		}


	}

}

bool AMOBABaseCharacter::canAttack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser){
	auto myActor = Cast<AMOBABaseCharacter>(damageCauser);

	auto otherActor = Cast<AMOBABaseActor>(damagedActor);
	if (otherActor) {
		bool can = myActor->baseProperty.bAbleToAttack;
		bool canBe = otherActor->canBeAttacked();

		auto causerCamp = myActor->baseProperty.baseCamp;
		auto damagedCamp = otherActor->getCamp();

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

void AMOBABaseCharacter::setValue(){

}

bool AMOBABaseCharacter::canBeAttacked(){

	return this->baseProperty.bCanBeAttacked;

}

Camp AMOBABaseCharacter::getCamp(){

	return this->baseProperty.baseCamp;

}

void AMOBABaseCharacter::assignBaseValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue){

	this->baseProperty = aBaseProperty;
	this->baseValue = aBaseValue;

}

