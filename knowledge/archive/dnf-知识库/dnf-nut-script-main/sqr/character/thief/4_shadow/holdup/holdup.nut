//flag1 shake 2 100

function checkExecutableSkill_holdup(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_HOLDUP);
	if (isUseSkill) 
    {
		obj.sq_AddSetStatePacket(STATE_HOLDUP, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_holdup(obj)  
{

	return true;
}

function onKeyFrameFlag_HOLDUP(obj,flagIndex)
{
	if(!obj)
		return false;

    if (flagIndex == 1)
    {
        obj.sq_SetShake(obj, 2, 100);
    }
}

function onAttack_HOLDUP(obj, damager, boundingBox, isStuck)
{

        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_HOLDUP, false, "character/thief/4_shadow/holdup/ap_holdup.nut", true);				 

        if(masterAppendage) 
        {
//            sq_HoldAndDelayDie(damager, obj, true, false, false, 0, 0, ENUM_DIRECTION_NEUTRAL , masterAppendage);

            local holdTime = sq_GetLevelData(obj, SKILL_HOLDUP, 1, sq_GetSkillLevel(obj, SKILL_HOLDUP) );

            masterAppendage.sq_SetValidTime( holdTime );
        }
        if (isEnemyBack(obj,damager))
        {
            obj.getVar("isBack").clear_vector();
            obj.getVar("isBack").push_vector(1);
        }
}

function onSetState_HOLDUP(obj, state, datas, isResetTimer)
{	
	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_HOLDUP );
	obj.sq_SetCurrentAttackInfo(ATTACKINFO_HOLDUP );
	local damage = obj.sq_GetBonusRateWithPassive(SKILL_HOLDUP , STATE_HOLDUP , 0, 1.0);
	obj.sq_SetCurrentAttackBonusRate(damage);				
	obj.getVar("isBack").clear_vector();
	obj.getVar("isBack").push_vector(0);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onEndCurrentAni_HOLDUP(obj)
{
    if (obj.getVar("isBack").get_vector(0) == 1)
    {
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_HOLDUP , STATE_HOLDUP , 0, 1.0);
        sendOneHitAllMonsterShaowAreaObj(obj,damage);
    }
    obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}