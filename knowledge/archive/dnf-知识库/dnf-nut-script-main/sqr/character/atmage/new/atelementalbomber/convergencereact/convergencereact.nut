function checkExecutableSkill_ConvergenceReact(obj)
{
	if (!obj) return false;
	
	local isUse = obj.sq_IsUseSkill(SKILL_CONVERGENCEREACT);
	
	if (isUse)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(0);
		obj.sq_IsEnterSkillLastKeyUnits(SKILL_CONVERGENCEREACT);
		obj.sq_AddSetStatePacket(STATE_CONVERGENCEREACT, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_ConvergenceReact(obj)
{
	return true;
}

function onSetState_ConvergenceReact(obj, state, datas, isResetTimer)
{	
	local state = obj.getVar("state").get_vector(0);
	
	obj.sq_StopMove();
	
	if(state == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_CONVERGENCEREACTREADY_BODY);
	}
	if(state == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_CONVERGENCEREACTATTACK1_BODY);
	}
	if(state == 2)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_CONVERGENCEREACTATTACK2_BODY);
	}
}

function onTimeEvent_ConvergenceReact(obj, timeEventIndex, timeEventCount)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 2)
	{
		if (timeEventIndex == 0)
		{
			createConvergenceReactDummy(obj);
		}
	}
}

function onEndCurrentAni_ConvergenceReact(obj)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 0)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_CONVERGENCEREACT, STATE_PRIORITY_USER, false);
	}
	if(state == 1)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_CONVERGENCEREACT, STATE_PRIORITY_USER, false);
	}
	if(state == 2)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onKeyFrameFlag_ConvergenceReact(obj,flagIndex)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 0)
	{
		if (flagIndex == 0)	
		{
			sq_flashScreen(obj, 480, 0, 0, 153, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		}
		if (flagIndex == 1)	
		{
			sq_SetMyShake(obj, 5, 240);
			sq_flashScreen(obj, 0, 40, 40, 153, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
			createCRAttackBack_04(obj, 0, 0, 0);
			createCRAttackBack1_04(obj, 0, 0, 0);
			createCRAttackFrontA_17(obj, 0, 0, 0);
			createCRAttackFrontA1_17(obj, 0, 0, 0);
		}
	}
	if(state == 1)
	{
		if (flagIndex == 0)	
		{
			sq_flashScreen(obj, 280, 0, 0, 102, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
			
			createCRAttackBack2_04(obj, 0, 0, 0);
			createCRAttackFrontA2_17(obj, 0, 0, 0);
			
		}
	}
	if(state == 2)
	{
		if (flagIndex == 0)	
		{
			obj.sq_PlaySound("CONVERGENCE_REACT_BURST");
			sq_SetMyShake(obj, 3, 1120);
			sq_flashScreen(obj, 0, 1000, 360, 153, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
			
			createCRAttackFrontB_01(obj, 0, 0, 0);
			createCRAttackFrontB_Dust(obj, 0, 0, 0);
			
			local attT = obj.sq_GetIntData(SKILL_CONVERGENCEREACT, 0);
			obj.setTimeEvent(0, 1000 / attT, attT, true);
		}
	}
	return true;
}

function createConvergenceReactDummy(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_CONVERGENCEREACT, STATE_CONVERGENCEREACT, 0, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atelementalbomber/animation/atconvergencereact/atconvergencereactdummy.ani",
	"passiveobject/actionobject/new/atmage/atelementalbomber/attackinfo/atconvergencereactdummy.atk",true,atk,100,0,0,0);		
}

function createCRAttackBack_04(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atconvergencereact/attackback_04.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createCRAttackBack1_04(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atconvergencereact/attackback1_04.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createCRAttackBack2_04(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atconvergencereact/attackback2_04.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createCRAttackFrontA_17(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atconvergencereact/attackfronta_17.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createCRAttackFrontA1_17(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atconvergencereact/attackfronta1_17.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createCRAttackFrontA2_17(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atconvergencereact/attackfronta2_17.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createCRAttackFrontB_01(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atconvergencereact/attackfrontb_01.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createCRAttackFrontB_Dust(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atconvergencereact/attackfrontb_dust.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}