function sq_AddFunctionName(appendage) {
	appendage.sq_AddFunctionName("proc", "proc_appendage_buff_ghost")
	appendage.sq_AddFunctionName("prepareDraw", "prepareDraw_appendage_buff_ghost")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_buff_ghost")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_buff_ghost")
}

function sq_AddEffect(appendage) {
	if (!appendage) return;
}

function drawAppend_appendage_buff_ghost(appendage, isOver, x, y, isFlip) {
	if (!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}

	local anif = appendage.getVar().GetAnimationMap("spiritcf", "character/swordman/effect/animation/spiritconversion/buff_loop.ani");
	local anib = appendage.getVar().GetAnimationMap("spiritcb", "character/swordman/effect/animation/spiritconversion/buff_effect_l_00.ani");

	if (anif && isOver) {
		sq_AnimationProc(anif);
		sq_drawCurrentFrame(anif, x, y + sq_GetObjectHeight(parentObj) / 5, isFlip);
	}
	else if (anib && !isOver) {
		sq_AnimationProc(anib);
		sq_drawCurrentFrame(anib, x, y, isFlip);
	}
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

}

function prepareDraw_appendage_buff_ghost(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();
}