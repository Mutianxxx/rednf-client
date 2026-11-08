function checkExecutableSkill_inhang(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_INHANG);

	if (isUse) {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_INHANG , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}

function checkCommandEnable_inhang(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	

	if (state == STATE_STAND)
		return true;
		
	if(state == STATE_ATTACK)
	{
		return true;
	}

	return true;
}

function onSetState_INHANG(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	obj.sq_StopMove();

    local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_INHANG_READY);

        obj.sq_SetCurrentAttackInfo(ATTACKINFO_INHANG_NEW);
	obj.sq_PlaySound("R_MW_VACUUM");
        obj.getVar("dama").clear_obj_vector();

        local damage = obj.sq_GetBonusRateWithPassive(SKILL_INHANG , STATE_INHANG, 0, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);				

    }else if (state == 1)
    {
        obj.setTimeEvent(0,obj.sq_GetIntData(SKILL_INHANG, 0),0,true);		
        obj.setTimeEvent(1,obj.sq_GetIntData(SKILL_INHANG, 1),0,false);		
        obj.setTimeEvent(2,20,0,false);		
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_INHANG_LOOP);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_INHANG_NEW);

        local damage = obj.sq_GetBonusRateWithPassive(SKILL_INHANG , STATE_INHANG, 0, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);				

		local bloodCutObjCount = obj.getMyPassiveObjectCount(24357);			
		for (local i = 0; i < bloodCutObjCount ; ++i) 
		{ 
				local bloodCutObj = obj.getMyPassiveObject(24357,i);
                if (bloodCutObj && bloodCutObj.getVar("id").get_vector(0) == 25)
                {
                    obj.getVar("dama").push_obj_vector( bloodCutObj );
                    return true;
                }
		}

        local currentAttackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackeHitStunTime(currentAttackInfo, 0);

    }else if (state == 2)
    {

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_INHANG_END);
    }

	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);

}


function onEndCurrentAni_INHANG(obj)
{
    local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_INHANG , STATE_PRIORITY_USER, false);
    }else if (state == 2)
    {
		obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
    }
}


function onTimeEvent_INHANG(obj, timeEventIndex, timeEventCount)
{

    local state = obj.getVar("state").get_vector(0);

    if (timeEventIndex == 0)
    {
        obj.resetHitObjectList();

    }else if (timeEventIndex == 1)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_INHANG , STATE_PRIORITY_USER, false);

    }else if (timeEventIndex == 2)
    {
        if (state == 1)
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
                    local x_move = obj.sq_GetIntData(SKILL_INHANG, 2);
                    local y_move = obj.sq_GetIntData(SKILL_INHANG, 3);
                    if (objX < damaX) x_move = - x_move;
                    if (objY < damaY) y_move = - y_move;
                    damager.setCurrentPos(damaX + x_move,damaY + y_move,damaZ);


            }


        }
    }
}

function onProc_INHANG(obj)
{


    if (false)
    {
        local pAni = obj.sq_GetCurrentAni();


    }

}





function onAttack_INHANG(obj, damager, boundingBox, isStuck)
{
	if (!obj || !damager) return;

    if (!sq_IsFixture(damager) )
    {
        obj.getVar("dama").push_obj_vector(damager);
//
//		local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 
//        SKILL_INHANG, true, "character/atmage/inhang/ap_inhang.nut", false);


    }

}

