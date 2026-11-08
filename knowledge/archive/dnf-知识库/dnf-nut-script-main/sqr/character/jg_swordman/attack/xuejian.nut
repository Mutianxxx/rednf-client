
//????????Gskill/JG_SwordMan/swordman2.skl

function onKeyFrameFlag_XueJian(obj,flagIndex)
{
	if(!obj)
		return false;
		
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	
	if(state == STATE_XUE_JIAN)
	{
			if (flagIndex == 100)//????100
			{
		//obj.sq_SetShake(obj,3,500);
		//sq_flashScreen(obj, 0, 250, 300, 140, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);//?????
				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOOD_SWORD, -1, SKL_LVL_COLUMN_IDX_0, 5.0);//??????????SKL.0?????????????????1.0??
				local sizeRate = obj.sq_GetIntData(SKILL_BLOOD_SWORD, 6);
				obj.sq_StartWrite();//????????
				obj.sq_WriteDword(attackBonusRate);	// ??????????
				obj.sq_WriteWord(sizeRate);		// OBJ???????????
				obj.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 0, 0);//???i???
			}
		

	}	
	return true;
}

}
