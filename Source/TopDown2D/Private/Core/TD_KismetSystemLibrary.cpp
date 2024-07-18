// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TD_KismetSystemLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Core/Game/TD_GameInstance.h"

UTD_GameInstance* UTD_KismetSystemLibrary::GetGameInstance(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		return Cast<UTD_GameInstance>(World->GetGameInstance());
	}
	return nullptr;
}

FTimerHandle UTD_KismetSystemLibrary::SetTimerDelegate(FTimerDynamicDelegate Delegate, float Time, bool bLooping,
	bool bMaxOncePerFrame, float InitialStartDelay, float InitialStartDelayVariance)
{
	return UKismetSystemLibrary::K2_SetTimerDelegate(Delegate, Time, bLooping, bMaxOncePerFrame, InitialStartDelay, InitialStartDelayVariance);
}

void UTD_KismetSystemLibrary::ClearTimerHandle(const UObject* WorldContextObject, FTimerHandle Handle)
{
	UKismetSystemLibrary::K2_ClearTimerHandle(WorldContextObject, Handle);
}
