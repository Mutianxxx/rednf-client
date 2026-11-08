
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_HOTLOVE_FRIEND")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_HOTLOVE_FRIEND")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_HOTLOVE_FRIEND")
}



function sq_AddEffect(appendage)
{
	//appendage.sq_AddEffectBack("character/mage/animation/ani_als/hotlove/hotloveenchanbuff_roof_00.ani");
}

function drawAppend_appendage_HOTLOVE_FRIEND(appendage, isOver, x, y, isFlip) {
	if (!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!parentObj) {
		//appendage.setValid(false);
		return;
	}

	local anib = appendage.getVar().GetAnimationMap("hotlovefb", "character/mage/animation/ani_als/hotlove/hotloveenchanbuff_roof_00.ani");

	if (anib && !isOver) {
		sq_AnimationProc(anib);
		sq_drawCurrentFrame(anib, x, y, isFlip);
	}
}

function proc_appendage_HOTLOVE_FRIEND(appendage)
{
	if(!appendage) {
		return;		
	}
	local parentObj = appendage.getParent();

	if (!parentObj) {
		//appendage.setValid(false);
		return;
	}

}



function onStart_appendage_HOTLOVE_FRIEND(appendage)
{
}

