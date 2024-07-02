// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "TD_WeaponManage.generated.h"

class UPaperFlipbook;
class ATD_WeaponBase;

UCLASS()
class TOPDOWN2D_API ATD_WeaponManage : public AActor
{
	GENERATED_BODY()

public:
	ATD_WeaponManage();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TArray<TObjectPtr<ATD_WeaponBase>> Weapons;

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
	 */
	void SetWeapons(UPaperFlipbook* InFlipbook, const float InDamage, const FVector& InVelocity,
	                const FVector& InWeaponScale, const FVector& InSphereScale, const FVector& InActorLocation,
	                const FGameplayTag& InTargetTag, const float InSurvival);
};
