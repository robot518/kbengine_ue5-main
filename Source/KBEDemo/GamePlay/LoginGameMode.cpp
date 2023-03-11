// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameMode.h"
#include "KBEnginePlugins/Engine/KBEngine.h"
#include "KBEnginePlugins/Engine/KBEMain.h"
#include "KBEnginePlugins/Scripts/KBUtil.h"
#include "KBClient.h"


ALoginGameMode::ALoginGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALoginGameMode::InstallEvent()
{
	Super::InstallEvent();

	// login
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onCreateAccountResult, OnCreateAccountResult);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginFailed, OnLoginFailed);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onVersionNotMatch, OnVersionNotMatch);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onScriptVersionNotMatch, OnScriptVersionNotMatch);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseappFailed, OnLoginBaseappFailed);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseapp, OnLoginBaseapp);
	KBENGINE_REGISTER_EVENT("onLoginSuccessfully", OnLoginSuccessfully);
	KBENGINE_REGISTER_EVENT("Loginapp_importClientMessages", Loginapp_importClientMessages);
	KBENGINE_REGISTER_EVENT("Baseapp_importClientMessages", Baseapp_importClientMessages);
	KBENGINE_REGISTER_EVENT("Baseapp_importClientEntityDef", Baseapp_importClientEntityDef);
}

void ALoginGameMode::BeginPlay()
{
	// 每次进入到这个界面时对KBE做一次清理，否则KBE插件内缓存的内容将一直存在
	KBEngine::KBEngineApp::getSingleton().reset();

	Super::BeginPlay();
}

bool ALoginGameMode::ValidEmail(FString strEmail)
{
	return KBEngine::KBEngineApp::getSingleton().validEmail(strEmail);
}

void ALoginGameMode::OnCreateAccountResult(const UKBEventData* pEventData)
{
	const UKBEventData_onCreateAccountResult* ServerData = Cast<UKBEventData_onCreateAccountResult>(pEventData);

	DDH::Debug() << "OnCreateAccountResult : errorCode --> " << ServerData->errorCode << " ; errorStr --> " << ServerData->errorStr << DDH::Endl();
}

void ALoginGameMode::OnLoginFailed(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginFailed* ServerData = Cast<UKBEventData_onLoginFailed>(pEventData);

	DDH::Debug() << "OnLoginFailed : failedcode --> " << ServerData->failedcode << " ; errorStr --> " << ServerData->errorStr << DDH::Endl();
}

void ALoginGameMode::OnVersionNotMatch(const UKBEventData* pEventData)
{
	const UKBEventData_onVersionNotMatch* ServerData = Cast<UKBEventData_onVersionNotMatch>(pEventData);

	DDH::Debug() << "OnVersionNotMatch : clientVersion --> " << ServerData->clientVersion << " ; serverVersion --> " << ServerData->serverVersion << DDH::Endl();
}

void ALoginGameMode::OnScriptVersionNotMatch(const UKBEventData* pEventData)
{
	const UKBEventData_onScriptVersionNotMatch* ServerData = Cast<UKBEventData_onScriptVersionNotMatch>(pEventData);

	DDH::Debug() << "OnScriptVersionNotMatch : clientScriptVersion --> " << ServerData->clientScriptVersion << " ; serverScriptVersion --> " << DDH::Endl();
}

void ALoginGameMode::OnLoginBaseappFailed(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginBaseappFailed* ServerData = Cast<UKBEventData_onLoginBaseappFailed>(pEventData);

	DDH::Debug() << "OnLoginBaseappFailed : failedcode --> " << ServerData->failedcode << " ; errorStr --> " << ServerData->errorStr << DDH::Endl();
}

void ALoginGameMode::OnLoginSuccessfully(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginSuccessfully* ServerData = Cast<UKBEventData_onLoginSuccessfully>(pEventData);

	DDH::Debug() << "OnLoginSuccessfully : entity_uuid --> " << ServerData->entity_uuid << " ; entity_id --> " << ServerData->entity_id << DDH::Endl();

	UGameplayStatics::OpenLevel(GetWorld(), FName("SelectAvatarMap"));
}

void ALoginGameMode::OnLoginBaseapp(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginBaseapp* ServerData = Cast<UKBEventData_onLoginBaseapp>(pEventData);

	DDH::Debug() << "OnLoginBaseapp : eventName --> " << ServerData->eventName << DDH::Endl();
}

void ALoginGameMode::Loginapp_importClientMessages(const UKBEventData* pEventData)
{
	const UKBEventData_Loginapp_importClientMessages* ServerData = Cast<UKBEventData_Loginapp_importClientMessages>(pEventData);

	DDH::Debug() << "Loginapp_importClientMessages : eventName --> " << ServerData->eventName << DDH::Endl();
}

void ALoginGameMode::Baseapp_importClientMessages(const UKBEventData* pEventData)
{
	const UKBEventData_Baseapp_importClientMessages* ServerData = Cast<UKBEventData_Baseapp_importClientMessages>(pEventData);

	DDH::Debug() << "Baseapp_importClientMessages : eventName --> " << ServerData->eventName << DDH::Endl();
}

void ALoginGameMode::Baseapp_importClientEntityDef(const UKBEventData* pEventData)
{
	const UKBEventData_Baseapp_importClientEntityDef* ServerData = Cast<UKBEventData_Baseapp_importClientEntityDef>(pEventData);

	DDH::Debug() << "Baseapp_importClientEntityDef : eventName --> " << ServerData->eventName << DDH::Endl();
}
