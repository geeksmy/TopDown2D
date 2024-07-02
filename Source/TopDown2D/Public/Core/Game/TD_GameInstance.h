// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TD_GameInstance.generated.h"

class ATD_WeaponManage;
class ATD_WeaponBase;
class ATD_PlayerController;
/**
 * 
 */
UCLASS()
class TOPDOWN2D_API UTD_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<ATD_WeaponManage> TD_WeaponManage;
};
