function checkExecutableSkill_Nastrond(obj)  
{
	if (!obj) return false;
	
	local isUse = obj.sq_IsUseSkill(SKILL_NASTROND);

	if (isUse)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_NASTROND, STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function checkCommandEnable_Nastrond(obj)
{
	return true;
}

function onSetState_Nastrond(obj, state, datas, isResetTimer)
{	
	local state = obj.getVar("state").get_vector(0);
	
	obj.sq_StopMove();

	if (state == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATNASTRONDSTART_BODY);
		
		createNastrondStartBack_00(obj);
		createNastrondStartFront_00(obj);
		createNastrondStartUnderCover_00(obj);
	}
	if (state == 1)
	{
		local objectManager = obj.getObjectManager();
		local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
		local yPos = objectManager.getFieldYPos(400, 0, ENUM_DRAWLAYER_NORMAL);
		local zPos = 800;
		obj.sq_SetCurrentPos(obj, xPos, yPos, zPos);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATNASTROND1ST_BODY);
		obj.sq_ZStop();
		
		createNastrond1Body(obj);
		createNastrond1StFront_00(obj);
		createNastrond1StUnderCover_00(obj);
		createNastrond1StBottom_00(obj);
	}
	if (state == 2)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATNASTROND2ST_BODY);
		obj.sq_ZStop();
		
		createNastrond2Body(obj);
		createNastrond2StBack_00(obj);
		createNastrond2StFront_00(obj);
		createNastrond2StUnderCover_00(obj);
	}
	if (state == 3)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATNASTROND3ST_BODY);
		obj.sq_ZStop();
		
		createNastrond3StBack_00(obj);
		createNastrond3StFront_00(obj);
		createNastrond3StUnderCover_00(obj);
	}
	if (state == 4)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATNASTROND4ST_BODY);
		obj.sq_ZStop();
		
		createNastrond4Body(obj);
		createNastrond4StFront_00(obj);
		createNastrond4StScreenCover_00(obj);
		createNastrond4StUnderCover_00(obj);
	}
	if (state == 5)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATNASTROND5ST_BODY);
		obj.sq_ZStop();
		
		createNastrond5Body(obj);
		createNastrond5StFront_00(obj);
		createNastrond5StScreenCover_00(obj);
		createNastrond5StUnderCover_00(obj);
	}
	if (state == 6)
	{
		obj.sq_SetCurrentPos(obj, obj.getXPos(), obj.getYPos(), 0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATNASTRONDEND_BODY);
		
		createNastrondEndFront_00(obj);
		createNastrondEndScreenCover_00(obj);
	}
}

function onTimeEvent_Nastrond(obj, timeEventIndex, timeEventCount)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 3)
	{
		if (timeEventIndex == 0)
		{
			createNastrond1MutiHit(obj);
		}
	}
	if(state == 5)
	{
		if (timeEventIndex == 0)
		{
			createNastrond2MutiHit(obj);
		}
	}
}

function onEndCurrentAni_Nastrond(obj)
{
	local state = obj.getVar("state").get_vector(0);
	
	if (state == 0)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_NASTROND, STATE_PRIORITY_USER, false);
	}
	if (state == 1)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_NASTROND, STATE_PRIORITY_USER, false);
	}
	if (state == 2)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(3);
		obj.sq_AddSetStatePacket(STATE_NASTROND, STATE_PRIORITY_USER, false);
	}
	if (state == 3)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(4);
		obj.sq_AddSetStatePacket(STATE_NASTROND, STATE_PRIORITY_USER, false);
	}
	if (state == 4)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(5);
		obj.sq_AddSetStatePacket(STATE_NASTROND, STATE_PRIORITY_USER, false);
	}
	if (state == 5)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(6);
		obj.sq_AddSetStatePacket(STATE_NASTROND, STATE_PRIORITY_USER, false);
	}
	if (state == 6)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onKeyFrameFlag_Nastrond(obj, flagIndex)
{
	local state = obj.getVar("state").get_vector(0);
	
	if (state == 1)
	{
		if (flagIndex == 0)
		{
			obj.sq_PlaySound("NASTROND_1_START");
		}
		if (flagIndex == 1)
		{
			sq_SetMyShake(obj,10,50);
			createNastrond1Hit(obj);
		}
		if (flagIndex == 2)
		{
			//`playSpearSound`	20	0	222	
		}
	}
	if (state == 2)
	{
		if (flagIndex == 0)
		{
			sq_SetMyShake(obj,15,150);
			createNastrond2Hit(obj);
		}
		if (flagIndex == 1)
		{
			sq_SetMyShake(obj,15,200);
			createNastrond3Hit(obj);
		}
		if (flagIndex == 2)
		{
			sq_SetMyShake(obj,15,200);
			createNastrond4Hit(obj);
		}
		if (flagIndex == 3)
		{
			sq_SetMyShake(obj,50,250);
			createNastrond5Hit(obj);
		}
	}
	if (state == 3)
	{
		if (flagIndex == 0)
		{
			sq_SetMyShake(obj,10,700);
			
			local attT = obj.sq_GetIntData(SKILL_NASTROND, 2);
			obj.setTimeEvent(0, 500 / attT, attT, true);
		}
	}
	if (state == 4)
	{
		if (flagIndex == 0)
		{
			//createUIAniWithIDPath(obj,44,"etc/ultimateskillani/atmage_glacialmaster_neo.ani");
		}
	}
	if (state == 5)
	{
		if (flagIndex == 0)
		{
			sq_SetMyShake(obj,6,600);
			
			local attT = obj.sq_GetIntData(SKILL_NASTROND, 4);
			obj.setTimeEvent(0, 300 / attT, attT, true);
		}
		if (flagIndex == 1)
		{
			sq_SetMyShake(obj,15,250);
			createNastrond6Hit(obj);
		}
		if (flagIndex == 2)
		{
			sq_flashScreen(obj,0,200,100,153, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		}
	}
	return true;
}

function createNastrond1Hit(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_NASTROND, STATE_NASTROND, 0, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atglacialmaster/animation/atnastrond/dummy.ani",
	"passiveobject/actionobject/new/atmage/atglacialmaster/attackinfo/atnastrondattack1.atk",true,atk,100,0,0,-800);		
}

function createNastrond2Hit(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_NASTROND, STATE_NASTROND, 1, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atglacialmaster/animation/atnastrond/dummy.ani",
	"passiveobject/actionobject/new/atmage/atglacialmaster/attackinfo/atnastrondattack2.atk",true,atk,100,0,0,-800);		
}

function createNastrond3Hit(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_NASTROND, STATE_NASTROND, 2, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atglacialmaster/animation/atnastrond/dummy.ani",
	"passiveobject/actionobject/new/atmage/atglacialmaster/attackinfo/atnastrondattack3.atk",true,atk,100,0,0,-800);		
}

function createNastrond4Hit(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_NASTROND, STATE_NASTROND, 3, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atglacialmaster/animation/atnastrond/dummy.ani",
	"passiveobject/actionobject/new/atmage/atglacialmaster/attackinfo/atnastrondattack4.atk",true,atk,100,0,0,-800);		
}

function createNastrond5Hit(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_NASTROND, STATE_NASTROND, 4, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atglacialmaster/animation/atnastrond/dummy.ani",
	"passiveobject/actionobject/new/atmage/atglacialmaster/attackinfo/atnastrondattack5.atk",true,atk,100,0,0,-800);		
}

function createNastrond1MutiHit(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_NASTROND, STATE_NASTROND, 5, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atglacialmaster/animation/atnastrond/dummy.ani",
	"passiveobject/actionobject/new/atmage/atglacialmaster/attackinfo/atnastrondmultiattack1.atk",true,atk,100,0,0,-800);		
}

function createNastrond2MutiHit(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_NASTROND, STATE_NASTROND, 6, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atglacialmaster/animation/atnastrond/dummy.ani",
	"passiveobject/actionobject/new/atmage/atglacialmaster/attackinfo/atnastrondmultiattack2.atk",true,atk,100,0,0,-800);		
}

function createNastrond6Hit(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_NASTROND, STATE_NASTROND, 7, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/atmage/atglacialmaster/animation/atnastrond/dummy.ani",
	"passiveobject/actionobject/new/atmage/atglacialmaster/attackinfo/atnastrondattack6.atk",true,atk,100,0,0,-800);		
}

function createNastrond1Body(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/nastrond1st.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond2Body(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/nastrond2st.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond4Body(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/nastrond4st.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond5Body(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/nastrond5st.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrondStartBack_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrondstartback_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrondStartFront_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrondstartfront_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrondStartUnderCover_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrondstartundercover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_CLOSEBACK);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond1StFront_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond1stfront_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond1StUnderCover_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond1stundercover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_CLOSEBACK);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond1StBottom_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond1stbottom_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond2StBack_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond2stback_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond2StFront_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond2stfront_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond2StUnderCover_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond2stundercover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_CLOSEBACK);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond3StBack_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond3stback_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond3StFront_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond3stfront_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond3StUnderCover_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond3stundercover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_CLOSEBACK);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond4StFront_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond4stfront_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond4StScreenCover_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond4stscreencover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond4StUnderCover_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond4stundercover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_CLOSEBACK);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond5StFront_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond5stfront_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond5StScreenCover_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond5stscreencover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrond5StUnderCover_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrond5stundercover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_CLOSEBACK);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrondEndFront_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrondendfront_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createNastrondEndScreenCover_00(obj)
{
	local ani = sq_CreateAnimation("","character/mage/effect/animation/atnastrond/atnastrondendscreencover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function create_Atmage_GlacialMaster_Neo(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/actionobject/new/atmage/atglacialmaster/animation/atnastrond/atmage_glacialmaster_neo.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local objectManager = obj.getObjectManager();
	local xPos = objectManager.getFieldXPos(0, ENUM_DRAWLAYER_COVER);
	local yPos = objectManager.getFieldYPos(0, 0, ENUM_DRAWLAYER_COVER);
	pooledObj.setCurrentPos(xPos ,yPos, 0);
	pooledObj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
	sq_AddObject(obj, pooledObj, 0, false);
}