// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceController.h"
#include "Blueprint/UserWidget.h"

void ASpaceController::BeginPlay()
{
	// Spent so long getting this thing to work
	FStringClassReference MyWidgetClassRef(TEXT("/Game/Blueprints/CPP_SpaceInvadersHUD.CPP_SpaceInvadersHUD_C"));
	if (UClass* MyWidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>())
	{
		UUserWidget* MyWidget = CreateWidget<UUserWidget>(GetWorld(), MyWidgetClass);
		MyWidget->AddToViewport();
		// Do stuff with MyWidget
	}
}





