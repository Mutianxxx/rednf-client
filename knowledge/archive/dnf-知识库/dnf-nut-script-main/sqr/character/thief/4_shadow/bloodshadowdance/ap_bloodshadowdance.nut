
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BloodShadowDance")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BloodShadowDance")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BloodShadowDance")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_BloodShadowDance(appendage)
{
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	sq_SetCustomRotate(parentObj,-0.0 );
	gbl_HoldAndDelayEffectSetByAppendageEnd(appendage);
	
}

function proc_appendage_BloodShadowDance(appendage)
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
	gbl_HoldAndDelayEffectSetByAppendageLoopNoClear(appendage);
}



function onStart_appendage_BloodShadowDance(appendage)
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

