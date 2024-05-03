// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Abilities/OneShot_GT_WallRun.h"

#include "Character/OneShotPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/OneShotBaseASC.h"
#include "Gameplay/OneShotBaseAttributeSet.h"
#include "Gameplay/OneShotBaseGameAbility.h"

UOneShot_GT_WallRun* UOneShot_GT_WallRun::WallRun(UGameplayAbility* OwningAbility, const float Interval, const FVector Rotation, const float Speed, FGameplayTagContainer TagContainer)
{
	UOneShot_GT_WallRun* MyObj = NewAbilityTask<UOneShot_GT_WallRun>(OwningAbility);
	MyObj->checkInterval = Interval;
	MyObj->PlayerCharacter= Cast<AOneShotPlayerCharacter>(OwningAbility->GetOwningActorFromActorInfo());
	MyObj->WallRotation = Rotation;
	MyObj->MaxRunningSpeed = Speed;
	MyObj->AbilityTagContainer = TagContainer;
	return MyObj;
}

void UOneShot_GT_WallRun::Activate()
{
	Super::Activate();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOneShot_GT_WallRun::PerformWallRun, checkInterval, true);
}

void UOneShot_GT_WallRun::PerformWallRun()
{
	if (PlayerCharacter->IsValidLowLevelFast())
	{
		
		FVector PlayerInput = PlayerCharacter->GetLastMovementInputVector();
		FRotator PlayerRotation = PlayerCharacter->GetActorRotation();
		FVector PlayerInputLocal = PlayerRotation.UnrotateVector(PlayerInput);
		
		if (PlayerCharacter->GetAttributeSet()->GetStamina() > 0.f && PlayerInputLocal.X > 0.9 && PlayerInputLocal.Y < 0.1 && PlayerCharacter->GetAbilitySystemComponent()->HasAnyMatchingGameplayTags(AbilityTagContainer))
		{
			FVector CurrentVelocity = PlayerCharacter->GetCharacterMovement()->Velocity;
			PlayerCharacter->GetCharacterMovement()->Velocity = FVector(FMath::Clamp(CurrentVelocity.X * 1.1f, 0 - MaxRunningSpeed, MaxRunningSpeed), FMath::Clamp(CurrentVelocity.Y * 1.1f, 0 - MaxRunningSpeed, MaxRunningSpeed), FMath::Max(CurrentVelocity.Z, -200.f));
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			OnFinished.Broadcast();
		}
	}
	
}

void UOneShot_GT_WallRun::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}
