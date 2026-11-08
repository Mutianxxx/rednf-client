function checkExecutableSkill_inwind(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_INWIND);
	if (isUseSkill) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);	// subState????
		obj.sq_AddSetStatePacket(STATE_INWIND, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_inwind(obj)
{
    return true;
}




function onSetState_INWIND(obj, state, datas, isResetTimer)
{
	if (!obj) return;

	obj.sq_StopMove();
	
	
	local subState = obj.sq_GetVectorData(datas, 0);	// subState
	obj.sq_SetSkillSubState(obj, subState);
	

	if (subState == 0)
	{
        obj.getVar("dama").clear_obj_vector();

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_INWIND_NEW_READY);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_INWIND_NEW_READY);
        obj.setTimeEvent(0,20,0,false);		

	}
	else if (subState == 1)
	{
		sq_flashScreen(obj,0,80,160,150, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        obj.sq_SetShake(obj, 5, 240);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_INWIND_NEW_ATTACK);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_INWIND_NEW_ATTACK);	
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_INWIND , STATE_INWIND, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);
}




function onTimeEvent_INWIND(obj, timeEventIndex, timeEventCount)
{
    if (obj.sq_GetSkillSubState(obj) == 0)
    {
        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();

        for(local i=0;i<objectsSize;++i)
        {

                local damager = var.get_obj_vector(i);
                local objX = obj.getXPos();
                local objY = obj.getYPos();
                local damaX = damager.getXPos();
                local damaY = damager.getYPos();
                local damaZ = damager.getZPos();
                local x_move = obj.sq_GetIntData(SKILL_INWIND, 0);
                local y_move = obj.sq_GetIntData(SKILL_INWIND, 1);

                if (objX < damaX) x_move = - x_move;
                if (objY < damaY) y_move = - y_move;
                if(damaZ > 0)
                {
                    damaZ = damaZ - 5;
                }else{
                    damaZ = 0;
                }
                damager.setCurrentPos(damaX + x_move,damaY + y_move,damaZ);

        }
    }

}



function onAttack_INWIND(obj, damager, boundingBox, isStuck)
{
    if (obj.sq_GetSkillSubState(obj) == 0)
    {
        if(damager.getState() != STATE_HOLD && !sq_IsFixture(damager) )
        {
            obj.getVar("dama").push_obj_vector(damager);
        }
    }

}
function onEndCurrentAni_INWIND(obj)
{
	if (!obj) return;
	
	
	if (obj.sq_GetSkillSubState(obj) == 0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_INWIND, STATE_PRIORITY_USER, true);
	}
	else if (obj.sq_GetSkillSubState(obj) == 1) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}
