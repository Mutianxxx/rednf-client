
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BESTOMMASTER")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BESTOMMASTER")
}



function sq_AddEffect(appendage)
{
}

function proc_appendage_BESTOMMASTER(appendage)
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
	if (appendage.getVar("flag").get_vector(0) == 0)
	{
		appendage.getVar("flag").clear_vector();
		appendage.getVar("flag").push_vector(1);
		local parentObj = appendage.getParent();
		local sourceObj = appendage.getSource();
		local posX = sq_GetDistancePos(sourceObj.getXPos(), sourceObj.getDirection(), 50);
		sq_BinaryStartWrite();
		sq_BinaryWriteDword(0);	// attackBonusRate
		sq_SendCreatePassiveObjectPacketPos(sourceObj, 24332, 0, posX, sourceObj.getYPos() + 1, 0);
	}

}



function onStart_appendage_BESTOMMASTER(appendage)
{

    appendage.getVar("flag").clear_vector();
    appendage.getVar("flag").push_vector(0);

}

