
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_WomanControl")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_WomanControl")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_WomanControl")
}


function sq_AddEffect(appendage)
{

}

function onEnd_appendage_WomanControl(appendage)
{

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

}

function proc_appendage_WomanControl(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

}



function onStart_appendage_WomanControl(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
}