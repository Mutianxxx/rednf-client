
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_zealoffaith_friend")
	appendage.sq_AddFunctionName("proc", "proc_appendage_zealoffaith_friend")
}

function drawAppend_appendage_zealoffaith_friend(appendage, isOver, x, y, isFlip)
{
	if (!appendage) {
		return;
	}
	local obj = appendage.getParent();
	
	if (!obj) {
		appendage.setValid(false);
		return;
	}

	local backAni = appendage.getVar().GetAnimationMap("zealoffaithb", "character/priest/seducer/effect/animation/atzealoffaith/zealoffaith_cross.ani");
	local frontAni = appendage.getVar().GetAnimationMap("zealoffaithf", "character/priest/seducer/effect/animation/atzealoffaith/zealoffaith_light.ani");

	if (frontAni && isOver) {
		sq_AnimationProc(frontAni);
		sq_drawCurrentFrame(frontAni, x, y, isFlip);
	}	
	else if (backAni && !isOver) {
		sq_AnimationProc(backAni);
		sq_drawCurrentFrame(backAni, x, y, isFlip);
	}
}


function proc_appendage_zealoffaith_friend(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if(!sourceObj || !parentObj) 
	{
		appendage.setValid(false);
		return;
	}
	if(!sq_IsInBattle())
	{
		appendage.setValid(false);
	}
}

