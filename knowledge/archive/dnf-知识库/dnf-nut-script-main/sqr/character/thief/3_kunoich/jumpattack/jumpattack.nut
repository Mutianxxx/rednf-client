//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function onAfterSetState_jumpattack_thief(obj, state, datas, isResetTimer)
{
	if(!obj) return;

	local equipchakraweapon = obj.sq_GetSkillLevel(SKILL_EQUIPCHAKRAWEAPON);
	local kusanagi = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut");
	if(equipchakraweapon > 0  && (obj.getWeaponSubType()==5 || kusanagi == true))
	{
		if(kusanagi == true)
		{
			if(obj.isMyControlObject())
			{
				obj.sq_StartWrite();
				obj.sq_WriteDword(62);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 60, 0, 60);
				obj.sq_StartWrite();
				obj.sq_WriteDword(62);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 60, 20, 60);
				obj.sq_StartWrite();
				obj.sq_WriteDword(62);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 60, -20, 60);
			}
		}
		else
		{
			als_ani(obj, "character/thief/effect/animation/chakraweapon/chakraweaponjumpatk_eff_a.ani", 40, 0, -20, 0, 100, 1, 1, 1.0);
			if(obj.isMyControlObject())
			{
				obj.sq_StartWrite();
				obj.sq_WriteDword(1);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 90, 0, 0);
			}
		}
	}
}

