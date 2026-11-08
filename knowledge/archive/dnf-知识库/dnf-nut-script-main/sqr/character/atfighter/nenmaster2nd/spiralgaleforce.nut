

function checkExecutableSkill_spiralgaleforce(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SPIRALGALEFORCE);
	
	if(isUse)
	{
		local apPath = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
		local ballAp = "character/atfighter/nenmaster2nd/ap_spiralnen.nut";
		if(CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath))
		{
			destroyObjectByVar(obj, "SpiralGaleForcePool");
			CNSquirrelAppendage.sq_RemoveAppendage(obj, apPath);
			if(CNSquirrelAppendage.sq_IsAppendAppendage(obj, ballAp))
				CNSquirrelAppendage.sq_RemoveAppendage(obj, ballAp);
			return;
		}
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SPIRALGALEFORCE, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_spiralgaleforce(obj)
{
	if (!obj) return false;
	local OnForce = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut");
	
	if(OnForce)
	{
		return true;
	}
	else
	{
		if(obj.getVar("SpiralInhaleEnergy").size_vector() > 0 && obj.getVar("SpiralInhaleEnergy").get_vector(0) >= 500)
		{
			return true;
		}
	}
	
	return false;
}

function onSetState_spiralgaleforce(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);

	switch(substate)
	{
	case 0:
		obj.sq_StopMove();
		obj.sq_PlaySound("MF_SPIRAL_GALEFORCE");
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPIRALGALEFORCE_CAST1_BODY);

		break;
	case 1:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPIRALGALEFORCE_CAST2_BODY);
		break;
	}
	obj.sq_SetStaticSpeedInfo(4, 4,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onEndCurrentAni_spiralgaleforce(obj)
{
	if(!obj) return;
	local substate = obj.getSkillSubState();
	switch(substate)
	{
	case 0:
		obj.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, false);
		break;
	case 1:
		obj.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, false);
		break;
	}
}

function onKeyFrameFlag_spiralgaleforce(obj, flagIndex)
{
if (!obj) return false;
switch(flagIndex)
{
case 1:
if(obj.isMyControlObject())
sq_SetMyShake(obj,1,150);

local CQNGZIGCgYHMeZVH = "passiveobject/chang_qing_skill/atfighter/animation/atspiralgaleforce/cast2_effect_01.ani";
createAnimationPooledEx(obj, CQNGZIGCgYHMeZVH,1, true,obj.getXPos(), obj.getYPos(), obj.getZPos()+50 ,false);

local append = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, append, false);
if (appendage != null)
{
appendage.sq_SetValidTime(0);
appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_SPIRALGALEFORCE, sq_GetSkillLevel(obj, SKILL_SPIRALGALEFORCE));
appendage.setEnableIsBuff(true);
CNSquirrelAppendage.sq_Append(appendage, obj, obj, true);
}

local CQqdeGQZxZ2jg7bhO = "character/fighter/effect/animation/atspiralgaleforce/buff_01.ani";
local CQKMX3hsJTi68p = createAnimationPooledEx(obj, CQqdeGQZxZ2jg7bhO, 2,true,obj.getXPos(), obj.getYPos()-1, obj.getZPos(),false);

destroyObjectByVar(obj, "SpiralGaleForcePool");
obj.getVar("SpiralGaleForcePool").clear_obj_vector();
obj.getVar("SpiralGaleForcePool").push_obj_vector(CQKMX3hsJTi68p);

break;
}
return true;
}

function createAnimationPooledEx(obj, aniPath,layer, moveWithParent, x, y, z ,aniEx)
{
local ani = sq_CreateAnimation("",aniPath);
if(aniEx != false)
{
	ani.setImageRateFromOriginal(aniEx, aniEx);
	ani.setAutoLayerWorkAnimationAddSizeRate(aniEx);
}

local pooledObject = sq_CreatePooledObject(ani,true);

pooledObject.setCurrentPos(x,y,z);
if(moveWithParent)
sq_moveWithParent(obj, pooledObject);

sq_SetEnumDrawLayer(pooledObject, layer);
sq_SetCurrentDirection(pooledObject, obj.getDirection());

sq_AddObject(obj, pooledObject, OBJECTTYPE_DRAWONLY, false);

return pooledObject;
}


