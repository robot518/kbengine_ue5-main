#pragma once

#include "KBGameModeBase.h"
#include "GameModeWorld.generated.h"

UCLASS()
class KBEDEMO_API AGameModeWorld : public AKBGameModeBase
{
	GENERATED_BODY()

public:
	// 设置此 empty 属性的默认值
	AGameModeWorld();

protected:
	// 已在游戏开始或生成时调用
	virtual void BeginPlay() override;

public:
	/*
		安装登陆时需要监听的KBE事件
	*/
	virtual void InstallEvent() override;

	UFUNCTION(BlueprintCallable, Category = KBEngine)
		void reqRelive(int reliveType);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void addSpaceGeometryMapping(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void onEnterWorld(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void onEnterSpace(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void onLeaveWorld(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void onLeaveSpace(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_position(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_direction(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void updatePosition(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void onControlled(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_HP(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_MP(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_HP_Max(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_MP_Max(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_level(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_name(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_moveSpeed(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_modelScale(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_modelID(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_entityNO(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_flags(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_state(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_subState(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void set_forbids(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void recvDamage(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void otherAvatarOnJump(const UKBEventData* pEventData);

	/* KBE事件
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void onAddSkill(const UKBEventData* pEventData);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		AGameEntity* findGameEntity(int entityID);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void addGameEntity(int entityID, AGameEntity* entity);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void removeGameEntity(int entityID);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		AHoverCarSpawn* findHoverCarEntity(int entityID);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void addHoverCarEntity(int entityID, AHoverCarSpawn* entity);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void removeHoverCarEntity(int entityID);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		ACarPawn* findCarEntity(int entityID);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void addCarEntity(int entityID, ACarPawn* entity);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void removeCarEntity(int entityID);

	void OnAnimUpdate(const UKBEventData* EventData);

	void OnHoverCarMoveSpeedUpdate(const UKBEventData* EventData);

	TMap<ENTITY_ID, AGameEntity*> gameEntities;

	TMap<ENTITY_ID, AHoverCarSpawn*> hoverCarEntities;

	TMap<ENTITY_ID, ACarPawn*> carEntities;

	// 在编辑器中配置相关类
	UPROPERTY(EditDefaultsOnly, Category = KBEngine)
		TArray<TSubclassOf<class AGameEntity>> GameEntityClassArray;

	// 在编辑器中配置相关类
	UPROPERTY(EditDefaultsOnly, Category = KBEngine)
		TArray<TSubclassOf<class APlayerCharacter>> PlayerCharacterClassArray;

	// 在编辑器中配置相关类
	UPROPERTY(EditDefaultsOnly, Category = KBEngine)
		TArray<TSubclassOf<class AHoverCarSpawn>> HoverCarSpawnClassArray;

	// 在编辑器中配置相关类
	UPROPERTY(EditDefaultsOnly, Category = KBEngine)
		TArray<TSubclassOf<class AHoverPlayerCarSpawn>> HoverPlayerCarSpawnClassArray;

	// 在编辑器中配置相关类
	UPROPERTY(EditDefaultsOnly, Category = KBEngine)
		TArray<TSubclassOf<class ACarPawn>> CarPawnClassArray;

	// 在编辑器中配置相关类
	UPROPERTY(EditDefaultsOnly, Category = KBEngine)
		TArray<TSubclassOf<class APlayerCarPawn>> PlayerCarPawnClassArray;
};
