// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KBGameModeBase.h"
#include "LoginGameMode.generated.h"

/**
 * 
 */

//class UKBEMain;
//class ULoginWidget;
UCLASS()
class KBEDEMO_API ALoginGameMode : public AKBGameModeBase
{
	GENERATED_BODY()

public:

	ALoginGameMode();
	/*
		安装登陆时需要监听的KBE事件
	*/
	virtual void InstallEvent() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool ValidEmail(FString strEmail);

	/* KBE事件
	*/
	void OnCreateAccountResult(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void OnLoginFailed(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void OnVersionNotMatch(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void OnScriptVersionNotMatch(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void OnLoginBaseappFailed(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void OnLoginSuccessfully(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void OnLoginBaseapp(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void Loginapp_importClientMessages(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void Baseapp_importClientMessages(const UKBEventData* pEventData);

	/* KBE事件
	*/
	void Baseapp_importClientEntityDef(const UKBEventData* pEventData);
	


public:

	/*ULoginWidget* LoginWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ULoginWidget> LoginWidgetClass;*/

	//UKBEMain* KBEMain;

};
