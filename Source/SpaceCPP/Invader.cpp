// Fill out your copyright notice in the Description page of Project Settings.

#include "Invader.h"
#include "SpaceCPP_GameModeBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UOBject/ConstructorHelpers.h"
#include "Public/TimerManager.h"
#include "Engine/World.h"



// Sets default values
AInvader::AInvader()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USphereComponent* InvaderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	InvaderComponent->InitSphereRadius(60.f);
	InvaderComponent->bGenerateOverlapEvents = true;
	RootComponent = InvaderComponent;

	InvaderVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Representation"));
	InvaderVisual->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInvader::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &AInvader::RepeatingFunction, 6.0f, true, 6.0f);
}

// Called every frame
void AInvader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentLocation = this->GetActorLocation();
	switch (TimerTick)
	{
	case 1:
		CurrentLocation.Y += Speed * DeltaTime;
		break;
	case 2:
		CurrentLocation.X -= (Speed * DeltaTime)/2;
		break;
	case 3:
		CurrentLocation.Y -= Speed * DeltaTime;
		break;
	case 4:
		CurrentLocation.X -= (Speed * DeltaTime) / 2;
		break;
	}
	SetActorLocation(CurrentLocation);
}

void AInvader::RepeatingFunction()
{
	switch (TimerTick)
	{
	case 1:
		TimerTick++;
		break;
	case 2:
		TimerTick++;
		break;
	case 3:
		TimerTick++;
		break;
	case 4:
		TimerTick = 1;
		break;
	}
}

void AInvader::DestroyEnemy()
{
	ASpaceCPP_GameModeBase* gameMode = Cast<ASpaceCPP_GameModeBase>(GetWorld()->GetAuthGameMode());
	gameMode->NumEnemies--;
	Destroy();
}