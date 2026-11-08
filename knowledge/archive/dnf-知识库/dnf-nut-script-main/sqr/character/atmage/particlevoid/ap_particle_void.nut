
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ParticleVoid")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ParticleVoid")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_ParticleVoid")
}

function sq_AddEffect(appendage)
{
}
//?bap?s??}?l?N???檺???
function onStart_appendage_ParticleVoid(appendage)
{


	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}

	local sqrChr = sq_GetCNRDObjectToSQRCharacter(parentObj);
    //sqrChr ?? ?H????H
	sqrChr.sq_StartWrite();
	sqrChr.sq_WriteDword(0);	// attackBonusRate
	sqrChr.sq_SendCreatePassiveObjectPacket(24343, 0, 0, 1, 0);


}
//ap?B??L?{?????檺???
function proc_appendage_ParticleVoid(appendage)
{
	if(!appendage || !appendage.isValid()) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}



//    parentObj.setCurrentPos(parentObj.getXPos(),parentObj.getYPos(),0);
    //???ap?O?_???T???[?F?A?p?G???T???[?A?H???N?|?????_??
}

//ap????Z?B?檺???
function onEnd_appendage_ParticleVoid(appendage)
{
	if(!appendage) {
		return;
	}	
		
	local parentObj = appendage.getParent();
				
	if(!parentObj) {
		appendage.setValid(false);
		return;
	}			
		
}

