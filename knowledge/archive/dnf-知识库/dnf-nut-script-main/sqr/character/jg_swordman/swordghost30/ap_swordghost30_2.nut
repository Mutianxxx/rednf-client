function sq_AddFunctionName(appendage) {
	appendage.sq_AddFunctionName("proc", "proc_appendage_buff_ghost")
	appendage.sq_AddFunctionName("prepareDraw", "prepareDraw_appendage_buff_ghost")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_buff_ghost")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_buff_ghost")
	appendage.sq_AddFunctionName("isEnd", "isEnd_appendage_buff_ghost")
}

function sq_AddEffect(appendage) {
	if (!appendage) return;
	appendage.sq_AddEffectFront("character/swordman/effect/animation/bladespirit/yasuo_obj_q_sub_00.ani")
	appendage.sq_AddEffectFront("character/swordman/effect/animation/bladespirit/yasuo_obj_q_sub_01.ani")

}

function proc_appendage_buff_ghost(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();

	if (!obj) {
		appendage.setValid(false);
		return;
	}

	local time = appendage.getTimer().Get();

	local x = obj.getXPos();
	local y = obj.getYPos();
	local z = obj.getZPos();

	local t = appendage.getVar().get_timer_vector(0);

	if (!t) return;

	if (t.isOnEvent(time) == true) {

		//sq_SendCreatePassiveObjectPacketPos(obj,24201, 0, x, y, z);

	}

	if (t.isEnd() == true) {
		appendage.setValid(false);
	}
}

function onStart_appendage_buff_ghost(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();

	if (!obj) {
		appendage.setValid(false);
		return;
	}

	initGetVarTimer(appendage, 1, 150, 90000);

}

function prepareDraw_appendage_buff_ghost(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();
}

function onEnd_appendage_buff_ghost(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();

}

// ??? ?? ??? ???
function isEnd_appendage_buff_ghost(appendage) {

	return false;
}