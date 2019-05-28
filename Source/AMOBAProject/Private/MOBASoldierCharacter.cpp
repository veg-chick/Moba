// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBASoldierCharacter.h"

AMOBASoldierCharacter::AMOBASoldierCharacter()
{

}

SoldierRoad& AMOBASoldierCharacter::GetRoad()
{
	return road;
}

void AMOBASoldierCharacter::assignSoldierValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, SoldierRoad aRoad){

	assignBaseValueForAPI(aBaseProperty, aBaseValue);
	this->road = aRoad;

}
