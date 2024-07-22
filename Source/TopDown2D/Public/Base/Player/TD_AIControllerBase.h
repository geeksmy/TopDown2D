// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "TD_AIControllerBase.generated.h"

UCLASS()
class TOPDOWN2D_API ATD_AIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	ATD_AIControllerBase();

private:
	UFUNCTION()
	void MoveToTarget();
	
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
	UPROPERTY()
	FTimerHandle SuccessHandle;
	UPROPERTY()
	FTimerHandle FailureHandle;
	UPROPERTY()
	FTimerHandle SpawnPointHandle;

public:
	void SpawnPoint();
	void SetSpawnPointHandle(const FTimerHandle& InHandle) { SpawnPointHandle = InHandle; };
};
