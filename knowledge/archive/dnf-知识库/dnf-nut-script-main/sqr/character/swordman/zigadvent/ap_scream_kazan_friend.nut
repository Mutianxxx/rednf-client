//////////////////////////////////////////////////////////////////////////////////////////////////
//									By Uncle Bang
//////////////////////////////////////////////////////////////////////////////////////////////////








function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_scream_kazan_friend")
	appendage.sq_AddFunctionName("proc", "proc_appendage_scream_kazan_friend")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_scream_kazan_friend")
}



function sq_AddEffect(appendage)
{

}



function onStart_appendage_scream_kazan_friend(appendage)
{
	if(!appendage) 
	{
		return;
	}
	appendage.setBuffIconImage(154);
}



function proc_appendage_scream_kazan_friend(appendage)
{
	if(!appendage)
	{
		return;
	}
}



function onEnd_appendage_scream_kazan_friend(appendage)
{
	if(!appendage) 
	{
		return;
	}
}


