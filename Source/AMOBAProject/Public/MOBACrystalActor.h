// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "MOBACrystalActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UENUM()
enum CrystalRoad { crystaltTop, crystalMid, crystalDown };

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

	CrystalRoad road;

	UPROPERTY(VisibleAnywhere ,Category = "Components")
		UStaticMeshComponent* RootComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* BaseMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* StructMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* ClickComp;

public:

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		CrystalRoad& getRoad();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignCrystalValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, CrystalRoad aRoad);

};
