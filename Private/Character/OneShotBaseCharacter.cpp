// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OneShotBaseCharacter.h"
#include "UObject/ScriptInterface.h"
#include "GameplayEffect.h"
#include "OneShot/Public/Gameplay/OneShotBaseAttributeSet.h"
#include "OneShot/Public/Gameplay/OneShotBaseASC.h"
#include "OneShot/Public/Gameplay/OneShotBaseGameAbility.h"
#include "GameplayTags.h"

// Sets default values
AOneShotBaseCharacter::AOneShotBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CharacterAttributeSet = CreateDefaultSubobject<UOneShotBaseAttributeSet>(TEXT("AttributeSet"));
	CharacterASC = CreateDefaultSubobject<UOneShotBaseASC>(TEXT("AbilitySystemComponent"));
	CharacterLevel = 1;
}

void AOneShotBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AddStartupGameplayAbility();
}

void AOneShotBaseCharacter::UnPossessed()
{
	Super::UnPossessed();
}

void AOneShotBaseCharacter::AddGameplayTag(FGameplayTag AddedTag)
{  
	CharacterASC->AddLooseGameplayTag(AddedTag);
}

void AOneShotBaseCharacter::RemoveGameplayTag(FGameplayTag RemovedTag)
{
	CharacterASC->RemoveLooseGameplayTag(RemovedTag);
}

void AOneShotBaseCharacter::GiveGameplayAbilityToCharacter(TSubclassOf<UOneShotBaseGameAbility> AbilityToGive,
	int32 PlayerInputId)
{
	CharacterASC->GiveAbility(FGameplayAbilitySpec(AbilityToGive, CharacterLevel, PlayerInputId));
}

UOneShotBaseASC* AOneShotBaseCharacter::GetAbilitySystemComponent() const
{
	return CharacterASC;
}

UOneShotBaseAttributeSet* AOneShotBaseCharacter::GetAttributeSet() const
{
	return CharacterAttributeSet;
}

void AOneShotBaseCharacter::HandleHealthChange(float delta, const FGameplayTagContainer& TagContainer)
{
	OnHealthChanged(delta, TagContainer);
}

void AOneShotBaseCharacter::HandleStaminaChange(float delta, const FGameplayTagContainer& TagContainer)
{
	OnStaminaChanged(delta, TagContainer);
}

void AOneShotBaseCharacter::AddStartupGameplayAbility()
{
	check(CharacterASC)

	if(!bAbilitiesInitialized)
	{
		for (int32 Id = 0; Id != CharacterStartupGameAbilities.Num(); ++Id)
		{
			CharacterASC->GiveAbility(FGameplayAbilitySpec(CharacterStartupGameAbilities[Id], CharacterLevel, Id, this));
		}
		for (TSubclassOf<UGameplayEffect>& GameplayEffect : CharacterStartupGameplayEffect)
		{
			FGameplayEffectContextHandle EffectContextHandle = CharacterASC->MakeEffectContext();
			EffectContextHandle.AddSourceObject(this);

			FGameplayEffectSpecHandle EffectSpecHandle = CharacterASC->MakeOutgoingSpec(GameplayEffect, CharacterLevel, EffectContextHandle);

			if (EffectSpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActivateGEHandle = CharacterASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			}
		}
	}
}

// Called when the game starts or when spawned
void AOneShotBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOneShotBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOneShotBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

