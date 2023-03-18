#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameEntity.generated.h"

const int ModelID_NPC = 1002;
const int ModelID_Monster1 = 1003;
const int ModelID_Monster2 = 1004;
const int ModelID_Gate = 40001001;
const int ModelID_Avatar = 90000001;

class UBoxComponent;

UCLASS()
class KBEDEMO_API AGameEntity : public ACharacter
{
	GENERATED_BODY()

public:
	// 设置此 empty 属性的默认值
	AGameEntity();

protected:
	// 已在游戏开始或生成时调用
	virtual void BeginPlay() override;

	/** Called once this actor has been deleted */
	virtual void Destroyed() override;

	static FName GroundName;

public:
	// 已调用每个帧
	virtual void Tick(float DeltaTime) override;

	// 调用以绑定要输出的功能
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	virtual bool isPlayer() {
		return false;
	}

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f) override;

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void updateLocation(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void OnOverlapBegin(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void OnOverlapEnd(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void setTargetLocation(const FVector& loc)
	{
		targetLocation = loc;
	}

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void setTargetRotator(const FRotator3f& rot)
	{
		targetRotator = (FRotator)rot;
	}

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void setIsOnGround(bool onGround)
	{
		isOnGround = onGround;
	}

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	virtual void setModelID(int modelID);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	float modelScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int modelID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	float moveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	int entityID;

	// 实体将要移动到的目的地位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FVector targetLocation;

	// 实体将要移动到的目的朝向
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	FRotator targetRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
	bool isOnGround;

	UPROPERTY(BlueprintReadOnly)
		float AnimSpeed;

	UPROPERTY(BlueprintReadOnly)
		float AnimDirection;

	UPROPERTY(BlueprintReadOnly)
		bool AnimIsInAir;

	UPROPERTY(EditAnyWhere)
		TObjectPtr<UBoxComponent> GroundBox;

	//上一次同步动作时间
	float LastUpdateAnimTime;
	//更新动作时间间隔
	float UpdateAnimSpaceTime;
	//剩余动作更新时间
	float RemainAnimSpaceTime;

	void SetTargetAnim(float Speed, float Direction);

	//目标动作和角度
	float TargetSpeed;

	float TargetDirection;

	//上一次的速度和角度
	float LastSpeed;

	float LastDirection;

private:
	void createAvatar();
	void createMonster();

};
