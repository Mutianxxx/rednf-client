function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onVaildTimeEnd", "onVaildTimeEnd_appendage_RoseinDark")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_RoseinDark")
	
}

function onEnd_appendage_RoseinDark(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	if(!obj) 
	{
		appendage.setValid(false);
		return;
	}
	local pObj = sq_GetCNRDObjectToActiveObject(obj);
	if(pObj)
		pObj.getVar("RoseinDarkCount").setInt(0, 0);
	local pChr = sq_GetCNRDObjectToSQRCharacter(obj);
	if(pChr)
		pChr.getVar("RoseinDarkCount").setInt(0, 0);
}

function onVaildTimeEnd_appendage_RoseinDark(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	if(!obj)
	{
		appendage.setValid(false);
		return;
	}
	
	local pObj = sq_GetCNRDObjectToActiveObject(obj);
	if(pObj){
		local buffcount = pObj.getVar("RoseinDarkCount").getInt(0);
		if(buffcount > 0)
			pObj.getVar("RoseinDarkCount").setInt(0, 0);
	}
	
	local pChr = sq_GetCNRDObjectToSQRCharacter(pObj);
	if(pChr){
		if(buffcount > 0)
			pChr.getVar("RoseinDarkCount").setInt(0, 0);
	}
	
}