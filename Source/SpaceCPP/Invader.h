// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Invader.generated.h"


UCLASS()
class SPACECPP_API AInvader : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AInvader();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* InvaderVisual;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector CurrentLocation;

	int TimerTick{ 1 };

	void RepeatingFunction();

	FTimerHandle MemberTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Variables")
		float Speed = 150.f;

	void DestroyEnemy();
};
