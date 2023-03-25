#include "GameModeWorld.h"
#include "EngineMinimal.h"
#include "../Entity/GameEntity.h"
#include "../Entity/PlayerCharacter.h"
#include "KBEnginePlugins/Engine/KBEngine.h"
#include "KBEnginePlugins/Engine/Entity.h"
#include "../Entity/HoverCarSpawn.h"
#include "../Entity/HoverPlayerCarSpawn.h"

// 设置默认值
AGameModeWorld::AGameModeWorld()
{
	// 设置此 empty，以调用每个帧的 Tick()。如果不需要，可以禁用此功能以提高性能。
	PrimaryActorTick.bCanEverTick = true;
}

void AGameModeWorld::InstallEvent()
{
	Super::InstallEvent();

	// in world
	// 这个事件触发时我们需要切换地图到游戏世界地图
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::addSpaceGeometryMapping, addSpaceGeometryMapping);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onEnterWorld, onEnterWorld);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLeaveWorld, onLeaveWorld);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onEnterSpace, onEnterSpace);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLeaveSpace, onLeaveSpace);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::set_position, set_position);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::set_direction, set_direction);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::updatePosition, updatePosition);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onControlled, onControlled);

	// in world(register by scripts)
	KBENGINE_REGISTER_EVENT("set_HP", set_HP);
	KBENGINE_REGISTER_EVENT("set_MP", set_MP);
	KBENGINE_REGISTER_EVENT("set_HP_Max", set_HP_Max);
	KBENGINE_REGISTER_EVENT("set_MP_Max", set_MP_Max);
	KBENGINE_REGISTER_EVENT("set_level", set_level);
	KBENGINE_REGISTER_EVENT("set_name", set_name);
	KBENGINE_REGISTER_EVENT("set_moveSpeed", set_moveSpeed);
	KBENGINE_REGISTER_EVENT("set_modelScale", set_modelScale);
	KBENGINE_REGISTER_EVENT("set_modelID", set_modelID);
	KBENGINE_REGISTER_EVENT("set_entityNO", set_entityNO);
	KBENGINE_REGISTER_EVENT("set_flags", set_flags);
	KBENGINE_REGISTER_EVENT("set_state", set_state);
	KBENGINE_REGISTER_EVENT("set_subState", set_subState);
	KBENGINE_REGISTER_EVENT("set_forbids", set_forbids);
	KBENGINE_REGISTER_EVENT("recvDamage", recvDamage);
	KBENGINE_REGISTER_EVENT("otherAvatarOnJump", otherAvatarOnJump);
	KBENGINE_REGISTER_EVENT("onAddSkill", onAddSkill);

	KBENGINE_REGISTER_EVENT("OnAnimUpdate", OnAnimUpdate);
	KBENGINE_REGISTER_EVENT("OnHoverCarMoveSpeedUpdate", OnHoverCarMoveSpeedUpdate);
}

// 已在游戏开始或生成时调用
void AGameModeWorld::BeginPlay()
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
	//TSubclassOf<class APlayerCharacter>& APlayerCharacterClass = PlayerCharacterClassArray[0];
	//auto DeferredActor = Cast<APlayerCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, APlayerCharacterClass, SpawnTransform));
	//if (DeferredActor != nullptr)
	//{
	//	DeferredActor->entityID = 666;
	//	DeferredActor->moveSpeed = 15.f;
	//	UGameplayStatics::FinishSpawningActor(DeferredActor, SpawnTransform);
	//}
}

void AGameModeWorld::reqRelive(int reliveType)
{
	// 由于玩家的Avatar实体注册了该事件， 如果此时Avatar实体存在那么必然会执行到该事件 
	UKBEventData_reqRelive* pEventData = NewObject<UKBEventData_reqRelive>();
	pEventData->reliveType = reliveType;
	KBENGINE_EVENT_FIRE("relive", pEventData);
}

AGameEntity* AGameModeWorld::findGameEntity(int entityID)
{
	AGameEntity** pGameEntity = gameEntities.Find(entityID);
	if (pGameEntity)
		return *pGameEntity;

	return NULL;
}

void AGameModeWorld::addGameEntity(int entityID, AGameEntity* entity)
{
	gameEntities.Add(entityID, entity);
}

void AGameModeWorld::removeGameEntity(int entityID)
{
	gameEntities.Remove(entityID);
}

AHoverCarSpawn* AGameModeWorld::findHoverCarEntity(int entityID)
{
	AHoverCarSpawn** pGameEntity = hoverCarEntities.Find(entityID);
	if (pGameEntity)
		return *pGameEntity;

	return NULL;
}

void AGameModeWorld::addHoverCarEntity(int entityID, AHoverCarSpawn* entity)
{
	hoverCarEntities.Add(entityID, entity);
}

void AGameModeWorld::removeHoverCarEntity(int entityID)
{
	hoverCarEntities.Remove(entityID);
}

void AGameModeWorld::OnAnimUpdate(const UKBEventData* EventData)
{
	const UKBEventData_OnAnimUpdate* data = Cast<UKBEventData_OnAnimUpdate>(EventData);
	AGameEntity* pAGameEntity = findGameEntity(data->EntityId);
	if (pAGameEntity) {
		pAGameEntity->SetTargetAnim(data->Speed, data->Direction);
	}
}

void AGameModeWorld::OnHoverCarMoveSpeedUpdate(const UKBEventData* EventData)
{
	const UKBEventData_OnHoverCarMoveSpeedUpdate* data = Cast<UKBEventData_OnHoverCarMoveSpeedUpdate>(EventData);
	AHoverCarSpawn* pAGameEntity = findHoverCarEntity(data->EntityId);
	if (pAGameEntity) {
		pAGameEntity->SetTargetMoveSpeed(data->Speed);
	}
}

void AGameModeWorld::addSpaceGeometryMapping_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::onEnterWorld_Implementation(const UKBEventData* pEventData)
{
	const UKBEventData_onEnterWorld* pData = Cast<UKBEventData_onEnterWorld>(pEventData);

	FRotator Rot(0.f, 0.f, 0.f);
	KBDir2UE4Dir(Rot, pData->direction);
	FTransform SpawnTransform(Rot, (FVector)pData->position);

	if (pData->isPlayer)
	{
		if (iType == 0)
		{
			TSubclassOf<class APlayerCharacter>& APlayerCharacterClass = PlayerCharacterClassArray[0];
			auto DeferredActor = Cast<APlayerCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, APlayerCharacterClass, SpawnTransform));
			if (DeferredActor != nullptr)
			{
				DeferredActor->entityID = pData->entityID;
				DeferredActor->moveSpeed = pData->moveSpeed;
				UGameplayStatics::FinishSpawningActor(DeferredActor, SpawnTransform);
			}
		}
		else if (iType == 1) 
		{
			TSubclassOf<class AHoverPlayerCarSpawn>& APlayerCarPawnClass = HoverPlayerCarSpawnClassArray[0];
			auto DeferredActor = Cast<AHoverCarSpawn>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, APlayerCarPawnClass, SpawnTransform));
			if (DeferredActor != nullptr)
			{
				DeferredActor->entityID = pData->entityID;
				DeferredActor->moveSpeed = pData->moveSpeed;
				UGameplayStatics::FinishSpawningActor(DeferredActor, SpawnTransform);
			}
		}
		
	}
	else
	{
		if (iType == 0)
		{
			TSubclassOf<class AGameEntity>& AGameEntityClass = GameEntityClassArray[0];
			auto DeferredActor = Cast<AGameEntity>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, AGameEntityClass, SpawnTransform));
			if (DeferredActor != nullptr)
			{
				DeferredActor->entityID = pData->entityID;
				DeferredActor->moveSpeed = pData->moveSpeed;
				UGameplayStatics::FinishSpawningActor(DeferredActor, SpawnTransform);
			}
		}
		else if (iType == 1)
		{
			TSubclassOf<class AHoverCarSpawn>& ACarPawnClass = HoverCarSpawnClassArray[0];
			auto DeferredActor = Cast<AHoverCarSpawn>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ACarPawnClass, SpawnTransform));
			if (DeferredActor != nullptr)
			{
				DeferredActor->entityID = pData->entityID;
				DeferredActor->moveSpeed = pData->moveSpeed;
				UGameplayStatics::FinishSpawningActor(DeferredActor, SpawnTransform);
			}
		}
	}
}

void AGameModeWorld::onLeaveWorld_Implementation(const UKBEventData* pEventData)
{
	const UKBEventData_onLeaveWorld* pData = Cast<UKBEventData_onLeaveWorld>(pEventData);
	if (iType == 0)
	{
		AGameEntity* pAGameEntity = findGameEntity(pData->entityID);
		if (pAGameEntity)
		{
			pAGameEntity->Destroy();
		}
	}
	else if (iType == 1)
	{
		AHoverCarSpawn* pAGameEntity = findHoverCarEntity(pData->entityID);
		if (pAGameEntity)
		{
			pAGameEntity->Destroy();
		}
	}
}

void AGameModeWorld::onEnterSpace_Implementation(const UKBEventData* pEventData)
{
	const UKBEventData_onEnterSpace* pData = Cast<UKBEventData_onEnterSpace>(pEventData);

	FRotator Rot(0.f, 0.f, 0.f);
	KBDir2UE4Dir(Rot, pData->direction);
	FTransform SpawnTransform(Rot, (FVector)pData->position);

	if (pData->isPlayer)
	{
		TSubclassOf<class APlayerCharacter>& APlayerCharacterClass = PlayerCharacterClassArray[0];
		auto DeferredActor = Cast<APlayerCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, APlayerCharacterClass, SpawnTransform));
		if (DeferredActor != nullptr)
		{
			DeferredActor->entityID = pData->entityID;
			DeferredActor->moveSpeed = pData->moveSpeed;
			UGameplayStatics::FinishSpawningActor(DeferredActor, SpawnTransform);
		}
	}
	else
	{
		check(false);
	}
}

void AGameModeWorld::onLeaveSpace_Implementation(const UKBEventData* pEventData)
{
	const UKBEventData_onLeaveSpace* pData = Cast<UKBEventData_onLeaveSpace>(pEventData);
	AGameEntity* pAGameEntity = findGameEntity(pData->entityID);

	if (pAGameEntity)
	{
		pAGameEntity->Destroy();
	}
}

void AGameModeWorld::set_position_Implementation(const UKBEventData* pEventData)
{
	const UKBEventData_set_position* pData = Cast<UKBEventData_set_position>(pEventData);
	if (iType == 0)
	{
		AGameEntity* pAGameEntity = findGameEntity(pData->entityID);
		if (pAGameEntity)
		{
			pAGameEntity->SetActorLocation((FVector)pData->position);
			pAGameEntity->setTargetLocation((FVector)pData->position);
			pAGameEntity->setIsOnGround(pData->isOnGround);
		}
	}
	else if (iType == 1)
	{
		AHoverCarSpawn* pAGameEntity = findHoverCarEntity(pData->entityID);
		if (pAGameEntity)
		{
			pAGameEntity->SetActorLocation((FVector)pData->position);
			pAGameEntity->setTargetLocation((FVector)pData->position);
			pAGameEntity->setIsOnGround(pData->isOnGround);
		}
	}
}

void AGameModeWorld::set_direction_Implementation(const UKBEventData* pEventData)
{
	const UKBEventData_set_direction* pData = Cast<UKBEventData_set_direction>(pEventData);
	if (iType == 0)
	{
		AGameEntity* pAGameEntity = findGameEntity(pData->entityID);
		if (pAGameEntity)
		{
			pAGameEntity->setTargetRotator((FRotator3f)pData->direction);
		}
	}
	else if (iType == 1)
	{
		AHoverCarSpawn* pAGameEntity = findHoverCarEntity(pData->entityID);
		if (pAGameEntity)
		{
			pAGameEntity->setTargetRotator((FRotator3f)pData->direction);
		}
	}
}

void AGameModeWorld::updatePosition_Implementation(const UKBEventData* pEventData)
{
	const UKBEventData_updatePosition* pData = Cast<UKBEventData_updatePosition>(pEventData);
	if (iType == 0)
	{
		AGameEntity* pAGameEntity = findGameEntity(pData->entityID);
		if (pAGameEntity)
		{
			pAGameEntity->setTargetLocation((FVector)pData->position);
			pAGameEntity->setIsOnGround(pData->isOnGround);
		}
	}
	else if (iType == 1)
	{
		AHoverCarSpawn* pAGameEntity = findHoverCarEntity(pData->entityID);
		if (pAGameEntity)
		{
			pAGameEntity->setTargetLocation((FVector)pData->position);
			pAGameEntity->setIsOnGround(pData->isOnGround);
		}
	}
}

void AGameModeWorld::onControlled_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_HP_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_MP_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_HP_Max_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_MP_Max_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_level_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_name_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_moveSpeed_Implementation(const UKBEventData* pEventData)
{
	const UKBEventData_set_moveSpeed* pData = Cast<UKBEventData_set_moveSpeed>(pEventData);
	if (iType == 0)
	{
		AGameEntity* pAGameEntity = findGameEntity(pData->entityID);
		if (pAGameEntity)
			pAGameEntity->moveSpeed = pData->moveSpeed;
	}
	else if (iType == 1)
	{
		AHoverCarSpawn* pAGameEntity = findHoverCarEntity(pData->entityID);
		if (pAGameEntity)
			pAGameEntity->moveSpeed = pData->moveSpeed;
	}
}

void AGameModeWorld::set_modelScale_Implementation(const UKBEventData* pEventData)
{
	const UKBEventData_set_modelScale* pData = Cast<UKBEventData_set_modelScale>(pEventData);
	AGameEntity* pAGameEntity = findGameEntity(pData->entityID);

	if (pAGameEntity)
		pAGameEntity->modelScale = (float)(pData->modelScale / 100.0f);
}

void AGameModeWorld::set_modelID_Implementation(const UKBEventData* pEventData)
{
	const UKBEventData_set_modelID* pData = Cast<UKBEventData_set_modelID>(pEventData);
	AGameEntity* pAGameEntity = findGameEntity(pData->entityID);
	if (pAGameEntity)
		pAGameEntity->setModelID(pData->modelID);
}

void AGameModeWorld::set_entityNO_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_flags_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_state_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_subState_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::set_forbids_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::recvDamage_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::otherAvatarOnJump_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeWorld::onAddSkill_Implementation(const UKBEventData* pEventData)
{

}
