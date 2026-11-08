
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_SPEEDSLADE")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_SPEEDSLADE")
}

function sq_AddEffect(appendage)
{
}


function proc_appendage_SPEEDSLADE(appendage)
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
    if (parentObj.getXPos() < sourceObj.getXPos() )
	{
        parentObj.setCurrentDirection(ENUM_DIRECTION_LEFT);
    }else{
        parentObj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
    }
}



function onStart_appendage_SPEEDSLADE(appendage)
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

