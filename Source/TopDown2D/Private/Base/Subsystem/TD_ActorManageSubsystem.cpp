// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Subsystem/TD_ActorManageSubsystem.h"

#include "Base/Character/Weapon/TD_WeaponBase.h"

void UTD_ActorManageSubsystem::SetWeapons(UPaperFlipbook* InFlipbook, const float InDamage, const FVector& InVelocity,
                                          const FVector& InWeaponScale, const FVector& InSphereScale, const FVector& InActorLocation,
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
