function drawNewDamageUI_AllGrowJob(obj) {
	if (!obj) return;
	
	drawExSkillButtonIcon(obj);

	if (INVENTORY_DOWN == 1) {
		drawSkinStorage_AllGrowJob(obj);
	}
	
	//Debug
	//overloadFiles(obj);
	//PrintScreenInfo(obj);
}