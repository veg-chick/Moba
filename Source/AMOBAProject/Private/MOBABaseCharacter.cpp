// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBABaseCharacter.h"

// Sets default values
AMOBABaseCharacter::AMOBABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMOBABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMOBABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMOBABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

