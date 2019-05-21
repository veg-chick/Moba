// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MOBABaseActor.generated.h"

//��Ӫ
enum Camp { blue, red, other };

//��������
struct BaseProperty {
	//������Ӫ
	Camp baseCamp;

	//Ѫ���ָ�����
	float hp;
	float maxHp;
	float hpRecovery;

	//�Ƿ��������������ָ�����
	bool bHaveMp;
	float mp;
	float maxMp;
	float mpRecovery;

	//����ħ��
	int armor;
	int magicResist;

	//�ƶ��ٶ�
	int moveSpeed;

	//�ܷ񹥻����Ƿ�Զ�̣���������
	bool bAbleToAttack;
	bool bIsRemote;
	int attackRange;

	//������������ǿ��,�����ٶ�
	int attackStrength;
	int powerStrength;
	float attackSpeed;
	float maxAttackSpeed;

	//�ȼ�������ֵ
	int level;
	int experience;

	//��Ұ�뾶
	int sightRange;

};

//�˺�����
UENUM()
enum DamageType { physical, magic, real, treat };

//��ɱ����
struct BaseValue {
	//��ҽ���
	int goldValue;

	//���齱��
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
	//��������
	BaseProperty baseProperty;

	//��������
	BaseValue baseValue;

	//�����˺�
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void applyDamage(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);

	//����
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void deadHandle(AActor* deadActor, AActor* deadCauser);

	//����
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		void attack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);

	//�ܷ���й���
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		bool canAttack(AActor* damagedActor, DamageType damageType, float damage, AActor* damageCauser);

	//���ü�ֵ
	UFUNCTION(BlueprintCallable, Category = "MyMOBA")
		virtual void setValue();

public:


	//���캯��
	AMOBABaseActor(BaseProperty aBaseProperty, BaseValue aBaseValue);

};
