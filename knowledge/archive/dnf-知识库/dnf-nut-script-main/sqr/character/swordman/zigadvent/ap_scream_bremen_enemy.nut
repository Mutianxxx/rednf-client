
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_scream_bremen_enemy")
	appendage.sq_AddFunctionName("proc", "proc_appendage_scream_bremen_enemy")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_scream_bremen_enemy")
}



function sq_AddEffect(appendage)
{

}



function onStart_appendage_scream_bremen_enemy(appendage)
{
	if(!appendage) 
	{
		return;
	}
	local parentObj = appendage.getParent();
	als_ani(parentObj, "common/commoneffect/animation/disenchanted.ani", 0, 0, 0, 0, 100, 0, 1, 1.0);
}



function proc_appendage_scream_bremen_enemy(appendage)
{
	if(!appendage)
	{
		return;
	}
}



function onEnd_appendage_scream_bremen_enemy(appendage)
{
	if(!appendage) 
	{
		return;
	}
}


