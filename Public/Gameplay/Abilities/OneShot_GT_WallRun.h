// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "OneShot/Public/Character/OneShotPlayerCharacter.h"
#include "OneShot_GT_WallRun.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWallRunActionDelegate);

/**
 * Repeatedly check character's stamina and perform the wall run action
 */
UCLASS()
class ONESHOT_API UOneShot_GT_WallRun : public UAbilityTask
{
	GENERATED_BODY()


public:
	
	UPROPERTY(BlueprintAssignable)
	FWallRunActionDelegate OnFinished;
	
	UFUNCTION(BlueprintCallable, Category= "Ability|Tasks", meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UOneShot_GT_WallRun* WallRun(UGameplayAbility* OwningAbility, float Interval, FVector Rotation, float Speed);
	virtual void Activate() override;

protected:
	
	FTimerHandle TimerHandle;
	
	float checkInterval;
	
	FVector WallRotation;

	float MaxRunningSpeed;

	AOneShotPlayerCharacter* PlayerCharacter;

	void PerformWallRun();
	
	virtual void OnDestroy(bool bInOwnerFinished) override;
	
};
