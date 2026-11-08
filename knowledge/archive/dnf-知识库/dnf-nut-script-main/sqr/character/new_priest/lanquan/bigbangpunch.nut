

SUB_STATE_PUNCH		<- 0


function checkExecutableSkill_priest_bigbangpunch(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(90);
	local skill = sq_GetSkill(obj, 90);
	if (isUse && !skill.isSealFunction())
	{

       	obj.sq_IntVectClear();
        	obj.sq_IntVectPush(4);
        	obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(50, STATE_PRIORITY_USER, true);
		return true;
	}
	else if (isUse && skill.isSealFunction())
	{

        	obj.sq_IntVectClear();
        	obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(50, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_priest_bigbangpunch(obj)
{

	return true;
}


function onAfterSetState_priest_bigbangpunch(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	local subState1 = obj.sq_GetVectorData(datas, 1);
	obj.getVar("bigbangstate").clear_vector();
	obj.getVar("bigbangstate").push_vector( substate );
	SUB_STATE_PUNCH = subState1;
}

function onProcCon_priest_bigbangpunch(obj)
{
	if (!obj) 
		return false;
	local substate = obj.getVar("bigbangstate").get_vector(0)
	local skill = sq_GetSkill(obj, 90);
	if(substate==1&& !skill.isSealFunction()){
		SUB_STATE_PUNCH = 3;
		obj.sq_IntVectClear();
        	obj.sq_IntVectPush(4);
        	obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(50, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}
/*
function onBeforeAttack_priest_bigbangpunch(obj, damager, boundingBox, isStuck)
{
	local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 90, false, "character/new_priest/lanquan/ap_priest_bigbangpunch.nut", true);
//sq_AddMessage(22);	
    if (!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/new_priest/lanquan/ap_priest_bigbangpunch.nut"))
    {
		//sq_AddMessage(33);	
			CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/new_priest/lanquan/ap_priest_bigbangpunch.nut");		
    }
}*/
function onKeyFrameFlag_priest_bigbangpunch(obj,flagIndex)
{
	if(!obj || SUB_STATE_PUNCH) return false;
	obj.sq_IntVectClear();
	obj.sq_IntVectPush(flagIndex);
	obj.sq_IntVectPush(1);
	obj.sq_AddSetStatePacket(50, STATE_PRIORITY_IGNORE_FORCE, true);
	return true;
}
