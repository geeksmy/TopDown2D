// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TD_AssetManager.h"

#include "AbilitySystemGlobals.h"
#include "Core/TD_GameplayTags.h"

UTD_AssetManager::UTD_AssetManager()
{
	FTD_GameplayTags::InitGameplayTags();
}

UTD_AssetManager& UTD_AssetManager::Get()
{
	check(GEngine)
	UTD_AssetManager* TD_AssetManager = Cast<UTD_AssetManager>(GEngine->AssetManager);
	return *TD_AssetManager;
}

void UTD_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
