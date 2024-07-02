// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TD_EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTD_EnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWN2D_API ITD_EnemyInterface
{
	GENERATED_BODY()

public:
	/** 受击效果
	 * 
	 * @param Damage 伤害
	 */
	virtual void HitEffect(const float Damage) = 0;
};
