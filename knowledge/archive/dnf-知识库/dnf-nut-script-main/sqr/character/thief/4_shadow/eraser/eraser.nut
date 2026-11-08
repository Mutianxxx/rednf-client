function onSetState_Eraser(obj, state, datas, isResetTimer)
{
	local substate = obj.sq_GetVectorData(datas, 0);
    obj.getVar("value").clear_vector();
    obj.getVar("value").push_vector(substate);
}

function onEndCurrentAni_Eraser(obj)
{
    if (isAssassin(obj))
    {
        if (obj.getVar("value").get_vector(0) == 18)
        {
            local damage = obj.sq_GetBonusRateWithPassive(8 , -1, 4, 1.0);
            sendOneHitAllMonsterShaowAreaObj(obj,damage);
        }
    }
}