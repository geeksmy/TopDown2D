// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TD_KismetSystemLibrary.generated.h"

class UNavigationQueryFilter;
class ANavigationData;
class UTD_ActorManageSubsystem;
/**
 * 自定义公共函数
 */
UCLASS()
class TOPDOWN2D_API UTD_KismetSystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static UGameInstance* GetGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static UTD_ActorManageSubsystem* GetActorManageSubsystem(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static void GetGetRandomLocationInNavigableRadius(UObject* WorldContextObject, const FVector& Origin,
	                                                  FVector& RandomLocation, float Radius,
	                                                  ANavigationData* NavData = NULL,
	                                                  TSubclassOf<UNavigationQueryFilter> FilterClass = NULL);

	template <class UserClass>
	static FTimerHandle SetTimer(const UObject* WorldContextObject, UserClass* InObj,
	                             typename FTimerDelegate::TMethodPtr<UserClass> InTimerMethod, float InRate,
	                             bool bLooping,
	                             float InFirstDelay = -1);

	static void ClearTimerHandle(const UObject* WorldContextObject, FTimerHandle Handle);

	// 检查在屏幕内
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static bool CheckOnScreen(const UObject* WorldContextObject, const FVector& WorldLocation);
};

template <class UserClass>
FTimerHandle UTD_KismetSystemLibrary::SetTimer(const UObject* WorldContextObject, UserClass* InObj,
                                               FTimerDelegate::TMethodPtr<UserClass> InTimerMethod, float InRate,
                                               bool bLooping,
                                               float InFirstDelay)
{
	FTimerHandle TimerHandle;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,
	                                                             EGetWorldErrorMode::LogAndReturnNull))
	{
		World->GetTimerManager().SetTimer(TimerHandle, InObj, InTimerMethod, InRate, bLooping, InFirstDelay);
	}
	return TimerHandle;
}
