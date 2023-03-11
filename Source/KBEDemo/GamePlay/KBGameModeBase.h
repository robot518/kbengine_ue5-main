// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KBEnginePlugins/Scripts/LogicEvents.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KBGameModeBase.generated.h"

/**
 * 
 */
class UKBEventData;
UCLASS()
class KBEDEMO_API AKBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AKBGameModeBase();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	/**
	* Initialize the game.
	* The GameMode's InitGame() event is called before any other functions (including PreInitializeComponents() )
	* and is used by the GameMode to initialize parameters and spawn its helper classes.
	* @warning: this is called before actors' PreInitializeComponents.
	*/
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/** Called when a Controller with a PlayerState leaves the match. */
	virtual void Logout(AController* Exiting) override;

	void Fire(const FString& eventName, UKBEventData* pEventData);

	virtual void InstallEvent();
	
	virtual void UnInstallEvent();

	// 登录连接回调
	virtual void OnKicked(const UKBEventData* pEventData);
	virtual void OnDisconnected(const UKBEventData* pEventData);
	virtual void OnConnectionState(const UKBEventData* pEventData);
	virtual void OnReloginBaseappSuccessfully(const UKBEventData* pEventData);
	virtual void OnReloginBaseappFailed(const UKBEventData* pEventData);

	void StartReloginBaseappTimer();

	void StopReloginBaseappTimer();

	//重登baseapp项目
	void OnReloginBaseappTimer();

protected:
	FTimerHandle TimerHandle;

	bool StartRelogin;
	
};
