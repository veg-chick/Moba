// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBAHeroCharacter.h"
#include "Public/MOBAHeroADCOne.h"
#include "Public/MOBAHeroADOne.h"
#include "Public/MOBAHeroAPOne.h"
#include "Public/MOBAHeroAssassinOne.h"
#include "Public/MOBAHeroTankOne.h"
#include "Public/MOBAHeroAssistOne.h"
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
#include "Net/UnrealNetwork.h"
#include "MOBAPlayerState.h"
#include "TimerManager.h"

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

	SetReplicates(true);

}

void AMOBAHeroCharacter::Tick(float DeltaSeconds)
{
	
	Super::Tick(DeltaSeconds);

	if (HeroState == State::Dead)
	{
		FTimerManager CalDeadtime;
		heroProperty.deadtime = CalDeadtime.GetTimerRemaining(DeadTimer);
	}

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

	if (GetbCanReleaseSkills())
	{
		if ((GetQPoint() != 0.0f) && (GetMp() >= GetQCost()))
			GetbMayQ() = true;
		else GetbMayQ() = false;
		if ((GetWPoint() != 0.0f) && (GetMp() >= GetWCost()))
			GetbMayW() = true;
		else GetbMayW() = false;
		if ((GetEPoint() != 0.0f) && (GetMp() >= GetECost()))
			GetbMayE() = true;
		else GetbMayE() = false;
	}

	if (QTimerManager.IsTimerActive(TimeHandles.SkillQTimer))
	{
		SkillProperty.RemainingQCD = QTimerManager.GetTimerRemaining(TimeHandles.SkillQTimer);
	}
	if (WTimerManager.IsTimerActive(TimeHandles.SkillWTimer))
	{
		SkillProperty.RemainingWCD = WTimerManager.GetTimerRemaining(TimeHandles.SkillWTimer);
	}
	if (ETimerManager.IsTimerActive(TimeHandles.SkillETimer))
	{
		SkillProperty.RemainingECD = ETimerManager.GetTimerRemaining(TimeHandles.SkillETimer);
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
	if (Distance > this->GetAttackRange() || !this->GetbAbleToAttack()) return;
	else
	{
		ServerAttackToActor(BeAttackedActor);
	}

}

void AMOBAHeroCharacter::ServerAttackToActor_Implementation(AMOBABaseActor* BeAttackedActor)
{
	StopMove();
	this->GetbIsAttacking() = true;
	this->GetbRecallSucceed() = false;
	this->GetbAbleToAttack() = false;
	this->GetbCanMove() = false;
	this->GetbCanReleaseSkills() = false;
	FVector Direction = BeAttackedActor->GetActorLocation() - this->GetActorLocation();
	Direction.Normalize();
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewRotation.Pitch = 0.0f;
	NewRotation.Roll = 0.0f;
	SetActorRotation(NewRotation);
	float AttackCDTime = 1.0f / this->GetAttackSpeed();
	auto MyTimeHanlde = TimeHandles.AttackTimer;
	GetWorldTimerManager().ClearTimer(MyTimeHanlde);
	GetWorldTimerManager().SetTimer(MyTimeHanlde, this, &AMOBAHeroCharacter::ResetAttackTimer, AttackCDTime);

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
	if (Distance > this->GetAttackRange() || !this->GetbAbleToAttack()) return;
	else
	{
		auto MayBeAttackingHero = Cast<AMOBAHeroCharacter>(BeAttackedCharacter);
		if (MayBeAttackingHero)
		{
			this->GetbIsAttackingHero() = true;
		}

		ServerAttackToCharacter(BeAttackedCharacter);
	}
}

void AMOBAHeroCharacter::AddBuff(Buff BuffType, float Time)
{
	if (BuffType == Buff::RedBuff)
	{
		switch (HeroBuff)
		{
		case Buff::RedBuff:
		case Buff::RedAndBlue:
		case Buff::RedAndDragon:
		case Buff::BlueAndRedAndDragon:
			GetWorldTimerManager().ClearTimer(RedBuffTimer);
			break;
		case Buff::BlueBuff:
			HeroBuff = Buff::RedAndBlue;
			GetHpRecovery() += 18.0f;
			GetAttackStrength() += 30.0f;
			GetWorldTimerManager().SetTimer(RedBuffTimer, this, &AMOBAHeroCharacter::ResetRedBuff, Time);
			break;
		case Buff::DragonBuff:
			HeroBuff = Buff::RedAndDragon;
			GetHpRecovery() += 18.0f;
			GetAttackStrength() += 30.0f;
			GetWorldTimerManager().SetTimer(RedBuffTimer, this, &AMOBAHeroCharacter::ResetRedBuff, Time);
			break;
		case Buff::BlueAndDragon:
			HeroBuff = Buff::BlueAndRedAndDragon;
			GetHpRecovery() += 18.0f;
			GetAttackStrength() += 30.0f;
			GetWorldTimerManager().SetTimer(RedBuffTimer, this, &AMOBAHeroCharacter::ResetRedBuff, Time);
		default:
			break;
		}
	}
	else if (BuffType == Buff::BlueBuff)
	{
		switch (HeroBuff)
		{
		case Buff::BlueBuff:
		case Buff::RedAndBlue:
		case Buff::BlueAndDragon:
		case Buff::BlueAndRedAndDragon:
			GetWorldTimerManager().ClearTimer(BlueBuffTimer);
			break;
		case Buff::RedBuff:
			HeroBuff = Buff::RedAndBlue;
			GetMpRecovery() += 12.0f;
			GetWorldTimerManager().SetTimer(BlueBuffTimer, this, &AMOBAHeroCharacter::ResetBlueBuff, Time);
			break;
		case Buff::DragonBuff:
			HeroBuff = Buff::BlueAndDragon;
			GetMpRecovery() += 12.0f;
			GetWorldTimerManager().SetTimer(BlueBuffTimer, this, &AMOBAHeroCharacter::ResetBlueBuff, Time);
			break;
		case Buff::RedAndDragon:
			HeroBuff = Buff::BlueAndRedAndDragon;
			GetMpRecovery() += 12.0f;
			GetWorldTimerManager().SetTimer(BlueBuffTimer, this, &AMOBAHeroCharacter::ResetBlueBuff, Time);
		default:
			break;
		}
	}
	else if (BuffType == Buff::DragonBuff)
	{
		switch (HeroBuff)
		{
		case Buff::DragonBuff:
		case Buff::RedAndDragon:
		case Buff::BlueAndDragon:
		case Buff::BlueAndRedAndDragon:
			GetWorldTimerManager().ClearTimer(DragonBuffTimer);
			break;
		case Buff::RedBuff:
			HeroBuff = Buff::RedAndDragon;
			GetAttackStrength() += 80.0f;
			GetPowerStrength() += 80.0f;
			GetWorldTimerManager().SetTimer(DragonBuffTimer, this, &AMOBAHeroCharacter::ResetDragonBuff, Time);
			break;
		case Buff::BlueBuff:
			HeroBuff = Buff::BlueAndDragon;
			GetAttackStrength() += 80.0f;
			GetPowerStrength() += 80.0f;
			GetWorldTimerManager().SetTimer(DragonBuffTimer, this, &AMOBAHeroCharacter::ResetDragonBuff, Time);
			break;
		case Buff::RedAndBlue:
			HeroBuff = Buff::BlueAndRedAndDragon;
			GetAttackStrength() += 80.0f;
			GetPowerStrength() += 80.0f;
			GetWorldTimerManager().SetTimer(DragonBuffTimer, this, &AMOBAHeroCharacter::ResetDragonBuff, Time);
		default:
			break;
		}
	}
}

void AMOBAHeroCharacter::ServerAttackToCharacter_Implementation(AMOBABaseCharacter* BeAttackedCharacter)
{
	StopMove();
	this->GetbIsAttacking() = true;
	this->GetbRecallSucceed() = false;
	this->GetbAbleToAttack() = false;
	this->GetbCanMove() = false;
	this->GetbCanReleaseSkills() = false;
	FVector Direction = BeAttackedCharacter->GetActorLocation() - this->GetActorLocation();
	Direction.Normalize();
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewRotation.Pitch = 0.0f;
	NewRotation.Roll = 0.0f;
	SetActorRotation(NewRotation);
	float AttackCDTime = 1.0f / this->GetAttackSpeed();
	auto MyTimeHanlde = TimeHandles.AttackTimer;
	GetWorldTimerManager().ClearTimer(MyTimeHanlde);
	GetWorldTimerManager().SetTimer(MyTimeHanlde, this, &AMOBAHeroCharacter::ResetAttackTimer, AttackCDTime);

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

void AMOBAHeroCharacter::AddQ()
{
	if (this->GetCanAddQ())
	{
		this->SkillProperty.QPoint += 1.0f;
		this->SkillProperty.SkillPoint -= 1.0f;

		if (auto MyHero = Cast<AMOBAHeroADCOne>(this))
		{
			GetQCost() = GetQPoint() * 10.0f + 50.0f;
			GetCDofQ() = 10.5f - GetQPoint() * 0.5f;

		}
		else if (auto MyHero = Cast<AMOBAHeroADOne>(this))
		{
			GetQCost() = GetQPoint() * 10.0f + 30.0f;
			GetCDofQ() = 15.5f - GetQPoint() * 0.5f;

		}
		else if (auto MyHero = Cast<AMOBAHeroAPOne>(this))
		{
			GetQCost() = GetQPoint() * 5.0f + 10.0f;
			GetCDofQ() = 3.5f;

		}
		else if (auto MyHero = Cast<AMOBAHeroAssassinOne>(this))
		{
			GetQCost() = GetQPoint() * 20.0f + 10.0f;
			GetCDofQ() = 7.0f;
		}
		else if (auto MyHero = Cast<AMOBAHeroAssistOne>(this))
		{
			GetQCost() = GetQPoint() * 30.0f + 50.0f;
			GetCDofQ() = 21.5f - this->GetQPoint() * 0.5f;
		}
		else if (auto MyHero = Cast<AMOBAHeroTankOne>(this))
		{
			GetCDofQ() = 12.0f - this->GetQPoint();
		}
	}
}

void AMOBAHeroCharacter::AddW()
{
	if (this->GetCanAddW())
	{
		this->SkillProperty.WPoint += 1.0f;
		this->SkillProperty.SkillPoint -= 1.0f;
	}

	if (auto MyHero = Cast<AMOBAHeroADCOne>(this))
	{
		GetWCost() = GetWPoint() * 20.0f + 70.0f;
		GetCDofW() = 18.0f - GetWPoint() * 2.0f;

	}
	else if (auto MyHero = Cast<AMOBAHeroADOne>(this))
	{
		GetWCost() = GetWPoint() * 10.0f + 70.0f;
		GetCDofW() = 18.5f - GetWPoint() * 1.5f;
	}
	else if (auto MyHero = Cast<AMOBAHeroAPOne>(this))
	{
		GetWCost() = GetWPoint() * 10.0f + 70.0f;
		GetCDofW() = 100.0f - GetWPoint() * 5.0f;
	}
	else if (auto MyHero = Cast<AMOBAHeroAssassinOne>(this))
	{
		GetWCost() = GetWPoint() * 10.0f + 50.0f;
		GetCDofW() = 21.0f - GetWPoint();
	}
	else if (auto MyHero = Cast<AMOBAHeroAssistOne>(this))
	{
		GetWCost() = 110.0f - GetWPoint() * 10.0f;
		GetCDofW() = 18.5f - this->GetWPoint() * 1.5f;
	}
	else if (auto MyHero = Cast<AMOBAHeroTankOne>(this))
	{
		GetCDofW() = 21.0f - this->GetWPoint();
	}
}

void AMOBAHeroCharacter::AddE()
{
	if (this->GetCanAddE())
	{
		this->SkillProperty.EPoint += 1.0f;
		this->SkillProperty.SkillPoint -= 1.0f;
	}

	if (auto MyHero = Cast<AMOBAHeroADCOne>(this))
	{
		GetECost() = GetWPoint() * 10.0f + 90.0f;
		GetCDofE() = 90.0f - (this->GetEPoint() - 1.0f) * 15.0f;

	}
	else if (auto MyHero = Cast<AMOBAHeroADOne>(this))
	{
		GetECost() = GetEPoint() * 20.0f + 150.0f;
		GetCDofE() = 200.0f - this->GetEPoint() * 20.0f;

	}
	else if (auto MyHero = Cast<AMOBAHeroAPOne>(this))
	{
		GetECost() = GetEPoint() * 10.0f + 120.0f;
		GetCDofE() = 130.0f - GetEPoint() * 10.0f;

	}
	else if (auto MyHero = Cast<AMOBAHeroAssassinOne>(this))
	{
		GetECost() = GetEPoint() * 10.0f + 70.0f;
		GetCDofE() = 10.0f;

	}
	else if (auto MyHero = Cast<AMOBAHeroAssistOne>(this))
	{
		GetECost() = GetWPoint() * 10.0f + 70.0f;
		GetCDofE() = 21.5f - this->GetEPoint() * 1.5f;
	}
	else if (auto MyHero = Cast<AMOBAHeroTankOne>(this))
	{
		GetCDofE() = 130.0f - this->GetEPoint() * 10.0f;
	}
}

void AMOBAHeroCharacter::resetHero()
{
	AMOBAPlayerState* GS = Cast<AMOBAPlayerState>(this->GetPlayerState());
	if (GS)
	{
		GS->ClearCombKillNumber();
		GS->AddDeathNumber();
	}

	GetWorldTimerManager().ClearTimer(DeadTimer);
	GetWorldTimerManager().SetTimer(DeadTimer, this, &AMOBAHeroCharacter::DeadHeroHandle, 3.0f);


	this->ServerRPCChangeState(State::Dead);

	float resetTime = this->heroProperty.resetTime;
	auto MyTimeHanlde = TimeHandles.ResetTimer;
	GetWorldTimerManager().ClearTimer(MyTimeHanlde);
	GetWorldTimerManager().SetTimer(MyTimeHanlde, this, &AMOBAHeroCharacter::ResetHeroHandle, resetTime);

}


void AMOBAHeroCharacter::AddExperienceToHero(float ExperienceValue)
{
	this->GetExperience() += ExperienceValue;
	auto MyExperienceJudge = this->GetExperience() / 100.0f;
	auto MyLevel = this->GetLevel();
	auto MaxLevel = this->GetMaxLevel();

	if ((MyExperienceJudge >= MyLevel) && (MyLevel < MaxLevel))
	{
		levelUp();
	}
}

void AMOBAHeroCharacter::ResetAttackTimer()
{
	this->GetbAbleToAttack() = true;
	this->GetbIsAttackingHero() = false;
	this->GetbIsAttacking() = false;
	this->GetbCanMove() = true;
	this->GetbCanReleaseSkills() = true;
}

void AMOBAHeroCharacter::AddCDReduction(float CD)
{
	auto& MyCD = SkillProperty.CDReduction;
	MyCD = FMath::Clamp(MyCD + CD, 0.0f, SkillProperty.MaxCDReduction);
}

void AMOBAHeroCharacter::ChangeReleasingSkill(float Target)
{
	if (Target == 1.0f)
	{
		StopMove();
		SetbAbleToAttack(false);
		SetbCanMove(false);
		GetbIsReleasingQ() = true;
		FTimerHandle MyTImer;
		GetWorldTimerManager().ClearTimer(MyTImer);
		GetWorldTimerManager().SetTimer(MyTImer, this, &AMOBAHeroCharacter::ResetReleasingQ, 1.0f);
	}
	if (Target == 2.0f)
	{
		StopMove();
		SetbAbleToAttack(false);
		SetbCanMove(false);
		GetbIsReleasingW() = true;
		FTimerHandle MyTImer;
		GetWorldTimerManager().ClearTimer(MyTImer);
		GetWorldTimerManager().SetTimer(MyTImer, this, &AMOBAHeroCharacter::ResetReleasingW, 1.0f);
	}
	if (Target == 3.0f)
	{
		StopMove();
		SetbAbleToAttack(false);
		SetbCanMove(false);
		GetbIsReleasingE() = true;
		FTimerHandle MyTImer;
		GetWorldTimerManager().ClearTimer(MyTImer);
		GetWorldTimerManager().SetTimer(MyTImer, this, &AMOBAHeroCharacter::ResetReleasingE, 1.0f);
	}


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

	baseValue.experienceValue = 10.0f;
	baseValue.goldValue = 300.0f;

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

	this->ServerRPCChangeState(State::Normal);

	SkillProperty.bCanReleaseSkills = true;
	heroProperty.bIsInjured = false;
	baseProperty.bCanBeAttacked = true;
	baseProperty.bCanMove = true;
	baseProperty.bAbleToAttack = true;
	baseProperty.bHaveMp = true;
}

void AMOBAHeroCharacter::ResetQSkill()
{
	this->SkillProperty.bCanQ = true;
}

void AMOBAHeroCharacter::ResetWSkill()
{
	this->SkillProperty.bCanW = true;
}

void AMOBAHeroCharacter::ResetESkill()
{
	this->SkillProperty.bCanE = true;
}

void AMOBAHeroCharacter::ResetHeroHandle()
{

	this->baseProperty.hp = this->baseProperty.maxHp;
	this->baseProperty.mp = this->baseProperty.maxMp;
	this->ServerRPCChangeState(State::Dead, true);
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
	heroPro.FakeAttackSpeed += myGro.attackSpeedGrowth;

	myPro.armor += myGro.armorGrowth;
	myPro.magicResist += myGro.magicResistGrowth;

	heroPro.resetTime += myGro.resetTimeGrowth;

	if (myPro.level <= 13.0f)
		SkillProperty.SkillPoint += 1.0f;
	myPro.level += 1.0f;
}

void AMOBAHeroCharacter::Recall()
{
	ServerRPCRecall();
}

void AMOBAHeroCharacter::ServerRPCRecall_Implementation()
{
	GetCharacterMovement()->StopMovementImmediately();

	auto& myTimeHandle = this->TimeHandles.ResetTimer;

	GetWorldTimerManager().ClearTimer(myTimeHandle);

	this->GetbRecallSucceed() = true;

	GetWorldTimerManager().SetTimer(myTimeHandle, this, &AMOBAHeroCharacter::RecallHandle, 8.0f);
}

bool AMOBAHeroCharacter::ServerRPCRecall_Validate()
{
	return true;
}

void AMOBAHeroCharacter::RecallHandle()
{
	if (this->GetbRecallSucceed())
	{
		SetActorLocation(birthLocation);
	}
}

void AMOBAHeroCharacter::HpRecoveryHandle()
{
	auto MyTimeHanlde = TimeHandles.HpRecoveryTimer;
	GetWorldTimerManager().ClearTimer(MyTimeHanlde);
	GetWorldTimerManager().SetTimer(MyTimeHanlde, this, &AMOBAHeroCharacter::HpRecoveryHandle, 1.0f);

	ServerRPCHpRecovery();
}

void AMOBAHeroCharacter::ServerRPCHpRecovery_Implementation()
{
	if (this->GetHp() != this->GetMaxHp() && this->GetHp() > 0.0f)
	{
		GetHp() = FMath::Clamp(this->GetHp() + this->GetHpRecovery(), 0.0f, this->GetMaxHp());
	}

	this->GetGold() += 1.0f;
}

bool AMOBAHeroCharacter::ServerRPCHpRecovery_Validate()
{
	return true;
}

void AMOBAHeroCharacter::MpRecoveryHandle()
{
	auto MyTimeHanlde = TimeHandles.MpRecoveryTimer;
	GetWorldTimerManager().ClearTimer(MyTimeHanlde);
	GetWorldTimerManager().SetTimer(MyTimeHanlde, this, &AMOBAHeroCharacter::MpRecoveryHandle, 1.0f);

	ServerRPCMpRecovery();
}

void AMOBAHeroCharacter::ServerRPCChangeState_Implementation(State TargetState, bool IsCanceling /*= false*/)
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

bool AMOBAHeroCharacter::ServerRPCChangeState_Validate(State TargetState, bool IsCanceling /*= false*/)
{
	return true;
}

void AMOBAHeroCharacter::ServerRPCMpRecovery_Implementation()
{
	if (this->GetMp() != this->GetMaxMp() && this->GetMp() > 0.0f)
	{
		GetMp() = FMath::Clamp(this->GetMp() + this->GetMpRecovery(), 0.0f, this->GetMaxMp());
	}
}

bool AMOBAHeroCharacter::ServerRPCMpRecovery_Validate()
{
	return true;
}


void AMOBAHeroCharacter::ExceptionState(State TargetState, float Time)
{
	ServerRPCChangeState(TargetState);
	if (TargetState == State::Stun)
	{
		FTimerHandle& MyTimeHandle = TimeHandles.StunTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAHeroCharacter::ResetStunState, Time);
	}
	if (TargetState == State::Silence)
	{
		FTimerHandle& MyTimeHandle = TimeHandles.SilenceTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAHeroCharacter::ResetSilenceState, Time);
	}
	if (TargetState == State::Imprison)
	{
		FTimerHandle& MyTimeHandle = TimeHandles.ImprisonTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAHeroCharacter::ResetImprisonState, Time);
	}

}

void AMOBAHeroCharacter::HeroReleaseQ(AMOBAHeroCharacter* Target)
{
	if (auto MyHero = Cast<AMOBAHeroADCOne>(this))
		MyHero->ReleaseQ(Target, MyHero->GetQCost());
	else if (auto MyHero = Cast<AMOBAHeroADOne>(this))
		MyHero->ReleaseQ(Target, MyHero->GetQCost());
	else if (auto MyHero = Cast<AMOBAHeroAPOne>(this))
		MyHero->ReleaseQ(Target, MyHero->GetQCost());
	else if (auto MyHero = Cast<AMOBAHeroAssassinOne>(this))
		MyHero->ReleaseQ(Target, MyHero->GetQCost());
	else if (auto MyHero = Cast<AMOBAHeroAssistOne>(this))
		MyHero->ReleaseQ(Target, MyHero->GetQCost());
	else if (auto MyHero = Cast<AMOBAHeroTankOne>(this))
		MyHero->ReleaseQ(Target, MyHero->GetQCost());

}

void AMOBAHeroCharacter::HeroReleaseW(AMOBAHeroCharacter* Target)
{
	if (auto MyHero = Cast<AMOBAHeroADCOne>(this))
		MyHero->ReleaseW(MyHero->GetWCost());
	else if (auto MyHero = Cast<AMOBAHeroADOne>(this))
		MyHero->ReleaseW(MyHero->GetWCost());
	else if (auto MyHero = Cast<AMOBAHeroAPOne>(this))
		MyHero->ReleaseW(MyHero->GetWCost());
	else if (auto MyHero = Cast<AMOBAHeroAssassinOne>(this))
		MyHero->ReleaseW(MyHero->GetWCost());
	else if (auto MyHero = Cast<AMOBAHeroAssistOne>(this))
		MyHero->ReleaseW(Target, MyHero->GetWCost());
	else if (auto MyHero = Cast<AMOBAHeroTankOne>(this))
		MyHero->ReleaseW(MyHero->GetWCost());
}

void AMOBAHeroCharacter::HeroReleaseE(AMOBAHeroCharacter* Target)
{
	if (auto MyHero = Cast<AMOBAHeroADCOne>(this))
		MyHero->ReleaseE(MyHero->GetECost());
	else if (auto MyHero = Cast<AMOBAHeroADOne>(this))
		MyHero->ReleaseE(MyHero->GetECost());
	else if (auto MyHero = Cast<AMOBAHeroAPOne>(this))
		MyHero->ReleaseE(Target,MyHero->GetECost());
	else if (auto MyHero = Cast<AMOBAHeroAssassinOne>(this))
		MyHero->ReleaseE(Target,MyHero->GetECost());
	else if (auto MyHero = Cast<AMOBAHeroAssistOne>(this))
		MyHero->ReleaseE(Target, MyHero->GetECost());
	else if (auto MyHero = Cast<AMOBAHeroTankOne>(this))
		MyHero->ReleaseE(MyHero->GetECost());
}

void AMOBAHeroCharacter::ResetSkills(float Target)
{
	float MyCDTime;
	if (Target == 1.0f)
	{
		this->SkillProperty.bCanQ = false;
		MyCDTime = SkillProperty.CDofQ * SkillProperty.CDReduction;
		FTimerHandle& MyTimeHandle = TimeHandles.SkillQTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAHeroCharacter::ResetQSkill, MyCDTime);
	}
	if (Target == 2.0f)
	{
		this->SkillProperty.bCanW = false;
		MyCDTime = SkillProperty.CDofW * SkillProperty.CDReduction;
		FTimerHandle& MyTimeHandle = TimeHandles.SkillWTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAHeroCharacter::ResetWSkill, MyCDTime);
	}
	if (Target == 3.0f)
	{
		this->SkillProperty.bCanE = false;
		MyCDTime = SkillProperty.CDofE * SkillProperty.CDReduction;
		FTimerHandle& MyTimeHandle = TimeHandles.SkillETimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAHeroCharacter::ResetESkill, MyCDTime);
	}
}

void AMOBAHeroCharacter::BuyEquipment(Equip BuyingEquip)
{
	ServerRPCBuyEquipment(BuyingEquip);
}

void AMOBAHeroCharacter::ServerRPCBuyEquipment_Implementation(Equip BuyingEquip)
{
	Equip* MyEquip = nullptr;
	if (HeroPack.PackOne == Equip::NullEquip)
		MyEquip = &(HeroPack.PackOne);
	else if (HeroPack.PackTwo == Equip::NullEquip)
		MyEquip = &(HeroPack.PackTwo);
	else if (HeroPack.PackThree == Equip::NullEquip)
		MyEquip = &(HeroPack.PackThree);
	else if (HeroPack.PackFour == Equip::NullEquip)
		MyEquip = &(HeroPack.PackFour);
	else if (HeroPack.PackFive == Equip::NullEquip)
		MyEquip = &(HeroPack.PackFive);
	else if (HeroPack.PackSix == Equip::NullEquip)
		MyEquip = &(HeroPack.PackSix);
	else return;

	if (MyEquip)
	{
		if (BuyingEquip == Equip::Sword)
		{
			if (GetGold() >= 300.0f)
			{
				GetGold() -= 300.0f;
				GetAttackStrength() += 15.0f;
				*MyEquip = Equip::Sword;
			}
			else return;
		}
		if (BuyingEquip == Equip::Dagger)
		{
			if (GetGold() >= 300.0f)
			{
				GetGold() -= 300.0f;
				GetFakeAttackSpeed() += 0.2f;
				GetAttackSpeed() = FMath::Clamp(GetAttackSpeed() + 0.2f, 0.0f, GetMaxAttackSpeed());
				*MyEquip = Equip::Dagger;
			}
			else return;
		}
		if (BuyingEquip == Equip::Pickaxe)
		{
			if (GetGold() >= 800.0f)
			{
				GetGold() -= 800.0f;
				GetAttackStrength() += 30.0f;
				*MyEquip = Equip::Pickaxe;
			}
			else return;
		}
		if (BuyingEquip == Equip::BigSword)
		{
			if (GetGold() >= 1500.0f)
			{
				GetGold() -= 1500.0f;
				GetAttackStrength() += 60.0f;
				*MyEquip = Equip::BigSword;
			}
			else return;
		}
		if (BuyingEquip == Equip::Cloth)
		{
			if (GetGold() >= 300.0f)
			{
				GetGold() -= 300.0f;
				GetArmor() += 15.0f;
				*MyEquip = Equip::Cloth;
			}
			else return;
		}
		if (BuyingEquip == Equip::Cloak)
		{
			if (GetGold() >= 400.0f)
			{
				GetGold() -= 400.0f;
				GetMagicResist() += 15.0f;
				*MyEquip = Equip::Cloak;
			}
			else return;
		}
		if (BuyingEquip == Equip::Shield)
		{
			if (GetGold() >= 700.0f)
			{
				GetGold() -= 700.0f;
				GetMagicResist() += 20.0f;
				GetArmor() += 20.0f;
				GetMaxHp() += 200.0f;
				GetHp() = FMath::Clamp(GetHp() + 200.0f, 0.0f, GetMaxHp());
				*MyEquip = Equip::Shield;
			}
			else return;
		}
		if (BuyingEquip == Equip::Armor)
		{
			if (GetGold() >= 1500.0f)
			{
				GetGold() -= 1500.0f;
				GetMagicResist() += 50.0f;
				GetArmor() += 50.0f;
				GetMaxHp() += 400.0f;
				GetHp() = FMath::Clamp(GetHp() + 400.0f, 0.0f, GetMaxHp());
				*MyEquip = Equip::Armor;
			}
			else return;
		}
		if (BuyingEquip == Equip::MagicBook)
		{
			if (GetGold() >= 500.0f)
			{
				GetGold() -= 500.0f;
				GetPowerStrength() += 20.0f;
				*MyEquip = Equip::MagicBook;
			}
			else return;
		}
		if (BuyingEquip == Equip::Wand)
		{
			if (GetGold() >= 900.0f)
			{
				GetGold() -= 900.0f;
				GetPowerStrength() += 50.0f;
				*MyEquip = Equip::Wand;
			}
			else return;
		}
		if (BuyingEquip == Equip::Boxer)
		{
			if (GetGold() >= 400.0f)
			{
				GetGold() -= 400.0f;
				GetStrikeRate() += 0.15f;
				*MyEquip = Equip::Boxer;
			}
			else return;
		}
		if (BuyingEquip == Equip::StrikeCloak)
		{
			if (GetGold() >= 800.0f)
			{
				GetGold() -= 800.0f;
				GetStrikeRate() += 0.25f;
				*MyEquip = Equip::StrikeCloak;
			}
			else return;
		}

	}
}

bool AMOBAHeroCharacter::ServerRPCBuyEquipment_Validate(Equip BuyingEquip)
{
	return true;
}

void AMOBAHeroCharacter::assignHeroValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, FHeroProperty aHeroProperty, FHeroGrowth aHeroGrowth) {

	assignBaseValueForAPI(aBaseProperty, aBaseValue);
	this->heroProperty = aHeroProperty;
	this->heroGrowth = aHeroGrowth;

}

void AMOBAHeroCharacter::SellEquipment(float PackageNumber)
{
	ServerRPCSellEquipment(PackageNumber);
}

void AMOBAHeroCharacter::ResetRedBuff()
{
	GetHpRecovery() -= 18.0f;
	GetAttackStrength() -= 30.0f;
	switch (HeroBuff)
	{
	case Buff::RedBuff:
		HeroBuff = Buff::NullBuff;
		break;
	case Buff::RedAndBlue:
		HeroBuff = Buff::BlueBuff;
		break;
	case Buff::RedAndDragon:
		HeroBuff = Buff::DragonBuff;
		break;
	case Buff::BlueAndRedAndDragon:
		HeroBuff = Buff::BlueAndDragon;
		break;
	default:
		GetHpRecovery() += 18.0f;
		GetAttackStrength() += 30.0f;
		break;
	}
}

void AMOBAHeroCharacter::ResetBlueBuff()
{
	GetMpRecovery() -= 12.0f;
	switch (HeroBuff)
	{
	case Buff::BlueBuff:
		HeroBuff = Buff::NullBuff;
		break;
	case Buff::RedAndBlue:
		HeroBuff = Buff::RedBuff;
		break;
	case Buff::BlueAndDragon:
		HeroBuff = Buff::DragonBuff;
		break;
	case Buff::BlueAndRedAndDragon:
		HeroBuff = Buff::RedAndDragon;
		break;
	default:
		GetMpRecovery() += 12.0f;
		break;
	}
}

void AMOBAHeroCharacter::ResetDragonBuff()
{
	GetAttackStrength() -= 80.0f;
	GetPowerStrength() -= 80.0f;
	switch (HeroBuff)
	{
	case Buff::DragonBuff:
		HeroBuff = Buff::NullBuff;
		break;
	case Buff::RedAndDragon:
		HeroBuff = Buff::RedBuff;
		break;
	case Buff::BlueAndDragon:
		HeroBuff = Buff::BlueBuff;
		break;
	case Buff::BlueAndRedAndDragon:
		HeroBuff = Buff::RedAndBlue;
		break;
	default:
		GetAttackStrength() += 80.0f;
		GetPowerStrength() += 80.0f;
		break;
	}
}

void AMOBAHeroCharacter::ServerRPCSellEquipment_Implementation(float PackageNumber)
{
	Equip* MyEquip = nullptr;
	switch ((int)PackageNumber)
	{
	case 1:
		MyEquip = &(HeroPack.PackOne);
		break;
	case 2:
		MyEquip = &(HeroPack.PackTwo);
		break;
	case 3:
		MyEquip = &(HeroPack.PackThree);
		break;
	case 4:
		MyEquip = &(HeroPack.PackFour);
		break;
	case 5:
		MyEquip = &(HeroPack.PackFive);
		break;
	case 6:
		MyEquip = &(HeroPack.PackSix);
		break;
	default:
		return;
	}

	if (*MyEquip == Equip::NullEquip)
		return;
	else
	{
		if (*MyEquip == Equip::Sword)
		{
			GetGold() += 300.0f * 0.6f;
			GetAttackStrength() -= 15.0f;
		}
		if (*MyEquip == Equip::Dagger)
		{
			GetGold() += 300.0f * 0.6f;
			GetFakeAttackSpeed() -= 0.2f;
			GetAttackSpeed() = FMath::Clamp(GetFakeAttackSpeed(), 0.0f, GetMaxAttackSpeed());
		}
		if (*MyEquip == Equip::Pickaxe)
		{
			GetGold() += 800.0f * 0.6f;
			GetAttackStrength() -= 30.0f;
		}
		if (*MyEquip == Equip::BigSword)
		{
			GetGold() += 1500.0f * 0.6f;
			GetAttackStrength() -= 60.0f;

		}
		if (*MyEquip == Equip::Cloth)
		{

			GetGold() += 300.0f * 0.6f;
			GetArmor() -= 15.0f;

		}
		if (*MyEquip == Equip::Cloak)
		{

			GetGold() += 400.0f * 0.6f;
			GetMagicResist() -= 15.0f;

		}
		if (*MyEquip == Equip::Shield)
		{

			GetGold() += 700.0f * 0.6f;
			GetMagicResist() -= 20.0f;
			GetArmor() -= 20.0f;
			GetMaxHp() -= 200.0f;
			GetHp() = FMath::Clamp(GetHp(), 0.0f, GetMaxHp());

		}
		if (*MyEquip == Equip::Armor)
		{

			GetGold() += 1500.0f * 0.6f;
			GetMagicResist() -= 50.0f;
			GetArmor() -= 50.0f;
			GetMaxHp() -= 400.0f;
			GetHp() = FMath::Clamp(GetHp(), 0.0f, GetMaxHp());
		}
		if (*MyEquip == Equip::MagicBook)
		{
			GetGold() += 500.0f * 0.6f;
			GetPowerStrength() -= 20.0f;
		}
		if (*MyEquip == Equip::Wand)
		{
			GetGold() += 900.0f * 0.6f;
			GetPowerStrength() -= 50.0f;
		}
		if (*MyEquip == Equip::Boxer)
		{
			GetGold() += 400.0f * 0.6f;
			GetStrikeRate() -= 0.15f;
		}
		if (*MyEquip == Equip::StrikeCloak)
		{
			GetGold() += 800.0f * 0.6f;
			GetStrikeRate() -= 0.25f;
		}

		*MyEquip = Equip::NullEquip;
	}
}

bool AMOBAHeroCharacter::ServerRPCSellEquipment_Validate(float PackageNumber)
{
	return true;
}



void AMOBAHeroCharacter::StopMove()
{
	ServerRPCStopMove();
}

void AMOBAHeroCharacter::ServerRPCStopMove_Implementation()
{
	GetMovementComponent()->StopMovementImmediately();
}

bool AMOBAHeroCharacter::ServerRPCStopMove_Validate()
{
	return true;
}

void AMOBAHeroCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AMOBAHeroCharacter, heroProperty, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AMOBAHeroCharacter, TimeHandles, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AMOBAHeroCharacter, birthLocation, COND_OwnerOnly);
	DOREPLIFETIME(AMOBAHeroCharacter, HeroPack);
	DOREPLIFETIME(AMOBAHeroCharacter, HeroState);
	DOREPLIFETIME(AMOBAHeroCharacter, heroGrowth);
}
