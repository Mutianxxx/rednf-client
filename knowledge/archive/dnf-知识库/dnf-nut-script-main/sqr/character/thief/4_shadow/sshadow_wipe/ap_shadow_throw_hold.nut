
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ShadowWipe")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BShadowWipe")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_ShadowWipe")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_ShadowWipe(appendage)
{
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	sq_SetCustomRotate(parentObj,-0.0 );
	gbl_HoldAndDelayEffectSetByAppendageEnd(appendage);
	
}

function proc_appendage_ShadowWipe(appendage)
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
	gbl_HoldAndDelayEffectSetByAppendageLoop(appendage);
}



function onStart_appendage_BShadowWipe(appendage)
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

