function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BloodMageMonsterAppendage_WindStrike")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BloodMageMonsterAppendage_WindStrike")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BloodMageMonsterAppendage_WindStrike")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_BloodMageMonsterAppendage_WindStrike(appendage)
{
    onEndBloodMageAppendage(appendage);
}

function proc_appendage_BloodMageMonsterAppendage_WindStrike(appendage)
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
    onProcBloodMageAppendage(appendage,5);
//    parentObj.setCurrentPos(parentObj.getXPos(),parentObj.getYPos(),0);
}



function onStart_appendage_BloodMageMonsterAppendage_WindStrike(appendage)
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

    appendage.getVar("count").clear_vector();
    appendage.getVar("count").push_vector( 0 );

    onstartBloodMageAppendage(appendage);



//	sqrChr.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);

}

