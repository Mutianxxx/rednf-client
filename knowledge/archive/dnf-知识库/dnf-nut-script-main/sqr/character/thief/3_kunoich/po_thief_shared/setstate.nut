



function setState_po_thief_shared(obj, state, datas)
{
	if(!obj) return;

	local id = obj.getVar("id").get_vector(0);
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	local parentChr = sq_ObjectToSQRCharacter(obj.getTopCharacter());



	switch(id)
	{
		case 9://???? ?? ju???
			switch(state)
			{
				case 10://???? ?? ju??? ???
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(7);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 3);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FLAMETORNADO, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local skill_level = sq_GetSkillLevel(parentChr, SKILL_FLAMETORNADO);
					local act_rate = sq_GetLevelData(parentChr, SKILL_FLAMETORNADO, 2, skill_level);
					local act_level = sq_GetLevelData(parentChr, SKILL_FLAMETORNADO, 3, skill_level);
					local act_time = sq_GetLevelData(parentChr, SKILL_FLAMETORNADO, 4, skill_level);
					local act_damage = parentChr.sq_GetPowerWithPassive(SKILL_FLAMETORNADO, -1, 5, -1, 1.0);
					sq_SetChangeStatusIntoAttackInfo(pAttack, 0, ACTIVESTATUS_BURN, act_rate, act_level, act_time, act_damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FLAMETORNADO, 1);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local attackTerm = sq_GetIntData(parentChr, SKILL_FLAMETORNADO, 0);
					obj.setTimeEvent(0, attackTerm, 0, false);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), 400);
					obj.getVar("flametornadoMove").clear_vector();
					obj.getVar("flametornadoMove").push_vector(xDistance);

					local objectManager = obj.getObjectManager();
					for(local i = 0; i < objectManager.getCollisionObjectNumber(); ++ i)
					{
						local object = objectManager.getCollisionObject(i);
						if(object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE))
						{
							local mobXPos = sq_GetXPos(object);
							local mobYPos = sq_GetYPos(object);
							obj.getVar("flametornadoAttract").clear_vector();
							obj.getVar("flametornadoAttract").push_vector(mobXPos);
							obj.getVar("flametornadoAttract").push_vector(mobYPos);
						}
					}
				break;
				case 11://???? ?? ju??? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(8);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 3);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FLAMETORNADO, -1, 1, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local skill_level = sq_GetSkillLevel(parentChr, SKILL_FLAMETORNADO);
					local act_rate = sq_GetLevelData(parentChr, SKILL_FLAMETORNADO, 2, skill_level);
					local act_level = sq_GetLevelData(parentChr, SKILL_FLAMETORNADO, 3, skill_level);
					local act_time = sq_GetLevelData(parentChr, SKILL_FLAMETORNADO, 4, skill_level);
					local act_damage = parentChr.sq_GetPowerWithPassive(SKILL_FLAMETORNADO, -1, 5, -1, 1.0);
					sq_SetChangeStatusIntoAttackInfo(pAttack, 0, ACTIVESTATUS_BURN, act_rate, act_level, act_time, act_damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FLAMETORNADO, 1);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
					sq_SetMyShake(obj, 5, 300);
				break;
			}
		break;
		case 12://???? ?? ???????? ???
			switch(state)
			{
				case 10://???? ?? ???????? ??? ???
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(11);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 3);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_BIGKUNAI, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), 3000);
					obj.getVar("bigkunaiMove").clear_vector();
					obj.getVar("bigkunaiMove").push_vector(xDistance);
					obj.sq_PlaySound("NSKUNAI_THROW");
				break;
				case 11://???? ?? ???????? ??? ???
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(12);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 3);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_BIGKUNAI, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local attackTerm = sq_GetIntData(parentChr, SKILL_BIGKUNAI, 0);
					obj.setTimeEvent(0, attackTerm, 0, false);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), 300);
					obj.getVar("bigkunaiMove").clear_vector();
					obj.getVar("bigkunaiMove").push_vector(xDistance);
					sq_SetMyShake(obj, 3, 1920);
					obj.sq_PlaySound("NSKUNAI_SPIN");
				break;
				case 12://???? ?? ???????? ??? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(12);

					local ani = obj.getCustomAnimation(13);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 3);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_BIGKUNAI, -1, 1, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_BIGKUNAI, 1);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
					sq_SetMyShake(obj, 5, 300);
					obj.sq_PlaySound("NSKUNAI_EXP");
				break;
			}
		break;
		case 13://???? ?? ???????? ????
			switch(state)
			{
				case 10://???? ?? ???????? ???? ???
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(14);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 3);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_BIGKUNAI, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local zDistance = 0;
					obj.getVar("bigkunaiMove").clear_vector();
					obj.getVar("bigkunaiMove").push_vector(zDistance);
				break;
				case 11://???? ?? ???????? ???? ???
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(15);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 3);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_BIGKUNAI, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local attackTerm = sq_GetIntData(parentChr, SKILL_BIGKUNAI, 0);
					obj.setTimeEvent(0, attackTerm, 0, false);
					sq_SetMyShake(obj, 3, 1920);
					obj.sq_PlaySound("NSKUNAI_SPIN");
				break;
				case 12://???? ?? ???????? ???? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(12);

					local ani = obj.getCustomAnimation(16);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 3);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_BIGKUNAI, -1, 1, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_BIGKUNAI, 1);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
					sq_SetMyShake(obj, 5, 300);
					obj.sq_PlaySound("NSKUNAI_EXP");
				break;
			}
		break;
		case 14://???? : ?????? ?????
			switch(state)
			{
				case 10://???? : ?????? ????? ???
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
					local ani = obj.getCustomAnimation(17);
					obj.setCurrentAnimation(ani);
				break;
				case 11://???? : ?????? ????? ???
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
					local ani = obj.getCustomAnimation(18);
					obj.setCurrentAnimation(ani);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), -200);
					local zDistance = 100;
					obj.getVar("migawariMove").clear_vector();
					obj.getVar("migawariMove").push_vector(xDistance);
					obj.getVar("migawariMove").push_vector(zDistance);
					sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
				break;
			}
			local pAni = obj.getCurrentAnimation();
			pAni.setRGBA(255, 255, 255, 0);
		break;
		case 25://???? ?? ??chu??????
			switch(state)
			{
				case 10://???? ?? ??chu?????? ??chu????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(29);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 10);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_GASOLINEFIRE, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);
				break;
				case 11://???? ?? ??chu?????? ??chu???
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(30);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 12);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_GASOLINEFIRE, -1, 2, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_GASOLINEFIRE, 1);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local skill_level = sq_GetSkillLevel(parentChr, SKILL_GASOLINEFIRE);
					local act_rate = sq_GetLevelData(parentChr, SKILL_GASOLINEFIRE, 3, skill_level);
					local act_level = sq_GetLevelData(parentChr, SKILL_GASOLINEFIRE, 4, skill_level);
					local act_time = sq_GetLevelData(parentChr, SKILL_GASOLINEFIRE, 5, skill_level);
					local act_damage = parentChr.sq_GetPowerWithPassive(SKILL_GASOLINEFIRE, -1, 6, -1, 1.0);
					sq_SetChangeStatusIntoAttackInfo(pAttack, 0, ACTIVESTATUS_BURN, act_rate, act_level, act_time, act_damage);
					sq_SetMyShake(obj, 8, 300);
					obj.sq_PlaySound("GASOLINEFIRE_BALL_EXP");
				break;
			}
		break;
		case 32://???? ?? ????????? ????????
			switch(state)
			{
				case 10://???? ?? ????????? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(37);
					obj.setCurrentAnimation(ani);
				break;
				case 11://???? ?? ????????? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(38);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 17);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 1, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
					local sizeRate = sq_GetLevelData(parentChr, SKILL_DOOMFIELD, 6, skill_level);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
					sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
					sq_SetMyShake(obj, 8, 300);
				break;
			}
		break;
		case 33://???? ?? ????????? ???????????1
			switch(state)
			{
				case 10://???? ?? ????????? ???1
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(39);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 19);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 3, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
					local sizeRate = sq_GetLevelData(parentChr, SKILL_DOOMFIELD, 7, skill_level);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
					sq_SetMyShake(obj, 8, 300);
				break;
				case 11://???? ?? ????????? ???????1
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(45);
					obj.setCurrentAnimation(ani);
					obj.sq_PlaySound("R_NINPOJIN_EXP");

					local attackInfo = sq_GetCustomAttackInfo(obj, 20);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 4, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
					local sizeRate = sq_GetLevelData(parentChr, SKILL_DOOMFIELD, 7, skill_level);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
					sq_SetMyShake(obj, 10, 300);
					sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
				break;
			}
		break;
		case 34://???? ?? ????????? ???????????2
			switch(state)
			{
				case 10://???? ?? ????????? ???2
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(40);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 19);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 3, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
					local sizeRate = sq_GetLevelData(parentChr, SKILL_DOOMFIELD, 7, skill_level);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
					sq_SetMyShake(obj, 8, 300);
				break;
				case 11://???? ?? ????????? ???????2
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(45);
					obj.setCurrentAnimation(ani);
					obj.sq_PlaySound("R_NINPOJIN_EXP");

					local attackInfo = sq_GetCustomAttackInfo(obj, 20);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 4, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
					local sizeRate = sq_GetLevelData(parentChr, SKILL_DOOMFIELD, 7, skill_level);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
					sq_SetMyShake(obj, 10, 300);
					sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
				break;
			}
		break;
		case 35://???? ?? ????????? ???????????3
			switch(state)
			{
				case 10://???? ?? ????????? ???3
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(41);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 19);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 3, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
					local sizeRate = sq_GetLevelData(parentChr, SKILL_DOOMFIELD, 7, skill_level);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
					sq_SetMyShake(obj, 8, 300);
				break;
				case 11://???? ?? ????????? ???????3
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(45);
					obj.setCurrentAnimation(ani);
					obj.sq_PlaySound("R_NINPOJIN_EXP");

					local attackInfo = sq_GetCustomAttackInfo(obj, 20);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 4, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
					local sizeRate = sq_GetLevelData(parentChr, SKILL_DOOMFIELD, 7, skill_level);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
					sq_SetMyShake(obj, 10, 300);
					sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
				break;
			}
		break;
		case 36://???? ?? ????????? ???????????4
			switch(state)
			{
				case 10://???? ?? ????????? ???4
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(42);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 19);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 3, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
					local sizeRate = sq_GetLevelData(parentChr, SKILL_DOOMFIELD, 7, skill_level);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
				break;
				case 11://???? ?? ????????? ???????4
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(45);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 20);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 4, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
					local sizeRate = sq_GetLevelData(parentChr, SKILL_DOOMFIELD, 7, skill_level);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
				break;
			}
		break;
		case 37://???? ?? ????????? ???????????5
			switch(state)
			{
				case 10://???? ?? ????????? ???5
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(43);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 19);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 3, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
					local sizeRate = sq_GetLevelData(parentChr, SKILL_DOOMFIELD, 7, skill_level);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
				break;
				case 11://???? ?? ????????? ???????5
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(45);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 20);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 4, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
					local sizeRate = sq_GetLevelData(parentChr, SKILL_DOOMFIELD, 7, skill_level);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
				break;
			}
		break;
		case 38://???? ?? ????????? ???????????6
			switch(state)
			{
				case 10://???? ?? ????????? ???6
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(44);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 19);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 3, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
					local sizeRate = sq_GetLevelData(parentChr, SKILL_DOOMFIELD, 7, skill_level);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
					sq_SetMyShake(obj, 8, 300);
				break;
				case 11://???? ?? ????????? ???????6
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(45);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 20);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 4, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
					local sizeRate = sq_GetLevelData(parentChr, SKILL_DOOMFIELD, 7, skill_level);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
				break;
			}
		break;
		case 46://????????
			switch(state)
			{
				case 10://???????? ???
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(52);
					obj.setCurrentAnimation(ani);
					sq_SetMyShake(obj, 5, 300);
					sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
				break;
				case 11://???????? ????????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(53);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 25);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_YAMATAOROCHI, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local skill_level = sq_GetSkillLevel(parentChr, SKILL_YAMATAOROCHI);
					local act_rate = sq_GetLevelData(parentChr, SKILL_YAMATAOROCHI, 2, skill_level);
					local act_level = sq_GetLevelData(parentChr, SKILL_YAMATAOROCHI, 3, skill_level);
					local act_time = sq_GetLevelData(parentChr, SKILL_YAMATAOROCHI, 4, skill_level);
					local act_damage = parentChr.sq_GetPowerWithPassive(SKILL_YAMATAOROCHI, -1, 5, -1, 1.0);
					sq_SetChangeStatusIntoAttackInfo(pAttack, 0, ACTIVESTATUS_BURN, act_rate, act_level, act_time, act_damage, 2000, 1, act_damage);

					local term = sq_GetIntData(parentChr, SKILL_YAMATAOROCHI, 0);
					obj.setTimeEvent(0, term, 0, false);
				break;
				case 12://???????? ???
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(12);

					local ani = obj.getCustomAnimation(54);
					obj.setCurrentAnimation(ani);
				break;
			}
		break;
		case 47://???????? ???
			switch(state)
			{
				case 10://???????? ??? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(55);
					obj.setCurrentAnimation(ani);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_YAMATAOROCHI, 2);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
				break;
				case 11://???????? ??? ???
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(56);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 26);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_YAMATAOROCHI, -1, 1, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local skill_level = sq_GetSkillLevel(parentChr, SKILL_YAMATAOROCHI);
					local act_rate = sq_GetLevelData(parentChr, SKILL_YAMATAOROCHI, 6, skill_level);
					local act_level = sq_GetLevelData(parentChr, SKILL_YAMATAOROCHI, 7, skill_level);
					local act_time = sq_GetLevelData(parentChr, SKILL_YAMATAOROCHI, 8, skill_level);
					local act_damage = parentChr.sq_GetPowerWithPassive(SKILL_YAMATAOROCHI, -1, 9, -1, 1.0);
					sq_SetChangeStatusIntoAttackInfo(pAttack, 0, ACTIVESTATUS_POISON, act_rate, act_level, act_time, act_damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_YAMATAOROCHI, 2);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local term = sq_GetIntData(parentChr, SKILL_YAMATAOROCHI, 1);
					obj.setTimeEvent(0, term, 0, false);
				break;
				case 12://???????? ??? ???
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(12);

					local ani = obj.getCustomAnimation(57);
					obj.setCurrentAnimation(ani);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_YAMATAOROCHI, 2);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
				break;
			}
		break;
		case 50://???? ?? ???????? ?
			switch(state)
			{
				case 10://???? ?? ???????? ? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(60);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 27);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 2);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local hitCount = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 0);
					obj.setTimeEvent(0, 720 / hitCount, 0, true);
					obj.sq_SetMaxHitCounterPerObject(hitCount);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), 280);
					local yDistance = sq_GetDistancePos(y, obj.getDirection(), 100);
					obj.getVar("smallSurikenMove").clear_vector();
					obj.getVar("smallSurikenMove").push_vector(xDistance);
					obj.getVar("smallSurikenMove").push_vector(yDistance);
				break;
				case 11://???? ?? ???????? ? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(61);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 27);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 2);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), -330);
					local yDistance = sq_GetDistancePos(y, obj.getDirection(), -80);
					obj.getVar("smallSurikenMove").clear_vector();
					obj.getVar("smallSurikenMove").push_vector(xDistance);
					obj.getVar("smallSurikenMove").push_vector(yDistance);
				break;
			}
		break;
		case 51://???? ?? ???????? ?
			switch(state)
			{
				case 10://???? ?? ???????? ? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(60);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 27);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 2);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local hitCount = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 0);
					obj.setTimeEvent(0, 720 / hitCount, 0, true);
					obj.sq_SetMaxHitCounterPerObject(hitCount);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), 320);
					local yDistance = sq_GetDistancePos(y, obj.getDirection(), 50);
					obj.getVar("smallSurikenMove").clear_vector();
					obj.getVar("smallSurikenMove").push_vector(xDistance);
					obj.getVar("smallSurikenMove").push_vector(yDistance);
				break;
				case 11://???? ?? ???????? ? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(61);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 27);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 2);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), -370);
					local yDistance = sq_GetDistancePos(y, obj.getDirection(), -30);
					obj.getVar("smallSurikenMove").clear_vector();
					obj.getVar("smallSurikenMove").push_vector(xDistance);
					obj.getVar("smallSurikenMove").push_vector(yDistance);
				break;
			}
		break;
		case 52://???? ?? ???????? ?
			switch(state)
			{
				case 10://???? ?? ???????? ? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(60);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 27);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 2);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local hitCount = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 0);
					obj.setTimeEvent(0, 720 / hitCount, 0, true);
					obj.sq_SetMaxHitCounterPerObject(hitCount);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), 380);
					local yDistance = sq_GetDistancePos(y, obj.getDirection(), 0);
					obj.getVar("smallSurikenMove").clear_vector();
					obj.getVar("smallSurikenMove").push_vector(xDistance);
					obj.getVar("smallSurikenMove").push_vector(yDistance);
				break;
				case 11://???? ?? ???????? ? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(61);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 27);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 2);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), -430);
					local yDistance = sq_GetDistancePos(y, obj.getDirection(), -0);
					obj.getVar("smallSurikenMove").clear_vector();
					obj.getVar("smallSurikenMove").push_vector(xDistance);
					obj.getVar("smallSurikenMove").push_vector(yDistance);
				break;
			}
		break;
		case 53://???? ?? ???????? ?
			switch(state)
			{
				case 10://???? ?? ???????? ? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(60);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 27);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 2);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local hitCount = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 0);
					obj.setTimeEvent(0, 720 / hitCount, 0, true);
					obj.sq_SetMaxHitCounterPerObject(hitCount);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), 280);
					local yDistance = sq_GetDistancePos(y, obj.getDirection(), -50);
					obj.getVar("smallSurikenMove").clear_vector();
					obj.getVar("smallSurikenMove").push_vector(xDistance);
					obj.getVar("smallSurikenMove").push_vector(yDistance);
				break;
				case 11://???? ?? ???????? ? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(61);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 27);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 2);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), -330);
					local yDistance = sq_GetDistancePos(y, obj.getDirection(), 30);
					obj.getVar("smallSurikenMove").clear_vector();
					obj.getVar("smallSurikenMove").push_vector(xDistance);
					obj.getVar("smallSurikenMove").push_vector(yDistance);
				break;
			}
		break;
		case 54://???? ?? ???????? ??
			switch(state)
			{
				case 10://???? ?? ???????? ?? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(62);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 28);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 1, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 3);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local hitCount = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 1);
					obj.setTimeEvent(0, 600 / hitCount, 0, true);
					obj.sq_SetMaxHitCounterPerObject(hitCount);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), 200);
					obj.getVar("bigSurikenMove").clear_vector();
					obj.getVar("bigSurikenMove").push_vector(xDistance);
				break;
				case 11://???? ?? ???????? ?? ???1
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(63);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 28);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 1, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 3);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), -50);
					local yDistance = sq_GetDistancePos(y, obj.getDirection(), -50);
					obj.getVar("bigSurikenMove").clear_vector();
					obj.getVar("bigSurikenMove").push_vector(xDistance);
					obj.getVar("bigSurikenMove").push_vector(yDistance);
				break;
				case 12://???? ?? ???????? ?? ???2
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(12);

					local ani = obj.getCustomAnimation(64);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 28);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 1, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 3);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), -100);
					local yDistance = sq_GetDistancePos(y, obj.getDirection(), 50);
					obj.getVar("bigSurikenMove").clear_vector();
					obj.getVar("bigSurikenMove").push_vector(xDistance);
					obj.getVar("bigSurikenMove").push_vector(yDistance);
				break;
				case 13://???? ?? ???????? ?? ???3
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(13);

					local ani = obj.getCustomAnimation(65);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 28);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 1, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 3);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), 50);
					local yDistance = sq_GetDistancePos(y, obj.getDirection(), 100);
					obj.getVar("bigSurikenMove").clear_vector();
					obj.getVar("bigSurikenMove").push_vector(xDistance);
					obj.getVar("bigSurikenMove").push_vector(yDistance);
				break;
				case 14://???? ?? ???????? ?? ???4
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(14);

					local ani = obj.getCustomAnimation(66);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 28);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 1, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 3);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), 100);
					local yDistance = sq_GetDistancePos(y, obj.getDirection(), -100);
					obj.getVar("bigSurikenMove").clear_vector();
					obj.getVar("bigSurikenMove").push_vector(xDistance);
					obj.getVar("bigSurikenMove").push_vector(yDistance);
				break;
			}
		break;
		case 59://???
			switch(state)
			{
				case 10://??? ????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(71);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 30);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_AMATERAS, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);
				break;
				case 11://??? ???
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(72);
					obj.setCurrentAnimation(ani);

					local delay = ani.getDelaySum(false);
					local explosionCount = sq_GetIntData(parentChr, SKILL_AMATERAS, 0);
					obj.setTimeEvent(2, delay / explosionCount, explosionCount, false);
				break;
				case 12://??? ???
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(12);

					local ani = obj.getCustomAnimation(73);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 30);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_AMATERAS, -1, 2, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);
				break;
			}
		break;
		case 71://???? : ?????? ??????????????
			switch(state)
			{
				case 10://???? : ?????? ????? ???????????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
					local ani = obj.getCustomAnimation(17);
					obj.setCurrentAnimation(ani);
				break;
				case 11://???? : ?????? ????? ???????????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
					local ani = obj.getCustomAnimation(18);
					obj.setCurrentAnimation(ani);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), -200);
					local zDistance = 100;
					obj.getVar("migawariMove").clear_vector();
					obj.getVar("migawariMove").push_vector(xDistance);
					obj.getVar("migawariMove").push_vector(zDistance);
					sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
				break;
			}
		break;
		case 75://???? ?? ??chu???????????????
			switch(state)
			{
				case 10://???? ?? ??chu?????? ??chu????????????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(29);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 10);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_GASOLINEFIRE, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);
				break;
				case 11://???? ?? ??chu?????? ??chu????????????
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(30);
					obj.setCurrentAnimation(ani);

					local attackInfo = sq_GetCustomAttackInfo(obj, 12);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_GASOLINEFIRE, -1, 2, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_GASOLINEFIRE, 1);
					sizeRate = sizeRate.tofloat() / 100.0;
					ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
					ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
					sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

					local skill_level = sq_GetSkillLevel(parentChr, SKILL_GASOLINEFIRE);
					local act_rate = sq_GetLevelData(parentChr, SKILL_GASOLINEFIRE, 3, skill_level);
					local act_level = sq_GetLevelData(parentChr, SKILL_GASOLINEFIRE, 4, skill_level);
					local act_time = sq_GetLevelData(parentChr, SKILL_GASOLINEFIRE, 5, skill_level);
					local act_damage = parentChr.sq_GetPowerWithPassive(SKILL_GASOLINEFIRE, -1, 6, -1, 1.0);
					sq_SetChangeStatusIntoAttackInfo(pAttack, 0, ACTIVESTATUS_BURN, act_rate, act_level, act_time, act_damage);
					sq_SetMyShake(obj, 8, 300);
					obj.sq_PlaySound("GASOLINEFIRE_BALL_EXP");
				break;
			}
		break;
	}
}



