// Fill out your copyright notice in the Description page of Project Settings.


#include "KBGameModeBase.h"
#include "KBEnginePlugins/Engine/KBEngine.h"
#include "KBEnginePlugins/Engine/KBEvent.h"
#include "KBEnginePlugins/Scripts/KBUtil.h"


AKBGameModeBase::AKBGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AKBGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	InstallEvent();
}


void AKBGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnInstallEvent();
}

void AKBGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AKBGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	// 可以在这里理解为玩家编辑器Stop游戏或者离开了这个场景
	if (Exiting)
	{
		UnInstallEvent();
	}
}

void AKBGameModeBase::Fire(const FString& eventName, UKBEventData* pEventData)
{
	KBENGINE_EVENT_FIRE(eventName, pEventData);
}

void AKBGameModeBase::InstallEvent()
{
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onKicked, OnKicked);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onDisconnected, OnDisconnected);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onConnectionState, OnConnectionState);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappSuccessfully, OnReloginBaseappSuccessfully);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappFailed, OnReloginBaseappFailed);
}

void AKBGameModeBase::UnInstallEvent()
{
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void AKBGameModeBase::OnKicked(const UKBEventData* pEventData)
{
	const UKBEventData_onKicked* ServerData = Cast<UKBEventData_onKicked>(pEventData);

	DDH::Debug() << "OnKicked : failedcode --> " << ServerData->failedcode << " ; errorStr --> " << ServerData->errorStr << DDH::Endl();
}

void AKBGameModeBase::OnDisconnected(const UKBEventData* pEventData)
{
	const UKBEventData_onDisconnected* ServerData = Cast<UKBEventData_onDisconnected>(pEventData);

	DDH::Debug() << "OnDisconnected : eventName --> " << ServerData->eventName << DDH::Endl();
}

void AKBGameModeBase::OnConnectionState(const UKBEventData* pEventData)
{
	const UKBEventData_onConnectionState* ServerData = Cast<UKBEventData_onConnectionState>(pEventData);

	DDH::Debug() << "OnConnectionState : success --> " << ServerData->success << " ; address --> " << ServerData->address << DDH::Endl();
}

void AKBGameModeBase::OnReloginBaseappSuccessfully(const UKBEventData* pEventData)
{
	const UKBEventData_onReloginBaseappSuccessfully* ServerData = Cast<UKBEventData_onReloginBaseappSuccessfully>(pEventData);

	DDH::Debug() << "OnReloginBaseappSuccessfully : eventName --> " << ServerData->eventName << DDH::Endl();
}

void AKBGameModeBase::OnReloginBaseappFailed(const UKBEventData* pEventData)
{
	const UKBEventData_onReloginBaseappFailed* ServerData = Cast<UKBEventData_onReloginBaseappFailed>(pEventData);

	DDH::Debug() << "OnReloginBaseappFailed : failedcode --> " << ServerData->failedcode << " ; errorStr --> " << ServerData->errorStr << DDH::Endl();
}

void AKBGameModeBase::StartReloginBaseappTimer()
{
	if (!TimerHandle.IsValid())
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AKBGameModeBase::OnReloginBaseappTimer, 1.0f, false, 1.0f);
}

void AKBGameModeBase::StopReloginBaseappTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AKBGameModeBase::OnReloginBaseappTimer()
{
	KBEngine::KBEngineApp::getSingleton().reloginBaseapp();

	if (TimerHandle.IsValid())
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AKBGameModeBase::OnReloginBaseappTimer, 1.0f, false, 3.0f);
}
