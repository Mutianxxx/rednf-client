function onProcCon_gunner_jump(obj)
{
	if (!obj) return;
	if(sq_GetSkillLevel(obj,248)>0)
	{
		EnableSoften(obj,5,8);
		SetSkillState(obj,5,169,[1,5,0]);
	}
	
	if(sq_GetSkillLevel(obj,SKILL_SCORCHTACTICS) > 0)
	{
		local jumpScorchtactics = obj.sq_GetIntData(SKILL_SCORCHTACTICS, 7);
		if(jumpScorchtactics > 0)
		{
			EnableSoften(obj,SKILL_SCORCHTACTICS,STATE_SCORCHTACTICS);
			SetSkillState(obj,SKILL_SCORCHTACTICS,STATE_SCORCHTACTICS,[1]);
		}
	}
}