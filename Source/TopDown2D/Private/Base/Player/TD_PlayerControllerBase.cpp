// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Player/TD_PlayerControllerBase.h"
#include "Core/Input/IMC_Context.h"
#include "Base/Input/IA/IA_Base.h"
#include "EnhancedInputSubsystems.h"
#include "Base/Character/TD_CharacterBase.h"
#include "Base/Character/Weapon/TD_WeaponManage.h"
#include "Base/Input/TD_InputComponent.h"
#include "Core/TD_GameplayTags.h"
#include "Core/TD_KismetSystemLibrary.h"
#include "Core/Game/TD_GameInstance.h"

void ATD_PlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	check(ContextIMC); // 断言 输入映射

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(ContextIMC, 0);
	}
}

void ATD_PlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	UTD_InputComponent* TD_InputComponent = CastChecked<UTD_InputComponent>(InputComponent);
	TD_InputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &ATD_PlayerControllerBase::Move);
	TD_InputComponent->BindAction(ShootIA, ETriggerEvent::Started, this, &ATD_PlayerControllerBase::Shoot);
}

void ATD_PlayerControllerBase::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	ATD_CharacterBase* TD_CharacterBase = Cast<ATD_CharacterBase>(GetCharacter());
	TD_CharacterBase->XDirection = InputAxisVector.X;
	TD_CharacterBase->YDirection = InputAxisVector.Y;
	const FRotator Rotator = GetControlRotation(); // 获取控制器旋转
	const FRotator YawRotator(0.f, Rotator.Yaw, 0.f); // 平面 只需要Yaw轴

	FVector ForwardDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X); // 计算前后朝向
	FVector RightDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y); // 计算左右朝向

	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection, TD_CharacterBase->XDirection); // 前后移动 基于X轴
		ControllerPawn->AddMovementInput(RightDirection, TD_CharacterBase->YDirection); // 左右移动 基于Y轴
	}
}

void ATD_PlayerControllerBase::Shoot(const FInputActionValue& Value)
{
	UTD_GameInstance* Instance = UTD_KismetSystemLibrary::GetGameInstance(this);
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	FVector ActorLocation = GetPawn()->GetActorLocation();
	// 计算 角色位置->鼠标点击位置 的速度向量
	const FVector Velocity = FRotator(
		0.f, FRotationMatrix::MakeFromX(CursorHit.Location - ActorLocation).Rotator().Yaw, 0.f).Vector() * 200.f;
	Instance->TD_WeaponManage->SetWeapons(ShuriKen, 5.f, Velocity, FVector(1.f), FVector(1.f),
	                                      ActorLocation, FTD_GameplayTags::Get().CharacterEnemy, 1.f);
}
