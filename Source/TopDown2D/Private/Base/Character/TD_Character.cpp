// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Character/TD_Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Core/TD_GameplayTags.h"
#include "GameFramework/SpringArmComponent.h"

ATD_Character::ATD_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-90.f, 0.f, -90.f));
	SpringArm->bDoCollisionTest = false;
	Camera->SetupAttachment(SpringArm);
	Camera->SetProjectionMode(ECameraProjectionMode::Type::Orthographic);
	Camera->SetOrthoWidth(600.f);
	
	FCollisionResponseContainer Container(ECR_Ignore);
	Container.SetResponse(ECC_WorldStatic, ECR_Block);
	Container.SetResponse(ECC_WorldDynamic, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannels(Container);

	Tags.Add(FTD_GameplayTags::Get().CharacterPlayer.GetTagName());
}

