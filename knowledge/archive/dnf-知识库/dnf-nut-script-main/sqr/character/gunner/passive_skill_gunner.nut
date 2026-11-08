

function ProcPassiveSkill_Gunner(obj, skill_index, skill_level)
{
	if (skill_index == 126)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/gunner/zuolunaoyi/ap_zuolunaoyi.nut", true);
		}
	}
	else if (skill_index == 11)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/gunner/fastshoot/ap_fastshoot.nut", true);
		}
		else
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/gunner/fastshoot/ap_fastshoot.nut")) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/gunner/fastshoot/ap_fastshoot.nut");
			}
		}
	}
	else if (skill_index == 129)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/gunner/heavyweaponalteration/ap_heavyweaponalteration.nut", true);
		}
		else
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/gunner/heavyweaponalteration/ap_heavyweaponalteration.nut")) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/gunner/heavyweaponalteration/ap_heavyweaponalteration.nut");
			}
		}
	}
	else if (skill_index == 171)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/gunner/appendage/ap_gunner_comminterrupt.nut", true);
		}
	}
	else if (skill_index == 254)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/gunner/latentability/ap_latentability.nut", true);
		}
	}
	else if (skill_index == 248)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/gunner/appendage/ap_stylish_buff.nut", true);
 			local subCount = obj.sq_GetLevelData(skill_index, 2, skill_level); 
			local recoverTime = obj.sq_GetLevelData(skill_index, 3, skill_level); 
			appendage.getVar().clear_vector(); 
			appendage.getVar().push_vector(subCount); 
			appendage.getVar().push_vector(subCount); 
			 
			appendage.getVar().clear_timer_vector();
			appendage.getVar().push_timer_vector();
			local t = appendage.getVar().get_timer_vector(0);
			t.setParameter(recoverTime, -1); 
			t.resetInstant(0); 
		}
	}
	else if (skill_index == 119)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/gunner/hs_1/ap_hs1.nut", true);
		}
		else
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/gunner/hs_1/ap_hs1.nut")) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/gunner/hs_1/ap_hs1.nut");
			}
		}
	}
	else if (skill_index == SKILL_ALTERATION)
	{
		local append = "character/gunner/assault/assaultattack/ap_alteration.nut";
		if (skill_level > 0) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, append, true);
			procpassive_alteration(obj, appendage);
		}
		else
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, append)) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, append);
			}
		}
	}
	else if (skill_index == SKILL_SENSIBILITY)
	{
		local append = "character/gunner/assault/sensibility/ap_sensibility.nut";
		if (skill_level > 0) {
			CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, append, true);
		}
		else
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, append)) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, append);
			}
		}
	}
	else if (skill_index == SKILL_RETROFIT)
	{
		local append = "character/gunner/assault/retrofit/ap_retrofit.nut";
		if (skill_level > 0) {
			CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, append, true);
		}
		else
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, append)) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, append);
			}
		}
	}
	else if (skill_index == SKILL_RECONSTRUCTIONBODY)
	{
		local append = "character/gunner/assault/reconstructionbody/ap_reconstructionbody.nut";
		if (skill_level > 0) {
			CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, append, true);
		}
		else
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, append)) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, append);
			}
		}
	}
	else if (skill_index == SKILL_AUTOMATICPISTOLMASTERY_ASSAULT)
	{
		local append = "character/gunner/assault/automaticpistolmastery/ap_automaticpistolmastery.nut";
		if (skill_level > 0) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, append, true);
			procpassive_automaticpistolmastery(obj, appendage);
		}
		else
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, append)) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, append);
			}
		}
	}
	
	return true;
}


function procpassive_alteration(obj, appendage) {
	if (!appendage) {
		return;
	}

	local skill_level = obj.sq_GetSkillLevel(SKILL_ALTERATION);
	local chrLevel = obj.sq_GetSkillLevel(174);

	local equipmentPhysicalAttack = obj.sq_GetLevelData(SKILL_ALTERATION, 1, skill_level).tofloat();
	equipmentPhysicalAttack = equipmentPhysicalAttack / 100;
	local phyBonus = sq_GetIntData(obj, SKILL_ALTERATION, 4);
	local physicalAttack = sq_GetIntData(obj, SKILL_ALTERATION, 2) + chrLevel * phyBonus;
	local attackSpeed = obj.sq_GetLevelData(SKILL_ALTERATION, 2, skill_level);
	local moveSpeed = obj.sq_GetLevelData(SKILL_ALTERATION, 3, skill_level);

	local change_appendage = appendage.sq_getChangeStatus("alteration"); 
	if (!change_appendage) {
		change_appendage = appendage.sq_AddChangeStatus("alteration", obj, obj, 0, 0, false, 0); 
	}
	if (change_appendage) {
		change_appendage.clearParameter();
		change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, false, attackSpeed.tofloat());
		change_appendage.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED, false, moveSpeed.tofloat());
		if (obj.getWeaponSubType() == 1) {
			
			change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK, true, equipmentPhysicalAttack);
			change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, false, physicalAttack.tofloat());
		}
	}
}

function procpassive_automaticpistolmastery(obj, appendage) {
	if (!appendage) {
		return;
	}
	local skill_level = obj.sq_GetSkillLevel(SKILL_AUTOMATICPISTOLMASTERY_ASSAULT);

	local value1 = obj.sq_GetLevelData(SKILL_AUTOMATICPISTOLMASTERY_ASSAULT, 0, skill_level);
	local value2 = obj.sq_GetLevelData(SKILL_AUTOMATICPISTOLMASTERY_ASSAULT, 2, skill_level);
	value2 = -value2.tofloat();
	local change_appendage = appendage.sq_getChangeStatus("automaticpistolmastery");
	if (!change_appendage) {
		change_appendage = appendage.sq_AddChangeStatus("automaticpistolmastery", obj, obj, 0, 0, false, 0);
	}
	if (change_appendage) {
		change_appendage.clearParameter();
		if (obj.getWeaponSubType() == 1) {
			change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK_BONUS, true, value1.tofloat() * 0.1);
			change_appendage.addParameter(CHANGE_STATUS_TYPE_STUCK, false, value2 * 0.1);
		}
	}
}

 
function onStartGhost_My_gunner_stylish(obj)
{
    if(CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/gunner/appendage/ap_stylish.nut"))
        CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/gunner/appendage/ap_stylish.nut");

    
    local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_GUNNER_STYLISH, false, "character/gunner/appendage/ap_stylish.nut", false);
    if(appendage)
    {
        local skill_level = sq_GetSkillLevel(obj, SKILL_GUNNER_STYLISH);
        appendage.sq_SetValidTime(obj.sq_GetLevelData(SKILL_GUNNER_STYLISH, 6, skill_level));
        appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, ENUM_CHARACTERJOB_GUNNER, SKILL_GUNNER_STYLISH, skill_level); 
        CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_GUNNER_STYLISH, true);

        local change_appendage = appendage.sq_getChangeStatus("changeStatus");
        if(!change_appendage)
            change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, CHANGE_STATUS_TYPE_HP_MAX, false, 0, APID_COMMON);
        if(change_appendage)
        {

            local speedRate = obj.sq_GetLevelData(SKILL_GUNNER_STYLISH, 5, skill_level);

            change_appendage.clearParameter();

            change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, false, speedRate.tofloat());
            change_appendage.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED, false, speedRate.tofloat());
        }
    }
}


 
function onProcIsSub_My_gunner_stylish(obj)
{
 local isSetState = onProc_My_gunner_stylish(obj);
 if(isSetState != 0)
 {
 sq_BinaryStartWrite();
 sq_BinaryWriteWord(isSetState); 
 sq_SendChangeSkillEffectPacket(obj, 248); 
 }
} ;

 
 
function onProc_My_gunner_stylish(obj)
{
 local isSetState = CNSquirrelAppendage.sq_GetAppendage(obj, "character/gunner/appendage/ap_stylish_buff.nut");
 if(!isSetState) return 0;
 if(isSetState.getVar().get_vector(0)<=0)return 0;
 
 if(!sq_GetSkill(obj, 9).isInCoolTime()) 
 {
 obj.setSkillCommandEnable(9, true); 
 if(obj.sq_IsEnterSkill(9) != -1) 
 {
 obj.startSkillCoolTime(9, sq_GetSkillLevel(obj, 9), -1); 
 
 obj.sq_IntVectClear();
 obj.sq_IntVectPush(15);
 obj.sq_IntVectPush(1);
 obj.sq_IntVectPush(0);
 obj.sq_IntVectPush(100);
 obj.sq_AddSetStatePacket(24, STATE_PRIORITY_USER, true);
 return 1;
 }
 }
 
 if(!sq_GetSkill(obj, 72).isInCoolTime()) 
 {
 obj.setSkillCommandEnable(72, true); 
 if(obj.sq_IsEnterSkill(72) != -1) 
 {
 obj.startSkillCoolTime(72, sq_GetSkillLevel(obj, 72), -1); 
 
 obj.sq_IntVectClear();
 obj.sq_IntVectPush(37);
 obj.sq_IntVectPush(0);
 obj.sq_IntVectPush(0);
 obj.sq_AddSetStatePacket(37, STATE_PRIORITY_USER, true);
 return 1;
 }
 }
 
 if(!sq_GetSkill(obj, 104).isInCoolTime()) 
 {
 obj.setSkillCommandEnable(104, true); 
 if(obj.sq_IsEnterSkill(104) != -1) 
 {
 obj.startSkillCoolTime(104, sq_GetSkillLevel(obj, 104), -1); 
 
 obj.sq_IntVectClear();
 obj.sq_IntVectPush(1);
 obj.sq_IntVectPush(97);
 obj.sq_AddSetStatePacket(58, STATE_PRIORITY_USER, true);
 return 1;
 }
 }
 
 if(!sq_GetSkill(obj, 51).isInCoolTime()) 
 {
 obj.setSkillCommandEnable(51, true); 
 if(obj.sq_IsEnterSkill(51) != -1) 
 {
 obj.startSkillCoolTime(51, sq_GetSkillLevel(obj, 51), -1); 
 
 obj.sq_IntVectClear();
 obj.sq_IntVectPush(0);
 obj.sq_IntVectPush(obj.getDirection());
 obj.sq_IntVectPush(4);
 obj.sq_AddSetStatePacket(41, STATE_PRIORITY_USER, true);
 return 1;
 }
 }
 
 if(!sq_GetSkill(obj, 64).isInCoolTime()) 
 {
 obj.setSkillCommandEnable(64, true); 
 if(obj.sq_IsEnterSkill(64) != -1) 
 {
 obj.startSkillCoolTime(64, sq_GetSkillLevel(obj, 64), -1); 
 
 obj.sq_IntVectClear();
 obj.sq_IntVectPush(0);
 obj.sq_AddSetStatePacket(33, STATE_PRIORITY_USER, true);
 return 1;
 }
 }
 
 if(!sq_GetSkill(obj, 5).isInCoolTime()) 
 {
 obj.setSkillCommandEnable(5, true); 
 if(obj.sq_IsEnterSkill(5) != -1) 
 {
 obj.startSkillCoolTime(5, sq_GetSkillLevel(obj, 5), -1); 
 
 obj.sq_IntVectClear();
 obj.sq_IntVectPush(1);
 obj.sq_IntVectPush(5);
 obj.sq_IntVectPush(0);
 obj.sq_AddSetStatePacket(8, STATE_PRIORITY_USER, true);
 return 1;
 }
 }
 
    if(!sq_GetSkill(obj, 236).isInCoolTime()) 
    {
        obj.setSkillCommandEnable(236, true);
        if(obj.sq_IsEnterSkill(236) != -1)
        {
            obj.startSkillCoolTime(236, sq_GetSkillLevel(obj, 236), -1);

            
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(0); 
            obj.sq_IntVectPush(236); 
            obj.sq_AddSetStatePacket(236, STATE_PRIORITY_USER, true);
            return 1;
        }
    }
 
    if(!sq_GetSkill(obj, 237).isInCoolTime()) 
    {
        obj.setSkillCommandEnable(237, true); 
        if(obj.sq_IsEnterSkill(237) != -1) 
        {
            obj.startSkillCoolTime(237, sq_GetSkillLevel(obj, 237), -1); 
            obj.sq_AddSetStatePacket(237, STATE_PRIORITY_USER, false); 
            return 1;
        }
    }
 
    if(!sq_GetSkill(obj, 238).isInCoolTime()) 
    {
        obj.setSkillCommandEnable(238, true);
        if(obj.sq_IsEnterSkill(238) != -1)
        {
            obj.startSkillCoolTime(238, sq_GetSkillLevel(obj, 238), -1);

            obj.sq_IntVectClear();
            obj.sq_IntVectPush(0);
            obj.sq_IntVectPush(238);
            obj.sq_AddSetStatePacket(238, STATE_PRIORITY_USER, true);
            return 1;
        }
    }
 
    if(!sq_GetSkill(obj, 239).isInCoolTime()) 
    {
        obj.setSkillCommandEnable(239, true);
        if(obj.sq_IsEnterSkill(239) != -1)
        {
            obj.startSkillCoolTime(239, sq_GetSkillLevel(obj, 239), -1);

            obj.getVar("direction").clear_vector();
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(0);
            obj.sq_IntVectPush(239);
            obj.sq_AddSetStatePacket(239, STATE_PRIORITY_USER, true);
            return 1;
        }
    }
 
    if(!sq_GetSkill(obj, 240).isInCoolTime()) 
    {
        obj.setSkillCommandEnable(240, true);
        if(obj.sq_IsEnterSkill(240) != -1)
        {
            obj.startSkillCoolTime(240, sq_GetSkillLevel(obj, 240), -1);

            obj.sq_IntVectClear();
            obj.sq_IntVectPush(0); 
            obj.sq_IntVectPush(240); 
            obj.sq_AddSetStatePacket(240, STATE_PRIORITY_USER, true);
            return 1;
        }
    }
 return 0;
} ;


function procSkill_Gunner(obj)
{
	if(!obj) return;
	Gunner_2nd_Gunner_HS1(obj);
	procSkill_ChangQing751675335_AlphaSupporta(obj);
	procSkillBreachingDown(obj);
	return;
}

function procSkillBreachingDown(obj) {
	if (!obj) return;
	local growType = sq_getGrowType(obj);
	local skillLevel = sq_GetSkillLevel(obj, 99);
	if (growType == 0 && skillLevel > 0) {
		if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/gunner/assault/breachingdown/ap_attack.nut")) {
			CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BREACHINGDOWN, false, "character/gunner/assault/breachingdown/ap_attack.nut", true);
		}
	}
	return;
}

function RemoveAllAniEx( CQ_Value_n6G9FpE, CQ_Value_GCnb )
{
	if (!CQ_Value_GCnb)
	{
		CQ_Value_GCnb = "aniobj";
	}

	if (this.CHANGE_STATUS_TYPE_MAX != 60)
	{
		return;
	}

	local CQ_Value_hSMpx1 = CQ_Value_n6G9FpE.getVar(CQ_Value_GCnb);
	local CQ_Value_poy = CQ_Value_hSMpx1.get_obj_vector_size();

	for( local CQ_Value_3qN7H = 0; CQ_Value_3qN7H < CQ_Value_poy; CQ_Value_3qN7H++ )
	{
		local CQ_Value_qlycufW = CQ_Value_hSMpx1.get_obj_vector(CQ_Value_3qN7H);

		if (CQ_Value_qlycufW)
		{
			CQ_Value_qlycufW.setValid(false);
		}
	}

	CQ_Value_n6G9FpE.getVar(CQ_Value_GCnb).clear_obj_vector();
}

function CreateAni_HS_1( CQ_Value_K8du, CQ_Value_TBAHXy, CQ_Value_sFx, CQ_Value_6GXzU, CQ_Value_eEetfPo, CQ_Value_Xw6D, CQ_Value_xxe2rl, CQ_Value_Pd5, CQ_Value_9Mae2 )
{
	local CQ_Value_tHkADqs = this.sq_CreateAnimation("", CQ_Value_TBAHXy);

	if (this.CHANGE_STATUS_TYPE_MAX != 60)
	{
		return;
	}

	if (CQ_Value_xxe2rl != false)
	{
		CQ_Value_tHkADqs.setImageRateFromOriginal(CQ_Value_xxe2rl, CQ_Value_xxe2rl);
		CQ_Value_tHkADqs.setAutoLayerWorkAnimationAddSizeRate(CQ_Value_xxe2rl);
	}

	if (CQ_Value_Pd5 != false)
	{
		CQ_Value_tHkADqs.setSpeedRate(CQ_Value_Pd5);
	}

	local CQ_Value_BaJN = this.sq_CreatePooledObject(CQ_Value_tHkADqs, true);
	CQ_Value_BaJN = this.sq_SetEnumDrawLayer(CQ_Value_BaJN, CQ_Value_sFx);
	this.sq_SetCurrentDirection(CQ_Value_BaJN, CQ_Value_K8du.getDirection());
	CQ_Value_BaJN.setCurrentPos(CQ_Value_6GXzU, CQ_Value_eEetfPo, CQ_Value_Xw6D);

	if (CQ_Value_9Mae2)
	{
		this.sq_moveWithParent(CQ_Value_K8du, CQ_Value_BaJN);
	}

	this.sq_AddObject(CQ_Value_K8du, CQ_Value_BaJN, this.OBJECTTYPE_DRAWONLY, false);
	return CQ_Value_BaJN;
}

function Gunner_2nd_Gunner_HS1( CQ_Value_veUhlH )
{
	if (this.CHANGE_STATUS_TYPE_MAX != 60)
	{
		return;
	}

	if (this.sq_GetSkillLevel(CQ_Value_veUhlH, 119) > 0)
	{
		local CQ_Value_DY1 = CQ_Value_veUhlH.getMyPassiveObjectCount(24238);

		if (CQ_Value_DY1 < 1)
		{
			CQ_Value_veUhlH.sq_StartWrite();
			CQ_Value_veUhlH.sq_WriteDword(0);
			CQ_Value_veUhlH.sq_WriteDword(70);
			CQ_Value_veUhlH.sq_WriteDword(120);
			CQ_Value_veUhlH.sq_SendCreatePassiveObjectPacket(24238, 0, 70, 0, 120);
			CQ_Value_veUhlH.sq_StartWrite();
			CQ_Value_veUhlH.sq_WriteDword(0);
			CQ_Value_veUhlH.sq_WriteDword(-70);
			CQ_Value_veUhlH.sq_WriteDword(120);
			CQ_Value_veUhlH.sq_SendCreatePassiveObjectPacket(24238, 0, -70, 0, 120);
		}
	}
}

function SetOldSkill_HS_1( CQ_Value_MRiI, CQ_Value_n21, CQ_Value_GKiR9, CQ_Value_hIfUZbp, CQ_Value_pWSa, CQ_Value_3vYZhS, CQ_Value_qgV )
{
	if (this.CHANGE_STATUS_TYPE_MAX != 60)
	{
		return;
	}

	local CQ_Value_KhWbP = CQ_Value_MRiI.getMyPassiveObjectCount(24238);

	for( local CQ_Value_T47owCr = 0; CQ_Value_T47owCr < CQ_Value_KhWbP; ++CQ_Value_T47owCr )
	{
		local CQ_Value_sZrK = CQ_Value_MRiI.getMyPassiveObject(24238, CQ_Value_T47owCr);

		if (CQ_Value_sZrK)
		{
			if (CQ_Value_sZrK.getState() == 0)
			{
				local CQ_Value_6P77Me = this.sq_GetGlobalIntVector();
				this.sq_IntVectorClear(CQ_Value_6P77Me);

				if (CQ_Value_n21 == 260105)
				{
					this.sq_IntVectorPush(CQ_Value_6P77Me, 150);
				}
				else
				{
					this.sq_IntVectorPush(CQ_Value_6P77Me, 0);
				}

				CQ_Value_sZrK.addSetStatePacket(10, CQ_Value_6P77Me, this.STATE_PRIORITY_AUTO, false, "");
				local CQ_Value_eyI = CQ_Value_MRiI.getState();
				CQ_Value_MRiI.sq_SendCreatePassiveObjectPacket(CQ_Value_n21, 0, CQ_Value_pWSa, CQ_Value_3vYZhS, CQ_Value_qgV);
				//CQ_Value_MRiI.sq_SendCreatePassiveObjectPacket(CQ_Value_n21, 0, CQ_Value_pWSa, CQ_Value_3vYZhS, CQ_Value_qgV);
				if (CQ_Value_eyI == 14)
				{
					CQ_Value_MRiI.sq_IntVectClear();
					CQ_Value_MRiI.sq_AddSetStatePacket(14, this.STATE_PRIORITY_IGNORE_FORCE, true);
				}
				else
				{
					CQ_Value_MRiI.sq_IntVectClear();
					CQ_Value_MRiI.sq_AddSetStatePacket(0, this.STATE_PRIORITY_IGNORE_FORCE, true);
				}

				local CQ_Value_Xnluc = {
					[260108] = [
						"passiveobject/chang_qing_skill/gunner/animation/hs1/rx78_02.ani",
						0,
						false,
						0
					],
					[260109] = [
						"passiveobject/chang_qing_skill/gunner/animation/hs1/ez8ex_01.ani",
						0,
						0.51999998,
						10
					],
					[260110] = [
						"passiveobject/chang_qing_skill/gunner/animation/hs1/ez8ex_01.ani",
						0,
						false,
						0
					],
					[260107] = [
						"passiveobject/chang_qing_skill/gunner/animation/hs1/exs_05.ani",
						0,
						false,
						0
					],
					[260106] = [
						"passiveobject/chang_qing_skill/gunner/animation/hs1/exs_05.ani",
						0,
						false,
						0
					],
					[260105] = [
						"passiveobject/chang_qing_skill/gunner/animation/hs1/tempester_02.ani",
						150,
						false,
						0
					]
				};

				if (CQ_Value_Xnluc.rawin(CQ_Value_n21))
				{
					local CQ_Value_xkKG6ai = CQ_Value_Xnluc[CQ_Value_n21][0];
					local CQ_Value_P6q4 = CQ_Value_Xnluc[CQ_Value_n21][1];
					local CQ_Value_9C3zi3 = CQ_Value_Xnluc[CQ_Value_n21][2];
					local CQ_Value_tSq = CQ_Value_Xnluc[CQ_Value_n21][3];
					this.CreateAni_HS_1(CQ_Value_MRiI, CQ_Value_xkKG6ai, this.ENUM_DRAWLAYER_NORMAL, CQ_Value_MRiI.getXPos() + (CQ_Value_MRiI.getDirection() == 0 ? -(CQ_Value_pWSa + CQ_Value_tSq) : CQ_Value_pWSa + CQ_Value_tSq), CQ_Value_MRiI.getYPos(), CQ_Value_MRiI.getZPos() + CQ_Value_P6q4, CQ_Value_9C3zi3, 65.0, false);
				}

				return;
			}
		}
	}
}

function procAppend_po_Gunner_HS1( CQ_Value_ka4sAK )
{
	if (!CQ_Value_ka4sAK)
	{
		return;
	}

	local CQ_Value_aep = CQ_Value_ka4sAK.getVar("state").get_vector(0);
	local CQ_Value_5c3dk = this.sq_ObjectToSQRCharacter(CQ_Value_ka4sAK.getTopCharacter());

	if (this.CHANGE_STATUS_TYPE_MAX != 60)
	{
		return;
	}

	if (!CQ_Value_5c3dk)
	{
		this.sq_SendDestroyPacketPassiveObject(CQ_Value_ka4sAK);
	}

	local CQ_Value_wfpn132 = CQ_Value_ka4sAK.getVar().get_vector(0);
	local CQ_Value_Z1hp = CQ_Value_ka4sAK.getVar().get_vector(1);
	local CQ_Value_zJFLcU = CQ_Value_ka4sAK.getDirection();
	local CQ_Value_Osb = CQ_Value_5c3dk.getDirection();

	if (CQ_Value_Osb != CQ_Value_zJFLcU)
	{
		CQ_Value_ka4sAK.setDirection(CQ_Value_Osb);
		local CQ_Value_8rNYK = CQ_Value_ka4sAK.getVar("Face").get_obj_vector(0);

		if (CQ_Value_8rNYK)
		{
			this.sq_SetCurrentDirection(CQ_Value_8rNYK, CQ_Value_Osb);
		}
	}

	this.sq_setCurrentAxisPos(CQ_Value_ka4sAK, 0, CQ_Value_5c3dk.getXPos() + (CQ_Value_5c3dk.getDirection() == 0 ? -CQ_Value_wfpn132 : CQ_Value_wfpn132));
	this.sq_setCurrentAxisPos(CQ_Value_ka4sAK, 1, CQ_Value_5c3dk.getYPos());
	this.sq_setCurrentAxisPos(CQ_Value_ka4sAK, 2, CQ_Value_5c3dk.getZPos() + CQ_Value_Z1hp);
	local CQ_Value_WYyiou6 = CQ_Value_ka4sAK.getVar("ObjTime").get_vector(0);

	switch(CQ_Value_aep)
	{
	case 10:
		local CQ_Value_VRdH = this.sq_GetObjectTime(CQ_Value_ka4sAK);
		local CQ_Value_Y3t5VB = CQ_Value_VRdH - CQ_Value_WYyiou6;
		local CQ_Value_SL9 = CQ_Value_ka4sAK.getVar("tarPos").get_vector(0);
		local CQ_Value_dOPt = CQ_Value_ka4sAK.getVar("tarPos").get_vector(1);

		if (CQ_Value_Y3t5VB <= 155)
		{
			local CQ_Value_ytxFg9 = this.sq_GetUniformVelocity(CQ_Value_ka4sAK.getXPos(), CQ_Value_SL9, CQ_Value_Y3t5VB, 150);
			local CQ_Value_NbX = this.sq_GetUniformVelocity(CQ_Value_ka4sAK.getZPos(), CQ_Value_dOPt, CQ_Value_Y3t5VB, 150);
			this.sq_setCurrentAxisPos(CQ_Value_ka4sAK, 0, CQ_Value_ytxFg9);
			this.sq_setCurrentAxisPos(CQ_Value_ka4sAK, 2, CQ_Value_NbX);

			if (CQ_Value_ka4sAK.getVar().getBool(0) && CQ_Value_Y3t5VB > 50)
			{
				local CQ_Value_bnwTO = "passiveobject/chang_qing_skill/gunner/animation/hs1/callrobot_01.ani";

				this.CreateAni_HS_1(CQ_Value_ka4sAK, CQ_Value_bnwTO, this.ENUM_DRAWLAYER_NORMAL, CQ_Value_SL9, CQ_Value_ka4sAK.getYPos() - 1, CQ_Value_dOPt - 220, false, false, false);
				CQ_Value_ka4sAK.getVar().setBool(0, false);
			}
		}
		else if (CQ_Value_Y3t5VB > 155 && CQ_Value_Y3t5VB <= 255)
		{
			this.sq_setCurrentAxisPos(CQ_Value_ka4sAK, 0, CQ_Value_SL9);
			this.sq_setCurrentAxisPos(CQ_Value_ka4sAK, 2, CQ_Value_dOPt);
		}
		else if (CQ_Value_Y3t5VB > 255 && CQ_Value_Y3t5VB <= 455)
		{
			local CQ_Value_ytxFg9 = this.sq_GetUniformVelocity(CQ_Value_ka4sAK.getXPos(), CQ_Value_5c3dk.getXPos() + (CQ_Value_5c3dk.getDirection() == 0 ? -CQ_Value_wfpn132 : CQ_Value_wfpn132), CQ_Value_Y3t5VB - 255, 200);
			local CQ_Value_NbX = this.sq_GetUniformVelocity(CQ_Value_ka4sAK.getZPos(), CQ_Value_5c3dk.getZPos() + CQ_Value_Z1hp, CQ_Value_Y3t5VB - 255, 200);
			this.sq_setCurrentAxisPos(CQ_Value_ka4sAK, 0, CQ_Value_ytxFg9);
			this.sq_setCurrentAxisPos(CQ_Value_ka4sAK, 2, CQ_Value_NbX);
		}
		else if (CQ_Value_Y3t5VB > 455)
		{
			local CQ_Value_mX5 = this.sq_GetGlobalIntVector();
			this.sq_IntVectorClear(CQ_Value_mX5);
			this.sq_IntVectorPush(CQ_Value_mX5, 0);
			CQ_Value_ka4sAK.addSetStatePacket(0, CQ_Value_mX5, this.STATE_PRIORITY_AUTO, false, "");
		}

		break;

	case 11:
		break;
	}
}

function setHeadShotMasteryState_Gunner(obj, state, datas)
{
	if(obj.getCurrentSkillIndex()>0)
		return;
	local level = sq_GetSkillLevel(obj, SKILL_HEADSHOTMASTERY);
	local skill_level = sq_GetSkillLevel(obj, 5);
	if(level > 0 && skill_level > 0 && sq_getGrowType(obj) == 1 && isHeadShotMastery(obj)){
	
		local substate0 = obj.sq_GetVectorData(datas, 0);
		local substate1 = obj.sq_GetVectorData(datas, 1);
		local substate2 = obj.sq_GetVectorData(datas, 3);
		//if( (substate1==1 || substate1==0) && state==8 )
		if(substate0 ==0 && (substate1<0 || substate1 ==11) &&  state==8 && CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/gunner/headshotmastery/ap_headshotmastery.nut") )
		{
			sq_IntVectorClear(datas);
			sq_IntVectorPush(datas, 1);
			sq_IntVectorPush(datas, 5);
			sq_IntVectorPush(datas, 0);
			obj.getVar("inShot").clear_vector();
			obj.getVar("inShot").push_vector(1);
		}
		else if(substate0 ==1 && (substate1==0 || substate1==1) && substate2<0 &&  state==8  && !CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/gunner/headshotmastery/ap_headshotmastery.nut"))
		{
			obj.getVar("atkpup").clear_vector();
			obj.getVar("atkpup").push_vector(1);
		}
	}
}

function setFastShootState_Gunner(obj, state, datas)
{
	if(obj.getCurrentSkillIndex()>0)
		return;
	local level = sq_GetSkillLevel(obj, 11);
	if(level > 0){
		local substate0 = obj.sq_GetVectorData(datas, 0);
		local substate1 = obj.sq_GetVectorData(datas, 1);
		if(substate0 ==0 && substate1<0 &&  state==8)
		{
			sq_IntVectorClear(datas);
			sq_IntVectorPush(datas, 0);
			sq_IntVectorPush(datas, 11);
		}
	}
}

function setState_Gunner(obj, state, datas, isResetTimer)
{
	setState_AllGrowJob(obj, state, datas, isResetTimer);
	setFastShootState_Gunner(obj, state, datas);
	setHeadShotMasteryState_Gunner(obj, state, datas);
	ChangQing751675335_AlphaSupporta(obj, state, datas, isResetTimer);
}

