
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ReLive")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ReLive")
	appendage.sq_AddFunctionName("onSetHp", "onSetHp_appendage_ReLive")
}

function sq_AddEffect(appendage)
{

}


function onSetHp_appendage_ReLive(appendage, hp, attacker)
{
	if(!appendage)
		return hp;
	
		
	local parentObj = appendage.getParent();

	
	local org_hp = -1;
    if (hp <= 0)
    {
        appendage.getVar("flag").clear_vector();
        appendage.getVar("flag").push_vector(1);

        parentObj = sq_GetCNRDObjectToActiveObject(parentObj);
        local appendage = CNSquirrelAppendage.sq_AppendAppendage(parentObj, parentObj, SKILL_RELIVE, false,
             "character/new_mage/relive/ap_relive_alter.nut", true);

        return 0;
    }
    return hp;
}



function proc_appendage_ReLive(appendage)
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

    if (appendage.getVar("flag").get_vector(0) == 1)
    {

    }
//    parentObj.setCurrentPos(0,0,0);
}



function onStart_appendage_ReLive(appendage)
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

