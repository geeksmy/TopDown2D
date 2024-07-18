// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TD_KismetSystemLibrary.generated.h"

class UTD_GameInstance;
/**
 * 自定义公共函数
 */
UCLASS()
class TOPDOWN2D_API UTD_KismetSystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static UTD_GameInstance* GetGameInstance(const UObject* WorldContextObject);

	// UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	template <class UserClass>
	static void SetTimer(const UObject* WorldContextObject, UserClass* InObj,
	                     typename FTimerDelegate::TMethodPtr<UserClass> InTimerMethod, float InRate);


	static FTimerHandle SetTimerDelegate(FTimerDynamicDelegate Delegate, float Time, bool bLooping, bool bMaxOncePerFrame = false, float InitialStartDelay = 0.f, float InitialStartDelayVariance = 0.f);
	static void ClearTimerHandle(const UObject* WorldContextObject, FTimerHandle Handle);
};

template <class UserClass>
void UTD_KismetSystemLibrary::SetTimer(const UObject* WorldContextObject, UserClass* InObj,
                                       FTimerDelegate::TMethodPtr<UserClass> InTimerMethod, float InRate)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		FTimerHandle TimerHandle;
		World->GetTimerManager().SetTimer(TimerHandle, InObj, InTimerMethod, InRate);
	}
}
