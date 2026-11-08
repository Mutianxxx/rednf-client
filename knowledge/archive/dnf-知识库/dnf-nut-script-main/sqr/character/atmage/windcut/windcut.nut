function checkExecutableSkill_windcut(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_WINDCUT);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_WINDCUT , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}

function checkCommandEnable_windcut(obj)
{

	return true;
}

function onSetState_WINDCUT(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_WINDCUT);
    obj.sq_SetCurrentAttackInfo(ATTACKINFO_WINDCUT);
	local ani = obj.sq_GetCurrentAni();
	local delay = 300;
    local attCount = sq_GetLevelData(obj, SKILL_WINDCUT, 1, sq_GetSkillLevel(obj, SKILL_WINDCUT));
    local size = sq_GetLevelData(obj, SKILL_WINDCUT, 2, sq_GetSkillLevel(obj, SKILL_WINDCUT));
    createWINDCUT(obj,size);

    local sizeRate = size.tofloat() / 100.0;
    local currentAni = sq_GetCurrentAnimation(obj);
    sq_SetAttackBoundingBoxSizeRate(currentAni, sizeRate, sizeRate, sizeRate);


    obj.setTimeEvent(0, delay/attCount, 0, true);

    local damage = obj.sq_GetBonusRateWithPassive(SKILL_WINDCUT , STATE_WINDCUT, 0, 1.0);
    obj.sq_SetCurrentAttackBonusRate(damage);				

	local currentAttackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackeHitStunTime(currentAttackInfo, 0);

	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);

}

function onEndState_WINDCUT(obj, new_state)
{

    local size = sq_GetLevelData(obj, SKILL_WINDCUT, 2, sq_GetSkillLevel(obj, SKILL_WINDCUT));
    local sizeRate = 100.0 / size.tofloat() ;
    local currentAni = sq_GetCurrentAnimation(obj);
    sq_SetAttackBoundingBoxSizeRate(currentAni, sizeRate, sizeRate, sizeRate);

}

function createWINDCUT(obj,size)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atwindcut/windcut_eff_01.ani");
    local sizeRate = size.tofloat() / 100.0;
	local pooledObj = sq_CreatePooledObject(ani,true);
	
	pooledObj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());

    local currentAni = sq_GetCurrentAnimation(pooledObj);
    currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
    currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
	
	sq_AddObject(obj,pooledObj,0,false);	

}



function onEndCurrentAni_WINDCUT(obj)
{




	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

function onTimeEvent_WINDCUT(obj, timeEventIndex, timeEventCount)
{

    if (timeEventIndex == 0)
    {
        obj.resetHitObjectList();
    }
}