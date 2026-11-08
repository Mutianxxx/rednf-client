
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BLOOD")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BLOOD")
}


function sq_AddEffect(appendage)
{
}

function proc_appendage_BLOOD(appendage)
{
	if(!appendage) {
		return;		
	}

//	local parentObj = appendage.getParent();				
//    parentObj.setCurrentPos(parentObj.getXPos(),parentObj.getYPos(),0);

}



function onStart_appendage_BLOOD(appendage)
{
	if(!appendage) {
		return;
	}

}

