
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_graceofdevine")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_graceofdevine")
	appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_graceofdevine")
}

function sq_AddEffect(appendage)
{
}

function proc_appendage_graceofdevine(appendage)
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
	local obj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	local attackinfo = sq_GetCurrentAttackInfo(obj);
	if(attackinfo){
		if(!attackinfo.isValidElement(ENUM_ELEMENT_LIGHT))
			attackinfo.setElement(ENUM_ELEMENT_LIGHT); 
	}
}

function onStart_appendage_graceofdevine(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
}

function onAttackParent_appendage_graceofdevine(appendage, realAttacker, damager, boundingBox, isStuck)
{

	if(!appendage) return;
	local obj = appendage.getParent();
	if(!obj) {
		appendage.setValid(false);
		return;
	}
	local pChr = sq_GetCNRDObjectToSQRCharacter(obj);
	
	local active_damager = sq_GetCNRDObjectToActiveObject(damager);
	
	if(!active_damager) 
		return 0;
	if(!pChr.isEnemy(active_damager))
	{
		return 0;
	}
	local appendage_count = active_damager.getVar("DevineCount").getInt(0);
	local skill_level = pChr.sq_GetSkillLevel(SKILL_GRACE_OF_DEVINE);
	local change_count = pChr.sq_GetIntData(SKILL_GRACE_OF_DEVINE, 0);
	
	if(appendage_count >= change_count){
		return;
	}
	
	local appendage = CNSquirrelAppendage.sq_AppendAppendage(active_damager, active_damager, SKILL_GRACE_OF_DEVINE, false,
	 "character/atpriest/appendage/ap_graceofdevine_sub.nut", false);
	
	CNSquirrelAppendage.sq_AppendAppendageID(appendage, active_damager, active_damager, SKILL_GRACE_OF_DEVINE, false);

	appendage = active_damager.GetSquirrelAppendage("character/atpriest/appendage/ap_graceofdevine_sub.nut");

	if(appendage)
	{
		appendage_count++;
		active_damager.getVar("DevineCount").setInt(0, appendage_count);
		local change_time = pChr.sq_GetIntData(SKILL_GRACE_OF_DEVINE, 1);
		appendage.sq_SetValidTime(change_time); 
		local registValue = sq_GetLevelData(pChr, SKILL_GRACE_OF_DEVINE, 0, skill_level); 
		registValue = -registValue*appendage_count;
		local change_appendage = appendage.sq_getChangeStatus("devinesub");
		if(!change_appendage)
			change_appendage = appendage.sq_AddChangeStatusAppendageID(damager, damager, 0, CHANGE_STATUS_TYPE_ELEMENT_TOLERANCE_LIGHT, false, registValue, APID_COMMON);
		if(change_appendage) {
			change_appendage.clearParameter();
			change_appendage.addParameter(CHANGE_STATUS_TYPE_ELEMENT_TOLERANCE_LIGHT, false, registValue.tofloat());
		}
	}
	
}

