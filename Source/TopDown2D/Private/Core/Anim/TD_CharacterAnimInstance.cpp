// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Anim/TD_CharacterAnimInstance.h"

#include "Base/Character/TD_Character.h"

void UTD_CharacterAnimInstance::OnInit_Implementation()
{
	TD_Character = Cast<ATD_Character>(GetOwningActor());
}
