// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Sequencer/IPaperZDSequencerSource.h"
#include "TD_CharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UPaperFlipbook;
class UPaperZDAnimationComponent;

UCLASS()
class TOPDOWN2D_API ATD_CharacterBase : public ACharacter, public IPaperZDSequencerSource
{
	GENERATED_BODY()

public:
	ATD_CharacterBase();
	
public:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPaperFlipbookComponent> Sprite;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PaperZD", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperZDAnimationComponent> AnimationComponent;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	float XDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	float YDirection = 1.f;

public:
	//~ Begin UObject Interface
	virtual void PostLoad() override;
	virtual void Serialize(FArchive& Ar) override;
	//~ End UObject Interface

	//~ Begin AActor Interface
	virtual void PostInitializeComponents() override;
	//~ End AActor Interface

	//~ Begin IPaperZDSequencerSource Interface
	virtual TSubclassOf<UPaperZDAnimInstance> GetSequencerAnimInstanceClass() const override;
	virtual UPaperZDAnimInstance* GetSequencerAnimInstance() override;
	//~ End IPaperZDSequencerSource Interface

	//getters
	FORCEINLINE UPaperZDAnimationComponent* GetAnimationComponent() const { return AnimationComponent; }

	/* Obtain the AnimInstance that drives this character. */
	UFUNCTION(BlueprintPure, Category = "PaperZD")
	UPaperZDAnimInstance* GetAnimInstance() const;
	FORCEINLINE class UPaperFlipbookComponent* GetSprite() const { return Sprite; }
	void SetAnimInstance(const TSubclassOf<UPaperZDAnimInstance>& InAnimInstanceClass) const;
};
