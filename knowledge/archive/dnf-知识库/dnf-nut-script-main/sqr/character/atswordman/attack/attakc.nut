
function onSetState_AtSwordman_Attack(obj, CQv6OzwmIj1E6CChMNnO, CQiCltjh3oye1qXcjv9, CQ1SLFG1yM8v7d6T)
{
	if(!obj) return
local CQUiQ2uiZvsh2s5bbf = obj.sq_GetVectorData(CQiCltjh3oye1qXcjv9, 0)
obj.setSkillSubState(CQUiQ2uiZvsh2s5bbf)
obj.sq_StopMove()
local CQHm4Tcbjuj5Vg5xquxg = obj.sq_GetBonusRateWithPassive(174, -1, 0, getATSwordmanBonus(obj,1.0,-1))/10+100
switch(CQUiQ2uiZvsh2s5bbf)
	{
	case 0:
		obj.sq_SetCurrentAttackInfo(0)
		local CQjTEe6fSBGV3X4mI = 100
		if(sq_GetSkillLevel(obj, 3) > 0)
		{
			BodyMagicSword(obj, "InnerBladeAttack1")
			obj.sq_SetCurrentAnimation(47)
		}
		else if(sq_GetSkillLevel(obj, 148) > 0)
		{
			BodyCalldaimus(obj, "CallDaimusAttack1")
			obj.sq_SetCurrentAnimation(367)
		}
		else if(sq_GetSkillLevel(obj, 62) > 0)
		{
			obj.sq_SetCurrentAnimation(508)
			obj.sq_SetCurrentAttackInfo(128)
			local CQE83AJS7cvFBm3vSbD = sq_GetLevelData(obj,62, 0, sq_GetSkillLevel(obj, 62))
			CQHm4Tcbjuj5Vg5xquxg = CQHm4Tcbjuj5Vg5xquxg + CQE83AJS7cvFBm3vSbD
		}
		else if(sq_GetSkillLevel(obj, 202) > 0)
		{
			obj.sq_PlaySound("R_SW_1ATK")
			local CQ4BpMitqOCELB3w = checkAppend_Dualweapon(obj)
			obj.sq_SetCurrentAnimation(SetChrAniIndex_Dualweapon(obj,CQ4BpMitqOCELB3w))
			obj.sq_SetCurrentAttackInfo(SetChrAtkIndex_Dualweapon(obj,CQ4BpMitqOCELB3w))
		}
		else
		{
			obj.sq_PlaySound("R_SW_1ATK")
			obj.sq_SetCurrentAnimation(0)
		}
		sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj))
		obj.sq_SetStaticSpeedInfo(2, 2, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
	break
	case 1:
		obj.sq_SetCurrentAttackInfo(1)
		local CQjTEe6fSBGV3X4mI = 120
		if(sq_GetSkillLevel(obj, 3) > 0)
		{
			BodyMagicSword(obj, "InnerBladeAttack2")
			if(MagicSword_IsAppebd(obj))
				obj.sq_SetCurrentAnimation(288)
			else
				obj.sq_SetCurrentAnimation(48)
		}
		else if(sq_GetSkillLevel(obj, 148) > 0)
		{
			BodyCalldaimus(obj, "CallDaimusAttack2")
			obj.sq_SetCurrentAnimation(368)
		}
		else if(sq_GetSkillLevel(obj, 62) > 0)
		{
			obj.sq_SetCurrentAnimation(509)
			obj.sq_SetCurrentAttackInfo(129)
		}
		else if(sq_GetSkillLevel(obj, 202) > 0)
		{
			obj.sq_PlaySound("R_SW_2ATK")
			local CQ4BpMitqOCELB3w = checkAppend_Dualweapon(obj)
		}
		else
		{
			obj.sq_PlaySound("R_SW_2ATK")
			obj.sq_SetCurrentAnimation(1)
		}
		sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj))
		obj.sq_SetStaticSpeedInfo(2, 2, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
	break
	case 2:
		obj.sq_SetCurrentAttackInfo(2)
		local CQjTEe6fSBGV3X4mI = 150
		if(sq_GetSkillLevel(obj, 3) > 0)
		{
			BodyMagicSword(obj, "InnerBladeAttack3")
			if(MagicSword_IsAppebd(obj))
				obj.sq_SetCurrentAnimation(289)
			else
				obj.sq_SetCurrentAnimation(49)
			obj.sq_SetStaticSpeedInfo(2, 2, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
		}
		else if(sq_GetSkillLevel(obj, 148) > 0)
		{
			BodyCalldaimus(obj, "CallDaimusAttack3")
			obj.sq_SetCurrentAnimation(369)
			obj.sq_SetStaticSpeedInfo(2, 2, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
		}
		else if(sq_GetSkillLevel(obj, 62) > 0)
		{
			obj.sq_SetCurrentAnimation(510)
			obj.sq_SetCurrentAttackInfo(130)
			local CQE83AJS7cvFBm3vSbD = sq_GetLevelData(obj,62, 0, sq_GetSkillLevel(obj, 62))
			CQHm4Tcbjuj5Vg5xquxg = CQHm4Tcbjuj5Vg5xquxg + CQE83AJS7cvFBm3vSbD
}
		else if(sq_GetSkillLevel(obj, 202) > 0)
		{
			obj.sq_PlaySound("R_SW_3ATK");
			obj.sq_SetStaticSpeedInfo(2, 2, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
		}
		else
		{
			obj.sq_SetCurrentAnimation(2);
			obj.sq_SetStaticSpeedInfo(2, 2, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
			//obj.sq_PlaySound("R_SW_3ATK");
		}
		obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),obj.getState());
		sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
	break;
	case 3:
		if(sq_GetSkillLevel(obj, 148) > 0)
		{
			BodyCalldaimus(obj, "CallDaimusAttack4")
			obj.sq_SetCurrentAnimation(370)
		}
		obj.sq_SetCurrentAttackInfo(82)
local CQjTEe6fSBGV3X4mI = 150
break
case 4:
		if(sq_GetSkillLevel(obj, 148) > 0)
		{
			BodyCalldaimus(obj, "CallDaimusAttack5")
obj.sq_SetCurrentAnimation(371)
}
		obj.sq_SetCurrentAttackInfo(83)
local CQjTEe6fSBGV3X4mI = 150
break
}
	
	if(sq_GetSkillLevel(obj, 62) > 0)
	{
		local CQXGyaWan2KHsN9taDo = sq_GetCurrentAttackBonusRate(obj)
local CQxHdXlTPnUIDs8w = obj.sq_GetLevelData(62, 0, sq_GetSkillLevel(obj, 62))
obj.sq_SetCurrentAttackBonusRate(CQXGyaWan2KHsN9taDo + CQxHdXlTPnUIDs8w)
}
	
}

function onProcCon_AtSwordman_Attack(obj)
{
	if(!obj) return
	local CQ9exbFEiMWnoO7WLMF1 = obj.getSkillSubState()
	local CQtcXptmVv7TOU6E8 = obj.getCurrentAnimation()
	local CQBfeKzgQya8pV6uRFk = CQtcXptmVv7TOU6E8.GetCurrentFrameIndex()
	if(sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))
	{
		switch(CQ9exbFEiMWnoO7WLMF1)
		{
		case 0:
			if(obj.isCurrentCutomAniIndex(0) && CQBfeKzgQya8pV6uRFk>3)
			{
				obj.sq_IntVectClear()
				obj.sq_IntVectPush(1)
				obj.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true)
			}
			else if(sq_GetSkillLevel(obj, 3) > 0 && CQBfeKzgQya8pV6uRFk>5)
			{
				obj.sq_IntVectClear()
				obj.sq_IntVectPush(1)
				obj.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true)
			}
			else if(sq_GetSkillLevel(obj, 148) > 0 && CQBfeKzgQya8pV6uRFk>2)
			{
				obj.sq_IntVectClear()
				obj.sq_IntVectPush(1)
				obj.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true)
			}
			else if(sq_GetSkillLevel(obj, 62) > 0 && CQBfeKzgQya8pV6uRFk>3)
			{
				obj.sq_IntVectClear()
				obj.sq_IntVectPush(1)
				obj.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true)
			}
			else if(sq_GetSkillLevel(obj, 202) > 0 && CQBfeKzgQya8pV6uRFk>2)
			{
				obj.sq_IntVectClear()
				obj.sq_IntVectPush(1)
				obj.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true)
			}
			break
		case 1:
			if(obj.isCurrentCutomAniIndex(1) && CQBfeKzgQya8pV6uRFk>3)
			{
				obj.sq_IntVectClear()
				obj.sq_IntVectPush(2)
				obj.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true)
			}
			else if(sq_GetSkillLevel(obj, 3) > 0 && CQBfeKzgQya8pV6uRFk>5)
			{
				obj.sq_IntVectClear()
				obj.sq_IntVectPush(2)
				obj.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true)
			}
			else if(sq_GetSkillLevel(obj, 148) > 0 && CQBfeKzgQya8pV6uRFk>3)
			{
				obj.sq_IntVectClear()
				obj.sq_IntVectPush(2)
				obj.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true)
			}
			else if(sq_GetSkillLevel(obj, 62) > 0 && CQBfeKzgQya8pV6uRFk>2)
			{
				obj.sq_IntVectClear()
				obj.sq_IntVectPush(2)
				obj.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true)
			}
			else if(sq_GetSkillLevel(obj, 202) > 0 && CQBfeKzgQya8pV6uRFk>3)
			{
				obj.sq_IntVectClear()
				obj.sq_IntVectPush(2)
				obj.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true)
			}
			break
		case 2:
			if(sq_GetSkillLevel(obj, 148) > 0 && CQBfeKzgQya8pV6uRFk>3)
			{
				obj.sq_IntVectClear()
				obj.sq_IntVectPush(3)
				obj.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true)
			}
			break
		case 3:
			if(sq_GetSkillLevel(obj, 148) > 0 && CQBfeKzgQya8pV6uRFk>2)
			{
				obj.sq_IntVectClear()
				obj.sq_IntVectPush(4)
				obj.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true)
			}
			break
		}
	}
	ForcePush_ATSwordman(obj,169,[1,1,200],6)
}

function onAttack_AtSwordman_Attack(obj, CQiKaYpiccBJEf5pcDWs, CQ1I5ubbsOWIyI4Au, CQUWaHdN2X6twh3sEuM)
{
	if(!obj) return false
	local CQHvk4XStzEUuA3F = obj.getSkillSubState()
	MagicSword_BasiconAttack(obj, CQiKaYpiccBJEf5pcDWs, CQ1I5ubbsOWIyI4Au, CQUWaHdN2X6twh3sEuM)
	Calldaimus_onAttack(obj,CQiKaYpiccBJEf5pcDWs, CQ1I5ubbsOWIyI4Au, CQUWaHdN2X6twh3sEuM)
}

function onEndCurrentAni_AtSwordman_Attack(obj)
{
	if(!obj) return
	obj.sq_IntVectClear()
	obj.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
}