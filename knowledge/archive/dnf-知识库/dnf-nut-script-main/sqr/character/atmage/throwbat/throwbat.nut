function checkExecutableSkill_throwbat(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_THROWBAT);
	if (isUseSkill) {

		obj.sq_AddSetStatePacket(STATE_THROWBAT, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_throwbat(obj)
{

		
	return true;
}

function onSetState_THROWBAT(obj, state, datas, isResetTimer)
{

	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_THROWBAT_BOBY);
    createThrowBatAwakeningCasting(obj);
//	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
//			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}



function onEndCurrentAni_THROWBAT(obj)
{
    if(!obj.isMyControlObject())
        return false;
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}



function createThrowBatHitEffect(obj,damager)
{
    if(!obj.isMyControlObject())
        return false;
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atliliac/particle_1.ani");
	local rand = sq_getRandom(0,4).tointeger();
    if (rand > 3)
        ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atliliac/particle_2.ani");
    else if (rand > 2)
        ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atliliac/particle_3.ani");
    else if (rand > 1)
        ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atliliac/particle_4.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createThrowBatAwakeningCasting(obj)
{
    if(!obj.isMyControlObject())
        return false;
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atliliac/liliac_castawake_effect.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function onKeyFrameFlag_THROWBAT(obj,flagIndex)
{
	if(!obj)
		return false;

	local isMyControlObject = obj.sq_IsMyControlObject();

	// ????? ??????? ????
	if (isMyControlObject && flagIndex == 1)
	{

		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_THROWBAT, STATE_THROWBAT, 0, 1.0);
//		local attackBonusRate2 = obj.sq_GetBonusRateWithPassive(SKILL_THROWBAT, STATE_THROWBAT, 1, 1.0);

        local distance = obj.sq_GetIntData(SKILL_THROWBAT, 0);
        local attackSumTime = obj.sq_GetIntData(SKILL_THROWBAT, 1);
        local attackTime = obj.sq_GetIntData(SKILL_THROWBAT, 2);
        local absortBlood = obj.sq_GetIntData(SKILL_THROWBAT, 3);
        local isBlood = 0;

        if (obj.sq_GetSkillLevel(SKILL_BLOODOATH) > 0)
            isBlood = 1;

		obj.sq_StartWrite();
		obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
		obj.sq_WriteDword(1);
		obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
		obj.sq_WriteDword(distance);	// attackBonusRate
		obj.sq_WriteDword(attackSumTime);	// attackBonusRate
		obj.sq_WriteDword(attackTime);	// attackBonusRate
		obj.sq_WriteDword(absortBlood);	// attackBonusRate
		obj.sq_WriteDword(isBlood);	// attackBonusRate
		obj.sq_WriteDword(2000);	// attackBonusRate

		obj.sq_SendCreatePassiveObjectPacket(24364, 0, 44, 0, 66);

	}
	return true;
}
