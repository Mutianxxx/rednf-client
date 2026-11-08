
function checkExecutableSkill_womandance(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_WOMANDANCE);
	if (isUse) {
		local job = getNyarly(obj);
		if (job) {
			obj.sq_PlaySound("HARLEQUIN_AKASHIC");
			
			job.getVar("state").clear_vector();
			job.getVar("state").push_vector(5);
			
			job.getVar("subState").clear_vector();
			job.getVar("subState").push_vector(0);
			
			job.getVar("dance").clear_vector();
			if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL)) 
			{
				job.getVar("dance").push_vector(job.getXPos());
				job.getVar("dance").push_vector(job.getYPos());
			}else
			{
				job.getVar("dance").push_vector(obj.getXPos());
				job.getVar("dance").push_vector(obj.getYPos());
			}
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
			job.addSetStatePacket(15, pIntVec, STATE_PRIORITY_AUTO, false, "");
		}
	}
	return false;
}


function checkCommandEnable_womandance(obj) {
	if (!obj) return false;
	return getNyarly(obj);
}