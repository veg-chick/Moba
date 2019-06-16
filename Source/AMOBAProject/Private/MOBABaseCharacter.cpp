// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBABaseCharacter.h"
#include "Public/MOBAHeroCharacter.h"
#include "Public/MOBATowerCharacter.h"
#include "Public/MOBAWildCharacter.h"
#include "Engine/Classes/GameFramework/Character.h"
#include "Engine/Classes/GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"
#include "MOBAPlayerState.h"
#include "MOBAGameMode.h"
#include "Kismet/GameplayStatics.h"


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
			//DeadHandle(DamagedActor, DamageCauser);
		}

	}

}

void AMOBABaseCharacter::ReceiveDamageFromCharacter(AMOBABaseCharacter* DamagedActor, DamageType Type, float Damage, AMOBABaseCharacter* DamageCauser)
{

	if (DamagedActor)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, AttackedFX, this->GetActorLocation());
		Attacker = DamageCauser;
		DamagedActor->GetbIsBeingAttacked() = true;

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

			float TDamage = Damage * physicalPercent;

			myHp = FMath::Clamp(myHp - TDamage, 0.0f, myMaxHp);

			auto MayBeHeroAttacking = Cast<AMOBAHeroCharacter>(DamageCauser);
			if (MayBeHeroAttacking)
			{
				if (MayBeHeroAttacking->GetLifeSteal() != 0.0f)
				{
					auto FakeHp = MayBeHeroAttacking->GetHp() + TDamage * MayBeHeroAttacking->GetLifeSteal();
					MayBeHeroAttacking->GetHp() = FMath::Clamp(FakeHp, 0.0f, MayBeHeroAttacking->GetMaxHp());
				}
			}

		}

		if (Type == DamageType::magic)
		{

			float tDamage = Damage * magicPercent;

			myHp = FMath::Clamp(myHp - tDamage, 0.0f, myMaxHp);

		}

		if (Type == DamageType::treat)
		{
			auto MayBeAHero = Cast<AMOBAHeroCharacter>(DamagedActor);
			if (MayBeAHero)
			{
				if (MayBeAHero->GetbIsInjured())
				{
					myHp = FMath::Clamp(myHp + Damage * 0.5f, 0.0f, myMaxHp);
				}
			}
			else
			{
				myHp = FMath::Clamp(myHp + Damage, 0.0f, myMaxHp);
			}


		}

		if (myHp <= 0.0f)
		{
			auto MayBeAHero = Cast<AMOBAHeroCharacter>(DamageCauser);
			if (MayBeAHero)
			{
				AMOBAPlayerState* GS = Cast<AMOBAPlayerState>(MayBeAHero->GetPlayerState());
				auto MayBeKilledHero = Cast<AMOBAHeroCharacter>(DamagedActor);
				if (GS)
				{
					if (MayBeKilledHero)
					{
						GS->AddKillNumber();
						GS->AddCombKillNumber();
					}

					else
					{
						GS->AddSoldierKillNumber();
					}
				}
				MayBeAHero->GetGold() += DamagedActor->GetGoldValue();
				MayBeAHero->AddExperienceToHero(DamagedActor->GetExperienceValue());
				auto MayBeKilledBuff = Cast<AMOBAWildCharacter>(DamagedActor);
				if (MayBeKilledBuff)
				{
					MayBeKilledBuff->KillValueForHero(MayBeAHero);
				}
			}
			DamagedActor->DeadHandle(DamagedActor, DamageCauser);
		}

		auto RecallingHero = Cast<AMOBAHeroCharacter>(DamagedActor);
		if (RecallingHero)
		{
			RecallingHero->GetbIsRecalling() = false;
		}

	}
}

void AMOBABaseCharacter::DeadHandle(AMOBABaseCharacter* DeadCharacter, AMOBABaseCharacter* DamageCauser)
{
	if (DeadCharacter)
	{
		AMOBAGameMode* GM = Cast<AMOBAGameMode>(this->GetWorld()->GetAuthGameMode());
		if (GM)
		{
			GM->OnCharacterKilled.Broadcast(DeadCharacter, DamageCauser);
		}

		DeadCharacter->GetMovementComponent()->StopMovementImmediately();

		this->GetbCanBeAttacked() = false;
		this->GetbAbleToAttack() = false;

		auto MayBeHero = Cast<AMOBAHeroCharacter>(DeadCharacter);
		if (MayBeHero)
		{
			DeadCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			MayBeHero->resetHero();
		}
		else
		{
			auto MayBeTower = Cast<AMOBATowerCharacter>(DeadCharacter);
			if (MayBeTower)
			{
				MayBeTower->TowerDeadHandle();
				return;
			}

			auto MayBeWild = Cast<AMOBAWildCharacter>(DeadCharacter);
			if (MayBeWild)
			{
				MayBeWild->WildDeadHandle();
			}

			DeadCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			DeadCharacter->SetLifeSpan(1.0f);
		}

	}

}


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


void AMOBABaseCharacter::assignBaseValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue)
{
	this->baseProperty = aBaseProperty;
	this->baseValue = aBaseValue;
}

void AMOBABaseCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMOBABaseCharacter, baseProperty);
}

