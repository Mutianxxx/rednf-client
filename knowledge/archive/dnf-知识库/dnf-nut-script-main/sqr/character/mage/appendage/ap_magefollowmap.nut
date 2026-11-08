
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
	
    local index = obj.getVar("followSkillIndex").getInt(0);
	if(index==253){
		if((obj.getVar("ctrlKey").getBool(0)==false)&&(!obj.isDownSkillLastKey())){
			obj.sq_IntVectClear();
        	obj.sq_IntVectPush(1);
			obj.sq_IntVectPush(10000);
        	obj.sq_AddSetStatePacket(253, STATE_PRIORITY_USER, true);
			appendage.setValid(false);
		}
	}else{
		if (!obj.isDownSkillLastKey()) {
        	obj.sq_IntVectClear();
        	obj.sq_IntVectPush(1);
			obj.sq_IntVectPush(10000);
        	obj.sq_AddSetStatePacket(index, STATE_PRIORITY_USER, true);
			appendage.setValid(false);
    	}
	}

}


