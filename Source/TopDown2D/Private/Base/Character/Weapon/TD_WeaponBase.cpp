// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Character/Weapon/TD_WeaponBase.h"

#include "PaperFlipbookComponent.h"
#include "Base/Character/TD_Enemy.h"
#include "Components/SphereComponent.h"
#include "Core/TD_KismetSystemLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"


ATD_WeaponBase::ATD_WeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	WeaponFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("WeaponFlipbook"));
	WeaponFlipbook->SetupAttachment(SceneRoot);
	WeaponFlipbook->SetCollisionProfileName(FName("NoCollision"));
	WeaponFlipbook->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(WeaponFlipbook);
	Sphere->SetSphereRadius(8.f);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(SceneRoot);
	ProjectileMovement->InitialSpeed = 200.f;
	ProjectileMovement->MaxSpeed = 200.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->Velocity = FVector(0.f);
}

void ATD_WeaponBase::SetParam(UPaperFlipbook* InFlipbook, const float InDamage, const FVector& InVelocity,
                              const FVector& InWeaponScale, const FVector& InSphereScale,
                              const FGameplayTag& InTargetTag, const float InSurvival, const float InWallop)
{
	WeaponFlipbook->SetFlipbook(InFlipbook);
	WeaponFlipbook->SetRelativeScale3D(InWeaponScale);
	ProjectileMovement->Velocity = InVelocity;
	Sphere->SetRelativeScale3D(InSphereScale);
	Damage = InDamage;
	TargetTag = InTargetTag;
	Wallop = InWallop;

	WeaponState = EWeaponState::Active;

	TimerHandle = UTD_KismetSystemLibrary::SetTimer(this, this, &ATD_WeaponBase::Reclaim, InSurvival, false);
}

void ATD_WeaponBase::Reclaim()
{
	WeaponFlipbook->SetFlipbook(nullptr);
	WeaponFlipbook->SetRelativeScale3D(FVector(1.f));
	ProjectileMovement->Velocity = FVector(0.f);
	Sphere->SetRelativeScale3D(FVector(1.f));
	Damage = 0.f;
	Wallop = 0.f;
	TargetTag = FGameplayTag();
	SetActorLocation(FVector(10000.f, 10000.f, -1000.f));
	WeaponState = EWeaponState::Reclaim;
	UTD_KismetSystemLibrary::ClearTimerHandle(this, TimerHandle);
}

void ATD_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ATD_WeaponBase::BeginOverlap);
}

void ATD_WeaponBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TargetTag.GetTagName()))
	{
		ATD_Enemy* Enemy = Cast<ATD_Enemy>(OtherActor);
		Enemy->HitEffect(Damage, Wallop);
	}
}
