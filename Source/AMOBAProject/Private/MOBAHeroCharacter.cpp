// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBAHeroCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"
#include "Engine/World.h"
#include "MOBAPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AMOBAHeroCharacter::AMOBAHeroCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1600.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMOBAHeroCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (APlayerController * PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}


void AMOBAHeroCharacter::SetNewMoveDestination(const FVector DestLocation, float Speed)
{
	float const Distance = FVector::Dist(DestLocation, GetActorLocation());

	// We need to issue move command only if far enough in order for walk animation to play correctly
	if ((Distance > 120.0f)) {

		this->GetCharacterMovement()->MaxWalkSpeed = Speed;
		AMOBAPlayerController* PC = Cast<AMOBAPlayerController>(this->GetController());
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(PC, DestLocation);
	}
}

void AMOBAHeroCharacter::AttackToAActor(AMOBABaseActor* BeAttackedActor)
{
	float const Distance = FVector::Dist(BeAttackedActor->GetActorLocation(), this->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Attack To Actor Succeed!"));
	if (Distance > this->getAttackRange()) return;
}

void AMOBAHeroCharacter::AttackToACharacter(AMOBABaseCharacter* BeAttackedCharacter)
{
	float const Distance = FVector::Dist(BeAttackedCharacter->GetActorLocation(), this->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Attack To Character Succeed!"));
	if (Distance > this->getAttackRange()) return;
}

void AMOBAHeroCharacter::resetHero()
{
	//No need to disable player input
	//DetachFromControllerPendingDestroy();

	//Prohibition of release Skills
	this->baseProperty.bAbleToAttack = false;

	auto myMovementComp = GetCharacterMovement();
	//Set the move speed to 0
	auto accelerationBefore = myMovementComp->MaxAcceleration;
	myMovementComp->MaxAcceleration = 0.0f;
	auto  maxWalkSpeedBefore = myMovementComp->MaxWalkSpeed;
	myMovementComp->MaxWalkSpeed = 0.0f;

	float resetTime = this->heroProperty.resetTime;
	auto myTimeHanlde = timeHandles.resetTimer;

	GetWorldTimerManager().SetTimer(myTimeHanlde, this, &AMOBAHeroCharacter::resetHeroHandle, resetTime);

	//Set the move speed to before
	myMovementComp->MaxAcceleration = accelerationBefore;
	myMovementComp->MaxWalkSpeed = maxWalkSpeedBefore;

}

void AMOBAHeroCharacter::BeginPlay()
{
	Super::BeginPlay();


	birthLocation = this->GetActorLocation();

}

void AMOBAHeroCharacter::resetQSkill()
{

}

void AMOBAHeroCharacter::resetWSkill()
{

}

void AMOBAHeroCharacter::resetESkill()
{

}

void AMOBAHeroCharacter::resetRSkill()
{
	
}

void AMOBAHeroCharacter::resetHeroHandle()
{

	this->baseProperty.hp = this->baseProperty.maxHp;
	this->baseProperty.mp = this->baseProperty.maxMp;
	this->baseProperty.bAbleToAttack = true;
	//Allow release skills

	this->SetActorLocation(birthLocation);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

void AMOBAHeroCharacter::levelUp()
{
	auto& myPro = this->baseProperty;
	if (myPro.level < myPro.maxLevel) {
		auto& heroPro = this->heroProperty;
		auto myGro = this->heroGrowth;


		myPro.maxHp += myGro.hpGrowth;
		myPro.hp += myGro.hpGrowth;

		myPro.maxMp += myGro.mpGrowth;
		myPro.mp += myGro.mpGrowth;

		myPro.attackStrength += myGro.attackGrowth;
		myPro.attackSpeed = FMath::Clamp(myPro.attackSpeed + myGro.attackSpeedGrowth, 0.0f, myPro.maxAttackSpeed);

		myPro.armor += myGro.armorGrowth;
		myPro.magicResist += myGro.magicResistGrowth;

		heroPro.resetTime += myGro.resetTimeGrowth;

	}



}

void AMOBAHeroCharacter::reCall()
{
	auto& myTimeHandle = this->timeHandles.resetTimer;

	GetWorldTimerManager().ClearTimer(myTimeHandle);

	GetWorldTimerManager().SetTimer(myTimeHandle, this, &AMOBAHeroCharacter::reCallHandle, 8.0f);

}

void AMOBAHeroCharacter::reCallHandle()
{
	SetActorLocation(birthLocation);
}

void AMOBAHeroCharacter::assignHeroValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, FHeroProperty aHeroProperty, FHeroGrowth aHeroGrowth) {

	assignBaseValueForAPI(aBaseProperty, aBaseValue);
	this->heroProperty = aHeroProperty;
	this->heroGrowth = aHeroGrowth;

}
