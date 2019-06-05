// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBATowerCharacter.h"
#include "Public/MOBAHubCrystalActor.h"
#include "Public/MOBACrystalActor.h"
#include "Public/MOBAHeroCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"



AMOBATowerCharacter::AMOBATowerCharacter()
{
	RootComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComp"));
	RootComponent = RootComp;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	BaseMeshComp->SetupAttachment(RootComp);

	StructMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StructMeshComp"));
	StructMeshComp->SetupAttachment(RootComp);

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->SetupAttachment(RootComp);

	ClickComp = CreateDefaultSubobject<USphereComponent>(TEXT("ClickComp"));
	ClickComp->SetupAttachment(RootComp);

	this->SetValue();

}

TowerRoad& AMOBATowerCharacter::GetRoad()
{
	return road;
}

TowerType& AMOBATowerCharacter::GetTowerType()
{
	return towerType;
}

void AMOBATowerCharacter::assignTowerValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, TowerRoad aRoad, TowerType aTowerType)
{
	assignBaseValueForAPI(aBaseProperty, aBaseValue);
	this->road = aRoad;
	this->towerType = aTowerType;
}


void AMOBATowerCharacter::AttackToCharacterOnce(AMOBABaseCharacter * TargetToAttack)
{

	if (this->GetbAbleToAttack())
	{
		this->GetbIsAttacking() = true;
		auto MyAttackStrength = this->GetAttackStrength();
		TargetToAttack->ReceiveDamageFromCharacter(TargetToAttack, DamageType::physical, MyAttackStrength, this);
		this->GetbAbleToAttack() = false;
		auto MyTimeHandle = this->AttackTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		auto AttackCDTime = 1.0f / GetAttackSpeed();
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBATowerCharacter::ResetTimer, AttackCDTime);
		this->GetbIsAttacking() = false;
	}
}

bool AMOBATowerCharacter::IsEnemyHeroAttackingMyHero(AMOBAHeroCharacter* EnemyHero)
{
	if (EnemyHero->GetbIsAttackingHero())
		return true;
	return false;
}


void AMOBATowerCharacter::TowerDeadHandle()
{
	
	if (GetTowerType() == TowerType::hub)
	{
		TowerPointerToHub->GetbCanBeAttacked() = true;
	}
	else if (GetTowerType() == TowerType::highland)
	{
		TowerPointerToCrystal->GetbCanBeAttacked() = true;
	}
	else
	{
		TowerPointerToTower->GetbCanBeAttacked() = true;
	}
}

void AMOBATowerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GetTowerType() == TowerType::outter)
	{
		GetbCanBeAttacked() = true;
	}
	else
	{
		GetbCanBeAttacked() = false;
	}


}

void AMOBATowerCharacter::ResetTimer()
{
	this->GetbAbleToAttack() = true;
}

void AMOBATowerCharacter::SetValue()
{
	baseProperty.hp = 1800.0f;
	baseProperty.maxHp = 1800.0f;
	baseProperty.armor = 100.0f;
	baseProperty.magicResist = 100.0f;
	baseProperty.attackSpeed = 1.0f;
	baseProperty.attackStrength = 200.0f;
	baseProperty.attackRange = 800.0f;
	baseProperty.bIsRemote = true;
	baseProperty.bHaveMp = false;
	baseProperty.bCanBeAttacked = false;
	baseProperty.bAbleToAttack = true;

	baseValue.experienceValue = 2.5f;
	baseValue.goldValue = 200.0f;

}
