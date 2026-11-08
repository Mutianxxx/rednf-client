//FLAG 1 flash 10 50 10 76 255 0 255 bottom
//Flag 1 10 230
//flag offest finish 


function checkExecutableSkill_painfugraden(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_PAINFUGRADEN);
	if (isUseSkill) 
	{
		obj.sq_AddSetStatePacket(STATE_PAINFUGRADEN, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_painfugraden(obj)
{
	return true;
}

function onKeyFrameFlag_PAINFUGRADEN(obj,flagIndex)
{
	if (!obj) return;
	if (flagIndex == 1 && obj.getVar("flag").get_vector(0) == 0 )
	{
		obj.getVar("flag").set_vector(0,1); 
		createFrontFinishSuccessPainfuGraden(obj);
	}
}

function createBackSuccessPainfuGraden(obj)
{
	if (!obj) return;
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/painfulgarden/backsuccess_00.ani");
	if (!ani) return;
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() - 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFrontSuccessPainfuGraden(obj)
{
	if (!obj) return;
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/painfulgarden/frontsuccess_00.ani");
	if (!ani) return;
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFrontFinishSuccessPainfuGraden(obj)
{
	if (!obj) return;
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/painfulgarden/successfinish_26.ani");
	if (ani){
		local pooledObj = sq_CreatePooledObject(ani,true);
		pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
		pooledObj.setCurrentDirection(obj.getDirection());
		sq_AddObject(obj,pooledObj,2,false);	
	}
}

function onSetState_PAINFUGRADEN(obj, state, datas, isResetTimer)
{
	if (!obj) return;
//    local damage = obj.sq_GetBonusRateWithPassive(SKILL_PAINFUGRADEN , STATE_PAINFUGRADEN, 0, 1.0);
	obj.sq_StopMove();
    setBobyNumber(obj,getBobyNumber(obj) + 1 );
    if (!isDollState(obj) )//???O?@????A
    {
        obj.sq_SetCurrentAnimation( CUSTOM_PAINFUGRADE_BODY );
    }else{
        local ani = obj.getVar().GetAnimationMap("painfugrraden", "passiveobject/zrr_skill/newmage/animation/dot/mad_painfulgardenstart.ani"); 
        if (ani)
		obj.setCurrentAnimation(ani);
    }
    obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED , SPEED_TYPE_CAST_SPEED , SPEED_VALUE_DEFAULT , SPEED_VALUE_DEFAULT , 1.0 , 1.0);
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
    createFrontSuccessPainfuGraden(obj);
    createBackSuccessPainfuGraden(obj);
    local level = sq_GetSkillLevel(obj, SKILL_PAINFUGRADEN);
    local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_PAINFUGRADEN , STATE_PAINFUGRADEN, 0, 1.0);//?h?q????
    //
    local attackBonusRate2 = obj.sq_GetBonusRateWithPassive(SKILL_PAINFUGRADEN , STATE_PAINFUGRADEN, 2, 1.0);//?z??????
    local hitCount = sq_GetLevelData(obj, SKILL_PAINFUGRADEN, 1,  level);
    //???????? 9
	
	local bloodAtk = obj.sq_GetPowerWithPassive(SKILL_PAINFUGRADEN, -1, 4, -1, 1.0);
	
	local bloodleve = sq_GetLevelData(obj, SKILL_PAINFUGRADEN, 3, level);
	local bloodtime = sq_GetLevelData(obj, SKILL_PAINFUGRADEN, 5, level);
		
	local holdProc = sq_GetLevelData(obj, SKILL_PAINFUGRADEN, 8, level);
	local holdleve = sq_GetLevelData(obj, SKILL_PAINFUGRADEN, 7, level);
	local holdtime = sq_GetLevelData(obj, SKILL_PAINFUGRADEN, 6, level);
	
	sq_BinaryStartWrite();
	sq_BinaryWriteDword(attackBonusRate);	// attackBonusRate
	sq_BinaryWriteDword(10);
	sq_BinaryWriteDword(hitCount);
	sq_BinaryWriteDword(attackBonusRate2);
	sq_BinaryWriteDword(bloodAtk);
	sq_BinaryWriteDword(bloodleve);
	sq_BinaryWriteDword(bloodtime);
	sq_BinaryWriteDword(holdProc);
	sq_BinaryWriteDword(holdleve);
	sq_BinaryWriteDword(holdtime);
	obj.sq_SendCreatePassiveObjectPacket(24366, 0, 0, -1, 0);


}

function onEndCurrentAni_PAINFUGRADEN(obj)
{
    obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}
