
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_SHAOWAREA_ENEMY")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_SHAOWAREA_ENEMY")
}

function sq_AddEffect(appendage)
{
}


function proc_appendage_SHAOWAREA_ENEMY(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
//    parentObj.setCurrentPos(parentObj.getXPos(),parentObj.getYPos(),100);
	if(!sourceObj || !parentObj || sourceObj.getState() == STATE_STAND) 
    {
		appendage.setValid(false);
		return;
	}

 
}



function onStart_appendage_SHAOWAREA_ENEMY(appendage)
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

