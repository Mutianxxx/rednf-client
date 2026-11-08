
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_NEWBLOODDOGHOLD")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_NEWBLOODDOGHOLD")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_NEWBLOODDOGHOLD")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_NEWBLOODDOGHOLD(appendage)
{

    gbl_HoldAndDelayEffectSetByAppendageEnd(appendage);
    
}

function proc_appendage_NEWBLOODDOGHOLD(appendage)
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
    gbl_HoldAndDelayEffectSetByAppendageLoop(appendage);
}



function onStart_appendage_NEWBLOODDOGHOLD(appendage)
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

