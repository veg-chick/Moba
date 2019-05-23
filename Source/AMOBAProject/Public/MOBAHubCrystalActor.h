// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "MOBAHubCrystalActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class AMOBAPROJECT_API AMOBAHubCrystalActor : public AMOBABaseActor
{
	GENERATED_BODY()

public:
	AMOBAHubCrystalActor();
	AMOBAHubCrystalActor(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue);

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
