// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OneShotBaseCharacter.generated.h"

struct FGameplayTag;
class UOneShotBaseASC;
class UOneShotBaseAttributeSet;
class UOneShotBaseGameAbility;
class UGameplayEffect;

UCLASS()
class ONESHOT_API AOneShotBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOneShotBaseCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void UnPossessed() override;

	UFUNCTION(BlueprintCallable, Category= "Tag")
	void AddGameplayTag(FGameplayTag AddedTag);

	UFUNCTION(BlueprintCallable, Category= "Tag")
	void RemoveGameplayTag(FGameplayTag RemovedTag);

	UFUNCTION(BlueprintCallable, Category="Abilities")
	void GiveGameplayAbilityToCharacter(TSubclassOf<UOneShotBaseGameAbility> AbilityToGive, int32 PlayerInputId);

	UOneShotBaseASC* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable)
	UOneShotBaseAttributeSet* GetAttributeSet() const;
	
	void HandleHealthChange(float delta, const struct FGameplayTagContainer& TagContainer);

	void HandleStaminaChange(float delta, const struct FGameplayTagContainer& TagContainer);

protected:

	void AddStartupGameplayAbility();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void OnHealthChanged(float delta, const struct FGameplayTagContainer& TagContainer);

	UFUNCTION(BlueprintImplementableEvent)
		void OnStaminaChanged(float delta, const struct FGameplayTagContainer& TagContainer);
	UPROPERTY()
	UOneShotBaseAttributeSet* CharacterAttributeSet;

	UPROPERTY(BlueprintReadOnly)
	UOneShotBaseASC* CharacterASC;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UOneShotBaseGameAbility>> CharacterStartupGameAbilities;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> CharacterStartupGameplayEffect;

	
	UPROPERTY(BlueprintReadOnly)
	int32 CharacterLevel;

	bool bAbilitiesInitialized;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
