// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MOBABaseActor.generated.h"

//阵营
enum Camp { blue, red, other };

//基础属性
struct BaseProperty {
	//所属阵营
	Camp baseCamp;

	//血，恢复速率
	float hp;
	float maxHp;
	float hpRecovery;

	//是否有蓝条，蓝，恢复速率
	bool bHaveMp;
	float mp;
	float maxMp;
	float mpRecovery;

	//护甲魔抗
	int armor;
	int magicResist;

	//移动速度
	int moveSpeed;

	//能否攻击，是否远程，攻击距离
	bool bAbleToAttack;
	bool bIsRemote;
	int attackRange;

	//攻击力，法术强度,攻击速度
	int attackStrength;
	int powerStrength;
	float attackSpeed;
	float maxAttackSpeed;

	//等级，经验值
	int level;
	int experience;

	//视野半径
	int sightRange;

};

//伤害类型
UENUM()
enum DamageType { physical, magic, real, treat };

//击杀奖励
struct BaseValue {
	//金币奖励
	int goldValue;

	//经验奖励
	int experienceValue;

};


UCLASS()
class AMOBAPROJECT_API AMOBABaseActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMOBABaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	//基本属性
	BaseProperty baseProperty;

	//基本奖励
	BaseValue baseValue;

	//接受伤害
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void applyDamage(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);

	//死亡
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void deadHandle(AActor* deadActor, AActor* deadCauser);

	//攻击
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void attack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);

	//能否进行攻击
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool canAttack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);

	//设置价值
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		virtual void setValue();

public:


	//构造函数
	AMOBABaseActor(BaseProperty aBaseProperty, BaseValue aBaseValue);

};
