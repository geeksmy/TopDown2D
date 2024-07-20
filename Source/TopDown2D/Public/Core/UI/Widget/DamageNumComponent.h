// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageNumComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWN2D_API UDamageNumComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UDamageNumComponent();

	void SetDamageNum(const float Damage, bool bBlockedHit, bool bCriticalHit);

private:
	UFUNCTION()
	void DestroyCom();

protected:
	UPROPERTY()
	FTimerHandle TimerHandle;
};
