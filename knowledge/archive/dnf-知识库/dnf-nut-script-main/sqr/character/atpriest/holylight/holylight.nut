
function checkExecutableSkill_HolyLight(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_HOLY_LIGHT);
	if (isUse)
	{
		local state = obj.sq_GetState();
		if(state == STATE_ARIA_OF_COURAGE || state == STATE_ARIA_OF_REGENERATION)
		{
			addHolyLightBuff(obj);
		}else{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_HOLY_LIGHT, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}
	}
	return false;
}

function checkCommandEnable_HolyLight(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND || state == STATE_DASH || state == STATE_ARIA_OF_COURAGE || state == STATE_ARIA_OF_REGENERATION){
		return true;
	}
	else{
		return false;
	}
}

function onSetState_HolyLight(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	if(substate == 0)
	{
		
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_HOLY_LIGHT_CAST_BODY);
		sq_StartDrawCastGauge(obj, sq_GetCastTime(obj, SKILL_HOLY_LIGHT, sq_GetSkillLevel(obj, SKILL_HOLY_LIGHT)), true);
		addHolyLightBuff(obj);
	}
	else if(substate == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_HOLY_LIGHT_START_BODY);
	}
}

function onEndCurrentAni_HolyLight(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_HOLY_LIGHT, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 1)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onEndState_HolyLight(obj, newState) {
	if(!obj)
		return false;
	if(newState != STATE_HOLY_LIGHT)
		sq_EndDrawCastGauge(obj);
}

function addHolyLightBuff(obj) {
	if(!obj) return;
	obj.sq_PlaySound("PW_HOLYLIGHT");
	local skill_level = sq_GetSkillLevel(obj, SKILL_HOLY_LIGHT);
	local time = sq_GetLevelData(obj, SKILL_HOLY_LIGHT, 0, skill_level);
	local value2 = sq_GetLevelData(obj, SKILL_HOLY_LIGHT, 2, skill_level);
	local value3 = sq_GetLevelData(obj, SKILL_HOLY_LIGHT, 3, skill_level);
	local power =  obj.sq_GetPowerWithPassive(SKILL_HOLY_LIGHT, STATE_HOLY_LIGHT, 1, -1,1.0);
	local size = obj.sq_GetIntData(SKILL_HOLY_LIGHT, 6);
	local objectManager = obj.getObjectManager();
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i += 1) {
		local tar = objectManager.getCollisionObject(i);
		if (tar && tar.isObjectType(OBJECTTYPE_CHARACTER) && !obj.isEnemy(tar)) {
			tar = sq_GetCNRDObjectToSQRCharacter(tar);
			local XPos = sq_Abs(tar.getXPos() - obj.getXPos());
			local YPos = sq_Abs(tar.getYPos() - obj.getYPos());
			if (XPos < (obj.sq_GetIntData(SKILL_HOLY_LIGHT, 0) - 200) && YPos < (obj.sq_GetIntData(SKILL_HOLY_LIGHT, 0) - 200)) {
				//CNSquirrelAppendage.sq_RemoveAppendage(tar, "character/atpriest/holylight/ap_holylight.nut");
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(tar, obj, SKILL_HOLY_LIGHT, false, "character/atpriest/holylight/ap_holylight.nut", false);
				appendage.sq_SetValidTime(time);
				appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_HOLY_LIGHT, skill_level);
				appendage.getVar("holylightbuff").clear_vector();
				appendage.getVar("holylightbuff").push_vector(value2);
				appendage.getVar("holylightbuff").push_vector(value3);
				appendage.getVar("holylightbuff").push_vector(power);
				appendage.getVar("holylightbuff").push_vector(size);
				CNSquirrelAppendage.sq_AppendAppendageID(appendage, tar, obj, APID_MAGIC_SHIELD, false);
				appendage.setBuffIconImage(44);
				
			}
		}
	}
}
