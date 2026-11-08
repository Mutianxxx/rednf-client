
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ReLive_Alter")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ReLive_Alter")
	appendage.sq_AddFunctionName("onSetHp", "onSetHp_appendage_ReLive_Alter")
}

function sq_AddEffect(appendage)
{
	appendage.sq_AddEffectFront("character/mage/animation/ani_als/eternalpossession/enchantress_help/enchantresshelp_main_00.ani");
}


function onSetHp_appendage_ReLive_Alter(appendage, hp, attacker)
{
	if(!appendage)
		return hp;
	
		
	local parentObj = appendage.getParent();

	
    return hp;
}



function proc_appendage_ReLive_Alter(appendage)
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
		appendage.setValid(false);
		return;
    }
}



function onStart_appendage_ReLive_Alter(appendage)
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
    appendage.getVar("flag").clear_vector();
    appendage.getVar("flag").push_vector(0);

}

