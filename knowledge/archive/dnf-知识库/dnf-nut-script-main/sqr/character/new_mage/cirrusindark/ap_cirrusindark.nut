
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_CIRRUSINDARK")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_CIRRUSINDARK")
	appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_CIRRUSINDARK")
}



function sq_AddEffect(appendage)
{
}

function proc_appendage_CIRRUSINDARK(appendage)
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

	local sqrObj = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	
	if(sqrObj)
	{
		sqrObj.sq_RemovePassiveSkillAttackBonusRate(SKILL_CIRRUSINDARK);
		sqrObj.sq_AddPassiveSkillAttackBonusRate(SKILL_CIRRUSINDARK, 1);


	}

}



function onStart_appendage_CIRRUSINDARK(appendage)
{

}

function onAttackParent_appendage_CIRRUSINDARK(appendage, realAttacker, damager, boundingBox, isStuck)
{

	if(!appendage) return;
	local obj = appendage.getParent();
	if(!obj) {
		appendage.setValid(false);
		return;
	}
	local pChr = sq_GetCNRDObjectToSQRCharacter(obj);
	
	local active_damager = sq_GetCNRDObjectToActiveObject(damager);
	
	if(!active_damager) return 0;
	if(!pChr.isEnemy(active_damager))
	{
		return 0;
	}
	local appendage_count = active_damager.getVar("RoseinDarkCount").getInt(0);
	local skill_level = pChr.sq_GetSkillLevel(SKILL_CIRRUSINDARK);
	local change_count = sq_GetLevelData(pChr, SKILL_CIRRUSINDARK, 5, skill_level);
	if(appendage_count >= change_count){
		return;
	}
	
	local appendage = CNSquirrelAppendage.sq_AppendAppendage(active_damager, active_damager, SKILL_CIRRUSINDARK, false,
	 "character/new_mage/cirrusindark/ap_roseindark.nut", false);
	
	CNSquirrelAppendage.sq_AppendAppendageID(appendage, active_damager, active_damager, SKILL_CIRRUSINDARK, false);

	appendage = active_damager.GetSquirrelAppendage("character/new_mage/cirrusindark/ap_roseindark.nut");

	if(appendage)
	{
		appendage_count++;
		active_damager.getVar("RoseinDarkCount").setInt(0, appendage_count);
		local change_time = sq_GetLevelData(pChr, SKILL_CIRRUSINDARK, 4, skill_level);
		appendage.sq_SetValidTime(change_time); 
		local registValue = sq_GetLevelData(pChr, SKILL_CIRRUSINDARK, 3, skill_level); 
		registValue = -registValue*appendage_count;
		//print("registValue:"+registValue+"\n\r");
		//print("change_time:"+change_time+"\n\r");
		local change_appendage = appendage.sq_getChangeStatus("roseindark");
		if(!change_appendage)
			change_appendage = appendage.sq_AddChangeStatusAppendageID(damager, damager, 0, CHANGE_STATUS_TYPE_ELEMENT_TOLERANCE_ALL, false, registValue, APID_COMMON);
		if(change_appendage) {
			change_appendage.clearParameter();
			change_appendage.addParameter(CHANGE_STATUS_TYPE_ELEMENT_TOLERANCE_ALL, false, registValue.tofloat());
		}
		//print("ok!\n\r");
	}
	
}
