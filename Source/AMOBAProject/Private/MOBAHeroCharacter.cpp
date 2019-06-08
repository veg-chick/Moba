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
#include "Math/RandomStream.h"
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

	this->SetValue();

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
	this->GetbRecallSucceed() = false;
	float const Distance = FVector::Dist(DestLocation, GetActorLocation());

	// We need to issue move command only if far enough in order for walk animation to play correctly
	if (Distance > 120.0f && this->GetbCanMove())
	{
		this->GetCharacterMovement()->MaxWalkSpeed = Speed;
		if (Speed > 10) 
		{
			AMOBAPlayerController* PC = Cast<AMOBAPlayerController>(this->GetController());
			if (PC)
			{
				UE_LOG(LogTemp, Warning, TEXT("Move!"))
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(PC, DestLocation);
			}
		}
	}
	if (Role < ROLE_Authority)
	{
		ServerMoveToLocation(DestLocation, Speed);
	}
}


void AMOBAHeroCharacter::ServerMoveToLocation_Implementation(const FVector DestLocation, float Speed)
{
	float const Distance = FVector::Dist(DestLocation, GetActorLocation());

	// We need to issue move command only if far enough in order for walk animation to play correctly
	if (Distance > 120.0f && this->GetbCanMove())
	{
		this->GetCharacterMovement()->MaxWalkSpeed = Speed;
		if (Speed > 10)
		{
			AMOBAPlayerController* PC = Cast<AMOBAPlayerController>(this->GetController());
			if (PC)
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(PC, DestLocation);
			}
		}
	}
}

bool AMOBAHeroCharacter::ServerMoveToLocation_Validate(const FVector DestLocation, float Speed)
{
	return true;
}

void AMOBAHeroCharacter::AttackToAActor(AMOBABaseActor* BeAttackedActor)
{
	float const Distance = FVector::Dist(BeAttackedActor->GetActorLocation(), this->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Attack To Actor Succeed!"));
	if (Distance > this->GetAttackRange()) return;
	else
	{
		this->GetbIsAttacking() = true;
		this->GetbRecallSucceed() = false;
		this->GetbAbleToAttack() = false;
		ServerAttackToActor(BeAttackedActor);
		float AttackCDTime = 1.0f / this->GetAttackSpeed();
		auto MyTimeHanlde = timeHandles.AttackTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHanlde);
		GetWorldTimerManager().SetTimer(MyTimeHanlde, this, &AMOBAHeroCharacter::ResetAttackTimer, AttackCDTime);
		this->GetbIsAttacking() = false;
	}

}

void AMOBAHeroCharacter::ServerAttackToActor_Implementation(AMOBABaseActor* BeAttackedActor)
{
	auto MyAttackStrength = this->GetAttackStrength();
	BeAttackedActor->ReceiveDamageFromCharacter(BeAttackedActor, DamageType::physical, MyAttackStrength, this);
}

bool AMOBAHeroCharacter::ServerAttackToActor_Validate(AMOBABaseActor* BeAttackedActor)
{
	return true;
}


void AMOBAHeroCharacter::AttackToACharacter(AMOBABaseCharacter* BeAttackedCharacter)
{
	float const Distance = FVector::Dist(BeAttackedCharacter->GetActorLocation(), this->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Attack To Character Succeed!"));
	if (Distance > this->GetAttackRange()) return;
	else
	{
		this->GetbIsAttacking() = true;
		this->GetbRecallSucceed() = false;
		this->GetbAbleToAttack() = false;

		auto MayBeAttackingHero = Cast<AMOBAHeroCharacter>(BeAttackedCharacter);
		if (MayBeAttackingHero)
		{
			this->GetbIsAttackingHero() = true;
		}

		ServerAttackToCharacter(BeAttackedCharacter);

		float AttackCDTime = 1.0f / this->GetAttackSpeed();
		auto MyTimeHanlde = timeHandles.AttackTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHanlde);
		GetWorldTimerManager().SetTimer(MyTimeHanlde, this, &AMOBAHeroCharacter::ResetAttackTimer, AttackCDTime);
		this->GetbIsAttacking() = false;
	}
}

void AMOBAHeroCharacter::AddQ()
{
	if (this->GetCanAddQ())
	{
		this->SkillProperty.QPoint += 1.0f;
		this->SkillProperty.SkillPoint -= 1.0f;
	}
}

void AMOBAHeroCharacter::AddW()
{
	if (this->GetCanAddW())
	{
		this->SkillProperty.WPoint += 1.0f;
		this->SkillProperty.SkillPoint -= 1.0f;
	}
}

void AMOBAHeroCharacter::AddE()
{
	if (this->GetCanAddE())
	{
		this->SkillProperty.EPoint += 1.0f;
		this->SkillProperty.SkillPoint -= 1.0f;
	}
}

void AMOBAHeroCharacter::AddR()
{
	if (this->GetCanAddE())
	{
		this->SkillProperty.RPoint += 1.0f;
		this->SkillProperty.SkillPoint -= 1.0f;
	}
}

void AMOBAHeroCharacter::ServerAttackToCharacter_Implementation(AMOBABaseCharacter* BeAttackedCharacter)
{
	auto MyAttackStrength = this->GetAttackStrength();
	//Strike
	FRandomStream MyRandomStream;
	auto MyStrikeRate = this->GetStrikeRate();
	auto MyStrikeDamage = this->GetStrikeDamage();
	MyRandomStream.GenerateNewSeed();
	auto RandomResult = MyRandomStream.GetFraction();
	if (RandomResult <= MyStrikeRate && RandomResult >= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Strike!"));
		MyAttackStrength *= MyStrikeDamage;
	}

	BeAttackedCharacter->ReceiveDamageFromCharacter(BeAttackedCharacter, DamageType::physical, MyAttackStrength, this);
}

bool AMOBAHeroCharacter::ServerAttackToCharacter_Validate(AMOBABaseCharacter* BeAttackedCharacter)
{
	return true;
}


void AMOBAHeroCharacter::resetHero()
{
	this->GetGoldValue() = 300.0f;
	this->GetCombKillNumber() = 0.0f;

	this->ChangeState(State::Dead);

	float resetTime = this->heroProperty.resetTime;
	auto MyTimeHanlde = timeHandles.ResetTimer;
	GetWorldTimerManager().ClearTimer(MyTimeHanlde);
	GetWorldTimerManager().SetTimer(MyTimeHanlde, this, &AMOBAHeroCharacter::resetHeroHandle, resetTime);

}

void AMOBAHeroCharacter::AddCombKillNumber()
{
	this->GetCombKillNumber() += 1.0f;
	if (GetCombKillNumber() <= 8.0f)
	{
		this->GetGoldValue() += 50.0f;
	}
}

void AMOBAHeroCharacter::AddExperienceToHero(float ExperienceValue)
{
	this->GetExperienceValue() += ExperienceValue;
	auto MyExperienceJudge = this->GetExperience() / 100.0f;
	auto MyLevel = this->GetLevel();
	auto MaxLevel = this->GetMaxLevel();

	if ((MyExperienceJudge > MyLevel) && (MyLevel < MaxLevel))
	{
		levelUp();
	}
}

void AMOBAHeroCharacter::ResetAttackTimer()
{
	this->GetbAbleToAttack() = true;
	this->GetbIsAttackingHero() = false;
}

void AMOBAHeroCharacter::AddCDReduction(float CD)
{
	auto& MyCD = SkillProperty.CDReduction;
	MyCD = FMath::Clamp(MyCD + CD, 0.0f, SkillProperty.MaxCDReduction);
}

void AMOBAHeroCharacter::BeginPlay()
{
	Super::BeginPlay();


	birthLocation = this->GetActorLocation();

	this->HpRecoveryHandle();
	if (this->GetBHaveMp())
	{
		this->MpRecoveryHandle();
	}

}

void AMOBAHeroCharacter::SetValue()
{
	baseProperty.hp = 500.0f;
	baseProperty.maxHp = 500.0f;
	baseProperty.mp = 300.0f;
	baseProperty.maxMp = 300.0f;
	baseProperty.attackStrength = 60.0f;
	baseProperty.attackSpeed = 0.8f;
	baseProperty.mpRecovery = 1.0f;
	baseProperty.hpRecovery = 1.0f;
	baseProperty.armor = 50.0f;
	baseProperty.magicResist = 30.0f;
	baseProperty.level = 1.0f;
	baseProperty.maxLevel = 18.0f;
	baseProperty.maxAttackSpeed = 2.5f;
	baseProperty.experience = 10.0f;

	heroProperty.lifeSteal = 0.0f;
	heroProperty.Gold = 0.0f;
	heroProperty.resetTime = 5.0f;
	heroProperty.strikeDamage = 2.0f;

	heroGrowth.armorGrowth = 3.0f;
	heroGrowth.attackGrowth = 7.0f;
	heroGrowth.attackSpeedGrowth = 0.08f;
	heroGrowth.experienceCarriedGrowth = 4.0f;
	heroGrowth.hpGrowth = 80.0f;
	heroGrowth.hpRecoveryGrowth = 0.2f;
	heroGrowth.magicResistGrowth = 2.0f;
	heroGrowth.mpGrowth = 30.0f;
	heroGrowth.mpRecoveryGrowth = 0.2f;
	heroGrowth.resetTimeGrowth = 4.0f;
	SkillProperty.CDReduction = 0.0f;
	SkillProperty.MaxCDReduction = 0.4f;

	this->ChangeState(State::Normal);

	SkillProperty.bCanReleaseSkills = true;
	heroProperty.bIsInjured = false;
	baseProperty.bCanBeAttacked = true;
	baseProperty.bCanMove = true;
	baseProperty.bAbleToAttack = true;
	baseProperty.bHaveMp = true;
}

void AMOBAHeroCharacter::resetQSkill()
{
	this->SkillProperty.bCanQ = true;
}

void AMOBAHeroCharacter::resetWSkill()
{
	this->SkillProperty.bCanW = true;
}

void AMOBAHeroCharacter::resetESkill()
{
	this->SkillProperty.bCanE = true;
}

void AMOBAHeroCharacter::resetRSkill()
{
	this->SkillProperty.bCanR = true;
}

void AMOBAHeroCharacter::resetHeroHandle()
{

	this->baseProperty.hp = this->baseProperty.maxHp;
	this->baseProperty.mp = this->baseProperty.maxMp;
	this->ChangeState(State::Dead, true);

	this->SetActorLocation(birthLocation);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

void AMOBAHeroCharacter::levelUp()
{
	auto& myPro = this->baseProperty;
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

	SkillProperty.SkillPoint += 1.0f;

}

void AMOBAHeroCharacter::reCall()
{
	GetCharacterMovement()->StopMovementImmediately();

	auto& myTimeHandle = this->timeHandles.ResetTimer;

	GetWorldTimerManager().ClearTimer(myTimeHandle);

	this->GetbRecallSucceed() = true;

	GetWorldTimerManager().SetTimer(myTimeHandle, this, &AMOBAHeroCharacter::reCallHandle, 8.0f);

}

void AMOBAHeroCharacter::reCallHandle()
{
	if (this->GetbRecallSucceed())
	{
		SetActorLocation(birthLocation);
	}
}

void AMOBAHeroCharacter::HpRecoveryHandle()
{
	auto MyTimeHanlde = timeHandles.HpRecoveryTimer;
	GetWorldTimerManager().ClearTimer(MyTimeHanlde);
	GetWorldTimerManager().SetTimer(MyTimeHanlde, this, &AMOBAHeroCharacter::HpRecoveryHandle, 1.0f);

	if (this->GetHp() != this->GetMaxHp())
	{
		GetHp() = FMath::Clamp(this->GetHp() + this->GetHpRecovery(), 0.0f, this->GetMaxHp());
	}
}

void AMOBAHeroCharacter::MpRecoveryHandle()
{

	auto MyTimeHanlde = timeHandles.MpRecoveryTimer;
	GetWorldTimerManager().ClearTimer(MyTimeHanlde);
	GetWorldTimerManager().SetTimer(MyTimeHanlde, this, &AMOBAHeroCharacter::MpRecoveryHandle, 1.0f);


	if (this->GetMp() != this->GetMaxMp())
	{
		GetMp() = FMath::Clamp(this->GetMp() + this->GetMpRecovery(), 0.0f, this->GetMaxMp());
	}
}

void AMOBAHeroCharacter::ChangeState(State TargetState, bool IsCanceling)
{
	if (!IsCanceling)
	{
		this->GetHeroState() = TargetState;
	}
	else
	{
		if (this->GetHeroState() == TargetState)
		{
			this->GetHeroState() = State::Normal;
		}
	}

	if (TargetState == State::Imprison)
	{
		this->GetbRecallSucceed() = false;
		this->GetbCanMove() = (false ^ IsCanceling);
	}
	if (TargetState == State::Silence)
	{
		this->GetbRecallSucceed() = false;
		this->GetbCanReleaseSkills() = (false ^ IsCanceling);
	}
	if (TargetState == State::Stun)
	{
		this->GetbRecallSucceed() = false;
		this->GetbAbleToAttack() = (false ^ IsCanceling);
		this->GetbCanMove() = (false ^ IsCanceling);
		this->GetbCanReleaseSkills() = (false ^ IsCanceling);
	}
	if (TargetState == State::Dead)
	{
		this->GetbRecallSucceed() = false;
		this->GetbAbleToAttack() = (false ^ IsCanceling);
		this->GetbCanMove() = (false ^ IsCanceling);
		this->GetbCanReleaseSkills() = (false ^ IsCanceling);
		this->GetbCanBeAttacked() = (false ^ IsCanceling);
	}
}

void AMOBAHeroCharacter::ExceptionState(State TargetState, float Time)
{
	ChangeState(TargetState);
	if (TargetState == State::Stun)
	{
		FTimerHandle& MyTimeHandle = timeHandles.StunTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAHeroCharacter::ResetStunState, Time);
	}
	if (TargetState == State::Silence)
	{
		FTimerHandle& MyTimeHandle = timeHandles.SilenceTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAHeroCharacter::ResetSilenceState, Time);
	}
	if (TargetState == State::Imprison)
	{
		FTimerHandle& MyTimeHandle = timeHandles.ImprisonTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAHeroCharacter::ResetImprisonState, Time);
	}

}

void AMOBAHeroCharacter::assignHeroValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, FHeroProperty aHeroProperty, FHeroGrowth aHeroGrowth) {

	assignBaseValueForAPI(aBaseProperty, aBaseValue);
	this->heroProperty = aHeroProperty;
	this->heroGrowth = aHeroGrowth;

}

