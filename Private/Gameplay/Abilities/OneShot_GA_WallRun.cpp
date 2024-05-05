// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Abilities/OneShot_GA_WallRun.h"

#include "Character/OneShotPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/OneShotBaseASC.h"
#include "Gameplay/OneShotBaseAttributeSet.h"
#include "Gameplay/Abilities/OneShot_GT_WallRun.h"
#include "Kismet/GameplayStatics.h"
#include "Level/RunnableWall.h"


bool UOneShot_GA_WallRun::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                             const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UOneShot_GA_WallRun::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		PlayerCharacter = CastChecked<AOneShotPlayerCharacter>(ActorInfo->AvatarActor.Get());
		if(CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARunnableWall::StaticClass(), FoundActors);
			float ActorDistance;
			AActor* NearestWall = UGameplayStatics::FindNearestActor(PlayerCharacter->GetActorLocation(), FoundActors, ActorDistance);

			FVector NearestWallRotation = NearestWall->GetActorRotation().Vector();

			PlayerCharacter->GetCharacterMovement()->GravityScale = WallRunGravityScale;
			UOneShotBaseASC* AbilitySystemComponent = PlayerCharacter->GetAbilitySystemComponent();
			FGameplayTagContainer WallRunningTag = AbilityTags;
			// Interval can be adjusted for optimization
			UOneShot_GT_WallRun* WallRunTask = UOneShot_GT_WallRun::WallRun(this, 0.05f, NearestWallRotation, MaxRunningSpeed, WallRunningTag);
			WallRunTask->OnFinished.AddDynamic(this, &UOneShot_GA_WallRun::OnAbilityFinished);
			WallRunTask->ReadyForActivation();
		}
	}
}

void UOneShot_GA_WallRun::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void UOneShot_GA_WallRun::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UOneShot_GA_WallRun::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	PlayerCharacter->GetCharacterMovement()->GravityScale = 1.f;
	
	UOneShotBaseASC* ASC = PlayerCharacter->GetAbilitySystemComponent();
	if (ASC)
	{
		PlayerCharacter->RemoveGameplayTag(FGameplayTag::RequestGameplayTag(TEXT("OneShot.Abilities.Cost.WallRun")));
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UOneShot_GA_WallRun::OnAbilityFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}