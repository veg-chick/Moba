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

	float resetTime;

	float strikeRate;
	float strikeDamage;

	bool bIsInjured;

	float relativeArmorPenetration;
	float relativeMagicResistPenetration;

	int absoluteMagicResistPenetration;
	int absoluteArmorPentration;

	float lifeSteal;

};

USTRUCT(BlueprintType)
struct FHeroGrowth {

	GENERATED_BODY()

	float hpGrowth;
	float mpGrowth;

	float hpRecoveryGrowth;
	float mpRecoveryGrowth;

	int armorGrowth;
	int magicResistGrowth;

	int attackGrowth;
	float attackSpeedGrowth;

	int experienceCarriedGrowth;

	float resetTimeGrowth;
};


USTRUCT(BlueprintType)
struct FTimerHandles {

	GENERATED_BODY()

	FTimerHandle skillQTimer;
	FTimerHandle skillWTimer;
	FTimerHandle skillETimer;
	FTimerHandle skillRTimer;

	FTimerHandle resetTimer;



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

	FHeroProperty heroProperty;

	FHeroGrowth heroGrowth;

	FTimerHandles timeHandles;

	FBaseActorProperty baseProperty;

	FBaseActorValue baseValue;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "MOBAComponents")
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

public:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignHeroValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, FHeroProperty aHeroProperty, FHeroGrowth aHeroGrowth);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetHero();

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
		int& GetArmorGrowth() { return heroGrowth.armorGrowth; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		int& GetMagicResistGrowth() { return heroGrowth.magicResistGrowth; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		int& GetAttackGrowth() { return heroGrowth.attackGrowth; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetAttackSpeedGrowth() { return heroGrowth.attackSpeedGrowth; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		int& GetExperienceCarriedGrowth() { return heroGrowth.experienceCarriedGrowth; }

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
		int& GetAbsoluteMagicResistPenetration() { return heroProperty.absoluteMagicResistPenetration; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		int& GetAbsoluteArmorPentration() { return heroProperty.absoluteArmorPentration; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetLifeSteal() { return heroProperty.lifeSteal; }
};
