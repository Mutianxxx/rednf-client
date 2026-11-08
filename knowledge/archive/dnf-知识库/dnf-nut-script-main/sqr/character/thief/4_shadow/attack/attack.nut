



function onSetState_ThiefAttack(obj, state, datas, isResetTimer)
{	

    local attackIndex = obj.getAttackIndex();
    if (isAssassin(obj))
    {
        obj.getVar("isBack").clear_vector();
        obj.getVar("isBack").push_vector(0);
    }

    if (attackIndex == 25)
    {

    }
}

function onEndState_ThiefAttack(obj,new_state)
{
    local attackIndex = obj.getAttackIndex();
    if (attackIndex == 25 && new_state != STATE_ATTACK)
    {
        local pAni = sq_GetCurrentAnimation(obj);
        if(pAni)
            pAni.setFrameDelay(1,80,true);

    }
}

function onAfterSetState_ThiefAttack(obj, state, datas, isResetTimer)
{

    local attackIndex = obj.getAttackIndex();
    if (attackIndex == 25)
    {
        local pAni = sq_GetCurrentAnimation(obj);
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);

        if(pAni)
            pAni.setFrameDelay(1,9999,true);

    }
}

function onProc_ThiefAttack(obj)
{

    local atk = obj.getAttackIndex();
    if (atk == 25)
    {
        local oobj = getBellacreObject(obj);
        if (!oobj)
        {
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
        }else
        {
            local pAni = sq_GetCurrentAnimation(oobj);
            local frmIndex = sq_GetAnimationFrameIndex(pAni);
            if (frmIndex >= 21)
            {
                obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
            
            }else
			{
				if (frmIndex >= 4 && obj.getVar("flag").get_vector(0) == 0)
				{
					obj.sq_SetShake(obj, 4, 160);
					obj.getVar("flag").set_vector(0,1);
				}else if (frmIndex >= 16 && obj.getVar("flag").get_vector(1) == 0)
				{
					obj.sq_SetShake(obj, 7, 400);
					sq_flashScreen(obj,0,120,320,255, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
					obj.getVar("flag").set_vector(1,1);
				}
			
			}
            
        }
    }
}

function onAttack_ThiefAttack(obj, damager, boundingBox, isStuck)
{
	local attackIndex = obj.getAttackIndex();
	if (isAssassin(obj) && attackIndex == 3)
	{
		damager.setDirection(obj.getDirection());
		local damage = sq_GetCurrentAttackBonusRate(obj);
		sendOneHitAllMonsterShaowAreaObj(obj,damage);
	}
}

/*function onEndCurrentAni_ThiefAttack(obj)
{
    local attackIndex = obj.getAttackIndex();
    if (isAssassin(obj) && attackIndex == 2)
    {
		local damage = sq_GetCurrentAttackBonusRate(obj);
        sendOneHitAllMonsterShaowAreaObj(obj,damage);
    }
}*/
