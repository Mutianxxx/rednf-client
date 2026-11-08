function setCustomData_po_null85_loop_0(obj, receiveData)
{
	local id = receiveData.readDword();
    if (id == 0)
    {
        local ani = obj.getCustomAnimation(0);
		obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 0);
        sq_SetCurrentAttackInfo(obj, attackInfo);

        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        local power = mage.sq_GetPowerWithPassive(SKILL_NULL50, STATE_NULL50, 0, -1, 1.0);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, power);

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        createNull50SummonEffect(obj);
        createNull50SummonEffectGround(obj);
        sq_SetMyShake(obj,6,300);

    }else if (id == 1)
    {
        local ani = obj.getCustomAnimation(1);
		obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 1);
        sq_SetCurrentAttackInfo(obj, attackInfo);

        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        local power = mage.sq_GetPowerWithPassive(SKILL_NULL50, STATE_NULL50, 1, -1, 1.0);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, power);
        obj.setTimeEvent(0,mage.sq_GetIntData(SKILL_NULL50, 1),0,false);
        createNull50Ground1(obj);
        createNull50Hit1(obj);
        sq_SetMyShake(obj,1,900);
        
    }else if (id == 2)
    {
        local ani = obj.getCustomAnimation(2);
		obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 2);
        sq_SetCurrentAttackInfo(obj, attackInfo);

        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        local power = mage.sq_GetPowerWithPassive(SKILL_NULL50, STATE_NULL50, 1, -1, 1.0);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, power);
        obj.setTimeEvent(0,mage.sq_GetIntData(SKILL_NULL50, 1),0,false);
        createNull50Ground2(obj);
        createNull50Hit2(obj);
        sq_SetMyShake(obj,1,900);
    }else if (id == 3)
    {
        local ani = obj.getCustomAnimation(3);
		obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 3);
        sq_SetCurrentAttackInfo(obj, attackInfo);

        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        local power = mage.sq_GetPowerWithPassive(SKILL_NULL50, STATE_NULL50, 1, -1, 1.0);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, power);
        obj.setTimeEvent(0,mage.sq_GetIntData(SKILL_NULL50, 1),0,false);
        createNull50Ground3(obj);
        createNull50Hit3(obj);
        sq_SetMyShake(obj,1,900);
    }else if (id == 4)
    {
        local ani = obj.getCustomAnimation(4);
		obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 4);
        sq_SetCurrentAttackInfo(obj, attackInfo);

        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        local power = mage.sq_GetPowerWithPassive(SKILL_NULL50, STATE_NULL50, 1, -1, 1.0);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, power);
        obj.setTimeEvent(0,mage.sq_GetIntData(SKILL_NULL50, 1),0,false);
        createNull50Ground4(obj);
        createNull50Hit4(obj);
        createNull50Hit5(obj);
        createNull50FinishFront(obj);
    }else if (id == 5)
    {
        local ani = obj.getCustomAnimation(5);
		obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 5);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        local power = mage.sq_GetPowerWithPassive(SKILL_NULL50, STATE_NULL50, 2, -1, 1.0);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, power);
        createNull50Ground5(obj);


        
    }else if (id == 6)
    {
        local power = receiveData.readDword();
        local atkT = receiveData.readDword();
        obj.setTimeEvent(0,atkT,0,false);
        local ani = obj.getCustomAnimation(6);
		obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 6);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, power);

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);


    }
    obj.getVar("id").clear_vector();
    obj.getVar("id").push_vector(id);
}

function onKeyFrameFlag_po_null85_loop_0(obj, flagIndex)
{
    local id = obj.getVar("id").get_vector(0);
    if (id == 0)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").set_vector(0,1);
            sq_BinaryStartWrite();
            sq_BinaryWriteDword(1 );	// attackBonusRate
            sq_SendCreatePassiveObjectPacketPos(obj,24339, 0, obj.getXPos() , obj.getYPos() , obj.getZPos());
        }
    }else if (id == 5)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").set_vector(0,1);
            sq_SetMyShake(obj,7,400);
            sq_flashScreen(obj,0,100,0,127, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        }
    }else if (id == 6)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").set_vector(0,1);
            sq_SetMyShake(obj,4,3000);
        }
    }
}
function onTimeEvent_po_null85_loop_0(obj, timeEventIndex, timeEventCount)
{
    local id = obj.getVar("id").get_vector(0);
    if (id == 1 || id == 2 || id  == 3 || id == 4 || id == 6)
    {
            obj.resetHitObjectList();
    }
}


function onEndCurrentAni_po_null85_loop_0(obj)
{
    local id = obj.getVar("id").get_vector(0);
    if (id == 0)
    {

            sq_SendDestroyPacketPassiveObject(obj);	
    }else if (id == 1)
    {
            sq_BinaryStartWrite();
            sq_BinaryWriteDword(2 );	// attackBonusRate
            sq_SendCreatePassiveObjectPacketPos(obj,24339, 0, obj.getXPos() , obj.getYPos() , obj.getZPos());
            sq_SendDestroyPacketPassiveObject(obj);	
    }else if (id == 2)
    {
            sq_BinaryStartWrite();
            sq_BinaryWriteDword(3);	// attackBonusRate
            sq_SendCreatePassiveObjectPacketPos(obj,24339, 0, obj.getXPos() , obj.getYPos() , obj.getZPos());
            sq_SendDestroyPacketPassiveObject(obj);	
    }else if (id == 3)
    {
            sq_BinaryStartWrite();
            sq_BinaryWriteDword(4 );	// attackBonusRate
            sq_SendCreatePassiveObjectPacketPos(obj,24339, 0, obj.getXPos() , obj.getYPos() , obj.getZPos());
            sq_SendDestroyPacketPassiveObject(obj);	
    }else if (id == 4)
    {
            sq_BinaryStartWrite();
            sq_BinaryWriteDword(5 );	// attackBonusRate
            sq_SendCreatePassiveObjectPacketPos(obj,24339, 0, obj.getXPos() , obj.getYPos() , obj.getZPos());
            sq_SendDestroyPacketPassiveObject(obj);	
    }else if (id == 5)
    {
            sq_SendDestroyPacketPassiveObject(obj);	
    }else if (id == 6)
    {
            sq_SendDestroyPacketPassiveObject(obj);	
    }
}


function onAttack_po_null85_loop_0(obj,damager, boundingBox, isStuck)
{

}