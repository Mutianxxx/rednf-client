function checkExecutableSkill_cutneck(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_CUTNECK);
	if (isUseSkill) 
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_CUTNECK, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_cutneck(obj)  
{

	return true;
}


function createHitPassiveCutNeckBlood_a(obj,damager)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/cuttingneck/b_b_eff_a.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createHitPassiveCutNeckBlood_b(obj,damager)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/cuttingneck/c_1.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos());
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}
function onAttack_CUTNECK(obj, damager, boundingBox, isStuck)
{
    
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
		if(!sq_IsFixture(damager)) 
        {
            createHitPassiveCutNeckBlood_a(obj,damager);
            if (isEnemyBack(obj,damager))
            {
                obj.getVar("isLast").clear_vector();
                obj.getVar("isLast").push_vector(1);

            }
            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_CUTNECK, false, 
            "character/thief/4_shadow/cutneck/ap_cutneck.nut", true);				 
        }
    }else if (state == 1)
    {
		if(!sq_IsFixture(damager)) 
        {
            createHitPassiveCutNeckBlood_b(obj,damager);
        }
    }
}

function onSetState_CUTNECK(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_CUTNECK_DOWN);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_CUTNECK_DOWN);
        obj.getVar("isLast").clear_vector();
        obj.getVar("isLast").push_vector(0);

        obj.getVar("zpos").clear_vector();
        obj.getVar("zpos").push_vector( obj.getZPos() );

        local damage = obj.sq_GetBonusRateWithPassive(SKILL_CUTNECK , STATE_CUTNECK, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

    }else if (state == 1)
    {
		sq_setCurrentAxisPos(obj, 2, 0);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_CUTNECK_CUT);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_CUTNECK_CUT);

        local damage = obj.sq_GetBonusRateWithPassive(SKILL_CUTNECK , STATE_CUTNECK, 1, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				
    }
    obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onProc_CUTNECK(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        local startZ = obj.getVar("zpos").get_vector(0);
        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);
        local delayT = pAni.getDelaySum(false);

		local v = sq_GetAccel(startZ, 0, currentT, delayT, true);
		sq_setCurrentAxisPos(obj, 2, v);


    }
}


function onEndCurrentAni_CUTNECK(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        if (obj.getVar("isLast").get_vector(0) == 1)
        {
             obj.getVar("state").clear_vector();
             obj.getVar("state").push_vector(1);
             obj.sq_AddSetStatePacket(STATE_CUTNECK, STATE_PRIORITY_USER, true);
        }else{
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
        }
    }else if (state == 1)
    {
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_CUTNECK , STATE_CUTNECK, 1, 1.0);
        sendOneHitAllMonsterShaowAreaObj(obj,damage);
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}