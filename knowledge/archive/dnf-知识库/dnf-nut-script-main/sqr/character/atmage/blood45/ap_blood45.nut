
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BLOOD45")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BLOOD45")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BLOOD45")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_BLOOD45(appendage)
{

    gbl_HoldAndDelayEffectSetByAppendageEnd(appendage);
    
}

function proc_appendage_BLOOD45(appendage)
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
//    gbl_HoldAndDelayEffectSetByAppendageLoop(appendage);
    gbl_HoldAndDelayEffectSetByAppendageLoopNoClear(appendage);
}



function onStart_appendage_BLOOD45(appendage)
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

