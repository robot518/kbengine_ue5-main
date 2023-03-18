/*
	Generated by KBEngine!
	Please do not modify this file!
	
	tools = kbcmd
*/

#pragma once

#include "KBECommon.h"
#include "EntityCall.h"
#include "KBETypes.h"
#include "CustomDataTypes.h"

#include "EntityCallTestBase.h"
#include "EntityCallTestNoBaseBase.h"

// defined in */scripts/entity_defs/Avatar.def

namespace KBEngine
{

class KBENGINEPLUGINS_API EntityBaseEntityCall_AvatarBase : public EntityCall
{
public:
	EntityBaseEntityCall_TestBase* component1;
	EntityBaseEntityCall_TestBase* component2;
	EntityBaseEntityCall_TestNoBaseBase* component3;

	EntityBaseEntityCall_AvatarBase(int32 eid, const FString& ename);

	virtual ~EntityBaseEntityCall_AvatarBase();
};

class KBENGINEPLUGINS_API EntityCellEntityCall_AvatarBase : public EntityCall
{
public:
	EntityCellEntityCall_TestBase* component1;
	EntityCellEntityCall_TestBase* component2;
	EntityCellEntityCall_TestNoBaseBase* component3;

	EntityCellEntityCall_AvatarBase(int32 eid, const FString& ename);

	virtual ~EntityCellEntityCall_AvatarBase();
	void AnimUpdate(const ANIM_INFO& arg1);
	void HoverCarMoveSpeedUpdate(const HOVERCAR_INFO& arg1);
	void dialog(int32 arg1, uint32 arg2);
	void jump();
	void relive(uint8 arg1);
	void requestPull();
	void useTargetSkill(int32 arg1, int32 arg2);
};

}