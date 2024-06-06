// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/OneShotRegularProjectile.h"


AOneShotRegularProjectile::AOneShotRegularProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(CollisionSphereSize);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AOneShotBaseProjectile::OnHit);

	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = ProjectileSpeed;
	ProjectileMovement->MaxSpeed = ProjectileSpeed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	InitialLifeSpan = ProjectileLifeSpan;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileStaticMechsComponent"));
	ProjectileMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

void AOneShotRegularProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Set the static mesh for the static mesh component on begin play
	if (ProjectileMeshComponent)
	{
		UStaticMesh* StaticMesh = ProjectileMesh.GetDefaultObject();
		if (StaticMesh)
		{
			ProjectileMeshComponent->SetStaticMesh(StaticMesh);
		}
	}
	
}
