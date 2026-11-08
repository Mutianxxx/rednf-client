function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BloodMageMonsterAppendage_Attack1_Character")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BloodMageMonsterAppendage_Attack1_Character")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BloodMageMonsterAppendage_Attack1_Character")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_BloodMageMonsterAppendage_Attack1_Character(appendage)
{
}

function proc_appendage_BloodMageMonsterAppendage_Attack1_Character(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				

    local currT = appendage.getTimer().Get();
    if (currT > 950)
    {
        local parentObj = appendage.getSource();
        parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODOATH, 0) );
		appendage.setValid(false);
    }

	if(!sourceObj || !parentObj) 
    {
		appendage.setValid(false);
		return;
	}
//    parentObj.setCurrentPos(parentObj.getXPos(),parentObj.getYPos(),0);
}



function onStart_appendage_BloodMageMonsterAppendage_Attack1_Character(appendage)
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



//	sqrChr.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);

}

