// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBASpringActor.h"
#include "Public/MOBABaseCharacter.h"

// Sets default values
AMOBASpringActor::AMOBASpringActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMOBASpringActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMOBASpringActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMOBASpringActor::assignSpringCampForAPI(Camp aCamp)
{
	springCamp = aCamp;
}

void AMOBASpringActor::friendHandle(AActor* who)
{
	auto treatedCharacter = Cast<AMOBABaseCharacter>(who);
	if (treatedCharacter)
	{
		treatedCharacter->applyDamage(who, DamageType::treat, 500.0f, this);
	}
}

void AMOBASpringActor::enemyHandle(AActor* who)
{
	auto DamagedCharacter = Cast<AMOBABaseCharacter>(who);
	if (DamagedCharacter)
	{
		DamagedCharacter->applyDamage(who, DamageType::real, 1000.0f, this);
	}
}

