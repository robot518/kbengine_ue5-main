#include "GameEntity.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "../GamePlay/GameModeWorld.h"
#include "EngineMinimal.h"
#include "KBEnginePlugins/Engine/KBEngine.h"
#include "KBEnginePlugins/Engine/Entity.h"

FName AGameEntity::GroundName(TEXT("Landscape_0"));

// 设置默认值
AGameEntity::AGameEntity()
{
	// 设置此 empty，以调用每个帧的 Tick()。如果不需要，可以禁用此功能以提高性能。
	PrimaryActorTick.bCanEverTick = true;
	entityID = 0;
	moveSpeed = 0.f;
	isOnGround = false;

	GroundBox = CreateDefaultSubobject<UBoxComponent>(TEXT("GroundBox"));
	GroundBox->SetupAttachment(RootComponent);
	GroundBox->SetCollisionProfileName(FName("OverlapAll"));

	FScriptDelegate OverlapBegin;
	OverlapBegin.BindUFunction(this, "OnOverlapBegin");
	GroundBox->OnComponentBeginOverlap.Add(OverlapBegin);
	
	FScriptDelegate OverlapEnd;
	OverlapEnd.BindUFunction(this, "OnOverlapEnd");
	GroundBox->OnComponentEndOverlap.Add(OverlapEnd);
}

// 已在游戏开始或生成时调用
void AGameEntity::BeginPlay()
{
	Super::BeginPlay();

	auto XGameMode = Cast<AGameModeWorld>(UGameplayStatics::GetGameMode(this));
	
	if (XGameMode)
	{
		// 把自己注册到AGameModeWorld，方便后面查找
		XGameMode->addGameEntity(this->entityID, this);
		KBEngine::Entity* pEntity = KBEngine::KBEngineApp::getSingleton().findEntity(entityID);

		LastUpdateAnimTime = GetWorld()->TimeSeconds;

		// 由于UE4可视化实体创建要晚于KBE的插件的逻辑实体，而KBE插件实体先前可能已经触发了一些属性设置事件
		// 因此此时我们可能已经错过了一些事件，我们只能在此补救必要的触发了， 例如：名称和血量属性值
		if (pEntity)
			pEntity->callPropertysSetMethods();
	}
}

void AGameEntity::Destroyed()
{
	Super::Destroyed();

	auto XGameMode = Cast<AGameModeWorld>(UGameplayStatics::GetGameMode(this));

	if (XGameMode)
	{
		// 把自己注册到AGameModeWorld，方便后面查找
		XGameMode->removeGameEntity(this->entityID);
	}
}

void AGameEntity::updateLocation(float DeltaTime)
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

	//动作更新
	RemainAnimSpaceTime -= DeltaTime * 5;
	float AnimLerpPercent = FMath::Clamp(RemainAnimSpaceTime / UpdateAnimSpaceTime, 0.f, 1.f);
	AnimSpeed = FMath::Lerp(TargetSpeed, LastSpeed, AnimLerpPercent);
	AnimDirection = FMath::Lerp(TargetDirection, LastDirection, AnimLerpPercent);
}

void AGameEntity::OnOverlapBegin(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetFName().IsEqual(GroundName)) 
	{
		//AnimIsInAir = false;
	}
}

void AGameEntity::OnOverlapEnd(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetFName().IsEqual(GroundName))
	{
		//AnimIsInAir = true;
	}
}

// 已调用每个帧
void AGameEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isPlayer())
	{
		updateLocation(DeltaTime);
	}
}

// 调用以绑定要输出的功能
void AGameEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGameEntity::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);

	Super::FaceRotation(CurrentRotation, DeltaTime);
}

void AGameEntity::setModelID(int sub_modelID)
{
	this->modelID = sub_modelID;

	if (this->modelID == ModelID_Avatar)
	{
		this->createAvatar();
	}
	else
	{
		this->createMonster();
	}
}

void AGameEntity::SetTargetAnim(float Speed, float Direction)
{
	TargetSpeed = Speed;
	TargetDirection = Direction;
	LastSpeed = AnimSpeed;
	LastDirection = AnimDirection;

	UpdateAnimSpaceTime = GetWorld()->TimeSeconds - LastUpdateAnimTime;
	RemainAnimSpaceTime = UpdateAnimSpaceTime;
	LastUpdateAnimTime = GetWorld()->TimeSeconds;
}

void AGameEntity::createAvatar()
{
	TArray<UActorComponent*> components = this->GetComponents().Array();
	for (int i = 0; i < components.Num(); i++)
	{
		if (components[i]->GetName() == "Scene")  //调整血条位置
		{
			UWidgetComponent* pWidget = (UWidgetComponent*)components[i];
			pWidget->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
		}

		if (components[i]->GetName() == "Sphere")	//隐藏整球
		{
			USphereComponent* pSphere = (USphereComponent*)components[i];
			pSphere->SetActive(false);
			pSphere->SetVisibility(false);
		}

		if (components[i]->GetName() == "Cone")		//隐藏圆锥体
		{
			UStaticMeshComponent* pCone = (UStaticMeshComponent*)components[i];
			pCone->SetActive(false);
			pCone->SetVisibility(false);
		}
	}
}

void AGameEntity::createMonster()
{
	USkeletalMeshComponent* SkeletalMesh = this->GetMesh();
	SkeletalMesh->SetActive(false);
	SkeletalMesh->SetVisibility(false);
}
