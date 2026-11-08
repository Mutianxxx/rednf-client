
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BLOODHIT2")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BLOODHIT2")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BLOODHIT2")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_BLOODHIT2(appendage)
{
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
    sq_SetCustomRotate(parentObj,-0.0 );
    gbl_HoldAndDelayEffectSetByAppendageEnd(appendage);
    
}

function proc_appendage_BLOODHIT2(appendage)
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
    local currentAni = sq_GetCurrentAnimation(parentObj);
    currentAni.setEffectLayer(true, GRAPHICEFFECT_NONE, true, sq_RGB(0, 0, 0), sq_ALPHA(255), true, false);
    gbl_HoldAndDelayEffectSetByAppendageLoop(appendage);
}



function onStart_appendage_BLOODHIT2(appendage)
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

