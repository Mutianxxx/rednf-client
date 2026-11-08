
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BLOODOATH")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BLOODOATH")
}


function sq_AddEffect(appendage)
{
}

function proc_appendage_BLOODOATH(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
    local skill = null;

	local parentObj = appendage.getParent();
	local obj = sq_GetCNRDObjectToSQRCharacter(parentObj);

    skill = sq_GetSkill(obj, SKILL_BLOODCUT);
	if(skill)
		skill.setCommandEnable(checkCommandEnable_bloodcut(obj)); 

    skill = sq_GetSkill(obj, SKILL_BLOODDOWN);
	if(skill)
		skill.setCommandEnable(checkCommandEnable_blooddown(obj)); 

    skill = sq_GetSkill(obj, SKILL_BLOODHANG);
	if(skill)
		skill.setCommandEnable(checkCommandEnable_bloodhang(obj)); 

    skill = sq_GetSkill(obj, SKILL_BLOODHIT);
	if(skill)
		skill.setCommandEnable(checkCommandEnable_bloodhit(obj)); 

    skill = sq_GetSkill(obj, SKILL_BLOODHOLD);
	if(skill)
		skill.setCommandEnable(checkCommandEnable_bloodhold(obj)); 

    skill = sq_GetSkill(obj, SKILL_BLOODSCREAM);
	if(skill)
		skill.setCommandEnable(checkCommandEnable_bloodscream(obj)); 

    skill = sq_GetSkill(obj, SKILL_BLOODSONG);
	if(skill)
		skill.setCommandEnable(checkCommandEnable_bloodsong(obj)); 

    skill = sq_GetSkill(obj, SKILL_WING);
	if(skill)
		skill.setCommandEnable(checkCommandEnable_wing(obj)); 

    skill = sq_GetSkill(obj, SKILL_WINGOUT);
	if(skill)
		skill.setCommandEnable(checkCommandEnable_wingout(obj)); 

}



function onStart_appendage_BLOODOATH(appendage)
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

