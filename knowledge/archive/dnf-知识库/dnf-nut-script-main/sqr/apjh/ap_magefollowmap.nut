
function sq_AddFunctionName(appendage) {
	appendage.sq_AddFunctionName("proc", "proc_appendage_mageFollowMap")
	appendage.sq_AddFunctionName("onDamageParent", "onDamageParent_appendage_mageFollowMap")
}

function onDamageParent_appendage_mageFollowMap(appendage ,attacker, boundingBox, isStuck) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();
	obj = sq_GetCNRDObjectToSQRCharacter(obj);
	
	appendage.setValid(false);
}

function proc_appendage_mageFollowMap(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();
	obj = sq_GetCNRDObjectToSQRCharacter(obj);
				
	if (!obj) {
		appendage.setValid(false);
		return;
	}
	
	if (!obj.isDownSkillLastKey()) {
		local index = obj.getVar("followSkillIndex").getInt(0);
        obj.sq_IntVectClear();
        obj.sq_IntVectPush(1);
        obj.sq_AddSetStatePacket(index, STATE_PRIORITY_USER, true);
		appendage.setValid(false);
    }
}


