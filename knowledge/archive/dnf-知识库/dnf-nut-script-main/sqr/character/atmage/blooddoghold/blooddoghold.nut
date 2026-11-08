blooddoghold_zheng <- 0
is_move <- 0

function checkExecutableSkill_blooddoghold(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_BLOODDOGHOLD);
	if (isUseSkill) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);	// subState????
		obj.sq_AddSetStatePacket(STATE_BLOODDOGHOLD, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}



// ????????? ???? ?????? ?????? ???????. true?? ??????? ??? ???????? ?????? ????. (??????? state??  ??????? ó??????.)
function checkCommandEnable_blooddoghold(obj)
{
	if(!obj)
		return false;
	local state = obj.sq_GetState();
		
	if(state == STATE_ATTACK)
	{
		return true;
	}
    if (state == STATE_STAND)
    {
        return true;
    }
		
	return false;
}


function onEndState_BLOODDOGHOLD(obj, state)
{
	// ??????? ???? ??? ??? ?????? ????? ?????? ????
	sq_EndDrawCastGauge(obj);
}


function onSetState_BLOODDOGHOLD(obj, state, datas, isResetTimer)
{
	if (!obj) return;

	obj.sq_StopMove();
	
	
	local subState = obj.sq_GetVectorData(datas, 0);	// subState
	obj.sq_SetSkillSubState(obj, subState);
	
	if (subState == 0)
	{

        obj.getVar("dama").clear_obj_vector();

        obj.sq_SendCreatePassiveObjectPacket(12335, 0, 0, 1, 0);
        blooddoghold_zheng = 0;
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODDOGHOLD);

        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODDOGHOLD , STATE_BLOODDOGHOLD, 0, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);				

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODDOGHOLD);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	}
	else if (subState == 1)
	{
        is_move = 0;
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODDOGHOLD);

        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODDOGHOLD , STATE_BLOODDOGHOLD, 1, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);				

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODDOGHOLD_END);
	}
}



// prepareDraw
function prepareDraw_BLOODDOGHOLD(obj)
{
	if (!obj) return;
}



function onProc_BLOODDOGHOLD(obj)
{
    
    local pAni = obj.sq_GetCurrentAni();

    local NowFrame = obj.sq_GetCurrentFrameIndex(pAni);

    local objX = obj.getXPos();
    local objY = obj.getYPos();
    local objZ = obj.getZPos();

    local var = obj.getVar("dama");  		
    local objectsSize = var.get_obj_vector_size();

    local dvalue = -1;
    if (obj.getDirection() == ENUM_DIRECTION_RIGHT) dvalue = 1;

    for(local i=0;i<objectsSize;++i)
    {
        if (obj.sq_GetSkillSubState(obj) == 0) 
        {

            local damager = var.get_obj_vector(i);

            if (NowFrame % 4 == 0)
            {
                damager.setCurrentPos( objX + 120 * dvalue,objY + 1,10);
            }else{
                damager.setCurrentPos( objX + 200 * dvalue,objY + 1,10);
            }
        }else{
            if (NowFrame == 0 || NowFrame == 1) damager.setCurrentPos( objX - 58 * dvalue,objY + 1,objZ + 299);
            if (NowFrame == 2) damager.setCurrentPos( objX + 158 * dvalue,objY + 1,objZ + 193);
            if (NowFrame >= 3 && NowFrame <= 8) damager.setCurrentPos( objX + 253 * dvalue,objY + 1,objZ + 56);

        }
    }

    if (blooddoghold_zheng == NowFrame) return ;

    if (obj.sq_GetSkillSubState(obj) == 0) 
    {
        blooddoghold_zheng = NowFrame;
        if (blooddoghold_zheng % 2 == 0) obj.resetHitObjectList();
    } else {
        if (NowFrame >= 9 && is_move == 0)
        {
        is_move = 1;
             if (obj.getDirection() == ENUM_DIRECTION_LEFT)
             {
                 obj.sq_SetfindNearLinearMovablePos(obj.getXPos() - 240,obj.getYPos(),obj.getXPos(),obj.getYPos(),10);
             } else {
                 obj.sq_SetfindNearLinearMovablePos(obj.getXPos() + 240,obj.getYPos(),obj.getXPos(),obj.getYPos(),10);
             }
        }
     }
}



// onEndCurrentAni
function onEndCurrentAni_BLOODDOGHOLD(obj)
{
	if (!obj) return;
	
	
	if (obj.sq_GetSkillSubState(obj) == 0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);	// subState????
		obj.sq_AddSetStatePacket(STATE_BLOODDOGHOLD, STATE_PRIORITY_USER, true);
	}
	else if (obj.sq_GetSkillSubState(obj) == 1) {
        obj.sq_SendCreatePassiveObjectPacket(12036, 0, 0, 1, 0);
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onAttack_BLOODDOGHOLD(obj, damager, boundingBox, isStuck)
{
    local objX = obj.getXPos();
    local objY = obj.getYPos();

    obj.sq_PlaySound("SKELETON_DIE_01");

    obj.sq_SetShake(obj, 5, 100);

    if (obj.sq_GetSkillSubState(obj) == 0) 
    {

        obj.getVar("dama").push_obj_vector(damager);

    }

}