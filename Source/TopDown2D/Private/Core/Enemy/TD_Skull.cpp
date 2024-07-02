// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Enemy/TD_Skull.h"

#include "Components/CapsuleComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Core/Anim/TD_EnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Sound/SoundCue.h"


ATD_Skull::ATD_Skull()
{
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> Move_D_Obj(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Asset/Enemy/Skull/Skull_Move_D.Skull_Move_D'"));
	if (Move_D_Obj.Succeeded())
	{
		Sprite->SetFlipbook(Move_D_Obj.Object);
	}
	GetCapsuleComponent()->SetCapsuleSize(14.f, 14.f);
	GetCharacterMovement()->MaxWalkSpeed = 80.f;

	static ConstructorHelpers::FClassFinder<UTD_EnemyAnimInstance> ABP_Enemy_Class(TEXT("/Script/PaperZD.PaperZDAnimBP'/Game/BP/Amin/Enemy/ABP_Enemy.ABP_Enemy_C'"));
	if (ABP_Enemy_Class.Succeeded())
	{
		SetAnimInstance(ABP_Enemy_Class.Class);
	}
	
	static  ConstructorHelpers::FObjectFinder<UPaperZDAnimSequence> MoveAnim_Obj(TEXT("/Script/PaperZD.PaperZDAnimSequence_Flipbook'/Game/BP/Amin/Enemy/AnimSequences/AS_Skull_Move.AS_Skull_Move'"));
	if (MoveAnim_Obj.Succeeded())
	{
		MoveAnim = MoveAnim_Obj.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> HitSound_Obj(TEXT("/Script/Engine.SoundCue'/Game/Asset/Sound/Coins_Cue.Coins_Cue'"));
	if (HitSound_Obj.Succeeded())
	{
		HitSound = HitSound_Obj.Object;
	}
}

