//flag1 flash 0 0 160 204 255 255 255 bottom
//shake 7 240
//flag2 flash 0 0 160 204 255 255 255 bottom
//shake 7 240
//CUSTOM_ANI_SHAOWSLASH_FRIST <- 142
//CUSTOM_ANI_SHAOWSLASH_SECOND_A <- 143
//CUSTOM_ANI_SHAOWSLASH_SECOND_AA <- 144
//CUSTOM_ANI_SHAOWSLASH_FINISH_A <- 145
//CUSTOM_ANI_SHAOWSLASH_FINISH_B <- 146
//CUSTOM_ANI_SHAOWSLASH_FINISH_C <- 147

//ATTACKINFO_SHAOWSLASH_FRIST <- 56
//ATTACKINFO_SHAOWSLASH_SECOND <- 57
//ATTACKINFO_SHAOWSLASH_FINISH <- 58

function checkExecutableSkill_shaowslash(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_SHAOWSLASH);
	if (isUseSkill) 
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_SHAOWSLASH, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_shaowslash(obj)  
{

	return true;
}




function onSetState_SHAOWSLASH(obj, state, datas, isResetTimer)
{	
    if (!obj) return;
    local state = obj.getVar("state").get_vector(0);
    obj.sq_StopMove();
    local damage = obj.sq_GetBonusRateWithPassive(SKILL_SHAOWSLASH , STATE_SHAOWSLASH, 0, 1.0);

    if (state == 0)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_SHAOWSLASH_FRIST);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_SHAOWSLASH_FRIST );
        obj.sq_SetCurrentAttackBonusRate(damage);

    }else if (state == 1)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_SHAOWSLASH_SECOND_A);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_SHAOWSLASH_SECOND );
        obj.sq_SetCurrentAttackBonusRate(damage);


    }else if (state == 2)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_SHAOWSLASH_SECOND_AA);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_SHAOWSLASH_SECOND);
        obj.sq_SetCurrentAttackBonusRate(damage);

    }else if (state == 3)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_SHAOWSLASH_FINISH_A);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_SHAOWSLASH_SECOND);
        obj.sq_SetCurrentAttackBonusRate(damage);

    }else if (state == 4)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_SHAOWSLASH_FINISH_B);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_SHAOWSLASH_SECOND);
        if (obj.getVar("isBack").get_vector(0) == 1)
        {
		damage = obj.sq_GetBonusRateWithPassive(SKILL_SHAOWSLASH , STATE_SHAOWSLASH, 3, 1.0);
		sendOneHitAllMonsterShaowAreaObj(obj,damage);
        }
        else
        {
        	damage = obj.sq_GetBonusRateWithPassive(SKILL_SHAOWSLASH , STATE_SHAOWSLASH, 2, 1.0);
        }
        obj.sq_SetCurrentAttackBonusRate(damage);
        local backDistance = 60+sq_Abs(obj.getVar("isBack").get_vector(1) - obj.getXPos());
        local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),backDistance.tointeger());
        obj.sq_SetfindNearLinearMovablePos(posX ,obj.getYPos(),obj.getXPos(), obj.getYPos(), 10);
        obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
    }else if (state == 5)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_SHAOWSLASH_FINISH_C);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_SHAOWSLASH_SECOND);
        if (obj.getVar("isBack").get_vector(0) == 1)
        {
		damage = obj.sq_GetBonusRateWithPassive(SKILL_SHAOWSLASH , STATE_SHAOWSLASH, 3, 1.0);
        }
        else
        {
        	damage = obj.sq_GetBonusRateWithPassive(SKILL_SHAOWSLASH , STATE_SHAOWSLASH, 2, 1.0);
        }
        obj.sq_SetCurrentAttackBonusRate(damage);
    }
    obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onEndCurrentAni_SHAOWSLASH(obj)
{
    if (!obj) return;
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_SHAOWSLASH, STATE_PRIORITY_USER, true);
    }else if (state == 1)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_SHAOWSLASH, STATE_PRIORITY_USER, true);
    }else if (state == 2)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(3);
		obj.sq_AddSetStatePacket(STATE_SHAOWSLASH, STATE_PRIORITY_USER, true);
    }else if (state == 3)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(4);
		obj.sq_AddSetStatePacket(STATE_SHAOWSLASH, STATE_PRIORITY_USER, true);
    }else if (state == 4)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(5);
		obj.sq_AddSetStatePacket(STATE_SHAOWSLASH, STATE_PRIORITY_USER, true);
    }else if (state == 5)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }

}

function onAttack_SHAOWSLASH(obj, damager, boundingBox, isStuck)
{
    if (!obj) return;
    if (!damager) return;
    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {
        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODSHAOWSLASH, false, 
        "character/thief/4_shadow/shaowslash/ap_shaowslash.nut", true);				 

        createHitEffectShaowSlash_a(obj,damager);
        if (isEnemyBack(obj,damager) )
        {
            obj.getVar("isBack").clear_vector();
            obj.getVar("isBack").push_vector(1);
            obj.getVar("isBack").push_vector(damager.getXPos());
        }
        else
        {
            obj.getVar("isBack").clear_vector();
            obj.getVar("isBack").push_vector(0);
            obj.getVar("isBack").push_vector(damager.getXPos());
        }

    }
    else if (state == 2)
    {
        createHitEffectShaowSlash_a(obj,damager);
    }
    else if (state == 3)
    {
        createHitEffectShaowSlash_b(obj,damager);

    }
    else if (state == 4||state == 5)
    {
        if(damager)
        {
            CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/thief/4_shadow/shaowslash/ap_shaowslash.nut");		
        }

        if (obj.getVar("isBack").get_vector(0) == 1)
        {
        	createHitEffectShaowSlash_c(obj,damager);
        	createHitEffectShaowSlash_d(obj,damager);
		local monObj = sq_GetCNRDObjectToActiveObject(damager);
		monObj.setDirection(obj.getDirection());
        }
        else{
        	createHitEffectShaowSlash_b(obj,damager);
        }
    }
}

function createHitEffectShaowSlash_a(obj,damager)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/finaldestruction/finaldestruction_blood2_start.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createHitEffectShaowSlash_b(obj,damager)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/finaldestruction/finialdestruction_hit_dodge.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createHitEffectShaowSlash_c(obj,damager)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/finaldestruction/finaldestruction_hit2_normal.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createHitEffectShaowSlash_d(obj,damager)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/finaldestruction/finaldestruction_backhit_front_normal.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createLineShaowSlash(obj)
{
	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/finaldestruction/finaldestruction_backhit_line_normal.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}