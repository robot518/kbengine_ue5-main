#include "EntityCallNPCBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_NPCBase::EntityBaseEntityCall_NPCBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_NPCBase::~EntityBaseEntityCall_NPCBase()
{
}



EntityCellEntityCall_NPCBase::EntityCellEntityCall_NPCBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_NPCBase::~EntityCellEntityCall_NPCBase()
{
}

void EntityCellEntityCall_NPCBase::AnimUpdate(const ANIM_INFO& arg1)
{
	Bundle* pBundleRet = newCall("AnimUpdate", 0);
	if(!pBundleRet)
		return;

	//((DATATYPE_ANIM_INFO*)EntityDef::id2datatypes[28])->addToStreamEx(*pBundleRet, arg1);
	sendCall(NULL);
}


}