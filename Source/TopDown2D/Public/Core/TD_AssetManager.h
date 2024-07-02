// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TD_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN2D_API UTD_AssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UTD_AssetManager();
	static UTD_AssetManager& Get();

private:
	virtual void StartInitialLoading() override;
};
