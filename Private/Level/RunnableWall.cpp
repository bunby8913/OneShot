// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/RunnableWall.h"

// Sets default values
ARunnableWall::ARunnableWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Wall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RunnableWall"));
	LaunchCount = InitialLaunchCount;

}

void ARunnableWall::SetLaunchCount(int32 UpdatedLaunchCount)
{
	LaunchCount = UpdatedLaunchCount;
	if (UpdatedLaunchCount == 0)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARunnableWall::ResetLaunchCount, LaunchCountResetInterval, false);
	}
}

// Called when the game starts or when spawned
void ARunnableWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARunnableWall::ResetLaunchCount()
{
	LaunchCount = InitialLaunchCount;
}

// Called every frame
void ARunnableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

