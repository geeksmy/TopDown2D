// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Character/TD_Enemy.h"

#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Core/TD_GameplayTags.h"
#include "Core/TD_KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ATD_Enemy::ATD_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;
	FCollisionResponseContainer Container(ECR_Ignore);
	Container.SetResponse(ECC_WorldStatic, ECR_Block);
	Container.SetResponse(ECC_WorldDynamic, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannels(Container);

	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Tags.Add(FTD_GameplayTags::Get().CharacterEnemy.GetTagName());
}

void ATD_Enemy::SetColor()
{ 
	Sprite->SetSpriteColor(FColor::White);
}

void ATD_Enemy::HitEffect(const float Damage)
{
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, FString::SanitizeFloat(Damage));
	Sprite->SetSpriteColor(FColor::Red);
	UGameplayStatics::PlaySound2D(this, HitSound);
	UTD_KismetSystemLibrary::SetTimer(this, this, &ATD_Enemy::SetColor, 0.1);
}