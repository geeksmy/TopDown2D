// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "TD_PlayerControllerBase.generated.h"

class UDamageNumComponent;
class UPaperFlipbook;
struct FInputActionValue;
class UIA_Base;
class UIMC_Context;
/**
 * 
 */
UCLASS()
class TOPDOWN2D_API ATD_PlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UIMC_Context> ContextIMC;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UIA_Base> MoveIA;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UIA_Base> ShootIA;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Shoot(const FInputActionValue& Value);

};
