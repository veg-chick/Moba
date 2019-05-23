// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBASoldierActor.h"

AMOBASoldierActor::AMOBASoldierActor(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, SoldierRoad aRoad) :AMOBABaseActor(aBaseProperty, aBaseValue), road(aRoad) {

}

AMOBASoldierActor::AMOBASoldierActor() {

}

SoldierRoad AMOBASoldierActor::getRoad() {
	return road;
}
