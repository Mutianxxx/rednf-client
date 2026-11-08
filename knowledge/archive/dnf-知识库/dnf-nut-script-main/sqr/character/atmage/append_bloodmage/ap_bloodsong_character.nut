function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BloodMageMonsterAppendage_BloodSong_Character")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BloodMageMonsterAppendage_BloodSong_Character")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BloodMageMonsterAppendage_BloodSong_Character")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_BloodMageMonsterAppendage_BloodSong_Character(appendage)
{
}

function proc_appendage_BloodMageMonsterAppendage_BloodSong_Character(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
    parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);

    local speed = parentObj.sq_GetIntData(SKILL_BLOODSONG,17);

    local currT = appendage.getTimer().Get() * speed / 100;


	if(!sourceObj || !parentObj) 
    {
		appendage.setValid(false);
		return;
	}
    setATTepesShake(appendage,currT);
    if (currT > 10000)
    {
        local parentObj = appendage.getSource();
        parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
		appendage.setValid(false);
    }
    if (currT > 1000 && appendage.getVar().get_vector(0) == 0)
    {
        appendage.getVar().set_vector(0,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }
    if (currT > 1600 && appendage.getVar().get_vector(1) == 0)
    {
        appendage.getVar().set_vector(1,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }
    if (currT > 2100 && appendage.getVar().get_vector(2) == 0)
    {
        appendage.getVar().set_vector(2,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }
    if (currT > 2500 && appendage.getVar().get_vector(3) == 0)
    {
        appendage.getVar().set_vector(3,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }
    if (currT > 3000 && appendage.getVar().get_vector(4) == 0)
    {
        appendage.getVar().set_vector(4,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }
    if (currT > 3400 && appendage.getVar().get_vector(5) == 0)
    {
        appendage.getVar().set_vector(5,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }
    if (currT > 3500 && appendage.getVar().get_vector(6) == 0)
    {
        appendage.getVar().set_vector(6,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }
    if (currT > 3600 && appendage.getVar().get_vector(7) == 0)
    {
        appendage.getVar().set_vector(7,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }
    if (currT > 3700 && appendage.getVar().get_vector(8) == 0)
    {
        appendage.getVar().set_vector(8,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }
    if (currT > 3800 && appendage.getVar().get_vector(8) == 0)
    {
        appendage.getVar().set_vector(8,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }
    if (currT > 3900 && appendage.getVar().get_vector(9) == 0)
    {
        appendage.getVar().set_vector(9,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }
    if (currT > 4000 && appendage.getVar().get_vector(10) == 0)
    {
        appendage.getVar().set_vector(10,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }
    if (currT > 4100 && appendage.getVar().get_vector(11) == 0)
    {
        appendage.getVar().set_vector(11,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }
    if (currT > 4200 && appendage.getVar().get_vector(12) == 0)
    {
        appendage.getVar().set_vector(12,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }
    if (currT > 4300 && appendage.getVar().get_vector(13) == 0)
    {
        appendage.getVar().set_vector(13,1);
        setBloodValue(parentObj,parentObj.sq_GetIntData(SKILL_BLOODSONG, 9) / 15);
    }



//    parentObj.setCurrentPos(parentObj.getXPos(),parentObj.getYPos(),0);
}

function setATTepesShake(appendage,t)
{
    
    local currentT = t;

	local parentObj = appendage.getParent();
    local obj = sq_GetCNRDObjectToSQRCharacter(parentObj);

    if (currentT > 1000 && appendage.getVar("shake").get_vector(0) == 0)
    {
        appendage.getVar("shake").set_vector(0,1);
        obj.sq_SetShake(obj, 10,150 );
    }else if (currentT > 1600 && appendage.getVar("shake").get_vector(1) == 0)
    {
        appendage.getVar("shake").set_vector(1,1);
    }else if (currentT > 2100 && appendage.getVar("shake").get_vector(2) == 0)
    {
        appendage.getVar("shake").set_vector(2,1);
        obj.sq_SetShake(obj, 8,100 );
    }else if (currentT > 2500 && appendage.getVar("shake").get_vector(3) == 0)
    {
        appendage.getVar("shake").set_vector(3,1);
        obj.sq_SetShake(obj, 7,100 );
    }else if (currentT > 3000 && appendage.getVar("shake").get_vector(4) == 0)
    {
        appendage.getVar("shake").set_vector(4,1);
//        obj.sq_SetShake(obj, 4,100 );
    }else if (currentT > 3400 && appendage.getVar("shake").get_vector(5) == 0)
    {
        appendage.getVar("shake").set_vector(5,1);
//        obj.sq_SetShake(obj, 4,100 );
    }else if (currentT > 3500 && appendage.getVar("shake").get_vector(6) == 0)
    {
        appendage.getVar("shake").set_vector(6,1);
        obj.sq_SetShake(obj, 5,1000 );
    }
}


function onStart_appendage_BloodMageMonsterAppendage_BloodSong_Character(appendage)
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


    appendage.getVar("shake").clear_vector();
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);
    appendage.getVar("shake").push_vector(0);

//	sqrChr.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);

}

