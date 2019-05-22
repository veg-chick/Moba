// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBAHubCrystalActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

AMOBAHubCrystalActor::AMOBAHubCrystalActor() {
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

AMOBAHubCrystalActor::AMOBAHubCrystalActor(BaseProperty aBaseProperty, BaseValue aBaseValue) :AMOBABaseActor(aBaseProperty, aBaseValue) {

}
