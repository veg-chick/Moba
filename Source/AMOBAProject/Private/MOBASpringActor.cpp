// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MOBASpringActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Public/MOBABaseCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMOBASpringActor::AMOBASpringActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnOverlapComp = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapConp"));
	OnOverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OnOverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OnOverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = OnOverlapComp;
	OnOverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AMOBASpringActor::OverlapHandle);
}

// Called when the game starts or when spawned
void AMOBASpringActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMOBASpringActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	nowtime += DeltaTime;
	//Detect if there is an overlapping AMOBABaseCharacter

}

void AMOBASpringActor::AssignSpringCampForAPI(Camp aCamp)
{
	springCamp = aCamp;
}

void AMOBASpringActor::FriendHandle(AMOBABaseCharacter* who)
{
	if (who)
	{
		if (who->GetHp() != 0.0f)
		{
			while (who->GetHp() < who->GetMaxHp())
			{
				ServerRPCFriendHandle(who);
			}
		}
	}
}


void AMOBASpringActor::ServerRPCFriendHandle_Implementation(AMOBABaseCharacter* who)
{
	who->ApplyDamage(who, DamageType::treat, 500.0f, this);
	PlayRedemptionEffects(who->GetActorLocation());
}

bool AMOBASpringActor::ServerRPCFriendHandle_Validate(AMOBABaseCharacter* who)
{
	return true;
}

void AMOBASpringActor::PlayRedemptionEffects_Implementation(FVector Location)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, Heal, Location);
}

void AMOBASpringActor::EnemyHandle(AMOBABaseCharacter* who)	
{
	if (who)
	{
		if (who->GetHp() != 0.0f)
		{
			while (who->GetHp() > 0.0f)
			{
				ServerRPCEnemyHandle(who);
			}
		}
	}
}


void AMOBASpringActor::ServerRPCEnemyHandle_Implementation(AMOBABaseCharacter* who)
{
	who->ApplyDamage(who, DamageType::real, 1000.0f, this);
	PlayExecutionEffects(who->GetActorLocation());
}

bool AMOBASpringActor::ServerRPCEnemyHandle_Validate(AMOBABaseCharacter* who)
{
	return true;
}

void AMOBASpringActor::PlayExecutionEffects_Implementation(FVector Location)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, Lighting, Location);
}

void AMOBASpringActor::OverlapHandle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (nowtime < 10.0f) return;

	AMOBABaseCharacter* OverlapChar = Cast<AMOBABaseCharacter>(OtherActor);
	if (OverlapChar)
	{
		if (this->GetCamp() == OverlapChar->GetCamp())
		{
			FriendHandle(OverlapChar);
		}
		else
		{
			EnemyHandle(OverlapChar);
		}
	}
}
