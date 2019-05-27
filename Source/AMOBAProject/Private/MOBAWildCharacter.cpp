// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBAWildCharacter.h"
#include "Engine/EngineTypes.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"

AMOBAWildCharacter::AMOBAWildCharacter()
{
	
}

void AMOBAWildCharacter::quickRecovery()
{

	auto myMaxHp = this->baseProperty.maxHp;
	auto& myHp = this->baseProperty.hp;

	myHp = FMath::Clamp(myMaxHp, 0.0f, myMaxHp);

}

void AMOBAWildCharacter::resetWild()
{
	//Move Back To Birth Location 

	quickRecovery();
}

void AMOBAWildCharacter::assignWildValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue){

	assignBaseValueForAPI(aBaseProperty, aBaseValue);

}

void AMOBAWildCharacter::BeginPlay()
{
	Super::BeginPlay();

	birthLocation = GetActorLocation();
}
