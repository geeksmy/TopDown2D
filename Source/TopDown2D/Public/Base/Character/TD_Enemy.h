// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TD_CharacterBase.h"
#include "Base/Interface/TD_EnemyInterface.h"
#include "Core/Data/DA_Enemy.h"
#include "TD_Enemy.generated.h"

class UDamageNumComponent;
class UPaperZDAnimSequence;

UCLASS()
class TOPDOWN2D_API ATD_Enemy : public ATD_CharacterBase, public ITD_EnemyInterface
{
	GENERATED_BODY()

public:
	ATD_Enemy();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void SetColor();
	void Repelled(const float Wallop);

public:
	UPaperZDAnimSequence* GetMoveAnim() { return MoveAnim; }
	virtual void HitEffect(const float Damage, const float Wallop) override;

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(const float Damage, bool bBlockedHit, bool bCriticalHit);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Anim")
	TObjectPtr<UPaperZDAnimSequence> MoveAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Data")
	TObjectPtr<UDA_Enemy> DAEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UDamageNumComponent> DamageComponentClass;

	UPROPERTY()
	FTimerHandle TimerHandle;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USoundBase> HitSound;
};
