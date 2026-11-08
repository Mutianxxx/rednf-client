function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_latentability")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_latentability")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_latentability")
}

function sq_AddEffect(appendage)
{
}

function proc_appendage_latentability(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	{
		local skillLevel = sqrChr.sq_GetSkillLevel(SKILL_LATENTABILITY);
		local value0 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 0, skillLevel); //ÕôÕá%
		local value1 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 1, skillLevel); //òªÕô%
		local value2 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 2, skillLevel); //ô÷Õô%
		local value3 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 3, skillLevel); //ïñãê%

		local value4 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 4, skillLevel); //ÕôÕá
		local value5 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 5, skillLevel); //òªÕô
		local value6 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 6, skillLevel); //ô÷Õô
		local value7 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 7, skillLevel); //ïñãê

		local value8 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 8, skillLevel); //Úª×âÍôÌªÕô%
		local value9 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 9, skillLevel); //ØªÛöÍôÌªÕô%
		local value10 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 10, skillLevel); //Ô¼Ø¡ÍôÌªÕô%
		local value11 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 11, skillLevel); //Ô¼Ø¡ÍôÌªÕô%

		local value12 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 12, skillLevel); //Úª×âÍôÌªÕô
		local value13 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 13, skillLevel); //ØªÛöÍôÌªÕô
		local value14 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 14, skillLevel); //Ô¼Ø¡ÍôÌªÕô
		local value15 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 15, skillLevel); //Ô¼Ø¡ÍôÌªÕô

		local value16 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 16, skillLevel); //ÍôÌªáÜÓø
		local value17 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 17, skillLevel); //ì¹ÔÑáÜÓø
		local value18 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 18, skillLevel); //à·Û¯áÜÓø

		local value19 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 19, skillLevel); //Úª×âøìÌªáã
		local value20 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 20, skillLevel); //ØªÛöøìÌªáã

		local value21 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 21, skillLevel); //ûýq
		local value22 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 22, skillLevel); //äÞq
		local value23 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 23, skillLevel); //â©q
		local value24 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 24, skillLevel); //ÎÃq
		local value25 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 25, skillLevel); //á¶êóáÕq

		local value26 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 26, skillLevel); //CD

		local value27 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 27, skillLevel); //Úª×âøìÌªß¿úª
		local value28 = sq_GetLevelData(sqrChr, SKILL_LATENTABILITY, 28, skillLevel); //ØªÛöøìÌªß¿úª
		local change_appendage = appendage.sq_getChangeStatus("latentability");
		if(!change_appendage)
		{
			change_appendage = appendage.sq_AddChangeStatus("latentability",obj, obj, 0, 37, true, 0);
		}
		if(change_appendage)
		{
			change_appendage.clearParameter();
			change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, true, value0.tofloat()); //ÕôÕá%
			change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK, true, value1.tofloat()); //òªÕô%
			change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_DEFENSE, true, value2.tofloat()); //ô÷Õô%
			change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_DEFENSE, true, value3.tofloat()); //ïñãê%

			change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, false, value4.tofloat()); //ÕôÕá
			change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, value5.tofloat()); //òªÕô
			change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_DEFENSE, false, value6.tofloat()); //ô÷Õô
			change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_DEFENSE, false, value7.tofloat()); //ïñãê

			change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK_BONUS, true, value8.tofloat()); //Úª×âÍôÌªÕô%
			change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK_BONUS, true, value9.tofloat()); //ØªÛöÍôÌªÕô%
			change_appendage.addParameter(CHANGE_STATUS_TYPE_ADDITIONAL_PHYSICAL_GENUINE_ATTACK, true, value10.tofloat()); //Ô¼Ø¡ÍôÌªÕô%
			change_appendage.addParameter(CHANGE_STATUS_TYPE_ADDITIONAL_MAGICAL_GENUINE_ATTACK, true, value11.tofloat()); //Ô¼Ø¡ÍôÌªÕô%

			change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK, false, value12.tofloat()); //Úª×âÍôÌªÕô
			change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_ATTACK, false, value13.tofloat()); //ØªÛöÍôÌªÕô
			change_appendage.addParameter(CHANGE_STATUS_TYPE_ADDITIONAL_PHYSICAL_GENUINE_ATTACK, false, value14.tofloat()); //Ô¼Ø¡ÍôÌªÕô
			change_appendage.addParameter(CHANGE_STATUS_TYPE_ADDITIONAL_MAGICAL_GENUINE_ATTACK, false, value15.tofloat()); //Ô¼Ø¡ÍôÌªÕô

			change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, true, value16.tofloat()); //ÍôÌªáÜÓø
			change_appendage.addParameter(CHANGE_STATUS_TYPE_CAST_SPEED, true, value17.tofloat()); //ì¹ÔÑáÜÓø
			change_appendage.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED, true, value18.tofloat()); //à·Û¯áÜÓø

			change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, false, value19.tofloat()); //Úª×âøìÌªáã
			change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_HIT_RATE, false, value20.tofloat()); //ØªÛöøìÌªáã

			change_appendage.addParameter(CHANGE_STATUS_TYPE_ELEMENT_ATTACK_FIRE, false, value21.tofloat()); //ûýq
			change_appendage.addParameter(CHANGE_STATUS_TYPE_ELEMENT_ATTACK_WATER, false, value22.tofloat()); //â©q
			change_appendage.addParameter(CHANGE_STATUS_TYPE_ELEMENT_ATTACK_DARK, false, value23.tofloat()); //äÞq
			change_appendage.addParameter(CHANGE_STATUS_TYPE_ELEMENT_ATTACK_LIGHT, false, value24.tofloat()); //ÎÃq
			change_appendage.addParameter(CHANGE_STATUS_TYPE_ELEMENT_ATTACK_ALL, false, value25.tofloat()); //á¶êóáÕq

			change_appendage.addParameter(CHANGE_STATUS_TYPE_COOLTIME_DECLINE, true, value26.tofloat()); //CD

			change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_DAMAGE_RATE, false, value27.tofloat()); //Úª×âøìÌªß¿úª
			change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_DAMAGE_RATE, false, value28.tofloat()); //ØªÛöøìÌªß¿úª
		}
	}
}

function onStart_appendage_latentability(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();

}

function onEnd_appendage_latentability(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
}
