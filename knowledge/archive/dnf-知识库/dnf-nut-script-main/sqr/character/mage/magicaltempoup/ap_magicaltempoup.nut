
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_magicaltempoup")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_magicaltempoup")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_magicaltempoup")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_magicaltempoup(appendage)
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
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	parentObj.getVar("isShowTime").setInt(0, 0);
}

function proc_appendage_magicaltempoup(appendage)
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



function onStart_appendage_magicaltempoup(appendage)
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

