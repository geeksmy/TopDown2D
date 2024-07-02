// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputCoreTypes.h"
#include "IMC_Context.generated.h"

class UIA_Base;
/**
 * 
 */
UCLASS()
class TOPDOWN2D_API UIMC_Context : public UInputMappingContext
{
	GENERATED_BODY()

public:
	void InitMove(UIA_Base* MoveIA);
	void AddMappings(UIA_Base* BaseIA, const FKey InKey);
};
