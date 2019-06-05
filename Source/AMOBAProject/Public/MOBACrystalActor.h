// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "MOBACrystalActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

class AMOBATowerCharacter;

UENUM(BlueprintType)
enum class CrystalRoad : uint8
{
	crystalTop UMETA(DisplayName = "crystalTop"),
	crystalMid UMETA(DisplayName = "crystalMid"),
	crystalDown UMETA(DisplayName = "crystalDown")
};

/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBACrystalActor : public AMOBABaseActor
{
	GENERATED_BODY()

public:
	AMOBACrystalActor();

	AMOBACrystalActor(FBaseActorProperty ABaseProperty, FBaseActorValue aBaseValue, CrystalRoad aRoad);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		CrystalRoad road;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* RootComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* BaseMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* StructMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* ClickComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		AMOBATowerCharacter* CrystalPointer;

public:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		CrystalRoad& getRoad();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignCrystalValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, CrystalRoad aRoad);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void CrystalDeadHandle();

	void SetValue();

};
