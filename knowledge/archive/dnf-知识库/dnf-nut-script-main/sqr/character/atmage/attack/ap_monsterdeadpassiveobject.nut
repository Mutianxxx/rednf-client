
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_MONSTERDEADPASSIVEOBJECT")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_MONSTERDEADPASSIVEOBJECT")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_MONSTERDEADPASSIVEOBJECT")
	appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_MONSTERDEADPASSIVEOBJECT")
}

function sq_AddEffect(appendage)
{
}
function getImmuneTypeDamageRate_appendage_MONSTERDEADPASSIVEOBJECT(appendage, damageRate, attacker)
{
	local parentObj = appendage.getParent();	
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
    if (parentObj.getHp() <= 1 )
    {
        damageRate = 0;
    }
    return damageRate;
}
function onEnd_appendage_MONSTERDEADPASSIVEOBJECT(appendage)
{
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
//    local value1 = sourceObj.sq_GetIntData(SKILL_BLOODONE, 0);
//    local value2 = sourceObj.sq_GetIntData(SKILL_BLOODONE, 1);
//    local value3 = sourceObj.sq_GetIntData(SKILL_BLOODONE, 2);

    sq_BinaryStartWrite();
    sq_BinaryWriteDword(0);	// attackBonusRate
    sq_BinaryWriteDword(62);
    sq_BinaryWriteDword( 1000 );
    sq_BinaryWriteDword( 5 );
    sq_SendCreatePassiveObjectPacketPos(sourceObj,24357, 0,parentObj.getXPos(), parentObj.getYPos() + 1, parentObj.getZPos() );

}

function proc_appendage_MONSTERDEADPASSIVEOBJECT(appendage)
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
//	local ani = parentObj.getCurrentAnimation();
}



function onStart_appendage_MONSTERDEADPASSIVEOBJECT(appendage)
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

