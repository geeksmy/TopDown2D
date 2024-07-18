// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Player/TD_AIControllerBase.h"

#include "Base/Character/TD_CharacterBase.h"
#include "Base/Character/TD_Enemy.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Core/TD_KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"


ATD_AIControllerBase::ATD_AIControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATD_AIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	MoveToTargetDelegate.BindDynamic(this, &ATD_AIControllerBase::MoveToTarget);
	UTD_KismetSystemLibrary::SetTimer(this, this, &ATD_AIControllerBase::MoveToTarget, 0.2);
}

void ATD_AIControllerBase::MoveToTarget()
{
	ATD_CharacterBase* CharacterBase = Cast<ATD_CharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	ATD_Enemy* Enemy = Cast<ATD_Enemy>(this->GetPawn());
	if (IsValid(Enemy) && IsValid(CharacterBase))
	{
		UAIBlueprintHelperLibrary::CreateMoveToProxyObject(GetWorld(), Enemy, CharacterBase->GetActorLocation(),
		                                                   CharacterBase);
	}
}

void ATD_AIControllerBase::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (Result.IsFailure())
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("移动失败"));
		MoveToTargetHandle = UTD_KismetSystemLibrary::SetTimerDelegate(MoveToTargetDelegate, 0.5, true);
	}
	if (Result.IsSuccess())
	{
		GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, TEXT("移动成功"));
		UTD_KismetSystemLibrary::ClearTimerHandle(this, MoveToTargetHandle);
		UTD_KismetSystemLibrary::SetTimer(this, this, &ATD_AIControllerBase::MoveToTarget, 0.2);
	}
}
