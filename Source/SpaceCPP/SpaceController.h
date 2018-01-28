// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpaceController.generated.h"

/**
 * 
 */
UCLASS()
class SPACECPP_API ASpaceController : public APlayerController
{
	GENERATED_BODY()
	
public:


	virtual void BeginPlay() override;
	
};
