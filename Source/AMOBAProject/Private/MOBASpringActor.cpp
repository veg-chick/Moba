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
	
	//Detect if there is an overlapping AMOBABaseCharacter

}

void AMOBASpringActor::AssignSpringCampForAPI(Camp aCamp)
{
	springCamp = aCamp;
}

void AMOBASpringActor::FriendHandle(AMOBABaseCharacter* who)
{
	if (who)
	{
		if (who->GetHp() != 0.0f)
		{
			while (who->GetHp() < who->GetMaxHp())
			{
				who->ApplyDamage(who, DamageType::treat, 500.0f, this);
			}
		}
	}
}

void AMOBASpringActor::EnemyHandle(AMOBABaseCharacter* who)	
{
	if (who)
	{
		if (who->GetHp() != 0.0f)
		{
			while (who->GetHp() > 0.0f)
			{
				who->ApplyDamage(who, DamageType::real, 1000.0f, this);
			}
		}
	}
}

void AMOBASpringActor::OverlapHandle(AMOBABaseCharacter* who)
{
	if (this->GetCamp() == who->GetCamp())
	{
		FriendHandle(who);
	}
	else
	{
		EnemyHandle(who);
	}
}

