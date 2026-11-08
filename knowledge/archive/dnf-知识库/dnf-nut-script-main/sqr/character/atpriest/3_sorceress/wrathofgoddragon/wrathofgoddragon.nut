 
function checkCommandEnable_WrathOfGodDragon(obj) {
	return true;
}

function checkExecutableSkill_WrathOfGodDragon(obj) {
	if (!obj) return false;
	local isUsed = obj.sq_IsUseSkill(SKILL_WRATHOFGODDRAGON);
	if (isUsed) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(10);
		obj.sq_AddSetStatePacket(STATE_WRATHOFGODDRAGON, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function onSetState_WrathOfGodDragon(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	switch (substate) {
	case 10:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_WRATHOFGODDRAGON_READYBODY);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_INFO_WRATHOFGODDRAGON);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_WRATHOFGODDRAGON , -1, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);
		break;
	case 0:
		obj.getVar("wrathofgoddragonSpeed").setFloat(0, 100.0);
		obj.getVar("wrathofgoddragonEnterCount").setInt(0, 0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_WRATHOFGODDRAGON);
		local UncleBangValue5 = sq_flashScreen(obj, 80, 60000, 240, 200, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		sq_createPooledObject(obj, "character/priest/effect/animation/atwrathodgoddragon/attack/06_background/atwrathofgoddragon_attack_background.ani", 0, -1, 0, 100, 1.0, 0, 0, 0);
		obj.getVar("wrathofgoddragonFlashObj").clear_obj_vector();
		obj.getVar("wrathofgoddragonFlashObj").push_obj_vector(UncleBangValue5);
		break;
	}
}

function onEndCurrentAni_WrathOfGodDragon(obj)
{
	if (!obj) return;
	local substate = obj.getSkillSubState();
	if (substate == 0)
	{
		
		sq_removePooledObject(obj);
		obj.sq_IntVectClear();
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 10)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_WRATHOFGODDRAGON, STATE_PRIORITY_IGNORE_FORCE, true);
	}
}

function onKeyFrameFlag_WrathOfGodDragon(obj, flagIndex)

{

	if (!obj) return false;
	local substate = obj.getSkillSubState();
	switch (substate)
	{
	case 0:
		switch (flagIndex)
		{
		case 10001:

			if (obj.isMyControlObject())

			{

				sq_SetMyShake(obj, 3, 100);

				obj.resetHitObjectList();

				obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_INFO_WRATHOFGODDRAGON);

				local UncleBangValue2 = obj.sq_GetBonusRateWithPassive(SKILL_WRATHOFGODDRAGON, -1, 0, 1.0);

				obj.sq_SetCurrentAttackBonusRate(UncleBangValue2);

			}

			break;

		case 10002:

			if (obj.isMyControlObject())

			{

				sq_SetMyShake(obj, 5, 100);

				obj.resetHitObjectList();

				obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_INFO_WRATHOFGODDRAGON);

				local UncleBangValue2 = obj.sq_GetBonusRateWithPassive(SKILL_WRATHOFGODDRAGON, -1, 1, 1.0);

				obj.sq_SetCurrentAttackBonusRate(UncleBangValue2);

			}

			break;

		case 10003:

			if (obj.isMyControlObject())

			{

				sq_SetMyShake(obj, 15, 300);

				sq_flashScreen(obj, 80, 80, 0, 255, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

				obj.resetHitObjectList();

				obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_INFO_WRATHOFGODDRAGON);

				local UncleBangValue2 = obj.sq_GetBonusRateWithPassive(SKILL_WRATHOFGODDRAGON, -1, 2, 1.0);

				obj.sq_SetCurrentAttackBonusRate(UncleBangValue2);

			}

			break;

		}

		break;

	}

	return true;

}

function onProc_WrathOfGodDragon(obj)

{

	if (!obj) return;

	local substate = obj.getSkillSubState();

	if (obj.isMyControlObject())

	{

		obj.setSkillCommandEnable(SKILL_WRATHOFGODDRAGON, true);

		if (substate == 0 && obj.getVar("wrathofgoddragonEnterCount").getInt(0) < (sq_GetIntData(obj, SKILL_WRATHOFGODDRAGON, 0) - 1))

		{

			if (obj.sq_IsEnterSkill(SKILL_WRATHOFGODDRAGON) != -1

			|| sq_IsKey(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))

			{

				obj.getVar("wrathofgoddragonSpeed").setFloat(0, obj.getVar("wrathofgoddragonSpeed").getFloat(0) + 1.0 * (sq_GetIntData(obj, SKILL_WRATHOFGODDRAGON, 1)));

				obj.getVar("wrathofgoddragonEnterCount").setInt(0, obj.getVar("wrathofgoddragonEnterCount").getInt(0) + 1);

			}

			obj.getCurrentAnimation().setSpeedRate(obj.getVar("wrathofgoddragonSpeed").getFloat(0));

		}

	}

}

function onEndState_WrathOfGodDragon(obj, newState)
{
	if (!obj) return;
	if (newState != STATE_WRATHOFGODDRAGON)
	{
		local UncleBangValue1 = obj.getVar("wrathofgoddragonFlashObj").get_obj_vector(0);
		UncleBangValue1 = sq_GetCNRDObjectToFlashScreen(UncleBangValue1);
		if (UncleBangValue1)
			UncleBangValue1.fadeOut();
	}
}