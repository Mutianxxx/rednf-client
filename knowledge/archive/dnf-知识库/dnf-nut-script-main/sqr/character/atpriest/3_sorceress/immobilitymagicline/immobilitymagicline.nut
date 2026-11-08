function checkCommandEnable_ImmobilityMagicLine(obj) {
	return true;

}

function checkExecutableSkill_ImmobilityMagicLine(obj) {
	if (!obj) return false;
	local UncleBangValue1 = obj.sq_IsUseSkill(SKILL_IMMOBILITYMAGICLINE);
	if (UncleBangValue1) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_IMMOBILITYMAGICLINE, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;

}

function onSetState_ImmobilityMagicLine(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local UncleBangValue1 = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(UncleBangValue1);
	obj.sq_StopMove();
	switch (UncleBangValue1) {
	case 0:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_IMMOBILITYMAGICLINE1);
		sq_StartDrawCastGauge(obj, sq_GetCastTime(obj, SKILL_IMMOBILITYMAGICLINE, sq_GetSkillLevel(obj, SKILL_IMMOBILITYMAGICLINE)), true);
		obj.sq_SetXScrollStart(400, 200);
		if (obj.isMyControlObject()) {
			local UncleBangValue2 = obj.sq_GetSkillLoad(234);
			local UncleBangValue3 = UncleBangValue2.getRemainLoadNumber();
			local UncleBangValue4 = sq_GetIntData(obj, SKILL_ROSARYSHOOTING, UncleBangValue3);
			obj.sq_StartWrite();
			obj.sq_WriteDword(3);
			obj.sq_WriteDword(9);
			obj.sq_WriteDword(UncleBangValue4);
			obj.sq_SendCreatePassiveObjectPacket(24338, 0, 0, 0, 0);
			RosaryBeadClear(obj);
		}
		local UncleBangValue5 = sq_flashScreen(obj, 80, 60000, 240, 200, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		obj.getVar("immobilitymagiclineFlashObj").clear_obj_vector();
		obj.getVar("immobilitymagiclineFlashObj").push_obj_vector(UncleBangValue5);
		break;
	case 1:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_IMMOBILITYMAGICLINE2);
		
		break;
	case 2:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_IMMOBILITYMAGICLINE3);
		obj.sq_SetXScrollStop(300);
		if (obj.isMyControlObject()) {
			sq_flashScreen(obj, 80, 80, 0, 255, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		}
		break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

}

function onEndCurrentAni_ImmobilityMagicLine(obj) {
	if (!obj || !obj.isMyControlObject()) return;
	local UncleBangValue1 = obj.getSkillSubState();
	if (UncleBangValue1 <= 1) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(UncleBangValue1 + 1);
		obj.sq_AddSetStatePacket(STATE_IMMOBILITYMAGICLINE, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if (UncleBangValue1 == 2) {
		obj.sq_IntVectClear();
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
	}

}

function onProcCon_ImmobilityMagicLine(obj) {
	if (!obj) return;
	local UncleBangValue1 = obj.getSkillSubState();
	if (UncleBangValue1 == 1 && obj.isMyControlObject()) {
		sq_SetKeyxEnable(obj, E_JUMP_COMMAND, true);
		if (sq_IsEnterCommand(obj, E_JUMP_COMMAND)) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(2);
			obj.sq_AddSetStatePacket(STATE_IMMOBILITYMAGICLINE, STATE_PRIORITY_IGNORE_FORCE, true);
		}
	}

}

function onEndState_ImmobilityMagicLine(obj, newState) {
	if (!obj) return;
	if (newState != STATE_IMMOBILITYMAGICLINE) {
		sq_EndDrawCastGauge(obj);
		sq_removePooledObject(obj);
		obj.sq_SetXScrollStop(0);
		local sq_var = obj.getVar("immobility");
		local append = "character/atpriest/3_sorceress/immobilitymagicline/ap_immobilitymagicline.nut";
		local objectsSize = sq_var.get_obj_vector_size();
		for (local i = 0; i < objectsSize; ++i) {
			local damager = sq_var.get_obj_vector(i);
			if (CNSquirrelAppendage.sq_IsAppendAppendage(damager, append)) {
				CNSquirrelAppendage.sq_RemoveAppendage(damager, append);
			}
		}
		local UncleBangValue1 = obj.getVar("immobilitymagiclineFlashObj").get_obj_vector(0);
		UncleBangValue1 = sq_GetCNRDObjectToFlashScreen(UncleBangValue1);
		if (UncleBangValue1) {
			UncleBangValue1.fadeOut();
		}
	
	}
	
}