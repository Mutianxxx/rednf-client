
function sq_AddFunctionName(appendage)
{
    appendage.sq_AddFunctionName("proc", "proc_appendage_RAGINWIND")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_RAGINWIND")
}

function onStart_appendage_RAGINWIND(appendage)
{
    return ;
    appendage.getVar("isBreak").clear_vector();
    appendage.getVar("isBreak").push_vector(0);
}
function proc_appendage_RAGINWIND(appendage)
{
	if(!appendage || !appendage.isValid()) {
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
