// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseCharacter.h"
#include "MOBATowerCharacter.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UENUM(BlueprintType)
enum class TowerRoad : uint8
{
	towerTop UMETA(DisplayName = "towerTop"),
	towerMid UMETA(DisplayName = "towerMid"),
	towerDown UMETA(DisplayName = "towerDown")
};

UENUM(BlueprintType)
enum class TowerType : uint8
{
	outter UMETA(DisplayName = "outter"),
	inner UMETA(DisplayName = "inner"),
	highland UMETA(DisplayName = "highland"),
	hub UMETA(DisplayName = "hub")
};


/**
 *
 */
UCLASS()
class AMOBAPROJECT_API AMOBATowerCharacter : public AMOBABaseCharacter
{
	GENERATED_BODY()

public:
	AMOBATowerCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		TowerRoad road;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		TowerType towerType;

public:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		TowerRoad& getRoad();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		TowerType& getTowerType();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignTowerValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, TowerRoad aRoad, TowerType aTowerType);

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
