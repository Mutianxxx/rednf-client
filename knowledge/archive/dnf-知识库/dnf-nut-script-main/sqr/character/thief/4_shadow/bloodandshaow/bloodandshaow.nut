//boom flash 600 560 600 255 0 0 0 bottom

//CUSTOM_ANI_BLOODANDSHAOW_READY <- 168
//CUSTOM_ANI_BLOODANDSHAOW_LOOP <- 169
//CUSTOM_ANI_BLOODANDSHAOW_FINISH <- 170
//ATTACKINFO_BLOODANDSHAOW_LOOP <- 65
function checkExecutableSkill_bloodandshaow(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_BLOODANDSHAOW);
	if (isUseSkill) 
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_BLOODANDSHAOW, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

/*function startSkillCoolTime_BLOODANDSHAOW(obj, skillIndex, skillLevel, currentCoolTime)
{
//    return 0;
    if (skillIndex != SKILL_HOTLOVE)
        return currentCoolTime;

    if (isDollState(obj))
        return currentCoolTime;

	local newCoolTime = currentCoolTime;
	local subtime = sq_GetLevelData(obj, SKILL_BLOODANDSHAOW, 5, sq_GetSkillLevel(obj, SKILL_BLOODANDSHAOW) );
    //10
    newCoolTime = (newCoolTime *(100 - subtime) ) / 100;

	return newCoolTime;	
}*/

function checkCommandEnable_bloodandshaow(obj)  
{

	return true;
}

function onKeyFrameFlag_BLOODANDSHAOW(obj,flagIndex)
{
    local state = obj.getVar("state").get_vector(0);

    if (obj.getVar("flag").get_vector(flagIndex) == 0)
    {
        obj.getVar("flag").set_vector(flagIndex,1);
        if (state == 0)
        {
            obj.sq_SetShake(obj, 4, 200);
        }else if (state == 1)
        {

            obj.resetHitObjectList();

            if (flagIndex == 1)
            {
                obj.sq_SetShake(obj, 4, 160);
            }else if (flagIndex == 4)
            {
                obj.sq_SetShake(obj, 3, 160);
            }else if (flagIndex == 25)
            {
                obj.sq_SetShake(obj, 3, 120);
            }else if (flagIndex == 18)
            {
                obj.sq_SetShake(obj, 2, 120);
            }else if (flagIndex == 9)
            {
                obj.sq_SetShake(obj, 2, 120);
            }else if (flagIndex == 11)
            {
                obj.sq_SetShake(obj, 3, 100);
            }

        }else if (state == 2)
        {
            if (flagIndex == 2)
            {

                local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOODANDSHAOW, STATE_BLOODANDSHAOW, 1, 1.0);
                obj.sq_StartWrite();
                obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
                obj.sq_WriteDword(98);	// attackBonusRate
                obj.sq_SendCreatePassiveObjectPacket(24357, 0, -obj.getVar("back").get_vector(0), obj.sq_GetIntData(SKILL_BLOODANDSHAOW, 4), obj.sq_GetIntData(SKILL_BLOODANDSHAOW, 5));

                obj.sq_SetShake(obj, 5, 200);
                sq_flashScreen(obj,200,560,200,204, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            }
        }



//            obj.getVar("speed").clear_vector();
//            obj.getVar("speed").push_vector(100);


        local currSpeed = obj.getVar("speed").get_vector(0);

        if (sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))
        {
           if (currSpeed + obj.sq_GetIntData(SKILL_BLOODANDSHAOW, 3) < obj.sq_GetIntData(SKILL_BLOODANDSHAOW, 2) )
           {
               currSpeed = currSpeed + obj.sq_GetIntData(SKILL_BLOODANDSHAOW, 3);
           }else{
               currSpeed = obj.sq_GetIntData(SKILL_BLOODANDSHAOW, 2);
           }
        }

        local currentAni = sq_GetCurrentAnimation(obj);
        currentAni.setSpeedRate(currSpeed.tofloat() );				
        obj.getVar("speed").set_vector(0,currSpeed);


    }

}

function onSetState_BLOODANDSHAOW(obj, state, datas, isResetTimer)
{	
    local state = obj.getVar("state").get_vector(0);
    obj.sq_StopMove();

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);

    if (state == 0)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODANDSHAOW_READY);
        sq_flashScreen(obj,500,4000,600,204, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

        obj.getVar("speed").clear_vector();
        obj.getVar("speed").push_vector( obj.sq_GetIntData(SKILL_BLOODANDSHAOW, 0) );

		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BLOODANDSHAOW, true,
		 "character/thief/4_shadow/bloodandshaow/ap_bloodandshaow.nut", false);

        local change_time = sq_GetLevelData(obj, SKILL_BLOODANDSHAOW, 2, sq_GetSkillLevel(obj, SKILL_BLOODANDSHAOW) );
        appendage.sq_SetValidTime(change_time);

		local skill_level = sq_GetSkillLevel(obj, SKILL_BLOODANDSHAOW);
		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_BLOODANDSHAOW, skill_level);
		
		CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_BLOODANDSHAOW, true);


    }else if (state == 1)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODANDSHAOW_LOOP);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODANDSHAOW_LOOP );

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODANDSHAOW , STATE_BLOODANDSHAOW, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				
        createHitEffectBloodAndShaow_PlayerEffect(obj);
        createHitEffectBloodAndShaow_a(obj);
//        createHitEffectBloodAndShaow_b(obj);
//        createHitEffectBloodAndShaow_c(obj);
//        createHitEffectBloodAndShaow_d(obj);


    }else if (state == 2)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODANDSHAOW_FINISH);
//        obj.sq_SetCurrentAttackInfo(ATTACKINFO_SPEEDLSADE_TLAST);
        sq_flashScreen(obj,100,1000,600,244, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);



        local backDistance = obj.sq_GetIntData(SKILL_BLOODANDSHAOW, 1);

		local downPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL);
        if (downPress) backDistance = obj.sq_GetIntData(SKILL_BLOODANDSHAOW, 6);

        local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), backDistance);

        obj.sq_SetfindNearLinearMovablePos(posX,obj.getYPos(),obj.getXPos(), obj.getYPos(), 10);

        obj.getVar("back").clear_vector();
        obj.getVar("back").push_vector(backDistance);

        createBloodAndShaowFinishEffect(obj,-backDistance,1,0);
        createBloodAndShaowFinishEffect2(obj,-backDistance,1,0);





    }
    obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function createBloodAndShaowFinishEffect3(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/newthier/animation/zetsuei/lastattackeffect/last01_normal01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}
function createBloodAndShaowFinishEffect(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/newthier/animation/zetsuei/lastattackeffect/last01_normal01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}
function createBloodAndShaowFinishEffect2(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/newthier/animation/zetsuei/lastattackeffect/last02_set06n11.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createHitEffectBloodAndShaow_a(obj)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/zetsuei/attack_hit01d01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createHitEffectBloodAndShaow_PlayerEffect(obj)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/zetsuei/playereffect/playereffect_black.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createHitEffectBloodAndShaow_b(obj)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/zetsuei/attack_set06d14.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createHitEffectBloodAndShaow_c(obj)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/zetsuei/effect_hit01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createHitEffectBloodAndShaow_d(obj)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/zetsuei/attack_set01body.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}
function onEndCurrentAni_BLOODANDSHAOW(obj)
{

    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_BLOODANDSHAOW, STATE_PRIORITY_USER, true);
    }else if (state == 1)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_BLOODANDSHAOW, STATE_PRIORITY_USER, true);
    }else if (state == 2)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }

}
