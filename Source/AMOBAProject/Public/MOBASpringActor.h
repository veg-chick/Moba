// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "GameFramework/Actor.h"
#include "MOBASpringActor.generated.h"

UCLASS()
class AMOBAPROJECT_API AMOBASpringActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMOBASpringActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	Camp springCamp;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void assignSpringCampForAPI(Camp aCamp);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		Camp& GetCamp() { return springCamp; };

protected:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void friendHandle(AActor* who);
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void enemyHandle(AActor* who);
};
