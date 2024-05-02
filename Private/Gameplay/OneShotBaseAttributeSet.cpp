// Fill out your copyright notice in the Description page of Project Settings.


#include "OneShot/Public/Gameplay/OneShotBaseAttributeSet.h"

#include "AbilitySystemComponent.h"


UOneShotBaseAttributeSet::UOneShotBaseAttributeSet():
Health(100.f),
Stamina(100.f),
MaxHealth(100.f),
MaxStamina(100.f)
{}

void UOneShotBaseAttributeSet::AttributeAdjustForMaximumChange(FGameplayAttributeData& AffectedData,
	const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttribute)
{
	const float currentMaxValue = MaxAttribute.GetCurrentValue();
	UAbilitySystemComponent* CharacterASC = GetOwningAbilitySystemComponent();

	if(CharacterASC)
	{
		const float CurrentValue = AffectedData.GetCurrentValue();
		float deltaValue = (CurrentValue > 0) ? (NewMaxValue / currentMaxValue * CurrentValue) : NewMaxValue;

		CharacterASC->ApplyModToAttributeUnsafe(AffectedAttribute, EGameplayModOp::Additive, deltaValue);
	}
}

void UOneShotBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute.GetName() == "Health")
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute.GetName() == "Stamina")
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}
	else if (Attribute.GetName() == "MaxHealth")
	{
		AttributeAdjustForMaximumChange(Health, MaxHealth, NewValue, Attribute);
	}
	else if (Attribute.GetName() == "MaxStamina")
	{
		AttributeAdjustForMaximumChange(Stamina, MaxStamina, NewValue, Attribute);
	}
	
	Super::PreAttributeChange(Attribute, NewValue);
}


void UOneShotBaseAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOneShotBaseAttributeSet, Health, OldHealth);
}

void UOneShotBaseAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOneShotBaseAttributeSet, Stamina, OldStamina);
}
