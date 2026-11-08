function onAfterSetState_CHAINSNATCHSUB(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_CHAINSNATCH, 53, 1, 1.0); 
	local attackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.getVar("snatchsubstate").clear_vector();
	obj.getVar("snatchsubstate").push_vector( substate );
}


function onEndCurrentAni_CHAINSNATCHSUB(obj)
{
	if (!obj) 
		return false;
	local substate = obj.getVar("snatchsubstate").get_vector(0);
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(53, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
}
