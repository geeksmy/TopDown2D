// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TD_GameplayTags.generated.h"

USTRUCT()
struct FTD_GameplayTags
{
	GENERATED_BODY()

private:
	static FTD_GameplayTags GameplayTags;

public:
	static const FTD_GameplayTags& Get() { return GameplayTags; }
	static void InitGameplayTags();

	FGameplayTag CharacterEnemy;
	FGameplayTag CharacterPlayer;
};
