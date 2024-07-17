// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Character/TD_Enemy.h"

#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Core/TD_GameplayTags.h"
#include "Core/TD_KismetSystemLibrary.h"
#include "Core/UI/Widget/DamageNumComponent.h"
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
	
	DamageComponentClass = UDamageNumComponent::StaticClass();
}

void ATD_Enemy::SetColor()
{ 
	Sprite->SetSpriteColor(FColor::White);
}

void ATD_Enemy::HitEffect(const float Damage)
{
	Sprite->SetSpriteColor(FColor::Red);
	UGameplayStatics::PlaySound2D(this, HitSound);

	ShowDamageNumber(Damage, false, false);
	
	UTD_KismetSystemLibrary::SetTimer(this, this, &ATD_Enemy::SetColor, 0.1);
}

void ATD_Enemy::ShowDamageNumber_Implementation(const float Damage, bool bBlockedHit, bool bCriticalHit)
{
	// 检查目标角色是否有效，是否有损坏组件类
	if (DamageComponentClass)
	{
		// 创建一个新的损坏数字组件，用于显示伤害效果
		UDamageNumComponent* DamageNum = NewObject<UDamageNumComponent>(this, DamageComponentClass);
		
		// 注册组件，使其成为有效的游戏对象
		DamageNum->RegisterComponent();
		
		// 将损坏数字组件附加到目标角色的根组件上，保持相对位置
		DamageNum->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		
		// 从目标角色的根组件上分离损坏数字组件，保持世界位置
		// 这一步可能是为了在显示完伤害数字后，将其从角色上移除，避免持续占用资源
		DamageNum->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		
		// 设置损坏数字的值，是否被阻挡以及是否为暴击
		// 这里将伤害值、是否被阻挡和是否为暴击的信息传递给损坏数字组件，用于正确显示伤害效果
		DamageNum->SetDamageNum(Damage, bBlockedHit, bCriticalHit);
	}
}
