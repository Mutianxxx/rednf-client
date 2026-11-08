function checkExecutableSkill_SwordGhost7(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_7);
	local state = obj.sq_GetState();



	if (state == STATE_GEI_ZHAN)
	{
		local skill = sq_GetSkill(obj, SKILL_SWORD_GHOST_7);
		//print( "skill:" + skill);
		
		if(skill.isInCoolTime()) 
			{
				//print( "skill_off");
				return false;
			}
		else
			{
				obj.sq_SendCreatePassiveObjectPacket(24201, 0, 120, 1, 0);
				//print( "skill_on");
				return true;
			}
		
		
	}

	else if (isUse) 
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_7 , STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}

function checkCommandEnable_SwordGhost7(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	
	if (state == STATE_STAND)
		return true;
	return true;
}

function onSetState_SwordGhost7(obj, state, datas, isResetTimer)
{	

	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();//?????????
	local skill_level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_7);
	if(substate == 0)
	{
	obj.sq_SetCurrentAnimation(143);	//????ANI???
	obj.sq_SendCreatePassiveObjectPacket(24201, 0, 120, 1, 0);
	}
	else if(substate == 1)
	{

	}
	else if(substate == 2)
	{

	}

}
 
function onProc_SwordGhost7(obj)
{
	if(!obj)
		return false;
	local substate = obj.getSkillSubState();

	if(substate == 0)
	{
		if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT , ENUM_SUBKEY_TYPE_ALL))
			{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_7, STATE_PRIORITY_IGNORE_FORCE, true);
			}
			else if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT , ENUM_SUBKEY_TYPE_ALL))
			{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(2);
			obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_7, STATE_PRIORITY_IGNORE_FORCE, true);
			}
			else if(sq_IsKeyDown(OPTION_HOTKEY_JUMP , ENUM_SUBKEY_TYPE_ALL))
			{
				obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
			}
		
	}
}


function onEndCurrentAni_SwordGhost7(obj)
{
		obj.sq_SendCreatePassiveObjectPacket(260152, 0, 0, 1, 0);
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}


