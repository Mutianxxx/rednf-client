
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_CONTROLDOLL")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_CONTROLDOLL")
}



function sq_AddEffect(appendage)
{
}

function proc_appendage_CONTROLDOLL(appendage)
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
	local obj = appendage.getParent();
	local sqrObj = sq_GetCNRDObjectToSQRCharacter(obj);
	if(sqrObj)
    {
		sq_ReleaseActiveStatus(sqrObj, ACTIVESTATUS_CURSE);
    }
}

function getCirrusInDarkBobyNumber(obj)
{
    local skill_level = sq_GetSkillLevel(obj, SKILL_CIRRUSINDARK);
    if (skill_level <= 0)
    {
        return 0;
    }else{
        return sq_GetLevelData(obj,  SKILL_CIRRUSINDARK, 2, skill_level);
    }
}

function onStart_appendage_CONTROLDOLL(appendage)
{
	local parentObj = appendage.getParent();
	local sqrObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
    appendage.getVar("num").clear_vector();
    appendage.getVar("num").push_vector(3 + getCirrusInDarkBobyNumber(sqrObj) );
}

