
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_guillotineme")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_guillotineme")
}
function sq_AddEffect(appendage)
{
}

function proc_appendage_guillotineme(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				

	if(!sourceObj || !parentObj ) 
    {
		appendage.setValid(false);
		return;
	}
 
}

function onStart_appendage_guillotineme(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	local time = parentObj.sq_GetIntData(SKILL_GUILLOTINE, 10);
	sq_SendMessage(parentObj, OBJECT_MESSAGE_INVINCIBLE, 1, 0);
	sq_PostDelayedMessage(parentObj, OBJECT_MESSAGE_INVINCIBLE, 0, 0, time);
}

