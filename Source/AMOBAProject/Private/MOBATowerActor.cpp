// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBATowerActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

AMOBATowerActor::AMOBATowerActor(BaseProperty aBaseProperty, BaseValue aBaseValue, TowerRoad aRoad, TowerType aTowerType) :AMOBABaseActor(aBaseProperty, aBaseValue), road(aRoad), towerType(aTowerType) {

}

AMOBATowerActor::AMOBATowerActor() {
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

TowerRoad AMOBATowerActor::getRoad() {
	return road;
}

TowerType AMOBATowerActor::getTowerType() {
	return towerType;
}
