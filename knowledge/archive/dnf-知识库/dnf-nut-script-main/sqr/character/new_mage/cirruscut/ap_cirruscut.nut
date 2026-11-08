
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_CIRRUSCUT")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_CIRRUSCUT")
}

function sq_AddEffect(appendage)
{

}
function proc_appendage_CIRRUSCUT(appendage)
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
}



function onStart_appendage_CIRRUSCUT(appendage)
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

