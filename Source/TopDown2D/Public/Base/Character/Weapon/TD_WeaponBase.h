// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "TD_WeaponBase.generated.h"

class UPaperFlipbook;
class UPaperFlipbookComponent;
class UProjectileMovementComponent;
class USphereComponent;

UENUM()
enum class EWeaponState : uint8
{
	Active, // 激活
	Reclaim // 回收
};

USTRUCT(BlueprintType)
struct FWeapon : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="ID")
	FGuid ID = FGuid();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="武器")
	TObjectPtr<UPaperFlipbook> Flipbook = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="伤害")
	float Damage = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="武器尺寸")
	FVector WeaponScale = FVector::Zero();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="碰撞体")
	FVector SphereScale = FVector::Zero();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="目标标签")
	FGameplayTag TargetTag = FGameplayTag();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="存活时间")
	float Survival = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="冲击力")
	float Wallop = 0.f;
};

UCLASS()
class TOPDOWN2D_API ATD_WeaponBase : public AActor
{
	GENERATED_BODY()

	ATD_WeaponBase();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Wallop = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag TargetTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponState WeaponState = EWeaponState::Reclaim;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPaperFlipbookComponent> WeaponFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY()
	FTimerHandle TimerHandle;

public:
	/** 设置武器属性
	 * 
	 * @param InFlipbook 图像序列
	 * @param InDamage 伤害
	 * @param InVelocity 速度
	 * @param InWeaponScale WeaponFlipbook尺寸
	 * @param InSphereScale Sphere尺寸
	 * @param InTargetTag 目标标签 
	 * @param InSurvival 存活时间
	 * @param InWallop 冲击力
	 */
	void SetParam(UPaperFlipbook* InFlipbook, const float InDamage, const FVector& InVelocity,
	              const FVector& InWeaponScale, const FVector& InSphereScale, const FGameplayTag& InTargetTag,
	              const float InSurvival, const float InWallop);

	void Reclaim();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
