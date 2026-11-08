
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_curseofbloodyfruit")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_curseofbloodyfruit")
}


function sq_AddEffect(appendage)
{

}

function proc_appendage_curseofbloodyfruit(appendage)
{
	if(!appendage) {
		return;
	}
	
}


function onStart_appendage_curseofbloodyfruit(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();	
	local obj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	local stage = sq_GetGlobaludpModuleStage();
	if (!stage) return false;

	local dungeon = sq_GetDungeonByStage(stage);
	if (!dungeon) return false;
	local dungeonIndex = sq_GetDuegonIndex(dungeon);
	local alpha = 50;
	if(dungeonIndex>=9700&&dungeonIndex<9720)
	{
		alpha = 50 + (dungeonIndex - 9700)*5;
	}
	CreateBlindDarkEffect(obj, alpha);
}