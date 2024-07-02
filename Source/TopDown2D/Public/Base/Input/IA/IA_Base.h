// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "IA_Base.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN2D_API UIA_Base : public UInputAction
{
	GENERATED_BODY()

public:
	void SetValueType(EInputActionValueType NewValueType);
};
