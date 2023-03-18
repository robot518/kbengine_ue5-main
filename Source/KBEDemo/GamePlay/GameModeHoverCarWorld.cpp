#include "GameModeHoverCarWorld.h"
#include "KBEnginePlugins/Engine/KBEngine.h"
#include "KBEnginePlugins/Engine/Entity.h"
#include "EngineMinimal.h"
#include "../Entity/HoverCarSpawn.h"

// 设置默认值
AGameModeHoverCarWorld::AGameModeHoverCarWorld()
{
	// 设置此 empty，以调用每个帧的 Tick()。如果不需要，可以禁用此功能以提高性能。
	PrimaryActorTick.bCanEverTick = true;
}

void AGameModeHoverCarWorld::InstallEvent()
{
	Super::InstallEvent();

	// in world
	// 这个事件触发时我们需要切换地图到游戏世界地图
	//KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::addSpaceGeometryMapping, addSpaceGeometryMapping);
	//KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onEnterWorld, onEnterWorld);
	//KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLeaveWorld, onLeaveWorld);
	//KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onEnterSpace, onEnterSpace);
	//KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLeaveSpace, onLeaveSpace);
	//KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::set_position, set_position);
	//KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::set_direction, set_direction);
	//KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::updatePosition, updatePosition);
	//KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onControlled, onControlled);

	//// in world(register by scripts)
	//KBENGINE_REGISTER_EVENT("set_HP", set_HP);
	//KBENGINE_REGISTER_EVENT("set_MP", set_MP);
	//KBENGINE_REGISTER_EVENT("set_HP_Max", set_HP_Max);
	//KBENGINE_REGISTER_EVENT("set_MP_Max", set_MP_Max);
	//KBENGINE_REGISTER_EVENT("set_level", set_level);
	//KBENGINE_REGISTER_EVENT("set_name", set_name);
	//KBENGINE_REGISTER_EVENT("set_moveSpeed", set_moveSpeed);
	//KBENGINE_REGISTER_EVENT("set_modelScale", set_modelScale);
	//KBENGINE_REGISTER_EVENT("set_modelID", set_modelID);
	//KBENGINE_REGISTER_EVENT("set_entityNO", set_entityNO);
	//KBENGINE_REGISTER_EVENT("set_flags", set_flags);
	//KBENGINE_REGISTER_EVENT("set_state", set_state);
	//KBENGINE_REGISTER_EVENT("set_subState", set_subState);
	//KBENGINE_REGISTER_EVENT("set_forbids", set_forbids);
	//KBENGINE_REGISTER_EVENT("recvDamage", recvDamage);
	//KBENGINE_REGISTER_EVENT("otherAvatarOnJump", otherAvatarOnJump);
	//KBENGINE_REGISTER_EVENT("onAddSkill", onAddSkill);
}

// 已在游戏开始或生成时调用
void AGameModeHoverCarWorld::BeginPlay()
{
	Super::BeginPlay();

	check(KBEngine::KBEngineApp::getSingleton().isInitialized());

	// 如果已经有被创建的实体，说明他们在上一个场景未来得及跳转之前已经通知创建了，但由于我们的world场景并没有来得及创建，这部分实体进入世界事件已经漏掉
	// 此时我们需要再次触发一次onEnterWorld，让表现层能够在游戏场景中创建出所有的实体
	KBEngine::KBEngineApp::ENTITIES_MAP& entities = KBEngine::KBEngineApp::getSingleton().entities();
	for (auto& item : entities)
	{
		KBEngine::Entity* pEntity = item.Value;

		UKBEventData_onEnterWorld* pEventData = NewObject<UKBEventData_onEnterWorld>();
		pEventData->entityID = pEntity->id();
		pEventData->spaceID = KBEngine::KBEngineApp::getSingleton().spaceID();
		KBPos2UE4Pos(pEventData->position, pEntity->position);
		pEventData->direction = pEntity->direction;
		pEventData->moveSpeed = pEntity->velocity();
		pEventData->isOnGround = pEntity->isOnGround();
		pEventData->isPlayer = pEntity->isPlayer();
		pEventData->entityClassName = pEntity->className();
		pEventData->res = TEXT("");
		KBENGINE_EVENT_FIRE(KBEngine::KBEventTypes::onEnterWorld, pEventData);
	}

	//FRotator Rot(0.f, 0.f, 0.f);
	//FVector3f Dir(0.f, 0.f, 0.f);
	//FVector Pos(0.f, 0.f, 300.f);
	//KBDir2UE4Dir(Rot, Dir);
	//FTransform SpawnTransform(Rot, Pos);

	////手动创建角色
	//TSubclassOf<class AHoverCarSpawn>& AHoverCarSpawnClass = HoverCarSpawnClassArray[0];
	//auto DeferredActor = Cast<AHoverCarSpawn>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, AHoverCarSpawnClass, SpawnTransform));
	//if (DeferredActor != nullptr)
	//{
	//	DeferredActor->entityID = 666;
	//	DeferredActor->moveSpeed = 15.f;
	//	UGameplayStatics::FinishSpawningActor(DeferredActor, SpawnTransform);
	//}
}

//void AGameModeHoverCarWorld::onEnterWorld_Implementation(const UKBEventData* pEventData)
//{
//	const UKBEventData_onEnterWorld* pData = Cast<UKBEventData_onEnterWorld>(pEventData);
//
//	FRotator Rot(0.f, 0.f, 0.f);
//	KBDir2UE4Dir(Rot, pData->direction);
//	FTransform SpawnTransform(Rot, (FVector)pData->position);
//
//	if (pData->isPlayer)
//	{
//		TSubclassOf<class AHoverCarSpawn>& AHoverCarSpawnClass = HoverCarSpawnClassArray[0];
//		auto DeferredActor = Cast<AHoverCarSpawn>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, AHoverCarSpawnClass, SpawnTransform));
//		if (DeferredActor != nullptr)
//		{
//			DeferredActor->entityID = 666;
//			DeferredActor->moveSpeed = 15.f;
//			UGameplayStatics::FinishSpawningActor(DeferredActor, SpawnTransform);
//		}
//	}
//	else
//	{
//		/*TSubclassOf<class AGameEntity>& AGameEntityClass = GameEntityClassArray[0];
//		auto DeferredActor = Cast<AGameEntity>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, AGameEntityClass, SpawnTransform));
//		if (DeferredActor != nullptr)
//		{
//			DeferredActor->entityID = pData->entityID;
//			DeferredActor->moveSpeed = pData->moveSpeed;
//			UGameplayStatics::FinishSpawningActor(DeferredActor, SpawnTransform);
//		}*/
//		//TSubclassOf<class AHoverCarSpawn>& AHoverCarSpawnClass = HoverCarSpawnClassArray[0];
//		//auto DeferredActor = Cast<AHoverCarSpawn>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, AHoverCarSpawnClass, SpawnTransform));
//		//if (DeferredActor != nullptr)
//		//{
//		//	DeferredActor->entityID = 666;
//		//	DeferredActor->moveSpeed = 15.f;
//		//	UGameplayStatics::FinishSpawningActor(DeferredActor, SpawnTransform);
//		//}
//	}
//}

