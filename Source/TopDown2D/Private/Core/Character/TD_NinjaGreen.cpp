// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/TD_NinjaGreen.h"

#include "Components/CapsuleComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Core/Anim/TD_CharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"


ATD_NinjaGreen::ATD_NinjaGreen()
{
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> Idle_D_Obj(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Asset/Character/NinjaGreen/Idle_D.Idle_D'"));
	if (Idle_D_Obj.Succeeded())
	{
		Sprite->SetFlipbook(Idle_D_Obj.Object);
	}
	GetCapsuleComponent()->SetCapsuleSize(10.f, 10.f);
	GetCharacterMovement()->MaxWalkSpeed = 120.f;

	static ConstructorHelpers::FClassFinder<UTD_CharacterAnimInstance> ABP_Character_Class(TEXT("/Script/PaperZD.PaperZDAnimBP'/Game/BP/Amin/Character/ABP_Character.ABP_Character_C'"));
	if (ABP_Character_Class.Succeeded())
	{
		SetAnimInstance(ABP_Character_Class.Class);
	}
}
