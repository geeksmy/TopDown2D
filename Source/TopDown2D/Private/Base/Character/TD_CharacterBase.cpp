// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Character/TD_CharacterBase.h"

#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperZDCustomVersion.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

const FGuid FPaperZDCustomVersion::GUID(0x11310AED, 0x2E554D61, 0xAF679AA3, 0xC5A1082A);

ATD_CharacterBase::ATD_CharacterBase()
{
	Sprite = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	if (Sprite)
	{
		Sprite->AlwaysLoadOnClient = true;
		Sprite->AlwaysLoadOnServer = true;
		Sprite->bOwnerNoSee = false;
		Sprite->bAffectDynamicIndirectLighting = true;
		Sprite->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Sprite->SetupAttachment(GetCapsuleComponent());
		static FName CollisionProfileName(TEXT("CharacterMesh"));
		Sprite->SetCollisionProfileName(CollisionProfileName);
		Sprite->SetGenerateOverlapEvents(false);
		Sprite->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
		Sprite->SetCollisionProfileName(FName("NoCollision"));
	}
	AnimationComponent = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("Animation"));
	AnimationComponent->InitRenderComponent(GetSprite());
}

void ATD_CharacterBase::PostLoad()
{
	Super::PostLoad();
}

void ATD_CharacterBase::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	Ar.UsingCustomVersion(FPaperZDCustomVersion::GUID);
}

void ATD_CharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsValid(this))
	{
		if (Sprite)
		{
			// force animation tick after movement component updates
			if (Sprite->PrimaryComponentTick.bCanEverTick && GetCharacterMovement())
			{
				Sprite->PrimaryComponentTick.AddPrerequisite(GetCharacterMovement(),
				                                             GetCharacterMovement()->PrimaryComponentTick);
			}
		}
	}
}

TSubclassOf<UPaperZDAnimInstance> ATD_CharacterBase::GetSequencerAnimInstanceClass() const
{
	return AnimationComponent->GetSequencerAnimInstanceClass();
}

UPaperZDAnimInstance* ATD_CharacterBase::GetSequencerAnimInstance()
{
	return AnimationComponent->GetSequencerAnimInstance();
}

UPaperZDAnimInstance* ATD_CharacterBase::GetAnimInstance() const
{
	return AnimationComponent->GetAnimInstance();
}

void ATD_CharacterBase::SetAnimInstance(const TSubclassOf<UPaperZDAnimInstance>& InAnimInstanceClass) const
{
	AnimationComponent->SetAnimInstanceClass(InAnimInstanceClass);
}
