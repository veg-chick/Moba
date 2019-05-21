// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBATowerActor.h"

AMOBATowerActor::AMOBATowerActor(BaseProperty aBaseProperty, BaseValue aBaseValue, TowerRoad aRoad, TowerType aTowerType) :AMOBABaseActor(aBaseProperty, aBaseValue), road(aRoad), towerType(aTowerType) {

}

AMOBATowerActor::AMOBATowerActor(){

}

TowerRoad AMOBATowerActor::getRoad() {
	return road;
}

TowerType AMOBATowerActor::getTowerType() {
	return towerType;
}
