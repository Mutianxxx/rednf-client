function onProc_priestcancel(obj)
{
	if (!obj) return false;

		if (sq_getJob(obj) == ENUM_CHARACTERJOB_PRIEST)
		{

			obj.setSkillCommandEnable(77, true);
		}
}