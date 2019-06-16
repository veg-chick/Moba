// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBACrystalActor.h"
#include "Public/MOBATowerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AMOBACrystalActor::AMOBACrystalActor(FBaseActorProperty ABaseProperty, FBaseActorValue aBaseValue, CrystalRoad aRoad) :AMOBABaseActor(ABaseProperty, aBaseValue), road(aRoad) {
	
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

AMOBACrystalActor::AMOBACrystalActor() {

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

CrystalRoad& AMOBACrystalActor::getRoad() {
	return road;
}

void AMOBACrystalActor::assignCrystalValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, CrystalRoad aRoad){

	assignBaseValueForAPI(aBaseProperty, aBaseValue);

	this->road = aRoad;

}

void AMOBACrystalActor::CrystalDeadHandle()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DestroyFX, GetActorLocation());

	SpawnRuin();
	Destroy();

	CrystalPointer->GetbCanBeAttacked() = true;
}

void AMOBACrystalActor::SetValue()
{
	baseProperty.hp = 2000.0f;
	baseProperty.maxHp = 2000.0f;
	baseProperty.armor = 50.0f;
	baseProperty.magicResist = 50.0f;
	baseProperty.hpRecovery = 5.0f;
	baseProperty.sightRange = 800.0f;

	baseValue.experienceValue = 10.0f;
	baseValue.goldValue = 50.0f;

	baseProperty.bCanBeAttacked = false;
	baseProperty.bHaveMp = false;
}


