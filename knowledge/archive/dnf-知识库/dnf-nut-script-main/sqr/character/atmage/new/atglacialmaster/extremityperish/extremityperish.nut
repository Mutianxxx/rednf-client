function checkExecutableSkill_ExtremityPerish(obj)  
{
	if (!obj) return false;
	
	local isUse = obj.sq_IsUseSkill(SKILL_EXTREMITYPERISH);

	if (isUse)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_EXTREMITYPERISH, STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function checkCommandEnable_ExtremityPerish(obj)
{
	return true;
}

function onSetState_ExtremityPerish(obj, state, datas, isResetTimer)
{	
	local state = obj.getVar("state").get_vector(0);
	
	obj.sq_StopMove();
	
	if (state == 0)
	{
		local objectManager = obj.getObjectManager();
		local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
		local yPos = objectManager.getFieldYPos(400, 0, ENUM_DRAWLAYER_NORMAL);
		obj.sq_SetCurrentPos(obj, xPos, yPos, 0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_EXTREMITYPERISH_PHASE1BODY);
		
		sq_flashScreen(obj,0,6000,0,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
	}
	if (state == 1)
	{
		local zPos = 800;
		obj.sq_SetCurrentPos(obj, obj.getXPos(), obj.getYPos(), zPos);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_EXTREMITYPERISHPARTYFRONT_80);
		obj.sq_ZStop();
		
		createExtremityPerish_PartyBody(obj);
		createExtremityPerish_PartyBottom38(obj);
		createExtremityPerish_PartyCover56(obj);
		createExtremityPerish_PartyCover112(obj);
		createExtremityPerish_PartyCover155(obj);
		createExtremityPerish_PartyFront_56_01(obj);
		createExtremityPerish_PartyFront_83(obj);
		createExtremityPerish_Phase2_Bottom38(obj);
		createExtremityPerish_Phase2_BackGround00(obj);
	}
	if (state == 2)
	{
		obj.sq_SetCurrentPos(obj, obj.getXPos(), obj.getYPos(), 0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_EXTREMITYPERISH_PHASE3BODY);
		
		createExtremityPerish_Phase3_End71(obj);
	}
}

function onTimeEvent_ExtremityPerish(obj, timeEventIndex, timeEventCount)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 1)
	{
		if (timeEventIndex == 0)
		{
			createExtremityPerish_Dummy2(obj);
		}
	}
}

function onEndCurrentAni_ExtremityPerish(obj)
{
	local state = obj.getVar("state").get_vector(0);
	
	if (state == 0)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_EXTREMITYPERISH, STATE_PRIORITY_USER, false);
	}
	if (state == 1)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_EXTREMITYPERISH, STATE_PRIORITY_USER, false);
	}
	if (state == 2)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onKeyFrameFlag_ExtremityPerish(obj, flagIndex)
{
	local state = obj.getVar("state").get_vector(0);
	
	if (state == 0)
	{
		if (flagIndex == 0)
		{
			obj.sq_PlaySound("EXTREMITYPERISH_CAST");
			sq_flashScreen(obj,0,80,0,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		}
		if (flagIndex == 1)
		{
			createExtremityPerish_Dummy1(obj);
			createExtremityPerish_Phase1_Back70(obj);
		}
		if (flagIndex == 2)
		{
			sq_SetMyShake(obj,10,200);
		}
		if (flagIndex == 3)
		{
			createExtremityPerish_Phase1_Bottom66(obj);
		}
	}
	
	if (state == 1)
	{
		if (flagIndex == 0)
		{
			local attT = obj.sq_GetIntData(SKILL_EXTREMITYPERISH, 2);
			obj.setTimeEvent(0, 2000 / attT, attT, true);
		}
		if (flagIndex == 1)
		{
			createExtremityPerish_PartyBack47(obj);
			createExtremityPerish_PartyBack50(obj);
			createExtremityPerish_Phase2_Back53(obj);
		}
		if (flagIndex == 2)
		{
			sq_SetMyShake(obj,2,180);
		}
		if (flagIndex == 3)
		{
			sq_SetMyShake(obj,2,300);
		}
		if (flagIndex == 4)
		{
			sq_SetMyShake(obj,4,500);
			createExtremityPerish_Dummy3(obj);
		}
	}
	return true;
}

function createExtremityPerish_Dummy1(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_EXTREMITYPERISH, STATE_EXTREMITYPERISH, 0, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atglacialmaster/animation/atextremityperish/attackdummy.ani",
	"passiveobject/actionobject/new/atmage/atglacialmaster/attackinfo/atextremityperish1.atk",true,atk,100,0,0,0);		
}

function createExtremityPerish_Dummy2(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_EXTREMITYPERISH, STATE_EXTREMITYPERISH, 1, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atglacialmaster/animation/atextremityperish/attackdummy.ani",
	"passiveobject/actionobject/new/atmage/atglacialmaster/attackinfo/atextremityperish2.atk",true,atk,100,0,0,-800);		
}

function createExtremityPerish_Dummy3(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_EXTREMITYPERISH, STATE_EXTREMITYPERISH, 2, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atglacialmaster/animation/atextremityperish/attackdummy.ani",
	"passiveobject/actionobject/new/atmage/atglacialmaster/attackinfo/atextremityperish3.atk",true,atk,100,0,0,-800);		
}

function createExtremityPerish_Phase1_Back70(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/phase1/extremityperishstartback_70.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createExtremityPerish_Phase1_Bottom66(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/phase1/extremityperishstartbottom_66.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createExtremityPerish_Phase2_Back53(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/phase2/extremityperishback_53.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createExtremityPerish_Phase2_BackGround00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/phase2/extremityperishbackgrounds_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_CLOSEBACK);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createExtremityPerish_Phase2_Bottom38(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/phase2/extremityperishbottom_38.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createExtremityPerish_PartyBody(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/party/partyfront_body.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createExtremityPerish_PartyBack47(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/party/extremityperishpartyback_47.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createExtremityPerish_PartyBack50(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/party/extremityperishpartyback_50.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createExtremityPerish_PartyBottom38(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/party/extremityperishpartybottom_38.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createExtremityPerish_PartyCover56(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/party/extremityperishpartycover_56.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createExtremityPerish_PartyCover112(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/party/extremityperishpartycover_112.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createExtremityPerish_PartyCover155(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/party/extremityperishpartycover_155.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createExtremityPerish_PartyFront_56_01(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/party/extremityperishpartyfront_56_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createExtremityPerish_PartyFront_83(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/party/extremityperishpartyfront_83.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createExtremityPerish_Phase3_End71(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atextremityperish/phase3/extremityperishend_71.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}
