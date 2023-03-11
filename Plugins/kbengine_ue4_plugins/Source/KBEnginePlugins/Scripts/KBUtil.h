// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/GameEngine.h"
#include "KBUtil.generated.h"


//框架自定义Debug输出类
#pragma region LogDebug

class KBENGINEPLUGINS_API DDRecord
{
private:
	//自身单例
	static TSharedPtr<DDRecord> RecordInst;

	//生成的字符串
	FString RecordInfo;

	//显示时间
	float ShowTime;

	//显示颜色
	FColor ShowColor;

public:

	//打印模式, 0 : Debug, 1 : Log, 2 : Warning, 3 : Error
	uint8 PatternID;

public:

	//构造函数
	inline DDRecord() {}

	~DDRecord() {}

	static TSharedPtr<DDRecord> Get();

	//设定参数
	inline void InitParam(float InTime, FColor InColor)
	{
		ShowTime = InTime;
		ShowColor = InColor;
	}

	//执行打印方法
	inline void Output() {
		switch (PatternID)
		{
		case 0:
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, ShowTime, ShowColor, RecordInfo);
		}
		break;
		case 1:
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *RecordInfo);
		}
		break;
		case 2:
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *RecordInfo);
		}
		break;
		case 3:
		{
			UE_LOG(LogTemp, Error, TEXT("%s"), *RecordInfo);
		}
		break;
		}
		//清空字符串
		RecordInfo.Empty();
	}

	//重写操作符<<
	inline DDRecord& operator<<(FString Info) { RecordInfo.Append(Info); return *this; }
	inline DDRecord& operator<<(FName Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FText Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(const char* Info) { RecordInfo += Info; return *this; }
	inline DDRecord& operator<<(const char Info) { RecordInfo.AppendChar(Info); return *this; }
	inline DDRecord& operator<<(int32 Info) { RecordInfo.Append(FString::FromInt(Info)); return *this; }
	inline DDRecord& operator<<(uint8 Info) { RecordInfo.Append(FString::FromInt(Info)); return *this; }
	inline DDRecord& operator<<(uint64 Info) { RecordInfo.Append(FString::FromInt(Info)); return *this; }
	inline DDRecord& operator<<(float Info) { RecordInfo.Append(FString::SanitizeFloat(Info)); return *this; }
	inline DDRecord& operator<<(double Info) { RecordInfo.Append(FString::SanitizeFloat(Info)); return *this; }
	inline DDRecord& operator<<(bool Info) { RecordInfo.Append(Info ? FString("true") : FString("false")); return *this; }
	inline DDRecord& operator<<(FVector2D Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FVector Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FRotator Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FQuat Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FTransform Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FMatrix Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FColor Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FLinearColor Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FMargin Info) { RecordInfo.Append((FString::SanitizeFloat(Info.Left) + FString(" , ") + FString::SanitizeFloat(Info.Top) + FString(" , ") + FString::SanitizeFloat(Info.Right) + FString(" , ") + FString::SanitizeFloat(Info.Bottom))); return *this; }

	//输出
	inline void operator<<(DDRecord& Record) { Record.Output(); }
};


//DDRecord::Get() << FString("sfdewhe") << FName << int << float << DDRecord::Get();


#pragma endregion


namespace DDH
{
	FORCEINLINE DDRecord& Debug(float InTime = 20.f, FColor InColor = FColor::Cyan)
	{
		DDRecord::Get()->PatternID = 0;
		DDRecord::Get()->InitParam(InTime, InColor);
		return *DDRecord::Get();
	}

	FORCEINLINE DDRecord& Debug(FColor InColor)
	{
		return Debug(3000.f, InColor);
	}

	FORCEINLINE DDRecord& Log()
	{
		DDRecord::Get()->PatternID = 1;
		return *DDRecord::Get();
	}

	FORCEINLINE DDRecord& Warning()
	{
		DDRecord::Get()->PatternID = 2;
		return *DDRecord::Get();
	}

	FORCEINLINE DDRecord& Error()
	{
		DDRecord::Get()->PatternID = 3;
		return *DDRecord::Get();
	}


	FORCEINLINE DDRecord& Endl()
	{
		return *DDRecord::Get();
	}

	//将传入的Enum值对应的FString输出, 直接输出Value对应的值
	template<typename TEnum>
	FORCEINLINE FString GetEnumValueAsString(const FString& Name, TEnum Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!EnumPtr)
			return FString("InValid");
		return EnumPtr->GetEnumName((int32)Value);
	}

	//将传入的Enum值对应的FName输出
	template<typename TEnum>
	FORCEINLINE FName GetEnumValueAsName(const FString& Name, TEnum Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!EnumPtr) {
			return FName("InValid");
		}
		return FName(*EnumPtr->GetEnumName((int32)Value));
	}

	//将传入的FName对应的Enum输出
	template<typename TEnum>
	FORCEINLINE TEnum GetEnumValueFromName(const FString& Name, FName Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!EnumPtr) {
			return TEnum(0);
		}
		return (TEnum)EnumPtr->GetIndexByName(Value);
	}

	//将传入的FName对应的Enum的序号输出
	FORCEINLINE int32 GetEnumIndexFromName(const FString& Name, FName Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, *Name, true);
		if (!EnumPtr) {
			return -1;
		}
		return EnumPtr->GetIndexByName(Value);
	}

	namespace DGH
	{
		//计算向量夹角, 返回 0 - 360 度, 第一个向量为标定向量, 按顺时针方向计算
		FORCEINLINE float CalcVectorAngle(FVector ArcVec, FVector DesVec)
		{
			ArcVec.Normalize();
			DesVec.Normalize();
			float ResAngle = (FVector::CrossProduct(ArcVec, DesVec).Z > 0 ? 1.f : -1.f) * FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(ArcVec, DesVec)));
			if (ResAngle < 0.f) ResAngle += 360.f;
			return ResAngle;
		}
		FORCEINLINE float CalcVector2DAngle(FVector2D ArcVec, FVector2D DesVec)
		{
			ArcVec.Normalize();
			DesVec.Normalize();
			float ResAngle = (FVector2D::CrossProduct(ArcVec, DesVec) > 0 ? 1.f : -1.f) * FMath::RadiansToDegrees(FMath::Acos(FVector2D::DotProduct(ArcVec, DesVec)));
			if (ResAngle < 0.f) ResAngle += 360.f;
			return ResAngle;
		}
	}
}

/**
 * 
 */
UCLASS()
class KBENGINEPLUGINS_API UKBUtil : public UObject
{
	GENERATED_BODY()

public:

	static UKBUtil* Get();

	FVector GetPlayerPos() const;

	void SetPlayerPos(FVector InPos);

	FVector GetCameraPos() const;

	void SetCameraPos(FVector InPos);

protected:

	static UKBUtil* KBInstance;

	FVector PlayerPos;

	FVector CameraPos;
	
};
