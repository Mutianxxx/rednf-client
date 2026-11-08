

function checkExecutableSkill_jumpdotquake(obj)  
{
    if (!isDollState(obj) )
    {

        local state = getDotObj(obj).getVar("state").get_vector(0);
        if ( state == 0 || state == 1 || state == 2)
        {
            local isUseSkill = obj.sq_IsUseSkill(SKILL_JUMPDOTQUAKE);
            if (obj.sq_GetState() == 0 || obj.sq_GetState() == 8 || obj.sq_GetState() == 14)
            {
                if (isUseSkill)
                {
                    obj.getVar("state").clear_vector();
                    obj.getVar("state").push_vector(0);
                    obj.sq_AddSetStatePacket(STATE_JUMPDOTQUAKE, STATE_PRIORITY_USER, true);
                }
            }else{
                if (isUseSkill)
                {
                    sendDotJumpDotQuake(obj);
                }
            }


        }
    }else{
        local isUseSkill = obj.sq_IsUseSkill(SKILL_JUMPDOTQUAKE);
        if (isUseSkill)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            obj.sq_AddSetStatePacket(STATE_JUMPDOTQUAKE, STATE_PRIORITY_USER, true);
        }
    }

}


function checkCommandEnable_jumpdotquake(obj)
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

function sendDotJumpDotQuake(obj) {
	local dot = getDotObj(obj);
	if (dot) {
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_JUMPDOTQUAKE, STATE_JUMPDOTQUAKE, 0, 1.0);
		local size = obj.sq_GetIntData(SKILL_JUMPDOTQUAKE, 3);
		local len = obj.sq_GetIntData(SKILL_JUMPDOTQUAKE, 0);
		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);
		if (sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && rightPress) len = obj.sq_GetIntData(SKILL_JUMPDOTQUAKE, 1);
		if (sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && leftPress) len = obj.sq_GetIntData(SKILL_JUMPDOTQUAKE, 1);

		dot.getVar("state").clear_vector();
		dot.getVar("state").push_vector(3);
		dot.getVar("subState").clear_vector();
		dot.getVar("subState").push_vector(0);
		dot.getVar("value").clear_vector();
		dot.getVar("value").push_vector(len);
		dot.getVar("value").push_vector(damage);
		dot.getVar("value").push_vector(size);
		local pIntVec = sq_GetGlobalIntVector();
		dot.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
	}
}


function onKeyFrameFlag_JUMPDOTQUAKE(obj,flagIndex)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        if (flagIndex == 1 &&  obj.getVar("flag").get_vector(0) == 0 )
        {
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);
            sendDotJumpDotQuake(obj);
        }
    }else if (state == 1)
    {
        if (flagIndex == 1 && obj.getVar("isUp").get_vector(0) == 0)
        {
            obj.getVar("isUp").clear_vector();
            obj.getVar("isUp").push_vector(1);
            sq_SendCreatePassiveObjectPacketPos(obj, 12246, 0, obj.getXPos(), obj.getYPos() + 1, 0);
        }
    }
}

function onProc_JUMPDOTQUAKE(obj) {
	local state = obj.getVar("state").get_vector(0);
	if (state == 1) {
		if (obj.getVar("isUp").get_vector(0) == 1) {
			obj.setCurrentPos(obj.getXPos(), obj.getYPos(), obj.getZPos() + 30);
		}
	} else if (state == 2) {
		if (obj.getZPos() <= 0) {
			local size = obj.sq_GetIntData(SKILL_JUMPDOTQUAKE, 3);
			obj.setCurrentPos(obj.getXPos(), obj.getYPos(), 0);
			sq_SendCreatePassiveObjectPacketPos(obj, 12290, 0, obj.getXPos(), obj.getYPos() + 2, 0);
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(0);
			sq_BinaryWriteDword(obj.sq_GetBonusRateWithPassive(SKILL_JUMPDOTQUAKE, STATE_JUMPDOTQUAKE, 0, 1.0));
			sq_BinaryWriteDword(size);
			sq_SendCreatePassiveObjectPacketPos(obj, 24346, 0, obj.getXPos(), obj.getYPos() + 1, 0);
			sq_flashScreen(obj, 100, 0, 100, 204, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
			sq_SendCreatePassiveObjectPacketPos(obj, 12247, 0, obj.getXPos(), obj.getYPos() + 1, 0);
			sq_SendCreatePassiveObjectPacketPos(obj, 12248, 0, obj.getXPos(), obj.getYPos() - 1, 0);
			sq_SetMyShake(obj, 5, 200);
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		} else {
			obj.setCurrentPos(obj.getXPos(), obj.getYPos(), obj.getZPos() - 60);
		}
	}
}

function onSetState_JUMPDOTQUAKE(obj, state, datas, isResetTimer)
{
    local state = obj.getVar("state").get_vector(0);
	obj.sq_StopMove();
    
    if (state == 0)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_JUMPDOTQUAKE);
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
    }else if (state == 1)
    {
		obj.sq_ZStop();
        local ani = obj.getVar().GetAnimationMap("jumpdotquake1", "passiveobject/zrr_skill/newmage/animation/dot/jumpingbearpress/mad/madjump.ani"); 
		obj.setCurrentAnimation(ani);

        obj.getVar("isUp").clear_vector();
        obj.getVar("isUp").push_vector(0);
    }else if (state == 2)
    {


		obj.sq_ZStop();
        local ani = obj.getVar().GetAnimationMap("jumpdotquake2", "passiveobject/zrr_skill/newmage/animation/dot/jumpingbearpress/mad/madhit_body.ani"); 
		obj.setCurrentAnimation(ani);
    }
	
//	obj.sq_SetCurrentAttackBonusRate(damage);				

}
function onEndCurrentAni_JUMPDOTQUAKE(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 1)
    {
        local posZ = obj.getZPos();
        obj.sq_SetfindNearLinearMovablePos(sq_GetDistancePos(obj.getXPos(),  obj.getDirection(), obj.sq_GetIntData(SKILL_JUMPDOTQUAKE, 0) ),obj.getYPos(),obj.getXPos(),obj.getYPos(),10);
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),posZ);

        obj.getVar("state").set_vector(0,2);
		obj.sq_AddSetStatePacket(STATE_JUMPDOTQUAKE, STATE_PRIORITY_USER, true);
    }
}
