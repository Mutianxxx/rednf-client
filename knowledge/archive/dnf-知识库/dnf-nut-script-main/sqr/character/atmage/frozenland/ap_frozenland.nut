
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_Frozenland")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_Frozenland")
}
function sq_AddEffect(appendage)
{
}

function proc_appendage_Frozenland(appendage)
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


function onStart_appendage_Frozenland(appendage)
{
	if(!appendage) {
		return;
	}
	
}


