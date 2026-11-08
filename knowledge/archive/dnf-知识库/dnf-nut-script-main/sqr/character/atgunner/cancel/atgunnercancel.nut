function onProc_atgunnercancel(obj)
{
	if (!obj) return false;
	obj.setSkillCommandEnable(40, true);
	obj.setSkillCommandEnable(53, true);
	obj.setSkillCommandEnable(76, true);
	obj.setSkillCommandEnable(77, true);
	obj.setSkillCommandEnable(51, true);

}

//CUSTOM_ANI_NITROMOTOR_SKY_SHOOT

function onAfterSetState_atgunnercancel(obj, state, datas, isResetTimer)
{
	if (!obj) return false;
	local skillIndex = obj.getCurrentSkillIndex();
	if(skillIndex == 47)
	{
		local zPos = obj.getZPos(); 
		if(zPos > 50) 
		{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_NITROMOTOR_SKY_THROW);
			obj.sq_ZStop();
		}
	}

}