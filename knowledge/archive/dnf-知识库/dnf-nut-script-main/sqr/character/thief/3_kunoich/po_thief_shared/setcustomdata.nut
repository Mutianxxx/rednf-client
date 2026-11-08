



function setCustomData_po_thief_shared(obj, receiveData)
{
	if(!obj) return;

	local id = receiveData.readDword();
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	obj.getVar("id").clear_vector();
	obj.getVar("id").push_vector(id);
	local parentChr = sq_ObjectToSQRCharacter(obj.getTopCharacter());
	local pAni = obj.getCurrentAnimation();



	switch(id)
	{
		case 0://???????? ???????
			local ani = obj.getCustomAnimation(0);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 0);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(174, -1, 0, 0.1);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local distance = sq_GetIntData(parentChr, SKILL_EQUIPCHAKRAWEAPON, 0);
			local xDistance = sq_GetDistancePos(x, obj.getDirection(), distance);
			obj.getVar("chakraMove").clear_vector();
			obj.getVar("chakraMove").push_vector(x);
			obj.getVar("chakraMove").push_vector(xDistance);
		break;
		case 1://???????? ?????
			local ani = obj.getCustomAnimation(0);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 0);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(174, -1, 0, 0.1);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			obj.sq_SetMoveParticle("Particle/chakraweapon.ptl", 0.0, -45.0);
			obj.setCustomRotate(true, sq_ToRadian(-45.0));
		break;
		case 2://???? ?? ????????? ????? ???
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(1);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);

			local attackTerm = sq_GetIntData(parentChr, SKILL_FLAMEBALL, 0);
			obj.setTimeEvent(0, attackTerm, 0, false);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_FLAMEBALL, 1);
			sizeRate = sizeRate.tofloat() / 100.0;
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
		break;
		case 3://???? ?? ????????? ????
			local ani = obj.getCustomAnimation(2);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 1);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FLAMEBALL, -1, 1, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local skill_level = sq_GetSkillLevel(parentChr, SKILL_FLAMEBALL);
			local act_rate = sq_GetLevelData(parentChr, SKILL_FLAMEBALL, 2, skill_level);
			local act_level = sq_GetLevelData(parentChr, SKILL_FLAMEBALL, 3, skill_level);
			local act_time = sq_GetLevelData(parentChr, SKILL_FLAMEBALL, 4, skill_level);
			local act_damage = sq_GetLevelData(parentChr, SKILL_FLAMEBALL, 5, skill_level);
			sq_SetChangeStatusIntoAttackInfo(pAttack, 0, ACTIVESTATUS_BURN, act_rate, act_level, act_time, act_damage);
		break;
		case 4://?????????????? ????? ???
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(3);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);
		break;
		case 5://?????????????? ????? ????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(4);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);
		break;
		case 6://?????????????? ???
			local ani = obj.getCustomAnimation(5);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 2);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_ILUSIONSHURIKEN, -1, 0, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_ILUSIONSHURIKEN, 0);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

			obj.setTimeEvent(0, 500, 0, false);
		break;
		case 7://?????????????? ????
			local ani = obj.getCustomAnimation(5);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 2);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_ILUSIONSHURIKEN, -1, 0, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_ILUSIONSHURIKEN, 0);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
			obj.sq_SetMoveParticle("Particle/illusionsuriken.ptl", 0.0, -45.0);
			obj.setCustomRotate(true, sq_ToRadian(-45.0));
		break;
		case 8://???? ?? ju??? ?????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(6);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);
		break;
		case 9://???? ?? ju???
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 10://???? ?? ???????? ????? ???
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(9);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);
			obj.sq_PlaySound("NSKUNAI_CAST");
		break;
		case 11://???? ?? ???????? ????? ????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(10);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);
			obj.sq_PlaySound("NSKUNAI_CAST");
		break;
		case 12://???? ?? ???????? ???
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 13://???? ?? ???????? ????
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 14://???? : ?????? ?????
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 15://???? : ?????? ???
			local ani = obj.getCustomAnimation(19);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 4);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_MIGAWARI, -1, 0, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);
		break;
		case 16://???? : ?????? ?????
			local ani = obj.getCustomAnimation(20);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 4);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_MIGAWARI, -1, 1, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);
		break;
		case 17://???? : ?????? ????
			local ani = obj.getCustomAnimation(21);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 5);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_MIGAWARI, -1, 2, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_MIGAWARI, 0);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
			sq_SetMyShake(obj, 5, 300);
			sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		break;
		case 18://???? ?? ????? ????? ???
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(22);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);
		break;
		case 19://???? ?? ????? ????? ????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(23);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);
		break;
		case 20://???? ?? ????? ???????
			local ani = obj.getCustomAnimation(24);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 6);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_SKYROADS, -1, 0, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);
		break;
		case 21://???? ?? ????? ?????????
			local ani = obj.getCustomAnimation(25);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 7);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_SKYROADS, -1, 1, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);
		break;
		case 22://???? ?? ????? ?????????
			local ani = obj.getCustomAnimation(26);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 8);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_SKYROADS, -1, 2, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_SKYROADS, 0);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
			sq_SetMyShake(obj, 10, 300);
			sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		break;
		case 23://???? ?? ????? ???????
			local ani = obj.getCustomAnimation(27);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 9);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_SKYROADS, -1, 3, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_SKYROADS, 1);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

			local skill_level = sq_GetSkillLevel(parentChr, SKILL_SKYROADS);
			local act_rate = sq_GetLevelData(parentChr, SKILL_SKYROADS, 4, skill_level);
			local act_level = sq_GetLevelData(parentChr, SKILL_SKYROADS, 5, skill_level);
			local act_time = sq_GetLevelData(parentChr, SKILL_SKYROADS, 6, skill_level);
			local act_damage = sq_GetLevelData(parentChr, SKILL_SKYROADS, 7, skill_level);
			sq_SetChangeStatusIntoAttackInfo(pAttack, 0, ACTIVESTATUS_BURN, act_rate, act_level, act_time, act_damage);
		break;
		case 24://???? ?? ??chu?????? ?????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(28);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);
			obj.sq_PlaySound("R_GASOLINEFIRE_CAST");
		break;
		case 25://???? ?? ??chu??????
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 26://???? ?? ??chu?????? ??????
			local ani = obj.getCustomAnimation(31);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 11);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_GASOLINEFIRE, -1, 1, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_GASOLINEFIRE, 0);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

			local skill_level = sq_GetSkillLevel(parentChr, SKILL_GASOLINEFIRE);
			local act_rate = sq_GetLevelData(parentChr, SKILL_GASOLINEFIRE, 3, skill_level);
			local act_level = sq_GetLevelData(parentChr, SKILL_GASOLINEFIRE, 4, skill_level);
			local act_time = sq_GetLevelData(parentChr, SKILL_GASOLINEFIRE, 5, skill_level);
			local act_damage = sq_GetLevelData(parentChr, SKILL_GASOLINEFIRE, 6, skill_level);
			sq_SetChangeStatusIntoAttackInfo(pAttack, 0, ACTIVESTATUS_BURN, act_rate, act_level, act_time, act_damage);
			sq_SetMyShake(obj, 10, 300);
			obj.sq_PlaySound("GASOLINEFIRE_BALL_EXP");
		break;
		case 27://???? ?? ???????? ?????
			local ani = obj.getCustomAnimation(32);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);

			local attackInfo = sq_GetCustomAttackInfo(obj, 13);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FLAMEFLOWER, -1, 0, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);
			if(pAni){
				local delay = pAni.getDelaySum(false);
				sq_flashScreen(obj, 0, delay, 0, 125, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
			}
		break;
		case 28://???? ?? ???????? ??????????
			local ani = obj.getCustomAnimation(33);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 14);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FLAMEFLOWER, -1, 1, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_FLAMEFLOWER, 1);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

			local HitCount = sq_GetIntData(parentChr, SKILL_FLAMEFLOWER, 0);
			obj.setTimeEvent(0, 1400 / HitCount, HitCount, false);
		break;
		case 29://???? ?? ???????? ???????????
			local ani = obj.getCustomAnimation(34);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 15);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FLAMEFLOWER, -1, 2, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_FLAMEFLOWER, 2);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
			sq_SetMyShake(obj, 8, 300);
			sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		break;
		case 30://???? ?? ????????? ?????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(35);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);

			local attackInfo = sq_GetCustomAttackInfo(obj, 18);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 2, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			if(obj.isMyControlObject())
			{
				parentChr.sq_StartWrite();
				parentChr.sq_WriteDword(31);//???? ?? ????????? ????
				sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 400), y, z);
				parentChr.sq_StartWrite();
				parentChr.sq_WriteDword(32);//???? ?? ????????? ????????????????
				sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 400), y, z);
			}

			local objectManager = obj.getObjectManager();
			for(local i = 0; i < objectManager.getCollisionObjectNumber(); ++ i)
			{
				local object = objectManager.getCollisionObject(i);
				if(object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE))
				{
					local mobXPos = sq_GetXPos(object);
					local mobYPos = sq_GetYPos(object);
					obj.getVar("attract").clear_vector();
					obj.getVar("attract").push_vector(mobXPos);
					obj.getVar("attract").push_vector(mobYPos);
				}
			}
		break;
		case 31://???? ?? ????????? ????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(36);
			obj.setCurrentAnimation(ani);

			local size = 1.0;
			local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
			local sizeRate = sq_GetLevelData(parentChr, SKILL_DOOMFIELD, 6, skill_level);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
		break;
		case 32://???? ?? ????????? ????????
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 33://???? ?? ????????? ???????????1
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 34://???? ?? ????????? ???????????2
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 35://???? ?? ????????? ???????????3
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 36://???? ?? ????????? ???????????4
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 37://???? ?? ????????? ???????????5
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 38://???? ?? ????????? ???????????6
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 39://?????????????? ?????
			local ani = obj.getCustomAnimation(46);
			obj.setCurrentAnimation(ani);
			obj.setCurrentDirection(sq_GetOppositeDirection(parentChr.getDirection()));
		break;
		case 40://?????????????? ????
			local ani = obj.getCustomAnimation(47);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 21);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FLYINGSWALLOW, -1, 0, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = 150;
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
		break;
		case 41://?????????????? ??shuo???
			local ani = obj.getCustomAnimation(48);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 22);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FLYINGSWALLOW, -1, 1, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = 150;
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

			local angle = receiveData.readDword();
			obj.setCustomRotate(true, sq_ToRadian(1.0 * angle));
		break;
		case 42://?????????????? ?????????
			local ani = obj.getCustomAnimation(49);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 23);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FLYINGSWALLOW, -1, 2, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_FLYINGSWALLOW, 0);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

			local xRan = sq_getRandom(-200, 200);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom1_normal.ani", xRan, 0, 0, 0, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom1_normal.ani", xRan, 0, 0, 0, 100 * sizeRate, 0, 1, 1.0);
		break;
		case 43://?????????????? ?????????????????
			local ani = obj.getCustomAnimation(50);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 24);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FLYINGSWALLOW, -1, 3, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_FLYINGSWALLOW, 1);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", 40, 10, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", 80, -30, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", 120, 40, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", 160, -25, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", -40, 40, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", -80, -30, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", -120, 25, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", -160, -10, 0, 90, 100 * sizeRate, 0, 1, 1.0);
		break;
		case 44://?????????????? ????????????????? ????
			local ani = obj.getCustomAnimation(50);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 24);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FLYINGSWALLOW, -1, 3, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_FLYINGSWALLOW, 2);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", 40, 10, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", 80, -30, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", 120, 40, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", 160, -25, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", -40, 40, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", -80, -30, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", -120, 25, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", -160, -10, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", 200, -50, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", -200, 50, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", 170, 35, 0, 90, 100 * sizeRate, 0, 1, 1.0);
			als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom2_normal.ani", -170, -35, 0, 90, 100 * sizeRate, 0, 1, 1.0);
		break;
		case 45://???????? ?????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(51);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);
		break;
		case 46://????????
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 47://???????? ???
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 48://???? ?? ???????? ????? ???
			local ani = obj.getCustomAnimation(58);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);
		break;
		case 49://???? ?? ???????? ????? ????
			local ani = obj.getCustomAnimation(59);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);
		break;
		case 50://???? ?? ???????? ?1
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 51://???? ?? ???????? ?2
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 52://???? ?? ???????? ?3
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 53://???? ?? ???????? ?4
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 54://???? ?? ???????? ??
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 55://???? ?? ???????? ?? ????
			local ani = obj.getCustomAnimation(67);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 29);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 2, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 3);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
			sq_SetMyShake(obj, 10, 300);
		break;
		case 56://???? ?? ???????? ?? ????
			local ani = obj.getCustomAnimation(68);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 28);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 1, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 4);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

			local hitCount = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 0);
			obj.setTimeEvent(0, 300 / hitCount, 0, true);
			obj.sq_SetMaxHitCounterPerObject(hitCount);
			local xDistance = sq_GetDistancePos(x, obj.getDirection(), 200);
			local zDistance = 0;
			obj.getVar("bigSurikenMove").clear_vector();
			obj.getVar("bigSurikenMove").push_vector(xDistance);
			obj.getVar("bigSurikenMove").push_vector(zDistance);
		break;
		case 57://???? ?? ???????? ?? ???? ????
			local ani = obj.getCustomAnimation(69);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 29);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FUUMASHURIKEN, -1, 2, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_FUUMASHURIKEN, 4);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
			sq_SetMyShake(obj, 10, 300);
		break;
		case 58://???? ?????
			local ani = obj.getCustomAnimation(70);
			obj.setCurrentAnimation(ani);
			ani.setRGBA(255, 255, 255, 0);
		break;
		case 59://????
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 60://???? ??????
			local ani = obj.getCustomAnimation(74);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 31);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_AMATERAS, -1, 1, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_AMATERAS, 1);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
			sq_SetMyShake(obj, 5, 100);
		break;
		case 61://???????? ?? ?????? ????????
			local ani = obj.getCustomAnimation(75);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 32);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_SWORDOFKUSANAGI, -1, 0, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = 60;
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);

			local distance = sq_GetIntData(parentChr, SKILL_SWORDOFKUSANAGI, 1);
			local xDistance = sq_GetDistancePos(x, obj.getDirection(), distance);
			obj.getVar("swordofkusanagiMove").clear_vector();
			obj.getVar("swordofkusanagiMove").push_vector(x);
			obj.getVar("swordofkusanagiMove").push_vector(xDistance);
			parentChr.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);	
			sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
		break;
		case 62://???????? ?? ?????? ???????? ??
			local ani = obj.getCustomAnimation(75);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 32);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_SWORDOFKUSANAGI, -1, 0, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			local size = 1.0;
			local sizeRate = 60;
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
			obj.sq_SetMoveParticle("Particle/swordofkusanagi.ptl", 0.0, -45.0);
			obj.setCustomRotate(true, sq_ToRadian(-45.0));
		break;
		case 63://???????? ?? ?????? ?????? ?????
			local ani = obj.getCustomAnimation(76);
			obj.setCurrentAnimation(ani);
			local delay = pAni.getDelaySum(false);
			sq_flashScreen(obj, 70, delay, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		break;
		case 64://???????? ?? ?????? ??????
			local ani = obj.getCustomAnimation(77);
			obj.setCurrentAnimation(ani);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_SWORDOFKUSANAGI, 2);
			sizeRate = sizeRate.tofloat() / 100.0;
			ani.setImageRateFromOriginal(size * sizeRate, size * sizeRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(size * sizeRate);
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
		break;
		case 65://???? ?? ????????? ????? ????????????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(1);
			obj.setCurrentAnimation(ani);

			local attackTerm = sq_GetIntData(parentChr, SKILL_FLAMEBALL, 0);
			obj.setTimeEvent(0, attackTerm, 0, false);

			local size = 1.0;
			local sizeRate = sq_GetIntData(parentChr, SKILL_FLAMEBALL, 1);
			sizeRate = sizeRate.tofloat() / 100.0;
			sq_SetAttackBoundingBoxSizeRate(ani, size * sizeRate, size * sizeRate, size * sizeRate);
		break;
		case 66://?????????????? ????? ????????????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(3);
			obj.setCurrentAnimation(ani);
		break;
		case 67://?????????????? ????? ???????????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(4);
			obj.setCurrentAnimation(ani);
		break;
		case 68://???? ?? ju??? ??????????????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(6);
			obj.setCurrentAnimation(ani);
		break;
		case 69://???? ?? ???????? ????? ????????????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(9);
			obj.setCurrentAnimation(ani);
			obj.sq_PlaySound("NSKUNAI_CAST");
		break;
		case 70://???? ?? ???????? ????? ???????????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(10);
			obj.setCurrentAnimation(ani);
			obj.sq_PlaySound("NSKUNAI_CAST");
		break;
		case 71://???? : ?????? ??????????????
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 72://???? ?? ????? ????? ????????????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(22);
			obj.setCurrentAnimation(ani);
		break;
		case 73://???? ?? ????? ????? ???????????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(23);
			obj.setCurrentAnimation(ani);
		break;
		case 74://???? ?? ??chu?????? ??????????????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(28);
			obj.setCurrentAnimation(ani);
		break;
		case 75://???? ?? ??chu???????????????
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 76://???? ?? ???????? ??????????????
			local ani = obj.getCustomAnimation(32);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 13);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FLAMEFLOWER, -1, 0, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);
			local delay = pAni.getDelaySum(false);
			sq_flashScreen(obj, 0, delay, 0, 125, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		break;
		case 77://???????? ??????????????
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(51);
			obj.setCurrentAnimation(ani);
		break;
		case 78://???? ?? ???????? ????? ????????????
			local ani = obj.getCustomAnimation(58);
			obj.setCurrentAnimation(ani);
		break;
		case 79://???? ?? ???????? ????? ???????????
			local ani = obj.getCustomAnimation(59);
			obj.setCurrentAnimation(ani);
		break;
		case 80://???? ??????????????
			local ani = obj.getCustomAnimation(70);
			obj.setCurrentAnimation(ani);
		break;
	}
}