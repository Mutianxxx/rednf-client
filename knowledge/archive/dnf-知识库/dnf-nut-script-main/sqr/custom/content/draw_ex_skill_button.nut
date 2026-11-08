

function drawExSkillButtonIcon(obj)//?????
{
	if(!obj) return;
	if(CFG_FUNC_NUTNEWSKILLSLOT < 1){
		return;
	}
	if(!obj.isMyControlObject()) return;
	if(!sq_IsMyCharacter(obj)) return;
	local sq_var = obj.getVar();
	local x = CFG_UI_NUTNEWSKILLCTRL_POS_X;//???X??
	local y = CFG_UI_NUTNEWSKILLCTRL_POS_Y;//???Y??
	local xc = CFG_UI_NUTNEWSKILLALT_POS_X;
	local yc = CFG_UI_NUTNEWSKILLALT_POS_Y;
	//y+31=565
	
	if (sq_getJob(obj) == ENUM_CHARACTERJOB_SWORDMAN)//??£º???
	{
		if(sq_getGrowType(obj) == 0)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 130), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 48), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 130, false );
				NewSkillCoolTimeUI( obj, 48, true );

		}
		if(sq_getGrowType(obj) == 1)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 246), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 86), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 246, false );
				NewSkillCoolTimeUI( obj, 86, true );

		}
		if(sq_getGrowType(obj) == 2)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 241), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));

				sq_DrawSkillIcon (sq_GetSkill(obj, 87), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 241, false );
				NewSkillCoolTimeUI( obj, 87, true );
		}
		if(sq_getGrowType(obj) == 3)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 231), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));

				sq_DrawSkillIcon (sq_GetSkill(obj, 85), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 231, false );
				NewSkillCoolTimeUI( obj, 85, true );
		}
		if(sq_getGrowType(obj) == 4)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 244), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));

				sq_DrawSkillIcon (sq_GetSkill(obj, 88), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 244, false );
				NewSkillCoolTimeUI( obj, 88, true );
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_FIGHTER)//??£º???
	{
		if(sq_getGrowType(obj) == 1)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 228), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));

				sq_DrawSkillIcon (sq_GetSkill(obj, 227), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 228, false );
				NewSkillCoolTimeUI( obj, 227, true );
		}
		if(sq_getGrowType(obj) == 2)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 232), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));

				sq_DrawSkillIcon (sq_GetSkill(obj, 71), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 232, false );
				NewSkillCoolTimeUI( obj, 71, true );
		}
		if(sq_getGrowType(obj) == 3)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 236), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));

				sq_DrawSkillIcon (sq_GetSkill(obj, 235), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 236, false );
				NewSkillCoolTimeUI( obj, 235, true );
		}
		if(sq_getGrowType(obj) == 4)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 239), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 63), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 239, false );
				NewSkillCoolTimeUI( obj, 63, true );
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_GUNNER)//??£º??
	{
		if(sq_getGrowType(obj) == 0)
		{
			sq_DrawSkillIcon (sq_GetSkill(obj, 133), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			sq_DrawSkillIcon (sq_GetSkill(obj, 118), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 133, false );
			NewSkillCoolTimeUI( obj, 118, true );
		}
		if(sq_getGrowType(obj) == 1)
		{
			sq_DrawSkillIcon (sq_GetSkill(obj, 240), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			sq_DrawSkillIcon (sq_GetSkill(obj, 64), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 240, false );
			NewSkillCoolTimeUI( obj, 64, true );
		}
		if(sq_getGrowType(obj) == 2)
		{

			sq_DrawSkillIcon (sq_GetSkill(obj, 235), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			sq_DrawSkillIcon (sq_GetSkill(obj, 54), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 235, false );
			NewSkillCoolTimeUI( obj, 54, true );
		}
		if(sq_getGrowType(obj) == 3)
		{
			sq_DrawSkillIcon (sq_GetSkill(obj, 247), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			sq_DrawSkillIcon (sq_GetSkill(obj, 67), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 247, false );
			NewSkillCoolTimeUI( obj, 67, true );
		}
		if(sq_getGrowType(obj) == 4)
		{
			sq_DrawSkillIcon (sq_GetSkill(obj, 245), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			sq_DrawSkillIcon (sq_GetSkill(obj, 70), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 245, false );
			NewSkillCoolTimeUI( obj, 70, true );
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_MAGE)//??£º??
	{
		if(sq_getGrowType(obj) == 0)
		{
			sq_DrawSkillIcon (sq_GetSkill(obj, 213), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 213, false);
			sq_DrawSkillIcon (sq_GetSkill(obj, 147), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 147, true);
		}
		if(sq_getGrowType(obj) == 1)
		{
			sq_DrawSkillIcon (sq_GetSkill(obj, 253), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 253, false);
			sq_DrawSkillIcon (sq_GetSkill(obj, 252), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 252, true);
		}
		if(sq_getGrowType(obj) == 2)
		{
			sq_DrawSkillIcon (sq_GetSkill(obj, 139), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			sq_DrawSkillIcon (sq_GetSkill(obj, 82), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 139, false );
			NewSkillCoolTimeUI( obj, 82, true );
		}
		if(sq_getGrowType(obj) == 3)
		{
			sq_DrawSkillIcon (sq_GetSkill(obj, 245), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			sq_DrawSkillIcon (sq_GetSkill(obj, 247), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 245, false );
			NewSkillCoolTimeUI( obj, 247, true );
		}
		if(sq_getGrowType(obj) == 4)
		{
			sq_DrawSkillIcon (sq_GetSkill(obj, 134), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			sq_DrawSkillIcon (sq_GetSkill(obj, 109), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 134, false );
			NewSkillCoolTimeUI( obj, 109, true );
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_PRIEST)//??£º???
	{
		if(sq_getGrowType(obj) == 1)
		{
				sq_DrawSkillIcon (sq_GetSkill(obj, 251), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 84), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 251, false );
				NewSkillCoolTimeUI( obj, 84, true );
		}
		if(sq_getGrowType(obj) == 2)
		{
				sq_DrawSkillIcon (sq_GetSkill(obj, 245), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 90), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 245, false );
				NewSkillCoolTimeUI( obj, 90, true );
		}
		if(sq_getGrowType(obj) == 3)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 241), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 93), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 241, false );
				NewSkillCoolTimeUI( obj, 93, true );
		}
		if(sq_getGrowType(obj) == 4)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 138), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 119), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 138, false );
				NewSkillCoolTimeUI( obj, 119, true );

		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_AT_GUNNER)//??£º??
	{
		if(sq_getGrowType(obj) == 1)
		{
			sq_DrawSkillIcon (sq_GetSkill(obj, 239), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			sq_DrawSkillIcon (sq_GetSkill(obj, 100), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 239, false );
			NewSkillCoolTimeUI( obj, 100, true );
		}
		if(sq_getGrowType(obj) == 2)
		{
			sq_DrawSkillIcon (sq_GetSkill(obj, 235), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			sq_DrawSkillIcon (sq_GetSkill(obj, 97), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 235, false );
			NewSkillCoolTimeUI( obj, 97, true );
		}
		if(sq_getGrowType(obj) == 3)
		{
			sq_DrawSkillIcon (sq_GetSkill(obj, 249), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			sq_DrawSkillIcon (sq_GetSkill(obj, 96), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 249, false );
			NewSkillCoolTimeUI( obj, 96, true );
		}
		if(sq_getGrowType(obj) == 4)
		{

			sq_DrawSkillIcon (sq_GetSkill(obj, 244), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			sq_DrawSkillIcon (sq_GetSkill(obj, 98), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
			NewSkillCoolTimeUI( obj, 244, false );
			NewSkillCoolTimeUI( obj, 98, true );
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_THIEF)//??£º??
	{
		if(sq_getGrowType(obj) == 1)
		{
				sq_DrawSkillIcon (sq_GetSkill(obj, 222), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 57), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 222, false );
				NewSkillCoolTimeUI( obj, 57, true );
		}
		if(sq_getGrowType(obj) == 2)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 225), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 59), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 225, false );
				NewSkillCoolTimeUI( obj, 59, true );

		}
		if(sq_getGrowType(obj) == 3)
		{
				sq_DrawSkillIcon (sq_GetSkill(obj, 100), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 103), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 100, false );
				NewSkillCoolTimeUI( obj, 103, true );
		}
		if(sq_getGrowType(obj) == 4)
		{
				sq_DrawSkillIcon (sq_GetSkill(obj, 247), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 243), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 247, false );
				NewSkillCoolTimeUI( obj, 243, true );
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_AT_FIGHTER)//??£º???
	{
		if(sq_getGrowType(obj) == 1)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 222), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 67), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 222, false );
				NewSkillCoolTimeUI( obj, 67, true );
		}
		if(sq_getGrowType(obj) == 2)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 225), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));

				sq_DrawSkillIcon (sq_GetSkill(obj, 41), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 225, false );
				NewSkillCoolTimeUI( obj, 41, true );

		}
		if(sq_getGrowType(obj) == 3)
		{

				sq_DrawSkillIcon (sq_GetSkill(obj, 228), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 105), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 228, false );
				NewSkillCoolTimeUI( obj, 105, true );
		}
		if(sq_getGrowType(obj) == 4)
		{
				sq_DrawSkillIcon (sq_GetSkill(obj, 231), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 63), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 231, false );
				NewSkillCoolTimeUI( obj, 63, true );
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_AT_MAGE)//??£º??
	{
		
		local growType = sq_getGrowType(obj);
		 switch(growType)
		{
			case 0:
				sq_DrawSkillIcon (sq_GetSkill(obj, 124), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 126), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 124, false );
				NewSkillCoolTimeUI( obj,126 , true );
			break;
			case 1:
				sq_DrawSkillIcon (sq_GetSkill(obj, 245), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 49), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 245, false );
				NewSkillCoolTimeUI( obj, 49, true );
			break;
			case 2:
				sq_DrawSkillIcon (sq_GetSkill(obj, 248), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 48), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 248, false );
				NewSkillCoolTimeUI( obj, 48, true );
			break;
			case 3:
				sq_DrawSkillIcon (sq_GetSkill(obj, 95), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 103), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 95, false );
				NewSkillCoolTimeUI( obj, 103, true );
			break;
			case 4:
				sq_DrawSkillIcon (sq_GetSkill(obj, 121), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 109), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 121, false );
				NewSkillCoolTimeUI( obj, 109, true );
			break;
		}
		
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_AT_PRIEST)//??£º?ì¾
	{
		local growType = sq_getGrowType(obj);
		 switch(growType)
		{
			case 1:
				sq_DrawSkillIcon (sq_GetSkill(obj, 113), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 151), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 113, false );
				NewSkillCoolTimeUI( obj, 151, true );
			break;
			case 2:
				sq_DrawSkillIcon (sq_GetSkill(obj, 136), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 134), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 136, false );
				NewSkillCoolTimeUI( obj, 134, true );
			break;
			case 3:
				sq_DrawSkillIcon (sq_GetSkill(obj, 249), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 244), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 249, false );
				NewSkillCoolTimeUI( obj, 244, true );
			break;
			case 4:
				sq_DrawSkillIcon (sq_GetSkill(obj, 164), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 250), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 164, false );
				NewSkillCoolTimeUI( obj, 250, true );
			break;
		}
	}
	else if(sq_getJob(obj) == 10){
		
		local growType = sq_getGrowType(obj);
		 switch(growType)
		{
			case 0:
				sq_DrawSkillIcon (sq_GetSkill(obj, 234), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 246), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 234, false );
				NewSkillCoolTimeUI( obj, 246, true );
			break;
			case 1:
				sq_DrawSkillIcon (sq_GetSkill(obj, 141), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 142), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 141, false );
				NewSkillCoolTimeUI( obj, 142, true );
			break;
			case 2:
				sq_DrawSkillIcon (sq_GetSkill(obj, 226), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 221), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 226, false );
				NewSkillCoolTimeUI( obj, 221, true );
			break;
			case 3:
				sq_DrawSkillIcon (sq_GetSkill(obj, 166), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 160), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 166, false );
				NewSkillCoolTimeUI( obj, 160, true );
			break;
			case 4:
				sq_DrawSkillIcon (sq_GetSkill(obj, 81), x, y, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				sq_DrawSkillIcon (sq_GetSkill(obj, 74), xc, yc, sq_ALPHA(CFG_UI_NUTNEWSKILLICON_ALPHA));
				NewSkillCoolTimeUI( obj, 81, false );
				NewSkillCoolTimeUI( obj, 74, true );
			break;
		}
	}
	

		local Img_Alt = sq_var.GetAnimationMap("alt", "sqr/custom/ani/skillicon/alt.ani");
		sq_DrawSpecificFrame(Img_Alt, xc + 7, yc + 11, false, 0, false, 1.0);
		local Img_Ctrl = sq_var.GetAnimationMap("ctrl", "sqr/custom/ani/skillicon/ctrl.ani");
		sq_DrawSpecificFrame(Img_Ctrl, x + 7, y + 11, false, 0, false, 1.0);
	
}

function NewSkillCoolTimeUI ( obj, index, alt )
{
	if ( !obj ) 
		return;
	local sq_var = obj.getVar();
	//if (!sq_IsInBattle())
	//	return;
	local x = CFG_UI_NUTNEWSKILLCTRL_POS_X + 13;
	local y = CFG_UI_NUTNEWSKILLCTRL_POS_Y + 10;
	if(alt==true){
		x = CFG_UI_NUTNEWSKILLALT_POS_X + 13;
		y = CFG_UI_NUTNEWSKILLALT_POS_Y + 10;
		if(obj.getVar("newslotindex").getInt(0)!=index){
			obj.getVar("newslotindex").setInt(0,index);
		}
	}
	else{
		if(obj.getVar("newslotindex").getInt(1)!=index){
			obj.getVar("newslotindex").setInt(1,index);
		}
	}
	local newexskilllevel = sq_GetSkillLevel(obj, index);
	//if(!obj.sq_IsCommandEnable(index) || skilllevel<1){
	local allstate = obj.sq_GetState();
	if(allstate == 3 || allstate == 4 || allstate == 5 || allstate == 9 || newexskilllevel<1)
	{
		local disableim = sq_var.GetAnimationMap("disableimc", "sqr/custom/ani/skillicon/disable.ani");
		sq_DrawSpecificFrame(disableim, x - 13, y - 10, false, 0, false, 1.0);
		//sq_AnimationProc(disableim);
		//sq_drawCurrentFrame(disableim, 486, y-10, false);
		drawBlockSkillLevelNumberBySkill(obj,x + 11,y - 10,newexskilllevel);
	}
	else{
		drawSkillLevelNumberBySkill(obj,x + 11,y - 10,newexskilllevel);
	}
	return;
}

function drawSkillLevelNumberBySkill(obj, x, y, var) {
	if (!obj)
		return;
	local sq_var = obj.getVar();
	local sub = 0;
	if (var >= 0 && var < 10) {
		local yellowNum1 = getSkillLevelNumber(obj, var);
		sq_DrawSpecificFrame(yellowNum1, x - sub, y, false, 0, false, 1.0);
	} else if (var >= 10 && var < 20) {
		local yellowNum2 = getSkillLevelNumber(obj, var -10);
		local yellowNum1 = getSkillLevelNumber(obj, 1);
		sq_DrawSpecificFrame(yellowNum2, x - sub, y, false, 0, false, 1.0);
		sq_DrawSpecificFrame(yellowNum1, x - 4, y, false, 0, false, 1.0);
	} else if (var >= 20 && var < 30) {
		local yellowNum2 = getSkillLevelNumber(obj, var -20);
		local yellowNum1 = getSkillLevelNumber(obj, 2);
		sq_DrawSpecificFrame(yellowNum2, x - sub, y, false, 0, false, 1.0);
		sq_DrawSpecificFrame(yellowNum1, x - 4, y, false, 0, false, 1.0);
	}
	sub += 15;
	local ani = sq_var.GetAnimationMap("YLVIcon", "common/newstylecomboui/skill_number/lv.ani");
	sq_DrawSpecificFrame(ani, x - sub, y, false, 0, false, 1.0);
}

function drawBlockSkillLevelNumberBySkill(obj,x,y,var)
{
	if ( !obj )
		return;
	local sub = 0;
	local sq_var = obj.getVar();
	if (var >= 0&&var<10)
	{
		local yellowNum1 = getBlockSkillLevelNumber(obj,var);
		sq_DrawSpecificFrame(yellowNum1, x - sub, y, false, 0, false, 1.0);
	}
	else if (var >= 10&&var<20)
	{
            local yellowNum2 = getBlockSkillLevelNumber(obj,var - 10);
            local yellowNum1 = getBlockSkillLevelNumber(obj,1);
            sq_DrawSpecificFrame(yellowNum1, x - sub, y, false, 0, false, 1.0);
            sq_DrawSpecificFrame(yellowNum2, x - 4, y, false, 0, false, 1.0);
	}
	else if(var >= 20&&var<30){
            local yellowNum2 = getBlockSkillLevelNumber(obj,var - 20);
            local yellowNum1 = getBlockSkillLevelNumber(obj,2);
            sq_DrawSpecificFrame(yellowNum1, x - sub, y, false, 0, false, 1.0);
            sq_DrawSpecificFrame(yellowNum2, x - 4, y, false, 0, false, 1.0);
	}
	sub += 15;

	local ani = sq_var.GetAnimationMap("BLVIcon","common/newstylecomboui/skill_number/block/lv.ani");
	sq_DrawSpecificFrame(ani, x - sub, y, false, 0, false, 1.0);
}

function getBlockSkillLevelNumber(obj,id)
{
    if(!obj) return;
    local sq_var = obj.getVar();
    local ani = null;
    if (id == 0)
        ani = sq_var.GetAnimationMap("B1Icon","common/newstylecomboui/skill_number/block/0.ani");
    else if (id == 1)
        ani = sq_var.GetAnimationMap("B1Icon","common/newstylecomboui/skill_number/block/1.ani");
    else if (id == 2)
        ani = sq_var.GetAnimationMap("B1Icon","common/newstylecomboui/skill_number/block/2.ani");
    else if (id == 3)
        ani = sq_var.GetAnimationMap("B1Icon","common/newstylecomboui/skill_number/block/3.ani");
    else if (id == 4)
        ani = sq_var.GetAnimationMap("B1Icon","common/newstylecomboui/skill_number/block/4.ani");
    else if (id == 5)
        ani = sq_var.GetAnimationMap("B1Icon","common/newstylecomboui/skill_number/block/5.ani");
    else if (id == 6)
        ani = sq_var.GetAnimationMap("B1Icon","common/newstylecomboui/skill_number/block/6.ani");
    else if (id == 7)
        ani = sq_var.GetAnimationMap("B1Icon","common/newstylecomboui/skill_number/block/7.ani");
    else if (id == 8)
        ani = sq_var.GetAnimationMap("B1Icon","common/newstylecomboui/skill_number/block/8.ani");
    else if (id == 9)
        ani = sq_var.GetAnimationMap("B1Icon","common/newstylecomboui/skill_number/block/9.ani");
    return ani;


}

function getSkillLevelNumber(obj,id)
{
    if(!obj) return;
    local sq_var = obj.getVar();
    local ani = null;
    if (id == 0)
        ani = sq_var.GetAnimationMap("Y0Icon","common/newstylecomboui/skill_number/0.ani");
    else if (id == 1)
        ani = sq_var.GetAnimationMap("Y1Icon","common/newstylecomboui/skill_number/1.ani");
    else if (id == 2)
        ani = sq_var.GetAnimationMap("Y2Icon","common/newstylecomboui/skill_number/2.ani");
    else if (id == 3)
        ani = sq_var.GetAnimationMap("Y3Icon","common/newstylecomboui/skill_number/3.ani");
    else if (id == 4)
        ani = sq_var.GetAnimationMap("Y4Icon","common/newstylecomboui/skill_number/4.ani");
    else if (id == 5)
        ani = sq_var.GetAnimationMap("Y5Icon","common/newstylecomboui/skill_number/5.ani");
    else if (id == 6)
        ani = sq_var.GetAnimationMap("Y6Icon","common/newstylecomboui/skill_number/6.ani");
    else if (id == 7)
        ani = sq_var.GetAnimationMap("Y7Icon","common/newstylecomboui/skill_number/7.ani");
    else if (id == 8)
        ani = sq_var.GetAnimationMap("Y8Icon","common/newstylecomboui/skill_number/8.ani");
    else if (id == 9)
        ani = sq_var.GetAnimationMap("Y9Icon","common/newstylecomboui/skill_number/9.ani");
    return ani;

}
