// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CharPawn.generated.h"

class ABullet;


UCLASS()
class SPACECPP_API ACharPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UCharMovementComponent* MyMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* CapsuleVisual;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Variables")
		int Ammo = 100;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class ABullet> Bullet;

	void Shoot();

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);


protected:
	//Input variable
	FVector2D MovementInput;

	//Input functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

};
