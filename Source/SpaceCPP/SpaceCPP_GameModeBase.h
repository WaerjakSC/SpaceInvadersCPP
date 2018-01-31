// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceCPP_GameModeBase.generated.h"

/**
 *
 */
UCLASS()
class SPACECPP_API ASpaceCPP_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASpaceCPP_GameModeBase();


	UPROPERTY(BlueprintReadWrite, Category = "HUD")
		int NumEnemies;

	int RepeatingCallsRemaining = 2;

	FTimerHandle SpawnStagger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		TSubclassOf<class AInvader> Invader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		FVector2D FirstSpawnLocation = FVector2D(1500.f, -1450.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float DistanceBetweenWaves = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float DistanceBetweenEnemies = 300.f;

	void RepeatingFunction();

protected:
	virtual void BeginPlay() override;

};
