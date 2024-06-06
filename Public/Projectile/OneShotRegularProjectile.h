// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/OneShotBaseProjectile.h"
#include "OneShotRegularProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ONESHOT_API AOneShotRegularProjectile : public AOneShotBaseProjectile
{
	GENERATED_BODY()

public:
	AOneShotRegularProjectile();

	virtual void BeginPlay() override;
};
