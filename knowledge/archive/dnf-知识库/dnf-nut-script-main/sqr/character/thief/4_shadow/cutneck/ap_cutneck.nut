
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_CUTNECK")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_CUTNECK")
}
function sq_AddEffect(appendage)
{
}



function proc_appendage_CUTNECK(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				

	if(!sourceObj || !parentObj || sourceObj.getState() == STATE_STAND) 
    {
		appendage.setValid(false);
		return;
	}
	if (checkIsHoldAndDelayEffect(parentObj) && parentObj.getState() != STATE_DOWN )
	{
        local pIntVec = sq_GetGlobalIntVector();
        sq_IntVectorClear(pIntVec);
        sq_IntVectorPush(pIntVec, parentObj.getDirection());
        sq_IntVectorPush(pIntVec, 0);
        sq_IntVectorPush(pIntVec, DOWN_PARAM_TYPE_FORCE);
        sq_IntVectorPush(pIntVec, 0);
        sq_IntVectorPush(pIntVec, 10);
        parentObj.addSetStatePacket(STATE_DOWN, pIntVec, STATE_PRIORITY_FORCE, false, "");
			
    }
			
}



function onStart_appendage_CUTNECK(appendage)
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

