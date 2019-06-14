// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseCharacter.h"
#include "MOBASoldierCharacter.generated.h"

struct FTimerHandle;

class AMOBAHeroCharacter;

UENUM(BlueprintType)
enum class SoldierRoad : uint8
{
	soldierTop UMETA(DisplayName = "soldierTop"),
	soldierMid UMETA(DisplayName = "soldierMid"),
	soldierDown UMETA(DisplayName = "soldierDown")
};


/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBASoldierCharacter : public AMOBABaseCharacter
{
	GENERATED_BODY()

public:
	AMOBASoldierCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		SoldierRoad road;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		bool bIsStrengthened;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FTimerHandle AttackTimer;

public:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		SoldierRoad& GetRoad();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool& GetbIsStrengthened() { return bIsStrengthened; }

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignSoldierValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, SoldierRoad aRoad);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ApplyCamp(Camp Apply_camp) { GetCamp() = Apply_camp; };

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ApplyRoad(SoldierRoad Apply_road) { GetRoad() = Apply_road; };

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AttackToCharacterOnce(AMOBABaseCharacter* TargetToAttack);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRPCAttackToCharacterOnce(AMOBABaseCharacter* TargetToAttack);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AttackToActorOnce(AMOBABaseActor* TargetToAttack);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRPCAttackToActorOnce(AMOBABaseActor* TargetToAttack);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool IsEnemyHeroAttackingMyHero(AMOBAHeroCharacter* EnemyHero);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SetSoldierLevel(float level) { SetLevel(level); }

protected:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetTimer();


	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void SoldierLevelUp();

	void SetValue();
};
