function checkExecutableSkill_secondwindhit(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SECONDWIDHIT);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_SECONDWIDHIT , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}




function checkCommandEnable_secondwindhit(obj)
{
	if (!obj) return false;
	return true;
}

function onSetState_SECONDWINDHIT(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();

        if(obj.isMyControlObject())
        {
            local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SECONDWIDHIT, STATE_SECONDWIDHIT, 0, 1.0);
            local level = sq_GetSkillLevel(obj, SKILL_SECONDWIDHIT);
            local attacktimes = sq_GetLevelData(obj, SKILL_SECONDWIDHIT, 1, level);
            local oncetime = 550/attacktimes;
            local size = sq_GetIntData(obj,SKILL_SECONDWIDHIT, 3);
            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
            obj.sq_WriteDword(19);	// attackBonusRate
            obj.sq_WriteDword(600);	// attackBonusRate
            obj.sq_WriteDword(600);	// attackBonusRate
            obj.sq_WriteDword(oncetime);	// attackBonusRate
            obj.sq_WriteDword(size);	// attackBonusRate
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, 50, -50, 0);
        }

    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);


	obj.sq_SetCurrentAnimation(CUSTOM_ANI_SECONDWINDHIT_BODY);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onEndCurrentAni_SECONDWINDHIT(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}


function onKeyFrameFlag_SECONDWINDHIT(obj,flagIndex)
{
	if(!obj)
		return false;
    if (obj.getVar("flag").get_vector(0) == 0)
    {
        if(obj.isMyControlObject())
        {
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);
            local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SECONDWIDHIT, STATE_SECONDWIDHIT, 0, 1.0);
            local level = sq_GetSkillLevel(obj, SKILL_SECONDWIDHIT);
            local attacktimes = sq_GetLevelData(obj, SKILL_SECONDWIDHIT, 1, level);
            local oncetime = 550/attacktimes;
            local size = sq_GetIntData(obj,SKILL_SECONDWIDHIT, 3);
            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
            obj.sq_WriteDword(20);	// attackBonusRate
            obj.sq_WriteDword(600);	// attackBonusRate
            obj.sq_WriteDword(600);	// attackBonusRate
            obj.sq_WriteDword(oncetime);	// attackBonusRate
            obj.sq_WriteDword(size);	// attackBonusRate
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, 50, 50, 0);
        }
        return true;
    }
}

function secondWindHit_PassiveobjectAppendByCharacter(obj,damager)
{
		if(damager.getState() != STATE_HOLD 
		     && sq_IsGrabable(obj,damager) 
		     && sq_IsHoldable(obj,damager) 
		     && !sq_IsFixture(damager) )
        {
            if (!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/secondwindhit/ap_secondwindhit.nut"))
            {
                local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_SECONDWIDHIT, true,
                 "character/atmage/secondwindhit/ap_secondwindhit.nut", false);
            }

        }

}

function createSecondWindHit_PassiveobjectEffect_A01(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athurricane_new/hurricane_missile_a01.ani");
    local size = obj.getVar("len").get_vector(3);
    local sizeRate = size.tofloat() / 100.0;
    ani.setImageRateFromOriginal(sizeRate, sizeRate);
    ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createSecondWindHit_PassiveobjectEffect_A02(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athurricane_new/hurricane_missile_a02.ani");
    local size = obj.getVar("len").get_vector(3);
    local sizeRate = size.tofloat() / 100.0;
    ani.setImageRateFromOriginal(sizeRate, sizeRate);
    ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createSecondWindHit_PassiveobjectEffect_B01(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athurricane_new/hurricane_missile_b01.ani");
    local size = obj.getVar("len").get_vector(3);
    local sizeRate = size.tofloat() / 100.0;
    ani.setImageRateFromOriginal(sizeRate, sizeRate);
    ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createSecondWindHit_PassiveobjectEffect_B02(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athurricane_new/hurricane_missile_b02.ani");
    local size = obj.getVar("len").get_vector(3);
    local sizeRate = size.tofloat() / 100.0;
    ani.setImageRateFromOriginal(sizeRate, sizeRate);
    ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

