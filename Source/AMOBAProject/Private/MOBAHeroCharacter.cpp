// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBAHeroCharacter.h"

AMOBAHeroCharacter::AMOBAHeroCharacter()
{

}

void AMOBAHeroCharacter::resetHero()
{

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

void AMOBAHeroCharacter::assignHeroValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, FHeroProperty aHeroProperty, FHeroGrowth aHeroGrowth){

	assignBaseValueForAPI(aBaseProperty, aBaseValue);
	this->heroProperty = aHeroProperty;
	this->heroGrowth = aHeroGrowth;

}
