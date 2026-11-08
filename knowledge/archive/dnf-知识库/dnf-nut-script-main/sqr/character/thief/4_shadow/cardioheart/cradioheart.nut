//state 1  shake 5 130

function checkExecutableSkill_cardioheart(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_CARDIOHEART);
	if (isUseSkill) 
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_CARDIOHEART, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_cardioheart(obj)
{

	return true;
}

function createHitPassiveCradioHeartBlood_a(obj,damager)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/cardioclasis/blood_a_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createHitPassiveCradioHeartBlood_b(obj,damager)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/cardioclasis/blood_b_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createHitPassiveCradioHeartBlood_c(obj,damager)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/cardioclasis/blood_c_01start.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function onAttack_CARDIOHEART(obj, damager, boundingBox, isStuck)
{
    
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
		if(!sq_IsFixture(damager)) 
        {
            createHitPassiveCradioHeartBlood_a(obj,damager);
            if (isEnemyBack(obj,damager))
            {
                obj.getVar("isLast").clear_vector();
                obj.getVar("isLast").push_vector(1);

            }


            obj.sq_SetShake(obj, 3, 100);

            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_CARDIOHEART, false, "character/thief/4_shadow/cardioheart/ap_cradioheart.nut", true);				 

            local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), obj.sq_GetIntData(SKILL_CARDIOHEART, 0) );
    // obj.sq_GetIntData(SKILL_CARDIOHEART, 0)
            masterAppendage.getVar("chrPos").clear_vector();
            masterAppendage.getVar("chrPos").push_vector(posX);
            masterAppendage.getVar("chrPos").push_vector(obj.getYPos() - 1 );

            masterAppendage.getVar("movT").clear_vector();
            masterAppendage.getVar("movT").push_vector( obj.sq_GetIntData(SKILL_CARDIOHEART, 1) );

            if(masterAppendage) 
            {
                sq_HoldAndDelayDie(damager, obj, true, false, false, 0, 0, ENUM_DIRECTION_NEUTRAL , masterAppendage);

                local holdTime = sq_GetLevelData(obj, SKILL_CARDIOHEART, 2, sq_GetSkillLevel(obj, SKILL_CARDIOHEART) );

                masterAppendage.sq_SetValidTime( holdTime );
            }
        }
    }else if (state == 1)
    {
		if(!sq_IsFixture(damager)) 
        {
            createHitPassiveCradioHeartBlood_b(obj,damager);
            createHitPassiveCradioHeartBlood_c(obj,damager);
        }
    }

}

function onSetState_CARDIOHEART(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_CRADIOHEART_PUSH);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_CRADIOHEART_PUSH);

        obj.getVar("dama").clear_obj_vector();
    
        obj.getVar("isLast").clear_vector();
        obj.getVar("isLast").push_vector(0);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_CARDIOHEART , STATE_CARDIOHEART, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

    }else if (state == 1)
    {
        obj.sq_SetShake(obj, 5, 130);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_CRADIOHEART_PULL);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_CRADIOHEART_PULL);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_CARDIOHEART , STATE_CARDIOHEART, 1, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

    }
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

}

function onEndCurrentAni_CARDIOHEART(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        if (obj.getVar("isLast").get_vector(0) == 1)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            obj.sq_AddSetStatePacket(STATE_CARDIOHEART, STATE_PRIORITY_USER, true);


        }else{
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
        }
    }else if (state == 1)
    {
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_CARDIOHEART , STATE_CARDIOHEART, 1, 1.0);
        sendOneHitAllMonsterShaowAreaObj(obj,damage);
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}