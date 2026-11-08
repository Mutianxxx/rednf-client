function checkExecutableSkill_CoconOfUndead(obj)
{
	if (!obj) return false;
	
	local necromancerObjCount = obj.getMyPassiveObjectCount(24336);
	
	for (local i = 0; i < necromancerObjCount; ++i) 
	{ 
		local necromancerObj = obj.getMyPassiveObject(24336, i);
		
		if (necromancerObj && necromancerObj.getVar("id").get_vector(0) == 1 || necromancerObj.getVar("id").get_vector(0) == 3 || necromancerObj.getVar("id").get_vector(0) == 5)
		{
			necromancerObj.setTimeEvent(1, 1, 0, false);
			return true;
		}
	}
	
	local isUse = obj.sq_IsUseSkill(SKILL_COCONOFUNDEAD);
	
	if (isUse)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(0);
		obj.sq_IsEnterSkillLastKeyUnits(SKILL_COCONOFUNDEAD);
		obj.sq_AddSetStatePacket(STATE_COCONOFUNDEAD, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_CoconOfUndead(obj)
{
	return true;
}

function onSetState_CoconOfUndead(obj, state, datas, isResetTimer)
{	
	local state = obj.getVar("state").get_vector(0);
	
	obj.sq_StopMove();
	
	if(state == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_COCOONOFUNDEADSTART_BODY);
	}
}

function onTimeEvent_CoconOfUndead(obj, timeEventIndex, timeEventCount)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 0)
	{
		if (timeEventIndex == 0)
		{
			createCoconOfUndead_MultiHit(obj);
		}
	}
}

function onEndCurrentAni_CoconOfUndead(obj)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 0)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onKeyFrameFlag_CoconOfUndead(obj,flagIndex)
{
	local state = obj.getVar("state").get_vector(0);
	
	local id = sq_GetObjectId(obj);
	
	if(state == 0)
	{
		if (flagIndex == 0)
		{
			createCoconOfUndead_StartBottom(obj, 0, 0, 0);
		}
		if (flagIndex == 1)
		{
			createCoconOfUndead_CoCoonaFront(obj, 250, 0, 0);
			createCoconOfUndead_CoCoonaBack(obj, 250, 0, 0);
			createCoconOfUndead_CoCoonaBaottom(obj, 250, 0, 0);
			
			local attT = 4;
			obj.setTimeEvent(0, 160 / attT, attT, true);
		}
		if (flagIndex == 2)
		{
			obj.sq_StartWrite();
			obj.sq_WriteDword(0);
			obj.sq_WriteDword(id);
			obj.sq_SendCreatePassiveObjectPacket(24336, 0, 250, 0, 0);
			
			createCoconOfUndead_RangeStartBottom(obj, 250, 0, 0);
			createCoconOfUndead_CoCoonStartBottom(obj, 250, 0, 0);
		}
	}
	return true;
}

function createCoconOfUndead_MultiHit(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_COCONOFUNDEAD, STATE_COCONOFUNDEAD, 0, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/cocoonattractionattack.ani",
	"passiveobject/actionobject/new/thief/necromancer/attackinfo/cocoonofundeadattractionattack.atk",true,atk,100,0,0,0);		
}

function createCoconOfUndead_StartBottom(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/thief/effect/animation/cocoonofundead/cocoonofundeadstartbottom_00.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createCoconOfUndead_RangeStartBottom(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/rangestartbottom_00.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createCoconOfUndead_CoCoonStartBottom(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/cocoonstartbottom_00.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createCoconOfUndead_CoCoonaFront(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/cocoonafront.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createCoconOfUndead_CoCoonaBack(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/cocoonaback.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createCoconOfUndead_CoCoonaBaottom(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/cocoonabottom.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createCoconOfUndead_RangeLoopBottom(obj, disX, disY, disZ)
{
	if (!obj.isMyControlObject())
		return false;

	local ani = sq_CreateAnimation("", "passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/rangeloopbottom_00.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
	obj.getVar("COU_End").push_obj_vector(pooledObj);
}

function createCoconOfUndead_CoCoonLoopBottom(obj, disX, disY, disZ)
{
	if (!obj.isMyControlObject())
		return false;

	local ani = sq_CreateAnimation("", "passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/cocoonloopbottom_00.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
	obj.getVar("COU_End").push_obj_vector(pooledObj);
}

function setVliadEffectCoconOfUndeadPassiveobject(obj)
{
	local var = obj.getVar("COU_End");
	
	local objectsSize = var.get_obj_vector_size();

	for(local i=0;i<objectsSize;++i)
	{
		local effectObj = var.get_obj_vector(i);
		
		if (effectObj)
		{
			effectObj.setValid(false);
		}
	}
}
