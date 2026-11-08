function checkExecutableSkill_HorrorOfMoros(obj)
{
	if (!obj) return false;
	
	local isUse = obj.sq_IsUseSkill(SKILL_HORROROFMOROS);
	
	if (isUse)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(0);
		obj.sq_IsEnterSkillLastKeyUnits(SKILL_HORROROFMOROS);
		obj.sq_AddSetStatePacket(STATE_HORROROFMOROS, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_HorrorOfMoros(obj)
{
	return true;
}

function onSetState_HorrorOfMoros(obj, state, datas, isResetTimer)
{	
	local state = obj.getVar("state").get_vector(0);
	
	obj.sq_StopMove();
	
	if(state == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MOROSATTACKBODY_BODY);
		
		local objectManager = obj.getObjectManager();
		local zPos = 800
		obj.sq_SetCurrentPos(obj, obj.getXPos(), obj.getYPos(), zPos);
		
		obj.sq_ZStop();
		
		createHorrorOfMoros_Body(obj);
		createHorrorOfMoros_BackGround(obj);
		createHorrorOfMoros_Cover(obj);
		createHorrorOfMoros_CoverCenter(obj);
		createHorrorOfMoros_CoverFront(obj);
		createHorrorOfMoros_Bottom(obj)
	}
}

function onEndCurrentAni_HorrorOfMoros(obj)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 0)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		obj.sq_SetCurrentPos(obj, obj.getXPos(), obj.getYPos(), 0);
	}
}

function onKeyFrameFlag_HorrorOfMoros(obj,flagIndex)
{
	local state = obj.getVar("state").get_vector(0);
	
	if(state == 0)
	{
		if (flagIndex == 0)
		{
			//[PLAY SOUND]	`HORROR_MOROS_START`
			//`LockPartyPlayerCutScene`	1	0	0	
		}
		if (flagIndex == 1)
		{
			obj.sq_PlaySound("RG_TF_HORROR_MOROS_01");
		}
		if (flagIndex == 2)
		{
			sq_SetMyShake(obj,3,360);
		}
		//if (flagIndex == 3)
		//{
			//[CAMERA]	`Moros`
		//}
		if (flagIndex == 4)
		{
			sq_SetMyShake(obj,10,240);
		}
		//if (flagIndex == 5)
		//{
			//[PLAY SOUND]	`HORROR_MOROS_APPEAR`
		//}
		if (flagIndex == 6)
		{
			sq_SetMyShake(obj,2,60);
		}
		if (flagIndex == 7)
		{
			sq_SetMyShake(obj,20,60);
		}
		if (flagIndex == 8)
		{
			sq_SetMyShake(obj,2,60);
			obj.sq_PlaySound("RG_TF_HORROR_MOROS_04");
		}
		if (flagIndex == 9)
		{
			sq_SetMyShake(obj,2,60);
			//立繪?�畫
		}
		if (flagIndex == 10)
		{
			sq_SetMyShake(obj,30,720);
		}
		if (flagIndex == 11)
		{
			createHorrorOfMorosHit(obj);	//`create Attack`	0	0	0	
			//[PLAY SOUND]	`HORROR_MOROS_FINISH`
		}
		if (flagIndex == 2)
		{
			//`LockPartyPlayerCutScene`	0	0	0	
			obj.sq_PlaySound("RG_TF_HORROR_MOROS_05");
		}
	}
	return true;
}

function createHorrorOfMorosHit(obj)
{
	local atk = obj.sq_GetBonusRateWithPassive(SKILL_HORROROFMOROS, STATE_HORROROFMOROS, 0, 1.0);
	sq_createAttackObjectWithPath(obj, 
	"passiveobject/actionobject/new/thief/necromancer/animation/horrorofmoros/horrorofmorosattack.ani",
	"passiveobject/actionobject/new/thief/necromancer/attackinfo/horrorofmorosattack.atk",true,atk,100,0,0,-800);		
}

function createHorrorOfMoros_Body(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/moros/morosattackbody.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local objectManager = obj.getObjectManager();
	local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
	local yPos = objectManager.getFieldYPos(500, 0, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(xPos ,yPos, 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createHorrorOfMoros_BackGround(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/moros/morosbackground_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local objectManager = obj.getObjectManager();
	local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
	local yPos = objectManager.getFieldYPos(500, 0, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(xPos ,yPos, 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createHorrorOfMoros_Cover(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/moros/morosattackcover_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local objectManager = obj.getObjectManager();
	local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
	local yPos = objectManager.getFieldYPos(700, 0, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(xPos ,yPos, 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createHorrorOfMoros_CoverCenter(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/moros/moroscovercenter_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local objectManager = obj.getObjectManager();
	local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
	local yPos = objectManager.getFieldYPos(400, 0, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(xPos ,yPos, 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createHorrorOfMoros_CoverFront(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/moros/moroscoverfront_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local objectManager = obj.getObjectManager();
	local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
	local yPos = objectManager.getFieldYPos(400, 0, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(xPos ,yPos, 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createHorrorOfMoros_Bottom(obj)
{
	local ani = sq_CreateAnimation("","character/thief/effect/animation/moros/morosbottom_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local objectManager = obj.getObjectManager();
	local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
	local yPos = objectManager.getFieldYPos(500, 0, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(xPos ,yPos, 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}
