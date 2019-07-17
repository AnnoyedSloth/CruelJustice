// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "CJGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FCJEnemyStat : public FTableRowBase
{
	GENERATED_BODY()

public:

	FCJEnemyStat() : id(0), hp(0), mp(0), attack(0), defense(0), exp(0){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		int32 id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		float hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		float mp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		float attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		float defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		int exp;
};

USTRUCT(BlueprintType)
struct FCJEnemyTransform : public FTableRowBase
{
	GENERATED_BODY()

public:
	
	FCJEnemyTransform() : id(0), x(0), y(0), z(0), yaw(0){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Transform)
		int32 id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Transform)
		float x;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Transform)
		float y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Transform)
		float z;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Transform)
		float yaw;
};


UCLASS()
class CRUELJUSTICE_API UCJGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class UDataTable* enemyStat;

	UPROPERTY()
	class UDataTable* enemyTransform;

public:
	UCJGameInstance();

	virtual void Init() override;

	//FCJEnemyStat* GetEnemyStat() const { return enemyStat; }
	//FCJEnemyTransform* GetEnemyTransform() const { return enemyTransform; }
	
};
