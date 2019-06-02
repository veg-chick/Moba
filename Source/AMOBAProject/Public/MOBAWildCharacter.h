// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseCharacter.h"
#include "MOBAWildCharacter.generated.h"

struct FTimerHandle;
struct FVector;

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
	
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		AMOBABaseCharacter* GetAttacker();



protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FTimerHandle wildResetTimeHanlde;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FTimerHandle AttackTimer;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void QuickRecovery();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void resetWild();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignWildValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue);

	FVector birthLocation;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetTimer();

};
