
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_SHAOWAREA")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_SHAOWAREA")
    appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_SHAOWAREA")	
}
function sq_AddEffect(appendage)
{
}
function onAttackParent_appendage_SHAOWAREA(appendage, realAttacker, damager, boundingBox, isStuck)
{
	local parentObj = appendage.getParent();
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
//    local state = parentObj.getState();

    //chr


    local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, parentObj, SKILL_SHAOWAREA, false,
    "character/thief/4_shadow/shaowarea/ap_shaowarea_enemy.nut", true);
    //?T?w?S???Q?????????
//    sendOneHitAllMonsterShaowAreaObj(parentObj);


}



function proc_appendage_SHAOWAREA(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				

	if(!sourceObj || !parentObj ) 
    {
		appendage.setValid(false);
		return;
	}
 
}



function onStart_appendage_SHAOWAREA(appendage)
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

