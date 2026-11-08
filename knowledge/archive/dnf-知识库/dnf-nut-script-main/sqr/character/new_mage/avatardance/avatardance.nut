function checkExecutableSkill_avatardance(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_AVATARDANCE);
	if (isUseSkill) 
    {

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_AVATARDANCE, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_avatardance(obj)
{

	return true;
}



function onSetState_AVATARDANCE(obj, state, datas, isResetTimer)
{

	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);


    obj.sq_SetCurrentAnimation(CUSTOM_ANI_AVATARDANCE0 + state);
    if (state == 0)
    {
		sq_flashScreen(obj,0,0,180,150, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        obj.getVar("dama").clear_obj_vector();
    }

    if (state == 1)
    {

		obj.sq_SetCurrentAttackInfo(ATTACKINFO_AVATARDANCE0);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_AVATARDANCE , STATE_AVATARDANCE, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				
    }

    if (state == 2)
    {

		obj.sq_SetCurrentAttackInfo(ATTACKINFO_AVATARDANCE1);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_AVATARDANCE , STATE_AVATARDANCE, 1, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

    }

    if (state == 3)
    {

		obj.sq_SetCurrentAttackInfo(ATTACKINFO_AVATARDANCE2);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_AVATARDANCE , STATE_AVATARDANCE, 2, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

    }

    if (state == 4)
    {
		local speed = 100;
		obj.sq_SetStaticMoveInfo(0, speed, speed, false);	
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);	

        obj.sq_SetShake(obj, 6, 150);
    }
    if (state == 5)
    {
		local speed = 400;
		obj.sq_SetStaticMoveInfo(0, speed, speed, false);	
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);	
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_AVATARDANCE3);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_AVATARDANCE , STATE_AVATARDANCE, 3, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

    }

    if (state == 7)
    {
        sq_flashScreen(obj,0,0,150,150, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        obj.sq_SetShake(obj, 8, 400);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_AVATARDANCE4);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_AVATARDANCE , STATE_AVATARDANCE, 4, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				
    }

}

function onProc_AVATARDANCE(obj)
{
    local state = obj.getVar("state").get_vector(0);
	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);

    if (state >= 5 && state < 7)
    {
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),140);

    }
    if (state == 0)
    {
        if (frmIndex == 3)
        {
            sq_flashScreen(obj,0,0,150,150, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        }
    }

    if (state == 1)
    {
        if (frmIndex == 1)
        {
            obj.sq_SetShake(obj, 6, 150);
        }
    }

    if (state == 2)
    {

        if (frmIndex == 2)
        {
            obj.sq_SetShake(obj, 6, 150);
        }
    }

    if (state == 3)
    {

        if (frmIndex == 2)
        {
            obj.sq_SetShake(obj, 6, 150);
        }
    }


}
function onAttack_AVATARDANCE(obj, damager, boundingBox, isStuck)
{

    local state = obj.getVar("state").get_vector(0);

    if (sq_IsFixture(damager))
        return false;
    if (state >=0 && state <= 5)
    {
        local dvalue = 1;
        if (sq_GetDirection(obj) == ENUM_DIRECTION_LEFT) dvalue = -1;
        if (state <= 2)
        {

            damager.setCurrentPos(obj.getXPos()+132*dvalue,obj.getYPos(),0);

        }else{

            damager.setCurrentPos(obj.getXPos() +309*dvalue,obj.getYPos(),0);
        }



    }


    if (state <= 6)
    {
        if (!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/new_mage/avatardance/ap_avatardance.nut"))
        {
            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODSONG, false, "character/new_mage/avatardance/ap_avatardance.nut", true);				 
            if(masterAppendage) 
            {
                sq_HoldAndDelayDie(damager, obj, true, true, true, 0, 0, ENUM_DIRECTION_DOWN , masterAppendage);
            }
        }
    }else{

        if(damager)
        {
            CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/new_mage/avatardance/ap_avatardance.nut");		
        }

    }
}

function onEndCurrentAni_AVATARDANCE(obj)
{
    local state = obj.getVar("state").get_vector(0);

    if (state < 7)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(state + 1);
		obj.sq_AddSetStatePacket(STATE_AVATARDANCE, STATE_PRIORITY_USER, true);

    }else{

		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }

}