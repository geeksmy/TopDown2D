// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UI/TD_UserWidgetBase.h"
#include "UI_Damage.generated.h"

class UTextBlock;
class USizeBox;
/**
 * 伤害显示UI
 */
UCLASS()
class TOPDOWN2D_API UUI_Damage : public UTD_UserWidgetBase
{
	GENERATED_BODY()

	UUI_Damage();

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	/**
	 * 根据招架和暴击状态获取颜色。
	 * 
	 * 此函数根据招架（bBlockedHit）和暴击（bCriticalHit）的状态，返回一个相应的颜色。
	 * 主要用于UI中对不同战斗事件的视觉区分。
	 * 
	 * @param bBlockedHit 招架状态，true表示招架成功，false表示未招架。
	 * @param bCriticalHit 暴击状态，true表示暴击，false表示未暴击。
	 * @return FSlateColor 返回根据招架和暴击状态计算得到的颜色。
	 */
	static FSlateColor GetColorBasedOnBlockAndCrit(bool bBlockedHit, bool bCriticalHit);

	/**
	 * 根据招架和暴击状态获取字体信息。
	 * 
	 * 此函数根据招架（bBlockedHit）和暴击（bCriticalHit）的状态，返回一个相应的字体信息。
	 * 字体信息包括字体本身及其颜色，主要用于UI中对不同战斗事件的文字展示。
	 * 
	 * @param bBlockedHit 招架状态，true表示招架成功，false表示未招架。
	 * @param bCriticalHit 暴击状态，true表示暴击，false表示未暴击。
	 * @return FSlateFontInfo 返回根据招架和暴击状态计算得到的字体信息。
	 */
	FSlateFontInfo GetFontOnBlockAndCrit(bool bBlockedHit, bool bCriticalHit) const;

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBoxRoot;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DamageNum;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> DamageAnim;

public:
	/**
	 * 设置伤害数值及相关属性
	 * 
	 * 本函数用于在对象上设置伤害数值，同时考虑了伤害是否被阻挡以及是否为暴击的情况。
	 * 这对于计算实际造成的伤害以及根据伤害类型进行相应的逻辑处理非常有用。
	 * 
	 * @param Damage 造成的伤害数值。
	 * @param bBlockedHit 表示伤害是否被阻挡。如果为真，则表示伤害被阻挡，可能需要进一步处理。
	 * @param bCriticalHit 表示伤害是否为暴击。如果为真，则表示此次伤害为暴击，可能需要根据暴击规则计算伤害。
	 */
	void SetDamageNum(const float Damage, bool bBlockedHit, bool bCriticalHit) const;
};
