// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MOBABaseActor.generated.h"

UENUM()
enum Camp { blue, red, other };

USTRUCT(BlueprintType)
struct FBaseActorProperty {

	GENERATED_BODY()

	Camp baseCamp;

	float hp;
	float maxHp;
	float hpRecovery;

	bool bHaveMp;
	float mp;
	float maxMp;
	float mpRecovery;

	int armor;
	int magicResist;

	int moveSpeed;

	bool bAbleToAttack;
	bool bCanBeAttacked;
	bool bIsRemote;
	int attackRange;

	int attackStrength;
	int powerStrength;
	float attackSpeed;
	float maxAttackSpeed;

	int level;
	int maxLevel;
	int experience;

	int sightRange;

};

UENUM()
enum DamageType { physical, magic, real, treat };

USTRUCT(BlueprintType)
struct FBaseActorValue {

	GENERATED_BODY()

	int goldValue;

	int experienceValue;

};


UCLASS()
class AMOBAPROJECT_API AMOBABaseActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMOBABaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	FBaseActorProperty baseProperty;

	bool bIsBroken;

	FBaseActorValue baseValue;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void deadHandle(AActor* deadActor, AActor* deadCauser);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void attack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool canAttack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);
	
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		virtual void setValue();

public:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void applyDamage(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);

	AMOBABaseActor(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue);

	bool canBeAttacked();

	Camp getCamp();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignBaseValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue);

};
