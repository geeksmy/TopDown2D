// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TD_KismetSystemLibrary.h"

#include "Core/Game/TD_GameInstance.h"

UTD_GameInstance* UTD_KismetSystemLibrary::GetGameInstance(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		return Cast<UTD_GameInstance>(World->GetGameInstance());
	}
	return nullptr;
}
