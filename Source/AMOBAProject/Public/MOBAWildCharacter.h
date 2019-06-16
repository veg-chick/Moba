// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseCharacter.h"
#include "MOBAWildCharacter.generated.h"

struct FTimerHandle;
struct FVector;
class AMOBAHeroCharacter;

UENUM(BlueprintType)
enum class AWildType : uint8
{
	BlueBuff UMETA(DisplayName = "BlueBuff"),
	RedBuff UMETA(DisplayName = "RedBuff"),
	Nash UMETA(DisplayName = "Nash"),
};


/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBAWildCharacter : public AMOBABaseCharacter
{
	GENERATED_BODY()

public:

	AMOBAWildCharacter();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AttackToCharacterOnce(AMOBABaseCharacter* TargetToAttack);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRPCAttackToCharacterOnce(AMOBABaseCharacter* TargetToAttack);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		AMOBABaseCharacter* GetAttacker();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		AWildType GetWildType() { return this->WildType; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void KillValueForHero(AMOBAHeroCharacter* AHero);


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FTimerHandle WildResetTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FTimerHandle BlueBuffTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FTimerHandle RedBuffTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FTimerHandle NashTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FTimerHandle AttackTimer;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void QuickRecovery();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetWild();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignWildValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue);

	AWildType WildType;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetTimer();

	void SetValue();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void WildLevelUp();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetWildLevel(float level);

public:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void WildDeadHandle();

	UFUNCTION(BlueprintImplementableEvent, Category = "MyMOBA")
		void WildResetHandle();

};
