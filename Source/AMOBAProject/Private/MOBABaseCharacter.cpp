// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBABaseCharacter.h"
#include "Public/MOBAHeroCharacter.h"
#include "Engine/Classes/GameFramework/Character.h"
#include "Engine/Classes/GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMOBABaseCharacter::AMOBABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMOBABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMOBABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMOBABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMOBABaseCharacter::ApplyDamage(AMOBABaseCharacter* DamagedActor, DamageType Type, float Damage, AActor* DamageCauser)
{

	if (DamagedActor) 
	{

		auto& myHp = DamagedActor->baseProperty.hp;

		auto myMaxHp = DamagedActor->baseProperty.maxHp;
		auto myArmor = DamagedActor->baseProperty.armor;
		auto myMagicResist = DamagedActor->baseProperty.magicResist;

		float physicalPercent = 1.0f - (myArmor / (100.0f + myArmor));
		float magicPercent = 1.0f - (myMagicResist / (100.0f + myMagicResist));

		if (Type == DamageType::real) {
			UE_LOG(LogTemp, Warning, TEXT("Real Damage Applyed!"));
			myHp = FMath::Clamp(myHp - Damage, 0.0f, myMaxHp);
		}

		if (Type == DamageType::physical) {

			float tDamage = Damage * physicalPercent;

			myHp = FMath::Clamp(myHp - tDamage, 0.0f, myMaxHp);

		}

		if (Type == DamageType::magic) {

			float tDamage = Damage * magicPercent;

			myHp = FMath::Clamp(myHp - tDamage, 0.0f, myMaxHp);

		}

		if (Type == DamageType::treat) {
			myHp = FMath::Clamp(myHp + Damage, 0.0f, myMaxHp);
		}

		if (myHp <= 0.0f) {
			DeadHandle(DamagedActor);
		}

	}

}

void AMOBABaseCharacter::ReceiveDamageFromCharacter(AMOBABaseCharacter* DamagedActor, DamageType Type, float Damage, AMOBABaseCharacter* DamageCauser)
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
			UE_LOG(LogTemp, Warning, TEXT("Real Damage Applyed!"));
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

		if (myHp <= 0.0f) 
		{
			auto MayBeAHero = Cast<AMOBAHeroCharacter>(DamageCauser);
			if (MayBeAHero)
			{
				MayBeAHero->GetGold() += DamagedActor->GetGoldValue();
				MayBeAHero->GetExperience() += DamagedActor->GetExperienceValue();
			}
			DamagedActor->DeadHandle(DamagedActor);
		}

		auto RecallingHero = Cast<AMOBAHeroCharacter>(DamagedActor);
		if (RecallingHero)
		{
			RecallingHero->GetbRecallSucceed() = false;
		}

	}
}

void AMOBABaseCharacter::DeadHandle(AMOBABaseCharacter* DeadCharacter)
{
	if (DeadCharacter) 
	{
		DeadCharacter->GetMovementComponent()->StopMovementImmediately();

		DeadCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		this->GetbCanBeAttacked() = false;
		this->GetbAbleToAttack() = false;

		auto mayBeHero = Cast<AMOBAHeroCharacter>(DeadCharacter);

		if (mayBeHero) 
		{
			mayBeHero->resetHero();
		}else 
		{
			DeadCharacter->SetLifeSpan(10.0f);
		}

	}

}

/*
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

}*/

bool AMOBABaseCharacter::canAttack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser)
{
	auto myActor = Cast<AMOBABaseCharacter>(damageCauser);

	auto otherActor = Cast<AMOBABaseActor>(damagedActor);
	if (otherActor) {
		bool can = myActor->baseProperty.bAbleToAttack;
		bool canBe = otherActor->GetbCanBeAttacked();

		auto causerCamp = myActor->baseProperty.baseCamp;
		auto damagedCamp = otherActor->GetCamp();

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

void AMOBABaseCharacter::setValue()
{

}

void AMOBABaseCharacter::assignBaseValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue)
{
	this->baseProperty = aBaseProperty;
	this->baseValue = aBaseValue;
}

