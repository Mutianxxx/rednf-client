function checkExecutableSkill_windsowrd(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_WINDSWORD);

	if (isUse) {

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_WINDSWORD , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}

function checkCommandEnable_windsowrd(obj)
{

	return true;
}


function onSetState_WINDSWORD(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);
    obj.sq_SetCurrentAnimation(CUSTOM_ANI_WINDSWORD + state);
    local ani = obj.sq_GetCurrentAni();
	local delay = ani.getDelaySum(false)/2;

    local damage = obj.sq_GetBonusRateWithPassive(SKILL_WINDSWORD , STATE_WINDSWORD, 0, 1.0); 

    obj.getVar("posX").clear_vector();
    obj.getVar("posX").push_vector(obj.getXPos());
    obj.getVar("posX").push_vector(delay);

    obj.sq_SetCurrentAttackInfo(ATTACKINFO_WINDSWORD);
    obj.sq_SetCurrentAttackBonusRate(damage);


    if (state %2 == 1)
    {

        local len = obj.sq_GetIntData(SKILL_WINDSWORD, (state - 1)/2 );
		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);
		if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && rightPress) len = obj.sq_GetIntData(SKILL_WINDSWORD, 5 + (state - 1)/2 );
		if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && leftPress) len = obj.sq_GetIntData(SKILL_WINDSWORD, 5 + (state - 1)/2 );

        obj.getVar("len").clear_vector();
        obj.getVar("len").push_vector(len );

		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_WINDSWORD , STATE_WINDSWORD, 1, 1.0); 
        	local atkT = obj.sq_GetIntData(SKILL_WINDSWORD, 10 );
        	local size = obj.sq_GetIntData(SKILL_WINDSWORD, 7 );
		obj.sq_StartWrite();
		obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
		obj.sq_WriteDword(28 + (state - 1)/2 );	// attackBonusRate
		obj.sq_WriteDword(atkT );	// attackBonusRate
		obj.sq_WriteDword(size );
		obj.sq_SendCreatePassiveObjectPacket(24357, 0, len/3, 1, 0);
        	obj.sq_PlaySound("GALE_HIGHWAY");
		//`GALE_HIGHWAY`

    }

	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,4.0, 4.0);

}

function onProc_WINDSWORD(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state%2 == 1)
    {

        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);
        local delayT = obj.getVar("posX").get_vector(1);
        local len = obj.getVar("len").get_vector(0);
    
		local v = sq_GetAccel(0, len, currentT, delayT, true);
		local srcX = obj.getVar("posX").get_vector(0);
		
		local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);
		 
		if(obj.isMovablePos(dstX, obj.getYPos() ))
			sq_setCurrentAxisPos(obj, 0, dstX);

    }


}


function onEndCurrentAni_WINDSWORD(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state > 9)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else{
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(state + 1);
		obj.sq_AddSetStatePacket(STATE_WINDSWORD , STATE_PRIORITY_USER, false);
    }
}


function getWindSwordBigSlashAnimation(obj,id)
{
    local ani = null;
    if (id == 39)
    {
        ani = obj.getVar().GetAnimationMap("SwordOfMindMulitingSlash", 
                    "passiveobject/zrr_skill/atmage/animation/atgalehighway/galehighway_b_bigslash.ani"); 
    }else if (id == 40)
    {
        ani = obj.getVar().GetAnimationMap("SwordOfMindMulitingSlash", 
                    "passiveobject/zrr_skill/atmage/animation/atgalehighway/galehighway_c_bigslash.ani"); 
    }else if (id == 41)
    {
        ani = obj.getVar().GetAnimationMap("SwordOfMindMulitingSlash", 
                    "passiveobject/zrr_skill/atmage/animation/atgalehighway/galehighway_d_bigslash.ani"); 
    }else if (id == 42)
    {
        ani = obj.getVar().GetAnimationMap("SwordOfMindMulitingSlash", 
                    "passiveobject/zrr_skill/atmage/animation/atgalehighway/galehighway_e_bigslash.ani"); 
    }else if (id == 43)
    {
        ani = obj.getVar().GetAnimationMap("SwordOfMindMulitingSlash", 
                    "passiveobject/zrr_skill/atmage/animation/atgalehighway/galehighway_f_bigslash.ani"); 
    }
    return ani;

}