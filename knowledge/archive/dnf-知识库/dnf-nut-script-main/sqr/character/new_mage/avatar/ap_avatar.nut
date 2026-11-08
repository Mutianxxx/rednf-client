
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_AVATAR")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_AVATAR")
}


function proc_appendage_AVATAR(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				

}



function onStart_appendage_AVATARD(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				

}

