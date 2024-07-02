// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimInstance.h"
#include "TD_CharacterAnimInstance.generated.h"

class ATD_Character;
/**
 * 
 */
UCLASS()
class TOPDOWN2D_API UTD_CharacterAnimInstance : public UPaperZDAnimInstance
{
	GENERATED_BODY()

	virtual void OnInit_Implementation() override;

public:
	UPROPERTY(BlueprintReadOnly, Category="Character")
	TObjectPtr<ATD_Character> TD_Character;
};
