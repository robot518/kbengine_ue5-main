// Fill out your copyright notice in the Description page of Project Settings.


#include "KBClient.h"
#include "Components/SceneComponent.h"
#include "KBEnginePlugins/Engine/KBEMain.h"

// Sets default values
AKBClient::AKBClient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	kbeMain = CreateDefaultSubobject<UKBEMain>(TEXT("kbeMain"));
}

// Called when the game starts or when spawned
void AKBClient::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKBClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

