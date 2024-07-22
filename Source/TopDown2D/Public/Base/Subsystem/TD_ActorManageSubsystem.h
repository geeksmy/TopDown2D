// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "Base/Character/TD_Enemy.h"
#include "TD_ActorManageSubsystem.generated.h"

class ATD_Enemy;
class ATD_WeaponBase;
class UPaperFlipbook;
/**
 * 
 */
UCLASS()
class TOPDOWN2D_API UTD_ActorManageSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** 设置武器池
	 * 
	 * @param InFlipbook 图像序列
	 * @param InDamage 伤害
	 * @param InVelocity 速度
	 * @param InWeaponScale WeaponFlipbook尺寸
	 * @param InSphereScale Sphere尺寸
	 * @param InTargetTag 目标标签 
	 * @param InSurvival 存活时间
	 * @param InActorLocation 武器发射位置
	 * @param InWallop 冲击力
	 */
	void SetWeapons(UPaperFlipbook* InFlipbook, const float InDamage, const FVector& InVelocity,
	                const FVector& InWeaponScale, const FVector& InSphereScale, const FVector& InActorLocation,
	                const FGameplayTag& InTargetTag, const float InSurvival, const float InWallop);

	void SetEnemys(const FEnemy& EnemyParam);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TArray<TObjectPtr<ATD_WeaponBase>> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TArray<TObjectPtr<ATD_Enemy>> ActiveEnemys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TArray<TObjectPtr<ATD_Enemy>> ReclaimEnemys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	uint8 MaxEnemy = 5;
};
