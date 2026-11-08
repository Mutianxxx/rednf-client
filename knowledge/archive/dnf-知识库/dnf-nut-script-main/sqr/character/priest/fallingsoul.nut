 
function IsCheckUseFallingSoul(obj) 
{
	if(!obj) 
		return false; 
	local appendage = obj.GetSquirrelAppendage("Appendage/Character/ap_avenger_devilstrike.nut"); 
	if(!appendage) 
		return false;
 
	if(appendage.sq_var.size_vector() > 1) {
 
		local level = sq_GetSkillLevel(obj, 131); 
		local consumeMax = sq_GetIntData(obj, 131, 0, level);
		local time = sq_GetLevelData(obj, 131, 1, level);
		local darkPower = sq_GetLevelData(obj, 131, 2, level);
		
		local consumeValue = appendage.sq_var.get_vector(1); 
		
		if(consumeValue == 0)
		{ 
			obj.startCantUseSkillWarning();
			if (obj.isMessage())
				sq_AddMessage(29002); 
			return false;
		}
 
		if(consumeMax < consumeValue)
			consumeValue = consumeMax; 
 
		local consumeRate = sq_GetLevelData(obj, 131, 0, level);
		local magicPowerUpMax = consumeRate/2;
		consumeRate = consumeRate.tofloat()/100.0;
 		local magicPowerUpValue = 0;
 		if(consumeValue < 0)
 		{
 			magicPowerUpValue = (5*consumeRate) + 0.5; 
 			consumeValue = 0;
 		}
 		else
 		{
 			magicPowerUpValue = (consumeValue*consumeRate) + 0.5; 
 		}
 		
		local firstTime = true;
		if(CNSquirrelAppendage.sq_IsAppendAppendage(obj, "FallingSoul"))
		{
			firstTime = false;
		}
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 131, false, "FallingSoul", false);
		if(appendage.sq_var.size_vector() > 0 && !firstTime)
		{
			magicPowerUpValue = magicPowerUpValue + appendage.sq_var.get_vector(0);
			if(magicPowerUpMax < magicPowerUpValue)
				magicPowerUpValue = magicPowerUpMax; 
		}
		//print("magicPowerUpValue : " + magicPowerUpValue); 
 
		magicPowerUpValue = magicPowerUpValue.tointeger();
 
		//print("magicPowerUpValue : " + magicPowerUpValue);
 
		
		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), 131, level);
 
		CNSquirrelAppendage.sq_Append(appendage, obj, obj);
		if(appendage)
		{
			appendage.sq_var.clear_vector();
			appendage.sq_var.push_vector(magicPowerUpValue); 
		}
		local change_appendage = appendage.sq_getChangeStatus("FallingSoulMagic");
		if(!change_appendage) {
			change_appendage = appendage.sq_AddChangeStatus("FallingSoulMagic",obj, obj, time, CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, magicPowerUpValue.tointeger());
		}
 
		if(change_appendage) {
			change_appendage.clearParameter();
			change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, magicPowerUpValue.tofloat());
			change_appendage.addParameter(CHANGE_STATUS_TYPE_ELEMENT_ATTACK_DARK, false, darkPower.tofloat());
		}
 
		local appendageInfo = appendage.getAppendageInfo();
		appendageInfo.setValidTime(time);
 
		consumeDevilGauge(obj, consumeValue); 
 
		return true;
	}
	return false;
}


function checkCommandEnable_FallingSoul(obj)
{
 if(!obj) return false;
 local bRet = true;
 
 local state = obj.sq_GetSTATE();
 
 if(state == STATE_ATTACK) {
 
 bRet = obj.sq_IsCommandEnable(131);
 }
 
 if(!bRet) return false;
 
 local appendage = obj.GetSquirrelAppendage("Appendage/Character/ap_avenger_devilstrike.nut"); 
 if(!appendage) 
 return false;
 
 local consumeValue = appendage.sq_var.get_vector(1); 
 if(consumeValue == 0)
 return false; 
 
 return true;
} ;


  


 
function checkExecutableSkill_FallingSoul(obj) 
{
	if(!obj) return false;
	local isUse = obj.sq_IsUseSkill(131);
	if(isUse) {
		if(IsCheckUseFallingSoul(obj)) { 
			obj.sq_IntVectClear(); 
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(0); 
			obj.sq_IntVectPush(131);
			obj.sq_IntVectPush(500);
			obj.sq_IntVectPush(500);
			obj.sq_IntVectPush(3);
			obj.sq_IntVectPush(4); 
			obj.sq_IntVectPush(4); 
			obj.sq_addSetStatePacket(STATE_THROW, STATE_PRIORITY_USER, true);
			return true;
		}
	} 
	return false;
} ;


 


 
function onSetState_FallingSoul(HmlmuQe6qZH6nJThYW1gng9, r95v9Gg7vxx, zWMRKeyJKeKhnYRhj, jgjgc7cUBdxIQ4aq14Rhnd8)
{ 
 if(!HmlmuQe6qZH6nJThYW1gng9) return;
} ;