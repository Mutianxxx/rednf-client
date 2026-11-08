function checkExecutableSkill_MicroUniverse(obj)
{
	if (!obj) return false;
	
	local isUse = obj.sq_IsUseSkill(SKILL_MICROUNIVERSE);
	
	if (isUse)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(0);
		obj.sq_IsEnterSkillLastKeyUnits(SKILL_MICROUNIVERSE);
		obj.sq_AddSetStatePacket(STATE_MICROUNIVERSE, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_MicroUniverse(obj)
{
	return true;
}

function onSetState_MicroUniverse(obj, state, datas, isResetTimer)
{	
	local state = obj.getVar("state").get_vector(0);
	
	obj.sq_StopMove();
	
	if(state == 0)
	{
		local objectManager = obj.getObjectManager();
		local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
		local yPos = objectManager.getFieldYPos(400, 0, ENUM_DRAWLAYER_NORMAL);
		obj.sq_SetCurrentPos(obj, xPos, yPos, 0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MICROUNIVERSESTART_BODY);
	}
	if(state == 1)
	{
		local zPos = 800;
		obj.sq_SetCurrentPos(obj, obj.getXPos(), obj.getYPos(), zPos);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MICROUNIVERSEA_BODY);
		obj.sq_ZStop();
		
		createMicroUniverse_Body(obj);
		createMicroUniverse_A_Bottom(obj);
	}
	if(state == 2)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MICROUNIVERSEB_BODY);
	}
}

function onTimeEvent_MicroUniverse(obj, timeEventIndex, timeEventCount)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 1)
	{
		if (timeEventIndex == 0)
		{
			createMicroUniverseMultiHit(obj);
		}
	}
}

function onEndCurrentAni_MicroUniverse(obj)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 0)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_MICROUNIVERSE, STATE_PRIORITY_USER, false);
	}
	if(state == 1)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_MICROUNIVERSE, STATE_PRIORITY_USER, false);
	}
	if(state == 2)
	{
		obj.sq_SetCurrentPos(obj, obj.getXPos(), obj.getYPos(), 0);
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onKeyFrameFlag_MicroUniverse(obj,flagIndex)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 0)
	{
		if (flagIndex == 0)	
		{
			sq_flashScreen(obj, 100, 220, 0, 255, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		}
	}
	if(state == 1)
	{
		if (flagIndex == 1)	
		{
			sq_SetMyShake(obj, 5, 160);
			createMicroUniverseFirstDummy(obj);
		}
		if (flagIndex == 2)	
		{
			sq_SetMyShake(obj, 1, 1320);
			sq_flashScreen(obj, 1320, 0, 40, 153, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_CLOSEBACK);
			
			createMicroUniverse_A_Cover41(obj);
			
			local attT = obj.sq_GetIntData(SKILL_MICROUNIVERSE, 0);
			obj.setTimeEvent(0, 1200 / attT, attT, true);	
		}
		if (flagIndex == 3)	
		{
			sq_SetMyShake(obj, 15, 160);
		}
		if (flagIndex == 4)	
		{
			sq_flashScreen(obj, 0, 40, 160, 204, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_CLOSEBACK);
		}
		if (flagIndex == 6)	
		{
			sq_flashScreen(obj, 0, 80, 0, 255, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_CLOSEBACK);
		}
		if (flagIndex == 7)	
		{
			createMicroUniverse_B_Cover00(obj);
			createMicroUniverse_B_CoverCut(obj);
		}
		if (flagIndex == 8)	
		{
			sq_SetMyShake(obj, 2, 160);
			sq_flashScreen(obj, 320, 0, 0, 153, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_CLOSEBACK);
		}
		if (flagIndex == 9)	
		{
			sq_SetMyShake(obj, 8, 120);
		}
		if (flagIndex == 10)	
		{
			sq_SetMyShake(obj, 15, 80);
			sq_flashScreen(obj, 0, 40, 160, 255, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_CLOSEBACK);
			
			createMicroUniverseExpDummy(obj);
		}
		if (flagIndex == 11)	
		{
			//createUIAniWithIDPath(obj,43,"etc/ultimateskillani/atmage_elementalbomber_neo.ani");
		}
		if (flagIndex == 12)	
		{
			sq_flashScreen(obj, 0, 800, 0, 255, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_NORMAL);
		}
		if (flagIndex == 13)	
		{
			sq_flashScreen(obj, 0, 200, 300, 229, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_NORMAL);
		}
	}
	return true;
}

function createMicroUniverseFirstDummy(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_MICROUNIVERSE, STATE_MICROUNIVERSE, 0, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atelementalbomber/animation/atmicrouniverse/atmicrouniversefirsthitdummy.ani",
	"passiveobject/actionobject/new/atmage/atelementalbomber/attackinfo/atmicrouniversefirsthitdummy.atk",true,atk,100,0,0,-800);		
}

function createMicroUniverseMultiHit(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_MICROUNIVERSE, STATE_MICROUNIVERSE, 1, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atelementalbomber/animation/atmicrouniverse/atmicrouniversemultihitdummy.ani",
	"passiveobject/actionobject/new/atmage/atelementalbomber/attackinfo/atmicrouniversemultihitdummy.atk",true,atk,100,0,0,-800);		
}

function createMicroUniverseExpDummy(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_MICROUNIVERSE, STATE_MICROUNIVERSE, 2, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atelementalbomber/animation/atmicrouniverse/atmicrouniverseexplosiondummy.ani",
	"passiveobject/actionobject/new/atmage/atelementalbomber/attackinfo/atmicrouniverseexplosiondummy.atk",true,atk,100,0,0,-800);		
}

function createMicroUniverse_Body(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atmicrouniverse/microuniversea_effbody.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createMicroUniverse_A_Bottom(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atmicrouniverse/microuniverseabottom_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createMicroUniverse_A_Cover41(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atmicrouniverse/microuniverseacover_41.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createMicroUniverse_B_Cover00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atmicrouniverse/microuniversebcover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createMicroUniverse_B_CoverCut(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atmicrouniverse/microuniversebcovercutscene_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createATMage_ElementalBomber_Neo(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/actionobject/new/atmage/atelementalbomber/animation/atmicrouniverse/atmage_elementalbomber_neo.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local objectManager = obj.getObjectManager();
	local xPos = objectManager.getFieldXPos(0, ENUM_DRAWLAYER_COVER);
	local yPos = objectManager.getFieldYPos(0, 0, ENUM_DRAWLAYER_COVER);
	pooledObj.setCurrentPos(xPos ,yPos, 0);
	pooledObj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
	sq_AddObject(obj, pooledObj, 0, false);
}
