// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBATowerCharacter.h"
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

TowerRoad& AMOBATowerCharacter::getRoad()
{
	return road;
}

TowerType& AMOBATowerCharacter::getTowerType()
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
	//�������ܣ���һ��character����һ�� (Soldier,Hero)
	//����Ҫ�жϾ��룬�Ѿ��ƶ���������Χ��
	//��aһ�¾ͺ�
}

bool AMOBATowerCharacter::IsEnemyHeroAttackingMyHero(AMOBABaseCharacter * EnemyHero)
{
	//����һ���з�hero�����з�hero�������ҷ�hero����return true
	return false;
}
