function checkCommandEnable_RosaryWildShot(obj)

{

	return true;

}

function checkExecutableSkill_RosaryWildShot(obj)

{

	if (!obj) return false;

	local UncleBangValue1 = obj.sq_IsUseSkill(SKILL_ROSARYWILDSHOT);

	if (UncleBangValue1)

	{

		obj.sq_IntVectClear();

		obj.sq_IntVectPush(0);

		obj.sq_AddSetStatePacket(STATE_ROSARYWILDSHOT, STATE_PRIORITY_IGNORE_FORCE, true);

		return true;

	}

	return false;

}

function onSetState_RosaryWildShot(obj, state, datas, isResetTimer)

{

	if (!obj) return;

	local UncleBangValue1 = obj.sq_GetVectorData(datas, 0);

	obj.setSkillSubState(UncleBangValue1);

	obj.sq_StopMove();

	switch (UncleBangValue1)

	{

	case 0:

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ROSARYWILDSHOT1);

		if (obj.isMyControlObject())

		{

			local UncleBangValue2 = obj.sq_GetSkillLoad(234);

			local UncleBangValue3 = UncleBangValue2.getRemainLoadNumber();

			local UncleBangValue4 = sq_GetIntData(obj, SKILL_ROSARYSHOOTING, UncleBangValue3);

			obj.sq_StartWrite();

			obj.sq_WriteDword(3);

			obj.sq_WriteDword(12);

			obj.sq_WriteDword(UncleBangValue4);

			obj.sq_SendCreatePassiveObjectPacket(24338, 0, 300, 0, 0);

		}

		break;

	case 1:

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ROSARYWILDSHOT2);

		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_INFO_ROSARYWILDSHOT);

		local UncleBangValue2 = obj.sq_GetSkillLoad(234);

		local UncleBangValue3 = UncleBangValue2.getRemainLoadNumber();

		local UncleBangValue4 = sq_GetIntData(obj, SKILL_ROSARYSHOOTING, UncleBangValue3);

		local UncleBangValue8 = obj.sq_GetBonusRateWithPassive(SKILL_ROSARYWILDSHOT, -1, 0, 1.0);

		UncleBangValue8 = UncleBangValue8 * (1 + UncleBangValue4.tofloat() / 100);

		obj.sq_SetCurrentAttackBonusRate(UncleBangValue8.tointeger());

		sq_setCurrentAttackBoundingBoxSizeRate(obj, 1.0, sq_GetIntData(obj, SKILL_ROSARYWILDSHOT, 0));

		RosaryBeadClear(obj);

		break;

	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onEndCurrentAni_RosaryWildShot(obj)

{

	if (!obj || !obj.isMyControlObject()) return;

	local UncleBangValue1 = obj.getSkillSubState();

	if (UncleBangValue1 == 0)

	{

		obj.sq_IntVectClear();

		obj.sq_IntVectPush(1);

		obj.sq_AddSetStatePacket(STATE_ROSARYWILDSHOT, STATE_PRIORITY_IGNORE_FORCE, true);

	}

	if (UncleBangValue1 >= 1)

	{

		obj.sq_IntVectClear();

		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);

	}

}

function onAttack_RosaryWildShot(obj, damager, boundingBox, isStuck)

{

	if (!obj || !obj.isMyControlObject()) return;

	local UncleBangValue1 = obj.getSkillSubState();

	switch (UncleBangValue1)

	{

	case 1:

		sq_AtrractionForce(obj, damager, false, 270, -1, 500.0, 500.0, false);

		break;

	}

}