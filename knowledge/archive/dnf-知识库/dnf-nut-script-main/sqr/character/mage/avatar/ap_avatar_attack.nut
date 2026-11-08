
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_mage_avatar_attack") 
}


function proc_appendage_mage_avatar_attack(append)
{
	if (!append) return;
	local sourceObj = append.getSource();
	if (!sourceObj)
	{
		append.setValid(false);
		return;
	}
}


