// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MOBABaseActor.generated.h"

UENUM(BlueprintType)
enum class Camp : uint8
{
	blue UMETA(DisplayName = "blue"),
	red UMETA(DisplayName = "red"),
	other UMETA(DisplayName = "other")
};

USTRUCT(BlueprintType)
struct FBaseActorProperty {

	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		Camp baseCamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float maxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float hpRecovery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		bool bHaveMp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float mp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float maxMp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float mpRecovery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float magicResist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float moveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		bool bAbleToAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		bool bCanBeAttacked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		bool bIsRemote;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float attackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float sightRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float attackStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float powerStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float attackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float maxAttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float maxLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseProperty")
		float experience;

};

UENUM(BlueprintType)
enum class DamageType : uint8
{
	physical UMETA(DisplayName = "physical"),
	magic UMETA(DisplayName = "magic"),
	real UMETA(DisplayName = "real"),
	treat UMETA(DisplayName = "treat")
};

USTRUCT(BlueprintType)
struct FBaseActorValue {

	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseValue")
		float goldValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorBaseValue")
		float experienceValue;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FBaseActorProperty baseProperty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		bool bIsBroken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FBaseActorValue baseValue;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void DeadHandle(AMOBABaseActor* DeadActor);

	//UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		//void attack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool canAttack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		virtual void setValue();

public:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReceiveDamageFromCharacter(AMOBABaseActor* DamagedActor, DamageType Type, float Damage, AMOBABaseCharacter* DamageCauser);

	AMOBABaseActor(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignBaseValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue);

public:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbCanBeAttacked();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		Camp& GetCamp();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetHp() { return baseProperty.hp; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetMaxHp() { return baseProperty.maxHp; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetHpRecovery() { return baseProperty.hpRecovery; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetBHaveMp() { return baseProperty.bHaveMp; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetMp() { return baseProperty.mp; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetMaxMp() { return baseProperty.maxMp; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetMpRecovery() { return baseProperty.mpRecovery; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetArmor() { return baseProperty.armor; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetMagicResist() { return baseProperty.magicResist; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetMoveSpeed() { return baseProperty.moveSpeed; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbAbleToAttack() { return baseProperty.bAbleToAttack; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbIsRemote() { return baseProperty.bIsRemote; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetAttackRange() { return baseProperty.attackRange; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetSeightrange() { return baseProperty.sightRange; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetAttackStrength() { return baseProperty.attackStrength; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetPowerStrength() { return baseProperty.powerStrength; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetAttackSpeed() { return baseProperty.attackSpeed; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetMaxAttackSpeed() { return baseProperty.maxAttackSpeed; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetLevel() { return baseProperty.level; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetMaxLevel() { return baseProperty.maxLevel; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetExperience() { return baseProperty.experience; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetGoldValue() { return baseValue.goldValue; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetExperienceValue() { return baseValue.experienceValue; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbIsBroken() { return bIsBroken; }

};
