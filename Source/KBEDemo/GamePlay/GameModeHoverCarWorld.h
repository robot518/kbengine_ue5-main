#pragma once

#include "KBGameModeBase.h"
#include "GameModeHoverCarWorld.generated.h"

UCLASS()
class KBEDEMO_API AGameModeHoverCarWorld : public AKBGameModeBase
{
	GENERATED_BODY()

public:
	// 设置此 empty 属性的默认值
	AGameModeHoverCarWorld();

protected:
	// 已在游戏开始或生成时调用
	virtual void BeginPlay() override;

public:
	virtual void InstallEvent() override;
	// 在编辑器中配置相关类
	UPROPERTY(EditDefaultsOnly, Category = KBEngine)
	TArray<TSubclassOf<class AHoverCarSpawn>> HoverCarSpawnClassArray;
};
