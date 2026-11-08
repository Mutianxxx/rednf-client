function checkExecutableSkill_null50(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_NULL50);
	if (isUseSkill) {
		obj.sq_AddSetStatePacket(STATE_NULL50, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}



function checkCommandEnable_null50(obj)
{
	if(!obj)
		return false;

	return true;
}

function onSetState_NULL50(obj, state, datas, isResetTimer)
{
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);

	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_NULL50);

	local castTime = sq_GetCastTime(obj, SKILL_NULL50, sq_GetSkillLevel(obj, SKILL_NULL50)  );
	local animation = sq_GetCurrentAnimation(obj);
	local startTime = animation.getDelaySum(false);
	local speedRate = startTime.tofloat() / castTime.tofloat();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
		SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);

	sq_StartDrawCastGauge(obj, castTime, true);


}



function onEndCurrentAni_NULL50(obj)
{
    if (!obj.isMyControlObject())
        return false;
	obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
}


function onKeyFrameFlag_NULL50(obj,flagIndex)
{
    if (!obj.isMyControlObject())
        return false;
    if (flagIndex == 1)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);

            sq_BinaryStartWrite();
            sq_BinaryWriteDword(0);	
            obj.sq_SendCreatePassiveObjectPacket(24339, 0, obj.sq_GetIntData(SKILL_NULL50, 0),1, 0);

            local skill_level = sq_GetSkillLevel(obj, SKILL_NULL50);

            if (skill_level >= 3)
            {
                local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_NULL50, false,
                 "character/atmage/null50/ap_null50.nut", true);

                local change_time = sq_GetLevelData(obj, SKILL_NULL50, 6, sq_GetSkillLevel(obj, SKILL_NULL50) );
                appendage.sq_SetValidTime(change_time);



                appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_NULL50, skill_level);
                CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_NULL50, true);






                local Stone = sq_GetLevelData(obj, SKILL_NULL50, 4, sq_GetSkillLevel(obj, SKILL_NULL50) );
                setBreakSenseEnegry(obj,getBreakSenseEnegry(obj) + Stone * 100 );
                local magicAtk = sq_GetLevelData(obj, SKILL_NULL50, 5, sq_GetSkillLevel(obj, SKILL_NULL50) );






                local change_appendage = appendage.sq_getChangeStatus("Horror");

                if(!change_appendage)
                {
                    change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, 
                    CHANGE_STATUS_TYPE_MAGICAL_ATTACK, 
                    false, magicAtk, APID_COMMON);

                }

                if (change_appendage){
                    change_appendage.clearParameter();
                    change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, magicAtk.tofloat());
                }
            }

//            obj.sq_SendCreatePassiveObjectPacket(24341, 0, 120, 0, 0);

        }
    }
}


function createNull50Ground1(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athorror/eye/07_ground/ground_01/athorror_ground_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createNull50Ground2(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athorror/eye/07_ground/ground_02/athorror_ground_02.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}




function createNull50Ground3(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athorror/eye/07_ground/ground_03/athorror_ground_03.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createNull50Ground4(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athorror/eye/07_ground/ground_04_finish/athorror_ground_04_finish.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createNull50Ground5(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athorror/eye/07_ground/ground_04_finish01/athorror_ground_04_finish01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createNull50Hit1(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athorror/03_attack01/hit_01/athorror_hit_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createNull50Hit2(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athorror/04_attack02/hit_02/athorror_hit_02.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createNull50Hit3(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athorror/05_attack03/hit_03/athorror_hit_03.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createNull50FinishFront(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athorror/06_finish/front_finish/athorror_front_finish.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createNull50Hit4(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athorror/06_finish/attack_04_finish01/athorror_attack_04_finish01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createNull50Hit5(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athorror/06_finish/hit_04/athorror_hit_04.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createNull50SummonEffect(obj)
{

	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/athorror/01_summon/athorror_summon.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createNull50SummonEffectGround(obj)
{

	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/athorror/01_summon/ground/athorror_summon_ground.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() - 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}
