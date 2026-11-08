//????
function checkCommandEnable_defaneblood(obj)
{
	if(!obj) return false;
	local mystate = obj.sq_GetState();
	if(mystate == 3||mystate == 4||mystate == 5||mystate == 9){
		return false;
	}
	return true;
}

function checkExecutableSkill_defaneblood(obj)  
{
	if(!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill( SKILL_DEFANEBLOOD );

	if (isUseSkill) 
	{

		local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_DEFANEBLOOD, false, "character/swordman/defaneblood/ap_defaneblood.nut", true);				 

		local level = sq_GetSkillLevel(obj, SKILL_DEFANEBLOOD);		
		local maxHp = sq_GetLevelData(obj, SKILL_DEFANEBLOOD, 0, level);
		local time = obj.sq_GetIntData(SKILL_DEFANEBLOOD, 0);
		//sq_GetLevelData(obj, SKILL_DEFANEBLOOD, 1, level);
		local cd = sq_GetLevelData(obj, SKILL_DEFANEBLOOD, 2, level);
		//local maxH = sq_GetLevelData(obj, SKILL_DEFANEBLOOD, 1, level);
		local nowHp = obj.getHp()*100/obj.getHpMax();
		masterAppendage.getVar("hpMax").clear_vector();
		if(nowHp<maxHp){
			masterAppendage.getVar("hpMax").push_vector( nowHp.tointeger() );
		}else{
			masterAppendage.getVar("hpMax").push_vector( maxHp );
		}
		masterAppendage.sq_SetValidTime( time );

		masterAppendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_DEFANEBLOOD, level );
		CNSquirrelAppendage.sq_AppendAppendageID(masterAppendage, obj, obj, SKILL_DEFANEBLOOD, true);
		masterAppendage.setEnableIsBuff(true);
		masterAppendage.setBuffIconImage(96);
		return true;
	}
	return false;
}

function startSkillCoolTime_defaneblood(obj, skillIndex, skillLevel, currentCoolTime)
{
	local newCoolTime	= currentCoolTime;
	
	if(SKILL_DEFANEBLOOD == skillIndex)
	{
		local level		= sq_GetSkillLevel(obj, SKILL_DEFANEBLOOD);
		local cooltime	= sq_GetLevelData(obj, SKILL_DEFANEBLOOD, 2, level);
		newCoolTime	= cooltime;
	}
	return newCoolTime;	
}
