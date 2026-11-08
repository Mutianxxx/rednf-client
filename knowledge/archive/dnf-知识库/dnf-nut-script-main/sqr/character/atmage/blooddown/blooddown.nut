function checkExecutableSkill_blooddown(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_BLOODDOWN);

	if (isUse) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0); 
		obj.sq_AddSetStatePacket(STATE_BLOODDOWN , STATE_PRIORITY_USER, true);
		return true;
	}

	return false;
}

function checkCommandEnable_blooddown(obj)
{
	if (!obj) return false;	
    if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_BLOODDOWN, 3)))
    return false;
	return true;
}




function setCharacterFristAnimation_Torment(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_BLOODDOWN );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attorment/torment_end_effb01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attorment/torment_loop_back_eff01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attorment/torment_loop_effb01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attorment/torment_start_back_eff01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attorment/torment_start_effb01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attorment/torment_loop_effb01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attorment/torment_loop_back_eff01.ani");

        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/blooddown/torment_end_body.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/blooddown/torment_loop_body.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/blooddown/torment_start_body.ani");

    }
}



function createBloodDownAni(obj,ani,y,z)
{
    ani = sq_CreateAnimation("",ani);
    local size = obj.sq_GetIntData(SKILL_BLOODDOWN,2);
    local sizeRate = size.tofloat()/100.0;
    ani.setImageRateFromOriginal(sizeRate, sizeRate);
    ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);


	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector(pooledObj);
}

function clearBloodDownEffectObj(obj)
{
    local var = obj.getVar("effectObj");  		
    local objectsSize = var.get_obj_vector_size();

    for(local i=0;i<objectsSize;++i)
    {
        local effectObj = var.get_obj_vector(i);
        if (effectObj)
        {
//            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos(), obj.getYPos(), 0 );
            effectObj.setValid(false);
        }
    }
}

function onSetState_BLOODDOWN(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	obj.sq_StopMove();

	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
    local size = obj.sq_GetIntData(SKILL_BLOODDOWN,2);

    local posZ = (50 * size) / 100;

    if (state == 0)
    {
        obj.getVar("effectObj").clear_obj_vector();
        if (obj.isMyControlObject())
        {
            setBloodValue(obj,-obj.sq_GetIntData(SKILL_BLOODDOWN, 3));
            sq_flashScreen(obj,120,0,0,102, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            obj.sq_PlaySound("TORMENT_BURST");
            obj.sq_PlaySound("MW_TORMENT");

        }
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODDOWN_START);



        createBloodDownAni(obj,"passiveobject/zrr_skill/atmage/animation/attorment/torment_start_back_eff01.ani",-1,posZ);
        createBloodDownAni(obj,"passiveobject/zrr_skill/atmage/animation/attorment/torment_start_effb01.ani",1,0);


    }else if (state == 1)
    {


        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODDOWN_LOOP);

        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODDOWN , STATE_BLOODDOWN, 0, 1.0);
	if(obj.isMyControlObject())
    {

        local hitcount = obj.sq_GetIntData(SKILL_BLOODDOWN,0);
        local time = obj.sq_GetIntData(SKILL_BLOODDOWN,1) + obj.sq_GetIntData(SKILL_BLOODDOWN,1) / hitcount;

        obj.setTimeEvent(0,time,0,false);		
        obj.sq_SetShake(obj, 3, time);

		obj.sq_StartWrite();
		obj.sq_WriteDword(damage);	// attackBonusRate
		obj.sq_WriteDword(54);	// attackBonusRate
		obj.sq_WriteDword( size );	// attackBonusRate
		obj.sq_WriteDword( time );	// attackBonusRate
		obj.sq_WriteDword( hitcount );	// attackBonusRate

		obj.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);
    }

        clearBloodDownEffectObj(obj);
        createBloodDownAni(obj,"passiveobject/zrr_skill/atmage/animation/attorment/torment_loop_back_eff01.ani",-1,posZ);
        createBloodDownAni(obj,"passiveobject/zrr_skill/atmage/animation/attorment/torment_loop_effb01.ani",1,0);

    }else if (state == 2)
    {
        obj.sq_SetShake(obj, 6, 200);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODDOWN_END);

        clearBloodDownEffectObj(obj);
        createBloodDownAni(obj,"passiveobject/zrr_skill/atmage/animation/attorment/torment_end_back_eff.ani",-1,posZ);
        createBloodDownAni(obj,"passiveobject/zrr_skill/atmage/animation/attorment/torment_end_effb01.ani",1,0);

    }

	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);

}

function onEndState_BLOODDOWN(obj, new_state)
{
    if (new_state != STATE_BLOODDOWN)
    {
        clearBloodDownEffectObj(obj);
    }
}


function onTimeEvent_BLOODDOWN(obj, timeEventIndex, timeEventCount)
{
	if(!obj.isMyControlObject()) {
		return;
	}
    local state = obj.getSkillSubState();
    if (state == 1)
    {
        if (timeEventIndex == 0)
        {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(2); 
            obj.sq_AddSetStatePacket(STATE_BLOODDOWN , STATE_PRIORITY_USER, true);

        }
    }
}


function onEndCurrentAni_BLOODDOWN(obj)
{
	if(!obj.isMyControlObject()) {
		return;
	}
    local state = obj.getSkillSubState();
    if (state == 0)
    {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1); 
		obj.sq_AddSetStatePacket(STATE_BLOODDOWN , STATE_PRIORITY_USER, true);
    }else if (state == 2)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }

}


function onProc_BLOODDOWN(obj)
{

    local pAni = obj.sq_GetCurrentAni();
    local currentT = sq_GetCurrentTime(pAni);
    local state = obj.getSkillSubState();
    local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
    if (state == 0)
    {
        if (frmIndex == 2)
        {

            if(obj.isMyControlObject())
            {
                sq_flashScreen(obj,0,60,120,204, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            }
        }
    }

}
