function checkExecutableSkill_newblooddoghold(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_NEWBLOODDOGHOLD);
	if (isUseSkill) {
		obj.sq_AddSetStatePacket(STATE_NEWBLOODDOGHOLD, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_newblooddoghold(obj)
{
	if(!obj)
		return false;
		
    if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_NEWBLOODDOGHOLD, 2)))
    return false;
	return true;
}


function setCharacterFristAnimation_PhatomBale(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_NEWBLOODDOGHOLD );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/newblooddoghold/last.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/newblooddoghold/loop.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/newblooddoghold/ready.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atphantombale/02_attack00/hit/atphantombale_attack00_hit_base.ani");

        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atphantombale/02_attack00/hit/atphantombale_attack00_hit_base.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atphantombale/02_attack00/front/atphantombale_attack00_front_base.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atphantombale/02_attack00/back/atphantombale_attack00_back_base.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atphantombale/04_finish/finish_back.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atphantombale/02_attack00/hit/atphantombale_attack00_hit_base.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/newblooddoghold/atphantombale_body.ani");
    }
}


function onSetState_NBDDH(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	obj.sq_StopMove();
    obj.sq_SendCreatePassiveObjectPacket(12335, 0, 0, 1, 0);
    obj.sq_PlaySound("BLOODDOWN_4");
//    setBloodValue(obj,-obj.sq_GetIntData(SKILL_NEWBLOODDOGHOLD, 2));

	obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOODDOGHOLD_READY);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);
}


function onEndCurrentAni_NBDDH(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}


function onKeyFrameFlag_NBDDH(obj,flagIndex)
{
	if(!obj)
		return false;

	local isMyControlObject = obj.sq_IsMyControlObject();


	if (isMyControlObject && flagIndex == 1)
	{
		


		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

		local upPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL);
		local downPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL);

        local len = obj.sq_GetIntData(SKILL_NEWBLOODDOGHOLD, 3);
		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_NEWBLOODDOGHOLD, STATE_NEWBLOODDOGHOLD, 0, 1.0);
		local attackBonusRate2 = obj.sq_GetBonusRateWithPassive(SKILL_NEWBLOODDOGHOLD, STATE_NEWBLOODDOGHOLD, 1, 1.0);
				

		if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && rightPress) len = obj.sq_GetIntData(SKILL_NEWBLOODDOGHOLD, 6);
		if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && leftPress) len = obj.sq_GetIntData(SKILL_NEWBLOODDOGHOLD, 6);

				
		obj.sq_StartWrite();
		obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
		obj.sq_WriteDword(4);		// power
		obj.sq_WriteDword(obj.sq_GetIntData(SKILL_NEWBLOODDOGHOLD, 0));		// power
		obj.sq_WriteDword(obj.sq_GetIntData(SKILL_NEWBLOODDOGHOLD, 1));		// power
		obj.sq_WriteDword(attackBonusRate2);	// attackBonusRate
		obj.sq_WriteDword(obj.sq_GetIntData(SKILL_NEWBLOODDOGHOLD, 4) );		// power
		obj.sq_WriteDword(obj.sq_GetIntData(SKILL_NEWBLOODDOGHOLD, 5) );
		obj.sq_SendCreatePassiveObjectPacket(24357, 0, len, 1, 0);
        createPhantomBaleStart_Front(obj,len,2,0);
        createPhantomBaleStart_Bat(obj,len,1,0);
        createPhantomBaleStart_Back(obj,len,-1,0);

	}
	return true;
}


function createPhantomBaleStart_HitEffect(obj,x,y,z)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atphantombale/02_attack00/hit/atphantombale_attack00_hit_base.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + y,obj.getZPos() + z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createPhantomBaleStart_Front(obj,x,y,z)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atphantombale/02_attack00/front/atphantombale_attack00_front_base.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + y,z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createPhantomBale4State_1_HitEffect(obj,damager)
{

	local ani = null;

    local rand = sq_getRandom(0,4).tointeger();

    if (rand == 0)
    {
        ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atphantombale/bitehiteffect/hit01.ani");
    }else if (rand == 1)
    {
        ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atphantombale/bitehiteffect/hit02.ani");
    }else if (rand == 2)
    {
        ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atphantombale/bitehiteffect/hit03.ani");
    }else
    {
        ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atphantombale/bitehiteffect/hit04.ani");
    }


	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(damager.getXPos(), damager.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createPhantomBaleStart_Back(obj,x,y,z)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atphantombale/02_attack00/back/atphantombale_attack00_back_base.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + y,z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createPhantomBaleStart_Bat(obj,x,y,z)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atphantombale/02_attack00/bat/atphantombale_attack00_bat_base.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + y,z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createPhantomBaleFinalyBack(obj,x,y,z)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atphantombale/04_finish/atphantombale_finish_crack.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + y,z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createPhantomBaleFinalySplashBase(obj,x,y,z)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atphantombale/04_finish/splash/atphantombale_finish_splash_base.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + y,z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createPhantomBaleFinalyFrontBackEffect(obj,x,y,z)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atphantombale/04_finish/finish_back.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + y,z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createPhantomBaleLoopHitEffect(obj,damager)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atphantombale/02_attack00/hit/atphantombale_attack00_hit_base.ani");

	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(damager.getXPos(), damager.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}