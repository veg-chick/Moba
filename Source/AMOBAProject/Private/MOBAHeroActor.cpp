// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBAHeroActor.h"
#include "Engine/EngineTypes.h"

AMOBAHeroActor::AMOBAHeroActor() {

}

AMOBAHeroActor::AMOBAHeroActor(FBaseActorProperty bP, FBaseActorValue bV, FHeroProperty hP, FHeroGrowth hG, FHeroValue hV) :AMOBABaseActor(bP, bV), heroProperty(hP), heroGrowth(hG), heroValue(hV) {

}

void AMOBAHeroActor::resetHero() {

}

void AMOBAHeroActor::resetQSkill() {

}

void AMOBAHeroActor::resetWSkill() {

}

void AMOBAHeroActor::resetESkill() {

}

void AMOBAHeroActor::resetRSkill() {

}

