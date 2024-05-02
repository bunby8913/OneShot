// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RunnableWall.generated.h"

UCLASS()
class ONESHOT_API ARunnableWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARunnableWall();

	int32 GetLaunchCount() const {return LaunchCount;};

	void SetLaunchCount(int32 UpdatedLaunchCount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ResetLaunchCount();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Wall;
	
	UPROPERTY(EditAnywhere)
	int32 InitialLaunchCount = 1;

	UPROPERTY(EditAnywhere)
	float LaunchCountResetInterval = 10.f;

	int32 LaunchCount;
	
	FTimerHandle TimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
