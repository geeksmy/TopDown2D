// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_Enemy.generated.h"

class UPaperZDAnimSequence;
/**
 * 
 */
UCLASS()
class TOPDOWN2D_API UDA_Enemy : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="ID")
	FGuid ID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="名称")
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="移动动画")
	TObjectPtr<UPaperZDAnimSequence> MoveAnim;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="攻击")
	float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="速度")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="经验")
	float Exp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="存活时间")
	float SurviveTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="重量(影响击退距离)")
	float Weight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="Boss")
	bool bBoos;
};
