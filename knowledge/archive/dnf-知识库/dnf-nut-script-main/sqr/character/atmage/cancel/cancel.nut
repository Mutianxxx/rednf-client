function checkExecutableSkill_cancel(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_CANCEL);
	if (isUseSkill) {
        if (!isEventHorizen(obj))
        {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(0); 
            obj.sq_AddSetStatePacket(STATE_CANCEL, STATE_PRIORITY_USER, true);
            return true;
        }else{
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(1); 
            obj.sq_AddSetStatePacket(STATE_CANCEL, STATE_PRIORITY_USER, true);
            removeEventHorizen(obj);
            return true;
        }
	}
	return false;
}


function checkCommandEnable_cancel(obj)
{
    return true;
}
function createFocus_Cancel(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atd_force/atd_force_finish_focus1.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
    local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x );
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}
function createDashAni_Cancel(obj,x,y,z,isFilp,imageRorate)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atd_force/atd_force_dash_eff.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
    local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x );
    local rorateRate = imageRorate.tofloat() / 100.0;
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
    if (isFilp == 1)
    {
		pooledObj.setCurrentDirection(sq_GetOppositeDirection(pooledObj.getDirection()));
        
    }
     sq_SetCustomRotate(pooledObj,rorateRate);	

	sq_AddObject(obj,pooledObj,2,false);	
}
function onSetState_CANCEL(obj, state, datas, isResetTimer)
{
	if (!obj) return;

	obj.sq_StopMove();
	
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
    obj.getVar("posXdistance").clear_vector();
    obj.getVar("posXdistance").push_vector(0);
    obj.getVar("posYdistance").clear_vector();
    obj.getVar("posYdistance").push_vector(0);
    obj.getVar("posZdistance").clear_vector();
    obj.getVar("posZdistance").push_vector(0);
    
    
	if (state == 0)
	{
        obj.getVar("dama").clear_obj_vector();
        
        obj.getVar("isGrab").clear_vector();
        obj.getVar("isGrab").push_vector(1);
        
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWCANCEL_CASTING1);
        
    }else if (state == 1)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWCANCEL_CASTING2);
        if (obj.isMyControlObject())
        {
            sq_SetMyShake(obj,15,120);
            local power = obj.sq_GetPowerWithPassive(SKILL_CANCEL, STATE_CANCEL, 4, -1, 1.0);

            obj.sq_StartWrite();
            obj.sq_WriteDword(power);	
            obj.sq_WriteDword(71);	
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, obj.sq_GetIntData(SKILL_CANCEL, 0), obj.sq_GetIntData(SKILL_CANCEL, 1), 0);
            obj.sq_StartWrite();
            obj.sq_WriteDword(power);	
            obj.sq_WriteDword(71);	
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, -obj.sq_GetIntData(SKILL_CANCEL, 2), obj.sq_GetIntData(SKILL_CANCEL, 3), 0);
            obj.sq_StartWrite();
            obj.sq_WriteDword(power);	
            obj.sq_WriteDword(71);	
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, obj.sq_GetIntData(SKILL_CANCEL, 4), obj.sq_GetIntData(SKILL_CANCEL, 5), 0);
            obj.sq_StartWrite();
            obj.sq_WriteDword(power);	
            obj.sq_WriteDword(71);	
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, obj.sq_GetIntData(SKILL_CANCEL, 6), obj.sq_GetIntData(SKILL_CANCEL, 7), 0);
        }
    }else if (state == 2)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWCANCEL_ACTION1);
        setBreakSenseEnegry(obj,getBreakSenseEnegry(obj) + obj.sq_GetIntData(SKILL_CANCEL, 23) );
        
    }else if (state == 3)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWCANCEL_ACTION2);
        
    }else if (state == 4)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWCANCEL_ACTION3);
        

    }else if (state == 5)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWCANCEL_FINISH);
        

    }else if (state == 6)
    {
        if (obj.isMyControlObject())
        {
            sq_flashScreen(obj,0,120,0,178, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
            sq_SetMyShake(obj,10,180);
            local attackBonusRate = obj.sq_GetPowerWithPassive(SKILL_CANCEL, STATE_CANCEL, 5, -1, 1.0);
            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);	
            obj.sq_WriteDword(72);	
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);
        }
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWCANCEL_GRABFINISH  );
    }else if (state == 7)
    {
        if (obj.isMyControlObject())
        {
            sq_SetMyShake(obj,15,120);
            local power = obj.sq_GetPowerWithPassive(SKILL_CANCEL, STATE_CANCEL, 2, -1, 1.0);

            obj.sq_StartWrite();
            obj.sq_WriteDword(power);	
            obj.sq_WriteDword(71);	
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, obj.sq_GetIntData(SKILL_CANCEL, 25), 
                                                        obj.sq_GetIntData(SKILL_CANCEL, 26), 0);
        }
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWCANCEL_CASTING2);
    }else if (state == 8)
    {
        if (obj.isMyControlObject())
        {
            sq_flashScreen(obj,0,120,0,178, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
            sq_SetMyShake(obj,10,180);
            local attackBonusRate = obj.sq_GetPowerWithPassive(SKILL_CANCEL, STATE_CANCEL, 3, -1, 1.0);
            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);	
            obj.sq_WriteDword(72);	
            obj.sq_SendCreatePassiveObjectPacket(24357, 0,obj.sq_GetIntData(SKILL_CANCEL, 25), 
                                                obj.sq_GetIntData(SKILL_CANCEL, 26), 0);
        }
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWCANCEL_GRABFINISH  );
    }

    local ani = obj.sq_GetCurrentAni();
	local delay = ani.getDelaySum(false);

    obj.getVar("pos").clear_vector();
    obj.getVar("pos").push_vector(delay);
    obj.getVar("pos").push_vector(obj.getXPos() );
    obj.getVar("pos").push_vector(obj.getYPos() );
    obj.getVar("pos").push_vector(obj.getZPos() );
}




function onProc_CANCEL(obj)
{
    local state = obj.getSkillSubState();
    if (state >= 2 && state <= 5)
    {
        local posXdistance = obj.getVar("posXdistance").get_vector(0);
        local posYdistance = obj.getVar("posYdistance").get_vector(0);
        local posZdistance = obj.getVar("posZdistance").get_vector(0);
        
        if (posXdistance + posYdistance + posZdistance != 0)
        {
            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();
            if (objectsSize > 0)
            {

                for(local i=0;i<objectsSize;++i)
                {
                    local damager = var.get_obj_vector(i);
                    local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), posXdistance);
                    if (sq_IsHoldable(obj,damager))
                        damager.setCurrentPos(posX ,obj.getYPos()+posYdistance,obj.getZPos() + posZdistance);

                    if (state == 5)
                    {
                        if ( CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/cancel/ap_cancel.nut") )
                        {
                            CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/cancel/ap_cancel.nut");
                        }
                    }

                }
            }
        }

    }

}




function onEndCurrentAni_CANCEL(obj)
{
	if(!obj.isMyControlObject()) {
		return;
	}
    local state = obj.getSkillSubState();
    if (state == 0)
    {
        if (obj.getVar("dama").get_obj_vector_size() > 0 )
        {
            
            if (obj.getVar("isGrab").get_vector(0) == 0)
            {
                obj.sq_IntVectClear();
                obj.sq_IntVectPush(2); 
                obj.sq_AddSetStatePacket(STATE_CANCEL, STATE_PRIORITY_USER, true);
            }else{
                obj.sq_IntVectClear();
                obj.sq_IntVectPush(7); 
                obj.sq_AddSetStatePacket(STATE_CANCEL, STATE_PRIORITY_USER, true);
            }
        }else{
            
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
        }
    }else if(state == 1)
    {
                obj.sq_IntVectClear();
                obj.sq_IntVectPush(6); 
                obj.sq_AddSetStatePacket(STATE_CANCEL, STATE_PRIORITY_USER, true);
    }else if (state == 2)
    {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(3); 
        obj.sq_AddSetStatePacket(STATE_CANCEL, STATE_PRIORITY_USER, true);
    }else if (state == 3)
    {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(4); 
        obj.sq_AddSetStatePacket(STATE_CANCEL, STATE_PRIORITY_USER, true);
    }else if (state == 4)
    {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(5); 
        obj.sq_AddSetStatePacket(STATE_CANCEL, STATE_PRIORITY_USER, true);
    }else if (state == 5)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 6)
    {
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 7)
    {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(8); 
        obj.sq_AddSetStatePacket(STATE_CANCEL, STATE_PRIORITY_USER, true);
    }else if (state == 8)
    {
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }

}




function onAttack_CANCEL(obj, damager, boundingBox, isStuck)
{
    local state = obj.getSkillSubState();
}

function onKeyFrameFlag_CANCEL(obj,flagIndex)
{

    if (!obj.isMyControlObject() )
        return false;

    if (obj.getVar("flag").get_vector(0) == 0)
    {
        obj.getVar("flag").set_vector(0,1);
        local state = obj.getSkillSubState();
        local x = 0;
        local y = 0;
        local z = 0;        
		local attackBonusRate = obj.sq_GetPowerWithPassive(SKILL_CANCEL, STATE_CANCEL, 0, -1, 1.0);
		local attackBonusRate2 = obj.sq_GetPowerWithPassive(SKILL_CANCEL, STATE_CANCEL, 0, -1, 1.0);
		local attackBonusRate3 = obj.sq_GetPowerWithPassive(SKILL_CANCEL, STATE_CANCEL, 1, -1, 1.0);
        if (state == 0)
        {
            
            obj.sq_StartWrite();
            obj.sq_WriteDword(0);	
            obj.sq_WriteDword(68);	
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, obj.sq_GetIntData(SKILL_CANCEL, 8), obj.sq_GetIntData(SKILL_CANCEL, 9), obj.sq_GetIntData(SKILL_CANCEL, 10) );
            
        }else if (state == 2 )
        {

            x = obj.sq_GetIntData(SKILL_CANCEL, 11);
            y = obj.sq_GetIntData(SKILL_CANCEL, 12);
            z = obj.sq_GetIntData(SKILL_CANCEL, 13);
            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);	
            obj.sq_WriteDword(69);	
            obj.sq_WriteDword(0);	
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, x + 50, y, z);
            createDashAni_Cancel(obj,x,y,z,0,0);
            obj.getVar("posXdistance").set_vector(0,x);
            obj.getVar("posYdistance").set_vector(0,y);
            obj.getVar("posZdistance").set_vector(0,z);
            
        }else if (state == 3 )
        {
            x = obj.sq_GetIntData(SKILL_CANCEL, 14);
            y = obj.sq_GetIntData(SKILL_CANCEL, 15);
            z = obj.sq_GetIntData(SKILL_CANCEL, 16);

            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);	
            obj.sq_WriteDword(69);	
            obj.sq_WriteDword(314);	
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, x - 50, y, z);
            createDashAni_Cancel(obj,x,y,z,1,0);
            obj.getVar("posXdistance").set_vector(0,x);
            obj.getVar("posYdistance").set_vector(0,y);
            obj.getVar("posZdistance").set_vector(0,z);

            
        }else if (state == 4 )
        {
            x = obj.sq_GetIntData(SKILL_CANCEL, 17);
            y = obj.sq_GetIntData(SKILL_CANCEL, 18);
            z = obj.sq_GetIntData(SKILL_CANCEL, 19);

            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate2);	
            obj.sq_WriteDword(69);	
            obj.sq_WriteDword(157);	
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, x, y, z + 75);
            createDashAni_Cancel(obj,x,y,z,1,39);
            obj.getVar("posXdistance").set_vector(0,x);
            obj.getVar("posYdistance").set_vector(0,y);
            obj.getVar("posZdistance").set_vector(0,z);
            
        }else if (state == 5 )
        {
            x = obj.sq_GetIntData(SKILL_CANCEL, 20);
            y = obj.sq_GetIntData(SKILL_CANCEL, 21);
            z = obj.sq_GetIntData(SKILL_CANCEL, 22);
            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate3);	
            obj.sq_WriteDword(70);	
            obj.sq_WriteDword( obj.sq_GetPowerWithPassive(SKILL_CANCEL, STATE_CANCEL, 6, -1, 1.0) );	
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, x, y, z);
            createFocus_Cancel(obj,x,y,z);
            obj.getVar("posXdistance").set_vector(0,x);
            obj.getVar("posYdistance").set_vector(0,y);
            obj.getVar("posZdistance").set_vector(0,z);
            
        }

    }
    return true;
}

