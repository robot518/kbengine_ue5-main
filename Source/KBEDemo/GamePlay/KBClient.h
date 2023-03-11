// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KBClient.generated.h"

class UKBEMain;
UCLASS()
class KBEDEMO_API AKBClient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKBClient();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
		UKBEMain* kbeMain;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
