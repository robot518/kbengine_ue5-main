#include "HoverCarSpawn.h"
#include "../GamePlay/GameModeWorld.h"
#include "EngineMinimal.h"
#include "KBEnginePlugins/Engine/KBEngine.h"
#include "KBEnginePlugins/Engine/Entity.h"

// 设置默认值
AHoverCarSpawn::AHoverCarSpawn()
{
	// 设置此 pawn，以调用每个帧的 Tick()。如果不需要，可以禁用此功能以提高性能。
	PrimaryActorTick.bCanEverTick = true;
	entityID = 0;
	moveSpeed = 0.f;
	isOnGround = false;
}

// 已在游戏开始或生成时调用
void AHoverCarSpawn::BeginPlay()
{
	Super::BeginPlay();

	auto XGameMode = Cast<AGameModeWorld>(UGameplayStatics::GetGameMode(this));

	if (XGameMode)
	{
		// 把自己注册到AGameModeWorld，方便后面查找
		XGameMode->addHoverCarEntity(this->entityID, this);
		KBEngine::Entity* pEntity = KBEngine::KBEngineApp::getSingleton().findEntity(entityID);

		// 由于UE4可视化实体创建要晚于KBE的插件的逻辑实体，而KBE插件实体先前可能已经触发了一些属性设置事件
		// 因此此时我们可能已经错过了一些事件，我们只能在此补救必要的触发了， 例如：名称和血量属性值
		if (pEntity)
			pEntity->callPropertysSetMethods();
	}
}

void AHoverCarSpawn::Destroyed()
{
	Super::Destroyed();

	auto XGameMode = Cast<AGameModeWorld>(UGameplayStatics::GetGameMode(this));

	if (XGameMode)
	{
		// 把自己注册到AGameModeWorld，方便后面查找
		XGameMode->removeCarEntity(this->entityID);
	}
}

void AHoverCarSpawn::updateLocation(float DeltaTime)
{
	const FVector& currLocation = GetActorLocation();

	//Direction from Self to targetPos
	FVector vectorDirection = targetLocation - currLocation;

	float deltaSpeed = (moveSpeed * 10.f /*由于服务端脚本moveSpeed的单位是厘米，这里需要转换为UE4单位毫米*/) * DeltaTime;
	if (vectorDirection.Size() > deltaSpeed)
	{
		//Normalize Vector so it is just a direction
		vectorDirection.Normalize();

		//Move moveSpeed units toward the player, per tick
		SetActorLocation(currLocation + (vectorDirection * deltaSpeed));
	}
	else
	{
		SetActorLocation(targetLocation);
	}

	FaceRotation(targetRotator, DeltaTime);
}

// 已调用每个帧
void AHoverCarSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isPlayer())
	{
		updateLocation(DeltaTime);
	}
}

// 调用以绑定要输出的功能
void AHoverCarSpawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AHoverCarSpawn::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);

	Super::FaceRotation(CurrentRotation, DeltaTime);
}

void AHoverCarSpawn::setModelID(int sub_modelID)
{
	this->modelID = sub_modelID;
}

