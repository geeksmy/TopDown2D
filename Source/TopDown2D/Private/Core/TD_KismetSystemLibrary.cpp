// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TD_KismetSystemLibrary.h"

#include "NavigationSystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Base/Subsystem/TD_ActorManageSubsystem.h"

UGameInstance* UTD_KismetSystemLibrary::GetGameInstance(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,
	                                                             EGetWorldErrorMode::LogAndReturnNull))
	{
		return World->GetGameInstance();
	}
	return nullptr;
}

UTD_ActorManageSubsystem* UTD_KismetSystemLibrary::GetActorManageSubsystem(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,
	                                                             EGetWorldErrorMode::LogAndReturnNull))
	{
		return World->GetGameInstance()->GetSubsystem<UTD_ActorManageSubsystem>();
	}
	return nullptr;
}

void UTD_KismetSystemLibrary::GetGetRandomLocationInNavigableRadius(UObject* WorldContextObject, const FVector& Origin,
	FVector& RandomLocation, float Radius, ANavigationData* NavData, TSubclassOf<UNavigationQueryFilter> FilterClass)
{
	UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(WorldContextObject, Origin, RandomLocation, Radius, NavData, FilterClass);
}

void UTD_KismetSystemLibrary::ClearTimerHandle(const UObject* WorldContextObject, FTimerHandle Handle)
{
	UKismetSystemLibrary::K2_ClearTimerHandle(WorldContextObject, Handle);
}

bool UTD_KismetSystemLibrary::CheckOnScreen(const UObject* WorldContextObject, const FVector& WorldLocation)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,
	                                                             EGetWorldErrorMode::LogAndReturnNull))
	{
		if (const APlayerController* FirstPlayerController = World->GetFirstPlayerController())
		{
			FVector2D ScreenPosition;
			UGameplayStatics::ProjectWorldToScreen(FirstPlayerController, WorldLocation, ScreenPosition);

			FVector2D ViewPosition;
			World->GetGameViewport()->GetViewportSize(ViewPosition);

			return ScreenPosition.X > 0 && ScreenPosition.Y > 0 && ScreenPosition.X < ViewPosition.X && ScreenPosition.Y
				< ViewPosition.Y;
		}
	}

	return true;
}
