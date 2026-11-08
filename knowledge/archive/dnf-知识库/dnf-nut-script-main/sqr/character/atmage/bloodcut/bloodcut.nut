function checkExecutableSkill_bloodcut(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_BLOODCUT);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_BLOODCUT , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}

function checkCommandEnable_bloodcut(obj)
{
	if (!obj) return false;
    if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_BLOODCUT, 1)))
        return false;
	local state = obj.sq_GetState();
		return true;

	return false;
}

function setCharacterFristAnimation_Fang(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_BLOODCUT );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/bloodcut/bloodcut_ready.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atfang/blood_awake/atfang_attack_awake.ani");


    }
}


function onSetState_BLOODCUT(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	obj.sq_StopMove();
    if (obj.isMyControlObject())
        setBloodValue(obj,-obj.sq_GetIntData(SKILL_BLOODCUT, 1));
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODCUT_READY);

	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);

}

function onEndCurrentAni_BLOODCUT(obj)
{
	if(!obj.isMyControlObject()) {
		return;
	}
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

function onKeyFrameFlag_BLOODCUT(obj,flagIndex)
{
	if(!obj)
		return false;

	local isMyControlObject = obj.sq_IsMyControlObject();

	if (isMyControlObject && flagIndex == 1)
	{

        local len = obj.sq_GetIntData(SKILL_BLOODCUT, 0);
        local disT = len;

		local targetObj = findAngleTarget(obj, disT, 180, 100);
		if(targetObj) {
            disT = sq_Abs( targetObj.getXPos() - obj.getXPos() );
        }

		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOODCUT, STATE_BLOODCUT, 0, 1.0);
		obj.sq_StartWrite();
		obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
		obj.sq_WriteDword(0);	// attackBonusRate
		obj.sq_WriteDword( obj.sq_GetIntData(SKILL_BLOODCUT, 2) );
		obj.sq_SendCreatePassiveObjectPacket(24357, 0, disT, 1, 0);

/*
    	local ani = sq_CreateAnimation("","common/monster/new_warn/warningfloor_linebottom.ani");
	setChainEffectWithAnimationByCurrentPos(ani,
	[obj.getXPos(),obj.getYPos(),obj.getZPos()],
	[obj.getXPos() + 100,obj.getYPos() - 100,obj.getZPos()],
	400);
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),0);
	sq_AddObject(obj,pooledObj,2,false);	
*/


	}
	return true;
}


