// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Player/TD_AIControllerBase.h"

#include "Base/Character/TD_CharacterBase.h"
#include "Base/Character/TD_Enemy.h"
#include "Core/TD_KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"


ATD_AIControllerBase::ATD_AIControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATD_AIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	SpawnPointHandle = UTD_KismetSystemLibrary::SetTimer(this, this, &ATD_AIControllerBase::SpawnPoint, 0.3, true);
}

void ATD_AIControllerBase::MoveToTarget()
{
	ATD_CharacterBase* CharacterBase = Cast<ATD_CharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	ATD_Enemy* Enemy = Cast<ATD_Enemy>(this->GetPawn());
	if (IsValid(Enemy) && IsValid(CharacterBase))
	{
		
		MoveToActor(CharacterBase, 5.f, false);
	}
}

void ATD_AIControllerBase::SpawnPoint()
{
	// 获取游戏中的第一个玩家的棋子，以便为玩家提供新的随机位置。
	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	// 生成一个随机位置，该位置在玩家当前位置的可导航半径内。
	FVector RandomLocation;
	UTD_KismetSystemLibrary::GetGetRandomLocationInNavigableRadius(this, PlayerPawn->GetActorLocation(), RandomLocation,
	                                                               900.f);

	// 检查生成的随机位置是否在屏幕范围内，如果不在，则将玩家传送到该位置。
	if (!UTD_KismetSystemLibrary::CheckOnScreen(this, RandomLocation))
	{
		// 使用随机位置和玩家当前的旋转角度将玩家传送到新位置。
		ATD_Enemy* Enemy = GetPawn<ATD_Enemy>();
		RandomLocation.Z += 15.f;
		if (Enemy->TeleportTo(RandomLocation, FRotator::ZeroRotator))
		{
			Enemy->GetCharacterMovement()->MovementMode = MOVE_NavWalking;
			MoveToTarget();
			// 清除定时器句柄，确保后续的随机位置生成不会受到之前定时器的影响。
			UTD_KismetSystemLibrary::ClearTimerHandle(this, SpawnPointHandle);
		}
	}
}

void ATD_AIControllerBase::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (Result.IsSuccess())
	{
		UTD_KismetSystemLibrary::ClearTimerHandle(this, SuccessHandle);
		UTD_KismetSystemLibrary::SetTimer(this, this, &ATD_AIControllerBase::MoveToTarget, 0.2, false);
		return;
	}
	if (Result.IsFailure())
	{
		UTD_KismetSystemLibrary::ClearTimerHandle(this, FailureHandle);
		ATD_Enemy* Enemy = Cast<ATD_Enemy>(this->GetPawn());
		Enemy->GetCharacterMovement()->MovementMode = MOVE_NavWalking;
		FailureHandle = UTD_KismetSystemLibrary::SetTimer(this, this, &ATD_AIControllerBase::MoveToTarget, 0.5, true);
	}
}
