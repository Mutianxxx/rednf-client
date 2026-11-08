function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_edification")
	appendage.sq_AddFunctionName("proc", "proc_appendage_edification")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_edification")
}

function drawAppend_appendage_edification(appendage, isOver, x, y, isFlip)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
	
	if(isOver) 
	{
 		local ani = appendage.getVar().GetAnimationMap("edificationloop", "character/priest/effect/animation/atedification/edification_buff_loop_wind.ani");
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani, x, y, isFlip);
	}
}

function proc_appendage_edification(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
}

function onEnd_appendage_edification(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
	if (!sq_IsInBattle())
	{
		appendage.setValid(false);
		return;
	}
	if (parentObj.isDead()) 
	{
		appendage.setValid(false);
		return;
	}
	local edification_buff_end_wind = "character/priest/effect/animation/atedification/edification_buff_end_wind.ani";
	sq_AddDrawOnlyAniFromParent(parentObj,edification_buff_end_wind, 0, 1, 0);
	appendage.setValid(false);
}

