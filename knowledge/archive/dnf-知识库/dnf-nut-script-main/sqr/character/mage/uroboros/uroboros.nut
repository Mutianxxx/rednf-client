function checkExecutableSkill_mage_uroboros(obj) {
	if (!obj) return false;
	local flag = obj.sq_IsUseSkill(134);
	if (flag) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(134, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
};

function checkCommandEnable_mage_uroboros(obj) {
	if (!obj) return false;
	local flag = obj.sq_GetState();
	if (flag == STATE_STAND) return true;
	if (flag == STATE_ATTACK) {
		return obj.sq_IsCommandEnable(134);
	}
	return true;
};

function onSetState_mage_uroboros(obj, state, datas, wquMHdADyE) {
	if (!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_SetCurrentAttackInfo(50);
	local phIlPu_6nS = obj.sq_GetBonusRateWithPassive(134, 134, 1, 1.0);
	obj.sq_SetCurrentAttackBonusRate(phIlPu_6nS);
	switch (substate) {
	case 0:
		obj.sq_StopMove();
		obj.sq_SetCurrentAnimation(130);
		obj.sq_PlaySound("WZ_UROBOROS");
		obj.sq_SetStaticSpeedInfo(0, 0, SPEED_VALUE_DEFAULT, (SPEED_VALUE_DEFAULT * 1.5).tointeger(), 1.0, 1.0);
		break;
	case 1:
		obj.sq_SetCurrentAnimation(131);
		local level = sq_GetSkillLevel(obj, 134);
		local dlwGBUpBbKpQxmvUU = obj.sq_GetLevelData(134, 0, level);
		local i5cNv9iTs2MDrj = obj.sq_GetLevelData(134, 2, level);
		local dLMjqyeFJbHVJ = obj.sq_GetLevelData(134, 3, level);
		local KOsY2ex_iV1boa = obj.sq_GetLevelData(134, 5, level);

		obj.setTimeEvent(0, dlwGBUpBbKpQxmvUU, 1, false);

		obj.setTimeEvent(1, 300, 0, false);
		local element = getElementType(obj, true);
		if (element == ENUM_ELEMENT_NONE) {
			element = ENUM_ELEMENT_FIRE;
		}
		obj.setTimeEvent(2, KOsY2ex_iV1boa, 0, false);
		obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("effect/animation/uroboros/attack/attackset02_center.ani"), 0, -175);
		obj.getVar().clear_timer_vector();
		obj.getVar().push_timer_vector();
		local SrjpvaT7qrAuQ3gR = obj.getVar().get_timer_vector(0);
		SrjpvaT7qrAuQ3gR.setParameter(i5cNv9iTs2MDrj, -1);
		SrjpvaT7qrAuQ3gR.resetInstant(0);

		obj.getVar().push_timer_vector();
		local XvLSw2x57w580uwpKtG6_HNp = obj.getVar().get_timer_vector(1);
		XvLSw2x57w580uwpKtG6_HNp.setParameter(10, -1);
		XvLSw2x57w580uwpKtG6_HNp.resetInstant(0);
		obj.getVar().clear_vector();
		local var = obj.getVar();
		var.push_vector(element);
		var.push_vector(0);
		var.push_vector(0);
		var.push_vector(5);
		var.push_vector(i5cNv9iTs2MDrj);
		var.push_vector(dLMjqyeFJbHVJ);
		var.push_vector(150);
		var.push_vector(250);
		var.push_vector(sq_GetObjectTime(obj));

		local MqNmBAHWbN3mn6PfL6 = sq_AttractToMe(obj, 350, 0, 250);
		obj.getVar().setAppendage(0, MqNmBAHWbN3mn6PfL6);
		break;
	case 2:
		obj.sq_SetCurrentAnimation(132);
		obj.sq_AddStateLayerAnimation(-1, obj.sq_CreateCNRDAnimation("effect/animation/uroboros/idle/dustunder_01.ani"), 0, 0);
		obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("effect/animation/uroboros/idle/dustupper_01.ani"), 0, 0);
		local element = obj.getVar().get_vector(0);
		if (element != ENUM_ELEMENT_NONE) obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("effect/animation/uroboros/attack/attackset02_center.ani"), 0, -175);

		local GjHSUoO32gYu = sq_CreateDrawOnlyObject(obj, "character/mage/effect/animation/uroboros/idle/shockwave.ani_01.ani", ENUM_DRAWLAYER_BOTTOM, true);
		sq_moveWithParent(obj, GjHSUoO32gYu);
		obj.getVar("aniobj").clear_obj_vector();
		obj.getVar("aniobj").push_obj_vector(GjHSUoO32gYu);
		break;
	}
};

function onProc_mage_uroboros(obj) {
	if (!obj) return;
	local substate = obj.getSkillSubState();
	if (substate < 1) return;
	local var = obj.getVar();
	local wYZ0c8qSptd = sq_GetObjectTime(obj);
	local AosKQAq0UaTY7oawu = var.get_timer_vector(0);
	if (AosKQAq0UaTY7oawu) if (AosKQAq0UaTY7oawu.isOnEvent(wYZ0c8qSptd) == true) obj.resetHitObjectList();
	local IVnBFIYJpi1hlKC = var.get_timer_vector(1);
	if (IVnBFIYJpi1hlKC) if (IVnBFIYJpi1hlKC.isOnEvent(wYZ0c8qSptd) == true) {
		local K3nY2yIvjI0tZrH_xMEkNA = var.get_vector(1);
		if (K3nY2yIvjI0tZrH_xMEkNA == 0) return;
		local OwAkX_uZFPazuTEof = wYZ0c8qSptd - var.get_vector(8);
		local eb5UkN5l2Vxyx = 500;
		local rbCzpGGv9GrvmAndZUteCr = obj.getXPos() + sq_GetUniformVelocity(0, 6 * K3nY2yIvjI0tZrH_xMEkNA, OwAkX_uZFPazuTEof, eb5UkN5l2Vxyx);
		if (obj.isMovablePos(rbCzpGGv9GrvmAndZUteCr, obj.getYPos())) sq_setCurrentAxisPos(obj, 0, rbCzpGGv9GrvmAndZUteCr);
	}
};

function onProcCon_mage_uroboros(obj) {
	if (!obj) return;
	local substate = obj.getSkillSubState();
	if (substate < 1) return;
	local var = obj.getVar();
	local qyPBPgFKpGj6kG4UA = var.get_vector(1);
	local tIltF8MFUco = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
	local s6S6xdPTqo = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

	if (tIltF8MFUco && s6S6xdPTqo || !tIltF8MFUco && !s6S6xdPTqo) {
		if (qyPBPgFKpGj6kG4UA != 0) {
			sq_BinaryStartWrite();
			sq_BinaryWriteWord(2);
			sq_SendChangeSkillEffectPacket(obj, 134);
		}
	}
	else if (tIltF8MFUco) {
		if (qyPBPgFKpGj6kG4UA != -1) {
			sq_BinaryStartWrite();
			sq_BinaryWriteWord(3);
			sq_SendChangeSkillEffectPacket(obj, 134);
		}
	}
	else if (s6S6xdPTqo) {
		if (qyPBPgFKpGj6kG4UA != 1) {
			sq_BinaryStartWrite();
			sq_BinaryWriteWord(4);
			sq_SendChangeSkillEffectPacket(obj, 134);
		}
	}
	local nuONTa6VI4v225FlWMVPon = var.get_timer_vector(0);
	if (!nuONTa6VI4v225FlWMVPon) return;
	sq_SetKeyxEnable(obj, E_ATTACK_COMMAND, true);
	if (sq_IsEnterCommand(obj, E_ATTACK_COMMAND)) {
		local YpdaaPB6VDJMB = var.get_vector(2);
		local oazmmWNI4P0 = var.get_vector(3);
		if (YpdaaPB6VDJMB < oazmmWNI4P0) {
			YpdaaPB6VDJMB += 1;
			var.set_vector(2, YpdaaPB6VDJMB);
			sq_BinaryStartWrite();
			sq_BinaryWriteWord(1);
			sq_BinaryWriteDword(sq_GetUniformVelocity(var.get_vector(4), var.get_vector(5), YpdaaPB6VDJMB, oazmmWNI4P0));
			sq_BinaryWriteDword(sq_GetUniformVelocity(var.get_vector(6), var.get_vector(7), YpdaaPB6VDJMB, oazmmWNI4P0));
			sq_SendChangeSkillEffectPacket(obj, 134);
		}
	}
	if (substate < 2) return;
	sq_SetKeyxEnable(obj, E_JUMP_COMMAND, true);
	if (sq_IsEnterCommand(obj, E_JUMP_COMMAND)) onEndEff_mage_uroboros(obj);
};

function onKeyFrameFlag_mage_uroboros(obj, nLtWk2mg1p65eOKV) {
	if (!obj) return false;
	local substate = obj.getSkillSubState();
	if (substate == 0) {
		if (nLtWk2mg1p65eOKV == 1) obj.sq_PlaySound("WZ_UROBOROS_RIDE");
		else if (nLtWk2mg1p65eOKV == 2) {
			sq_SetMyShake(obj, 3, 80);
			sq_SetMyShake(obj, 1, 400);
			obj.sq_PlaySound("UROBOROS_ROTATE_LOOP", 9006);
		}
	}
	return true;
};

function onTimeEvent_mage_uroboros(obj, gMQEL0RWS992iwNOr5oLFQrN, FMeQDUA8OPVZ3WSSQi9Zw2) {
	if (!obj) return false;
	switch (gMQEL0RWS992iwNOr5oLFQrN) {
	case 0:
		onEndEff_mage_uroboros(obj);
		break;
	case 1:
		local bxQmxOwIDES81j1Mx = obj.getVar().get_vector(1);
		if (bxQmxOwIDES81j1Mx == 0) return false;
		local ani = sq_AddDrawOnlyAniFromParent(obj, "character/mage/effect/animation/uroboros/move/movedustbig_01.ani", 0, -1, 0);
		sq_SetCurrentDirection(ani, (bxQmxOwIDES81j1Mx == 1) ? ENUM_DIRECTION_RIGHT : ENUM_DIRECTION_LEFT);
		break;
	case 2:
		local element = obj.getVar().get_vector(0);
		if (element == ENUM_ELEMENT_NONE) {
			element = ENUM_ELEMENT_FIRE;
		}
		local v4BWMgOv4kQYVFf9l2h = sq_FindTarget(obj, -330, 330, 110, 100);
		if (!v4BWMgOv4kQYVFf9l2h) return false;
		local EK1GDT0gEgtgdjD2pJnYlDr = obj.getDirection();
		local oURvosJjTv = obj.getXPos();
		local T38JafaCIew = v4BWMgOv4kQYVFf9l2h.getXPos();
		local Q0sJRcSjDRMY51 = v4BWMgOv4kQYVFf9l2h.getYPos();
		local yumGAHoe_q_ro7KbH = sq_Atan2(sq_Abs(oURvosJjTv - T38JafaCIew).tofloat(), 175.0);
		if (oURvosJjTv > T38JafaCIew && EK1GDT0gEgtgdjD2pJnYlDr == ENUM_DIRECTION_RIGHT || oURvosJjTv < T38JafaCIew && EK1GDT0gEgtgdjD2pJnYlDr == ENUM_DIRECTION_LEFT) yumGAHoe_q_ro7KbH /= -1;
		local anifile = ["fire.ani", "ice.ani", "dark.ani", "light.ani"];
		local ani = sq_AddDrawOnlyAniFromParent(obj, "passiveobject/script_sqr_nut_qq506807329/mage/animation/uroboros/attackset03_" + anifile[element], 0, 0, 175);
		sq_moveWithParent(obj, ani);
		sq_SetCustomRotate(ani, yumGAHoe_q_ro7KbH);
		obj.getVar("aniobj").push_obj_vector(ani);
		obj.sq_PlaySound("R_UROBOROS_SPARK");
		if (obj.sq_IsMyControlObject()) {

			obj.sq_StartWrite();
			obj.sq_WriteDword(134);
			obj.sq_WriteDword(1);
			obj.sq_WriteDword(element);
			obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(134, 134, 4, 1.0));
			sq_SendCreatePassiveObjectPacketPos(obj, 24372, 0, T38JafaCIew, Q0sJRcSjDRMY51, 0);
			if (element < ENUM_ELEMENT_NONE) {
				obj.getVar().set_vector(0, element + 1);
			}
			else {
				obj.getVar().set_vector(0, ENUM_ELEMENT_FIRE);
			}

		}
		break;
	}
	return false;
};

function onEndCurrentAni_mage_uroboros(obj) {
	if (!obj) return;
	if (!obj.sq_IsMyControlObject()) return;
	local substate = obj.getSkillSubState();
	if (substate != 2) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(substate + 1);
		obj.sq_AddSetStatePacket(134, STATE_PRIORITY_USER, true);
	}
};

function onEndState_mage_uroboros(obj, BjCMS7121s1A) {
	if (!obj) return;
	if (BjCMS7121s1A != 134) {
		RemoveAllAni(obj);
		obj.stopSound(9006);

		local UiC9T_LYfJOjliP7v = obj.getVar().getAppendage(0);
		if (UiC9T_LYfJOjliP7v) UiC9T_LYfJOjliP7v.setValid(false);
	}
};

function onChangeSkillEffect_mage_uroboros(obj, BjCMS7121s1A, UiC9T_LYfJOjliP7v) {
	if (!obj) return;
	local olQSqmBqMxBNTyMACHZW2Kx = UiC9T_LYfJOjliP7v.readWord();
	switch (olQSqmBqMxBNTyMACHZW2Kx) {
	case 1:
		local TWemoJpCckKoXK7sw = obj.getVar().get_timer_vector(0);
		if (TWemoJpCckKoXK7sw) TWemoJpCckKoXK7sw.setEventTerm(UiC9T_LYfJOjliP7v.readDword());
		obj.sq_SetStaticSpeedInfo(0, 0, SPEED_VALUE_DEFAULT, (SPEED_VALUE_DEFAULT * (UiC9T_LYfJOjliP7v.readDword() / 100.0)).tointeger(), 1.0, 1.0);
		break;
	case 2:
		obj.getVar().set_vector(1, 0);
		break;
	case 3:
		obj.getVar().set_vector(8, sq_GetObjectTime(obj));
		obj.getVar().set_vector(1, -1);
		break;
	case 4:
		obj.getVar().set_vector(8, sq_GetObjectTime(obj));
		obj.getVar().set_vector(1, 1);
		break;
	}
};

function onEndEff_mage_uroboros(obj) {

	if (obj.sq_IsMyControlObject()) {
		obj.sq_StartWrite();
		obj.sq_WriteDword(134);
		obj.sq_WriteDword(2);
		obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(134, 134, 6, 1.0));
		obj.sq_SendCreatePassiveObjectPacket(24372, 0, 0, 0, 0);
		obj.sq_AddSetStatePacket(20, STATE_PRIORITY_USER, false);
	}
};

function getElementType(obj, flag) {
	if (!obj) return ENUM_ELEMENT_NONE;

	local element = ENUM_ELEMENT_NONE;
	local attackinfo = (flag) ? sq_GetCurrentAttackInfo(obj) : obj.sq_GetDefaultAttackInfo(0);
	if (attackinfo) {
		for (local i = ENUM_ELEMENT_FIRE; i < ENUM_ELEMENT_NONE; i++)
		if (attackinfo.isValidElement(i)) {
			element = i;
			break;
		}
	}
	return element;
}