#pragma once

#include "CoreMinimal.h"
#include "HoverCarSpawn.h"
#include "HoverPlayerCarSpawn.generated.h"

UCLASS()
class KBEDEMO_API AHoverPlayerCarSpawn : public AHoverCarSpawn
{
	GENERATED_BODY()

public:
	// 设置此 pawn 属性的默认值
	AHoverPlayerCarSpawn();

protected:
	// 已在游戏开始或生成时调用
	virtual void BeginPlay() override;

	/** Called once this actor has been deleted */
	virtual void Destroyed() override;

public:
	// 已调用每个帧
	virtual void Tick(float DeltaTime) override;

	// 调用以绑定要输出的功能
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//UFUNCTION(BlueprintCallable, Category = "KBEngine")
	virtual bool isPlayer() override {
		return true;
	}

	virtual void setModelID(int sub_modelID) override {
		this->modelID = sub_modelID;
	}

	FTimerHandle MoveUpdateHandle;

	void MoveUpdate();

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void SetHoverCarSpeed(float speed) {
		HoverCarMoveSpeed = speed;
	}
};
