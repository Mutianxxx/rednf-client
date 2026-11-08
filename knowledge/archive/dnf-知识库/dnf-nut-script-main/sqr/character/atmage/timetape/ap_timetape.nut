
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_TimeTape")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_TimeTape")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_TimeTape")
}


function sq_AddEffect(appendage)
{

//	appendage.sq_AddEffectFront("character/mage/atanimation/als_ani/timetape/hit/hit_loop_front.ani");
//	appendage.sq_AddEffectBack("character/mage/atanimation/als_ani/timetape/hit/hit_loop_back.ani");

}

function onEnd_appendage_TimeTape(appendage)
{

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local sqrObj = sq_GetCNRDObjectToSQRCharacter(sourceObj);
				
	if(parentObj && sqrObj) 
    {


        local front = appendage.getVar("obj").get_obj_vector(0);
        local back = appendage.getVar("obj").get_obj_vector(1);

        if (front && back)
        {

            front.setValid(false);
            back.setValid(false);
        }
	}

}

function proc_appendage_TimeTape(appendage)
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

    local front = appendage.getVar("obj").get_obj_vector(0);
    local back = appendage.getVar("obj").get_obj_vector(1);

    if (front && back)
    {
        front.setCurrentPos(parentObj.getXPos(),parentObj.getYPos() + 1,parentObj.getZPos() + parentObj.getObjectHeight()/2);
        back.setCurrentPos(parentObj.getXPos(),parentObj.getYPos() - 1,parentObj.getZPos() + parentObj.getObjectHeight()/2);
    }

    return false;

	local sqrChr = sq_GetCNRDObjectToSQRCharacter(sourceObj);

    local skill = sq_GetSkill(sqrChr, SKILL_TIMETAPE);
	if(skill)
		skill.setCommandEnable(true); 

    local iEnterSkill = sqrChr.sq_IsEnterSkill(SKILL_TIMETAPE);
    if (iEnterSkill != -1)
    {
        CheckEnemyTimeTapeAppend(sourceObj);
    }

}



function onStart_appendage_TimeTape(appendage)
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

	local Front = sq_AddDrawOnlyAniFromParent(parentObj, "character/mage/atanimation/als_ani/timetape/hit/hit_loop_front.ani"  ,0,-1,0);
	local Back = sq_AddDrawOnlyAniFromParent(parentObj, "character/mage/atanimation/als_ani/timetape/hit/hit_loop_back.ani"  ,0,-1,0);
    appendage.getVar("obj").clear_obj_vector();

    appendage.getVar("obj").push_obj_vector(  Front );
    appendage.getVar("obj").push_obj_vector(  Back  );

}