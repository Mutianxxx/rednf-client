
sq_RunScript("Custom/Content/NewRankSystem.nut");
sq_RunScript("apjh/skillcooltime.nut");

sq_RunScript("apjh/onstartdungeon.nut");
sq_RunScript("apjh/onstartmap.nut");
sq_RunScript("apjh/drawmaincustomui.nut");
sq_RunScript("apjh/procappend.nut");
sq_RunScript("apjh/drawcustomui.nut");
sq_RunScript("apjh/onmouseleftbuttondown.nut");
sq_RunScript("apjh/resetdungeonstart.nut");
sq_RunScript("apjh/useskill_before.nut");

sq_RunScript("ui/damagefont/damagefont_header.nut");
sq_RunScript("ui/damagefont/damagefont_cache.nut");
sq_RunScript("ui/damagefont/damagefont_function.nut");

sq_RunScript("ui/monsterui/monsterui_function.nut");

sq_RunScript("ui/preload/preload_function.nut");
sq_RunScript("ui/preload/preload_skill_config.nut");
sq_RunScript("ui/preload/preload_monster_config.nut");

sq_RunScript("ui/cutscene/cutin_header.nut");
sq_RunScript("ui/cutscene/cutin_function.nut");
sq_RunScript("ui/cutscene/buff_function.nut");
sq_RunScript("ui/cutscene/ultimate_function.nut");

sq_RunScript("ui/pvpfont/pvpfont_header.nut");
sq_RunScript("ui/pvpfont/pvpfont_function.nut");

sq_RunScript("ui/skinstorage/damagefont_key_value.nut");
sq_RunScript("ui/skinstorage/skinstorage_header.nut");
sq_RunScript("ui/skinstorage/skinstorage_function.nut");

sq_RunScript("custom/content/new_skill_button.nut");
sq_RunScript("custom/content/draw_ex_skill_button.nut");

function isUsableItem_AllGrowJob(obj,itemIndex)
{
	if(DO_FONT_FILE_KEY == 0)
		tranFontKeyToValue();
		
	local job = sq_getJob(obj);
	local growType = sq_getGrowType(obj);
		
	if(job != CURRENT_CHARACTER_JOB || growType != CURRENT_CHARACTER_GROW_TYPE)
	{
		CURRENT_CHARACTER_JOB = job;
		CURRENT_CHARACTER_GROW_TYPE = growType;
		setCharacterDefaultCutscene(job,growType);
	}

	if(itemIndex >= 490010001 && itemIndex <= 490010091)
		checkDamageFontItem(itemIndex);
}

function duegonUsableItem(itemIndex)
{
	if(itemIndex == 10312077)
	{
		return isInBloodyFruitDuegon();
	}
	if(itemIndex >= 10315105 && itemIndex <= 10315109)
	{
		return isInDuegon(5006);
	}
	return true;
}