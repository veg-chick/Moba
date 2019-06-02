// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBATowerCharacter.h"
#include "Public/MOBAHubCrystalActor.h"
#include "Public/MOBACrystalActor.h"
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
	//函数功能：对一个character攻击一次 (Soldier,Hero)
	//不需要判断距离，已经移动到攻击范围内
	//简单a一下就好
}

bool AMOBATowerCharacter::IsEnemyHeroAttackingMyHero(AMOBABaseCharacter * EnemyHero)
{
	//传入一个敌方hero，若敌方hero攻击了我方hero，则return true
	return false;

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
