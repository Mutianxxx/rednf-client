

function onAfterSetState_atgunner_windmill(obj, state, datas, isResetTimer)
{
	if (!obj) return;
	local vectorDataA = obj.sq_GetVectorData(datas, 0); 
	obj.getVar().clear_vector(); 
	obj.getVar().push_vector(vectorDataA); 
	local skillLevel = sq_GetSkillLevel(obj, 250); 
	if(skillLevel > 0)
	{
		local levelDataA = obj.sq_GetLevelData(250, 0, skillLevel);
		local levelDataB = obj.sq_GetLevelData(250, 1, skillLevel);
		obj.sq_SetStaticMoveInfo(0, levelDataA, levelDataA, true);
		obj.sq_SetStaticMoveInfo(1, levelDataB, levelDataB, true);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); 
	}
} ;



function onProcCon_atgunner_windmill(obj)
{
	if (!obj)
		return;
	local substate = obj.getVar().get_vector(0);
	if (substate == 3) 
		onProcIsSub_My_atgunner_stylish(obj);
 
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
	
	obj.setSkillCommandEnable(3, true);
	if(obj.sq_IsEnterSkill(3) != -1 || sq_IsKeyDown(OPTION_HOTKEY_SKILL2 , ENUM_SUBKEY_TYPE_ALL)){
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(52, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}