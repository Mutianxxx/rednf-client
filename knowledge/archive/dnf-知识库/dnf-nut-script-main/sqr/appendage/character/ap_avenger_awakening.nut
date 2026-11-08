function sq_AddFunctionName(appendage) {
	appendage.sq_AddFunctionName("proc", "proc_appendage_avenger_awakening")
	appendage.sq_AddFunctionName("prepareDraw", "prepareDraw_appendage_avenger_awakening")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_avenger_awakening")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_avenger_awakening")
	appendage.sq_AddFunctionName("isEnd", "isEnd_appendage_avenger_awakening")
	appendage.sq_AddFunctionName("onSetHp", "onSetHp_appendage_avenger_awakening")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_avenger_awakening")
}

function drawAppend_appendage_avenger_awakening(appendage, isOver, x, y, isFlip) {
	if (!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}

	local ani = appendage.getVar().GetAnimationMap("avenger_awakening", "Character/Priest/Effect/Animation/ScytheMastery/1_aura_normal.ani");
	if (ani && isOver) {
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani, x, y, isFlip);
	}
}

function onSetHp_appendage_avenger_awakening(appendage, hp, attacker) {
	if (!appendage) {
		return hp;
	}
	if(!sq_IsInBattle()){
		return hp;
	}
	local obj = appendage.getParent();
	if (!obj) {
		return hp;
	}
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	if (!sqrChr.isMyControlObject()) {
		return hp;
	}
	local currentHp = hp;
	local orghp = appendage.sq_var.get_vector(3);

	if (attacker) {
		local attackInfo = sq_GetCurrentAttackInfo(attacker);
		if (attackInfo) {
			if (attackInfo.isIgnoreDieHard_)
				return hp;
		}
	}
	if (currentHp <= 0) {
		appendage.sq_var.set_vector(0, 0);
		return orghp;
	}
	return currentHp;
};

function onStart_appendage_avenger_awakening(appendage) {
	if (!appendage) {
		return;
	}
	local obj = appendage.getParent();
	if (!obj)
		return;
	obj.setObjectHeight(-1);
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	if (!sqrChr)
		return;
	sqrChr.setHp(sqrChr.getHpMax(), null, true);
	sqrChr.sq_SetSoundTagCreatureCommand("PR_DGUARDIAN_CMD_PRT");
	sqrChr.sq_SetSoundTagLackMp("PR_DGUARDIAN_NOMANA");
	sqrChr.sq_SetSoundTagCoolTime("PR_DGUARDIAN_COOLTIME");
	sqrChr.sq_SetSoundTagBackStepStart("PR_DGUARDIAN_BSTEP");
	sqrChr.sq_SetSoundTagThrowItem("PR_DGUARDIAN_BSTEP");
};

function onEnd_appendage_avenger_awakening(appendage) {
	if (!appendage) {
		return;
	}
	if(!sq_IsInBattle()){
		appendage.setValid(false);
		return;
	}
	local obj = appendage.getParent();
	if (!obj) {
		appendage.setValid(false);
		return;
	}
	obj.setObjectHeight(-1);
	local hpmaxup = appendage.sq_getHpMaxUp("HpMaxUp");
	if (hpmaxup) {
		if (hpmaxup.isValid()) {
			hpmaxup.setValid(false);
		}
	}
	local orghp = appendage.sq_var.get_vector(3);
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	if (!sqrChr)
		return;
	sq_SetCustomDamageType(sqrChr, false, 0);
	sqrChr.setHp(orghp, null, true);
	sqrChr.sq_SetSoundTagCreatureCommand("PR_CMD_PET");
	sqrChr.sq_SetSoundTagLackMp("PR_NOMANA");
	sqrChr.sq_SetSoundTagCoolTime("PR_COOLTIME");
	sqrChr.sq_SetSoundTagBackStepStart("PR_BSTEP");
	sqrChr.sq_SetSoundTagThrowItem("PR_THROW");
};



function isEnd_appendage_avenger_awakening(appendage) {
	if (!appendage) {
		return true;
	}
	if(!sq_IsInBattle()){
		return true;
	}
	local timer = appendage.getTimer().Get();

	local maxT = appendage.sq_var.get_vector(0);
	local doomshp = appendage.sq_var.get_vector(1);

	if (timer >= maxT || doomshp <= 0) {

		return true;
	}

	return false;
};
