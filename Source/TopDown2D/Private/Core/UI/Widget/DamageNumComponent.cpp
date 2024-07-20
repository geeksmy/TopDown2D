// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/Widget/DamageNumComponent.h"

#include "Core/TD_KismetSystemLibrary.h"
#include "Core/UI/Widget/UI_Damage.h"


UDamageNumComponent::UDamageNumComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<UUI_Damage> DamageWidget_Class(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BP/UI/WBP_Damage.WBP_Damage_C'"));
	if (DamageWidget_Class.Succeeded())
	{
		SetWidgetClass(DamageWidget_Class.Class);
	}
	// 设置窗口空间为屏幕空间
	Space = EWidgetSpace::Screen;

}

void UDamageNumComponent::SetDamageNum(const float Damage, bool bBlockedHit, bool bCriticalHit)
{
	UUI_Damage* DamageWidget = Cast<UUI_Damage>(GetWidget());
	DamageWidget->SetDamageNum(Damage, bBlockedHit, bCriticalHit);

	// 自动销毁
	TimerHandle = UTD_KismetSystemLibrary::SetTimer(this, this, &UDamageNumComponent::DestroyCom, 0.6, false);
}

void UDamageNumComponent::DestroyCom()
{
	UTD_KismetSystemLibrary::ClearTimerHandle(this, TimerHandle);
	DestroyComponent();
}

