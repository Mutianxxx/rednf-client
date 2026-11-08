function checkExecutableSkill_madbigbreak(obj)  
{
    if (!isDollState(obj) )
    {

        local state = getDotObj(obj).getVar("state").get_vector(0);
        if ( state == 0 || state == 1 || state == 2)
        {
            local isUseSkill = obj.sq_IsUseSkill(SKILL_MADBIGBREAK);
            if (obj.sq_GetState() == 0 || obj.sq_GetState() == 8 || obj.sq_GetState() == 14)
            {
                if (isUseSkill)
                {
                    obj.getVar("state").clear_vector();
                    obj.getVar("state").push_vector(0);
                    obj.sq_AddSetStatePacket(STATE_MADBIGBREAK, STATE_PRIORITY_USER, true);
                }
            }else{
                if (isUseSkill)
                {
                    sendDotMadBigBreak(obj);
                }
            }


        }
    }else{

        local isUseSkill = obj.sq_IsUseSkill(SKILL_MADBIGBREAK);
        if (isUseSkill)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            obj.sq_AddSetStatePacket(STATE_MADBIGBREAK, STATE_PRIORITY_USER, true);
        }
    }

}


function checkCommandEnable_madbigbreak(obj)
{
    if (!isDollState(obj))
    {
        return true;
    }else{
        if ( obj.sq_GetState() == 0 || obj.sq_GetState() == 8 || obj.sq_GetState() == 14 )
            return true;
    }
    return false;
}
function sendDotMadBigBreak(obj)
{
    local dot = getDotObj(obj)
    if(dot)
    {
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_MADBIGBREAK , STATE_MADBIGBREAK, 0, 1.0);
        local count = obj.sq_GetIntData(SKILL_MADBIGBREAK, 0);
        dot.getVar("state").clear_vector();
        dot.getVar("state").push_vector(4);
        dot.getVar("subState").clear_vector();
        dot.getVar("subState").push_vector(0);
        dot.getVar("value").clear_vector();
        dot.getVar("value").push_vector(count);
        dot.getVar("value").push_vector(damage);
        local pIntVec = sq_GetGlobalIntVector();
        dot.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
    }
}

function onKeyFrameFlag_MADBIGBREAK(obj,flagIndex)
{
    if (flagIndex == 1 &&  obj.getVar("flag").get_vector(0) == 0 )
    {
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(1);
    }
}

function onSetState_MADBIGBREAK(obj, state, datas, isResetTimer)
{

	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        sendDotMadBigBreak(obj);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_MADBIGBREAK);
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
    }else if (state == 1){

        local ani = obj.getVar().GetAnimationMap("madbigbreak1", "passiveobject/zrr_skill/newmage/animation/dot/madbigbreak/mad/madattack1.ani"); 
		obj.setCurrentAnimation(ani);

        sq_BinaryStartWrite();
        sq_BinaryWriteDword(1);
        sq_BinaryWriteDword( obj.sq_GetBonusRateWithPassive(SKILL_MADBIGBREAK , STATE_MADBIGBREAK, 0, 1.0) );
        sq_SendCreatePassiveObjectPacketPos(obj, 24346, 0, obj.getXPos(), obj.getYPos() + 1, 0);
        sq_SendCreatePassiveObjectPacketPos(obj, 12249, 0, obj.getXPos(), obj.getYPos() + 1, 0);


    }else if (state == 2){

        local ani = obj.getVar().GetAnimationMap("madbigbreak2", "passiveobject/zrr_skill/newmage/animation/dot/madbigbreak/mad/madattack2.ani"); 
        obj.setCurrentAnimation(ani);

        sq_BinaryStartWrite();
        sq_BinaryWriteDword(2);
        sq_BinaryWriteDword( obj.sq_GetBonusRateWithPassive(SKILL_MADBIGBREAK , STATE_MADBIGBREAK, 0, 1.0) );
        sq_SendCreatePassiveObjectPacketPos(obj, 24346, 0, obj.getXPos(), obj.getYPos() + 1, 0);
        sq_SendCreatePassiveObjectPacketPos(obj, 12250, 0, obj.getXPos(), obj.getYPos() + 1, 0);
        sq_SendCreatePassiveObjectPacketPos(obj, 12289, 0, obj.getXPos(), obj.getYPos() + 2, 0);

    }


}



function onEndCurrentAni_MADBIGBREAK(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 1)
    {
        obj.getVar("state").set_vector(0,2);
		obj.sq_AddSetStatePacket(STATE_MADBIGBREAK, STATE_PRIORITY_USER, true);
    }else if (state == 2)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}
