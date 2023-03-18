#include "EntityCallMonsterBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_MonsterBase::EntityBaseEntityCall_MonsterBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_MonsterBase::~EntityBaseEntityCall_MonsterBase()
{
}



EntityCellEntityCall_MonsterBase::EntityCellEntityCall_MonsterBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_MonsterBase::~EntityCellEntityCall_MonsterBase()
{
}

void EntityCellEntityCall_MonsterBase::AnimUpdate(const ANIM_INFO& arg1)
{
	Bundle* pBundleRet = newCall("AnimUpdate", 0);
	if(!pBundleRet)
		return;

	//((DATATYPE_ANIM_INFO*)EntityDef::id2datatypes[28])->addToStreamEx(*pBundleRet, arg1);
	sendCall(NULL);
}


}