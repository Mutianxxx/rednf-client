//writeclosuretofile("DamageTool.f", main);
//function main()
function NewRankSystem(obj)
{
	if (!obj) return;
	if(CFG_FUNC_NUTNEWSCORE < 1){
		return;
	}
	//Ðñ?êÈöÇ
	local base_x = CFG_UI_NUTNEWSCORE_POS_X;
	local base_y = CFG_UI_NUTNEWSCORE_POS_Y;
	//?ÝÂò¦?
	local Dungeon_num = obj.getVar("Dungeon_num").getInt(0);
	//??ò¦?
	local Combo = obj.getVar("Dungeon_Combo").getInt(0);
	//????
	local t = obj.getVar("Dungeon_Time").get_ct_vector(0);
	if (!t)
	{
		obj.getVar("Dungeon_Time").clear_ct_vector();
		obj.getVar("Dungeon_Time").push_ct_vector();
		t = obj.getVar("Dungeon_Time").get_ct_vector(0);
		t.Reset();
		t.Start(1220, 0);
		//return true;
	}

	local currentT = t.Get();
	//ñìöÇ÷âÙ¥Óø
	local alpha_value = 255;
	if (currentT > 2500)
		alpha_value = 100;
	local alpha = sq_ALPHA(alpha_value);
	//ñìöÇ÷âÙ¥Óø
	if (currentT >= 1200)
		obj.getVar("Dungeon_Combo").setInt(0, 0);
	//í®Ù½?ÝÂÓÞá³
	local AnisizeRate = sq_GetUniformVelocity(110, 100, currentT, 200);
	//local AnisizeRate = currentT;
	local img_size = AnisizeRate.tofloat() / 100.0;
	//?ÝÂí®Ù½
	Dungeon_Rank(obj, base_x + 3, base_y - 35, alpha, Dungeon_num, img_size)

	//?ÝÂ?í®
	Dungeon_Score_num(obj, base_x + 2, base_y + 5, alpha, Dungeon_num, img_size)
	//?ð¤??
	local ComboAnisizeRate = sq_GetUniformVelocity(130, 100, currentT, 100);
	local Combo_img_size = ComboAnisizeRate.tofloat() / 100.0;
	Dungeon_Combo(obj, base_x - 17, base_y + 17, sq_ALPHA(255), 0, Combo_img_size)

	//?ð¤ð«ãÆãáãÓ
	local py_vauel = 0;
	local MonsterKillVauel = obj.getVar("MonsterKillVauel").getInt(0);
	if (MonsterKillVauel > 0)
	{
		py_vauel = 17;
	}
	local Combo = obj.getVar("Dungeon_Combo").getInt(0); //?ÝÂò¦?combo
	if (Combo == 0 && MonsterKillVauel == 0)
	{
		py_vauel = -17;
	}
	Dungeon_Tip(obj, base_x - 17, base_y + 17 + py_vauel, sq_ALPHA(255), 0, 1.0)
	//?ð¤ÎÖÚª??ãáãÓ
	Dungeon_MonsterKillTip(obj, base_x - 85, base_y - 60, sq_ALPHA(255), 0, 1.0)
	//?ð¤??ïÃ
	Dungeon_MonsterKillNum(obj, base_x - 17, base_y + 34, sq_ALPHA(255), 0, 1.0)
	//ôÕÊ¥?ÝÂAPD
	local Appendage = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/job_common/apd/ap_new_rank.nut")
	if (!Appendage)
		local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "character/job_common/apd/ap_new_rank.nut", true);

}

function Dungeon_MonsterKillNum(obj, base_x, base_y, alpha, Dungeon_num, size)
{
	local baseRGB = sq_RGB(255, 255, 255);
	local sq_var = obj.getVar();

	local MonsterKillNum_Tip = sq_var.GetAnimationMap("MonsterKillNumTip",
		"common/commoneffect/animation/newranksystem/combo_bonus.ani");
	local MonsterKillNum_TipEtc = sq_var.GetAnimationMap("MonsterKillNumrff",
		"common/commoneffect/animation/newranksystem/killpoint_num.ani");

	local MonsterKillNum_one = sq_var.GetAnimationMap("MonsterKillNum_one",
		"common/commoneffect/animation/newranksystem/killpoint_num.ani");

	local i = 12;

	local t = obj.getVar("MonsterKillTime").get_ct_vector(0);
	if (!t)
	{
		obj.getVar("MonsterKillTime").clear_ct_vector();
		obj.getVar("MonsterKillTime").push_ct_vector();
		t = obj.getVar("MonsterKillTime").get_ct_vector(0);
		t.Reset();
		t.Start(1227, 0);
	}
	local currentT = t.Get();

	local MonsterKillFlag = obj.getVar("MonsterKillFlag").getInt(0);
	local MonsterKillVauel = obj.getVar("MonsterKillVauel").getInt(0);


	if (currentT >= 1200)
	{
		if (MonsterKillVauel > 5000 && MonsterKillVauel > 1)
		{
			KillTip(obj, 5)
			PlaySound_Rate(obj, 1, 100, 100, "HK3_PERFECT");
		}
		if (MonsterKillVauel > 4000 && MonsterKillVauel > 1)
		{
			KillTip(obj, 4)
			PlaySound_Rate(obj, 1, 100, 100, "HK3_EXCELLENT");
		}
		else if (MonsterKillVauel > 3000 && MonsterKillVauel > 1)
		{
			KillTip(obj, 3)
			PlaySound_Rate(obj, 1, 100, 100, "HK3_GFRAME");
		}
		else if (MonsterKillVauel > 2000 && MonsterKillVauel > 1)
		{
			KillTip(obj, 2)
			PlaySound_Rate(obj, 1, 100, 100, "HK3_NICE");
		}
		else if (MonsterKillVauel > 1000 && MonsterKillVauel > 1)
		{
			KillTip(obj, 1)
			PlaySound_Rate(obj, 1, 100, 100, "HK3_GOOD");
		}
		obj.getVar("MonsterKillFlag").setInt(0, 0);
		obj.getVar("MonsterKillVauel").setInt(0, 0);
	}

	if (MonsterKillVauel > 0)
	{

		local Size_Etc1 = sq_GetUniformVelocity(125, 100, currentT, 150);
		local img_size_Etc1 = Size_Etc1.tofloat() / 100.0;
		MonsterKillNum_one.setImageRateFromOriginal(img_size_Etc1, img_size_Etc1);
		local xpos = 0;

		//??ïÃí®?
		sq_DrawSpecificFrameEffect_SIMPLE(MonsterKillNum_Tip, base_x + xpos, base_y, 11, sq_RGB(255, 255, 255), sq_ALPHA(255), false);
		//??ïÃÝ¬?
		sq_DrawSpecificFrameEffect_SIMPLE(MonsterKillNum_TipEtc, base_x - 30 + xpos, base_y + 5, 12, sq_RGB(255, 255, 255), sq_ALPHA(255), false);
		//??ïÃ?í®
		local Num = MonsterKillVauel

		local geNum = Num / 1 % 10;
		local shiNum = Num / 10 % 10;
		local baiNum = Num / 100 % 10;
		local qianNum = Num / 1000 % 10;
		local WanNum = Num / 10000 % 10;

		if (Num >= 99999)
			Num = 99999;
		sq_DrawSpecificFrameEffect_SIMPLE(MonsterKillNum_one, base_x - 30 - (i * 1) + xpos, base_y + 5, geNum + 1, sq_RGB(255, 255, 255), sq_ALPHA(255), false);
		if (Num > 9)
		{
			sq_DrawSpecificFrameEffect_SIMPLE(MonsterKillNum_one, base_x - 30 - (i * 2) + xpos, base_y + 5, shiNum + 1, sq_RGB(255, 255, 255), sq_ALPHA(255), false);
		}
		if (Num > 99)
		{
			sq_DrawSpecificFrameEffect_SIMPLE(MonsterKillNum_one, base_x - 30 - (i * 3) + xpos, base_y + 5, baiNum + 1, sq_RGB(255, 255, 255), sq_ALPHA(255), false);
		}
		if (Num > 999)
		{
			sq_DrawSpecificFrameEffect_SIMPLE(MonsterKillNum_one, base_x - 30 - (i * 4) + xpos, base_y + 5, qianNum + 1, sq_RGB(255, 255, 255), sq_ALPHA(255), false);
		}
		if (Num > 9999)
		{
			sq_DrawSpecificFrameEffect_SIMPLE(MonsterKillNum_one, base_x - 30 - (i * 5) + xpos, base_y + 5, WanNum + 1, sq_RGB(255, 255, 255), sq_ALPHA(255), false);
		}
	}

}

function Dungeon_MonsterKillTip(obj, base_x, base_y, alpha, Dungeon_num, size)
{
	local baseRGB = sq_RGB(255, 255, 255);
	local sq_var = obj.getVar();

	local monsterkill_Tip = sq_var.GetAnimationMap("monsterkillback",
		"common/commoneffect/animation/newranksystem/monsterkill_grade.ani");

	local monsterkill_Tip2 = sq_var.GetAnimationMap("monsterkillbacktwo",
		"common/commoneffect/animation/newranksystem/monsterkill_grade.ani");


	local monsterkillbackl = sq_var.GetAnimationMap("monsterkillbackl",
		"common/commoneffect/animation/newranksystem/monsterkill_grade_l.ani");

	local monsterkill_Dark = sq_var.GetAnimationMap("monsterkillDark",
		"common/commoneffect/animation/newranksystem/monsterkill_grade.ani");

	local MonsterKillTip = obj.getVar("KillTip").getInt(0);
	if (MonsterKillTip > 0)
	{
		local t = obj.getVar("KillTip").get_ct_vector(0);
		if (!t)
		{
			obj.getVar("KillTip").clear_ct_vector();
			obj.getVar("KillTip").push_ct_vector();
			t = obj.getVar("KillTip").get_ct_vector(0);
			t.Reset();
			t.Start(1226, 0);
		}
		local currentT = t.Get();
		//

		if (currentT > 1500)
		{
			obj.getVar("KillTip").setInt(0, 0);
		}
		local Xpos = sq_GetUniformVelocity(60, 0, currentT, 150);
		local ALPHA = sq_GetUniformVelocity(0, 255, currentT, 300);
		local ALPHA2 = sq_GetUniformVelocity(250, 0, currentT, 300);
		local ALPHA_Effect = sq_GetUniformVelocity(0, 255, currentT, 150);
		local Size = sq_GetUniformVelocity(135, 80, currentT, 80); //ÛÜî¼ÓÞá³
		local img_size = Size.tofloat() / 100.0;
		local Size_Etc1 = sq_GetUniformVelocity(100, 75, currentT, 150);
		local img_size_Etc1 = Size_Etc1.tofloat() / 100.0;

		monsterkill_Tip.setImageRateFromOriginal(img_size, img_size);
		monsterkill_Tip2.setImageRateFromOriginal(0.8, 0.8);
		monsterkill_Dark.setImageRateFromOriginal(img_size_Etc1, img_size_Etc1);


		sq_AnimationProc(monsterkillbackl);
		//sq_drawCurrentFrame(monsterkillbackl, base_x, base_y, false);
		//ýÙî¼
		sq_DrawSpecificFrameEffect_SIMPLE(monsterkill_Tip2, base_x, base_y, 10, sq_RGB(255, 255, 255), sq_ALPHA(ALPHA), false);
		//ÛÜî¼
		sq_DrawSpecificFrameEffect_SIMPLE(monsterkill_Tip, base_x, base_y, 6, sq_RGB(255, 255, 255), sq_ALPHA(ALPHA2), false);
		//?
		sq_DrawSpecificFrameEffect_SIMPLE(monsterkill_Dark, base_x + Xpos, base_y, MonsterKillTip, sq_RGB(255, 255, 255), sq_ALPHA(ALPHA_Effect), false);
	}

}

function Dungeon_Rank(obj, base_x, base_y, alpha, Dungeon_num, size) //?ÝÂí®Ù½
{
	local baseRGB = sq_RGB(255, 0, 0);
	local size = 1.0;
	local sq_var = obj.getVar();
	/*

*/

	local dungeon_rank = sq_var.GetAnimationMap("dungeon_rank",
		"common/commoneffect/animation/newranksystem/dungeon_rank.ani");
	sq_AnimationProc(dungeon_rank);

	local dungeon_rank_bottom = sq_var.GetAnimationMap("dungeon_rank_bottom",
		"common/commoneffect/animation/newranksystem/dungeon_rank_bottom.ani");
	sq_AnimationProc(dungeon_rank_bottom);

	local dungeon_rank_effect = sq_var.GetAnimationMap("dungeon_rank_effect",
		"common/commoneffect/animation/newranksystem/dungeon_rank_glow2.ani");
	sq_AnimationProc(dungeon_rank_effect);


	local dungeon_rank_effect2 = sq_var.GetAnimationMap("dungeon_rank_efft",
		"common/commoneffect/animation/newranksystem/dungeon_rank_glow.ani");
	sq_AnimationProc(dungeon_rank_effect2);

	dungeon_rank.setImageRateFromOriginal(size, size);
	local Rank_Level = 0
	local Clip = 0

	local t = obj.getVar("Dungeon_RankEffect").get_ct_vector(0);
	local flagst = obj.getVar("Dungeon_RankEffectTip").getInt(0);

	if (!t)
	{
		obj.getVar("Dungeon_RankEffect").clear_ct_vector();
		obj.getVar("Dungeon_RankEffect").push_ct_vector();
		t = obj.getVar("Dungeon_RankEffect").get_ct_vector(0);
		t.Reset();
		t.Start(1228, 0);
	}
	local currentT = t.Get();



	local py = 0;
	if (Dungeon_num >= 0 && Dungeon_num <= 15000) //F
	{

		Clip = (Dungeon_num.tofloat() / 15000.0) * 27.0
		Rank_Level = 7
	}
	else if (Dungeon_num >= 15001 && Dungeon_num <= 85000) //D
	{
		if (flagst == 0)
		{
			PlaySound_Rate(obj, 1, 100, 100, "COMPOSE_TEXT");

			obj.getVar("Dungeon_RankEffect").clear_ct_vector();
			obj.getVar("Dungeon_RankEffectTip").setInt(0, 1);
		}
		Clip = (Dungeon_num.tofloat() / 85000.0) * 27.0
		Rank_Level = 6
	}
	else if (Dungeon_num >= 85001 && Dungeon_num <= 450000) //C
	{
		if (flagst == 1)
		{
			PlaySound_Rate(obj, 1, 100, 100, "COMPOSE_TEXT");
			obj.getVar("Dungeon_RankEffect").clear_ct_vector();
			obj.getVar("Dungeon_RankEffectTip").setInt(0, 2);
		}
		Clip = (Dungeon_num.tofloat() / 450000.0) * 27.0
		Rank_Level = 5
	}
	else if (Dungeon_num >= 450001 && Dungeon_num <= 850000) //B
	{
		if (flagst == 2)
		{
			PlaySound_Rate(obj, 1, 100, 100, "COMPOSE_TEXT");
			obj.getVar("Dungeon_RankEffect").clear_ct_vector();
			obj.getVar("Dungeon_RankEffectTip").setInt(0, 3);
		}
		Clip = ((Dungeon_num.tofloat() - 450000.0) / 35000.0) * 27.0
		Rank_Level = 4
	}
	else if (Dungeon_num >= 850001 && Dungeon_num <= 1350000) //A
	{
		if (flagst == 3)
		{
			PlaySound_Rate(obj, 1, 100, 100, "COMPOSE_TEXT");
			obj.getVar("Dungeon_RankEffect").clear_ct_vector();
			obj.getVar("Dungeon_RankEffectTip").setInt(0, 4);
		}
		Clip = ((Dungeon_num.tofloat() - 850000.0) / 47000.0) * 27.0
		Rank_Level = 3
	}
	else if (Dungeon_num >= 1350001 && Dungeon_num <= 1850000) //S
	{
		if (flagst == 4)
		{
			PlaySound_Rate(obj, 1, 100, 100, "COMPOSE_TEXT");
			obj.getVar("Dungeon_RankEffect").clear_ct_vector();
			obj.getVar("Dungeon_RankEffectTip").setInt(0, 5);
		}
		Clip = ((Dungeon_num.tofloat() - 1350000.0) / 45000.0) * 27.0
		Rank_Level = 2
	}
	else if (Dungeon_num >= 1850001 && Dungeon_num <= 2300000) //SS
	{
		py = 10;
		if (flagst == 5)
		{
			PlaySound_Rate(obj, 1, 100, 100, "COMPOSE_TEXT");
			obj.getVar("Dungeon_RankEffect").clear_ct_vector();
			obj.getVar("Dungeon_RankEffectTip").setInt(0, 6);
		}
		Clip = ((Dungeon_num.tofloat() - 1850001.0) / 45000.0) * 27.0
		Rank_Level = 1
	}
	else if (Dungeon_num >= 2300001) //SSS
	{
		py = 10;
		if (flagst == 6)
		{
			PlaySound_Rate(obj, 1, 100, 100, "COMPOSE_TEXT");
			obj.getVar("Dungeon_RankEffect").clear_ct_vector();
			obj.getVar("Dungeon_RankEffectTip").setInt(0, 0);
		}

		Clip = ((Dungeon_num.tofloat() - 2300001.0) / 38000.0) * 27.0
		Rank_Level = 0
	}
	obj.getVar("Rank_Leveltt").setInt(0, Rank_Level);
	if (Clip >= 27)
		Clip = 27; //??ùÚð¤
	//
	local ALPHA_Effect = sq_GetUniformVelocity(255, 0, currentT - 200, 800);
	local Size = sq_GetUniformVelocity(250, 100, currentT, 200);
	local img_size = Size.tofloat() / 100.0;
	dungeon_rank_effect.setImageRateFromOriginal(img_size, img_size);
	sq_DrawSpecificFrameEffect_SIMPLE(dungeon_rank_bottom, base_x - 3, base_y - 2, Rank_Level, sq_RGB(0, 0, 0), alpha, false);

	setClip(base_x - 50, base_y - Clip.tointeger(), base_x, base_y);
	sq_DrawSpecificFrameEffect_SIMPLE(dungeon_rank, base_x, base_y, Rank_Level, sq_RGB(255, 255, 255), alpha, false);
	releaseClip();

	sq_DrawSpecificFrameEffect_SIMPLE(dungeon_rank_effect, base_x - 23, base_y - 15, Rank_Level, sq_RGB(255, 255, 255), sq_ALPHA(ALPHA_Effect), true);

	local Sizex = sq_GetUniformVelocity(170, 0, currentT - 100, 200);
	local img_sizex = Sizex.tofloat() / 100.0;
	dungeon_rank_effect2.setImageRateFromOriginal(img_sizex, img_sizex);

	sq_drawCurrentFrame(dungeon_rank_effect2, base_x - 12 - py, base_y - 15, false);

}

function Dungeon_Score_num(obj, base_x, base_y, alpha, Num, size) //?ÝÂ?í®
{

	local baseRGB = sq_RGB(255, 255, 255);
	local sq_var = obj.getVar();
	local dungeon_score_num = sq_var.GetAnimationMap("dungeon_score_num",
		"common/commoneffect/animation/newranksystem/dungeon_score_num.ani");
	sq_AnimationProc(dungeon_score_num);
	dungeon_score_num.setImageRateFromOriginal(size, size);
	if (Num >= 9999999)
		Num = 9999999;
	local geNum = Num / 1 % 10;
	local shiNum = Num / 10 % 10;
	local baiNum = Num / 100 % 10;
	local qianNum = Num / 1000 % 10;
	local wanNum = Num / 10000 % 10;
	local swanNum = Num / 100000 % 10;
	local bwanNum = Num / 1000000 % 10;
	local i = 20;
	if (Num >= 0)
	{
		sq_DrawSpecificFrameEffect_SIMPLE(dungeon_score_num, base_x - (i * 0), base_y, geNum, baseRGB, alpha, false);
	}
	if (Num > 9)
	{
		sq_DrawSpecificFrameEffect_SIMPLE(dungeon_score_num, base_x - (i * 1), base_y, shiNum, baseRGB, alpha, false);
	}
	if (Num > 99)
	{
		sq_DrawSpecificFrameEffect_SIMPLE(dungeon_score_num, base_x - (i * 2), base_y, baiNum, baseRGB, alpha, false);
	}
	if (Num > 999)
	{
		sq_DrawSpecificFrameEffect_SIMPLE(dungeon_score_num, base_x - (i * 3), base_y, qianNum, baseRGB, alpha, false);
	}
	if (Num > 9999)
	{
		sq_DrawSpecificFrameEffect_SIMPLE(dungeon_score_num, base_x - (i * 4), base_y, wanNum, baseRGB, alpha, false);
	}
	if (Num > 99999)
	{
		sq_DrawSpecificFrameEffect_SIMPLE(dungeon_score_num, base_x - (i * 5), base_y, swanNum, baseRGB, alpha, false);
	}
	if (Num > 999999)
	{
		sq_DrawSpecificFrameEffect_SIMPLE(dungeon_score_num, base_x - (i * 6), base_y, bwanNum, baseRGB, alpha, false);
	}
}

function Dungeon_Combo(obj, base_x, base_y, alpha, Num, size) //?ÝÂ???í®
{
	local baseRGB = sq_RGB(255, 255, 255);
	local sq_var = obj.getVar();
	local dungeon_Combo = sq_var.GetAnimationMap("dungeon_ComboTip", "common/commoneffect/animation/newranksystem/combo_bonus.ani");
	local dungeon_Combo_Plus = sq_var.GetAnimationMap("dungeon_Plus", "common/commoneffect/animation/newranksystem/combo_bonus_plus.ani");
	local Combo = obj.getVar("Dungeon_Combo").getInt(0); //?ÝÂò¦?combo
	if (Combo >= 9999999)
		Combo = 9999999;
	local geNum = Combo / 1 % 10;
	sq_AnimationProc(dungeon_Combo);
	sq_AnimationProc(dungeon_Combo_Plus);
	dungeon_Combo_Plus.setImageRateFromOriginal(size, size);
	if (Combo > 0)
	{
		sq_DrawSpecificFrameEffect_SIMPLE(dungeon_Combo, base_x, base_y, 5, baseRGB, alpha, false);
		local i = 12;
		if (Combo >= 0)
		{
			sq_DrawSpecificFrameEffect_SIMPLE(dungeon_Combo_Plus, base_x - 28 - (i * 0), base_y + 3, 0, baseRGB, alpha, false);
		}
	}
}

function Dungeon_Tip(obj, base_x, base_y, alpha, Num, size) //ãáãÓð«ãÆ
{

	local baseRGB = sq_RGB(255, 255, 255);
	local sq_var = obj.getVar();
	local dungeon_ComboTipTTT1 = sq_var.GetAnimationMap("dungeon_ComboTipTTT1",
		"common/commoneffect/animation/newranksystem/combo_bonus.ani");
	local dungeon_ComboTipTTT2 = sq_var.GetAnimationMap("dungeon_ComboTipTTT2",
		"common/commoneffect/animation/newranksystem/combo_bonus.ani");
	local dungeon_ComboTipTTT3 = sq_var.GetAnimationMap("dungeon_ComboTipTTT3",
		"common/commoneffect/animation/newranksystem/combo_bonus.ani");
	local dungeon_ComboTipTTT4 = sq_var.GetAnimationMap("dungeon_ComboTipTTT4",
		"common/commoneffect/animation/newranksystem/combo_bonus.ani");


	local ComboTip_Etc1 = sq_var.GetAnimationMap("ComboTip_Etc_A",
		"common/commoneffect/animation/newranksystem/combo_effect.ani");
	local ComboTip_Etc2 = sq_var.GetAnimationMap("ComboTip_Etc_B",
		"common/commoneffect/animation/newranksystem/combo_effect.ani");
	local ComboTip_Etc3 = sq_var.GetAnimationMap("ComboTip_Etc_C",
		"common/commoneffect/animation/newranksystem/combo_effect.ani");
	local ComboTip_Etc4 = sq_var.GetAnimationMap("ComboTip_Etc_D",
		"common/commoneffect/animation/newranksystem/combo_effect.ani");


	local i = 18;

	local Tip1 = obj.getVar("Tip1").getInt(0);
	local Tip2 = obj.getVar("Tip2").getInt(0);
	local Tip3 = obj.getVar("Tip3").getInt(0);
	local Tip4 = obj.getVar("Tip4").getInt(0);
	/*
	
	
	
	
	*/
	if (Tip1 > 0)
	{
		local t = obj.getVar("Tip1").get_ct_vector(0);
		if (!t)
		{
			obj.getVar("Tip1").clear_ct_vector();
			obj.getVar("Tip1").push_ct_vector();
			t = obj.getVar("Tip1").get_ct_vector(0);
			t.Reset();
			t.Start(1221, 0);
		}
		local currentT = t.Get();


		local Xpos = sq_GetUniformVelocity(60, 0, currentT, 150);
		if (currentT >= 1000)
		{
			Xpos = sq_GetUniformVelocity(0, 150, currentT - 1000, 150);
		}
		if (currentT > 1500)
		{
			obj.getVar("Tip1").setInt(0, 0);
		}
		local ALPHA = sq_GetUniformVelocity(0, 255, currentT, 200);
		local ALPHA_Effect = sq_GetUniformVelocity(255, 0, currentT, 150);
		local Size = sq_GetUniformVelocity(150, 100, currentT, 200);
		local img_size = Size.tofloat() / 100.0;
		local Size_Etc1 = sq_GetUniformVelocity(100, 0, currentT, 150);
		local img_size_Etc1 = Size_Etc1.tofloat() / 100.0;
		dungeon_ComboTipTTT1.setImageRateFromOriginal(img_size, img_size);
		ComboTip_Etc1.setImageRateFromOriginal(img_size_Etc1, img_size_Etc1);
		//sq_DrawSpecificFrameEffect_SIMPLE(ComboTip_Etc1, base_x - 5 , base_y + (i * 1), 0, baseRGB, sq_ALPHA(ALPHA_Effect), false);
		sq_DrawSpecificFrameEffect_SIMPLE(dungeon_ComboTipTTT1, base_x + Xpos, base_y + (i * 1), Tip1, baseRGB, sq_ALPHA(ALPHA), false);
		sq_AnimationProc(ComboTip_Etc1);
		sq_drawCurrentFrame(ComboTip_Etc1, base_x - 5, base_y + (i * 1), false);
	}
	if (Tip2 > 0)
	{

		local t = obj.getVar("Tip2").get_ct_vector(0);
		if (!t)
		{
			obj.getVar("Tip2").clear_ct_vector();
			obj.getVar("Tip2").push_ct_vector();
			t = obj.getVar("Tip2").get_ct_vector(0);
			t.Reset();
			t.Start(1222, 0);
		}
		local currentT = t.Get();
		if (currentT > 1500)
		{
			obj.getVar("Tip2").setInt(0, 0);
		}
		local Xpos = sq_GetUniformVelocity(60, 0, currentT, 150);
		if (currentT >= 1000)
		{
			Xpos = sq_GetUniformVelocity(0, 150, currentT - 1000, 150);
		}
		local ALPHA = sq_GetUniformVelocity(0, 255, currentT, 200);
		local ALPHA_Effect = sq_GetUniformVelocity(255, 0, currentT, 150);
		local Size = sq_GetUniformVelocity(150, 100, currentT, 200);
		local img_size = Size.tofloat() / 100.0;
		local Size_Etc1 = sq_GetUniformVelocity(100, 0, currentT, 150);
		local img_size_Etc1 = Size_Etc1.tofloat() / 100.0;
		dungeon_ComboTipTTT2.setImageRateFromOriginal(img_size, img_size);
		ComboTip_Etc2.setImageRateFromOriginal(img_size_Etc1 - 0.0, img_size_Etc1 - 0.0);
		//sq_DrawSpecificFrameEffect_SIMPLE(ComboTip_Etc2, base_x - 5  , base_y + (i * 2), 0, baseRGB, sq_ALPHA(ALPHA_Effect), false);
		sq_DrawSpecificFrameEffect_SIMPLE(dungeon_ComboTipTTT2, base_x + Xpos, base_y + (i * 2), Tip2, baseRGB, sq_ALPHA(ALPHA), false);
		sq_AnimationProc(ComboTip_Etc2);
		sq_drawCurrentFrame(ComboTip_Etc2, base_x - 5, base_y + (i * 2), false);
	}
	if (Tip3 > 0)
	{
		local t = obj.getVar("Tip3").get_ct_vector(0);
		if (!t)
		{
			obj.getVar("Tip3").clear_ct_vector();
			obj.getVar("Tip3").push_ct_vector();
			t = obj.getVar("Tip3").get_ct_vector(0);
			t.Reset();
			t.Start(1223, 0);
		}
		local currentT = t.Get();
		if (currentT > 1500)
		{
			obj.getVar("Tip3").setInt(0, 0);
		}
		local Xpos = sq_GetUniformVelocity(60, 0, currentT, 150);
		if (currentT >= 1000)
		{
			Xpos = sq_GetUniformVelocity(0, 150, currentT - 1000, 150);
		}
		local ALPHA = sq_GetUniformVelocity(0, 255, currentT, 200);
		local ALPHA_Effect = sq_GetUniformVelocity(255, 0, currentT, 150);
		local Size = sq_GetUniformVelocity(150, 100, currentT, 200);
		local img_size = Size.tofloat() / 100.0;
		local Size_Etc1 = sq_GetUniformVelocity(100, 0, currentT, 150);
		local img_size_Etc1 = Size_Etc1.tofloat() / 100.0;
		dungeon_ComboTipTTT3.setImageRateFromOriginal(img_size, img_size);
		ComboTip_Etc3.setImageRateFromOriginal(img_size_Etc1 - 0.0, img_size_Etc1 - 0.0);
		//sq_DrawSpecificFrameEffect_SIMPLE(ComboTip_Etc3, base_x - 5  , base_y + (i * 3), 0, baseRGB, sq_ALPHA(ALPHA_Effect), false);
		sq_DrawSpecificFrameEffect_SIMPLE(dungeon_ComboTipTTT3, base_x + Xpos, base_y + (i * 3), Tip3, baseRGB, sq_ALPHA(255), false);
		sq_AnimationProc(ComboTip_Etc3);
		sq_drawCurrentFrame(ComboTip_Etc3, base_x - 5, base_y + (i * 3), false);
	}
	if (Tip4 > 0)
	{
		local t = obj.getVar("Tip4").get_ct_vector(0);
		if (!t)
		{
			obj.getVar("Tip4").clear_ct_vector();
			obj.getVar("Tip4").push_ct_vector();
			t = obj.getVar("Tip4").get_ct_vector(0);
			t.Reset();
			t.Start(1224, 0);
		}
		local currentT = t.Get();
		if (currentT > 1500)
		{
			obj.getVar("Tip4").setInt(0, 0);
		}
		local Xpos = sq_GetUniformVelocity(60, 0, currentT, 150);
		if (currentT >= 1000)
		{
			Xpos = sq_GetUniformVelocity(0, 150, currentT - 1000, 150);
		}
		local ALPHA = sq_GetUniformVelocity(0, 255, currentT, 200);
		local ALPHA_Effect = sq_GetUniformVelocity(255, 0, currentT, 150);
		local Size = sq_GetUniformVelocity(150, 100, currentT, 200);
		local img_size = Size.tofloat() / 100.0;
		local Size_Etc1 = sq_GetUniformVelocity(100, 0, currentT, 150);
		local img_size_Etc1 = Size_Etc1.tofloat() / 100.0;
		dungeon_ComboTipTTT4.setImageRateFromOriginal(img_size, img_size);
		ComboTip_Etc4.setImageRateFromOriginal(img_size_Etc1 - 0.0, img_size_Etc1 - 0.0);
		//sq_DrawSpecificFrameEffect_SIMPLE(ComboTip_Etc4, base_x - 5  , base_y + (i * 4), 0, baseRGB, sq_ALPHA(ALPHA_Effect), false);
		sq_DrawSpecificFrameEffect_SIMPLE(dungeon_ComboTipTTT4, base_x + Xpos, base_y + (i * 4), Tip4, baseRGB, sq_ALPHA(255), false);
		sq_AnimationProc(ComboTip_Etc4);
		sq_drawCurrentFrame(ComboTip_Etc4, base_x - 5, base_y + (i * 4), false);
	}
}
//----------------
//APD:

function onStart_appendage_ap_new_rank(appendage)
{
	if (!appendage)
	{
		return;
	}
	local obj = appendage.getParent();
	obj.getVar("Dungeon_num").setInt(0, 0);
	obj.getVar("Dungeon_Combo").setInt(0, 0);
	obj.getVar("Attack_Tip").clear_vector();
}

function onDamageParent_ap_new_rank(appendage ,attacker, boundingBox, isStuck) 
{
	if (!appendage)
	{
		return;
	}
	local obj = appendage.getParent();
	local Dungeon_num = obj.getVar("Dungeon_num").getInt(0); //?ÝÂò¦?
	if (isStuck) //Ú±Ù¤ñé
	{
		PlaySound_Rate(obj, 1, 100, 99, "HK3_NMISS");
		obj.getVar("Dungeon_num").setInt(0, Dungeon_num + 35);
		Tip(obj, 4);
	}
}


function onAttackParent_ap_new_rank(appendage, realAttacker, damager, boundingBox, isStuck)
{
	if (!appendage)
	{
		return;
	}
	local obj = appendage.getParent();
	local Dungeon_num = obj.getVar("Dungeon_num").getInt(0); //?ÝÂò¦?

	local Combo = obj.getVar("Dungeon_Combo").getInt(0); //?ÝÂò¦?combo

	local Rank_Level = obj.getVar("Rank_Leveltt").getInt(0);
	local Rank_LevelTT = obj.getVar("Rank_Leveltt").getInt(0);

	if (Rank_Level == 0)
		Rank_LevelTT = 8;
	if (Rank_Level == 1)
		Rank_LevelTT = 7;
	if (Rank_Level == 2)
		Rank_LevelTT = 6;
	if (Rank_Level == 3)
		Rank_LevelTT = 5;
	if (Rank_Level == 4)
		Rank_LevelTT = 4;
	if (Rank_Level == 5)
		Rank_LevelTT = 3;
	if (Rank_Level == 6)
		Rank_LevelTT = 2;
	if (Rank_Level == 7)
		Rank_LevelTT = 1;

	local ComboCount = 1;
	for (local i = 1 ; i<= 20 ; i++)
	{
		local Chr = sq_GetCNRDObjectToSQRCharacter(obj);
		local data = Chr.sq_GetIntData(169, i);
		if (data > 0)
		{
			ComboCount = ComboCount + 1;
		}
	}
	obj.getVar("Dungeon_Combo").setInt(0, Combo + ComboCount); //???Õá

	local MonsterKillVauel = obj.getVar("MonsterKillVauel").getInt(0);
	//?öèüÀ??êÈ
	if (damager.isObjectType(OBJECTTYPE_ACTIVE))
	{

		obj.getVar("Dungeon_Time").clear_ct_vector(); //?ð¶ñ«??
		if (isStuck) //Ú±Ù¤ñé
		{
			PlaySound_Rate(obj, 1, 100, 99, "HK3_NMISS");
			//obj.getVar("Dungeon_num").setInt(0, Dungeon_num + 35);
			//Tip(obj, 4);
		}

		if (obj.getDirection() == damager.getDirection()) //ÛÎý¨Íô?
		{
			PlaySound_Rate(obj, 1, 100, 25, "HK3_BATK");
			obj.getVar("Dungeon_num").setInt(0, Dungeon_num + (sq_getRandom(550, 750) * Rank_LevelTT));
			Tip(obj, 6);
		}
		else if (damager.getZPos() >= 20) //Ý©ÍöÍô?
		{
			Tip(obj, 1);
			PlaySound_Rate(obj, 1, 100, 100, "HK3_AERIAL");
			obj.getVar("Dungeon_num").setInt(0, Dungeon_num + (sq_getRandom(250, 550) * Rank_LevelTT));
		}
		else if (damager.getState() == STATE_ATTACK) //÷òôý
		{
			if (IsInterval(obj, 500))
			{
				Tip(obj, 8);
				PlaySound_Rate(obj, 1, 100, 35, "HK3_COUNTER");
				obj.getVar("Dungeon_num").setInt(0, Dungeon_num + (sq_getRandom(650, 950) * Rank_LevelTT));
			}
		}
		else if (damager.getState() == STATE_HOLD) //Ë­Íó
		{
			if (IsInterval(obj, 500))
			{
				Tip(obj, 2);
				PlaySound_Rate(obj, 1, 100, 100, "HK3_COUNTER");
				obj.getVar("Dungeon_num").setInt(0, Dungeon_num + (sq_getRandom(1500, 2985) * Rank_LevelTT));
			}
		}
		else
		{
			obj.getVar("Dungeon_num").setInt(0, Dungeon_num + (sq_getRandom(100, 500) * Rank_LevelTT));
		}
		local activeObj = sq_GetCNRDObjectToActiveObject(damager);
		local hp = activeObj.getHp();
		local maxHp = activeObj.getHpMax();
		if (hp == 0) //??÷÷?
		{

			obj.getVar("MonsterKillTime").clear_ct_vector(); //?ð¶????


			if (sq_IsBoss(activeObj))
			{
				KillTip(obj, 5)
				PlaySound_Rate(obj, 1, 100, 100, "HK3_OKILL");

				obj.getVar("MonsterKillVauel").setInt(0, MonsterKillVauel + sq_getRandom(15000, 56200)); //???
			}
			else if (activeObj.isCommonChampion())
			{
				PlaySound_Rate(obj, 1, 100, 100, "HK3_OKILL");
				obj.getVar("MonsterKillVauel").setInt(0, MonsterKillVauel + sq_getRandom(8590, 15600)); //???
			}
			else if (sq_IsHellMonster(activeObj))
			{
				obj.getVar("MonsterKillVauel").setInt(0, MonsterKillVauel + sq_getRandom(9500, 18200)); //???
			}
			else if (sq_IsAiCharacter(activeObj))
			{
				obj.getVar("MonsterKillVauel").setInt(0, MonsterKillVauel + sq_getRandom(5200, 15000)); //???
			}
			else if (activeObj.isSuperChampion())
			{
				obj.getVar("MonsterKillVauel").setInt(0, MonsterKillVauel + sq_getRandom(5200, 23000)); //???
			}
			else if (activeObj.isChampion())
			{
				PlaySound_Rate(obj, 1, 100, 100, "HK3_OKILL");
				obj.getVar("MonsterKillVauel").setInt(0, MonsterKillVauel + sq_getRandom(5500, 15600)); //???
			}
			else if (sq_IsNamed(activeObj))
			{
				obj.getVar("MonsterKillVauel").setInt(0, MonsterKillVauel + sq_getRandom(8500, 12000)); //???
			}
			else
			{
				obj.getVar("MonsterKillVauel").setInt(0, MonsterKillVauel + sq_getRandom(350, 900)); //???
			}

			local MonsterKillVauel = obj.getVar("MonsterKillVauel").getInt(0);
			local Rank_Leveltt = obj.getVar("Rank_Leveltt").getInt(0);
			obj.getVar("Dungeon_num").setInt(0, Dungeon_num + MonsterKillVauel);

			//if (!sq_IsBoss(activeObj))
			//{
				//sq_AddSetStatePacketActiveObject(activeObj,0, sq_GetGlobalIntVector(), STATE_PRIORITY_FORCE);
			//}
		}
	}
	//		PlaySound_Rate(obj, 1, 100,100,"HK3_GOOD");
	//		PlaySound_Rate(obj, 1, 100,100,"HK3_NICE");
	//		PlaySound_Rate(obj, 1, 100,10,"HK3_OKILL");
	//obj.getVar("Dungeon_RankEffect").clear_ct_vector();
}




function proc_appendage_ap_new_rank(appendage)
{
	if (!appendage)
	{
		return;
	}
	local obj = appendage.getParent();

	local DamagableState = obj.isInDamagableState(obj);

	local HK3_GFRAME = obj.getVar("HK3_GFRAME").getInt(0); //Ùé?ëåüù

	if (DamagableState == false && HK3_GFRAME == 0)
	{
		PlaySound_Rate(obj, 1, 100, 100, "HK3_GFRAME");
		obj.getVar("HK3_GFRAME").setInt(0, 1);
		Tip(obj, 3)
	}
	else if (DamagableState == true && HK3_GFRAME == 1)
	{
		obj.getVar("HK3_GFRAME").setInt(0, 0);
	}

}

function PlaySound_Rate(obj, min, max, value, name)
{
	local randNum = sq_getRandom(min, max);

	if (value >= randNum)
	{
		obj.sq_PlaySound(name);
	}
}


function Tip(obj, randNum)
{
	local Tip1 = obj.getVar("Tip1").getInt(0);
	local Tip2 = obj.getVar("Tip2").getInt(0);
	local Tip3 = obj.getVar("Tip3").getInt(0);
	local Tip4 = obj.getVar("Tip4").getInt(0);
	if (Tip1 == 0)
	{
		obj.getVar("Tip1").setInt(0, randNum);
		obj.getVar("Tip1").clear_ct_vector();
	}
	else if (Tip1 > 0 && Tip2 == 0)
	{
		obj.getVar("Tip2").setInt(0, randNum);
		obj.getVar("Tip2").clear_ct_vector();
	}
	else if (Tip1 > 0 && Tip2 > 0 && Tip3 == 0)
	{
		obj.getVar("Tip3").setInt(0, randNum);
		obj.getVar("Tip3").clear_ct_vector();
	}
	else if (Tip1 > 0 && Tip2 > 0 && Tip3 > 0 && Tip4 == 0)
	{
		obj.getVar("Tip4").setInt(0, randNum);
		obj.getVar("Tip4").clear_ct_vector();
	}
	else
	{
		obj.getVar("Tip1").setInt(0, 0);
		obj.getVar("Tip1").clear_ct_vector();
		obj.getVar("Tip2").setInt(0, 0);
		obj.getVar("Tip2").clear_ct_vector();
		obj.getVar("Tip3").setInt(0, 0);
		obj.getVar("Tip3").clear_ct_vector();
		obj.getVar("Tip4").setInt(0, 0);
		obj.getVar("Tip4").clear_ct_vector();
	}
}

function KillTip(obj, randNum)
{

	local KillTip = obj.getVar("KillTip").getInt(0);
	if (KillTip == 0)
	{
		obj.getVar("KillTip").setInt(0, randNum);
		obj.getVar("KillTip").clear_ct_vector();
	}

}
