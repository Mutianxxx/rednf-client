function onProc_MAGEDASHATTACK(obj)
{
//			obj.sq_SendCreatePassiveObjectPacket(24357, 0, 100, 1, 55);
    if (isDollState(obj))
    {
		obj.sq_AddSetStatePacket(200, STATE_PRIORITY_USER, true);
    }
}

function onSetState_MAGEDASHATTACKNEW(obj, state, datas, isResetTimer)
{


		local isPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL) || sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL);

		if(!isPress)
			obj.sq_SetStaticMoveInfo(0, 450, 450, false, -500, true);

        local ani = getDashAttackAni_Mage(obj);
		obj.setCurrentAnimation(ani);

        local atk = getDashAttackInfo_Mage(obj);
        obj.sq_SetCurrentAttackInfo( atk );

}


function onEndCurrentAni_MAGEDASHATTACKNEW(obj)
{

		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}
