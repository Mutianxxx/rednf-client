
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_Tepes")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_Tepes")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_Tepes")
}

function sq_AddEffect(appendage)
{
}



function onEnd_appendage_Tepes(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
}


function proc_appendage_Tepes(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
    parentObj = sq_GetCNRDObjectToActiveObject(parentObj);
				
	if(!sourceObj || !parentObj || sourceObj.getState() != STATE_BLOODSONG) 
    {
		appendage.setValid(false);
		return;
	}
    local currentAni = sq_GetCurrentAnimation(parentObj);
    currentAni.setEffectLayer(true, GRAPHICEFFECT_NONE, true, sq_RGB(0, 0, 0), sq_ALPHA(255), true, false);
    gbl_HoldAndDelayEffectSetDownByAppendageLoop(appendage);
//    local currentAni = sq_GetCurrentAnimation(parentObj);
//    currentAni.setEffectLayer(true, GRAPHICEFFECT_NONE, true, sq_RGB(0, 0, 0), sq_ALPHA(255), true, false);


}



function onStart_appendage_Tepes(appendage)
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

