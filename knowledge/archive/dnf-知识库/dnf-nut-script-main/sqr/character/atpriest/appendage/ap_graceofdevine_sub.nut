function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onVaildTimeEnd", "onVaildTimeEnd_appendage_graceofdevine_sub")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_graceofdevine_sub")
	
}

function onEnd_appendage_graceofdevine_sub(appendage)
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
		pObj.getVar("DevineCount").setInt(0, 0);
	local pChr = sq_GetCNRDObjectToSQRCharacter(obj);
	if(pChr)
		pChr.getVar("DevineCount").setInt(0, 0);
}

function onVaildTimeEnd_appendage_graceofdevine_sub(appendage)
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
		local buffcount = pObj.getVar("DevineCount").getInt(0);
		if(buffcount > 0)
			pObj.getVar("DevineCount").setInt(0, 0);
	}
	
	local pChr = sq_GetCNRDObjectToSQRCharacter(pObj);
	if(pChr){
		if(buffcount > 0)
			pChr.getVar("DevineCount").setInt(0, 0);
	}
	
}