// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/Character/TD_CharacterBase.h"
#include "TD_Character.generated.h"

UCLASS()
class TOPDOWN2D_API ATD_Character : public ATD_CharacterBase
{
	GENERATED_BODY()

public:
	ATD_Character();

private:
	UPROPERTY(VisibleAnywhere, Category="Character")
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(VisibleAnywhere, Category="Character")
	TObjectPtr<UCameraComponent> Camera;
};
