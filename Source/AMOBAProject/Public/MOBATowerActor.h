// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "MOBATowerActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UENUM()
enum TowerRoad { towerTop, towerMid, towerDown };

UENUM()
enum TowerType { outter, inner, highland, hub };

/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBATowerActor : public AMOBABaseActor
{
	GENERATED_BODY()

public:
	AMOBATowerActor(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, TowerRoad aRoad, TowerType aTowerType);
	AMOBATowerActor();

protected:


	TowerRoad road;

	TowerType towerType;

public:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		TowerRoad getRoad();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		TowerType getTowerType();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignTowerValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue,TowerRoad aRoad,TowerType aTowerType);

protected:
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
};
