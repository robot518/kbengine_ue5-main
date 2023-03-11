#pragma once

#include "CoreMinimal.h"
#include "KBGameModeBase.h"
#include "GameModeSelectAvatar.generated.h"

UCLASS()
class KBEDEMO_API AGameModeSelectAvatar : public AKBGameModeBase
{
	GENERATED_BODY()

public:
	AGameModeSelectAvatar();

	/*
		安装登陆时需要监听的KBE事件
	*/
	virtual void InstallEvent() override;

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void onReqAvatarList(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void onCreateAvatarResult(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void addSpaceGeometryMapping(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void onRemoveAvatar(const UKBEventData* pEventData);

	UFUNCTION(BlueprintCallable, Category = KBEngine)
		void reqCreateAvatar(uint8 roleType, const FString& name);

	UFUNCTION(BlueprintCallable, Category = KBEngine)
		void reqRemoveAvatar(const FAVATAR_INFOS& avatarInfos);

	UFUNCTION(BlueprintCallable, Category = KBEngine)
		void selectAvatarGame(const FAVATAR_INFOS& avatarInfos);

};
