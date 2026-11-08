
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_SorceressBuffSelf")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_SorceressBuffSelf")
}


function drawAppend_appendage_SorceressBuffSelf(appendage, isOver, x, y, isFlip) {
	if (!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}

	local anif = appendage.getVar().GetAnimationMap("sorceressf", "character/mage/animation/ani_als/forbiddencurse/aura_buff_loop_00.ani");

	if (anif && isOver) {
		sq_AnimationProc(anif);
		sq_drawCurrentFrame(anif, x, y, isFlip);
	}
}

function proc_appendage_SorceressBuffSelf(appendage)
{
	if(!appendage) {
		return;		
	}

	local obj = appendage.getParent();
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();	

	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
}



