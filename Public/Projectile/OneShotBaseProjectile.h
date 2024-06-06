// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "OneShotBaseProjectile.generated.h"


UCLASS(Config=Game)
class ONESHOT_API AOneShotBaseProjectile : public AActor
{
	GENERATED_BODY()
	
protected:
	
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, Category=Projectle)
	UStaticMeshComponent* ProjectileMeshComponent;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category=Movement)
	float ProjectileSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category= Mesh)
	TSubclassOf<UStaticMesh> ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, Category= Mesh)
	float CollisionSphereSize = 3.f;

	UPROPERTY(EditDefaultsOnly, Category= Mesh)
	float ProjectileLifeSpan = 2.f;
	
public:
	// Sets default values for this actor's properties
	AOneShotBaseProjectile();

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	/** called when projectile hits something */
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
