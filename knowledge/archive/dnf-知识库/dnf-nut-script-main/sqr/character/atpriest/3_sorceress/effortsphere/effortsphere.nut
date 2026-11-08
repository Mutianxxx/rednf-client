function checkCommandEnable_EffortSphere(obj)
{
	return true;
}

function checkExecutableSkill_EffortSphere(obj)

{

	if (!obj) return false;

	local UncleBangValue1 = obj.sq_IsUseSkill(SKILL_EFFORTSPHERE);

	if (UncleBangValue1)

	{

		obj.sq_IntVectClear();

		obj.sq_IntVectPush(0);

		obj.sq_AddSetStatePacket(STATE_EFFORTSPHERE, STATE_PRIORITY_IGNORE_FORCE, true);

		return true;

	}

	return false;

}

function onSetState_EffortSphere(obj, state, datas, isResetTimer)

{

	if (!obj) return;

	local UncleBangValue1 = obj.sq_GetVectorData(datas, 0);

	obj.setSkillSubState(UncleBangValue1);

	obj.sq_StopMove();

	switch (UncleBangValue1)

	{

	case 0:
		
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_EFFORTSPHERE1);
		//obj.sq_PlaySound("R_PW_EFFORT_SPHERE");
		sq_StartDrawCastGauge(obj, sq_GetCastTime(obj, SKILL_EFFORTSPHERE, sq_GetSkillLevel(obj, SKILL_EFFORTSPHERE)), true);
		break;

	case 1:

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_EFFORTSPHERE2);

		if (obj.isMyControlObject())

		{
			local UncleBangValue2 = obj.sq_GetSkillLoad(234);
			local UncleBangValue3 = UncleBangValue2.getRemainLoadNumber();
			local UncleBangValue4 = sq_GetIntData(obj, SKILL_ROSARYSHOOTING, UncleBangValue3);
			obj.sq_StartWrite();
			obj.sq_WriteDword(3);
			obj.sq_WriteDword(5);
			obj.sq_WriteDword(UncleBangValue4);
			obj.sq_SendCreatePassiveObjectPacket(24338, 0, 150, 0, 90);
			obj.sq_PlaySound("EFFORT_SPHERE");
			RosaryBeadClear(obj);
		}

		break;

	}

	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

}

function onEndCurrentAni_EffortSphere(obj)

{

	if (!obj || !obj.isMyControlObject()) return;

	local UncleBangValue1 = obj.getSkillSubState();

	if (UncleBangValue1 == 0)

	{

		obj.sq_IntVectClear();

		obj.sq_IntVectPush(1);

		obj.sq_AddSetStatePacket(STATE_EFFORTSPHERE, STATE_PRIORITY_IGNORE_FORCE, true);

	}

	if (UncleBangValue1 >= 1)

	{

		obj.sq_IntVectClear();

		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);

	}

}

function onEndState_EffortSphere(obj, newState) {
	if(!obj)
		return false;
	if(newState != STATE_EFFORTSPHERE)
		sq_EndDrawCastGauge(obj);
}