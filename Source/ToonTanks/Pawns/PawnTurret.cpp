// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

//called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction() 
{
    // Call PawnBase HandleDestruction to play effects, the return here to do override functionality
    Super::HandleDestruction();
    Destroy();
}

//called every frame
void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(!PlayerPawn || ReturnDistanceToTarget() > FireRange)
    {
        return;
    }

    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
    // if Player == null || isDead then HOLD
    if(!PlayerPawn)
    {
        return;
    }
    // if Player is in range FIRE!
    if(ReturnDistanceToTarget() <= FireRange)
    {
        Fire();
    }
}

float APawnTurret::ReturnDistanceToTarget()
{
    if(!PlayerPawn)
    {
        return 0.0f;
    }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}