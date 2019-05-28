// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "GameFramework/Character.h"
#include "MOBABaseCharacter.generated.h"



UCLASS()
class AMOBAPROJECT_API AMOBABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMOBABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(EditAnywhere,Category="MyMOBA")
	FBaseActorProperty baseProperty;

	UPROPERTY(EditAnywhere,Category="MyMOBA")
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


	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignBaseValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue);

public:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbCanBeAttacked() { return baseProperty.bCanBeAttacked; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		Camp& GetCamp() { return baseProperty.baseCamp; }

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
		int& GetArmor() { return baseProperty.armor; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		int& GetMagicResist() { return baseProperty.magicResist; }

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
		int& GetAttackStrength() { return baseProperty.attackStrength; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		int& GetPowerStrength() { return baseProperty.powerStrength; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetAttackSpeed() { return baseProperty.attackSpeed; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetMaxAttackSpeed() { return baseProperty.maxAttackSpeed; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		int& GetLevel() { return baseProperty.level; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		int& GetMaxLevel() { return baseProperty.maxLevel; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		int& GetExperience() { return baseProperty.experience; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		int& GetGoldValue() { return baseValue.goldValue; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		int& GetExperienceValue() { return baseValue.experienceValue; }

public:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void setHp(float ok) { this->baseProperty.hp = ok; }
};
