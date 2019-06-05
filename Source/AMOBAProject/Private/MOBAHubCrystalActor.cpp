// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBAHubCrystalActor.h"
#include "Components/StaticMeshComponent.h"
#include "Public/MOBAGameMode.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

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

	this->SetValue();

}

AMOBAHubCrystalActor::AMOBAHubCrystalActor(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue) :AMOBABaseActor(aBaseProperty, aBaseValue) {

}

void AMOBAHubCrystalActor::SetValue()
{
	baseProperty.maxHp = 5000.0f;
	baseProperty.hp = 5000.0f;
	baseProperty.hpRecovery = 20.0f;
	baseProperty.bHaveMp = false;
	baseProperty.bCanBeAttacked = false;
	baseProperty.armor = 50.0f;
	baseProperty.magicResist = 50.0f;
}

void AMOBAHubCrystalActor::assignHubCrystalValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue){

	assignBaseValueForAPI(aBaseProperty, aBaseValue);

}

void AMOBAHubCrystalActor::EndTheGame(Camp winner)
{	
	AMOBAGameMode* GM = Cast<AMOBAGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->GameOver(winner);
	}
	
}
