// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Character/Weapon/TD_WeaponManage.h"

#include "Base/Character/Weapon/TD_WeaponBase.h"
#include "Core/TD_KismetSystemLibrary.h"
#include "Core/Game/TD_GameInstance.h"

ATD_WeaponManage::ATD_WeaponManage()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATD_WeaponManage::BeginPlay()
{
	Super::BeginPlay();
	if (UTD_GameInstance* Instance = UTD_KismetSystemLibrary::GetGameInstance(this))
	{
		Instance->TD_WeaponManage = this;
	}
}

void ATD_WeaponManage::SetWeapons(UPaperFlipbook* InFlipbook, const float InDamage, const FVector& InVelocity,
                                  const FVector& InWeaponScale, const FVector& InSphereScale,
                                  const FVector& InActorLocation,
                                  const FGameplayTag& InTargetTag, const float InSurvival)
{
	ATD_WeaponBase* WeaponReclaim  = nullptr;
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
	WeaponReclaim->SetParam(InFlipbook, InDamage, InVelocity, InWeaponScale, InSphereScale, InTargetTag, InSurvival);
}
