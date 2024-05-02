// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "OneShotBaseAttributeSet.generated.h"


// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) 

/**
 * 
 */
UCLASS()
class ONESHOT_API UOneShotBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	// Base attribute constructors
	UOneShotBaseAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Attribute")
		FGameplayAttributeData Health;
 		ATTRIBUTE_ACCESSORS(UOneShotBaseAttributeSet, Health)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Attirbute")
		FGameplayAttributeData MaxHealth;
		ATTRIBUTE_ACCESSORS(UOneShotBaseAttributeSet, MaxHealth);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Attribute")
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UOneShotBaseAttributeSet, Stamina)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Attribute")
		FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UOneShotBaseAttributeSet, MaxStamina)
	

	void AttributeAdjustForMaximumChange(FGameplayAttributeData& AffectedData, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttribute);

	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);
	
};
