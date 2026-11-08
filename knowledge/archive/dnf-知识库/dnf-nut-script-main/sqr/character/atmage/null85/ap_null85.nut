
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_NULL85")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_NULL85")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_NULL85")
}

function sq_AddEffect(appendage)
{
}
function onEnd_appendage_NULL85(appendage)
{
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	local sqrChr = sq_GetCNRDObjectToSQRCharacter(sourceObj);

    local sfProc = sq_GetLevelData(sqrChr, SKILL_NULL85, 4, sq_GetSkillLevel(sqrChr, SKILL_NULL85) );
    local sfLevel = sq_GetLevelData(sqrChr, SKILL_NULL85, 2, sq_GetSkillLevel(sqrChr, SKILL_NULL85) );
    local sfTime = sq_GetLevelData(sqrChr, SKILL_NULL85, 3, sq_GetSkillLevel(sqrChr, SKILL_NULL85) );


    sq_sendSetActiveStatusPacket( parentObj,sqrChr, ACTIVESTATUS_HOLD, sfProc.tofloat(), sfLevel, false, sfTime);

}

function proc_appendage_NULL85(appendage)
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


    local t = appendage.getTimer().Get();
    if (t < 1500)
    {
        local hei = sq_GetAccel( -parentObj.getObjectHeight() , 0,t, 1500, true);

        parentObj.setCurrentPos(parentObj.getXPos(),parentObj.getYPos(),hei);

    }else{


        parentObj.setCurrentPos(parentObj.getXPos(),parentObj.getYPos(),0);
    }



}



function onStart_appendage_NULL85(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	sourceObj = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}	

    local posX = sq_GetDistancePos( sourceObj.getXPos() , 
                                    sourceObj.getDirection(),
                                    sq_getRandom(200,500).tointeger() );

    local posY = sourceObj.getYPos() + sq_getRandom(-45,-15).tointeger();
    parentObj.setCurrentPos(posX,posY,0);

}

