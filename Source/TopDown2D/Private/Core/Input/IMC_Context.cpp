// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Input/IMC_Context.h"

#include "Base/Input/IA/IA_Base.h"

void UIMC_Context::InitMove(UIA_Base* MoveIA)
{
	UInputModifierSwizzleAxis* SwizzleAxisYXZ = NewObject<UInputModifierSwizzleAxis>(this, "SwizzleAxisYXZ");
	SwizzleAxisYXZ->Order = EInputAxisSwizzle::YXZ;

	UInputModifier* Negate = NewObject<UInputModifierNegate>(this, "Negate");
	
	FEnhancedActionKeyMapping Move_D = FEnhancedActionKeyMapping(MoveIA, EKeys::D); // 绑定D键
	Mappings.Add(Move_D);
	
	FEnhancedActionKeyMapping Move_A = FEnhancedActionKeyMapping(MoveIA, EKeys::A); // 绑定A键
	Move_A.Modifiers.Add(Negate);
	Mappings.Add(Move_A);
	
	FEnhancedActionKeyMapping Move_W = FEnhancedActionKeyMapping(MoveIA, EKeys::W); // 绑定W键
	Move_W.Modifiers.Add(SwizzleAxisYXZ);
	Move_W.Modifiers.Add(Negate);
	Mappings.Add(Move_W);

	FEnhancedActionKeyMapping Move_S = FEnhancedActionKeyMapping(MoveIA, EKeys::S); // 绑定W
	Move_S.Modifiers.Add(SwizzleAxisYXZ);
	Mappings.Add(Move_S);
}

void UIMC_Context::AddMappings(UIA_Base* BaseIA, const FKey InKey)
{
	FEnhancedActionKeyMapping BaseKey = FEnhancedActionKeyMapping(BaseIA, InKey); // 绑定D键
	Mappings.Add(BaseKey);
}

