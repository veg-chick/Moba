// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MOBABaseActorComponent.generated.h"

enum DamageType { physical, magic, real, treat };

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AMOBAPROJECT_API UMOBABaseActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMOBABaseActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	AActor* myOwner;



};
