function checkExecutableSkill_SwordGhost3(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_3);

	if (isUse) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_3, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}

function checkCommandEnable_SwordGhost3(obj) {
	if (!obj) return false;
	return true;
}

function onSetState_SwordGhost3(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);

	if (substate == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_BACK_JUMP_START);
		obj.sq_SetStaticMoveInfo(0, -350, 250, false);
		sq_SetZVelocity(obj, 150, -500);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}
	if (substate == 1) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_BACK_JUMP_RUN);
		obj.sq_SetStaticMoveInfo(0, -350, 250, false);
		sq_SetZVelocity(obj, -170, -500);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}
	if (substate == 2) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_BACK_JUMP_END);
		obj.sq_SetStaticMoveInfo(0, -350, 250, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}
	if (substate == 3) {
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 0.75, 0.75); //?????????????????
		obj.sq_SetStaticMoveInfo(0, -350, 250, false);
		sq_SetZVelocity(obj, 0, 0); //????-150,-500
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_NONE_JUMP);
		local gaugeValue_rate = setSwordGhost3State(obj);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_NONE_ATTACK4);

		local attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(attackInfo, getSwordGhost3BasicAttackBonus(obj));
		sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
		obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj), 8);
		sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
	}
}

function onProc_SwordGhost3(obj) {

	if (!obj) return;

	local substate = obj.getSkillSubState();
	local ZPos = obj.getZPos();
	if (substate == 0) {
		//print("0_ZPo = " + ZPos);
		if (ZPos >= 20) {
			if (sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL)) {
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(3);
				obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_3, STATE_PRIORITY_IGNORE_FORCE, true);
			}
		}
	}
	else if (substate == 1) {
		//print("1_ZPo = " + ZPos);
		if (ZPos <= 0) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(2);
			obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_3, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		if (sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL)) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(3);
			obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_3, STATE_PRIORITY_IGNORE_FORCE, true);
		}
	}
	else if (substate == 2) {

}
	else if (substate == 3) {
		setSwordGhost28Effect(obj);
	}

}

function onEndCurrentAni_SwordGhost3(obj) {

	local substate = obj.getSkillSubState();
	if (substate == 0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_3, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if (substate == 1) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_3, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 2) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	else if (substate == 3) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}

}