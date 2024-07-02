// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TD_GameplayTags.h"

#include "GameplayTagsManager.h"

FTD_GameplayTags FTD_GameplayTags::GameplayTags;

void FTD_GameplayTags::InitGameplayTags()
{
	GameplayTags.CharacterEnemy = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Type.Enemy"), FString("敌人类型"));
	GameplayTags.CharacterPlayer = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Type.Player"), FString("玩家类型"));
}
