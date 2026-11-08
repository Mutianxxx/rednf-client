//state 0
//state 1 onsetstate flash 0 60 80 76 255 0 0 bottom shake 10 250
//state 2 onsetstate shake 5 180
//state 3 flag1 shake 5 180
//state 4 flag1 shake 5 180
//state 5 flag2 jump
//state 6
//state 7 onsetstate flash 300 100 500 153 0 0 0 bottom
//flag 1 finish dash shake 5 180

//passiveobject 
//start flash 60 60 0 76 255 255 255 cover  shake 10 180

//CUSTOM_ANI_BLOODSHAOWSLASH_CASTING <- 156
//CUSTOM_ANI_BLOODSHAOWSLASH_CASTING_SLASH <- 157
//CUSTOM_ANI_BLOODSHAOWSLASH_SLASH2 <- 158
//CUSTOM_ANI_BLOODSHAOWSLASH_SLASH3 <- 159
//CUSTOM_ANI_BLOODSHAOWSLASH_SLASH4 <- 160
//CUSTOM_ANI_BLOODSHAOWSLASH_SLASH5 <- 161
//CUSTOM_ANI_BLOODSHAOWSLASH_SLASH6 <- 162
//CUSTOM_ANI_BLOODSHAOWSLASH_SLASH7 <- 163

//ATTACKINFO_BLOODSHAOWSLASH_CASTING <- 59
//ATTACKINFO_BLOODSHAOWSLASH_LOOP <- 60
//ATTACKINFO_BLOODSHAOWSLASH_FINISH <- 61

function checkExecutableSkill_bloodshaowslash(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_BLOODSHAOWSLASH);
	if (isUseSkill) 
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_BLOODSHAOWSLASH, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_bloodshaowslash(obj)  
{

	return true;
}

function onAttack_BLOODSHAOWSLASH(obj, damager, boundingBox, isStuck)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {
        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODSHAOWSLASH, false, 
        "character/thief/4_shadow/bloodshaowslash/ap_bloodshaowslash.nut", true);				 

        createHitEffectBloodShaowSlash_a(obj,damager);
        if (isEnemyBack(obj,damager) )
        {
            obj.getVar("isBack").clear_vector();
            obj.getVar("isBack").push_vector(1);
        }

    }else if (state == 2)
    {
        createHitEffectBloodShaowSlash_a(obj,damager);
    }else if (state == 3)
    {
        createHitEffectBloodShaowSlash_b(obj,damager);
    }else if (state == 4)
    {
        createHitEffectBloodShaowSlash_c(obj,damager);
    }else if (state == 5)
    {
        createHitEffectBloodShaowSlash_d(obj,damager);
    }else if (state == 6)
    {
    }else if (state == 7)
    {
        if(damager)
        {
            CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/thief/4_shadow/bloodshaowslash/ap_bloodshaowslash.nut");		
        }
        createHitEffectBloodShaowSlash_c(obj,damager);
        createHitEffectBloodShaowSlash_d(obj,damager);
    }
}

function createHitEffectBloodShaowSlash_a(obj,damager)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/finaldestruction/finaldestruction_blood2_start.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createHitEffectBloodShaowSlash_b(obj,damager)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/finaldestruction/finialdestruction_hit_dodge.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createHitEffectBloodShaowSlash_c(obj,damager)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/finaldestruction/finaldestruction_hit2_normal.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createHitEffectBloodShaowSlash_d(obj,damager)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/finaldestruction/finaldestruction_backhit_front_normal.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createLineBloodShaowSlash(obj)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/finaldestruction/finaldestruction_backhit_line_normal.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}
function onKeyFrameFlag_BLOODSHAOWSLASH(obj,flagIndex)
{
    local state = obj.getVar("state").get_vector(0);

    if (obj.getVar("flag").get_vector(flagIndex) == 0)
    {
        obj.getVar("flag").set_vector(flagIndex,1);

        if (flagIndex == 1)
        {
            if (state == 3)
            {
                obj.sq_SetShake(obj, 5, 180);
            }else if (state == 4)
            {
                obj.sq_SetShake(obj, 5, 180);
            }else if (state == 7)
            {
                obj.sq_SetShake(obj, 5, 180);
                //dash
//                createLineBloodShaowSlash(obj);
                local ani = obj.sq_GetCurrentAni();
                local startCurrentTime = sq_GetCurrentTime(ani);
                local len = obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,7);
                local dashTime = obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,8);
                obj.getVar("mov2").clear_vector();
                obj.getVar("mov2").push_vector(1);


                obj.getVar("mov").clear_vector();
                obj.getVar("mov").push_vector( obj.getXPos() );
                obj.getVar("mov").push_vector( len );
                obj.getVar("mov").push_vector( startCurrentTime );
                obj.getVar("mov").push_vector( dashTime );
            }
        }else if (flagIndex == 2)
        {
            if (state == 5)
            {
                sq_SetZVelocity(obj,obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,9),obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,10));
            }
        }
    }

}



function onSetState_BLOODSHAOWSLASH(obj, state, datas, isResetTimer)
{	
    local state = obj.getVar("state").get_vector(0);
	obj.sq_StopMove();
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);

    if (state == 0)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSHAOWSLASH_CASTING);
//        obj.sq_SetCurrentAttackInfo(ATTACKINFO_CUTNECK_DOWN);

        obj.getVar("isBack").clear_vector();
        obj.getVar("isBack").push_vector(0);


    }else if (state == 1)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSHAOWSLASH_CASTING_SLASH);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODSHAOWSLASH_CASTING);


        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSHAOWSLASH , STATE_BLOODSHAOWSLASH, 1, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);		

        sq_flashScreen(obj,0,60,80,76, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        obj.sq_SetShake(obj, 10, 250);
//obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,0);
        local ani = obj.sq_GetCurrentAni();
		local delay = ani.getDelaySum(false);
        local len = obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,0);

		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

		if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && leftPress) len = obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,1);
		if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && rightPress) len = obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,2);

        obj.getVar("mov").clear_vector();
        obj.getVar("mov").push_vector( obj.getXPos() );
        obj.getVar("mov").push_vector( len );
        obj.getVar("mov").push_vector( delay );

    }else if (state == 2)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSHAOWSLASH_SLASH2);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODSHAOWSLASH_LOOP);

        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSHAOWSLASH , STATE_BLOODSHAOWSLASH, 1, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);		

        obj.sq_SetShake(obj, 5, 180);
    }else if (state == 3)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSHAOWSLASH_SLASH3);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODSHAOWSLASH_LOOP);
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSHAOWSLASH , STATE_BLOODSHAOWSLASH, 1, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);		

    }else if (state == 4)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSHAOWSLASH_SLASH4);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODSHAOWSLASH_LOOP);
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSHAOWSLASH , STATE_BLOODSHAOWSLASH, 1, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);		
    }else if (state == 5)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSHAOWSLASH_SLASH5);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODSHAOWSLASH_LOOP);
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSHAOWSLASH , STATE_BLOODSHAOWSLASH, 2, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);		

        local ani = obj.sq_GetCurrentAni();
		local delay = ani.getDelaySum(false);
        local len = obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,3);

		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

		if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && leftPress) len = obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,4);
		if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && rightPress) len = obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,5);


        obj.getVar("mov").clear_vector();
        obj.getVar("mov").push_vector( obj.getXPos() );
        obj.getVar("mov").push_vector( len );
        obj.getVar("mov").push_vector( delay );

    }else if (state == 6)//drop
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSHAOWSLASH_SLASH6);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODSHAOWSLASH_LOOP);
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSHAOWSLASH , STATE_BLOODSHAOWSLASH, 3, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);		

        local dropTime = obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,6);

        obj.getVar("mov").clear_vector();
        obj.getVar("mov").push_vector( obj.getZPos() );
        obj.getVar("mov").push_vector( dropTime );

        obj.getVar("dropValue").clear_vector();
        obj.getVar("dropValue").push_vector(0);

    }else if (state == 7)
    {
        sq_flashScreen(obj,300,100,500,153, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSHAOWSLASH_SLASH7);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODSHAOWSLASH_FINISH);
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSHAOWSLASH , STATE_BLOODSHAOWSLASH, 0, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);		

        obj.getVar("mov").clear_vector();
        obj.getVar("mov2").clear_vector();
        obj.getVar("mov2").push_vector(0);

    }
    obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onProc_BLOODSHAOWSLASH(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
    }else if (state == 1)
    {
//        obj.getVar("mov").clear_vector();
//        obj.getVar("mov").push_vector( obj.getXPos() );
//        obj.getVar("mov").push_vector( len );
//        obj.getVar("mov").push_vector( delay );

        local startX = obj.getVar("mov").get_vector(0);
        local len = obj.getVar("mov").get_vector(1);
        local delay = obj.getVar("mov").get_vector(2);

        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);
        local vX = sq_GetAccel(0, len, currentT, delay, true);

		local dstX = sq_GetDistancePos(startX, obj.getDirection(),vX);

		if(obj.isMovablePos(dstX, obj.getYPos() ))
        {
			sq_setCurrentAxisPos(obj, 0, dstX);
        }

    }else if (state == 2)
    {
    }else if (state == 3)
    {
    }else if (state == 4)
    {
    }else if (state == 5)
    {

//        obj.getVar("mov").clear_vector();
//        obj.getVar("mov").push_vector( obj.getXPos() );
//        obj.getVar("mov").push_vector( len );
//        obj.getVar("mov").push_vector( delay );

        local startX = obj.getVar("mov").get_vector(0);
        local len = obj.getVar("mov").get_vector(1);
        local delay = obj.getVar("mov").get_vector(2);

        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);
        local vX = sq_GetAccel(0, len, currentT, delay, true);

		local dstX = sq_GetDistancePos(startX, obj.getDirection(),vX);

		if(obj.isMovablePos(dstX, obj.getYPos() ))
        {
			sq_setCurrentAxisPos(obj, 0, dstX);
        }
    }else if (state == 6)
    {
//        obj.getVar("mov").clear_vector();
//        obj.getVar("mov").push_vector( obj.getZPos() );
//        obj.getVar("mov").push_vector( dropTime );

        local startZ = obj.getVar("mov").get_vector(0);
        local dropT = obj.getVar("mov").get_vector(1);

        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);


        if (currentT < dropT)
        {
            local vZ = sq_GetAccel(0, startZ, currentT, dropT, true);
			sq_setCurrentAxisPos(obj, 2, startZ - vZ);
        }else{
            if (obj.getVar("dropValue").get_vector(0) == 0)
            {
                obj.getVar("dropValue").clear_vector();
                obj.getVar("dropValue").push_vector(1);

//passiveobject 
//start flash 60 60 0 76 255 255 255 cover  shake 10 180

                sq_flashScreen(obj,60,60,0,76, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
                obj.sq_SetShake(obj, 10, 180);

                local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSHAOWSLASH , STATE_BLOODSHAOWSLASH, 3, 1.0);

                obj.sq_StartWrite();
                obj.sq_WriteDword(damage);	// attackBonusRate
                obj.sq_WriteDword(97);	// attackBonusRate
                obj.sq_SendCreatePassiveObjectPacket(24357, 0,obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,11),obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,12), obj.sq_GetIntData(SKILL_BLOODSHAOWSLASH,13) );

            }

			sq_setCurrentAxisPos(obj, 2, 0);
        }


    }else if (state == 7)
    {
//                obj.getVar("mov").clear_vector();
//                obj.getVar("mov").push_vector( obj.getXPos() );   0
//                obj.getVar("mov").push_vector( len );             1
//                obj.getVar("mov").push_vector( startCurrentTime );2
//                obj.getVar("mov").push_vector( dashTime );        3

        if (obj.getVar("mov2").get_vector(0) == 1)
        {
            local startX = obj.getVar("mov").get_vector(0);
            local len = obj.getVar("mov").get_vector(1);
            local startCurrentTime = obj.getVar("mov").get_vector(2);
            local dashTime = obj.getVar("mov").get_vector(3);


            local pAni = obj.sq_GetCurrentAni();
            local currentT = sq_GetCurrentTime(pAni);
        
            if (currentT - startCurrentTime < dashTime)
            {
                local vX = sq_GetAccel(0, len, currentT - startCurrentTime, dashTime, true);

                local dstX = sq_GetDistancePos(startX, obj.getDirection(),vX);

                if(obj.isMovablePos(dstX, obj.getYPos() ))
                {
                    sq_setCurrentAxisPos(obj, 0, dstX);
                }
            }
        }
    }


}



function onEndCurrentAni_BLOODSHAOWSLASH(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_BLOODSHAOWSLASH, STATE_PRIORITY_USER, true);
    }else if (state == 1)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_BLOODSHAOWSLASH, STATE_PRIORITY_USER, true);
    }else if (state == 2)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(3);
		obj.sq_AddSetStatePacket(STATE_BLOODSHAOWSLASH, STATE_PRIORITY_USER, true);
    }else if (state == 3)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(4);
		obj.sq_AddSetStatePacket(STATE_BLOODSHAOWSLASH, STATE_PRIORITY_USER, true);
    }else if (state == 4)
    {
        if (obj.getVar("isBack").get_vector(0) == 1)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(5);
            obj.sq_AddSetStatePacket(STATE_BLOODSHAOWSLASH, STATE_PRIORITY_USER, true);
        }else{
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(7);
            obj.sq_AddSetStatePacket(STATE_BLOODSHAOWSLASH, STATE_PRIORITY_USER, true);
        }
    }else if (state == 5)
    {
//            obj.getVar("isBack").clear_vector();
//            obj.getVar("isBack").push_vector(1);


            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(6);
            obj.sq_AddSetStatePacket(STATE_BLOODSHAOWSLASH, STATE_PRIORITY_USER, true);

    }else if (state == 6)
    {
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSHAOWSLASH , STATE_BLOODSHAOWSLASH, 3, 1.0);
        sendOneHitAllMonsterShaowAreaObj(obj,damage);
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 7)
    {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}