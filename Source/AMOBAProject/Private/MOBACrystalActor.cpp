// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBACrystalActor.h"

AMOBACrystalActor::AMOBACrystalActor(BaseProperty ABaseProperty, BaseValue aBaseValue, CrystalRoad aRoad) :AMOBABaseActor(ABaseProperty, aBaseValue), road(aRoad) {

}

AMOBACrystalActor::AMOBACrystalActor() {

}

bool AMOBACrystalActor::isBroken() {
	return bIsBroken;
}

CrystalRoad AMOBACrystalActor::getRoad() {
	return road;
}
