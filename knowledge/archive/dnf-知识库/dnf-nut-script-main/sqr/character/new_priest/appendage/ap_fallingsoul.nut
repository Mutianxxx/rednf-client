
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_fallingsoul")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_fallingsoul")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_fallingsoul")
}

function proc_appendage_fallingsoul(appendage)
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


function onStart_appendage_fallingsoul(appendage)
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


function onEnd_appendage_fallingsoul(appendage)
{
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
    
}
