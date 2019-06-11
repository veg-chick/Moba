// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseCharacter.h"
#include "MOBATowerCharacter.generated.h"

class UStaticMeshComponent;
class USphereComponent;
struct FTimerHandle;

class AMOBACrystalActor;
class AMOBAHubCrystalActor;
class AMOBAHeroCharacter;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		AMOBATowerCharacter* TowerPointerToTower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		AMOBACrystalActor* TowerPointerToCrystal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		AMOBAHubCrystalActor* TowerPointerToHub;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		FTimerHandle AttackTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* BeAttackedFX;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* AttackFX;

public:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		TowerRoad& GetRoad();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		TowerType& GetTowerType();

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignTowerValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, TowerRoad aRoad, TowerType aTowerType);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AttackToCharacterOnce(AMOBABaseCharacter* TargetToAttack);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRPCAttackToCharacter(AMOBABaseCharacter* TargetToAttack);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool IsEnemyHeroAttackingMyHero(AMOBAHeroCharacter* EnemyHero);

		void TowerDeadHandle();


protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* RootComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* BaseMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* StructMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USceneComponent* AttackComp;




protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void ResetTimer();

	void SetValue();

	void PlayEffects(FVector Location);

};
