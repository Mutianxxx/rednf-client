function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_summonmonsterreckless")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_summonmonsterreckless")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_summonmonsterreckless")
}

function proc_appendage_summonmonsterreckless(appendage)
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


function onStart_appendage_summonmonsterreckless(appendage)
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


function onEnd_appendage_summonmonsterreckless(appendage)
{
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
    
}
