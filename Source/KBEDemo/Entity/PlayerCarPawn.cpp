#include "PlayerCarPawn.h"

// 设置默认值
APlayerCarPawn::APlayerCarPawn()
{
	// 设置此 pawn，以调用每个帧的 Tick()。如果不需要，可以禁用此功能以提高性能。
	PrimaryActorTick.bCanEverTick = true;
}

// 已在游戏开始或生成时调用
void APlayerCarPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCarPawn::Destroyed()
{
	Super::Destroyed();
}

// 已调用每个帧
void APlayerCarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 调用以绑定要输出的功能
void APlayerCarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

