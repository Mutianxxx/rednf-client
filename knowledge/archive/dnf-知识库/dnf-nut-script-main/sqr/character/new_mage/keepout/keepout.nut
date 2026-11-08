//STATE 0FLAG 1 [OFFSET] `pos`	49	0	59
//       FLAG 2 [OFFSET] `attackEnable`	57	0	66
//STATE 1FLAG 1 [OFFSET] `fire`	64	0	63
//4 180 shake
function checkExecutableSkill_keepout(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_KEEPOUT);
	if (isUseSkill) 
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_KEEPOUT, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_keepout(obj)
{

    return true;
//	return (!isDollState(obj) && isOpenBobyBox(obj) );
}

function onSetState_KEEPOUT(obj, state, datas, isResetTimer)
{
    local state = obj.getVar("state").get_vector(0);
	obj.sq_StopMove();

    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);

    if (state == 0)
    {
        obj.resetHitObjectList();
        if(!isDollState(obj) )
        {
            obj.sq_SetCurrentAnimation(CUSTOM_KEEPOUT_READY );
        }else{
            local ani = obj.getVar().GetAnimationMap("keepOut0", "character/mage/animation/zrr_ani/mad_keepoutstart.ani"); 
            obj.setCurrentAnimation(ani);
        }
        obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED , SPEED_TYPE_CAST_SPEED , SPEED_VALUE_DEFAULT , SPEED_VALUE_DEFAULT , 1.0 , 1.0);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_SPRLITMAGIC);
        obj.getVar("dama").clear_obj_vector();

    }else if (state == 1)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_KEEPOUT_SUCCESS );
        
    }else if (state == 2)
    {
        if(!isDollState(obj) )
        {
            obj.sq_SetCurrentAnimation(CUSTOM_KEEPOUT_FAIL );
        }else{
            local ani = obj.getVar().GetAnimationMap("keepOut1", "character/mage/animation/zrr_ani/mad_keepoutfail.ani"); 
            obj.setCurrentAnimation(ani);
        }
        
    }else if (state == 3)
    {
        if(!isDollState(obj) )
        {
            obj.sq_SetCurrentAnimation(CUSTOM_KEEPOUT_LAST );
        }else{
            local ani = obj.getVar().GetAnimationMap("keepOut2", "character/mage/animation/zrr_ani/mad_keepoutabody.ani"); 
            obj.setCurrentAnimation(ani);
        }
        
        
    }
}

function onAttack_KEEPOUT(obj, damager, boundingBox, isStuck)
{
    if (!sq_IsFixture(damager))
    {
        obj.getVar("dama").push_obj_vector(damager);


        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_KEEPOUT, false, "character/new_mage/keepout/ap_keepout.nut", true);				 
        if(masterAppendage) 
        {
            sq_HoldAndDelayDie(damager, obj, true, true, true, 200, 200, ENUM_DIRECTION_NEUTRAL , masterAppendage);
            damager.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
        }


    }
}
function onKeyFrameFlag_KEEPOUT(obj, flagIndex)
{
    local state = obj.getVar("state").get_vector(0);
    if (obj.getVar("flag").get_vector(flagIndex) == 0)
    {
        obj.getVar("flag").set_vector(flagIndex,1);

        if (state == 0)
        {
            if (flagIndex == 1)
            {

            }
        }else if (state == 3)
        {
                if (obj.getVar("dama").get_obj_vector_size() > 0)
                {
                    local damager = obj.getVar("dama").get_obj_vector(0);
                    local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_KEEPOUT, STATE_KEEPOUT, 0, 1.0);
                    obj.sq_StartWrite();
                    obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
                    obj.sq_WriteDword(19);
                    sq_SendCreatePassiveObjectPacketPos(obj,24364, 0, damager.getXPos() , damager.getYPos() ,damager.getZPos() + damager.getObjectHeight()/2);
                }
        }
    }
}
function onEndCurrentAni_KEEPOUT(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        if(!isDollState(obj) )
        {
            if (obj.getVar("dama").get_obj_vector_size() > 0)
            {
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(1);
                obj.sq_AddSetStatePacket(STATE_KEEPOUT, STATE_PRIORITY_USER, true);
            }else{
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(2);
                obj.sq_AddSetStatePacket(STATE_KEEPOUT, STATE_PRIORITY_USER, true);
            }
        }else{
            if (obj.getVar("dama").get_obj_vector_size() > 0)
            {
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(3);
                obj.sq_AddSetStatePacket(STATE_KEEPOUT, STATE_PRIORITY_USER, true);
            }else{
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(2);
                obj.sq_AddSetStatePacket(STATE_KEEPOUT, STATE_PRIORITY_USER, true);
            }
        }
    }else if (state == 1)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(3);
		obj.sq_AddSetStatePacket(STATE_KEEPOUT, STATE_PRIORITY_USER, true);
    }else if (state == 2)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 3)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}