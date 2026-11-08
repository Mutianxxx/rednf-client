function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_newstayjumpshoot")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_newstayjumpshoot")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_newstayjumpshoot")
}

function proc_appendage_newstayjumpshoot(appendage)
{
	if(!appendage) {
		appendage.setValid(false);
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


function onStart_appendage_newstayjumpshoot(appendage)
{
	if(!appendage) {
		appendage.setValid(false);
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(parentObj);
	sqrChr.getVar("stayjumpshoot").setBool(0, true);
}


function onEnd_appendage_newstayjumpshoot(appendage)
{
	if(!appendage) {
		appendage.setValid(false);
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(parentObj);
	sqrChr.getVar("stayjumpshoot").setBool(0, false);
	appendage.setValid(false);
}