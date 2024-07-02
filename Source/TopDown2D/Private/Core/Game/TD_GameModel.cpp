// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Game/TD_GameModel.h"

#include "Core/Character/TD_NinjaGreen.h"
#include "Core/Game/TD_GameState.h"
#include "Core/Player/TD_PlayerController.h"
#include "Core/Player/TD_PlayerState.h"
#include "Core/UI/HUD/TD_HUD.h"

ATD_GameModel::ATD_GameModel()
{
	DefaultPawnClass = ATD_NinjaGreen::StaticClass();
	PlayerControllerClass = ATD_PlayerController::StaticClass();
	PlayerStateClass = ATD_PlayerState::StaticClass();
	GameStateClass = ATD_GameState::StaticClass();
	HUDClass = ATD_HUD::StaticClass();
}
