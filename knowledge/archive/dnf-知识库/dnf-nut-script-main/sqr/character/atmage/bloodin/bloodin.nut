function checkExecutableSkill_bloodin(obj)  
{
	if (!obj) return false;

	local isUse = obj.sq_IsUseSkill(SKILL_BLOODIN);
    if (isUse)
    {

        obj.sq_AddSetStatePacket(STATE_BLOODIN, STATE_PRIORITY_USER, true);
    }
    return true;
}




function setCharacterFristAnimation_SoulSteel(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_BLOODIN );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atsoulsteel/flash_red.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atsoulsteel/awake/soulsteelawake_front_end_sp3.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atsoulsteel/awake/soulsteelawake_front_loop_sp3.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atsoulsteel/awake/soulsteelawake_front_start_up.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atsoulsteel/floor/floor_end_blackloop8.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atsoulsteel/floor/floor_loop_blackloop8.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atsoulsteel/floor/floor_start_blackloop8.ani");

        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/bloodin.ani");

    }
}



function checkCommandEnable_bloodin(obj)
{
	if(!obj)
		return false;
    if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_BLOODIN, 5)))
    return false;

	return true;
}

function onSetState_BLOODIN(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
    if (obj.isMyControlObject())
        setBloodValue(obj,-obj.sq_GetIntData(SKILL_BLOODIN, 5));

    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODIN);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);

}

function onEndCurrentAni_BLOODIN(obj)
{
	if(!obj.isMyControlObject()) {
		return;
	}
    obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

function createBloodInFlash(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atsoulsteel/flash_red.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() - 2,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}


function createBloodInEndFloorEffect(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atsoulsteel/floor/floor_end_blackloop8.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() - 2,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}

function onKeyFrameFlag_BLOODIN(obj,flagIndex)
{
    if (flagIndex == 1 && obj.isMyControlObject() )
    {

        local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOODIN, STATE_BLOODIN, 0, 1.0);

        sq_BinaryStartWrite();
		sq_BinaryWriteDword(attackBonusRate);	// attackBonusRate
        sq_BinaryWriteDword(1);
        sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODIN, 0));//cx time
        sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODIN, 1));//attack time
        sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODIN, 2));//max size
        sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODIN, 3));//min size
        sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODIN, 4));//sub value
        sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODIN, 6));//sub value
		obj.sq_SendCreatePassiveObjectPacket(24366, 0, 0, -1, 0);
        obj.sq_SetShake(obj, 2, 200);
        createBloodInFlash(obj);
        return true;
//        sq_flashScreen(obj,200,0,200,200, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
    }
}