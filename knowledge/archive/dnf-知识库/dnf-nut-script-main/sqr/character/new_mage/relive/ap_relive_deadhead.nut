
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_DeadHead")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_DeadHead")
}

function sq_AddEffect(appendage)
{
	appendage.sq_AddEffectFront("character/mage/animation/ani_als/eternalpossession/targeteffect/spotlight_00.ani");
	appendage.sq_AddEffectBack("character/mage/animation/ani_als/eternalpossession/targeteffect/spotlightground_00.ani");
}



function proc_appendage_DeadHead(appendage)
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
    parentObj = sq_GetCNRDObjectToActiveObject(parentObj);
    if (parentObj.getHp() <= 10)
    {
    }else{
    }
}



function onStart_appendage_DeadHead(appendage)
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

