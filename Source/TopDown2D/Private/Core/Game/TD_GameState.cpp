// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Game/TD_GameState.h"

#include "DataRegistrySubsystem.h"
#include "Base/Character/TD_Enemy.h"
#include "Base/Subsystem/TD_ActorManageSubsystem.h"
#include "Core/TD_KismetSystemLibrary.h"

ATD_GameState::ATD_GameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATD_GameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	UTD_ActorManageSubsystem* ActorManageSubsystem = UTD_KismetSystemLibrary::GetActorManageSubsystem(this);
	UDataRegistrySubsystem* DRSubsystem = GEngine->GetEngineSubsystem<UDataRegistrySubsystem>();
	FDataRegistryId EnemyID(FName("Enemy"), FName("Skull"));
	const FEnemy* EnemyParam = DRSubsystem->GetCachedItem<FEnemy>(EnemyID);
	ActorManageSubsystem->SetEnemys(*EnemyParam);
}
