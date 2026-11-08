function onProc_thunderstrikenew(obj)
{
	if(!obj) return;
	if(sq_GetSkillLevel(obj, 167)>0){
		if((!CNSquirrelAppendage.sq_IsAppendAppendage ( obj, "character/mage/appendage/ap_thunderstrike.nut" ))&&obj.getCurrentSkillIndex()==55) {
			CNSquirrelAppendage.sq_AppendAppendage ( obj, obj, 55, false, "character/mage/appendage/ap_thunderstrike.nut", true );
		}
	}
};

function onAfterSetState_thunderstrikenew(obj, state, datas, isResetTimer)
{
	local skillIndex = obj.getThrowIndex();
	switch(skillIndex)
	{
		case 94:
			if(obj.getThrowState() == 1 && obj.sq_GetSkillLevel(94) > 0){
				createFavoriteBuffEffect(obj, state, datas, isResetTimer);
				if (!isDollState(obj) )
				{
					obj.sq_SetCurrentAnimation(CUSTOM_FAVORITE_AFTER);
				}
				else
				{
					local ani = obj.getVar().GetAnimationMap("FavoriteCasting", "character/mage/animation/zrr_ani/favoritismcastingafter_mad_body.ani"); 
					obj.setCurrentAnimation(ani);
				}
			}
			break;
		case 170:
			if(obj.getThrowState() == 0 && obj.sq_GetSkillLevel(170) > 0){
				obj.sq_PlaySound("WZ_MASSTELEPORT");
			}
			break;
		case 15:
			break;
		default:
			local zPos = obj.getZPos(); 
			if(zPos > 40)
			{
				obj.sq_ZStop();
				obj.sq_SetCurrentAnimation(CUSTOM_ANI_JUMP_THROW);
				obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
			}
			break;
	}
	if(obj.sq_GetVectorData(datas, 0)!=1)
	{
		obj.getVar("skillindexu").clear_vector();
		obj.getVar("skillindexu").push_vector(obj.sq_GetVectorData(datas, 2));
	}
	obj.getVar("throwdata").clear_vector();
	obj.getVar("throwdata").push_vector(obj.sq_GetVectorData(datas, 0));
	obj.getVar("throwdata").push_vector(obj.sq_GetVectorData(datas, 1));
	obj.getVar("throwdata").push_vector(obj.sq_GetVectorData(datas, 2));
	obj.getVar("throwdata").push_vector(obj.sq_GetVectorData(datas, 3));
	obj.getVar("throwdata").push_vector(obj.sq_GetVectorData(datas, 4));
	obj.getVar("throwdata").push_vector(obj.sq_GetVectorData(datas, 5));
	obj.getVar("throwdata").push_vector(obj.sq_GetVectorData(datas, 6));
	obj.getVar("throwdata").push_vector(obj.sq_GetVectorData(datas, 7));
};


function onEndCurrentAni_thunderstrikenew(obj)
{
	if(!obj) return;
	if(obj.sq_IsMyControlObject() && obj.getVar("throwdata").get_vector(0)==1)
	{
		local skillIndex = obj.getCurrentSkillIndex();
		if(skillIndex<1)
		{
			skillIndex = obj.getVar("skillindexu").get_vector(0);
		}
		switch(skillIndex)
		{
			case 59:
				if(!isElementalPotential(obj)){
					return;
				}
				local x = obj.getXPos();
				local y = obj.getYPos();
				
				if (obj.getDirection() == ENUM_DIRECTION_RIGHT) {
					x = x + 300;
				} 
				else 
				{
					x = x - 300;
				}
				local chargetime = obj.getVar("throwdata").get_vector(1);
				createIceField(obj, x, y, chargetime );
				obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true); 
			break;
			case 148:
				local x = obj.getXPos();
				local y = obj.getYPos()+1;
				if (obj.getDirection() == ENUM_DIRECTION_RIGHT) {
					x = x + 100;
				} 
				else 
				{
					x = x - 100;
				}
				obj.sq_PlaySound("WZ_DARKMOON");
				local skillLevel = obj.sq_GetSkillLevel(148);
				if(obj.getThrowState() == 1 && skillLevel > 0){
					local time = sq_GetLevelData(obj, 148, 0, skillLevel);
					local hp = sq_GetLevelData(obj, 148, 1, skillLevel);
					local atkBonus = obj.sq_GetBonusRateWithPassive(148, 13, 3, 1.0);
					local blind_prob = sq_GetLevelData(obj, 148, 5, skillLevel);
					local blind_level = sq_GetLevelData(obj, 148, 4, skillLevel);
					local blind_time = sq_GetLevelData(obj, 148, 6, skillLevel);
					local blind_stuck = obj.sq_GetIntData(148, 1);
					local size = obj.sq_GetIntData(148, 0);

					local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 148, false, "character/mage/darkmoon/ap_darkmoon.nut", true);	
					masterAppendage.getVar("hpMax").clear_vector();
					masterAppendage.getVar("hpMax").push_vector(hp);
					masterAppendage.sq_SetValidTime(time);
					masterAppendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), 148, skillLevel);
					CNSquirrelAppendage.sq_AppendAppendageID(masterAppendage, obj, obj, 148, true);
					masterAppendage.setEnableIsBuff(true);
					
					sq_BinaryStartWrite();
					sq_BinaryWriteDword(atkBonus);
					sq_BinaryWriteDword(size);
					sq_BinaryWriteDword(blind_prob);
					sq_BinaryWriteDword(blind_level);
					sq_BinaryWriteDword(blind_time);
					sq_BinaryWriteDword(blind_stuck);
					sq_SendCreatePassiveObjectPacketPos(obj, 24354, 0, x, y, 170);
				}
			break;
		}
	}
	
}

function createIceField(obj, x, y, timer) {
	if (!obj)
		return;
	if (!obj.isMyControlObject())
		return;
	obj.sq_StartWrite();
	obj.sq_WriteDword(1);
	sq_SendCreatePassiveObjectPacketPos(obj, 23027, 0, x, y, 0);
	local chargetimer = timer - 350;
	if (chargetimer < 1) {
		chargetimer = 1;
	}
	local mageshowpre = 1;
	local mageshow_level;
	if (isShowTime(obj)) {
		mageshow_level = sq_GetSkillLevel(obj, 2);
		mageshowpre = 1 - sq_GetLevelData(obj, 2, 3, mageshow_level).tofloat() / 1000;
		if (mageshowpre < 0) {
			mageshowpre = 0;
		}
	}
	local chargepre = 1 - (800 * mageshowpre + 1) / chargetimer;
	if (chargepre < 0) {
		chargepre = 0;
	}
	local level = sq_GetSkillLevel(obj, 59);
	local iceAreaSizeLow = sq_GetLevelData(obj, 59, 2, level);
	local iceAreaSize = sq_GetLevelData(obj, 59, 3, level);
	local iceAreaRate = (iceAreaSize - iceAreaSizeLow) * chargepre * 0.0023 + iceAreaSizeLow * 0.0023;
	local lifeTime = (chargepre * 1000).tointeger();
	local iceRainCount = sq_GetIntData(obj, 59, 5, level);
	local iceRate = sq_GetLevelData(obj, 59, 5, level);
	local iceLevel = sq_GetLevelData(obj, 59, 6, level);
	local iceTime = sq_GetLevelData(obj, 59, 7, level);

	sq_BinaryStartWrite();
	sq_BinaryWriteFloat(iceAreaRate);
	sq_BinaryWriteDword(lifeTime);
	sq_BinaryWriteDword(iceRainCount);
	sq_BinaryWriteDword(iceRate);
	sq_BinaryWriteDword(iceLevel);
	sq_BinaryWriteDword(iceTime);
	obj.sq_SendCreatePassiveObjectPacket(24382, 0, 300, 1, 0);
}