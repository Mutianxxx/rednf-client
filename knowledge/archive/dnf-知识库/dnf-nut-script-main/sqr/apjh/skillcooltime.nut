function SkillCoolTimeUI(obj) {

	local skillmgr = obj.getSkillManager();
	local apd = getComboUiAppendage(obj);
	if (!apd) return false;

	local currentT = apd.getTimer().Get();
	local offsetX = 0;
	local offsetY = 0;

	if (apd.getVar("saveSkillOkTime").size_vector() == 0) {
		apd.getVar("saveSkillOkTime").clear_vector();
		for (local i = 0; i < 255; i++)
		apd.getVar("saveSkillOkTime").push_vector(-1);

		apd.getVar("saveCurrentSklTime").clear_vector();
		for (local i = 0; i < 255; i++)
		apd.getVar("saveCurrentSklTime").push_vector(-1);
	}
	if (obj.getVar("nskEnd").getBool(0)) {
		if (NewSkillCoolTimeEndAni(obj, true)) {
			obj.getVar("nskEnd").setBool(0, false);
		}
	}
	if (obj.getVar("nskEnd").getBool(1)) {
		if (NewSkillCoolTimeEndAni(obj, false)) {
			obj.getVar("nskEnd").setBool(1, false);
		}
	}

	for (local i = 1; i < 255; i++) {
		local skl = sq_GetSkill(obj, i);
		if (skl) {
			local isCool = skl.isInCoolTime();
			if (isCool) {
				if (apd.getVar("saveSkillOkTime").get_vector(i) == -1) {
					apd.getVar("saveSkillOkTime").set_vector(i, currentT);
					apd.getVar("saveCurrentSklTime").set_vector(i, skl.getCoolTime(obj, -1));
				}
				else {
					local id = skillmgr.getSlotindex(i);
					local newidc = obj.getVar("newslotindex").getInt(1);
					local newida = obj.getVar("newslotindex").getInt(0);
					if ((id >= 0 && id < 6)) {
						if(CFG_FUNC_NUTCOOLTIME < 1){
							return;
						}
						local coolTime = apd.getVar("saveCurrentSklTime").get_vector(i);
						local curCoolTime = coolTime - (currentT - apd.getVar("saveSkillOkTime").get_vector(i));
						if (curCoolTime >= 10000) drawSirocoUINumberWithPos(obj, 313 + CFG_UI_NUTCOOLTIME_EXBAR_OFFSETX + id * 31, 575 + CFG_UI_NUTCOOLTIME_EXBAR_OFFSETY, curCoolTime / 1000);
						else drawSirocoUINumberWithPosPoint(obj, 313 + CFG_UI_NUTCOOLTIME_EXBAR_OFFSETX  + id * 31, 575 + CFG_UI_NUTCOOLTIME_EXBAR_OFFSETY, curCoolTime / 100);
					}
					else if ((id >= 198 && id < 204)) {
						if(CFG_FUNC_NUTCOOLTIME < 1){
							return;
						}
						local id = id - 198;
						local coolTime = apd.getVar("saveCurrentSklTime").get_vector(i);
						local curCoolTime = coolTime - (currentT - apd.getVar("saveSkillOkTime").get_vector(i));
						if (curCoolTime >= 10000) drawSirocoUINumberWithPos(obj, 313 + CFG_UI_NUTCOOLTIME_BAR_OFFSETX + id * 31, 544 + CFG_UI_NUTCOOLTIME_BAR_OFFSETY, curCoolTime / 1000);
						else drawSirocoUINumberWithPosPoint(obj, 313 + CFG_UI_NUTCOOLTIME_BAR_OFFSETX  + id * 31, 544 + CFG_UI_NUTCOOLTIME_BAR_OFFSETY, curCoolTime / 100);
					}
					else if (newidc > 0 && newidc == i) {
						local coolTime = apd.getVar("saveCurrentSklTime").get_vector(i);
						local curCoolTime = coolTime - (currentT - apd.getVar("saveSkillOkTime").get_vector(i));
						NewSkillCoolTimeShadow(obj, coolTime, curCoolTime, false);
						if (curCoolTime >= 10000) {
							drawSirocoUINumberWithPos(obj, CFG_UI_NUTNEWSKILLCTRL_POS_X + 13, CFG_UI_NUTNEWSKILLCTRL_POS_Y + 10, curCoolTime / 1000);
						}
						else {
							if (curCoolTime < 100) {
								obj.getVar("nskEnd").setBool(1, true);
							}
							drawSirocoUINumberWithPosPoint(obj, CFG_UI_NUTNEWSKILLCTRL_POS_X + 13, CFG_UI_NUTNEWSKILLCTRL_POS_Y + 10, curCoolTime / 100);
						}
					}
					else if (newida > 0 && newida == i) {
						local coolTime = apd.getVar("saveCurrentSklTime").get_vector(i);
						local curCoolTime = coolTime - (currentT - apd.getVar("saveSkillOkTime").get_vector(i));
						NewSkillCoolTimeShadow(obj, coolTime, curCoolTime, true);
						if (curCoolTime >= 10000) {
							drawSirocoUINumberWithPos(obj, CFG_UI_NUTNEWSKILLALT_POS_X + 13, CFG_UI_NUTNEWSKILLALT_POS_Y + 10, curCoolTime / 1000);
						}
						else {
							if (curCoolTime < 100) {
								obj.getVar("nskEnd").setBool(0, true);
							}
							drawSirocoUINumberWithPosPoint(obj, CFG_UI_NUTNEWSKILLALT_POS_X + 13, CFG_UI_NUTNEWSKILLALT_POS_Y + 10, curCoolTime / 100);
						}
					}
					else {
						if(CFG_FUNC_NUTCOOLTIME < 1){
							return;
						}
						local coolTime = apd.getVar("saveCurrentSklTime").get_vector(i);
						local curCoolTime = coolTime - (currentT - apd.getVar("saveSkillOkTime").get_vector(i));
						local lastX = CFG_UI_NUTCOOLTIME_POS_X + offsetX;
						local lastY = CFG_UI_NUTCOOLTIME_POS_Y + offsetY;
						sq_DrawSkillIcon(skl, lastX, lastY, sq_ALPHA(100));
						if (curCoolTime >= 10000) 
							drawSirocoUINumberWithPos(obj, lastX + 11, lastY + 10, curCoolTime / 1000);
						else 
							drawSirocoUINumberWithPosPoint(obj, lastX + 11, lastY + 10, curCoolTime / 100);
						if (offsetX <= 150) {
							offsetX += 30;
						}
						else {
							offsetX = 0;
							offsetY -= 30;
						}
					}

				}
			}
			else {
				if (apd.getVar("saveSkillOkTime").get_vector(i) != -1) {
					apd.getVar("saveSkillOkTime").set_vector(i, -1);
				}
				else {
				}
			}
		}
	}
}

function getComboUiAppendage(obj) {
	return obj.GetSquirrelAppendage("apjh/currency.nut");
}

function drawSirocoUINumberWithPos(obj, x, y, var) {

	if (var == 0) {
		local ani = getSirocoUINumber(obj, 0);
		//sq_AnimationProc(ani);
		//sq_drawCurrentFrame(ani, x, y, false);
		sq_DrawSpecificFrame(ani, x, y, false, 0, false, 1.0);
		return false;
	}

	local saveVar = var;
	local saveVar2 = var;
	local offsetX = 0;
	local centerX = 0;

	while (saveVar2 > 0) {
		saveVar2 = saveVar2 / 10;
		centerX += 5;
	}

	while (saveVar > 0) {
		local v = saveVar % 10;
		local ani = getSirocoUINumber(obj, v);
		//sq_AnimationProc(ani);
		//sq_drawCurrentFrame(ani, x + offsetX, y, false);
		sq_DrawSpecificFrame(ani, x + offsetX, y, false, 0, false, 1.0);
		offsetX = offsetX - 5;
		saveVar = saveVar / 10;

	}

}

function getSirocoUINumber(obj, var) {
	local numImage = null;
	local sq_var = obj.getVar();
	var = var % 10;

	numImage = sq_var.GetAnimationMap("SirocoUINumber" + var, "common/skillcooltime/" + var + ".ani");

	return numImage;
}

function drawSirocoUINumberWithPosPoint(obj, x, y, var) {

	if (var < 0) {
		return false;
	}

	local offsetX = 0;
	local centerX = 0;

	local shi = var / 10;
	local ge = var % 10;

	local ani = getSirocoUINumber(obj, ge);
	//sq_AnimationProc(ani);
	sq_DrawSpecificFrame(ani, x + offsetX, y, false, 0, false, 1.0);
	//sq_drawCurrentFrame(ani, x + offsetX, y, false);
	offsetX = offsetX - 7;

	ani = getSirocoUINumber(obj, shi);
	//sq_AnimationProc(ani);
	//sq_drawCurrentFrame(ani, x + offsetX, y, false);
	sq_DrawSpecificFrame(ani, x + offsetX, y, false, 0, false, 1.0);
}

function NewSkillCoolTimeShadow(obj, coolTime, curCoolTime, alt) {
	if (!obj) return;
	local sq_var = obj.getVar();
	local nx = CFG_UI_NUTNEWSKILLCTRL_POS_X;
	local ny = CFG_UI_NUTNEWSKILLCTRL_POS_Y;
	if (alt == true) {
		nx = CFG_UI_NUTNEWSKILLALT_POS_X;
		ny = CFG_UI_NUTNEWSKILLALT_POS_Y;
	}
	local per = 28*curCoolTime/coolTime;
	local shadow = sq_var.GetAnimationMap("newcoolshadow", "sqr/custom/ani/skillicon/disable.ani");
	setClip(nx, ny, nx+28, ny + per.tointeger());
	sq_DrawSpecificFrame(shadow, nx, ny, false, 0, false, 1.0);
	releaseClip();
	return;
}

function NewSkillCoolTimeEndAni(obj, alt) {
	if (!obj) return;
	local nx = CFG_UI_NUTNEWSKILLCTRL_POS_X + 1;
	local ny = CFG_UI_NUTNEWSKILLCTRL_POS_Y - 26;
	local name = "nskC";
	if (alt == true) {
		nx = CFG_UI_NUTNEWSKILLALT_POS_X + 1;
		ny = CFG_UI_NUTNEWSKILLALT_POS_Y - 26;
		name = "nskA";
	}
	local end = obj.getVar().GetAnimationMap(name, "sqr/custom/ani/skillicon/cooltimeend.ani");
	sq_AnimationProc(end);
	sq_drawCurrentFrame(end, nx, ny + 27, false);
	if (sq_IsEnd(end)) {
		sq_Rewind(end);
		return true;
	}
	return false;
}
