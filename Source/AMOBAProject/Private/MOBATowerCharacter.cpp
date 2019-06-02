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
