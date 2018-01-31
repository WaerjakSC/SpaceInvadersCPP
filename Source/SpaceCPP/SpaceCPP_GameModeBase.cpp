// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceCPP_GameModeBase.h"
#include "Public/UMG.h"
#include "Slate.h"
#include "Invader.h"
#include "Public/TimerManager.h"
#include "Engine/World.h"
#include "CharPawn.h"


ASpaceCPP_GameModeBase::ASpaceCPP_GameModeBase()
{
	UPROPERTY(EditAnywhere)
		DefaultPawnClass = ACharPawn::StaticClass();
}

void ASpaceCPP_GameModeBase::BeginPlay() {

	UWorld * const World = GetWorld();
	if (World)
	{
		for (int j{ 0 }; j < 2; j++)
		{
			for (int i{ 1 }; i < 9; i++)
			{
				FVector Location = FVector((FirstSpawnLocation.X - j * DistanceBetweenEnemies), (FirstSpawnLocation.Y + i * DistanceBetweenWaves), 70.f);
				World->SpawnActor<AInvader>(Invader, Location, FRotator::ZeroRotator);
				NumEnemies++;
			}
		}

	}
	GetWorldTimerManager().SetTimer(SpawnStagger, this, &ASpaceCPP_GameModeBase::RepeatingFunction, 15.0f, true, 15.0f);
}
void ASpaceCPP_GameModeBase::RepeatingFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("Timer triggered"))
		if (--RepeatingCallsRemaining <= 0)
		{
			GetWorldTimerManager().ClearTimer(SpawnStagger);
			UE_LOG(LogTemp, Warning, TEXT("Timer cleared."))
		}
	UWorld * const World = GetWorld();
	if (World)
	{
		for (int j{ 0 }; j < 2; j++)
		{
			for (int i{ 1 }; i < 9; i++)
			{
				FVector Location = FVector((FirstSpawnLocation.X - j * DistanceBetweenEnemies), (FirstSpawnLocation.Y + i * DistanceBetweenWaves), 70.f);
				World->SpawnActor<AInvader>(Invader, Location, FRotator::ZeroRotator);
				NumEnemies++;
			}
		}

	}
}
