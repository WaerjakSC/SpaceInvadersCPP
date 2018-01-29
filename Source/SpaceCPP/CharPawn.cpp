// Fill out your copyright notice in the Description page of Project Settings.

#include "CharPawn.h"
#include "Bullet.h"
#include "Invader.h"
#include "CharMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
ACharPawn::ACharPawn()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCapsuleComponent* CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComponent"));
	CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
	RootComponent = CapsuleComponent;
	//CapsuleComponent->BodyInstance.SetCollisionProfileName("SpaceInvader");
	CapsuleComponent->bGenerateOverlapEvents = true;
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ACharPawn::OnOverlap);


	CharacterVisual = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Visual Representation"));
	CharacterVisual->SetupAttachment(RootComponent);
	

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MyMovementComponent = CreateDefaultSubobject<UCharMovementComponent>(TEXT("CustomMovementComponent"));
	MyMovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void ACharPawn::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ACharPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		if (!MovementInput.IsZero())
		{
			MovementInput = MovementInput.GetSafeNormal() * 600.0f;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}
}

UPawnMovementComponent* ACharPawn::GetMovementComponent() const {
	return MyMovementComponent;
}
void ACharPawn::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);

}

void ACharPawn::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}
void ACharPawn::Shoot()
{
	if (Ammo > 0 && Bullet != 0)
	{
		Ammo--;
		FVector Location = GetActorLocation();
		Location.X += 0.4f;
		GetWorld()->SpawnActor<ABullet>(Bullet, Location, GetActorRotation());
	}
}
// Called to bind functionality to input
void ACharPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &ACharPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACharPawn::MoveRight);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &ACharPawn::Shoot);

}
void ACharPawn::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(AInvader::StaticClass()))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}


