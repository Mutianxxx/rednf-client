//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function onAfterSetState_dashattack_thief(obj, state, datas, isResetTimer)
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
				obj.sq_WriteDword(61);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 100, 0, 60);
				obj.sq_StartWrite();
				obj.sq_WriteDword(61);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 100, 20, 60);
				obj.sq_StartWrite();
				obj.sq_WriteDword(61);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 100, -20, 60);
			}
		}
		else
		{
			als_ani(obj, "character/thief/effect/animation/chakraweapon/chakraweapondashatk_eff_a.ani", 20, 0, 0, 0, 100, 1, 1, 1.0);
			if(obj.isMyControlObject())
			{
				obj.sq_StartWrite();
				obj.sq_WriteDword(0);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 110, 0, 50);
			}
		}
	}
}

