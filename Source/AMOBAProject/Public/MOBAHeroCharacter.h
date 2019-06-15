// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseCharacter.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "MOBAHeroCharacter.generated.h"

struct FTimerHandle;
struct FVector;

class AMOBAHeroADOne;
class AMOBAHeroADCOne;
class AMOBAHeroAPOne;
class AMOBAHeroTankOne;
class AMOBAHeroAssistOne;
class AMOBAHeroAssassinOne;

UENUM(BlueprintType)
enum class State : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Stun UMETA(DisplayName = "Stun"),
	Silence UMETA(DisplayName = "Silence"),
	Imprison UMETA(DisplayName = "Imprison"),
	Dead UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class Equip : uint8
{
	NullEquip UMETA(DisplayName = "Null"),
	Sword UMETA(DisplayName = "Sword"),
	Pickaxe UMETA(DisplayName = "Pickaxe"),
	Dagger UMETA(DisplayName = "Dagger"),
	BigSword UMETA(DisplayName = "BigSword"),
	Cloth UMETA(DisplayName = "Cloth"),
	Cloak UMETA(DisplayName = "Cloak"),
	Shield UMETA(DisplayName = "Shield"),
	Armor UMETA(DisplayName = "Armor"),
	MagicBook UMETA(DisplayName = "MagicBook"),
	Wand UMETA(DisplayName = "Wand"),
	Boxer UMETA(DisplayName = "Boxer"),
	StrikeCloak UMETA(DisplayName = "Cloak"),
	LifePotion UMETA(DisplayName = "LifePotion"),
	MagicPotion UMETA(DisplayName = "MagicPotion")
};

USTRUCT(BlueprintType)
struct FHeroProperty {

	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "HeroCharacterProperty")
		float deadtime;

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
		float FakeAttackSpeed;

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
struct FHeroPack
{
	GENERATED_BODY()

	Equip PackOne = Equip::NullEquip;
	Equip PackTwo = Equip::NullEquip;
	Equip PackThree = Equip::NullEquip;
	Equip PackFour = Equip::NullEquip;
	Equip PackFive = Equip::NullEquip;
	Equip PackSix = Equip::NullEquip;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterTimer")
		FTimerHandle DeadTimer;

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
		bool bMayQ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		bool bMayW;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		bool bMayE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float CDofQ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float CDofW;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float CDofE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		bool bCanReleaseSkills;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float CDReduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float MaxCDReduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		bool bIsReleasingQ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		bool bIsReleasingW;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		bool bIsReleasingE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float SkillPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float QPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float WPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float EPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float QCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float WCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float ECost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float QRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float WRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroCharacterProperty")
		float ERange;

	float RemainingQCD;
	float RemainingWCD;
	float RemainingECD;

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

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FHeroProperty heroProperty;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FHeroGrowth heroGrowth;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FTimerHandles TimeHandles;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FHeroPack HeroPack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FSkillProperty SkillProperty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		bool bIsAttackingHero;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "MOBAComponents")
		FVector birthLocation;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "MOBAComponents")
		State HeroState;

	FTimerManager QTimerManager;
	FTimerManager WTimerManager;
	FTimerManager ETimerManager;

	FTimerHandle DeadTimer = TimeHandles.DeadTimer;

protected:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		virtual void BeginPlay()override;

	void SetValue();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetQSkill();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetWSkill();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetESkill();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetHeroHandle();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void levelUp();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRPCRecall();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void RecallHandle();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void HpRecoveryHandle();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRPCHpRecovery();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void MpRecoveryHandle();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRPCMpRecovery();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRPCChangeState(State TargetState, bool IsCanceling = false);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetStunState() { ServerRPCChangeState(State::Stun, true); }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetSilenceState() { ServerRPCChangeState(State::Silence, true); }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetImprisonState() { ServerRPCChangeState(State::Imprison, true); }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void DeadHeroHandle() { this->SetActorLocation(birthLocation); }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetSkills(float Target);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRPCBuyEquipment(Equip BuyingEquip);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRPCSellEquipment(float PackageNumber);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRPCStopMove();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerMoveToLocation(const FVector DestLocation, float Speed);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerAttackToActor(AMOBABaseActor* BeAttackedActor);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerAttackToCharacter(AMOBABaseCharacter* BeAttackedCharacter);


public:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignHeroValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, FHeroProperty aHeroProperty, FHeroGrowth aHeroGrowth);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetHero();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AddExperienceToHero(float ExperienceValue);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetAttackTimer();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AddCDReduction(float CD);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ChangeReleasingSkill(float Target);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ExceptionState(State TargetState, float Time);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetReleasingQ() { this->GetbIsReleasingQ() = false; this->SetbCanMove(true); this->SetbAbleToAttack(true); }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetReleasingW() { this->GetbIsReleasingW() = false; this->SetbCanMove(true); this->SetbAbleToAttack(true); }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetReleasingE() { this->GetbIsReleasingE() = false; this->SetbCanMove(true); this->SetbAbleToAttack(true); }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void HeroReleaseQ(AMOBAHeroCharacter* Target = nullptr);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void HeroReleaseW(AMOBAHeroCharacter* Target = nullptr);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void HeroReleaseE(AMOBAHeroCharacter* Target = nullptr);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void StopMove();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void Recall();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void BuyEquipment(Equip BuyingEquip);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SellEquipment(float PackageNumber);

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
		float& GetCDofQ() { return SkillProperty.CDofQ; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetCDofW() { return SkillProperty.CDofW; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetCDofE() { return SkillProperty.CDofE; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbCanReleaseSkills() { return SkillProperty.bCanReleaseSkills; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetSkillPoint() { return SkillProperty.SkillPoint; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetQPoint() { return SkillProperty.QPoint; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetWPoint() { return SkillProperty.WPoint; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetEPoint() { return SkillProperty.EPoint; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool GetCanAddQ() { return (SkillProperty.SkillPoint) && (baseProperty.level / 2.0f > SkillProperty.QPoint) && (SkillProperty.QPoint < 5.0f); }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool GetCanAddW() { return (SkillProperty.SkillPoint) && (baseProperty.level / 2.0f > SkillProperty.WPoint) && (SkillProperty.WPoint < 5.0f); }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool GetCanAddE() { return (SkillProperty.SkillPoint) && (baseProperty.level / 5.0f) > (SkillProperty.EPoint + 1.0f) && (SkillProperty.EPoint < 5.0f); }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbIsAttackingHero() { return bIsAttackingHero; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetCDReduction() { return SkillProperty.CDReduction; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetMaxCDReduction() { return SkillProperty.MaxCDReduction; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		State& GetHeroState() { return HeroState; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetFakeAttackSpeed() { return heroProperty.FakeAttackSpeed; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbIsReleasingQ() { return SkillProperty.bIsReleasingQ; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbIsReleasingW() { return SkillProperty.bIsReleasingW; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbIsReleasingE() { return SkillProperty.bIsReleasingE; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetQCost() { return SkillProperty.QCost; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetWCost() { return SkillProperty.WCost; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetECost() { return SkillProperty.ECost; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbMayQ() { return SkillProperty.bMayQ; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbMayW() { return SkillProperty.bMayW; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbMayE() { return SkillProperty.bMayE; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetQRange() { return SkillProperty.QRange; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetWRange() { return SkillProperty.WRange; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float& GetERange() { return SkillProperty.ERange; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AddQ();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AddW();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AddE();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float GetRemainingQCD() { return SkillProperty.RemainingQCD; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float GetRemainingWCD() { return SkillProperty.RemainingWCD; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		float GetRemainingECD() { return SkillProperty.RemainingWCD; }

};
