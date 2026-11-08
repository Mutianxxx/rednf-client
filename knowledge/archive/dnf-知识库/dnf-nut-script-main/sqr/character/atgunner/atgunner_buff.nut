
function onAfterSetState_atgunner_buff(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local buffSkillIndex = obj.getBuffSkillIndex();
	print("BuffSkillIndex:" + buffSkillIndex);
	local apd = "";
	if (buffSkillIndex == 33) {
		local skill_level = sq_GetSkillLevel(obj, 33);
		local time = sq_GetLevelData(obj, 33, 0, skill_level);
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 33, false, "character/atgunner/newstayjumpshoot/ap_newstayjumpshoot.nut", true);
		appendage.sq_SetValidTime(time);
	}
	else if(buffSkillIndex == 62){
		apd = "character/atgunner/appendage/ap_subweaponstuckdown.nut";
	}
	else if(buffSkillIndex == 46){
		apd = "character/atgunner/appendage/ap_robotics.nut";
	}
	if(apd != "")
	{
		if(CNSquirrelAppendage.sq_IsAppendAppendage(obj , "character/atgunner/appendage/ap_subweaponstuckdown.nut"))
		{
			CNSquirrelAppendage.sq_RemoveAppendage(obj , "character/atgunner/appendage/ap_subweaponstuckdown.nut");
		}
		else if(CNSquirrelAppendage.sq_IsAppendAppendage(obj , "character/atgunner/appendage/ap_robotics.nut"))
		{
			CNSquirrelAppendage.sq_RemoveAppendage(obj , "character/atgunner/appendage/ap_robotics.nut");
		}
		
		local validTime = obj.sq_GetLevelData(buffSkillIndex , 0 , sq_GetSkillLevel(obj , buffSkillIndex));;
		local Appendage = CNSquirrelAppendage.sq_AppendAppendage(obj , obj , buffSkillIndex , true , apd , true);
		Appendage.sq_SetValidTime(validTime);
	}
}

