/*
	Generated by KBEngine!
	Please do not modify this file!
	
	tools = kbcmd
*/

namespace KBEngine
{
	using UnityEngine;
	using System;
	using System.Collections;
	using System.Collections.Generic;

	// defined in */scripts/entity_defs/NPC.def
	public class EntityBaseEntityCall_NPCBase : EntityCall
	{

		public EntityBaseEntityCall_NPCBase(Int32 eid, string ename) : base(eid, ename)
		{
			type = ENTITYCALL_TYPE.ENTITYCALL_TYPE_BASE;
		}

	}

	public class EntityCellEntityCall_NPCBase : EntityCall
	{

		public EntityCellEntityCall_NPCBase(Int32 eid, string ename) : base(eid, ename)
		{
			type = ENTITYCALL_TYPE.ENTITYCALL_TYPE_CELL;
		}

		public void AnimUpdate(ANIM_INFO arg1)
		{
			Bundle pBundle = newCall("AnimUpdate", 0);
			if(pBundle == null)
				return;

			((DATATYPE_ANIM_INFO)EntityDef.id2datatypes[28]).addToStreamEx(bundle, arg1);
			sendCall(null);
		}

		public void HoverCarMoveSpeedUpdate(HOVERCAR_INFO arg1)
		{
			Bundle pBundle = newCall("HoverCarMoveSpeedUpdate", 0);
			if(pBundle == null)
				return;

			((DATATYPE_HOVERCAR_INFO)EntityDef.id2datatypes[30]).addToStreamEx(bundle, arg1);
			sendCall(null);
		}

		public void StageAnimUpdate(STAGEANIM_INFO arg1)
		{
			Bundle pBundle = newCall("StageAnimUpdate", 0);
			if(pBundle == null)
				return;

			((DATATYPE_STAGEANIM_INFO)EntityDef.id2datatypes[29]).addToStreamEx(bundle, arg1);
			sendCall(null);
		}

	}
	}
