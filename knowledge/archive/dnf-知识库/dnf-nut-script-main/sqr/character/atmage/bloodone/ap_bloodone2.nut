function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_bloodone2")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_bloodone2")
}


function sq_AddEffect(appendage)
{
}

function proc_appendage_bloodone2(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(parentObj);

    sqrChr.setShowEquipmentLayer(ENUM_EQUIPMENTTYPE_WEAPON, false);
}


function onStart_appendage_bloodone2(appendage)
{
	if(!appendage) {
		return;
	}
	

}