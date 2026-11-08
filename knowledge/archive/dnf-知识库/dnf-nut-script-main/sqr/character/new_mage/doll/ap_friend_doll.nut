
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_FRIEND_DOLL")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_FRIEND_DOLL")
}



function sq_AddEffect(appendage)
{
}

function proc_appendage_FRIEND_DOLL(appendage)
{
	if(!appendage) {
		return;		
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if(!parentObj) 
    {
		//appendage.setValid(false);
		return;
	}


/*	local sChr = sq_GetCNRDObjectToActiveObject(sourceObj);
	sChr = sq_GetCNRDObjectToSQRCharacter(sChr);
    if (!CNSquirrelAppendage.sq_IsAppendAppendage(sChr, "character/new_mage/doll/ap_doll.nut") )
    {
		appendage.setValid(false);
    }*/
				

}



function onStart_appendage_FRIEND_DOLL(appendage)
{

}

