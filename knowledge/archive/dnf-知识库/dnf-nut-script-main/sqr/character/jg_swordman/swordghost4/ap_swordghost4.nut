function sq_AddFunctionName(appendage) {
	appendage.sq_AddFunctionName("proc", "proc_appendage_swordghost4")
	appendage.sq_AddFunctionName("prepareDraw", "prepareDraw_appendage_swordghost4")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_swordghost4")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_swordghost4")
	appendage.sq_AddFunctionName("isEnd", "isEnd_appendage_swordghost4")
}

function sq_AddEffect(appendage) {
	if (!appendage) return;
}

function proc_appendage_swordghost4(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();

	if (!obj) {
		appendage.setValid(false);
		return;
	}

	local time = appendage.getTimer().Get();

	local t = appendage.getVar().get_timer_vector(0);
	local obj = sq_GetCNRDObjectToSQRCharacter(obj);
	if (!t) return;

	if (t.isOnEvent(time) == true) {

		//particleCreater.Restart(0);
		//particleCreater.SetPos(x, y, z);

		//sq_AddParticleObject(obj, particleCreater);
		setSwordGhostEnergyDec(obj, 1);
	}

}

function onStart_appendage_swordghost4(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();

	if (!obj) {
		appendage.setValid(false);
		return;
	}

	local obj = sq_GetCNRDObjectToSQRCharacter(obj);
	initGetVarTimer(appendage, 1, sq_GetLevelData(obj, 123, 2, sq_GetSkillLevel(obj, 123)), -1);

}

function prepareDraw_appendage_swordghost4(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();
}

function onEnd_appendage_swordghost4(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();

}

function isEnd_appendage_swordghost4(appendage) {

	return false;
}