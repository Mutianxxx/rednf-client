
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_FateSlave")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_FateSlave")
}



function sq_AddEffect(appendage)
{
}

function proc_appendage_FateSlave(appendage)
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
    gbl_HoldAndDelayEffectSetDownByAppendageLoop(appendage);
}



function onStart_appendage_FateSlave(appendage)
{

}

