// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Character/OneShotBaseCharacter.h"
#include "Logging/LogMacros.h"
#include "OneShotPlayerCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UUserWidget;


DECLARE_LOG_CATEGORY_EXTERN(LogOneShotPlayerCharacter, Log, All);

/**
 * 
 */
UCLASS()
class ONESHOT_API AOneShotPlayerCharacter : public AOneShotBaseCharacter
{
	GENERATED_BODY()

public:
	AOneShotPlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Input", meta=(AllowPrivateAccess = "True"))
	class UInputAction* LookAction;

	USkeletalMeshComponent* GetPlayerMesh() const {return ArmMesh;};
	UCameraComponent* GetPlayerCameraComponent() const {return PlayerCameraComponent;};

	/* If there is a gameplay ability has the abilityTag, cancel the ability and return true, if the ability not found, return false*/
	UFUNCTION(BlueprintCallable)
	bool EndAbilityWithTag(FGameplayTag AbilityTag);

	void Fire();
	
	virtual void Jump() override;
	
protected:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);


protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh", meta=(AllowPrivateAccess = "True"))
	USkeletalMeshComponent* ArmMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh", meta=(AllowPrivateAccess = "True"))
	UCameraComponent* PlayerCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "True"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "True"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere)
	float LaunchDistance = 5000.f;

	UPROPERTY(EditAnywhere)
	float LaunchAngle = 1.f;

	UPROPERTY( EditAnywhere, Category= "UI")
	TSubclassOf<UUserWidget> PlayerMainWidgetClass;

	UPROPERTY()
	UUserWidget* PlayerMainWidget;

};
