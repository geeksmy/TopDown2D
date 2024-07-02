// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Anim/TD_EnemyAnimInstance.h"

#include "Base/Character/TD_Enemy.h"

void UTD_EnemyAnimInstance::OnInit_Implementation()
{
	TD_Enemy = Cast<ATD_Enemy>(GetOwningActor());
}
