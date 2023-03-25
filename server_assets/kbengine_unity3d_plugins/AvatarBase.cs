/*
	Generated by KBEngine!
	Please do not modify this file!
	Please inherit this module, such as: (class Avatar : AvatarBase)
	tools = kbcmd
*/

namespace KBEngine
{
	using UnityEngine;
	using System;
	using System.Collections;
	using System.Collections.Generic;

	// defined in */scripts/entity_defs/Avatar.def
	// Please inherit and implement "class Avatar : AvatarBase"
	public abstract class AvatarBase : Entity
	{
		public EntityBaseEntityCall_AvatarBase baseEntityCall = null;
		public EntityCellEntityCall_AvatarBase cellEntityCall = null;

		public Int32 HP = 0;
		public virtual void onHPChanged(Int32 oldValue) {}
		public Int32 HP_Max = 0;
		public virtual void onHP_MaxChanged(Int32 oldValue) {}
		public Int32 MP = 0;
		public virtual void onMPChanged(Int32 oldValue) {}
		public Int32 MP_Max = 0;
		public virtual void onMP_MaxChanged(Int32 oldValue) {}
		public TestBase component1 = null;
		public TestBase component2 = null;
		public TestNoBaseBase component3 = null;
		public Int32 forbids = 0;
		public virtual void onForbidsChanged(Int32 oldValue) {}
		public UInt16 level = 0;
		public virtual void onLevelChanged(UInt16 oldValue) {}
		public UInt32 modelID = 0;
		public virtual void onModelIDChanged(UInt32 oldValue) {}
		public Byte modelScale = 30;
		public virtual void onModelScaleChanged(Byte oldValue) {}
		public Byte moveSpeed = 50;
		public virtual void onMoveSpeedChanged(Byte oldValue) {}
		public string name = "";
		public virtual void onNameChanged(string oldValue) {}
		public UInt16 own_val = 0;
		public virtual void onOwn_valChanged(UInt16 oldValue) {}
		public UInt32 spaceUType = 0;
		public virtual void onSpaceUTypeChanged(UInt32 oldValue) {}
		public SByte state = 0;
		public virtual void onStateChanged(SByte oldValue) {}
		public Byte subState = 0;
		public virtual void onSubStateChanged(Byte oldValue) {}
		public UInt32 uid = 0;
		public virtual void onUidChanged(UInt32 oldValue) {}
		public UInt32 utype = 0;
		public virtual void onUtypeChanged(UInt32 oldValue) {}

		public abstract void OnAnimUpdate(ANIM_INFO arg1); 
		public abstract void OnHoverCarMoveSpeedUpdate(HOVERCAR_INFO arg1); 
		public abstract void OnStageAnimUpdate(STAGEANIM_INFO arg1); 
		public abstract void dialog_addOption(Byte arg1, UInt32 arg2, string arg3, Int32 arg4); 
		public abstract void dialog_close(); 
		public abstract void dialog_setText(string arg1, Byte arg2, UInt32 arg3, string arg4); 
		public abstract void onAddSkill(Int32 arg1); 
		public abstract void onJump(); 
		public abstract void onRemoveSkill(Int32 arg1); 
		public abstract void recvDamage(Int32 arg1, Int32 arg2, Int32 arg3, Int32 arg4); 

		public AvatarBase()
		{
			foreach (System.Reflection.Assembly ass in AppDomain.CurrentDomain.GetAssemblies())
			{
				Type entityComponentScript = ass.GetType("KBEngine.Test");
				if(entityComponentScript != null)
				{
					component1 = (TestBase)Activator.CreateInstance(entityComponentScript);
					component1.owner = this;
					component1.entityComponentPropertyID = 16;
					component1.name_ = "Test";
				}
			}

			if(component1 == null)
				throw new Exception("Please inherit and implement, such as: \"class Test : TestBase\"");

			foreach (System.Reflection.Assembly ass in AppDomain.CurrentDomain.GetAssemblies())
			{
				Type entityComponentScript = ass.GetType("KBEngine.Test");
				if(entityComponentScript != null)
				{
					component2 = (TestBase)Activator.CreateInstance(entityComponentScript);
					component2.owner = this;
					component2.entityComponentPropertyID = 21;
					component2.name_ = "Test";
				}
			}

			if(component2 == null)
				throw new Exception("Please inherit and implement, such as: \"class Test : TestBase\"");

			foreach (System.Reflection.Assembly ass in AppDomain.CurrentDomain.GetAssemblies())
			{
				Type entityComponentScript = ass.GetType("KBEngine.TestNoBase");
				if(entityComponentScript != null)
				{
					component3 = (TestNoBaseBase)Activator.CreateInstance(entityComponentScript);
					component3.owner = this;
					component3.entityComponentPropertyID = 22;
					component3.name_ = "TestNoBase";
				}
			}

			if(component3 == null)
				throw new Exception("Please inherit and implement, such as: \"class TestNoBase : TestNoBaseBase\"");

		}

		public override void onComponentsEnterworld()
		{
			component1.onEnterworld();
			component2.onEnterworld();
			component3.onEnterworld();
		}

		public override void onComponentsLeaveworld()
		{
			component1.onLeaveworld();
			component2.onLeaveworld();
			component3.onLeaveworld();
		}

		public override List<EntityComponent> getComponents(string componentName, bool all)
		{
			List<EntityComponent> founds = new List<EntityComponent>();

			if (component1.name_ == componentName)
			{
				founds.Add(component1);
				if (!all)
					return founds;
			}

			if (component2.name_ == componentName)
			{
				founds.Add(component2);
				if (!all)
					return founds;
			}

			if (component3.name_ == componentName)
			{
				founds.Add(component3);
				if (!all)
					return founds;
			}

			return founds;
		}

		public override void onGetBase()
		{
			baseEntityCall = new EntityBaseEntityCall_AvatarBase(id, className);
			component1.onGetBase();
			component2.onGetBase();
			component3.onGetBase();
		}

		public override void onGetCell()
		{
			cellEntityCall = new EntityCellEntityCall_AvatarBase(id, className);
			component1.onGetCell();
			component2.onGetCell();
			component3.onGetCell();
		}

		public override void onLoseCell()
		{
			cellEntityCall = null;
			component1.onLoseCell();
			component2.onLoseCell();
			component3.onLoseCell();
		}

		public override EntityCall getBaseEntityCall()
		{
			return baseEntityCall;
		}

		public override EntityCall getCellEntityCall()
		{
			return cellEntityCall;
		}

		public override void attachComponents()
		{
			component1.onAttached(this);
			component2.onAttached(this);
			component3.onAttached(this);
		}

		public override void detachComponents()
		{
			component1.onDetached(this);
			component2.onDetached(this);
			component3.onDetached(this);
		}

		public override void onRemoteMethodCall(MemoryStream stream)
		{
			ScriptModule sm = EntityDef.moduledefs["Avatar"];

			UInt16 methodUtype = 0;
			UInt16 componentPropertyUType = 0;

			if(sm.usePropertyDescrAlias)
			{
				componentPropertyUType = stream.readUint8();
			}
			else
			{
				componentPropertyUType = stream.readUint16();
			}

			if(sm.useMethodDescrAlias)
			{
				methodUtype = stream.readUint8();
			}
			else
			{
				methodUtype = stream.readUint16();
			}

			Method method = null;

			if(componentPropertyUType == 0)
			{
				method = sm.idmethods[methodUtype];
			}
			else
			{
				Property pComponentPropertyDescription = sm.idpropertys[componentPropertyUType];
				switch(pComponentPropertyDescription.properUtype)
				{
					case 16:
						component1.onRemoteMethodCall(methodUtype, stream);
						break;
					case 21:
						component2.onRemoteMethodCall(methodUtype, stream);
						break;
					case 22:
						component3.onRemoteMethodCall(methodUtype, stream);
						break;
					default:
						break;
				}

				return;
			}

			switch(method.methodUtype)
			{
				case 12:
					ANIM_INFO OnAnimUpdate_arg1 = ((DATATYPE_ANIM_INFO)method.args[0]).createFromStreamEx(stream);
					OnAnimUpdate(OnAnimUpdate_arg1);
					break;
				case 13:
					HOVERCAR_INFO OnHoverCarMoveSpeedUpdate_arg1 = ((DATATYPE_HOVERCAR_INFO)method.args[0]).createFromStreamEx(stream);
					OnHoverCarMoveSpeedUpdate(OnHoverCarMoveSpeedUpdate_arg1);
					break;
				case 14:
					STAGEANIM_INFO OnStageAnimUpdate_arg1 = ((DATATYPE_STAGEANIM_INFO)method.args[0]).createFromStreamEx(stream);
					OnStageAnimUpdate(OnStageAnimUpdate_arg1);
					break;
				case 10101:
					Byte dialog_addOption_arg1 = stream.readUint8();
					UInt32 dialog_addOption_arg2 = stream.readUint32();
					string dialog_addOption_arg3 = stream.readUnicode();
					Int32 dialog_addOption_arg4 = stream.readInt32();
					dialog_addOption(dialog_addOption_arg1, dialog_addOption_arg2, dialog_addOption_arg3, dialog_addOption_arg4);
					break;
				case 10104:
					dialog_close();
					break;
				case 10102:
					string dialog_setText_arg1 = stream.readUnicode();
					Byte dialog_setText_arg2 = stream.readUint8();
					UInt32 dialog_setText_arg3 = stream.readUint32();
					string dialog_setText_arg4 = stream.readUnicode();
					dialog_setText(dialog_setText_arg1, dialog_setText_arg2, dialog_setText_arg3, dialog_setText_arg4);
					break;
				case 18:
					Int32 onAddSkill_arg1 = stream.readInt32();
					onAddSkill(onAddSkill_arg1);
					break;
				case 7:
					onJump();
					break;
				case 19:
					Int32 onRemoveSkill_arg1 = stream.readInt32();
					onRemoveSkill(onRemoveSkill_arg1);
					break;
				case 22:
					Int32 recvDamage_arg1 = stream.readInt32();
					Int32 recvDamage_arg2 = stream.readInt32();
					Int32 recvDamage_arg3 = stream.readInt32();
					Int32 recvDamage_arg4 = stream.readInt32();
					recvDamage(recvDamage_arg1, recvDamage_arg2, recvDamage_arg3, recvDamage_arg4);
					break;
				default:
					break;
			};
		}

		public override void onUpdatePropertys(MemoryStream stream)
		{
			ScriptModule sm = EntityDef.moduledefs["Avatar"];
			Dictionary<UInt16, Property> pdatas = sm.idpropertys;

			while(stream.length() > 0)
			{
				UInt16 _t_utype = 0;
				UInt16 _t_child_utype = 0;

				{
					if(sm.usePropertyDescrAlias)
					{
						_t_utype = stream.readUint8();
						_t_child_utype = stream.readUint8();
					}
					else
					{
						_t_utype = stream.readUint16();
						_t_child_utype = stream.readUint16();
					}
				}

				Property prop = null;

				if(_t_utype == 0)
				{
					prop = pdatas[_t_child_utype];
				}
				else
				{
					Property pComponentPropertyDescription = pdatas[_t_utype];
					switch(pComponentPropertyDescription.properUtype)
					{
						case 16:
							component1.onUpdatePropertys(_t_child_utype, stream, -1);
							break;
						case 21:
							component2.onUpdatePropertys(_t_child_utype, stream, -1);
							break;
						case 22:
							component3.onUpdatePropertys(_t_child_utype, stream, -1);
							break;
						default:
							break;
					}

					return;
				}

				switch(prop.properUtype)
				{
					case 47001:
						Int32 oldval_HP = HP;
						HP = stream.readInt32();

						if(prop.isBase())
						{
							if(inited)
								onHPChanged(oldval_HP);
						}
						else
						{
							if(inWorld)
								onHPChanged(oldval_HP);
						}

						break;
					case 47002:
						Int32 oldval_HP_Max = HP_Max;
						HP_Max = stream.readInt32();

						if(prop.isBase())
						{
							if(inited)
								onHP_MaxChanged(oldval_HP_Max);
						}
						else
						{
							if(inWorld)
								onHP_MaxChanged(oldval_HP_Max);
						}

						break;
					case 47003:
						Int32 oldval_MP = MP;
						MP = stream.readInt32();

						if(prop.isBase())
						{
							if(inited)
								onMPChanged(oldval_MP);
						}
						else
						{
							if(inWorld)
								onMPChanged(oldval_MP);
						}

						break;
					case 47004:
						Int32 oldval_MP_Max = MP_Max;
						MP_Max = stream.readInt32();

						if(prop.isBase())
						{
							if(inited)
								onMP_MaxChanged(oldval_MP_Max);
						}
						else
						{
							if(inWorld)
								onMP_MaxChanged(oldval_MP_Max);
						}

						break;
					case 16:
						component1.createFromStream(stream);
						break;
					case 21:
						component2.createFromStream(stream);
						break;
					case 22:
						component3.createFromStream(stream);
						break;
					case 40001:
						Vector3 oldval_direction = direction;
						direction = stream.readVector3();

						if(prop.isBase())
						{
							if(inited)
								onDirectionChanged(oldval_direction);
						}
						else
						{
							if(inWorld)
								onDirectionChanged(oldval_direction);
						}

						break;
					case 47005:
						Int32 oldval_forbids = forbids;
						forbids = stream.readInt32();

						if(prop.isBase())
						{
							if(inited)
								onForbidsChanged(oldval_forbids);
						}
						else
						{
							if(inWorld)
								onForbidsChanged(oldval_forbids);
						}

						break;
					case 41002:
						UInt16 oldval_level = level;
						level = stream.readUint16();

						if(prop.isBase())
						{
							if(inited)
								onLevelChanged(oldval_level);
						}
						else
						{
							if(inWorld)
								onLevelChanged(oldval_level);
						}

						break;
					case 41006:
						UInt32 oldval_modelID = modelID;
						modelID = stream.readUint32();

						if(prop.isBase())
						{
							if(inited)
								onModelIDChanged(oldval_modelID);
						}
						else
						{
							if(inWorld)
								onModelIDChanged(oldval_modelID);
						}

						break;
					case 41007:
						Byte oldval_modelScale = modelScale;
						modelScale = stream.readUint8();

						if(prop.isBase())
						{
							if(inited)
								onModelScaleChanged(oldval_modelScale);
						}
						else
						{
							if(inWorld)
								onModelScaleChanged(oldval_modelScale);
						}

						break;
					case 11:
						Byte oldval_moveSpeed = moveSpeed;
						moveSpeed = stream.readUint8();

						if(prop.isBase())
						{
							if(inited)
								onMoveSpeedChanged(oldval_moveSpeed);
						}
						else
						{
							if(inWorld)
								onMoveSpeedChanged(oldval_moveSpeed);
						}

						break;
					case 41003:
						string oldval_name = name;
						name = stream.readUnicode();

						if(prop.isBase())
						{
							if(inited)
								onNameChanged(oldval_name);
						}
						else
						{
							if(inWorld)
								onNameChanged(oldval_name);
						}

						break;
					case 6:
						UInt16 oldval_own_val = own_val;
						own_val = stream.readUint16();

						if(prop.isBase())
						{
							if(inited)
								onOwn_valChanged(oldval_own_val);
						}
						else
						{
							if(inWorld)
								onOwn_valChanged(oldval_own_val);
						}

						break;
					case 40000:
						Vector3 oldval_position = position;
						position = stream.readVector3();

						if(prop.isBase())
						{
							if(inited)
								onPositionChanged(oldval_position);
						}
						else
						{
							if(inWorld)
								onPositionChanged(oldval_position);
						}

						break;
					case 40002:
						stream.readUint32();
						break;
					case 41001:
						UInt32 oldval_spaceUType = spaceUType;
						spaceUType = stream.readUint32();

						if(prop.isBase())
						{
							if(inited)
								onSpaceUTypeChanged(oldval_spaceUType);
						}
						else
						{
							if(inWorld)
								onSpaceUTypeChanged(oldval_spaceUType);
						}

						break;
					case 47006:
						SByte oldval_state = state;
						state = stream.readInt8();

						if(prop.isBase())
						{
							if(inited)
								onStateChanged(oldval_state);
						}
						else
						{
							if(inWorld)
								onStateChanged(oldval_state);
						}

						break;
					case 47007:
						Byte oldval_subState = subState;
						subState = stream.readUint8();

						if(prop.isBase())
						{
							if(inited)
								onSubStateChanged(oldval_subState);
						}
						else
						{
							if(inWorld)
								onSubStateChanged(oldval_subState);
						}

						break;
					case 41004:
						UInt32 oldval_uid = uid;
						uid = stream.readUint32();

						if(prop.isBase())
						{
							if(inited)
								onUidChanged(oldval_uid);
						}
						else
						{
							if(inWorld)
								onUidChanged(oldval_uid);
						}

						break;
					case 41005:
						UInt32 oldval_utype = utype;
						utype = stream.readUint32();

						if(prop.isBase())
						{
							if(inited)
								onUtypeChanged(oldval_utype);
						}
						else
						{
							if(inWorld)
								onUtypeChanged(oldval_utype);
						}

						break;
					default:
						break;
				};
			}
		}

		public override void callPropertysSetMethods()
		{
			ScriptModule sm = EntityDef.moduledefs["Avatar"];
			Dictionary<UInt16, Property> pdatas = sm.idpropertys;

			Int32 oldval_HP = HP;
			Property prop_HP = pdatas[4];
			if(prop_HP.isBase())
			{
				if(inited && !inWorld)
					onHPChanged(oldval_HP);
			}
			else
			{
				if(inWorld)
				{
					if(prop_HP.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onHPChanged(oldval_HP);
					}
				}
			}

			Int32 oldval_HP_Max = HP_Max;
			Property prop_HP_Max = pdatas[5];
			if(prop_HP_Max.isBase())
			{
				if(inited && !inWorld)
					onHP_MaxChanged(oldval_HP_Max);
			}
			else
			{
				if(inWorld)
				{
					if(prop_HP_Max.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onHP_MaxChanged(oldval_HP_Max);
					}
				}
			}

			Int32 oldval_MP = MP;
			Property prop_MP = pdatas[6];
			if(prop_MP.isBase())
			{
				if(inited && !inWorld)
					onMPChanged(oldval_MP);
			}
			else
			{
				if(inWorld)
				{
					if(prop_MP.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onMPChanged(oldval_MP);
					}
				}
			}

			Int32 oldval_MP_Max = MP_Max;
			Property prop_MP_Max = pdatas[7];
			if(prop_MP_Max.isBase())
			{
				if(inited && !inWorld)
					onMP_MaxChanged(oldval_MP_Max);
			}
			else
			{
				if(inWorld)
				{
					if(prop_MP_Max.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onMP_MaxChanged(oldval_MP_Max);
					}
				}
			}

			component1.callPropertysSetMethods();

			component2.callPropertysSetMethods();

			component3.callPropertysSetMethods();

			Vector3 oldval_direction = direction;
			Property prop_direction = pdatas[2];
			if(prop_direction.isBase())
			{
				if(inited && !inWorld)
					onDirectionChanged(oldval_direction);
			}
			else
			{
				if(inWorld)
				{
					if(prop_direction.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onDirectionChanged(oldval_direction);
					}
				}
			}

			Int32 oldval_forbids = forbids;
			Property prop_forbids = pdatas[11];
			if(prop_forbids.isBase())
			{
				if(inited && !inWorld)
					onForbidsChanged(oldval_forbids);
			}
			else
			{
				if(inWorld)
				{
					if(prop_forbids.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onForbidsChanged(oldval_forbids);
					}
				}
			}

			UInt16 oldval_level = level;
			Property prop_level = pdatas[12];
			if(prop_level.isBase())
			{
				if(inited && !inWorld)
					onLevelChanged(oldval_level);
			}
			else
			{
				if(inWorld)
				{
					if(prop_level.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onLevelChanged(oldval_level);
					}
				}
			}

			UInt32 oldval_modelID = modelID;
			Property prop_modelID = pdatas[13];
			if(prop_modelID.isBase())
			{
				if(inited && !inWorld)
					onModelIDChanged(oldval_modelID);
			}
			else
			{
				if(inWorld)
				{
					if(prop_modelID.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onModelIDChanged(oldval_modelID);
					}
				}
			}

			Byte oldval_modelScale = modelScale;
			Property prop_modelScale = pdatas[14];
			if(prop_modelScale.isBase())
			{
				if(inited && !inWorld)
					onModelScaleChanged(oldval_modelScale);
			}
			else
			{
				if(inWorld)
				{
					if(prop_modelScale.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onModelScaleChanged(oldval_modelScale);
					}
				}
			}

			Byte oldval_moveSpeed = moveSpeed;
			Property prop_moveSpeed = pdatas[15];
			if(prop_moveSpeed.isBase())
			{
				if(inited && !inWorld)
					onMoveSpeedChanged(oldval_moveSpeed);
			}
			else
			{
				if(inWorld)
				{
					if(prop_moveSpeed.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onMoveSpeedChanged(oldval_moveSpeed);
					}
				}
			}

			string oldval_name = name;
			Property prop_name = pdatas[16];
			if(prop_name.isBase())
			{
				if(inited && !inWorld)
					onNameChanged(oldval_name);
			}
			else
			{
				if(inWorld)
				{
					if(prop_name.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onNameChanged(oldval_name);
					}
				}
			}

			UInt16 oldval_own_val = own_val;
			Property prop_own_val = pdatas[17];
			if(prop_own_val.isBase())
			{
				if(inited && !inWorld)
					onOwn_valChanged(oldval_own_val);
			}
			else
			{
				if(inWorld)
				{
					if(prop_own_val.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onOwn_valChanged(oldval_own_val);
					}
				}
			}

			Vector3 oldval_position = position;
			Property prop_position = pdatas[1];
			if(prop_position.isBase())
			{
				if(inited && !inWorld)
					onPositionChanged(oldval_position);
			}
			else
			{
				if(inWorld)
				{
					if(prop_position.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onPositionChanged(oldval_position);
					}
				}
			}

			UInt32 oldval_spaceUType = spaceUType;
			Property prop_spaceUType = pdatas[18];
			if(prop_spaceUType.isBase())
			{
				if(inited && !inWorld)
					onSpaceUTypeChanged(oldval_spaceUType);
			}
			else
			{
				if(inWorld)
				{
					if(prop_spaceUType.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onSpaceUTypeChanged(oldval_spaceUType);
					}
				}
			}

			SByte oldval_state = state;
			Property prop_state = pdatas[19];
			if(prop_state.isBase())
			{
				if(inited && !inWorld)
					onStateChanged(oldval_state);
			}
			else
			{
				if(inWorld)
				{
					if(prop_state.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onStateChanged(oldval_state);
					}
				}
			}

			Byte oldval_subState = subState;
			Property prop_subState = pdatas[20];
			if(prop_subState.isBase())
			{
				if(inited && !inWorld)
					onSubStateChanged(oldval_subState);
			}
			else
			{
				if(inWorld)
				{
					if(prop_subState.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onSubStateChanged(oldval_subState);
					}
				}
			}

			UInt32 oldval_uid = uid;
			Property prop_uid = pdatas[21];
			if(prop_uid.isBase())
			{
				if(inited && !inWorld)
					onUidChanged(oldval_uid);
			}
			else
			{
				if(inWorld)
				{
					if(prop_uid.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onUidChanged(oldval_uid);
					}
				}
			}

			UInt32 oldval_utype = utype;
			Property prop_utype = pdatas[22];
			if(prop_utype.isBase())
			{
				if(inited && !inWorld)
					onUtypeChanged(oldval_utype);
			}
			else
			{
				if(inWorld)
				{
					if(prop_utype.isOwnerOnly() && !isPlayer())
					{
					}
					else
					{
						onUtypeChanged(oldval_utype);
					}
				}
			}

		}
	}
}