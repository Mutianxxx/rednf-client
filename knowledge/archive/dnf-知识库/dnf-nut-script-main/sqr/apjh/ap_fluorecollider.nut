function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_fluorecollider")
}

function proc_appendage_fluorecollider ( appendage ) {
    if(!appendage) {
	return;
    }

    local obj = sq_GetCNRDObjectToSQRCharacter(appendage.getParent());
    local skill = sq_GetSkill(obj, 168);
    if(!skill){
		return;
    }
    if(skill.isSealFunction()){
		return;
    }
    local time = obj.sq_GetStateTimer();
    if(time > 200) {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	 obj.sq_SendCreatePassiveObjectPacket(90010004, 0, 100, 0, 0);
	obj.sq_StartWrite();
	obj.sq_WriteDword(105); 
 	obj.sq_WriteDword(obj.sq_GetPowerWithPassive(105, STATE_STAND, 4, -1, 1.0)); //sq_GetPowerWithPassive(SKILL_NULL50, STATE_NULL50, 1, -1, 1.0);
 	obj.sq_WriteDword(78);
	obj.sq_WriteDword(obj.sq_GetPowerWithPassive(105, STATE_STAND, 4, -1, 1.0)); 
	obj.sq_SendCreatePassiveObjectPacket(24372, 0, 100, 0, 0);
    }
    
}
