//flag1 [OFFSET] `mad`	32	0	43
//flag2 mad2
//passive flag Value
//1 shake 3 120
//2 skip 82 0 163
//3 skill use
//4 shake 6 60 1 hit 161 0 52
//5 shake 6 60 2 hit 151 0 53
//6 shake 6 60 3 hit 132 0 110
//7 shake 6 60 4 hit 135 0 75
//8 shake 6 60 5 hit 154 0 64
//9 shake 6 60 6 hit  99 0 48
//10 shake 12 300 fina 125 0 0
//11 return 


function checkExecutableSkill_madbigdog(obj)  
{
	if (!obj) return false;

	if (!isDollState(obj) )
	{
		local dot = getDotObj(obj);
		if(!dot)
			return false;
		local isUseSkill = obj.sq_IsUseSkill(SKILL_MADBIGDOG);
		
		if (isUseSkill) 
		{
			obj.getVar("state").clear_vector();
			obj.getVar("state").push_vector(0);
			obj.sq_AddSetStatePacket(STATE_MADBIGDOG, STATE_PRIORITY_USER, true);
		}
		else
		{
			return false;
		}
	}
	else
	{
		local isUseSkill = obj.sq_IsUseSkill(SKILL_MADBIGDOG);
		if (isUseSkill) 
		{
			obj.getVar("state").clear_vector();
			obj.getVar("state").push_vector(3);
			obj.sq_AddSetStatePacket(STATE_MADBIGDOG, STATE_PRIORITY_USER, true);
		}
		else
		{
			return false;
		}
	}
	return true;
}


function checkCommandEnable_madbigdog(obj)
{
	return true;
}

function sendMadBigDogStartAttackFlag(obj)
{
	if (!obj) return;
	local dot = getDotObj(obj);
	if(dot)
	{
		local damage = obj.sq_GetPowerWithPassive(SKILL_MADBIGDOG, STATE_MADBIGDOG, 0, -1, 1.0);
		local damage2 = obj.sq_GetPowerWithPassive(SKILL_MADBIGDOG, STATE_MADBIGDOG, 1, -1, 1.0);
		local size = obj.sq_GetIntData(SKILL_MADBIGDOG, 5);
		dot.getVar("state").clear_vector();
		dot.getVar("state").push_vector(7);
		dot.getVar("value").clear_vector();
		dot.getVar("value").push_vector(damage);
		dot.getVar("value").push_vector(damage2);
		dot.getVar("value").push_vector(size);
		local pIntVec = sq_GetGlobalIntVector();
		dot.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
	}
}

function onProc_MADBIGDOG(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),50);
        if (getDotState(obj) != 7)
        {
            sendMadBigDogStartAttackFlag(obj);
        }
    }else if (state == 2)
    {
        if (obj.getZPos() <= 0)
        {
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
        }
    }
}
function onSetState_MADBIGDOG(obj, state, datas, isResetTimer)
{

	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_MADBIGDOG_START);

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        obj.getVar("isfly").clear_vector();
        obj.getVar("isfly").push_vector(0);
		obj.sq_SetStaticMoveInfo(0, 200, 100, false);	
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
        sq_SetZVelocity(obj,400,-1500 );


    }else if (state == 1)
    {   
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_MADBIGDOG_LOOP);
    }else if (state == 2)
    {   
		obj.sq_SetStaticMoveInfo(0, 200, 100, false);	
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
        sq_SetZVelocity(obj,400,-1500 );
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_MADBIGDOG_END);
    }else if (state == 3)
    {

        local ani = obj.getVar().GetAnimationMap("madbigdog", "passiveobject/zrr_skill/newmage/animation/dot/madthebig/mad_body.ani"); 
		obj.setCurrentAnimation(ani);

        sq_SendCreatePassiveObjectPacketPos(obj, 12284, 0, obj.getXPos(), obj.getYPos() + 1, 0);
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);

    }
	
//	obj.sq_SetCurrentAttackBonusRate(damage);				

}
function onKeyFrameFlag_MADBIGDOG(obj, flagIndex)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        if (flagIndex == 1 &&  obj.getVar("flag").get_vector(0) == 0 )
        {
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);
            sendMadBigDogStartAttackFlag(obj);
        }
    }
    else if (state == 3)
    {
        if (obj.getVar("flag").get_vector(flagIndex) == 0)
        {
            obj.getVar("flag").set_vector(flagIndex,1);
            if (flagIndex == 1)
            {
                sq_SetMyShake(obj,3,120);
                sq_SendCreatePassiveObjectPacketPos(obj, 12292, 0, obj.getXPos(), obj.getYPos() + 1, 0);
            } else if (flagIndex >= 4 && flagIndex <= 9)
            {
                local dama = obj.sq_GetPowerWithPassive(SKILL_MADBIGDOG, STATE_MADBIGDOG, 0, -1, 1.0);
                sq_BinaryStartWrite();
                sq_BinaryWriteDword(dama);
                sq_BinaryWriteDword(9);
                sq_BinaryWriteDword( flagIndex - 3 );
                sq_SendCreatePassiveObjectPacketPos(obj, 24364, 0, obj.getXPos(), obj.getYPos() + 1, 0);
                sq_SetMyShake(obj,6,60);
            }else if (flagIndex == 10)
            {
                local dama = obj.sq_GetPowerWithPassive(SKILL_MADBIGDOG, STATE_MADBIGDOG, 1, -1, 1.0);
                local size = obj.sq_GetIntData(SKILL_MADBIGDOG, 5);
                sq_BinaryStartWrite();
                sq_BinaryWriteDword(dama);
                sq_BinaryWriteDword(10);
                sq_BinaryWriteDword(size);
                sq_SendCreatePassiveObjectPacketPos(obj, 24364, 0, obj.getXPos(), obj.getYPos() + 1, 0);
                sq_SetMyShake(obj,12,300);
                sq_SendCreatePassiveObjectPacketPos(obj, 12291, 0, obj.getXPos(), obj.getYPos() - 1, 0);
            }
        }
    }
}
function onEndCurrentAni_MADBIGDOG(obj)
{
	local state = obj.getVar("state").get_vector(0);
	if (state == 0)
	{
		//        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		obj.getVar("state").set_vector(0,1);
		obj.sq_AddSetStatePacket(STATE_MADBIGDOG, STATE_PRIORITY_USER, true);
	}
	else if (state == 3)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}
