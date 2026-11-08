
function onSetState_ATPriestAttack(obj, state, datas, isResetTimer)
{
	if(!obj) return
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
}

function onAttack_ATPriestAttack(obj, damager, boundingBox, isStuck)
{
	local attackIndex = obj.getAttackIndex();
}

function onAfterSetState_ATPriestAttack(obj, state, datas, isResetTimer)
{
	local substate = obj.sq_GetVectorData(datas, 0);
}