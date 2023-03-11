// Fill out your copyright notice in the Description page of Project Settings.


#include "KBUtil.h"

TSharedPtr<DDRecord> DDRecord::RecordInst = nullptr;

TSharedPtr<DDRecord> DDRecord::Get()
{
	if (!RecordInst.IsValid())
		RecordInst = MakeShareable(new DDRecord());
	return RecordInst;
}

UKBUtil* UKBUtil::KBInstance = nullptr;

UKBUtil* UKBUtil::Get()
{
	if (!KBInstance)
	{
		KBInstance = NewObject<UKBUtil>();
		KBInstance->AddToRoot();
	}
	return KBInstance;
}

FVector UKBUtil::GetPlayerPos() const
{
	return PlayerPos;
}

void UKBUtil::SetPlayerPos(FVector InPos)
{
	PlayerPos = InPos;
}

FVector UKBUtil::GetCameraPos() const
{
	return CameraPos;
}

void UKBUtil::SetCameraPos(FVector InPos)
{
	CameraPos = InPos;
}
