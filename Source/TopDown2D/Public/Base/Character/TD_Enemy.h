// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TD_CharacterBase.h"
#include "Base/Interface/TD_EnemyInterface.h"
#include "TD_Enemy.generated.h"

UENUM()
enum class EEnemyState : uint8
{
	Active, // 激活
	Reclaim // 回收
};

class UDamageNumComponent;
class UPaperZDAnimSequence;

USTRUCT(BlueprintType)
struct FEnemy : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="ID")
	FGuid ID = FGuid();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="名称")
	FName Name = FName();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="移动动画")
	TObjectPtr<UPaperZDAnimSequence> MoveAnim = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="攻击")
	float Attack = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="速度")
	float Speed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="经验")
	float Exp = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="存活时间")
	float SurviveTime = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="重量(影响击退距离)")
	float Weight = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="Boss")
	bool bBoos = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="胶囊体-半径")
	float Radius = 14.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="胶囊体-半高")
	float HalfHeight = 14.f;
};

UCLASS()
class TOPDOWN2D_API ATD_Enemy : public ATD_CharacterBase, public ITD_EnemyInterface
{
	GENERATED_BODY()

public:
	ATD_Enemy();

protected:
	virtual void Tick(float DeltaSeconds) override;
	void SetColor();
	void Repelled(const float Wallop);

public:
	UPaperZDAnimSequence* GetMoveAnim() { return MoveAnim; }
	virtual void HitEffect(const float Damage, const float Wallop) override;
	void SetParam(const FEnemy& InEnemyParam);

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(const float Damage, bool bBlockedHit, bool bCriticalHit);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Anim")
	TObjectPtr<UPaperZDAnimSequence> MoveAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Param")
	FEnemy EnemyParam = FEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UDamageNumComponent> DamageComponentClass;

	UPROPERTY()
	FTimerHandle TimerHandle;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::Reclaim;
};
