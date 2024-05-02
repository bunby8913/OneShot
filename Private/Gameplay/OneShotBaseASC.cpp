// Fill out your copyright notice in the Description page of Project Settings.


#include "OneShot/Public/Gameplay/OneShotBaseASC.h"

#include "AbilitySystemGlobals.h"


UOneShotBaseASC* UOneShotBaseASC::GetAbilitySystemComponentFromActor(const AActor* Actor, bool bLookForComponent)
{
	return Cast<UOneShotBaseASC>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, bLookForComponent));
}
