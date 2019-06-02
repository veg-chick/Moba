// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseCharacter.h"
#include "MOBASoldierCharacter.generated.h"

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

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AttackToActorOnce(AMOBABaseActor* TargetToAttack);


	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool IsEnemyHeroAttackingMyHero(AMOBABaseCharacter* EnemyHero);




};
