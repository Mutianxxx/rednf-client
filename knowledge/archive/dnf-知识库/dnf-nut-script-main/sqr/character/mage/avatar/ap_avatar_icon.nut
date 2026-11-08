
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_mage_avatar_icon") 
}

function proc_appendage_mage_avatar_icon(appendage) {
	if (!appendage) return;
	local parentObj = appendage.getParent();
	if (parentObj.isDead()) {
		appendage.setValid(false);
		return;
	}
}