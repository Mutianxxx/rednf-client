function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BloodMageMonsterAppendage_Attack4_Character")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BloodMageMonsterAppendage_Attack4_Character")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BloodMageMonsterAppendage_Attack4_Character")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_BloodMageMonsterAppendage_Attack4_Character(appendage)
{
}

function proc_appendage_BloodMageMonsterAppendage_Attack4_Character(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
    parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
    local currT = appendage.getTimer().Get();
    if (currT > 950)
    {
        local parentObj = appendage.getSource();
        parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODOATH, 3) / 4);
		appendage.setValid(false);
    }
    if (currT > 200 && appendage.getVar().get_vector(0) == 0)
    {
        appendage.getVar().set_vector(0,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODOATH, 3) / 4);
    }
    if (currT > 400 && appendage.getVar().get_vector(1) == 0)
    {
        appendage.getVar().set_vector(1,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODOATH, 3) / 4);
    }
    if (currT > 600 && appendage.getVar().get_vector(2) == 0)
    {
        appendage.getVar().set_vector(2,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODOATH, 3) / 4);
    }

	if(!sourceObj || !parentObj) 
    {
		appendage.setValid(false);
		return;
	}
//    parentObj.setCurrentPos(parentObj.getXPos(),parentObj.getYPos(),0);
}



function onStart_appendage_BloodMageMonsterAppendage_Attack4_Character(appendage)
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
    appendage.getVar().clear_vector();
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);

//	sqrChr.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);

}

