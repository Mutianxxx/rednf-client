function checkExecutableSkill_AdesPhantom(obj)
{
	if (!obj) return false;
	
	local isUse = obj.sq_IsUseSkill(SKILL_ADESPHANTOM);
	
	if (isUse)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(0);
		obj.sq_IsEnterSkillLastKeyUnits(SKILL_ADESPHANTOM);
		obj.sq_AddSetStatePacket(STATE_ADESPHANTOM, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_AdesPhantom(obj)
{
	return true;
}

function onSetState_AdesPhantom(obj, state, datas, isResetTimer)
{	
	local state = obj.getVar("state").get_vector(0);
	
	obj.sq_StopMove();
	
	if(state == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ADESPHANTOMSTART_BODY);
	}
	if(state == 1)
	{
		local objectManager = obj.getObjectManager();
		local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
		local yPos = objectManager.getFieldYPos(400, 0, ENUM_DRAWLAYER_NORMAL);
		local zPos = 800
		obj.sq_SetCurrentPos(obj, xPos, yPos, zPos);
		
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ADESPHANTOM1ST_BODY);
		obj.sq_ZStop();
		
		createAdesPhantom1StBody(obj);
		createAdesPhantom1St_Bottom(obj);
		createAdesPhantom1St_Front(obj);
		createAdesPhantom1St_UnderCover(obj);
		createAdesPhantom1St_UnderCover02A(obj);
	}
	if(state == 2)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ADESPHANTOM2ST_BODY);
		obj.sq_ZStop();
		
		createAdesPhantom2StBody(obj);
		createAdesPhantom2St_Front(obj);
		createAdesPhantom2St_SCover(obj);
		createAdesPhantom2St_TCover(obj);
	}
	if(state == 3)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ADESPHANTOM3ST_BODY);
		obj.sq_ZStop();
		
		createAdesPhantom3StBody(obj);
		createAdesPhantom3St_Back(obj);
		createAdesPhantom3St_Front(obj);
		createAdesPhantom3St_SCover(obj);
		createAdesPhantom3St_TCover(obj);
	}
	if(state == 4)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ADESPHANTOM4ST_BODY);
		obj.sq_ZStop();
		
		createAdesPhantom4StBody(obj);
		createAdesPhantom4St_Back(obj);
		createAdesPhantom4St_Front(obj);
		createAdesPhantom4St_SCover(obj);
		createAdesPhantom4St_UCover(obj);
	}
	if(state == 5)
	{
		local objectManager = obj.getObjectManager();
		local xPos = objectManager.getFieldXPos(400, ENUM_DRAWLAYER_NORMAL);
		local yPos = objectManager.getFieldYPos(400, 0, ENUM_DRAWLAYER_NORMAL);
		obj.sq_SetCurrentPos(obj, xPos, yPos, 0);
		
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ADESPHANTOMEND_BODY);
		
		createAdesPhantomEnd_Back(obj);
		createAdesPhantomEnd_Front(obj);
		createAdesPhantomEnd_UCover(obj);
	}
}

function onTimeEvent_AdesPhantom(obj, timeEventIndex, timeEventCount)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 2)
	{
		if (timeEventIndex == 0)
		{
			createAdesPhantom_MultiHit(obj);	//`create multi hit dummy`	3	0	10	
		}
	}
}

function onEndCurrentAni_AdesPhantom(obj)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 0)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_ADESPHANTOM, STATE_PRIORITY_USER, true);
	}
	if(state == 1)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_ADESPHANTOM, STATE_PRIORITY_USER, true);
	}
	if(state == 2)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(3);
		obj.sq_AddSetStatePacket(STATE_ADESPHANTOM, STATE_PRIORITY_USER, true);
	}
	if(state == 3)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(4);
		obj.sq_AddSetStatePacket(STATE_ADESPHANTOM, STATE_PRIORITY_USER, true);
	}
	if(state == 4)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(5);
		obj.sq_AddSetStatePacket(STATE_ADESPHANTOM, STATE_PRIORITY_USER, true);
	}
	if(state == 5)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onKeyFrameFlag_AdesPhantom(obj,flagIndex)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 1)
	{
		if (flagIndex == 0)
		{
			//[PLAY SOUND OPTION]
			//`ADESPHANTOM_HEARTBEAT`
			//`PLAY_MY_GLOBAL`
		}
		else if (flagIndex == 1)
		{
			createThief_Rogue_Neo(obj);	//?’ç•«
		}
	}
	if(state == 2)
	{
		if (flagIndex == 0)
		{
			local attT = obj.sq_GetIntData(SKILL_ADESPHANTOM, 2);
			obj.setTimeEvent(0, 260 / attT, attT, true);
			sq_SetMyShake(obj,15,150);
		}
	}
	if(state == 3)
	{
		if (flagIndex == 0)
		{
			sq_SetMyShake(obj,1,300);
		}
	}
	if(state == 4)
	{
		if (flagIndex == 0)
		{
			obj.sq_PlaySound("ADESPHANTOM_ADD");
		}
		else if (flagIndex == 1)
		{
			sq_SetMyShake(obj,30,200);
			sq_flashScreen(obj,20,30,20,76, sq_RGB(0,191,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		}
		else if (flagIndex == 2)
		{
			sq_SetMyShake(obj,25,600);
		}
		else if (flagIndex == 3)
		{
			createAdesPhantom_EndHit(obj);	//`create hit end dummy`30	0	32	
		}
	}
	if(state == 5)
	{
		if (flagIndex == 0)
		{
			sq_flashScreen(obj,0,50,1000,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		}
	}
	return true;
}

function createAdesPhantom_MultiHit(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_ADESPHANTOM, STATE_ADESPHANTOM, 0, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/thief/rogue/animation/adesphantom/attackdummy.ani",
	"passiveobject/actionobject/new/thief/rogue/attackinfo/adesphantommultihitdummy.atk",true,atk,100,0,0,-800);		
}

function createAdesPhantom_EndHit(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_ADESPHANTOM, STATE_ADESPHANTOM, 1, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/thief/rogue/animation/adesphantom/attackdummy.ani",
	"passiveobject/actionobject/new/thief/rogue/attackinfo/adesphantomhitenddummy.atk",true,atk,100,0,0,-800);		
}

function createAdesPhantom1StBody(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/adesphantom1st_body.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom2StBody(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/adesphantom2st_body.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom3StBody(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/adesphantom3st_body.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom4StBody(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/adesphantom4st_body.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom1St_Bottom(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/1st/adesphantom1stbottom_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom1St_Front(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/1st/adesphantom1stfront_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom1St_UnderCover(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/1st/adesphantom1stundercover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom1St_UnderCover02A(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/1st/adesphantom1stundercover_02a.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local objectManager = obj.getObjectManager();
	local xPos = objectManager.getFieldXPos(400, ENUM_DRAWLAYER_COVER);
	local yPos = objectManager.getFieldYPos(1200, 0, ENUM_DRAWLAYER_COVER);
	pooledObj.setCurrentPos(xPos ,yPos, 0);
	pooledObj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
	sq_AddObject(obj, pooledObj, 0, false);
}

function createAdesPhantom2St_Front(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/2st/adesphantom2stfront_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom2St_SCover(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/2st/adesphantom2stscreencover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom2St_TCover(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/2st/adesphantom2stundercover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom3St_Back(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/3st/adesphantom3stback_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom3St_Front(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/3st/adesphantom3stfront_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom3St_SCover(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/3st/adesphantom3stscreencover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom3St_TCover(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/3st/adesphantom3stundercover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom4St_Back(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/4st/adesphantom4stback_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom4St_Front(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/4st/adesphantom4stfront_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom4St_SCover(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/4st/adesphantom4stscreencover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantom4St_UCover(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/4st/adesphantom4stundercover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantomEnd_Back(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/end/adesphantomendback_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantomEnd_Front(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/end/adesphantomendfront_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createAdesPhantomEnd_UCover(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/adesphantom/end/adesphantomendundercover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(), 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}

function createThief_Rogue_Neo(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/actionobject/new/thief/rogue/animation/adesphantom/thief_rogue_neo.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	
	local objectManager = obj.getObjectManager();
	
	if (sq_GetDirection(obj) == ENUM_DIRECTION_LEFT)
	{
		local xPos = objectManager.getFieldXPos(1050, ENUM_DRAWLAYER_COVER);
		local yPos = objectManager.getFieldYPos(0, 0, ENUM_DRAWLAYER_COVER);
		pooledObj.setCurrentPos(xPos ,yPos ,0);
	}
	if (sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT)
	{
		local xPos = objectManager.getFieldXPos(-190, ENUM_DRAWLAYER_COVER);
		local yPos = objectManager.getFieldYPos(0, 0, ENUM_DRAWLAYER_COVER);
		pooledObj.setCurrentPos(xPos ,yPos ,0);
	}
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}


