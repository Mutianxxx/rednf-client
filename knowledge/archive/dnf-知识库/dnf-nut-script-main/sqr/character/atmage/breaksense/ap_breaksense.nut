
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BreakSense")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BreakSense")
}


function sq_AddEffect(appendage)
{
}

function proc_appendage_BreakSense(appendage)
{
	if(!appendage)
	{
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj) 
    {
		appendage.setValid(false);
		return;
	}

    local sqrChr = sq_GetCNRDObjectToSQRCharacter(parentObj);
    local state = appendage.getVar("state").get_vector(0);
    local startT = appendage.getVar("t").get_vector(0);
    if (state == 1)
    {

        local maxT = sqrChr.sq_GetIntData(SKILL_BREAKSENSE, 4);

        if (appendage.getTimer().Get() - startT > maxT)
        {
            appendage.getVar("state").set_vector(0,2);
            appendage.getVar("t").set_vector(0,appendage.getTimer().Get() );
        }
    }else if (state == 2)
    {
        local maxT2 = sqrChr.sq_GetIntData(SKILL_BREAKSENSE, 5);
        local maxEnegry = sqrChr.sq_GetIntData(SKILL_BREAKSENSE, 0);
        if (appendage.getTimer().Get() - startT > maxT2)
        {

            local decrease = sqrChr.sq_GetIntData(SKILL_BREAKSENSE, 3);
            if ((getBreakSenseEnegry(sqrChr) % maxEnegry) - decrease > 0)
            {
                setBreakSenseEnegry( sqrChr,getBreakSenseEnegry(sqrChr) - decrease);

            }else{
                appendage.getVar("state").set_vector(0,0);
                setBreakSenseEnegry( sqrChr,getBreakSenseEnegry(sqrChr) - getBreakSenseEnegry(sqrChr) % maxEnegry );
            }
            appendage.getVar("t").set_vector(0,appendage.getTimer().Get() );

        }
    }

//    appendage.getVar("nullValue").set_vector(0,sq_getRandom(0,1000).tointeger());
}

function onStart_appendage_BreakSense(appendage)
{
	if(!appendage)
	{
		return;
	}
	local parentObj = appendage.getParent();
    local sqrChr = sq_GetCNRDObjectToSQRCharacter(parentObj);

    appendage.getVar("nullValue").clear_vector();
    appendage.getVar("nullValue").push_vector(0);

    if (sq_GetSkillLevel(sqrChr, SKILL_STH_0) > 0)
    {

        local maxEnegry = sqrChr.sq_GetIntData(SKILL_BREAKSENSE, 0);
        local stoneNum = sq_GetLevelData(sqrChr, SKILL_STH_0, 0, sq_GetSkillLevel(sqrChr, SKILL_STH_0) );
        appendage.getVar("nullValue").set_vector(0,stoneNum * maxEnegry + maxEnegry - 1);
    }

    appendage.getVar("state").clear_vector();
    appendage.getVar("state").push_vector(0);

    appendage.getVar("t").clear_vector();
    appendage.getVar("t").push_vector(0);

}
