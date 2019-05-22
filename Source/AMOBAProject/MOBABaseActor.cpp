// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBABaseActor.h"

void AMOBABaseActor::setValue() {

}

// Sets default values
AMOBABaseActor::AMOBABaseActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMOBABaseActor::AMOBABaseActor(BaseProperty aBaseProperty, BaseValue aBaseValue) :baseProperty(aBaseProperty), baseValue(aBaseValue) {

}

// Called when the game starts or when spawned
void AMOBABaseActor::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void AMOBABaseActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AMOBABaseActor::applyDamage(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser) {

}

void AMOBABaseActor::deadHandle(AActor* deadActor, AActor* deadCauser) {

}

void AMOBABaseActor::attack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser) {

}

bool AMOBABaseActor::canAttack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser) {
	return false;
}

