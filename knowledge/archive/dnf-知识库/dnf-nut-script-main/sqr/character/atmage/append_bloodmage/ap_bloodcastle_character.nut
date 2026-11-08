function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BloodMageMonsterAppendage_BloodCastle_Character")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BloodMageMonsterAppendage_BloodCastle_Character")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BloodMageMonsterAppendage_BloodCastle_Character")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_BloodMageMonsterAppendage_BloodCastle_Character(appendage)
{
}

function proc_appendage_BloodMageMonsterAppendage_BloodCastle_Character(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
    parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
    local currT = appendage.getTimer().Get();
    if (currT > 15000)
    {
        local parentObj = appendage.getSource();
        parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODCASTLE, 5) / 35);
		appendage.setValid(false);
    }

    for (local i = 0;i < 35;i++)
    {
        if (currT > 200*( i + 1 ) && appendage.getVar().get_vector(i) == 0)
        {
            appendage.getVar().set_vector(i,1);
            setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODCASTLE, 5) / 35);
        }
    }


	if(!sourceObj || !parentObj) 
    {
		appendage.setValid(false);
		return;
	}
//    parentObj.setCurrentPos(parentObj.getXPos(),parentObj.getYPos(),0);
}



function onStart_appendage_BloodMageMonsterAppendage_BloodCastle_Character(appendage)
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
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);
    appendage.getVar().push_vector(0);

//	sqrChr.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);

}

