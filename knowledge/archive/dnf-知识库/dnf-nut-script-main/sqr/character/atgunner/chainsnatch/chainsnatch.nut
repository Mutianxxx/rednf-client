//CUSTOM_ANI_WIND_STRIKE_BODY

function checkExecutableSkill_chainsnatch(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_CHAINSNATCH);

	if (isUse) 
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);	//0, 1, 2, 3
		obj.sq_AddSetStatePacket(STATE_CHAINSNATCH, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}


function checkCommandEnable_chainsnatch(obj)
{
	return true;
}


function onAfterSetState_CHAINSNATCH(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_CHAINSNATCH, STATE_CHAINSNATCH, 0, 1.0); 
	local attackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.getVar("snatchstate").clear_vector();
	obj.getVar("snatchstate").push_vector( substate );
}

function onProcCon_CHAINSNATCH(obj)
{
	if (!obj) 
		return false;
	local substate = obj.getVar("snatchstate").get_vector(0);
	obj.setSkillCommandEnable(SKILL_CHAINSNATCH, true);
	if(substate==2 && obj.sq_IsEnterSkill(SKILL_CHAINSNATCH) != -1){
		//obj.sq_IntVectClear();
		//obj.sq_IntVectPush(3);
		//obj.sq_AddSetStatePacket(STATE_CHAINSNATCH, STATE_PRIORITY_IGNORE_FORCE, true);
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(53, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}