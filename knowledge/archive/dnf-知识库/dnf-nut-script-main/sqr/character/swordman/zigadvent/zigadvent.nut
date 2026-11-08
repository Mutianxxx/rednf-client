

function checkCommandEnable_swordman_zigadvent(obj)
{
	return true;
}



function checkExecutableSkill_swordman_zigadvent(obj)
{
	if(!obj) return false;
	local skill = sq_GetSkill(obj, 241);
	local isUse = obj.sq_IsUseSkill(241);
	if(isUse && skill && skill.isSealFunction())
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(241, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	else if(isUse && skill && !skill.isSealFunction())
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(241, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}



function onSetState_swordman_zigadvent(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	/*if(obj.sq_IsMyControlObject())
	{
		create_cutin(obj, 3, "etc/ultimateskillani/2ndcutin/swordman/guiqi.ani");
	}*/

	switch(subState)
	{
		case 0:
			obj.sq_SetCurrentAnimation(159);
		break;
		case 1:
			obj.sq_SetCurrentAnimation(159);
			if(!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/swordman/zigadvent/ap_zig_character.nut"))
			{
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "character/swordman/zigadvent/ap_zig_character.nut", true);
			}
		break;
	}
}



function onEndCurrentAni_swordman_zigadvent(obj)
{
	if(!obj) return;

	local subState = obj.getSkillSubState();
	switch(subState)
	{
		case 0:
			if(obj.sq_IsMyControlObject())
			{
				obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
			}
		break;
		case 1:
			if(obj.sq_IsMyControlObject())
			{
				obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
			}
		break;
	}
}



function onKeyFrameFlag_swordman_zigadvent(obj, flagIndex)
{
	if(!obj) return false;

	local subState = obj.getSkillSubState();
	switch(subState)
	{
		case 0:
			switch(flagIndex)
			{
				case 1:
					local xPos = 270;
					if(obj.sq_IsMyControlObject())
					{
						local skill_level = sq_GetSkillLevel(obj, 241);
						obj.sq_StartWrite();
						obj.sq_WriteDword(241);
						obj.sq_WriteDword(1);
						obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(241, 241, 0, 1.0));
						obj.sq_WriteDword(sq_GetLevelData(obj, 241, 5, skill_level));
						obj.sq_WriteDword(sq_GetLevelData(obj, 241, 6, skill_level));
						obj.sq_WriteDword(sq_GetLevelData(obj, 241, 7, skill_level));
						obj.sq_WriteDword(sq_GetLevelData(obj, 241, 8, skill_level));
						obj.sq_WriteDword(sq_GetLevelData(obj, 241, 1, skill_level));
						obj.sq_SendCreatePassiveObjectPacket(24370, 0, xPos, 1, 0);
						obj.sq_StartWrite();
						obj.sq_WriteDword(241);
						obj.sq_WriteDword(2);
						obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(241, 241, 2, 1.0));
						obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(241, 241, 3, 1.0));
						obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(241, 241, 4, 1.0));
						obj.sq_WriteDword(sq_GetLevelData(obj, 241, 9, skill_level));
						obj.sq_WriteDword(sq_GetLevelData(obj, 241, 10, skill_level));
						obj.sq_WriteDword(sq_GetLevelData(obj, 241, 11, skill_level));
						obj.sq_WriteDword(sq_GetLevelData(obj, 241, 12, skill_level));
						obj.sq_SendCreatePassiveObjectPacket(24370, 0, xPos, -1, 0);
						sq_flashScreen(obj, 0, 80, 300, 51, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
					}
					local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/swordman/animation/zigadvent/zigstart/zigstartback_start_floor.ani");
					local pooledObj = sq_CreatePooledObject(ani, true);
					sq_SetCurrentDirection(pooledObj, obj.getDirection());
					pooledObj.setCurrentPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(), xPos), obj.getYPos(), obj.getZPos());
					pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
					sq_AddObject(obj, pooledObj, OBJECTTYPE_DRAWONLY, false);
				break;
			}
		break;
		case 1:
			switch(flagIndex)
			{
				case 1:
					if(obj.isMyControlObject())
					{
						local zigPos = sq_GetIntData(obj, 241, 0);
						obj.sq_StartWrite();
						obj.sq_WriteDword(24);
						obj.sq_SendCreatePassiveObjectPacket(24349, 0, zigPos, 0, 0);
					}
				break;
			}
		break;
	}
	return true;
}

