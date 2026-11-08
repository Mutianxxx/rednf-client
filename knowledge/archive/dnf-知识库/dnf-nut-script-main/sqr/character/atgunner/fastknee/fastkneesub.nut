function onProcCon_FASTKNEESUB(obj)
{
	if (!obj) 
		return false;
	
	local skill = sq_GetSkill(obj, 64);
	
	if(!skill){
		return false;
	}
	if(skill.isSealFunction())
	{
		return false;
	}
	if(obj.sq_GetSkillLevel(64)<1)
	{
		return false;
	}
	
	obj.setSkillCommandEnable(7, true);
	if(obj.sq_IsEnterSkill(7) != -1 || sq_IsKeyDown(OPTION_HOTKEY_SKILL2 , ENUM_SUBKEY_TYPE_ALL)){
		obj.sq_IntVectClear();
		obj.sq_AddSetStatePacket(54, STATE_PRIORITY_IGNORE_FORCE, false);
		return true;
	}
	return false;
}