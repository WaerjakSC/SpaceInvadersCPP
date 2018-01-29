// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "CharPawn.h"
#include "Invader.h"
#include "SpaceCPP_GameModeBase.h"
#include "GameFrameWork/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"



// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USphereComponent* BulletComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	BulletComponent->InitSphereRadius(40.0f);
	RootComponent = BulletComponent;
	BulletComponent->bGenerateOverlapEvents = true;
	BulletComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);


	BulletVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Representation"));
	BulletVisual->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeAlive += DeltaTime;

	if (TimeAlive > TimeToKill)
	{
		Destroy();
	}

}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(AInvader::StaticClass()))
	{
		Cast<AInvader>(OtherActor)->DestroyEnemy();
		Destroy();
	}
}
