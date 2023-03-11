#include "GameModeSelectAvatar.h"
#include "KBEnginePlugins/Engine/KBEngine.h"
#include "KBEnginePlugins/Engine/KBEMain.h"
#include "KBEnginePlugins/Scripts/KBUtil.h"
#include "KBClient.h"

// 设置默认值
AGameModeSelectAvatar::AGameModeSelectAvatar()
{
	// 设置此 empty，以调用每个帧的 Tick()。如果不需要，可以禁用此功能以提高性能。
	PrimaryActorTick.bCanEverTick = true;
}

void AGameModeSelectAvatar::InstallEvent()
{
	Super::InstallEvent();

	// select-avatars(register by scripts)
	KBENGINE_REGISTER_EVENT("onReqAvatarList", onReqAvatarList);
	KBENGINE_REGISTER_EVENT("onCreateAvatarResult", onCreateAvatarResult);
	KBENGINE_REGISTER_EVENT("onRemoveAvatar", onRemoveAvatar);

	// begin enterworld
	// 这个事件触发时我们需要切换地图到游戏世界地图
	KBENGINE_REGISTER_EVENT("addSpaceGeometryMapping", addSpaceGeometryMapping);
}

void AGameModeSelectAvatar::onReqAvatarList_Implementation(const UKBEventData* pEventData)
{
}

void AGameModeSelectAvatar::onCreateAvatarResult_Implementation(const UKBEventData* pEventData)
{
}

void AGameModeSelectAvatar::onRemoveAvatar_Implementation(const UKBEventData* pEventData)
{
}

void AGameModeSelectAvatar::addSpaceGeometryMapping_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeSelectAvatar::reqCreateAvatar(uint8 roleType, const FString& name)
{
	// 由于Account实体注册了该事件， 如果此时Account实体存在那么必然会执行到该事件 
	UKBEventData_reqCreateAvatar* pEventData = NewObject<UKBEventData_reqCreateAvatar>();
	pEventData->roleType = roleType;
	pEventData->name = name;
	KBENGINE_EVENT_FIRE("reqCreateAvatar", pEventData);
}

void AGameModeSelectAvatar::reqRemoveAvatar(const FAVATAR_INFOS& avatarInfos)
{
	// 由于Account实体注册了该事件， 如果此时Account实体存在那么必然会执行到该事件 
	UKBEventData_reqRemoveAvatar* pEventData = NewObject<UKBEventData_reqRemoveAvatar>();
	pEventData->avatarInfos = avatarInfos;
	KBENGINE_EVENT_FIRE("reqRemoveAvatar", pEventData);
}

void AGameModeSelectAvatar::selectAvatarGame(const FAVATAR_INFOS& avatarInfos)
{
	// 由于Account实体注册了该事件， 如果此时Account实体存在那么必然会执行到该事件 
	UKBEventData_selectAvatarGame* pEventData = NewObject<UKBEventData_selectAvatarGame>();
	pEventData->avatarInfos = avatarInfos;
	KBENGINE_EVENT_FIRE("selectAvatarGame", pEventData);
}
