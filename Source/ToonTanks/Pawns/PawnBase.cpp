// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void APawnBase::RotateTurret(FVector LookAtTarget) 
{
	// Update TurretMesh to face LookAtTarget passed from Child classes
	FVector LookAtTargetCleaned = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = FVector(TurretMesh->GetComponentLocation());

	FRotator TurretRotation = FVector(LookAtTargetCleaned - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire() 
{
	// Get ProjectileSpawnPoint location && Rotation - > Spawn projectile class at location facing rotation
	if(ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this); 
	}
}

void APawnBase::HandleDestruction() 
{
	// -- Universal Functionality --
	// Play death effects particle, sound, and camera shake

	// -- Child Overrides --
	//		-- PawnTurret: Inform GameMode Turret died, then Destroy() self
	//		-- PawnTank: Inform GameMode Player died, then Hide() components && stop movement input
}


