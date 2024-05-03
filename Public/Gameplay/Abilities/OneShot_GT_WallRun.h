// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "OneShot_GT_WallRun.generated.h"

class AOneShotPlayerCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWallRunActionDelegate);

/**
 * Repeatedly check character's stamina and perform and update player velocity
 */
UCLASS()
class ONESHOT_API UOneShot_GT_WallRun : public UAbilityTask
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FWallRunActionDelegate OnFinished;
	
	UFUNCTION(BlueprintCallable, Category= "Ability|Tasks", meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UOneShot_GT_WallRun* WallRun(UGameplayAbility* OwningAbility, float Interval, FVector Rotation, float Speed, FGameplayTagContainer TagContainer);
	
	virtual void Activate() override;

protected:
	void PerformWallRun();
	
	virtual void OnDestroy(bool bInOwnerFinished) override;
	
	FTimerHandle TimerHandle;
	
	float checkInterval;
	
	float MaxRunningSpeed;
	
	FVector WallRotation;

	FGameplayTagContainer AbilityTagContainer;

	AOneShotPlayerCharacter* PlayerCharacter;

	// Used to determine which direction is the player approaching the wall, adjust velocity accordingly
	int32 DirectionFactor = 1;
	
	
};
