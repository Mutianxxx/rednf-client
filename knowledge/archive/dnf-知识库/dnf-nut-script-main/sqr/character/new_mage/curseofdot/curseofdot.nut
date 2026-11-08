//FLAG 1 CREATE FLOOR EFFECT
//DOT
//ACT1
    //FLAG 1 [OFFSET] `CreateMadStartBack`	0	-1	0
    //FLAG 2 SHAKE 10 240
    //[OFFSET]
    //`CreateCurseFloor`	0	0	0
    //[OFFSET]
    //`ActiveMultiHitTimer`	0	0	0
    //[OFFSET]
    //`StartBreathLoopSound`	-50	0	40
    //FLAG 3 FLASH 10 50 10 76 255 255 255 BOTTOM
    //FLAG 4 [OFFSET] `StartCancelAble`	0	0	0
//ACT2
    //FLAG 1 [OFFSET] `CreateMadLoopBack`	0	-1	0



function checkExecutableSkill_curseofdot(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_CURSEOFDOT);
	if (isUseSkill) 
    {
        obj.getVar("state").clear_vector();
        if (!isDollState(obj) )
        {
            obj.getVar("state").push_vector(0);
        }else{
            obj.getVar("state").push_vector(1);
        }
		obj.sq_AddSetStatePacket(STATE_CURSEOFDOT, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_curseofdot(obj)
{

	return true;
}
function sendDotCurseOfDot(obj)
{
    local dot = getDotObj(obj);
    if (dot)
    {
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_CURSEOFDOT , STATE_CURSEOFDOT, 0, 1.0);
        dot.getVar("state").clear_vector();
        dot.getVar("state").push_vector(10);
        dot.getVar("subState").clear_vector();
        dot.getVar("subState").push_vector(0);
        dot.getVar("value").clear_vector();
        dot.getVar("value").push_vector(damage);
        dot.getVar("value").push_vector( obj.sq_GetIntData(SKILL_CURSEOFDOT, 0) );
        dot.getVar("value").push_vector( obj.sq_GetIntData(SKILL_CURSEOFDOT, 1) );
        dot.getVar("value").push_vector( obj.sq_GetIntData(SKILL_CURSEOFDOT, 2) );
        local pIntVec = sq_GetGlobalIntVector();
        dot.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
    }
}
function onSetState_CURSEOFDOT(obj, state, datas, isResetTimer)
{
    local state = obj.getVar("state").get_vector(0);
    local atk = ( 1300 + obj.sq_GetIntData(SKILL_CURSEOFDOT, 0) ) / obj.sq_GetIntData(SKILL_CURSEOFDOT, 1);
	obj.sq_StopMove();

    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);


    if (state == 0)
    {

        sendDotCurseOfDot(obj);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_CURSEOFDOT_BOBY);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
    }else if (state == 1)
    {

        sq_BinaryStartWrite();
        sq_BinaryWriteDword(  obj.sq_GetBonusRateWithPassive(SKILL_CURSEOFDOT , STATE_CURSEOFDOT, 0, 1.0) );
        sq_BinaryWriteDword(12);
        sq_BinaryWriteDword(atk);
        sq_SendCreatePassiveObjectPacketPos(obj, 24364, 0, obj.getXPos(), obj.getYPos() + 1, 0);

        local ani = obj.getVar().GetAnimationMap("curseofdot1", "passiveobject/zrr_skill/newmage/animation/dot/curseofdot/madstartfront_19.ani"); 
		obj.setCurrentAnimation(ani);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
    }else if (state == 2)
    {

        sq_BinaryStartWrite();
        sq_BinaryWriteDword(  obj.sq_GetBonusRateWithPassive(SKILL_CURSEOFDOT , STATE_CURSEOFDOT, 0, 1.0) );
        sq_BinaryWriteDword(13);
        sq_BinaryWriteDword(atk);
        sq_BinaryWriteDword( obj.sq_GetIntData(SKILL_CURSEOFDOT, 0) );
        sq_SendCreatePassiveObjectPacketPos(obj, 24364, 0, obj.getXPos(), obj.getYPos() + 1, 0);

        local ani = obj.getVar().GetAnimationMap("curseofdot2", "passiveobject/zrr_skill/newmage/animation/dot/curseofdot/madloopfront_16.ani"); 
		obj.setCurrentAnimation(ani);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
    }else if (state == 3)
    {

        sq_BinaryStartWrite();
        sq_BinaryWriteDword( obj.sq_GetBonusRateWithPassive(SKILL_CURSEOFDOT , STATE_CURSEOFDOT, 0, 1.0) );
        sq_BinaryWriteDword(14);
        sq_BinaryWriteDword(atk);
        sq_SendCreatePassiveObjectPacketPos(obj, 24364, 0, obj.getXPos(), obj.getYPos() + 1, 0);
        local ani = obj.getVar().GetAnimationMap("curseofdot3", "passiveobject/zrr_skill/newmage/animation/dot/curseofdot/madend_body.ani"); 
		obj.setCurrentAnimation(ani);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
    }
}
function onProc_CURSEOFDOT(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 2)
    {
        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);
        if (currentT > obj.sq_GetIntData(SKILL_CURSEOFDOT, 0) )
        {
            obj.getVar("state").set_vector(0,3);
            obj.sq_AddSetStatePacket(STATE_CURSEOFDOT, STATE_PRIORITY_USER, true);
        }
    }
}
function onKeyFrameFlag_CURSEOFDOT(obj, flagIndex)
{

        if (obj.getVar("flag").get_vector(flagIndex) == 0)
        {
            local subState = obj.getVar("state").get_vector(0);
            obj.getVar("flag").set_vector(flagIndex,1);
            if (subState == 1)
            {
                if(flagIndex == 1)
                {

                }else if (flagIndex == 2)
                {
                    sq_SetMyShake(obj,10,240);
                    sq_BinaryStartWrite();
                    sq_BinaryWriteDword( 0 );
                    sq_BinaryWriteDword(8);
                    sq_BinaryWriteDword( obj.sq_GetIntData(SKILL_CURSEOFDOT, 2) );
                    sq_SendCreatePassiveObjectPacketPos(obj, 24366, 0, 
                    sq_GetDistancePos(obj.getXPos(),  obj.getDirection(), 460 ) , obj.getYPos() - 1, 0);


                }else if (flagIndex == 3)
                {
                    sq_flashScreen(obj,10,50,10,76, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
                }
            }
        }   



}
function onEndCurrentAni_CURSEOFDOT(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 1)
    {
        obj.getVar("state").set_vector(0,2);
		obj.sq_AddSetStatePacket(STATE_CURSEOFDOT, STATE_PRIORITY_USER, true);
    }else if (state == 3)
    {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}
