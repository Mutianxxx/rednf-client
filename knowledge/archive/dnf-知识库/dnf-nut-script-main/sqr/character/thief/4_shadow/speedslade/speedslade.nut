//CUSTOM_ANI_SPEEDSLADE_START <- 139
//CUSTOM_ANI_SPEEDSLADE_LOOPS <- 140
//CUSTOM_ANI_SPEEDLSADE_TLAST <- 141
//ATTACKINFO_SPEEDSLADE_LOOPS <- 54
//ATTACKINFO_SPEEDLSADE_TLAST <- 55

function checkExecutableSkill_speedslade(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_SPEEDSLADE);
	if (isUseSkill) 
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_SPEEDSLADE, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_speedslade(obj)  
{

	return true;
}

function onKeyFrameFlag_SPEEDSLADE(obj,flagIndex)
{
	if(!obj)
		return false;
    local state = obj.getVar("state").get_vector(0);
    if (state == 2)
    {
        if (flagIndex == 1)
        {

            if (obj.getVar("flag").get_vector(0) == 0)
            {
                obj.getVar("flag").clear_vector();
                obj.getVar("flag").push_vector(1);

                obj.sq_SetShake(obj, 5, 100);


            }
        }
    }
}

function onAttack_SPEEDSLADE(obj, damager, boundingBox, isStuck)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {
		if(!sq_IsFixture(damager)) 
        {
            if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/4_shadow/speedslade/ap_speedslade.nut"))
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_SPEEDSLADE, false, 
                "character/thief/4_shadow/speedslade/ap_speedslade.nut", true);				 
            }
        }
    }else if (state == 2)
    {
		if(!sq_IsFixture(damager)) 
        {
            local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), sq_GetIntData(obj, SKILL_SPEEDSLADE, 1) );
            damager.setCurrentPos(posX,obj.getYPos() - 1,0);
        }


//		damager.setCurrentDirection( obj.getDirection() );
    }
}

function createSpeedSladeFinishBack(obj,len,z)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/bladegust/bladegust_finish_back.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), len);
	
	pooledObj.setCurrentPos(posX,obj.getYPos() - 1,obj.getZPos() + z);
	
	pooledObj.setCurrentDirection(obj.getDirection());
	
	sq_AddObject(obj,pooledObj,0,false);	
}

function createBackSpeedSladeFinishBackGround(obj)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/bladegust/bladegust_finish_back_ground.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() - 2,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createBackSpeedSladeFinishNormalGround(obj)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/bladegust/bladegust_finish_normal_ground.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function onProc_SPEEDSLADE(obj)
{

	if(!obj) return;
    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {
        local isPress = sq_IsKeyDown(OPTION_HOTKEY_JUMP, ENUM_SUBKEY_TYPE_ALL)
        if (isPress)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(2);
            obj.sq_AddSetStatePacket(STATE_SPEEDSLADE, STATE_PRIORITY_USER, true);
        }   
    }
}

function onSetState_SPEEDSLADE(obj, state, datas, isResetTimer)
{	
    local state = obj.getVar("state").get_vector(0);
    obj.sq_StopMove();
    if (state == 0)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPEEDSLADE_START);
//        obj.sq_SetCurrentAttackInfo(ATTACKINFO_HOLDUP );
//		local damage = obj.sq_GetBonusRateWithPassive(SKILL_HOLDUP , STATE_HOLDUP , 0, 1.0);
//		obj.sq_SetCurrentAttackBonusRate(damage);				
    }else if (state == 1)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPEEDSLADE_LOOPS);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_SPEEDSLADE_LOOPS );
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SPEEDSLADE , STATE_SPEEDSLADE , 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				
		local ani = obj.sq_GetCurrentAni();
		local delay = ani.getDelaySum(false);

        local atkCount = sq_GetIntData(obj, SKILL_SPEEDSLADE, 0);
        obj.setTimeEvent(0,delay / atkCount ,0,true);		

    }else if (state == 2)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPEEDLSADE_TLAST);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_SPEEDLSADE_TLAST);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SPEEDSLADE , STATE_SPEEDSLADE , 2, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        createSpeedSladeFinishBack(obj,0,0);
        createBackSpeedSladeFinishBackGround(obj);
        createBackSpeedSladeFinishNormalGround(obj);
    }
    obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onTimeEvent_SPEEDSLADE(obj, timeEventIndex, timeEventCount)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {
        if (timeEventIndex == 0)
        {
                    obj.resetHitObjectList();

        }
    }
}

function onEndCurrentAni_SPEEDSLADE(obj)
{

    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_SPEEDSLADE, STATE_PRIORITY_USER, true);
    }else if (state == 1)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_SPEEDSLADE, STATE_PRIORITY_USER, true);
    }else if (state == 2)
    {
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SPEEDSLADE , STATE_SPEEDSLADE , 2, 1.0);
        sendOneHitAllMonsterShaowAreaObj(obj,damage);
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }

}