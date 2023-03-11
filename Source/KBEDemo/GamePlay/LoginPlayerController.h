// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoginPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KBEDEMO_API ALoginPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = KBEngine)
		int32 ScreenWidth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = KBEngine)
		int32 ScreenHeight;

protected:
	virtual void BeginPlay();
	
};
