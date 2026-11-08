
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_CANCEL")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_CANCEL")
}

function sq_AddEffect(appendage)
{
}

function proc_appendage_CANCEL(appendage)
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



function onStart_appendage_CANCEL(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

}

