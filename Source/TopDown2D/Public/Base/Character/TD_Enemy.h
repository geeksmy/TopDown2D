// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TD_CharacterBase.h"
#include "Base/Interface/TD_EnemyInterface.h"
#include "TD_Enemy.generated.h"

class UPaperZDAnimSequence;

UCLASS()
class TOPDOWN2D_API ATD_Enemy : public ATD_CharacterBase, public ITD_EnemyInterface
{
	GENERATED_BODY()

public:
	ATD_Enemy();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Anim")
	TObjectPtr<UPaperZDAnimSequence> MoveAnim;

public:
	UPaperZDAnimSequence* GetMoveAnim() { return MoveAnim; }

	void SetColor();
	virtual void HitEffect(const float Damage) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USoundBase> HitSound;
};
