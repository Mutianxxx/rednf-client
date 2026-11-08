function sq_AddFunctionName(appendage) {
	appendage.sq_AddFunctionName("proc", "proc_appendage_buff_beidong_flag")
	appendage.sq_AddFunctionName("prepareDraw", "prepareDraw_appendage_buff_beidong_flag")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_buff_beidong_flag")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_buff_beidong_flag")
	appendage.sq_AddFunctionName("isEnd", "isEnd_appendage_buff_beidong_flag")
}

function sq_AddEffect(appendage) {
	if (!appendage) return;
}

function proc_appendage_buff_beidong_flag(appendage) {
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
	}

	if (t.isEnd() == true) {
		appendage.setValid(false);
	}
}

function onStart_appendage_buff_beidong_flag(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();

	if (!obj) {
		appendage.setValid(false);
		return;
	}

	initGetVarTimer(appendage, 1, 60, 90000);

}

function prepareDraw_appendage_buff_beidong_flag(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();
}

function onEnd_appendage_buff_beidong_flag(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();

}

function isEnd_appendage_buff_beidong_flag(appendage) {

	return false;
}