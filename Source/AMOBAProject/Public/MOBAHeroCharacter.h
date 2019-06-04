// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseCharacter.h"
#include "MOBAHeroCharacter.generated.h"

struct FTimerHandle;
struct FVector;

UENUM(BlueprintType)
enum class State : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Stun UMETA(DisplayName = "Stun"),
	Silence UMETA(DisplayName = "Silence"),
	Imprison UMETA(DisplayName = "Imprison"),
	Dead UMETA(DisplayName = "Dead")
};


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		bool bIsAttacking;
	

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterTimer")
		FTimerHandle HpRecoveryTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterTimer")
		FTimerHandle MpRecoveryTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterTimer")
		FTimerHandle StunTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterTimer")
		FTimerHandle SilenceTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterTimer")
		FTimerHandle ImprisonTimer;

};

USTRUCT(BlueprintType)
struct FSkillProperty
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		bool bCanQ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		bool bCanW;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		bool bCanE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		bool bCanR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float CDofQ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float CDofW;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float CDofE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float CDofR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		bool bCanReleaseSkills;

};

USTRUCT(BlueprintType)
struct FScoreBoard
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float KillNumber = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float DeathNumber = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float CombKillNumber = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float SoldierKillNumber = 0.0f;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FSkillProperty SkillProperty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		bool bIsAttackingHero;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MOBAComponents")
		FVector birthLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MOBAComponents")
		FScoreBoard ScoreBoard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MOBAComponents")
		State HeroState;

protected:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		virtual void BeginPlay()override;

		virtual void ReleaseQ();

		virtual void ReleaseW();

		virtual void ReleaseE();

		virtual void ReleaseR();

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

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ChangeState(State TargetState, bool IsCanceling = false);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ExceptionState(State TargetState, float Time);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetStunState() { ChangeState(State::Stun, true); }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetSilenceState() { ChangeState(State::Silence, true); }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetImprisonState() { ChangeState(State::Imprison, true); }

public:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignHeroValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, FHeroProperty aHeroProperty, FHeroGrowth aHeroGrowth);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetHero();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AddCombKillNumber();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AddExperienceToHero(float ExperienceValue);

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

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbRecallSucceed() { return heroProperty.bRecallSucceed; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbCanQ() { return SkillProperty.bCanQ; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbCanW() { return SkillProperty.bCanW; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbCanE() { return SkillProperty.bCanE; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbCanR() { return SkillProperty.bCanR; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetCDofQ() { return SkillProperty.CDofQ; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetCDofW() { return SkillProperty.CDofW; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetCDofE() { return SkillProperty.CDofE; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetCDofR() { return SkillProperty.CDofR; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbCanReleaseSkills() { return SkillProperty.bCanReleaseSkills; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbIsAttacking() { return heroProperty.bIsAttacking; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetKillNumber() { return ScoreBoard.KillNumber; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetDeathNumber() { return ScoreBoard.DeathNumber; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetCombKillNumber() { return ScoreBoard.CombKillNumber; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetSoldierKillNumber() { return ScoreBoard.SoldierKillNumber; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbIsAttackingHero() { return bIsAttackingHero; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		State& GetHeroState() { return HeroState; }
};
