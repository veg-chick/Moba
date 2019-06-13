// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBABaseActor.h"
#include "GameFramework/Actor.h"
#include "MOBASpringActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMOBA")
		Camp springCamp;

	UPROPERTY(VisibleAnywhere, Category = "MyMOBA")
		USphereComponent* OnOverlapComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* Heal;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* Lighting;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void AssignSpringCampForAPI(Camp aCamp);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		Camp& GetCamp() { return springCamp; };

protected:
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void FriendHandle(AMOBABaseCharacter* who);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRPCFriendHandle(AMOBABaseCharacter* who);

	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void EnemyHandle(AMOBABaseCharacter* who);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRPCEnemyHandle(AMOBABaseCharacter* who);

	UFUNCTION(NetMulticast, Reliable)
		void PlayRedemptionEffects(FVector Location);

	UFUNCTION(NetMulticast, Reliable)
		void PlayExecutionEffects(FVector Location);

	UFUNCTION()
		void OverlapHandle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	float nowtime;
};
