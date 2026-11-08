function checkExecutableSkill_jumpattackwin(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_JUMPATTACKWIN);
	if (isUseSkill) {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);

		obj.sq_AddSetStatePacket(STATE_JUMPATTACKWIN, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_jumpattackwin(obj)
{
    return true;
}

function createFrontJumpAttackWinStart(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atviolentstorm/stormstartback_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function onSetState_JUMPATTACKWIN(obj, state, datas, isResetTimer)
{
	if (!obj) return;

	obj.sq_StopMove();
	
	local state = obj.getVar("state").get_vector(0);
	
	if (state == 0)
	{
        createFrontJumpAttackWinStart(obj,0,1,0);
        sq_SetMyShake(obj,4,200);
		obj.sq_SendCreatePassiveObjectPacket(12144, 0, 0, 0, 0);
        obj.sq_PlaySound("JUMPATTACKWIN3");
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_JUMPATTACKWIN_READY);
		obj.setTimeEvent(2,25,0,false);
	}
    if (state == 1)
    {
        sq_SetMyShake(obj,4,100);
		obj.sq_SetCurrentAnimation( CUSTOM_ANI_JUMPATTACKWIN_CIRCLE0 );

		obj.setTimeEvent(0,obj.sq_GetIntData(SKILL_JUMPATTACKWIN,0),1,false);

    }
    if (state == 2)
    {
        obj.sq_PlaySound("JUMPATTACKWIN1");
        obj.sq_PlaySound("JUMPATTACKWIN4");
        sq_SetMyShake(obj,5,obj.sq_GetIntData(SKILL_JUMPATTACKWIN,1));
		obj.setTimeEvent(0,obj.sq_GetIntData(SKILL_JUMPATTACKWIN,1),0,false);
        obj.setTimeEvent(1,obj.sq_GetIntData(SKILL_JUMPATTACKWIN,2),0,true);

		obj.sq_SendCreatePassiveObjectPacket(12141, 0, 0, 0, 0);
		obj.sq_SendCreatePassiveObjectPacket(12142, 0, 0, 0, 0);

		obj.sq_SendCreatePassiveObjectPacket(12145, 0, 0, 0, 0);
		obj.sq_SendCreatePassiveObjectPacket(12148, 0, 0, 0, 0);

		obj.sq_SetCurrentAnimation( CUSTOM_ANI_JUMPATTACKWIN_CIRCLE1 );

        obj.sq_SetCurrentAttackInfo(ATTACKINFO_JUMPATTACKWIN);
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_JUMPATTACKWIN , STATE_JUMPATTACKWIN, 0, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);				


    }
    if (state == 3)
    {
		obj.sq_SendCreatePassiveObjectPacket(12143, 0, 0, 0, 0);

		obj.sq_SendCreatePassiveObjectPacket(12146, 0, 0, 0, 0);
		obj.sq_SendCreatePassiveObjectPacket(12147, 0, 0, 0, 0);

        obj.sq_SetCurrentAttackInfo(ATTACKINFO_JUMPATTACKWIN_LAST);
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_JUMPATTACKWIN , STATE_JUMPATTACKWIN, 1, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);				

		obj.sq_SetCurrentAnimation( CUSTOM_ANI_JUMPATTACKWIN_END );

        sq_flashScreen(obj,0,80,0,255, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
        sq_SetMyShake(obj,7,300);
    }
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);
}



// onEndCurrentAni
function onEndCurrentAni_JUMPATTACKWIN(obj)
{
	if (!obj) return;
	local state = obj.getVar("state").get_vector(0);
	
	if (state == 0) {

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);

		obj.sq_AddSetStatePacket(STATE_JUMPATTACKWIN, STATE_PRIORITY_USER, true);
	}
    if (state == 3)
    {

		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }

}

function onProc_JUMPATTACKWIN(obj)
{


    if (state == 2)
    {

    }
}





function onTimeEvent_JUMPATTACKWIN(obj, timeEventIndex, timeEventCount)
{
    local state = obj.getVar("state").get_vector(0);
    if (timeEventIndex == 0)
    {
        if (state == 1)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(2);
            obj.sq_AddSetStatePacket(STATE_JUMPATTACKWIN, STATE_PRIORITY_USER, true);
        }

        if (state == 2)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(3);
            obj.sq_AddSetStatePacket(STATE_JUMPATTACKWIN, STATE_PRIORITY_USER, true);
        }
    }else if (timeEventIndex == 1)
    {
        if (state == 2)
        {
            obj.resetHitObjectList();
            sq_flashScreen(obj,50,0,50,50, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
        }
    }else if (timeEventIndex == 2)
    {
        if (state == 1)
        {

            local x = 0;
            local y = 0;
            local move = 4;

            if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL)) x = - move;
            if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL)) x = move;
            if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL)) y = - move;
            if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL)) y = move;

            obj.sq_SetfindNearLinearMovablePos(obj.getXPos() + x,obj.getYPos() + y,obj.getXPos(), obj.getYPos(), 10);


            local isPress = sq_IsKeyDown(OPTION_HOTKEY_JUMP, ENUM_SUBKEY_TYPE_ALL)
            if (isPress)
            {

                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(2);
                obj.sq_AddSetStatePacket(STATE_JUMPATTACKWIN, STATE_PRIORITY_USER, true);

            }

        }
    }
}