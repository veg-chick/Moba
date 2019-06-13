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
#include "Net/UnrealNetwork.h"

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
	this->GetbIsAttacking() = true;
	this->GetbRecallSucceed() = false;
	this->GetbAbleToAttack() = false;
	FVector Direction = BeAttackedActor->GetActorLocation() - this->GetActorLocation();
	Direction.Normalize();
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewRotation.Pitch = 0.0f;
	NewRotation.Roll = 0.0f;
	SetActorRotation(NewRotation);
	float AttackCDTime = 1.0f / this->GetAttackSpeed();
	auto MyTimeHanlde = timeHandles.AttackTimer;
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

void AMOBAHeroCharacter::ServerAttackToCharacter_Implementation(AMOBABaseCharacter* BeAttackedCharacter)
{
	this->GetbIsAttacking() = true;
	this->GetbRecallSucceed() = false;
	this->GetbAbleToAttack() = false;
	FVector Direction = BeAttackedCharacter->GetActorLocation() - this->GetActorLocation();
	Direction.Normalize();
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewRotation.Pitch = 0.0f;
	NewRotation.Roll = 0.0f;
	SetActorRotation(NewRotation);
	float AttackCDTime = 1.0f / this->GetAttackSpeed();
	auto MyTimeHanlde = timeHandles.AttackTimer;
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

void AMOBAHeroCharacter::resetHero()
{
	this->GetGoldValue() = 300.0f;
	this->GetCombKillNumber() = 0.0f;

	auto DeadTimer = timeHandles.DeadTimer;
	GetWorldTimerManager().ClearTimer(DeadTimer);
	GetWorldTimerManager().SetTimer(DeadTimer, this, &AMOBAHeroCharacter::DeadHeroHandle, 3.0f);


	this->ChangeState(State::Dead);

	float resetTime = this->heroProperty.resetTime;
	auto MyTimeHanlde = timeHandles.ResetTimer;
	GetWorldTimerManager().ClearTimer(MyTimeHanlde);
	GetWorldTimerManager().SetTimer(MyTimeHanlde, this, &AMOBAHeroCharacter::ResetHeroHandle, resetTime);

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
	this->GetExperience() += ExperienceValue;
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
	this->GetbIsAttacking() = false;
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
		GetbIsReleasingQ() = true;
		FTimerHandle MyTImer;
		GetWorldTimerManager().ClearTimer(MyTImer);
		GetWorldTimerManager().SetTimer(MyTImer, this, &AMOBAHeroCharacter::ResetReleasingQ, 1.0f);
	}
	if (Target == 2.0f)
	{
		GetbIsReleasingQ() = true;
		FTimerHandle MyTImer;
		GetWorldTimerManager().ClearTimer(MyTImer);
		GetWorldTimerManager().SetTimer(MyTImer, this, &AMOBAHeroCharacter::ResetReleasingW, 1.0f);
	}
	if (Target == 3.0f)
	{
		GetbIsReleasingQ() = true;
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

	this->ChangeState(State::Normal);

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
	this->ChangeState(State::Dead, true);
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

	if(myPro.level<=13.0f)
	SkillProperty.SkillPoint += 1.0f;
	myPro.level += 1.0f;
}

void AMOBAHeroCharacter::Recall()
{
	GetCharacterMovement()->StopMovementImmediately();

	auto& myTimeHandle = this->timeHandles.ResetTimer;

	GetWorldTimerManager().ClearTimer(myTimeHandle);

	this->GetbRecallSucceed() = true;

	GetWorldTimerManager().SetTimer(myTimeHandle, this, &AMOBAHeroCharacter::RecallHandle, 8.0f);

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
	auto MyTimeHanlde = timeHandles.HpRecoveryTimer;
	GetWorldTimerManager().ClearTimer(MyTimeHanlde);
	GetWorldTimerManager().SetTimer(MyTimeHanlde, this, &AMOBAHeroCharacter::HpRecoveryHandle, 1.0f);

	if (this->GetHp() != this->GetMaxHp() && this->GetHp() > 0.0f)
	{
		GetHp() = FMath::Clamp(this->GetHp() + this->GetHpRecovery(), 0.0f, this->GetMaxHp());
	}

	this->GetGold() += 1.0f;
}

void AMOBAHeroCharacter::MpRecoveryHandle()
{

	auto MyTimeHanlde = timeHandles.MpRecoveryTimer;
	GetWorldTimerManager().ClearTimer(MyTimeHanlde);
	GetWorldTimerManager().SetTimer(MyTimeHanlde, this, &AMOBAHeroCharacter::MpRecoveryHandle, 1.0f);


	if (this->GetMp() != this->GetMaxMp() && this->GetMp() > 0.0f)
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

void AMOBAHeroCharacter::ResetSkills(float Target)
{
	float MyCDTime;
	if(Target==1.0f)
	{
		MyCDTime = SkillProperty.CDofQ * SkillProperty.CDReduction;
		FTimerHandle& MyTimeHandle = timeHandles.SkillQTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAHeroCharacter::ResetQSkill, MyCDTime);
	}
	if (Target == 2.0f)
	{
		MyCDTime = SkillProperty.CDofW * SkillProperty.CDReduction;
		FTimerHandle& MyTimeHandle = timeHandles.SkillWTimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAHeroCharacter::ResetWSkill, MyCDTime);
	}
	if (Target == 3.0f)
	{
		MyCDTime = SkillProperty.CDofE * SkillProperty.CDReduction;
		FTimerHandle& MyTimeHandle = timeHandles.SkillETimer;
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
		GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AMOBAHeroCharacter::ResetESkill, MyCDTime);
	}
}

void AMOBAHeroCharacter::BuyEquipment(Equip BuyingEquip)
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

void AMOBAHeroCharacter::assignHeroValueForAPI(FBaseActorProperty aBaseProperty, FBaseActorValue aBaseValue, FHeroProperty aHeroProperty, FHeroGrowth aHeroGrowth) {

	assignBaseValueForAPI(aBaseProperty, aBaseValue);
	this->heroProperty = aHeroProperty;
	this->heroGrowth = aHeroGrowth;

}

void AMOBAHeroCharacter::SellEquipment(float PackageNumber)
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

void AMOBAHeroCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(AMOBAHeroCharacter, heroProperty);
	DOREPLIFETIME_CONDITION(AMOBAHeroCharacter, heroProperty, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AMOBAHeroCharacter, timeHandles, COND_OwnerOnly);
}
