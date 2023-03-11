// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginPlayerController.h"

void ALoginPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 2560*1440 / 4 w
	ConsoleCommand(FString::Printf(TEXT("r.setres %d x %dw"), ScreenWidth, ScreenHeight));
	
	bShowMouseCursor = true;
	
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
}
