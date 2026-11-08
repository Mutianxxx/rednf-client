function setActiveStatus_Thief(obj, activeStatus, power) {
	createDaThiefRateByTargetAndID(obj, obj, 1, power, 0, 1, 0);
	//    outPut("dummy/dummy.txt","active = " + activeStatus + " power =" + power + "\n");
	return 1;
}

function onClosePopupWindow_Thief(obj, popupType, windowTileType) {
	if (!obj) return;

}

function setEnableCancelSkill_Thief(P17_Ie67RvIkHnpfoMfPp0, XfsYmB3qtYof_mmblqAAafN) {
	if (!P17_Ie67RvIkHnpfoMfPp0) return false;
	if (!P17_Ie67RvIkHnpfoMfPp0.isMyControlObject()) return false;
	if (!XfsYmB3qtYof_mmblqAAafN) return true;
	P17_Ie67RvIkHnpfoMfPp0.setSkillCommandEnable(220, XfsYmB3qtYof_mmblqAAafN);
	P17_Ie67RvIkHnpfoMfPp0.setSkillCommandEnable(221, XfsYmB3qtYof_mmblqAAafN);
	P17_Ie67RvIkHnpfoMfPp0.setSkillCommandEnable(222, XfsYmB3qtYof_mmblqAAafN);
	P17_Ie67RvIkHnpfoMfPp0.setSkillCommandEnable(223, XfsYmB3qtYof_mmblqAAafN);
	P17_Ie67RvIkHnpfoMfPp0.setSkillCommandEnable(224, XfsYmB3qtYof_mmblqAAafN);
	P17_Ie67RvIkHnpfoMfPp0.setSkillCommandEnable(225, XfsYmB3qtYof_mmblqAAafN);
	return true;
}

function onChangeSkillEffect_Thief(zebrUf85bpwk, Fp6rhQKtOvlY, TMJNfY3L4tl) {
	if (!zebrUf85bpwk) return;
	switch (Fp6rhQKtOvlY) {
	case 224:
		local UPEZnSzjrt4aFf = TMJNfY3L4tl.readWord();
		switch (UPEZnSzjrt4aFf) {
		case 1:
			local aNYI5nmGqumVvgiY = sq_GetCNRDObjectToActiveObject(sq_GetObject(zebrUf85bpwk, TMJNfY3L4tl.readDword(), TMJNfY3L4tl.readDword()));
			if (aNYI5nmGqumVvgiY.isDead()) return;
			local OCFKys9S_yL = CNSquirrelAppendage.sq_AppendAppendage(aNYI5nmGqumVvgiY, aNYI5nmGqumVvgiY, 224, true, "character/new_thief/appendage/ap_monster_nicolas.nut", false);
			CNSquirrelAppendage.sq_Append(OCFKys9S_yL, aNYI5nmGqumVvgiY, aNYI5nmGqumVvgiY, false);

			OCFKys9S_yL.getVar("sqrChr").clear_obj_vector();
			OCFKys9S_yL.getVar("sqrChr").push_obj_vector(zebrUf85bpwk);
			break;
		case 2:
			local aNYI5nmGqumVvgiY = sq_GetCNRDObjectToActiveObject(sq_GetObject(zebrUf85bpwk, TMJNfY3L4tl.readDword(), TMJNfY3L4tl.readDword()));
			if (aNYI5nmGqumVvgiY.isDead()) return;
			if (aNYI5nmGqumVvgiY.isMyControlObject()) {
				local KB2Bn0UZWmBEcV6oIluSgBuv = sq_GetGlobalIntVector();
				sq_IntVectorClear(KB2Bn0UZWmBEcV6oIluSgBuv);
				sq_IntVectorPush(KB2Bn0UZWmBEcV6oIluSgBuv, 7);
				sq_AddSetStatePacketActiveObject(aNYI5nmGqumVvgiY, 8, KB2Bn0UZWmBEcV6oIluSgBuv, STATE_PRIORITY_USER);
			}
			break;
		case 3:
			local aNYI5nmGqumVvgiY = sq_GetCNRDObjectToActiveObject(sq_GetObject(zebrUf85bpwk, TMJNfY3L4tl.readDword(), TMJNfY3L4tl.readDword()));
			if (aNYI5nmGqumVvgiY.isDead()) return;
			sq_SetCurrentDirection(aNYI5nmGqumVvgiY, zebrUf85bpwk.getDirection());
			sq_MoveToNearMovablePos(aNYI5nmGqumVvgiY, sq_GetDistancePos(zebrUf85bpwk.getXPos(), zebrUf85bpwk.getDirection(), 100), zebrUf85bpwk.getYPos(), 0, zebrUf85bpwk.getXPos(), zebrUf85bpwk.getYPos(), 0, 100, -1, 5);
			sq_AddDrawOnlyAniFromParent(aNYI5nmGqumVvgiY, "monster/newmonsters/thief/nicolas/animation/effect/blackarachnia/start_smokenormal.ani", 0, -1, 0);
			sq_CreateDrawOnlyObject(aNYI5nmGqumVvgiY, "monster/newmonsters/thief/nicolas/animation/effect/blackarachnia/start_blackground.ani", ENUM_DRAWLAYER_BOTTOM, true);
			break;
		}
		break;
	}
}

function getRestAni_Thief(obj) {
	if (!obj) return null;

	local restani = obj.sq_GetRestAni();
	local kunoich = obj.sq_GetSkillLevel(63);

	if (kunoich > 0) {
		restani = obj.sq_GetCustomAni(CUSTOM_ANI_GROWTYPE_KUNOICH);
	}
	return restani;
}

function getStayAni_Thief(obj) {
	if (!obj) return null;

	local animation = obj.sq_GetStayAni();

	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut") == true) {
		animation = obj.sq_GetCustomAni(CUSTOM_ANI_SWORDOFKUSANAGI_STAY);
	}
	return animation;
}

function getMoveAni_Thief(obj) {
	if (!obj) return null;

	local animation = obj.sq_GetMoveAni();

	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut") == true) {
		animation = obj.sq_GetCustomAni(CUSTOM_ANI_SWORDOFKUSANAGI_MOVE);
	}
	return animation;
}

function getDashAni_Thief(obj) {
	if (!obj) return null;

	local animation = obj.sq_GetDashAni();

	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut") == true) {
		animation = obj.sq_GetCustomAni(CUSTOM_ANI_SWORDOFKUSANAGI_DASH);
	}
	return animation;
}

function getDashAttackAni_Thief(obj) {
	if (!obj) return null;

	local animation = obj.sq_GetDashAttackAni();

	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut") == true) {
		animation = obj.sq_GetCustomAni(CUSTOM_ANI_SWORDOFKUSANAGI_DASHATTACK);
	}
	return animation;
}

function getDashAttackInfo_Thief(obj) {
	if (!obj) return null;

	local attackInfo = obj.sq_GetDashAttackInfo();

	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut") == true) {
		attackInfo = sq_GetCustomAttackInfo(obj, 6);
	}
	return attackInfo;
}

function getJumpAni_Thief(obj) {
	if (!obj) return null;

	local animation = obj.sq_GetJumpAni();

	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut") == true) {
		animation = obj.sq_GetCustomAni(CUSTOM_ANI_SWORDOFKUSANAGI_JUMP);
	}
	return animation;
}

function getAttackAni_Thief(obj, index) {
	if (!obj) return null;

	local animation = obj.sq_GetAttackAni(index);

	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut") == true) {
		animation = obj.sq_GetCustomAni(CUSTOM_ANI_SWORDOFKUSANAGI_ATTACK1 + index);
	}
	if (isAssassin(obj)) {
		animation = obj.sq_GetCustomAni(CUSTOM_ANI_ASSASSIN_NORMALATTACK + index);
	} else {
		if (index == 15) {
			animation = obj.sq_GetCustomAni(72);
		}
	}
	return animation;
}

function getDefaultAttackInfo_Thief(obj, index) {
	if (!obj) return null;

	local attackInfo = obj.sq_GetDefaultAttackInfo(index);

	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut") == true) {
		attackInfo = sq_GetCustomAttackInfo(obj, 2);
	}
	if (isAssassin(obj)) {
		attackInfo = sq_GetCustomAttackInfo(obj, ATTACKINFO_ASSASSIN_NORMALATTACK + index);
	}
	return attackInfo;
}

function getAttackCancelStartFrameSize_Thief(obj) {
	if (!obj) return null;

	local maxAttackNumber = obj.sq_GetAttackCancelStartFrameSize();

	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut") == true) {
		maxAttackNumber = 1;
	}
	if (isAssassin(obj)) {
		maxAttackNumber = 3;
	}
	return maxAttackNumber;
}

function getJumpAttackAni_Thief(obj) {
	if (!obj) return null;

	local animation = obj.sq_GetJumpAttackAni();

	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut") == true) {
		animation = obj.sq_GetCustomAni(CUSTOM_ANI_SWORDOFKUSANAGI_JUMPATTACK);
	}
	return animation;
}

function getJumpAttackInfo_Thief(obj) {
	if (!obj) return null;

	local attackInfo = obj.sq_GetJumpAttackInfo();

	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut") == true) {
		attackInfo = sq_GetCustomAttackInfo(obj, 2);
	}
	return attackInfo;
}

function DeitiesRebirth(obj) {
	if (!obj) return;

	local SkillIndex = obj.getCurrentSkillIndex(); //????????????
	local state = obj.sq_GetState(); //????????
	if (sq_getGrowType(obj) == 3) {
		if (SkillIndex == -1 && obj.getVar("1").getInt(0) != 1) //????????
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(SKILL_DEITIESREBIRTH);
			obj.sq_AddSetStatePacket(STATE_DEITIESREBIRTH, STATE_PRIORITY_USER, true);
			obj.getVar("1").setInt(0, 1);
		}

		if (state == STATE_FIREHIDE) {
			obj.getVar("1").setInt(0, 0);
		}
	}
}

function procAppend_LeaveTrace(obj) {
	if (!obj) return;

	local appendage = obj.GetSquirrelAppendage("character/thief/3_kunoich/leavetrace/ap_leavetrace.nut");

	if (appendage) {
		if (appendage.isValid()) {
			local loadSlot = obj.sq_GetSkillLoad(88);
			if (loadSlot) {
				local remain_number = loadSlot.getRemainLoadNumber();
				if (remain_number > 0) {
					LeaveTrace(obj);
				}
			}
		}
	}
}

function LeaveTrace(obj) {
	if (!obj) return false;

	local state = obj.sq_GetState();
	local zPos = sq_GetZPos(obj);
	if (state == STATE_FLAMEBALL || state == STATE_ILUSIONSHURIKEN || state == STATE_FLAMETORNADO || state == STATE_BIGKUNAI || state == STATE_MIGAWARI || state == STATE_SKYROADS || state == STATE_GASOLINEFIRE || state == STATE_FLAMEFLOWER || state == STATE_DOOMFIELD || state == STATE_YAMATAOROCHI || state == STATE_FUUMASHURIKEN || state == STATE_AMATERAS) {
		CommonEnableLeaveTrace(obj, SKILL_FLAMEBALL, STATE_FLAMEBALL); //???? ?? ?????????
		CommonEnableLeaveTrace(obj, SKILL_ILUSIONSHURIKEN, STATE_ILUSIONSHURIKEN); //??????????????
		CommonEnableLeaveTrace(obj, SKILL_WOODMOVE, STATE_WOODMOVE); //???? : ?????????
		CommonEnableLeaveTrace(obj, SKILL_FLAMETORNADO, STATE_FLAMETORNADO); //???? ?? ju???
		CommonEnableLeaveTrace(obj, SKILL_BIGKUNAI, STATE_BIGKUNAI); //???? ?? ????????
		CommonEnableLeaveTrace(obj, SKILL_MIGAWARI, STATE_MIGAWARI); //???? : ??????
		CommonEnableLeaveTrace(obj, SKILL_SKYROADS, STATE_SKYROADS); //???? ?? ????
		CommonEnableLeaveTrace(obj, SKILL_GASOLINEFIRE, STATE_GASOLINEFIRE); //???? ?? ??chu??????
		CommonEnableLeaveTrace(obj, SKILL_FLAMEFLOWER, STATE_FLAMEFLOWER); //???? ?? ???????
		CommonEnableLeaveTrace(obj, SKILL_DOOMFIELD, STATE_DOOMFIELD); //???? ?? ?????????
		CommonEnableLeaveTrace(obj, SKILL_YAMATAOROCHI, STATE_YAMATAOROCHI); //????????
		CommonEnableLeaveTrace(obj, SKILL_FUUMASHURIKEN, STATE_FUUMASHURIKEN); //???? ?? ????????
		CommonEnableLeaveTrace(obj, SKILL_AMATERAS, STATE_AMATERAS); //???

		if (zPos > 0) {
			if (obj.sq_IsEnterSkill(SKILL_FLAMEBALL) != -1) {
				SetStateLeaveTrace(obj, SKILL_FLAMEBALL, STATE_FLAMEBALL, [1]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_ILUSIONSHURIKEN) != -1) {
				SetStateLeaveTrace(obj, SKILL_ILUSIONSHURIKEN, STATE_ILUSIONSHURIKEN, [1]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_WOODMOVE) != -1) {
				SetStateLeaveTrace(obj, SKILL_WOODMOVE, STATE_WOODMOVE, [1]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_BIGKUNAI) != -1) {
				SetStateLeaveTrace(obj, SKILL_BIGKUNAI, STATE_BIGKUNAI, [1]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_SKYROADS) != -1) {
				SetStateLeaveTrace(obj, SKILL_SKYROADS, STATE_SKYROADS, [1]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_GASOLINEFIRE) != -1) {
				SetStateLeaveTrace(obj, SKILL_GASOLINEFIRE, 6, [1, 0, 400]);
				obj.sq_PlaySound("R_TF_GASOLINEFIRE");
				if (obj.isMyControlObject()) {
					obj.sq_StartWrite();
					obj.sq_WriteDword(25); //???? ?? ??chu??????
					sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(sq_GetXPos(obj), obj.getDirection(), -180), sq_GetYPos(obj), 0);
				}
			}
			else if (obj.sq_IsEnterSkill(SKILL_FUUMASHURIKEN) != -1) {
				SetStateLeaveTrace(obj, SKILL_FUUMASHURIKEN, STATE_FUUMASHURIKEN, [1]);
			}
		}
		else {
			if (obj.sq_IsEnterSkill(SKILL_FLAMEBALL) != -1) {
				SetStateLeaveTrace(obj, SKILL_FLAMEBALL, STATE_FLAMEBALL, [0]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_ILUSIONSHURIKEN) != -1) {
				SetStateLeaveTrace(obj, SKILL_ILUSIONSHURIKEN, STATE_ILUSIONSHURIKEN, [0]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_WOODMOVE) != -1) {
				SetStateLeaveTrace(obj, SKILL_WOODMOVE, STATE_WOODMOVE, [0]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_FLAMETORNADO) != -1) {
				SetStateLeaveTrace(obj, SKILL_FLAMETORNADO, STATE_FLAMETORNADO, [0]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_BIGKUNAI) != -1) {
				SetStateLeaveTrace(obj, SKILL_BIGKUNAI, STATE_BIGKUNAI, [0]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_MIGAWARI) != -1) {
				SetStateLeaveTrace(obj, SKILL_MIGAWARI, STATE_MIGAWARI, [0]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_SKYROADS) != -1) {
				SetStateLeaveTrace(obj, SKILL_SKYROADS, STATE_SKYROADS, [0]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_GASOLINEFIRE) != -1) {
				SetStateLeaveTrace(obj, SKILL_GASOLINEFIRE, STATE_GASOLINEFIRE, [0]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_FLAMEFLOWER) != -1) {
				SetStateLeaveTrace(obj, SKILL_FLAMEFLOWER, STATE_FLAMEFLOWER, [0]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_DOOMFIELD) != -1) {
				SetStateLeaveTrace(obj, SKILL_DOOMFIELD, STATE_DOOMFIELD, [0]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_YAMATAOROCHI) != -1) {
				SetStateLeaveTrace(obj, SKILL_YAMATAOROCHI, STATE_YAMATAOROCHI, [0]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_FUUMASHURIKEN) != -1) {
				SetStateLeaveTrace(obj, SKILL_FUUMASHURIKEN, STATE_FUUMASHURIKEN, [0]);
			}
			else if (obj.sq_IsEnterSkill(SKILL_AMATERAS) != -1) {
				SetStateLeaveTrace(obj, SKILL_AMATERAS, STATE_AMATERAS, [0]);
			}
		}
	}
	return true;
}

function CommonEnableLeaveTrace(obj, skillindex, state) {
	if (obj.sq_GetState() == state) return false;
	obj.setSkillCommandEnable(skillindex, true);
	return true;
}

function SetJumpSkillState(obj, skillindex, state) {

	local iEnterSkill = obj.sq_IsEnterSkill(skillindex);
	if (iEnterSkill == -1) return false;
	if (obj.sq_GetState() == state) //üòö¢Ó×îñßÒ÷¾æ¨îîóÑÝïÎò ÛÁò­ÙíùÚêõûùÔÒËÁÐüÒö
	return false;
	if (obj.sq_IsUseSkill(skillindex)) //÷÷Ó¨Ó×îñÐüÒöãÀÜúÊ¦éÄ£¨cd ÕÀÙÄÔõðÉËì£©
	{
		if (skillindex == SKILL_GASOLINEFIRE) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(400);
			obj.sq_AddSetStatePacket(STATE_JUMP, STATE_PRIORITY_IGNORE_FORCE, true);
			obj.sq_PlaySound("R_TF_GASOLINEFIRE");
			if (obj.isMyControlObject()) {
				obj.sq_StartWrite();
				obj.sq_WriteDword(25);
				sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(sq_GetXPos(obj), obj.getDirection(), -180), sq_GetYPos(obj), 0);
			}
		}
		else {
			obj.sq_IntVectClear(); //?ð¶ú¾Õá£¨ßÒ÷¾£©
			obj.sq_IntVectPush(1);
			obj.sq_AddSetStatePacket(state, STATE_PRIORITY_USER, true); //àâöÇÐüÒößÒ÷¾
		}
		return true;

	}

}

function SetStateLeaveTrace(obj, skillindex, state, Arr) {
	if (obj.sq_GetState() == state) return false;
	if (obj.sq_IsUseSkill(skillindex)) {

		if (skillindex == SKILL_WOODMOVE) {
			local soften_number = sq_GetLevelData(obj, SKILL_LEAVETRACE, 0, sq_GetSkillLevel(obj, SKILL_LEAVETRACE));
			local skill_level = sq_GetSkillLevel(obj, 123);
			if (skill_level > 0) {
				soften_number = soften_number + sq_GetLevelData(obj, 123, 1, skill_level);
			}
			soften_number = soften_number.tointeger();
			local loadSlot = obj.sq_GetSkillLoad(88);
			if (loadSlot) {
				local remain_number = loadSlot.getRemainLoadNumber();
				if (remain_number < soften_number) {
					loadSlot.increaseLoadCount(1);
				}
			}
		}

		obj.sq_IntVectClear();
		if (Arr.len() < 1) {
			obj.sq_AddSetStatePacket(state, STATE_PRIORITY_USER, true);
			return true;
		}
		else {
			foreach(sub in Arr)
			obj.sq_IntVectPush(sub);
			obj.sq_AddSetStatePacket(state, STATE_PRIORITY_USER, true);
			LeaveTrace_Decrease(obj);
			return true;
		}
	}
}

function LeaveTrace_Decrease(obj) {
	local loadSlot = obj.sq_GetSkillLoad(88);
	if (loadSlot) {
		local remain_number = loadSlot.getRemainLoadNumber();
		if (remain_number > 0) {
			loadSlot.decreaseLoadCount(1);
			loadSlot.setStartCool();
		}
	}
}

function LeaveTrace_Body(obj) {
	local parentChr = sq_ObjectToSQRCharacter(obj.getTopCharacter());
	local pAni = obj.getCurrentAnimation();
	if (parentChr.sq_IsEnterSkill(SKILL_FLAMEBALL) != -1 && !sq_GetSkill(parentChr, SKILL_FLAMEBALL).isInCoolTime()) {
		pAni.setRGBA(255, 255, 255, 254);
	}
	else if (parentChr.sq_IsEnterSkill(SKILL_ILUSIONSHURIKEN) != -1 && !sq_GetSkill(parentChr, SKILL_ILUSIONSHURIKEN).isInCoolTime()) {
		pAni.setRGBA(255, 255, 255, 254);
	}
	else if (parentChr.sq_IsEnterSkill(SKILL_WOODMOVE) != -1 && !sq_GetSkill(parentChr, SKILL_WOODMOVE).isInCoolTime()) {
		pAni.setRGBA(255, 255, 255, 254);
	}
	else if (parentChr.sq_IsEnterSkill(SKILL_FLAMETORNADO) != -1 && !sq_GetSkill(parentChr, SKILL_FLAMETORNADO).isInCoolTime()) {
		pAni.setRGBA(255, 255, 255, 254);
	}
	else if (parentChr.sq_IsEnterSkill(SKILL_BIGKUNAI) != -1 && !sq_GetSkill(parentChr, SKILL_BIGKUNAI).isInCoolTime()) {
		pAni.setRGBA(255, 255, 255, 254);
	}
	else if (parentChr.sq_IsEnterSkill(SKILL_MIGAWARI) != -1 && !sq_GetSkill(parentChr, SKILL_MIGAWARI).isInCoolTime()) {
		pAni.setRGBA(255, 255, 255, 254);
	}
	else if (parentChr.sq_IsEnterSkill(SKILL_SKYROADS) != -1 && !sq_GetSkill(parentChr, SKILL_SKYROADS).isInCoolTime()) {
		pAni.setRGBA(255, 255, 255, 254);
	}
	else if (parentChr.sq_IsEnterSkill(SKILL_GASOLINEFIRE) != -1 && !sq_GetSkill(parentChr, SKILL_GASOLINEFIRE).isInCoolTime()) {
		pAni.setRGBA(255, 255, 255, 254);
	}
	else if (parentChr.sq_IsEnterSkill(SKILL_FLAMEFLOWER) != -1 && !sq_GetSkill(parentChr, SKILL_FLAMEFLOWER).isInCoolTime()) {
		pAni.setRGBA(255, 255, 255, 254);
	}
	else if (parentChr.sq_IsEnterSkill(SKILL_DOOMFIELD) != -1 && !sq_GetSkill(parentChr, SKILL_DOOMFIELD).isInCoolTime()) {
		pAni.setRGBA(255, 255, 255, 254);
	}
	else if (parentChr.sq_IsEnterSkill(SKILL_YAMATAOROCHI) != -1 && !sq_GetSkill(parentChr, SKILL_YAMATAOROCHI).isInCoolTime()) {
		pAni.setRGBA(255, 255, 255, 254);
	}
	else if (parentChr.sq_IsEnterSkill(SKILL_FUUMASHURIKEN) != -1 && !sq_GetSkill(parentChr, SKILL_FUUMASHURIKEN).isInCoolTime()) {
		pAni.setRGBA(255, 255, 255, 254);
	}
	else if (parentChr.sq_IsEnterSkill(SKILL_AMATERAS) != -1 && !sq_GetSkill(parentChr, SKILL_AMATERAS).isInCoolTime()) {
		pAni.setRGBA(255, 255, 255, 254);
	}
}

function als_ani(obj, aniFilename, disX, disY, disZ, imgangle, imgRate, Parent, layer, SpeedRate) {
	local angle = imgangle;
	local ani = sq_CreateAnimation("", aniFilename);
	sq_SetfRotateAngle(ani, sq_ToRadian(-angle.tofloat()));

	local sizeRate = imgRate;
	local size = sizeRate.tofloat() / 100.0;
	ani.setImageRateFromOriginal(size, size);
	ani.setAutoLayerWorkAnimationAddSizeRate(size);

	ani.setSpeedRate(100.0 * SpeedRate);

	local pooledObj = sq_CreatePooledObject(ani, true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());

	if (Parent == 1) {
		sq_moveWithParent(obj, pooledObj);
	}
	if (layer == 2) {
		sq_ChangeDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	}
	if (layer == 1) {
		sq_ChangeDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	}
	if (layer == 0) {
		sq_ChangeDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	}
	sq_AddObject(obj, pooledObj, 2, false);
	obj.getVar("aniobj").push_obj_vector(pooledObj);
}

function remove_ani(obj) {
	local var = obj.getVar("aniobj");
	local max_aniObj = var.get_obj_vector_size();
	for (local i = 0; i < max_aniObj; i++) {
		local aniObj = var.get_obj_vector(i);
		if (aniObj) aniObj.setValid(false);
	}
	obj.getVar("aniobj").clear_obj_vector();
}

function setBellarceStand(obj) {
	//obj.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true);
}

function getBellacreObject(obj) {
	local bellacre = obj.getMyPassiveObject(25012, 0);
	if (bellacre) return bellacre;
	return null;
}

function isAssassin(obj) {
	local skillLevel = sq_GetSkillLevel(obj, SKILL_ASSASSIN);
	if (skillLevel > 0) {
		return true;
	}
	return false;
}

function procAppend_yingwuzhede(obj) {
	local state = sq_GetState(obj);
	if (state == 63) {
		local pAni = sq_GetCurrentAnimation(obj);
		local frmIndex = sq_GetAnimationFrameIndex(pAni);
	} else if (state == 62) {
		local subState = obj.getSkillSubState();
		if (subState == 0) {
			local pAni = sq_GetCurrentAnimation(obj);
			local frmIndex = sq_GetAnimationFrameIndex(pAni);
			if (frmIndex >= 4) {

				local pIntVec = sq_GetGlobalIntVector();
				sq_IntVectorClear(pIntVec);
				sq_IntVectorPush(pIntVec, 1);

				obj.addSetStatePacket(state, pIntVec, STATE_PRIORITY_USER, false, "");

			}
		} else if (subState == 2) {
			local pAni = sq_GetCurrentAnimation(obj);
			local frmIndex = sq_GetAnimationFrameIndex(pAni);
			if (frmIndex >= 4) {

				local pIntVec = sq_GetGlobalIntVector();
				sq_IntVectorClear(pIntVec);

				obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_USER, false, "");

			}
		}
	}

}

function checkOverItemObject_Thief(obj) {
	//return setOverItemObject(obj);
}

function procAppend_JumpSkillNi(obj) {
	if (obj.isMyControlObject() && (sq_getGrowType(obj) == 3)) {
		local state = obj.sq_GetState();
		local now_z = obj.getZPos();
		if (now_z > 10 && state == 0) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(90);
			obj.sq_AddSetStatePacket(6, STATE_PRIORITY_USER, true);
		}
		if (state == STATE_FLAMEBALL || state == STATE_ILUSIONSHURIKEN || state == STATE_FLAMETORNADO || state == STATE_BIGKUNAI || state == STATE_MIGAWARI || state == STATE_SKYROADS || state == STATE_GASOLINEFIRE || state == STATE_FLAMEFLOWER || state == STATE_DOOMFIELD || state == STATE_YAMATAOROCHI || state == STATE_FUUMASHURIKEN || state == STATE_AMATERAS) return false;
		if (state == 6 || state == 7 || now_z > 5) {
			CommonEnableLeaveTrace(obj, SKILL_BIGKUNAI, STATE_BIGKUNAI);
			SetJumpSkillState(obj, SKILL_BIGKUNAI, STATE_BIGKUNAI);
			//obj.setSkillCommandEnable(81, true);
			CommonEnableLeaveTrace(obj, SKILL_FLAMEBALL, STATE_FLAMEBALL);
			SetJumpSkillState(obj, SKILL_FLAMEBALL, STATE_FLAMEBALL);
			//obj.setSkillCommandEnable(5, true);
			CommonEnableLeaveTrace(obj, 5, 24);
			SetJumpSkillState(obj, 5, 24);
			//obj.setSkillCommandEnable(96, true);
			CommonEnableLeaveTrace(obj, SKILL_FLYINGSWALLOW, STATE_FLYINGSWALLOW);
			SetJumpSkillState(obj, SKILL_FLYINGSWALLOW, STATE_FLYINGSWALLOW);
			//obj.setSkillCommandEnable(98, true);
			CommonEnableLeaveTrace(obj, SKILL_FUUMASHURIKEN, STATE_FUUMASHURIKEN);
			SetJumpSkillState(obj, SKILL_FUUMASHURIKEN, STATE_FUUMASHURIKEN);
			//obj.setSkillCommandEnable(91, true);
			CommonEnableLeaveTrace(obj, SKILL_GASOLINEFIRE, STATE_GASOLINEFIRE);
			SetJumpSkillState(obj, SKILL_GASOLINEFIRE, STATE_GASOLINEFIRE);
			//obj.setSkillCommandEnable(82, true);
			CommonEnableLeaveTrace(obj, SKILL_ILUSIONSHURIKEN, STATE_ILUSIONSHURIKEN);
			SetJumpSkillState(obj, SKILL_ILUSIONSHURIKEN, STATE_ILUSIONSHURIKEN);
			//obj.setSkillCommandEnable(89, true);
			CommonEnableLeaveTrace(obj, SKILL_SKYROADS, STATE_SKYROADS);
			SetJumpSkillState(obj, SKILL_SKYROADS, STATE_SKYROADS);
			//obj.setSkillCommandEnable(83, true);
			CommonEnableLeaveTrace(obj, SKILL_WOODMOVE, STATE_WOODMOVE);
			SetJumpSkillState(obj, SKILL_WOODMOVE, STATE_WOODMOVE);
		}

	}
}

function createAssassinHitEffect_Slash_Horionzal(obj,posX,posY,posZ)
{

	local ani = sq_CreateAnimation("","common/hiteffect/animation/assassinhiteffect/bloodslashlarge" + 2 +".ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(posX ,posY + 1,posZ );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}

function sq_setDirectionToPosX(obj,posX)
{

	local x = posX;
	local parX = obj.getXPos();

	if (x > parX)
		obj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
	else
		obj.setCurrentDirection(ENUM_DIRECTION_LEFT);

}

function sq_IsLand(obj)
{
	return (obj.getZPos() <= 0);
}

function setClipWithLimit(startX,startY,endX,endY)
{
	if (endX > startX && endY > startY)
	{
		setClip(startX,startY,endX,endY);
	}else
	{
		setClip(0,0,0,0);
	}

}