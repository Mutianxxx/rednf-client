function checkExecutableSkill_cure(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_CURE);
	if (isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_CURE, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_cure(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND || state == STATE_DASH){
		return true;
	}
	else{
		return false;
	}
}

function onSetState_Cure(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
		SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	if(substate == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_CURE_CAST_BODY);
		sq_StartDrawCastGauge(obj, sq_GetCastTime(obj, SKILL_CURE, sq_GetSkillLevel(obj, SKILL_CURE)), true);
	}
	if(substate == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_CURE_START_BODY);
		addCureBuff(obj);
	}
}

function onKeyFrameFlag_Cure(obj,flagIndex)
{
	if(!obj)
		return false;
	if (flagIndex == 0)
	{
		obj.sq_PlaySound("R_PW_CURE");
	}
	return true;
}

function onEndCurrentAni_Cure(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_CURE, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 1)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onEndState_Cure(obj, newState) {
	if(!obj)
		return false;
	if(newState != STATE_CURE)
		sq_EndDrawCastGauge(obj);
}

function addCureBuff(obj)
{
	local objectManager = obj.getObjectManager();
	local skill_level = sq_GetSkillLevel(obj, SKILL_CURE);
	local ani = sq_AddDrawOnlyAniFromParent(obj, "character/priest/effect/animation/atcure/priestcure.ani", 0, 1, 0);
	sq_moveWithParent(obj, ani);
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if(!object || !object.isObjectType(OBJECTTYPE_ACTIVE)){
			continue;
		}
		object = sq_GetCNRDObjectToActiveObject(object);
		if (object && !obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_CHARACTER) && 
			isDistanceOfTarget(obj,object,sq_GetIntData(obj, SKILL_CURE, 0)))
		{
			for (local activestatus = 0; activestatus < 18; activestatus+=1)
			{
				if(sq_IsValidActiveStatus(object, activestatus))
				{
					sq_ReleaseActiveStatus(object, activestatus);
				}
			}
		}
	}
}