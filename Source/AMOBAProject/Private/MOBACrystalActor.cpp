// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBACrystalActor.h"
#include "Public/MOBATowerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

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

	this->GetbCanBeAttacked() = false;
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
	CrystalPointer->GetbCanBeAttacked() = true;
}


