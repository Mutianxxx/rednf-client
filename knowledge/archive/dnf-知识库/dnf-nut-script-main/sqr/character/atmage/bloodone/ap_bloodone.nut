function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_bloodone")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_bloodone")
    appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_bloodone")	
}


function sq_AddEffect(appendage)
{
}


function onAttackParent_appendage_bloodone(appendage, realAttacker, damager, boundingBox, isStuck)
{

	local obj = appendage.getParent();	
	
	local sqrObj = sq_GetCNRDObjectToSQRCharacter(obj);

    if (!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/bloodone/ap_monsterbloodone.nut"))
    {
        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, sqrObj, SKILL_BLOODONE, 
        false, "character/atmage/bloodone/ap_monsterbloodone.nut", true);				 
    }


}

function proc_appendage_bloodone(appendage)
{
	if(!appendage) {
		return;
	}
	

}


function onStart_appendage_bloodone(appendage)
{
	if(!appendage) {
		return;
	}
	

}