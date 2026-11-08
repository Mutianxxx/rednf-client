

function onAttack_ATMageDashAttack(obj, damager, boundingBox, isStuck)
{
    if (!obj.isMyControlObject() )
        return false;

    local appendage2 = obj.GetSquirrelAppendage("character/atmage/attack/ap_bloodoath.nut");
    if (appendage2)
    {
       

        if (damager && !CNSquirrelAppendage.sq_IsAppendAppendage(damager,
            "character/atmage/append_bloodmage/ap_dash.nut"))
        {
            local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODOATH, false, 
            "character/atmage/append_bloodmage/ap_dash.nut", true);
             local ani = sq_AddDrawOnlyAniFromParent(damager, "passiveobject/zrr_skill/atmage/animation/hiteffect/bloodslashsmall2_01.ani", 0, 1, damager.getObjectHeight()/2);
		sq_moveWithParent(damager, ani);
            
        }

        if (obj)
        {
            local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BLOODOATH, false, 
            "character/atmage/append_bloodmage/ap_dash_character.nut", true);
            
        }



    }

}

function onSetState_ATMageDashAttack(obj, state, datas, isResetTimer)
{	
	if (!obj)
		return;

	local skillLevel = obj.sq_GetSkillLevel(SKILL_ICE_ELEMENTAL_ATTACK);

    local skillLevel3 = obj.sq_GetSkillLevel(SKILL_STICKMASTER);



    if (skillLevel > 0)
    {
        local skill = sq_GetSkill(obj, SKILL_ICE_ELEMENTAL_ATTACK);
        if (skill.isSealFunction() )
        {
            skillLevel = 0;
        }
    }


	if (skillLevel > 0)
	{
		local isPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL) || 
                        sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL);
		

		if(!isPress)
			obj.sq_SetStaticMoveInfo(0, 450, 450, false, -500, true);
		
	}
	else
	{
		obj.sq_SetStaticMoveInfo(0, 450, 450, false, -500, true);
	}



	if (skillLevel3 > 0)
	{
		local isPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL) || 
                        sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL);
		

		if(!isPress)
			obj.sq_SetStaticMoveInfo(0, 450, 450, false, -500, true);
		
        obj.setTimeEvent(0, obj.sq_GetIntData(SKILL_STICKMASTER,4), 0, true);
	}
	obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),obj.getState());		
	sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
}

function onTimeEvent_ATMageDashAttack(obj, timeEventIndex, timeEventCount)
{
    if (timeEventIndex == 0)
    {
        obj.resetHitObjectList();
    }
}

function onKeyFrameFlag_ATMageDashAttack(obj, flagIndex)
{
	if(!obj)
		return false;
	if (flagIndex == 1)
	{
		// ??????u?? ???????.
		if (obj.sq_IsMyControlObject())
		{
			// ?????? ???u? ????????? ??????
			local passiveObjectIndex = 24261;
			local power = -25;
			// ????u ????? ????
			local skill = sq_GetSkill(obj, SKILL_ELEMENTAL_CHANGE);
			local skillLevel = sq_GetSkillLevel(obj, SKILL_ELEMENTAL_CHANGE);
			if(!skillLevel){
				skillLevel = 1;
			}
			local attackBonusRate = 0;
			local sizeRate = sq_GetIntData(obj, SKILL_ELEMENTAL_CHANGE, 2);;
			// ?????? appendage?? ???????? u???.
			local element = obj.getThrowElement();
			
			// ???????? ??????? ???? ????? ????? ?????
			local appendage = obj.GetSquirrelAppendage("Character/ATMage/ElementalChange/ap_ATMage_Elemental_Change.nut");
			if (!appendage || !appendage.isValid())
				element = ENUM_ELEMENT_NONE;

			if (element != ENUM_ELEMENT_NONE)
			{
				if (element == ENUM_ELEMENT_FIRE){
					attackBonusRate = sq_GetBonusRateWithPassive(obj, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 1, 1.0) ;
					sizeRate = sizeRate*2;
					passiveObjectIndex = 24262;
				}

				else if (element == ENUM_ELEMENT_WATER){
					attackBonusRate = sq_GetBonusRateWithPassive(obj, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 2, 1.0) ;
					passiveObjectIndex = 24263;
				}
				else if (element == ENUM_ELEMENT_DARK){
					attackBonusRate = sq_GetBonusRateWithPassive(obj, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 6, 1.0) ;
					sizeRate = (sizeRate*1.5).tointeger();
					passiveObjectIndex = 24264;
				}
				else if (element == ENUM_ELEMENT_LIGHT){
					attackBonusRate = sq_GetBonusRateWithPassive(obj, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 10, 1.0) ;
					passiveObjectIndex = 24265;
				}

			}
			
			sq_SetCurrentAttackBonusRate(sq_GetCurrentAttackInfo(obj),attackBonusRate-power);
			obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),obj.getState());					
			power = sq_GetCurrentAttackBonusRate(obj);
			sq_SetCurrentAttackBonusRate(sq_GetCurrentAttackInfo(obj),-25);

			obj.sq_StartWrite();
			obj.sq_WriteWord(sizeRate);	// ?????? ??????(%)
			obj.sq_WriteWord(power);	// ?????? ?????(%)
			obj.sq_SendCreatePassiveObjectPacket(passiveObjectIndex, 0, 100, 1, 55);
		}
	}

	return true;
}
