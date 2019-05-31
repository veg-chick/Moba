// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseCharacter.h"
#include "MOBAHeroCharacter.generated.h"

struct FTimerHandle;
struct FVector;

USTRUCT(BlueprintType)
struct FHeroProperty {

	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float resetTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float strikeRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float strikeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		bool bIsInjured;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float relativeArmorPenetration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float relativeMagicResistPenetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float absoluteMagicResistPenetration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float absoluteArmorPentration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float lifeSteal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		bool bRecallSucceed;

};

USTRUCT(BlueprintType)
struct FHeroGrowth {

	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterGrowth")
		float hpGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterGrowth")
		float mpGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterGrowth")
		float hpRecoveryGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterGrowth")
		float mpRecoveryGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterGrowth")
		float armorGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterGrowth")
		float magicResistGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterGrowth")
		float attackGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterGrowth")
		float attackSpeedGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterGrowth")
		float experienceCarriedGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterGrowth")
		float resetTimeGrowth;
};


USTRUCT(BlueprintType)
struct FTimerHandles {

	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterTimer")
		FTimerHandle SkillQTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterTimer")
		FTimerHandle SkillWTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterTimer")
		FTimerHandle SkillETimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterTimer")
		FTimerHandle SkillRTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterTimer")
		FTimerHandle ResetTimer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterTimer")
		FTimerHandle AttackTimer;

};


/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBAHeroCharacter : public AMOBABaseCharacter
{
	GENERATED_BODY()

public:
	AMOBAHeroCharacter();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FHeroProperty heroProperty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FHeroGrowth heroGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FTimerHandles timeHandles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MOBAComponents")
		FVector birthLocation;

protected:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		virtual void BeginPlay()override;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetQSkill();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetWSkill();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetESkill();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetRSkill();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetHeroHandle();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void levelUp();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void reCall();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void reCallHandle();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void HpRecoveryHandle();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void MpRecoveryHandle();
	
public:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignHeroValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, FHeroProperty aHeroProperty, FHeroGrowth aHeroGrowth);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetHero();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetAttackTimer();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerMoveToLocation(const FVector DestLocation, float Speed);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerAttackToActor(AMOBABaseActor* BeAttackedActor);
	
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerAttackToCharacter(AMOBABaseCharacter* BeAttackedCharacter);

public:
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation, float Speed);

	void AttackToAActor(AMOBABaseActor* BeAttackedActor);

	void AttackToACharacter(AMOBABaseCharacter* BeAttackedCharacter);


protected:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

public:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetHpGrowth() { return heroGrowth.hpGrowth; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetMpGrowth() { return heroGrowth.mpGrowth; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetHpRecoveryGrowth() { return heroGrowth.hpRecoveryGrowth; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetMpRecoveryGrowth() { return heroGrowth.mpRecoveryGrowth; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetArmorGrowth() { return heroGrowth.armorGrowth; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetMagicResistGrowth() { return heroGrowth.magicResistGrowth; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetAttackGrowth() { return heroGrowth.attackGrowth; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetAttackSpeedGrowth() { return heroGrowth.attackSpeedGrowth; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetExperienceCarriedGrowth() { return heroGrowth.experienceCarriedGrowth; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetResetTimeGrowth() { return heroGrowth.resetTimeGrowth; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetResetTime() { return heroProperty.resetTime; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetStrikeRate() { return heroProperty.strikeRate; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetStrikeDamage() { return heroProperty.strikeDamage; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbIsInjured() { return heroProperty.bIsInjured; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetRelativeArmorPenetration() { return heroProperty.relativeArmorPenetration; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetRelativeMagicResistPenetration() { return heroProperty.relativeMagicResistPenetration; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetAbsoluteMagicResistPenetration() { return heroProperty.absoluteMagicResistPenetration; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetAbsoluteArmorPentration() { return heroProperty.absoluteArmorPentration; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetLifeSteal() { return heroProperty.lifeSteal; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetGold() { return heroProperty.Gold; }

	UFUNCTION(BlueprintCallable,Category="MyMOBA")
		bool& GetbRecallSucceed() { return heroProperty.bRecallSucceed; }

};
