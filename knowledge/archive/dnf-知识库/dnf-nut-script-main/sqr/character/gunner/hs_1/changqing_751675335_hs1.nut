


function checkExecutableSkill_RobotTempester( CQ_Value_zf5xwHU )
{
	if (!CQ_Value_zf5xwHU)
	{
		return false;
	}

	local CQ_Value_Kai2s1 = CQ_Value_zf5xwHU.sq_IsUseSkill(63);

	if (CQ_Value_Kai2s1)
	{
		if (this.CHANGE_STATUS_TYPE_MAX != 60)
		{
			return true;
		}

		local CQ_Value_JTuM = this.sq_GetSkillLevel(CQ_Value_zf5xwHU, 119);
		local CQ_Value_k7f = this.sq_GetLevelData(CQ_Value_zf5xwHU, 63, 0, this.sq_GetSkillLevel(CQ_Value_zf5xwHU, 63));

		if (CQ_Value_JTuM > 0)
		{
			this.SetOldSkill_HS_1(CQ_Value_zf5xwHU, 260105, CQ_Value_k7f, 0, 130, -1, 0);
		}

		return true;
	}

	return false;
}

function checkCommandEnable_RobotTempester( CQ_Value_aVSQI )
{
	if (!CQ_Value_aVSQI)
	{
		return false;
	}

	return true;

}

function checkExecutableSkill_RobotExsEx( CQ_Value_woCV )
{
	if (!CQ_Value_woCV)
	{
		return false;
	}

	local CQ_Value_ZqrRDS = CQ_Value_woCV.sq_IsUseSkill(106);

	if (CQ_Value_ZqrRDS)
	{
		if (this.CHANGE_STATUS_TYPE_MAX != 60)
		{
			return true;
		}

		local CQ_Value_zl7 = this.sq_GetSkillLevel(CQ_Value_woCV, 119);
		local CQ_Value_Ozraz = this.sq_GetLevelData(CQ_Value_woCV, 106, 0, this.sq_GetSkillLevel(CQ_Value_woCV, 106));

		if (CQ_Value_zl7 > 0)
		{
			this.SetOldSkill_HS_1(CQ_Value_woCV, 260106, CQ_Value_Ozraz, 0, 130, -1, 0);
		}

		return true;
	}

	return false;
}

function checkCommandEnable_RobotExsEx( CQ_Value_HanB )
{
	if (!CQ_Value_HanB)
	{
		return false;
	}


	return true;

}

function checkExecutableSkill_RobotExs( CQ_Value_CHTbbz )
{
	if (!CQ_Value_CHTbbz)
	{
		return false;
	}

	local CQ_Value_caKp968 = CQ_Value_CHTbbz.sq_IsUseSkill(29);

	if (CQ_Value_caKp968)
	{
		if (this.CHANGE_STATUS_TYPE_MAX != 60)
		{
			return true;
		}

		local CQ_Value_AeqK = this.sq_GetSkillLevel(CQ_Value_CHTbbz, 119);
		local CQ_Value_dc27EQ = this.sq_GetLevelData(CQ_Value_CHTbbz, 29, 0, this.sq_GetSkillLevel(CQ_Value_CHTbbz, 29));

		if (CQ_Value_AeqK > 0)
		{
			this.SetOldSkill_HS_1(CQ_Value_CHTbbz, 260107, CQ_Value_dc27EQ, 0, 130, -1, 0);
		}

		return true;
	}

	return false;
}

function checkCommandEnable_RobotExs( CQ_Value_bfo )
{
	if (!CQ_Value_bfo)
	{
		return false;
	}


	return true;

}

function checkExecutableSkill_RobotRX78( CQ_Value_gJoH )
{
	if (!CQ_Value_gJoH)
	{
		return false;
	}

	local CQ_Value_osg4eU = CQ_Value_gJoH.sq_IsUseSkill(27);

	if (CQ_Value_osg4eU)
	{
		if (this.CHANGE_STATUS_TYPE_MAX != 60)
		{
			return true;
		}

		local CQ_Value_2rD = this.sq_GetSkillLevel(CQ_Value_gJoH, 119);
		local CQ_Value_mYvt1 = this.sq_GetLevelData(CQ_Value_gJoH, 27, 0, this.sq_GetSkillLevel(CQ_Value_gJoH, 27));
		local crisisPer = this.sq_GetLevelData(CQ_Value_gJoH,42,1, this.sq_GetSkillLevel(CQ_Value_gJoH, 42))/50;
		crisisPer = crisisPer.tointeger();
		local random = sq_getRandom(0, 20);

		if (CQ_Value_2rD > 0)
		{
			if(crisisPer>=random){
				this.SetOldSkill_HS_1(CQ_Value_gJoH, 260108, CQ_Value_mYvt1, 0, 130, -20, 0);
				this.SetOldSkill_HS_1(CQ_Value_gJoH, 260108, CQ_Value_mYvt1, 0, 130, 20, 0);
			}else{
				this.SetOldSkill_HS_1(CQ_Value_gJoH, 260108, CQ_Value_mYvt1, 0, 130, -1, 0);
			}
		}

		return true;
	}

	return false;
}

function checkCommandEnable_RobotRX78( CQ_Value_JRBDSuS )
{
	if (!CQ_Value_JRBDSuS)
	{
		return false;
	}
	return true;
}

function checkExecutableSkill_RobotEz8( CQ_Value_aK9T6B )
{
	if (!CQ_Value_aK9T6B)
	{
		return false;
	}

	local CQ_Value_5OW = CQ_Value_aK9T6B.sq_IsUseSkill(28);

	if (CQ_Value_5OW)
	{
		if (this.CHANGE_STATUS_TYPE_MAX != 60)
		{
			return true;
		}

		local CQ_Value_wt8Ai = this.sq_GetSkillLevel(CQ_Value_aK9T6B, 119);
		local CQ_Value_ZyOMv8H = this.sq_GetLevelData(CQ_Value_aK9T6B, 28, 0, this.sq_GetSkillLevel(CQ_Value_aK9T6B, 28));

		if (CQ_Value_wt8Ai > 0)
		{
			this.SetOldSkill_HS_1(CQ_Value_aK9T6B, 260109, CQ_Value_ZyOMv8H, 0, 130, -1, 0);
		}

		return true;
	}

	return false;
}

function checkCommandEnable_RobotEz8( CQ_Value_znzh )
{
	if (!CQ_Value_znzh)
	{
		return false;
	}

	return true;
}

function checkExecutableSkill_RobotEz8Ex( CQ_Value_85Q )
{
	if (!CQ_Value_85Q)
	{
		return false;
	}

	local CQ_Value_WX4Vg = CQ_Value_85Q.sq_IsUseSkill(105);

	if (CQ_Value_WX4Vg)
	{
		if (this.CHANGE_STATUS_TYPE_MAX != 60)
		{
			return true;
		}

		local CQ_Value_VAQRBsX = this.sq_GetSkillLevel(CQ_Value_85Q, 119);
		local CQ_Value_Yu4U = this.sq_GetLevelData(CQ_Value_85Q, 105, 0, this.sq_GetSkillLevel(CQ_Value_85Q, 105));

		if (CQ_Value_VAQRBsX > 0)
		{
			this.SetOldSkill_HS_1(CQ_Value_85Q, 260110, CQ_Value_Yu4U, 0, 130, -1, 0);
		}

		return true;
	}

	return false;
}

function checkCommandEnable_RobotEz8Ex( CQ_Value_SUpaQj )
{
	if (!CQ_Value_SUpaQj)
	{
		return false;
	}

	return true;

}

function RemoveAllAniEx(CQ_Value_n6G9FpE,CQ_Value_GCnb)
{
if(!CQ_Value_GCnb)
CQ_Value_GCnb = "aniobj";

local CQ_Value_hSMpx1 = CQ_Value_n6G9FpE.getVar(CQ_Value_GCnb);
local CQ_Value_poy = CQ_Value_hSMpx1.get_obj_vector_size();
for(local CQ_Value_3qN7H=0; CQ_Value_3qN7H<CQ_Value_poy; CQ_Value_3qN7H++)
{
local CQ_Value_qlycufW = CQ_Value_hSMpx1.get_obj_vector(CQ_Value_3qN7H);
if(CQ_Value_qlycufW)
CQ_Value_qlycufW.setValid(false);
}
CQ_Value_n6G9FpE.getVar(CQ_Value_GCnb).clear_obj_vector();
}


function Gunner_2nd_Gunner_HS1Ex(CQ_Value_veUhlH)
{
}



function SetNewSkill_HS_1(CQ_Value_veUhlH)
{
}

function SetNewSkill_HS_1Ex(CQ_Value_veUhlH)
{
}
