// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/Widget/UI_Damage.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/SizeBoxSlot.h"
#include "Components/TextBlock.h"


UUI_Damage::UUI_Damage()
{
	DesignSizeMode = EDesignPreviewSizeMode::Desired;
}

void UUI_Damage::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(DamageAnim);
}

void UUI_Damage::NativePreConstruct()
{
	Super::NativePreConstruct();

	SizeBoxRoot->SetWidthOverride(100.f);
	SizeBoxRoot->SetHeightOverride(40.f);

	USizeBoxSlot* DamageNumSlot = Cast<USizeBoxSlot>(DamageNum->Slot);
	DamageNumSlot->SetHorizontalAlignment(HAlign_Center);
	DamageNumSlot->SetVerticalAlignment(VAlign_Center);
}

FSlateColor UUI_Damage::GetColorBasedOnBlockAndCrit(bool bBlockedHit, bool bCriticalHit)
{
	// 根据攻击情况确定返回的UI颜色
	if (bBlockedHit && !bCriticalHit)
	{
		// 当攻击被阻挡且不是致命打击时，返回蓝色
		FSlateColor SlateColor(FLinearColor::Blue);
		return SlateColor;
	}
	if (bCriticalHit && !bBlockedHit)
	{
		// 当攻击是致命打击且没有被阻挡时，返回红色
		FSlateColor SlateColor(FLinearColor::Red);
		return SlateColor;
	}
	if (bCriticalHit && bBlockedHit)
	{
		// 当攻击是致命打击且被阻挡时，返回黄色
		FSlateColor SlateColor(FLinearColor::Yellow);
		return SlateColor;
	}

	// 默认情况下，当攻击既不是致命打击也没有被阻挡时，返回白色
	FSlateColor SlateColor(FLinearColor::White);
	return SlateColor;
}

FSlateFontInfo UUI_Damage::GetFontOnBlockAndCrit(bool bBlockedHit, bool bCriticalHit) const
{
	// 初始化字体信息，用于后续根据不同的命中情况调整字体大小
	FSlateFontInfo FontInfo = DamageNum->GetFont();
	
	// 如果是被阻挡的非暴击伤害，增加字体大小的倍率为1.2
	if (bBlockedHit && !bCriticalHit)
	{
	    FontInfo.Size *= 1.2;
	    return FontInfo;
	}
	
	// 如果是暴击但未被阻挡的伤害，增加字体大小的倍率为2
	if (bCriticalHit && !bBlockedHit)
	{
	    FontInfo.Size *= 2;
	    return FontInfo;
	}
	
	// 如果同时是暴击且被阻挡的伤害，增加字体大小的倍率为1.5
	if (bCriticalHit && bBlockedHit)
	{
	    FontInfo.Size *= 1.5;
	    return FontInfo;
	}
	
	// 如果以上条件都不满足，返回原始的字体信息
	return FontInfo;
}

void UUI_Damage::SetDamageNum(const float Damage, bool bBlockedHit, bool bCriticalHit) const
{
	// 根据是否阻挡和是否暴击，获取文本颜色
	FSlateColor TextColor = GetColorBasedOnBlockAndCrit(bBlockedHit, bCriticalHit);
	// 设置伤害数字的颜色和不透明度
	DamageNum->SetColorAndOpacity(TextColor);
	
	// 根据是否阻挡和是否暴击，获取字体信息
	FSlateFontInfo FontInfo = GetFontOnBlockAndCrit(bBlockedHit, bCriticalHit);
	// 设置伤害数字的字体
	DamageNum->SetFont(FontInfo);
	
	// 设置伤害数字的文本为计算后的伤害值
	// 使用FText::AsNumber将伤害值转换为文本，并四舍五入到最接近的整数
	DamageNum->SetText(FText::AsNumber(FMath::RoundToInt(Damage)));
}
