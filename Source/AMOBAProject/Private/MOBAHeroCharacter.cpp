// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBAHeroCharacter.h"

AMOBAHeroCharacter::AMOBAHeroCharacter()
{

}

void AMOBAHeroCharacter::resetHero()
{

	DetachFromControllerPendingDestroy();

	float resetTime = this->heroProperty.resetTime;

	auto myTimeHanlde = timeHandles.resetTimer;

	GetWorldTimerManager().SetTimer(myTimeHanlde, this,&AMOBAHeroCharacter::resetHeroHandle, resetTime);


}

void AMOBAHeroCharacter::resetQSkill()
{

}

void AMOBAHeroCharacter::resetWSkill()
{

}

void AMOBAHeroCharacter::resetESkill()
{

}

void AMOBAHeroCharacter::resetRSkill()
{

}

void AMOBAHeroCharacter::resetHeroHandle()
{

}

void AMOBAHeroCharacter::assignHeroValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, FHeroProperty aHeroProperty, FHeroGrowth aHeroGrowth){

	assignBaseValueForAPI(aBaseProperty, aBaseValue);
	this->heroProperty = aHeroProperty;
	this->heroGrowth = aHeroGrowth;

}
