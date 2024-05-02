// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OneShotPlayerCharacter.h"
#include "OneShot/OneShotProjectile.h"
#include "camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "OneShot/Public/Gameplay/Abilities/OneShot_GA_WallRun.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/OneShotBaseASC.h"
#include "Kismet/GameplayStatics.h"
#include "Level/RunnableWall.h"

DEFINE_LOG_CATEGORY(LogOneShotPlayerCharacter)

AOneShotPlayerCharacter::AOneShotPlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCameraComponent->SetupAttachment(GetCapsuleComponent());
	PlayerCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	PlayerCameraComponent->bUsePawnControlRotation = true;

	ArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmMesh"));
	ArmMesh->SetOnlyOwnerSee(true);
	ArmMesh->SetupAttachment(PlayerCameraComponent);
	ArmMesh->bCastDynamicShadow = false;
	ArmMesh->CastShadow = false;
	ArmMesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void AOneShotPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AOneShotPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookaxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookaxisVector.X);
		AddControllerPitchInput(LookaxisVector.Y);
	}
}


bool AOneShotPlayerCharacter::EndAbilityWithTag(FName AbilityTag)
{
	if (GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(AbilityTag)))
	{
		FGameplayTagContainer TagToCancelAbilities = FGameplayTagContainer(FGameplayTag::RequestGameplayTag(AbilityTag));
		GetAbilitySystemComponent()->CancelAbilities(&TagToCancelAbilities);
		return true;
	}
	return false;
}

void AOneShotPlayerCharacter::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire ability triggered"))
}

void AOneShotPlayerCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	if (PrevMovementMode == MOVE_Falling)
	{
		GetCharacterMovement()->GravityScale = 1.f;
	}
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
}

void AOneShotPlayerCharacter::Jump()
{
	if (EndAbilityWithTag(TEXT("OneShot.Abilities.WallRunning")))
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARunnableWall::StaticClass(), FoundActors);
		float ActorDistance;
		AActor* NearestActor = UGameplayStatics::FindNearestActor(GetActorLocation(), FoundActors, ActorDistance);
		ARunnableWall* NearestWall = Cast<ARunnableWall>(NearestActor);
		if (NearestWall->GetLaunchCount() > 0)
		{
			FVector LaunchVector = PlayerCameraComponent->GetComponentRotation().Vector();
			LaunchVector.Z = LaunchAngle;
			LaunchVector *= LaunchDistance;
			GetCharacterMovement()->Velocity = FVector::ZeroVector;
			LaunchCharacter(LaunchVector, false, false);
			NearestWall->SetLaunchCount(NearestWall->GetLaunchCount() - 1);
		}
	}
	Super::Jump();
}

void AOneShotPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AOneShotPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOneShotPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOneShotPlayerCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
	else
	{
		UE_LOG(LogOneShotPlayerCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}
