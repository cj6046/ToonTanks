// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"


void ATankGameModeBase::BeginPlay() 
{
    // Get reference && Game win/lose conditions

    // Call HandleGameStart() to begin countdown, turret activation, pawn check, etc.
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{
    // Check what type of actor died, respond accordingly
    UE_LOG(LogTemp, Warning, TEXT("A Pawn died."));
}

void ATankGameModeBase::HandleGameStart() 
{
    // Initialize the start countdown, turret activation, pawn check, etc.
    // Call Blueprint version of GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    // See if player has destroyed all turrets, show win result
    // else if turret destroyed player, show lose result 
    // Call Blueprint version of GameOver(bool);
}

