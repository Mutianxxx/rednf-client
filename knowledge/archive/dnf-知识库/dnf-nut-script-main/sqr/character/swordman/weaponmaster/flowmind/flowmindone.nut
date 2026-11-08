



function onProc_FlowMindOne(obj)
{

	local isAppend = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/swordman/weaponmaster/flowmind/ap_liuxing.nut");
	if (isAppend)
	{
		local ajpd = sq_GetSkill(obj, 108).isInCoolTime();
		if (sq_IsKeyDown(OPTION_HOTKEY_JUMP, ENUM_SUBKEY_TYPE_ALL) && !ajpd)
		{

			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(63, STATE_PRIORITY_USER, true);

		}

		local ajpd1 = sq_GetSkill(obj, 109).isInCoolTime();
		if (sq_IsKeyDown(OPTION_HOTKEY_SKILL2, ENUM_SUBKEY_TYPE_ALL) && !ajpd1)
		{
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(0);
				obj.sq_AddSetStatePacket(64, STATE_PRIORITY_USER, true);
		}
	}
}