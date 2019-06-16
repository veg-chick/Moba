// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "GameFramework/Character.h"
#include "MOBABaseCharacter.generated.h"

struct FBaseActorProperty;
struct FBaseActorValue;

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

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FBaseActorProperty baseProperty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FBaseActorValue baseValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		AMOBABaseCharacter* Attacker;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* AttackedFX;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void DeadHandle(AMOBABaseCharacter* DeadCharacter, AMOBABaseCharacter* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool canAttack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);

public:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ApplyDamage(AMOBABaseCharacter* DamagedActor, DamageType Type, float Damage, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ReceiveDamageFromCharacter(AMOBABaseCharacter* DamagedActor,DamageType Type, float Damage,AMOBABaseCharacter* DamageCauser);

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
		float& GetSightrange() { return baseProperty.sightRange; }

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
		bool& GetbIsBeingAttacked() { return baseProperty.bIsBeingAttacked; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbCanMove() { return baseProperty.bCanMove; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbIsAttacking() { return baseProperty.bIsAttacking; }



	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetbCanBeAttacked(bool newbool) { baseProperty.bCanBeAttacked = newbool; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetCamp(Camp newcamp ) {  baseProperty.baseCamp = newcamp; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetHp(float newhp) {  baseProperty.hp = newhp; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetMaxHp(float newmaxhp) {  baseProperty.maxHp = newmaxhp; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetHpRecovery(float newhprec) {  baseProperty.hpRecovery = newhprec; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetBHaveMp(bool newbool) {  baseProperty.bHaveMp = newbool; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetMp(float newmp) {  baseProperty.mp = newmp; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetMaxMp(float newmaxmp) {  baseProperty.maxMp = newmaxmp; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetMpRecovery(float newmprec) {  baseProperty.mpRecovery = newmprec; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetArmor(float newarmor) {  baseProperty.armor = newarmor; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetMagicResist(float newmagicres) {  baseProperty.magicResist = newmagicres; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetMoveSpeed(float newspeed) {  baseProperty.moveSpeed = newspeed; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetbAbleToAttack(bool newbool) {  baseProperty.bAbleToAttack = newbool; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetbIsRemote(bool newbool) {  baseProperty.bIsRemote = newbool; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetAttackRange(float newattackrange) {  baseProperty.attackRange = newattackrange; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetSightrange(float newsightrange) {  baseProperty.sightRange = newsightrange; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetAttackStrength(float newattackstrength) {  baseProperty.attackStrength = newattackstrength; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetPowerStrength(float newpowerstrength) {  baseProperty.powerStrength = newpowerstrength; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetAttackSpeed(float newattackspeed) {  baseProperty.attackSpeed = newattackspeed; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetMaxAttackSpeed(float newmaxAS) {  baseProperty.maxAttackSpeed = newmaxAS; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetLevel(float newlevel) {  baseProperty.level = newlevel; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetMaxLevel(float newmaxlev) {  baseProperty.maxLevel = newmaxlev; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetExperience(float newexp) {  baseProperty.experience = newexp; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetGoldValue(float newgold) {  baseValue.goldValue = newgold; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetExperienceValue(float newexpval) {  baseValue.experienceValue = newexpval; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetbIsBeingAttacked(bool newbool) {  baseProperty.bIsBeingAttacked = newbool; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetbCanMove(bool newbool) {  baseProperty.bCanMove = newbool; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetbIsAttacking(bool newbool) {  baseProperty.bIsAttacking = newbool; }

};
