
function checkExecutableSkill_SwordGhost1(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_1);
	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_1, STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function checkCommandEnable_SwordGhost1(obj) {
	if (!obj) return false;
	local state = obj.sq_GetState();

	if (state == STATE_STAND) return true;

	return true;
}

function onSetState_SwordGhost1(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();

	obj.sq_SetStaticMoveInfo(0, 55, 100, false);
	obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL)) {
		obj.sq_SetStaticMoveInfo(0, 140, 100, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}
	if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL)) {
		obj.sq_SetStaticMoveInfo(0, 140, 100, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}

	local gaugeValue_rate = setSwordGhost3State(obj);
	local skill = sq_GetSkill(obj, 46);

	obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_NONE_ATTACK4);
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_NONE_ATTACK4);
	skill.resetCurrentCoolTime();
	//obj.sq_SetCurrentAttackBonusRate(damage);

	local attackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackBonusRate(attackInfo, getSwordGhost3BasicAttackBonus(obj));
	sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
	obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj), 8);
	sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));

	obj.sq_SendCreatePassiveObjectPacket(260158, 0, 20, 1, 0);

	//print( "upForce:" + upForce);
	//print( "power:" + power);
	//print( "attackBonusRate:" + attackBonusRate);

}

function onKeyFrameFlag_SwordGhost1(obj, flagIndex) {
	if (!obj) return false;
	local isAppendApd_buff_attack = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/JG_SwordMan/swordghost13/ap_buff.nut");
	if (isAppendApd_buff_attack) {
		if (flagIndex == 123) 
		{
			obj.sq_PlaySound("SM_MOONSPIRITSLASH_VS_01");
			obj.sq_SendCreatePassiveObjectPacket(260210, 0, 0, 0, 0);
			//obj.sq_SetShake(obj,5,65);
			obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("effect/animation/bladespirit/buff_attack2.ani"), -10, 0);
			obj.sq_AddStateLayerAnimation(3, obj.sq_CreateCNRDAnimation("effect/animation/bladespirit/buff_attack2_sub.ani"), -10, 0);
			obj.sq_AddStateLayerAnimation(5, obj.sq_CreateCNRDAnimation("effect/animation/bladespirit/buff_attack4_attack_sub_Z.ani"), -150, -3);
			return true;
		}
	}
}

function onProc_SwordGhost1(obj)
{
	if (!obj) return false;
	obj.setSkillCommandEnable(169, true);
	obj.setSkillCommandEnable(46, true);
	local t = obj.sq_IsEnterSkill(169);
	if (t != -1) {
		local isUse = obj.sq_IsUseSkill(169);
		if (isUse) {
			obj.startSkillCoolTime(169, 1, -1);
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_IntVectPush(1);
			obj.sq_IntVectPush(200);
			obj.sq_AddSetStatePacket(STATE_JUMP, STATE_PRIORITY_USER, true);
		}
	}
	local st = obj.sq_IsEnterSkill(46);
	if (st != -1) {
		local isUse = obj.sq_IsUseSkill(46);
		if (isUse) {
			obj.startSkillCoolTime(46, 1, -1);
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(-1);
			obj.sq_IntVectPush(-1);
			obj.sq_IntVectPush(-1);
			obj.sq_IntVectPush(-1);
			obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_2, STATE_PRIORITY_USER, true);
		}
	}
}

function onEndCurrentAni_SwordGhost1(obj) {
	if (!obj) return;
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}