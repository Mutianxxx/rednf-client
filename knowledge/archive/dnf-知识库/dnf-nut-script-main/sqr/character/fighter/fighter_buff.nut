
function onAfterSetState_fighter_buff(obj , state , datas , isResetTimer)
{
	if(!obj) return;
	local SkillIndex = obj.getBuffSkillIndex();
	local apd = "";
	print("BuffSkillIndex:" + SkillIndex);
	if(SkillIndex < 1)	return;
	
	if(SkillIndex == 31)
	{
		apd = "character/fighter/appendage/ap_attackspeedup.nut";
	}
	else if(SkillIndex == 38)
	{
		apd = "character/fighter/appendage/ap_enchantpoison.nut";
	}
	else if(SkillIndex == 50)
	{
		apd = "character/fighter/appendage/ap_definitegrab.nut";
	}
	
	if(!apd)	return;
	if(apd == "")	return;
	
	if(CNSquirrelAppendage.sq_IsAppendAppendage(obj , apd))
	{
		CNSquirrelAppendage.sq_RemoveAppendage(obj , apd);
	}
	
	local validTime = obj.sq_GetLevelData(SkillIndex , 0 , sq_GetSkillLevel(obj , SkillIndex));
	if(apd == "character/fighter/appendage/ap_attackspeedup.nut")
		validTime = obj.sq_GetLevelData(SkillIndex , 1 , sq_GetSkillLevel(obj , SkillIndex));
	local Appendage = CNSquirrelAppendage.sq_AppendAppendage(obj , obj , SkillIndex , true , apd , true);
	Appendage.sq_SetValidTime(validTime);
}
