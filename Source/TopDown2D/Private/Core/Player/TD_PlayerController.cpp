// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/TD_PlayerController.h"

#include "Base/Input/IA/IA_Axis1D.h"
#include "Base/Input/IA/IA_Axis2D.h"
#include "Core/Input/IMC_Context.h"
#include "PaperFlipbook.h"

ATD_PlayerController::ATD_PlayerController()
{
	MoveIA = CreateDefaultSubobject<UIA_Axis2D>("MoveIA");
	ContextIMC = CreateDefaultSubobject<UIMC_Context>("AuraContext");
	// 初始化InputMappingContext
	ContextIMC->InitMove(MoveIA);

	ShootIA = CreateDefaultSubobject<UIA_Axis1D>("ShootIA");
	ContextIMC->AddMappings(ShootIA, EKeys::LeftMouseButton);
	
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> ShuriKen_Obj(
		TEXT("/Script/Paper2D.PaperFlipbook'/Game/Asset/Weapons/Shuriken/Shuriken_Attack.Shuriken_Attack'"));
	if (ShuriKen_Obj.Succeeded())
	{
		ShuriKen = ShuriKen_Obj.Object;
	}

	bShowMouseCursor = true;
}
