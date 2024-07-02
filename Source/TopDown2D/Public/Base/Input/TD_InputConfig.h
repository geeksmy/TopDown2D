// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "TD_InputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FTD_InputAction
{
	GENERATED_BODY()

	FTD_InputAction(const FKey& InKey = EKeys::Invalid) : Key(InKey)
	{
	};

	FTD_InputAction(const UInputAction* InInputAction, const FGameplayTag& InInputTag,
	                 const FKey& InKey = EKeys::Invalid) : InputAction(InInputAction), Key(InKey)
	{
		InputTag = InInputTag;
	}

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly)
	FKey Key;
};

/**
 * 
 */
UCLASS()
class TOPDOWN2D_API UTD_InputConfig : public UDataAsset
{
	GENERATED_BODY()

	UTD_InputConfig();

public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FTD_InputAction> AbilityInputActions;

private:
	void AddAbilityInputAction(const UInputAction* InInputAction, const FGameplayTag& InInputTag,
	                           const FKey& InKey = EKeys::Invalid);
};
