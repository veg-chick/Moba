// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "GameFramework/Character.h"
#include "MOBABaseCharacter.generated.h"



UCLASS()
class AMOBAPROJECT_API AMOBABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMOBABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	FBaseActorProperty baseProperty;

	FBaseActorValue baseValue;

	

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void deadHandle(AActor* deadActor, AActor* deadCauser);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void attack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool canAttack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		virtual void setValue();

public:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void applyDamage(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);

	bool canBeAttacked();

	Camp getCamp();

};
