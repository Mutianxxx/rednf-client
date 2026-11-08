function setStateMiraclechine(obj, state, datas, isResetTimer) {

}

function checkCommandEnable_PrayForOracle(obj)
{
	return true;
}

function checkExecutableSkill_PrayForOracle(obj)
{
	if (!obj) return false;
	local UncleBangValue1 = obj.sq_IsUseSkill(SKILL_PRAYOFRORACLE);
	if (UncleBangValue1)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_PRAYOFRORACLE, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function onSetState_PrayForOracle(obj, state, datas, isResetTimer)

{

	if (!obj) return;

	local UncleBangValue1 = obj.sq_GetVectorData(datas, 0);

	obj.setSkillSubState(UncleBangValue1);

	obj.sq_StopMove();

	switch (UncleBangValue1)

	{

		case 0:

			obj.sq_SetCurrentAnimation(CUSTOM_ANI_PRAY1);
			obj.sq_PlaySound("R_PW_PRAY_ORACLE");

			local UncleBangValue2 = sq_GetCastTime(obj, SKILL_PRAYOFRORACLE, sq_GetSkillLevel(obj, SKILL_PRAYOFRORACLE));

			local UncleBangValue3 = sq_GetCurrentAnimation(obj);

			local UncleBangValue4 = sq_GetFrameStartTime(UncleBangValue3, 5);

			local UncleBangValue5 = UncleBangValue4.tofloat() / UncleBangValue2.tofloat();

			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, UncleBangValue5, UncleBangValue5);

			sq_StartDrawCastGauge(obj, UncleBangValue4, true);

			local UncleBangValue6 = sq_CreateAnimation("", "sqr/character/atpriest/3_sorceress/prayfororacle/neo_priestf_sorceress_buff.ani");

			local UncleBangValue7 = sq_CreatePooledObject(UncleBangValue6, true);

			local UncleBangValue8 = obj.getObjectManager();

			UncleBangValue7.setCurrentDirection(obj.getDirection());

			UncleBangValue7 = sq_SetEnumDrawLayer(UncleBangValue7, ENUM_DRAWLAYER_BOTTOM);

			UncleBangValue7.setCurrentPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 475), UncleBangValue8.getFieldYPos(0, 0, 7), 0);

			sq_AddObject(obj, UncleBangValue7, 2, false);

			break;

		case 1:

			obj.sq_SetCurrentAnimation(CUSTOM_ANI_PRAY2);

			if (obj.isMyControlObject())

			{
				obj.sq_StartWrite();

				obj.sq_WriteDword(3);

				obj.sq_WriteDword(0);

				obj.sq_SendCreatePassiveObjectPacket(24338, 0, 150, -1, 0);

			}

			break;

	}

}

function onEndCurrentAni_PrayForOracle(obj)

{

	if (!obj || !obj.isMyControlObject()) return;

	local UncleBangValue1 = obj.getSkillSubState();

	if (UncleBangValue1 == 0)

	{

		obj.sq_IntVectClear();

		obj.sq_IntVectPush(1);

		obj.sq_AddSetStatePacket(STATE_PRAYOFRORACLE, STATE_PRIORITY_IGNORE_FORCE, true);

	}

	if (UncleBangValue1 >= 1)

	{

		obj.sq_IntVectClear();

		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);

	}

}

function onEndState_PrayForOracle(obj, newState)
{
	if (!obj) return;
	local substate = obj.getSkillSubState();
	if (substate == 1) {
		local skillLevel = sq_GetSkillLevel(obj ,  SKILL_PRAYOFRORACLE);
		local time = sq_GetLevelData(obj, SKILL_PRAYOFRORACLE, 4, skillLevel);
		local magAtk = sq_GetLevelData(obj, SKILL_PRAYOFRORACLE, 0, skillLevel).tofloat();
		magAtk = magAtk/10;
		local phyDef = sq_GetLevelData(obj, SKILL_PRAYOFRORACLE, 1, skillLevel).tofloat();
		local magDef = sq_GetLevelData(obj, SKILL_PRAYOFRORACLE, 5, skillLevel).tofloat();
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_PRAYOFRORACLE, false, "character/atpriest/3_sorceress/prayfororacle/ap_prayfororacle.nut", false);
		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_PRAYOFRORACLE, sq_GetSkillLevel(obj, SKILL_PRAYOFRORACLE));
		CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_PRAYOFRORACLE, true);
		appendage = obj.GetSquirrelAppendage("character/atpriest/3_sorceress/prayfororacle/ap_prayfororacle.nut");
		if (appendage) {
			appendage.sq_SetValidTime(time);
			local change_appendage = appendage.sq_getChangeStatus("prayfororacle");
			if(!change_appendage)
			{
				change_appendage = appendage.sq_AddChangeStatus("prayfororacle",obj, obj, 0, 0, true, 0);
			}
			if (change_appendage){
				change_appendage.clearParameter();
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK_BONUS, true, magAtk);
				change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_DEFENSE, false, phyDef);
				change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_DEFENSE, false, magDef);
			}
		}
	}
	sq_EndDrawCastGauge(obj);
}