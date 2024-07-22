// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Subsystem/TD_ActorManageSubsystem.h"

#include "Base/Character/TD_Enemy.h"
#include "Base/Character/Weapon/TD_WeaponBase.h"

void UTD_ActorManageSubsystem::SetWeapons(UPaperFlipbook* InFlipbook, const float InDamage, const FVector& InVelocity,
                                          const FVector& InWeaponScale, const FVector& InSphereScale,
                                          const FVector& InActorLocation,
                                          const FGameplayTag& InTargetTag, const float InSurvival, const float InWallop)
{
	ATD_WeaponBase* WeaponReclaim = nullptr;
	for (const TObjectPtr<ATD_WeaponBase> Weapon : Weapons)
	{
		if (Weapon->WeaponState == EWeaponState::Reclaim)
		{
			WeaponReclaim = Weapon;
		}
	}

	if (!IsValid(WeaponReclaim))
	{
		ATD_WeaponBase* NewWeapon = GetWorld()->SpawnActor<ATD_WeaponBase>(ATD_WeaponBase::StaticClass());
		Weapons.Add(NewWeapon);
		WeaponReclaim = NewWeapon;
	}

	WeaponReclaim->SetActorLocation(InActorLocation);
	WeaponReclaim->SetParam(InFlipbook, InDamage, InVelocity, InWeaponScale, InSphereScale, InTargetTag, InSurvival,
	                        InWallop);
}

void UTD_ActorManageSubsystem::SetEnemys(const FEnemy& EnemyParam)
{
	if (ActiveEnemys.Num() >= MaxEnemy)
	{
		return;
	}
	
	ATD_Enemy* EnemyReclaim = nullptr;
	for (const TObjectPtr<ATD_Enemy> Enemy : ReclaimEnemys)
	{
		if (Enemy->EnemyState == EEnemyState::Reclaim)
		{
			EnemyReclaim = Enemy;
		}
	}

	if (!IsValid(EnemyReclaim))
	{
		if (ActiveEnemys.Num() + ReclaimEnemys.Num() >= MaxEnemy)
		{
			return;
		}
		ATD_Enemy* NewEnemy = GetWorld()->SpawnActor<ATD_Enemy>(FVector(0.f, 0.f, -1000.f), FRotator::ZeroRotator);
		ActiveEnemys.Add(NewEnemy);
		EnemyReclaim = NewEnemy;
	}

	EnemyReclaim->SetParam(EnemyParam);
}
