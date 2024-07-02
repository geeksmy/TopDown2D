// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Input/TD_InputConfig.h"

UTD_InputConfig::UTD_InputConfig()
{
}

const UInputAction* UTD_InputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (FTD_InputAction AbilityInputAction : AbilityInputActions)
	{
		if (AbilityInputAction.InputTag.MatchesTagExact(InputTag))
		{
			return AbilityInputAction.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] AbilityInputActions查找不到InputTag[%s]"), *GetNameSafe(this), *InputTag.ToString());
	}
	
	return nullptr;
}

void UTD_InputConfig::AddAbilityInputAction(const UInputAction* InInputAction, const FGameplayTag& InInputTag,
	const FKey& InKey)
{
	FTD_InputAction TD_InputAction(InInputAction, InInputTag, InKey);
	AbilityInputActions.Add(TD_InputAction);
}
