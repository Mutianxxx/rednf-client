function checkExecutableSkill_gunner_fastdraw(obj)
{
	if(!obj) return false; 
	if(obj.getWeaponSubType() != 0) return false;//���O������^�� �����ϥΧޯ�
	local useskill = obj.sq_IsUseSkill(SKILL_GUNNER_FASTDRAW); 
	if(useskill) 
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0); 
		obj.sq_IntVectPush(onGetLeftOrRight_gunner_fastdraw(obj, false)); 
		obj.sq_IntVectPush(onGetKeyDownDirection_gunner_fastdraw(obj)); 
		obj.sq_AddSetStatePacket(STATE_GUNNER_FASTDRAW, STATE_PRIORITY_USER, true); 
		return true; 
	}
	return false; 
}

function checkCommandEnable_gunner_fastdraw(obj)
{
	if(!obj) return false; 
	if(obj.getWeaponSubType() != 0) return false;//���O������^�� �����ϥΧޯ�
	local state = obj.sq_GetState(); 
	if(state == STATE_STAND) 
		return true; 
	if(state == STATE_ATTACK) 
	{
		return obj.sq_IsCommandEnable(SKILL_GUNNER_FASTDRAW); 
	}
	return true; 
}

function onCreateObject_gunner_fastdraw(obj, createObject)
{
	if(!obj) return;
	local state = obj.sq_GetState();
	if(state == STATE_GUNNER_FASTDRAW)
	{
		local Object = sq_GetCNRDObjectToCollisionObject(createObject); 
		if(Object && Object.getCollisionObjectIndex() == 22001)
		{
			obj.getVar("fastdraw").push_obj_vector(Object);
		}
	}
}

function onSetState_gunner_fastdraw(obj, state, datas, isResetTimer)
{
	if(!obj) return; 
	local substate0 = obj.sq_GetVectorData(datas, 0); 
	obj.setSkillSubState(substate0); 
	
	if(substate0 != 1)
	obj.sq_StopMove(); 
	local substate1 = obj.sq_GetVectorData(datas, 1); 
	local substate2 = obj.sq_GetVectorData(datas, 2); 
	switch(substate0)
	{
		case 0: 
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_GUNNER_FASTDRAW, false, "character/gunner/fastdraw/ap_fastdraw.nut", true);
			CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, 239, true);
			if(appendage)
			{
				local PHYSICAL_CRITICAL = 50;
				local change_appendage = appendage.sq_getChangeStatus("fastdraw");
				if(!change_appendage)
				{
					change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, 
					CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, 
					true, 0, APID_COMMON);
				}
				if(change_appendage)
				{
					change_appendage.clearParameter();
					change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, false, PHYSICAL_CRITICAL.tofloat());
				}
			}
			if(substate2 == ENUM_DIRECTION_UP) 
				obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_FASTDRAW_BODY_LEFTHANDSTART); 
			else 
				obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_FASTDRAW_BODY_LEFTHANDSTART_LOW); 
				obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_GUNNER_SUPPRESSINGFINISHFIRE); 
				obj.getVar().setBool(2,false); 
				obj.getVar().clear_vector(); 
				obj.getVar().push_vector(0); 
				obj.getVar().push_vector(0); 
			break;
			case 1: 
				local Xpox = 0; 
				local Zpox = 0; 
				switch(substate1)
				{
				case 1: 
					switch(substate2)
					{
						case ENUM_DIRECTION_UP: 
							Xpox = 64; 
							Zpox = 115; 
							obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_FASTDRAW_BODY_LEFTHANDSHOT); 
						break;
						case ENUM_DIRECTION_DOWN: 
							Xpox = 58; 
							Zpox = 79; 
							obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_FASTDRAW_BODY_LEFTHANDSHOT_LOW); 
						break;
					}
				break;
				case -1: 
					switch(substate2)
					{
						case ENUM_DIRECTION_UP: 
							Xpox = 110; 
							Zpox = 108; 
							obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_FASTDRAW_BODY_RIGHTHANDSHOT); 
						break;
						case ENUM_DIRECTION_DOWN: 
							Xpox = 111; 
							Zpox = 77; 
							obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_FASTDRAW_BODY_RIGHTHANDSHOT_LOW); 
						break;
					}
				break;
				}
				local AddDraw1 = sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/fastdraw/fastdraw_gunsmoke1.ani", Xpox, -1, Zpox); 
				local AddDraw2 = sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/fastdraw/fastdraw_shot" + sq_getRandom(1, 2).tostring() + "_a.ani", Xpox, 0, Zpox); 
				local AddDraw3 = sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/fastdraw/fastdraw_shock.ani", Xpox, 0, Zpox); 
				
				if(substate2 == ENUM_DIRECTION_DOWN)
				{
					sq_SetCustomRotate(AddDraw1, -0.349064); 
					sq_SetCustomRotate(AddDraw2, -0.349064); 
					sq_SetCustomRotate(AddDraw3, -0.349064); 
				}
				else
				sq_SetCustomRotate(AddDraw1, sq_ToRadian(sq_getRandom(0, 5).tofloat()) / [-1, 1][sq_getRandom(0, 1)]);
				if(obj.sq_IsMyControlObject())
				{
					if (substate2 == 2)
					{
						//sq_CreateParticle("character/gunner/particle/upattackrevolver.ptl", obj, Xpox, 0, Zpox, false, 0, 0, 1); 
						local particleCreater = null;
						particleCreater = obj.getVar("gunner_fastdraw").GetparticleCreaterMap("gunner_fastdraw", "passiveobject/character/gunner/particle/fastdrawbulletup.ptl", obj);
						particleCreater.Restart(0);
						particleCreater.SetPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(),Xpox),obj.getYPos(), Zpox);
						sq_AddParticleObject(obj, particleCreater);
					}
					if (substate2 == 3)
					{
						//sq_CreateParticle("character/gunner/particle/downattackrevolver.ptl", obj, Xpox, 0, Zpox, false, 0, 0, 1); 
						local particleCreater = null;
						particleCreater = obj.getVar("gunner_fastdraw1").GetparticleCreaterMap("gunner_fastdraw1", "passiveobject/character/gunner/particle/fastdrawbulletdown.ptl", obj);
						particleCreater.Restart(0);
						particleCreater.SetPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(),Xpox),obj.getYPos(), Zpox);
						sq_AddParticleObject(obj, particleCreater);
					}
				}
					sq_SetMyShake(obj, 1, 50); 
					obj.getVar().set_vector(1, obj.getVar().get_vector(1)+1); 
			break;
		case 2: 
			local Xpox = 0; 
			local Zpox = 0; 
			
			switch(substate1)
			{
				case 1: 
				switch(substate2)
				{
					case ENUM_DIRECTION_UP: 
						Xpox = sq_GetDistancePos(0, obj.getDirection(), 1); 
						Zpox = 83; 
						obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_FASTDRAW_BODY_LEFTHANDTURN); 
					break;
					case ENUM_DIRECTION_DOWN: 
						Xpox = sq_GetDistancePos(0, obj.getDirection(), 4); 
						Zpox = 84; 
						obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_FASTDRAW_BODY_LEFTHANDTURN_LOW); 
					break;
				}
				sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/fastdraw/fastdraw_turnrightdust.ani", ENUM_DRAWLAYER_NORMAL, true); 
				break;
				case -1: 
					switch(substate2)
					{
					case ENUM_DIRECTION_UP: 
						Xpox = sq_GetDistancePos(0, obj.getDirection(), 37); 
						Zpox = 128; 
						obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_FASTDRAW_BODY_RIGHTHANDTRUN); 
					break;
					case ENUM_DIRECTION_DOWN: 
						Xpox = sq_GetDistancePos(0, obj.getDirection(), 41); 
						Zpox = 129; 
						obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_FASTDRAW_BODY_RIGHTHANDTRUN_LOW); 
					break;
					}
					sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/fastdraw/fastdraw_turnleftdust.ani", ENUM_DRAWLAYER_NORMAL, true); 
				break;
			}
			obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_GUNNER_SUPPRESSINGFINISHFIRE); 
			
			local Random = sq_getRandom(160, 330); 
			sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/fastdraw/fastdraw_dustground1_front.ani", Random, 25, 0);
			sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/fastdraw/fastdraw_dustground1_back.ani", Random, -25, 0);
			
			sq_CreateParticle("passiveobject/character/gunner/particle/fastdrawthrowrevolver.ptl", obj, Xpox, 0, Zpox, false, 0, 0, 1);
			obj.getVar().set_vector(0, obj.getVar().get_vector(0) + 1); 
			obj.getVar().set_vector(1, 0); 
			obj.getVar().setBool(2, false); 
		break;
		case 3: 
			switch(substate1)
			{
				case 1: 
					if(substate2 == ENUM_DIRECTION_UP) 
						obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_FASTDRAW_BODY_LEFTHANDEND); 
					else 
						obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_FASTDRAW_BODY_LEFTHANDEND_LOW); 
				break;
				case -1: 
					if(substate2 == ENUM_DIRECTION_UP) 
						obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_FASTDRAW_BODY_RIGHTHANDEND); 
					else 
						obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_FASTDRAW_BODY_RIGHTHANDEND_LOW); 
				break;
			}
		break;
	}
	obj.getVar().setInt(0, substate2); 
	obj.getVar().setInt(1, substate1); 
}

function onKeyFrameFlag_gunner_fastdraw(obj, flagIndex)
{
	if(!obj) return false;
	local substate = obj.getSkillSubState(); 
	switch(substate)
	{
		case 3: 
		if(flagIndex == 1)
		{
			local substate2 = obj.getVar().getInt(0); 
			local substate1 = obj.getVar().getInt(1); 
			local dstX = 0; 
			local dstZ = 0; 
			
			switch(substate1)
			{
				case 1: 
					switch(substate2)
					{
					case ENUM_DIRECTION_UP: 
						dstX = sq_GetDistancePos(0, obj.getDirection(), 40); 
						dstZ = 125; 
					break;
					case ENUM_DIRECTION_DOWN: 
						dstX = sq_GetDistancePos(0, obj.getDirection(), 38); 
						dstZ = 123; 
					break;
					}
				break;
				case -1: 
					switch(substate2)
					{
						case ENUM_DIRECTION_UP: 
							dstX = sq_GetDistancePos(0, obj.getDirection(), 74); 
							dstZ = 116; 
						break;
						case ENUM_DIRECTION_DOWN: 
							dstX = sq_GetDistancePos(0, obj.getDirection(), 73); 
							dstZ = 118; 
						break;
					}
				break;
			}
		sq_CreateParticle("passiveobject/character/gunner/particle/fastdrawthrowrevolver.ptl", obj, dstX, 0, dstZ, false, 0, 0, 1); 
		}
		break;
	}
	return true;
}

function onProcCon_gunner_fastdraw(obj)
{
	if(!obj) return;
	local substate = obj.getSkillSubState(); 
	
	switch(substate)
	{
		case 1:
		case 2:
			sq_SetKeyxEnable(obj, E_JUMP_COMMAND, true); 
			if(sq_IsEnterCommand(obj, E_JUMP_COMMAND)) 
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); 
			break;
	}
	if(substate == 1 && obj.getVar().getBool(2)==false)
	{
		sq_SetKeyxEnable(obj, E_ATTACK_COMMAND, true); 
		if(sq_IsEnterCommand(obj, E_ATTACK_COMMAND)) 
		{
			local skilllevel = sq_GetSkillLevel(obj, SKILL_GUNNER_FASTDRAW); 
			sq_BinaryStartWrite();
			sq_BinaryWriteWord(1);
			sq_BinaryWriteDword(sq_GetLevelData(obj, SKILL_GUNNER_FASTDRAW, 4, skilllevel)); 
			sq_SendChangeSkillEffectPacket(obj, SKILL_GUNNER_FASTDRAW); 
			obj.getVar().setBool(2, true); 
		}
	}
}



function onProc_gunner_fastdraw(obj)
{
	if(!obj) return;
	local substate = obj.getSkillSubState(); 
	
	switch(substate)
	{
		case 1:
		case 2:
			local Count = obj.getMyPassiveObjectCount(22001);
			for(local i=0;i<Count;++i)
			{
				local object = obj.getMyPassiveObject(22001, i);
				local objecttt = obj.getVar("fastdraw").is_obj_vector(object);
				if(object && objecttt)
				{
					setCurrentAnimationFromCutomIndex(object, 1);
					local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_GUNNER_FASTDRAW, SKILL_GUNNER_FASTDRAW, 3, 1.0)
					local attackInfo = sq_GetCurrentAttackInfo(object);
					sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
				}
			}
			break;
	}
}





function onEndCurrentAni_gunner_fastdraw(obj)
{
	if(!obj) return;
	local substate = obj.getSkillSubState(); 
	switch(substate)
	{
		case 0:
			local Random = sq_getRandom(160, 330); 
			sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/fastdraw/fastdraw_dustground1_front.ani", Random, 25, 0);
			sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/fastdraw/fastdraw_dustground1_back.ani", Random, -25, 0);
			if(obj.sq_IsMyControlObject())
			{
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(1); 
				obj.sq_IntVectPush(onGetLeftOrRight_gunner_fastdraw(obj, false)); 
				obj.sq_IntVectPush(onGetKeyDownDirection_gunner_fastdraw(obj)); 
				obj.sq_AddSetStatePacket(STATE_GUNNER_FASTDRAW, STATE_PRIORITY_USER, true); 
			}
		break;
		case 2:
			if(obj.sq_IsMyControlObject())
			{
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(1); 
				obj.sq_IntVectPush(onGetLeftOrRight_gunner_fastdraw(obj, obj.getVar().getInt(1))); 
				obj.sq_IntVectPush(onGetKeyDownDirection_gunner_fastdraw(obj)); 
				obj.sq_AddSetStatePacket(STATE_GUNNER_FASTDRAW, STATE_PRIORITY_USER, true); 
			}
		break;
		case 1:
			if(obj.sq_IsMyControlObject())
			{
				local skilllevel = sq_GetSkillLevel(obj, SKILL_GUNNER_FASTDRAW); 
				obj.sq_IntVectClear();
				local currentAtkCount = obj.getVar().get_vector(1); 
				local maxAtkCount = (obj.getVar().getBool(2) == false)
				? sq_GetLevelData(obj, SKILL_GUNNER_FASTDRAW, 1, skilllevel) 
				: sq_GetLevelData(obj, SKILL_GUNNER_FASTDRAW, 2, skilllevel); 
				
				if(currentAtkCount >= maxAtkCount)
				{
					local Nowcount = obj.getVar().get_vector(0); 
					local Setcount = sq_GetLevelData(obj, SKILL_GUNNER_FASTDRAW, 0, skilllevel); 
					
					if(Nowcount >= Setcount)
					{
						obj.sq_IntVectPush(3); 
						obj.sq_IntVectPush(obj.getVar().getInt(1)); 
						obj.sq_IntVectPush(obj.getVar().getInt(0)); 
					}
					else
					{
						obj.sq_IntVectPush(2); 
						obj.sq_IntVectPush(obj.getVar().getInt(1)); 
						obj.sq_IntVectPush(onGetKeyDownDirection_gunner_fastdraw(obj)); 
					}
				}
				else
				{
					obj.sq_IntVectPush(1); 
					obj.sq_IntVectPush(obj.getVar().getInt(1)); 
					obj.sq_IntVectPush(onGetKeyDownDirection_gunner_fastdraw(obj)); 
				}
				obj.sq_AddSetStatePacket(STATE_GUNNER_FASTDRAW, STATE_PRIORITY_USER, true); 
			}
		break;
		case 3:
			if(obj.sq_IsMyControlObject())
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); 
		break;
	}
}

function onChangeSkillEffect_gunner_fastdraw(obj, skillIndex, reciveData)
{
	if(!obj) return;
	local substate = obj.getSkillSubState();
	
	if(substate == 1 && skillIndex == SKILL_GUNNER_FASTDRAW)
	{
		local Open = reciveData.readWord(); 
		switch(Open)
		{
			case 1:
				local Speed = reciveData.readDword()/100.0; 
				obj.sq_SetStaticSpeedInfo(0, 0, 0, (1000 * Speed).tointeger(), 0.0, 0.0); 
			break;
		}
	}
}

function onEndState_gunner_fastdraw(obj, new_state)
{
	local state = obj.sq_GetState();
	local SubState0 = obj.getVar("substate").get_vector(0);
	local SubState1 = obj.getVar("substate").get_vector(1);
	local SubState2 = obj.getVar("substate").get_vector(2);
	if (new_state != STATE_GUNNER_FASTDRAW)
	{
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/gunner/fastdraw/ap_fastdraw.nut");
	}
}

function onGetKeyDownDirection_gunner_fastdraw(obj)
{
	if(!obj) return ENUM_DIRECTION_UP;
	local shoot = ENUM_DIRECTION_UP; 
	local Target = sq_FindTarget(obj, 0, 285, 40, 120);

	if(Target) 
		shoot = ENUM_DIRECTION_DOWN; 

	if((sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_LEFT)
	|| (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_RIGHT)
	|| sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL))
		shoot = ENUM_DIRECTION_UP; 
	
	else
	if(shoot != ENUM_DIRECTION_DOWN && sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL))
		shoot = ENUM_DIRECTION_DOWN; 
	return shoot;
}

function onGetLeftOrRight_gunner_fastdraw(obj, Bool)
{
	if(!obj || !Bool) return 1;
	return Bool/-1; 
}
