
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_WIN85")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_WIN85")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_WIN85")
}
function sq_AddEffect(appendage)
{

	//appendage.sq_AddEffectFront("passiveobject/zrr_skill/atmage/animation/atfinaltempest/finaltempest_holdbody.ani");
	//appendage.sq_AddEffectBack("passiveobject/zrr_skill/atmage/animation/atfinaltempest/finaltempest_holdfloor.ani");
}

function drawAppend_appendage_WIN85(appendage, isOver, x, y, isFlip) {
	if (!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}

	local anif = appendage.getVar().GetAnimationMap("finaltf", "passiveobject/zrr_skill/atmage/animation/atfinaltempest/finaltempest_holdbody.ani");
	local anib = appendage.getVar().GetAnimationMap("finaltb", "passiveobject/zrr_skill/atmage/animation/atfinaltempest/finaltempest_holdfloor.ani");

	if (anif && isOver) {
		sq_AnimationProc(anif);
		sq_drawCurrentFrame(anif, x, y, isFlip);
	}
	else if (anib && !isOver) {
		sq_AnimationProc(anib);
		sq_drawCurrentFrame(anib, x, y, isFlip);
	}
}

function proc_appendage_WIN85(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj || sourceObj.getState() == STATE_STAND) 
    {
		appendage.setValid(false);
		return;
	}
}



function onStart_appendage_WIN85(appendage)
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
}

