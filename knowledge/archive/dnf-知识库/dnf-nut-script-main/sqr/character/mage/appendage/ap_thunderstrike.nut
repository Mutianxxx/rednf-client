function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_thunderstrike")
}


function proc_appendage_thunderstrike ( appendage ) {
    if(!appendage) {
		return;		
	}
    
    local obj = sq_GetCNRDObjectToSQRCharacter(appendage.getParent());
    	local skill = sq_GetSkill(obj, 167);
	if(!skill){
		return;
	}
	if(skill.isSealFunction()){
		return;
	}
    local thunder = obj.getMyPassiveObject(23020, 0); //???å¤©é???????????
    if(thunder) {
        local x = thunder.getXPos();
        local y = thunder.getYPos();
        local thunder1 = obj.getMyPassiveObject(9001001, 1); //???å¤©é??????å­???????
        if(!thunder1){
            sq_SendCreatePassiveObjectPacketPos( obj, 90010001, 1, x, y, 0);
			return;
        }
    }
}
