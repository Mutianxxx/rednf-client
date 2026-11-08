blood45_move <- 0
blood45_moveY <- 0
blood45_moveMax <- 0
mmmmm <- 0

function checkExecutableSkill_blood45(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_BLOOD45);
	if (isUseSkill) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);	// subState??
		obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}



// ????????? ???? ?????? ?????? ???????. true?? ??????? ??? ???????? ?????? ????. (??????? state??  ??????? ó??????.)
function checkCommandEnable_blood45(obj)
{
	if(!obj)
		return false;
    if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_BLOOD45, 3))) 
        return false;

	return true;

	return false;
}


function onEndState_BLOOD45(obj, state)
{
	// ??????? ???? ??? ??? ?????? ????? ?????? ????
	sq_EndDrawCastGauge(obj);
}


function onSetState_BLOOD45(obj, state, datas, isResetTimer)
{
	if (!obj) return;

	obj.sq_StopMove();
	

	local subState = obj.sq_GetVectorData(datas, 0);	// subState
	obj.sq_SetSkillSubState(obj, subState);
	
	if (subState == 0)
	{

        setBloodValue(obj,-obj.sq_GetIntData(SKILL_BLOOD45, 3));

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOOD45_READY);

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
	}
	else if (subState == 1)
	{

        local time = 900;
        local count = 40;
        blood45_move = 0;
        blood45_moveY = 0;

        obj.getVar("dama").clear_obj_vector();



        blood45_moveMax = obj.sq_GetIntData(SKILL_BLOOD45, 0);

    	obj.sq_timer_.setParameter(time / count, count - 1);
        obj.sq_timer_.resetInstant(0);

		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOOD45_ATTACK);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOOD45_ATTACK);


		if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && leftPress) blood45_moveMax = obj.sq_GetIntData(SKILL_BLOOD45, 2);
		if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && rightPress) blood45_moveMax = obj.sq_GetIntData(SKILL_BLOOD45, 2);



    	obj.getVar("check").clear_vector();
		obj.getVar("check").push_vector(blood45_moveMax);


        sq_flashScreen(obj,0,0,1000,150, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	}
    else if (subState == 2)
    {

    	obj.sq_SetCurrentAnimation( CUSTOM_ANI_BLOOD45_HOLDSUCCESS );
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOOD45_END);

        sq_flashScreen(obj,0,0,1000,150, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOOD45 , STATE_BLOOD45, 0, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);				
    }
    else if (subState == 3)
    {

    	local speed = 300;

        //obj.sq_PlaySound("BLOODDOWN_1");
		obj.sq_SetStaticMoveInfo(0, speed, speed, false);	
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);	

    	obj.sq_SetCurrentAnimation( CUSTOM_ANI_BLOOD45_END0 );

    }
    else if (subState == 4)
    {
        obj.sq_PlaySound("BLOODDOWN_1");

        obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
    	obj.sq_SetCurrentAnimation( CUSTOM_ANI_BLOOD45_END );
//    	obj.sq_SetCurrentAnimation( CUSTOM_ANI_BLOOD45_OKHOLD );
//CUSTOM_ANI_BLOOD45_OKHOLD
    }
    else if (subState == 5)
    {

        local damager = obj.getVar("dama").get_obj_vector(0);
        local posX = sq_GetDistancePos(damager.getXPos(), obj.getDirection(), 50);	
        obj.sq_SetfindNearLinearMovablePos(posX ,damager.getYPos() - 1,obj.getXPos() , obj.getYPos(), 10);
        obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
    	obj.sq_SetCurrentAnimation( CUSTOM_ANI_BLOOD45_OKHOLD );

    }
    else if (subState == 6)
    {

        sq_flashScreen(obj,0,0,1500,150, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        obj.sq_SetShake(obj, 10, 500);
    	obj.sq_SetCurrentAnimation( CUSTOM_ANI_BLOOD45_OKHOLD2 );
    }

		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}



// prepareDraw
function prepareDraw_BLOOD45(obj)
{
	if (!obj) return;
}



// onEndCurrentAni
function onEndCurrentAni_BLOOD45(obj)
{
	if (!obj) return;
	
	
	if (obj.sq_GetSkillSubState(obj) == 0) 
    {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);	// subState????
		obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
	}
	else if (obj.sq_GetSkillSubState(obj) == 1) 
    {

        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);


	}else if (obj.sq_GetSkillSubState(obj) == 3) 
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (obj.sq_GetSkillSubState(obj) == 4) 
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (obj.sq_GetSkillSubState(obj) == 5)
    {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(6);	// subState????
		obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
    }else if (obj.sq_GetSkillSubState(obj) == 6)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}




function onProc_BLOOD45(obj)
{
    if (obj.sq_GetSkillSubState(obj) == 1)
    {
        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);
        if (obj.sq_timer_.isOnEvent(currentT) == true)
        {

            local sq_var = obj.getVar("check");
            local move = sq_var.get_vector(0);
 //           local move = blood45_moveMax ;//obj.sq_GetIntData(SKILL_BLOOD45, 0);
            local moveX = move/40;
            local blood45_value = 1;

            if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT) blood45_value = -1;

            if (blood45_move <= move)
            {
                if (blood45_move<= (move * 2 )/ 3)
                {
                    obj.sq_SetfindNearLinearMovablePos(obj.getXPos() + moveX * 4 * blood45_value ,obj.getYPos(),obj.getXPos(), obj.getYPos(), 10);
                    blood45_move = blood45_move + moveX * 4;
                }else{
                    obj.sq_SetfindNearLinearMovablePos(obj.getXPos() + moveX * blood45_value ,obj.getYPos(),obj.getXPos(), obj.getYPos(), 10);
                    blood45_move = blood45_move + moveX ;
                }
            }

            if (blood45_moveY <= obj.sq_GetIntData(SKILL_BLOOD45, 1))
            {
                local upPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL);
                local downPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL);
                local moveY = obj.sq_GetIntData(SKILL_BLOOD45, 1);
                
                if (upPress)
                {
                    obj.sq_SetfindNearLinearMovablePos(obj.getXPos(),obj.getYPos() - moveY/40 ,obj.getXPos(), obj.getYPos(), 10);
                    blood45_moveY = blood45_moveY + moveY/40;
                }
                if (downPress)
                {
                    obj.sq_SetfindNearLinearMovablePos(obj.getXPos(),obj.getYPos() + moveY/40 ,obj.getXPos(), obj.getYPos(), 10);
                    blood45_moveY = blood45_moveY + moveY/40;

                }


            }
        }
    }else{
    if (obj.sq_GetSkillSubState(obj) == 1)
    {
        pass;
    }

    }
}

function onAttack_BLOOD45(obj, damager, boundingBox, isStuck)
{
    if (obj.sq_GetSkillSubState(obj) == 1)
    {
        obj.getVar("dama").push_obj_vector(damager);
		local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOOD45, false, "character/atmage/blood45/ap_blood45.nut", true);				 
		if(masterAppendage) 
        {
			sq_HoldAndDelayDie(damager, obj, true, true, true, 200, 200, ENUM_DIRECTION_NEUTRAL , masterAppendage);
        }

        if (obj.getVar("flag").get_vector(0) == 0)
        {


            obj.getVar("isHold").clear_vector();

            if(damager.getState() != STATE_HOLD 
                && sq_IsGrabable(obj,damager) 
                && sq_IsHoldable(obj,damager) 
                && !sq_IsFixture(damager))
            {
                obj.getVar("isHold").push_vector(0);
            }else{
                obj.getVar("isHold").push_vector(1);
            }

            sq_flashScreen(damager,0,0,5000,3000, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

            local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOOD45, STATE_BLOOD45, 0, 1.0);
            sq_BinaryStartWrite();
            sq_BinaryWriteDword(attackBonusRate);	
            sq_BinaryWriteDword(2);	
            if (damager.getObjectHeight() <= 100)
            {
                sq_BinaryWriteDword(100);
            }else{
                sq_BinaryWriteDword(damager.getObjectHeight());
            }
            sq_BinaryWriteDword(obj.getVar("isHold").get_vector(0));
            mmmmm = 20;
            
            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, damager.getXPos(), damager.getYPos() + 1, damager.getZPos());

//            sq_SendCreatePassiveObjectPacketPos(obj,12107, 0, damager.getXPos(), damager.getYPos() + 1, damager.getZPos());

//            sq_SendCreatePassiveObjectPacketPos(obj,12108, 0, damager.getXPos(), damager.getYPos() - 1, damager.getZPos() - 200);

//            sq_SendCreatePassiveObjectPacketPos(obj,12139, 0, damager.getXPos(), damager.getYPos() - 2, damager.getZPos() + 100);

            sq_flashScreen(damager,0,0,3000,900, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);


        }

        if (obj.getVar("isHold").get_vector(0) == 1)
        {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(2);	// subState????
            obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
        }else{
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(5);	// subState????
            obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
        }


    }else{
        if (obj.sq_GetSkillSubState(obj) == 2)
        {



        }
    }

}


function onKeyFrameFlag_BLOOD45(obj,flagIndex)
{
	if(!obj)
		return false;

	local isMyControlObject = obj.sq_IsMyControlObject();

	if (isMyControlObject && flagIndex == 1 && obj.sq_GetSkillSubState(obj) == 2)
    {
        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();

        for(local i=0;i<objectsSize;++i)
        {
            local damager = var.get_obj_vector(i);

            if (obj.getVar("isHold").get_vector(0) == 0)
            {
                local dvalue = 1;
                if (sq_GetDirection(obj) == ENUM_DIRECTION_LEFT) dvalue = -1;
                obj.sq_SetfindNearLinearMovablePos(damager.getXPos() + dvalue * 100,damager.getYPos(),obj.getXPos(),obj.getYPos(),10);
            }else{
                obj.setCurrentPos(damager.getXPos(),damager.getYPos(),0);

            }

            sq_flashScreen(damager,0,0,1500,150, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            obj.sq_SetShake(obj, 10, 500);

        }

        if (obj.getVar("isHold").get_vector(0) == 1)
        {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(3);	// subState????
            obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
        }else{
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(4);	// subState????
            obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
        }

    }

}