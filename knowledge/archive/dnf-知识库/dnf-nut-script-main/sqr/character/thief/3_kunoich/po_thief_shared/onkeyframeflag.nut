






function onKeyFrameFlag_po_thief_shared(obj, flagIndex)
{
	if(!obj) return false;

	local id = obj.getVar("id").get_vector(0);
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	local parentChr = sq_ObjectToSQRCharacter(obj.getTopCharacter());
	local pAni = obj.getCurrentAnimation();



	switch(id)
	{
		case 2://???? ?? ????????? ??????????
			switch(flagIndex)
			{
				case 10001:
					local attackInfo = sq_GetCustomAttackInfo(obj, 1);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FLAMEBALL, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local skill_level = sq_GetSkillLevel(parentChr, SKILL_FLAMEBALL);
					local act_rate = sq_GetLevelData(parentChr, SKILL_FLAMEBALL, 2, skill_level);
					local act_level = sq_GetLevelData(parentChr, SKILL_FLAMEBALL, 3, skill_level);
					local act_time = sq_GetLevelData(parentChr, SKILL_FLAMEBALL, 4, skill_level);
					local act_damage = sq_GetLevelData(parentChr, SKILL_FLAMEBALL, 5, skill_level);
					sq_SetChangeStatusIntoAttackInfo(pAttack, 0, ACTIVESTATUS_BURN, act_rate, act_level, act_time, act_damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FLAMEBALL, 1);
					sizeRate = sizeRate.tofloat() / 100.0;
					als_ani(obj, "character/thief/effect/animation/flameball/mouthpieceflameball.ani", 0, 0, 0, 0, 100 * sizeRate, 0, 1, 1.0);
					als_ani(obj, "character/thief/effect/animation/flameball/loop/loop_flameball_normal.ani", 0, 0, 0, 0, 100 * sizeRate, 0, 0, 1.0);
					als_ani(obj, "character/thief/effect/animation/flameball/loop/loop_flameball_dodge.ani", 0, 0, 0, 0, 100 * sizeRate, 0, 1, 1.0);
					als_ani(obj, "character/thief/effect/animation/flameball/end/end_flameball_normal.ani", 0, 0, 0, 0, 100 * sizeRate, 0, 0, 1.0);
					als_ani(obj, "character/thief/effect/animation/flameball/end/end_flameball_dodge.ani", 0, 0, 0, 0, 100 * sizeRate, 0, 1, 1.0);
					als_ani(obj, "character/thief/effect/animation/flameball/end/end_flameball_end_normal.ani", 0, 0, 0, 0, 100 * sizeRate, 0, 0, 1.0);
					als_ani(obj, "character/thief/effect/animation/flameball/end/end_flameball_end_dodge.ani", 0, 0, 0, 0, 100 * sizeRate, 0, 1, 1.0);
				break;
				case 10002:
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
					sq_SetMyShake(obj, 5, 300);
				break;
			}
		break;
		case 4://?????????????? ??????????
			switch(flagIndex)
			{
				case 10001:
					obj.sq_PlaySound("R_GHOSTKUNAI_THROW");
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_ILUSIONSHURIKEN);
					local ilusionCount = sq_GetLevelData(parentChr, SKILL_ILUSIONSHURIKEN, 1, skill_level);
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(6);//?????????????? ????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 60), y, z + 60);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(6);//?????????????? ????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 140), y + 50, z + 60);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(6);//?????????????? ????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 180), y - 50, z + 60);
						if(ilusionCount >= 3)
						{
							parentChr.sq_StartWrite();
							parentChr.sq_WriteDword(6);//?????????????? ????
							sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 30), y + 80, z + 60);
						}
						if(ilusionCount >= 4)
						{
							parentChr.sq_StartWrite();
							parentChr.sq_WriteDword(6);//?????????????? ????
							sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 80), y - 80, z + 60);
						}
					}
				break;
			}
		break;
		case 5://?????????????? ??????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(7);//?????????????? ????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 60), y, z + 60);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(7);//?????????????? ????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), -10), y + 30, z + 60);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(7);//?????????????? ????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), -10), y - 30, z + 60);
					}
				break;
			}
		break;
		case 8://???? ?? ju??? ??????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(9);//???? ?? ju???
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 60), y, z);
					}
				break;
			}
		break;
		case 10://???? ?? ???????????????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(12);//???? ?? ?????????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 99), y, z + 53);
					}
				break;
			}
		break;
		case 11://???? ?? ???????????????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(13);//???? ?? ?????????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 90), y, z);
					}
				break;
			}
		break;
		case 14://???? : ?????? ??????
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? : ?????? ??????????
					switch(flagIndex)
					{
						case 10001:
							if(obj.isMyControlObject())
							{
								parentChr.sq_StartWrite();
								parentChr.sq_WriteDword(15);//???? : ?????? ????
								sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y, z);
							}
						break;
					}
				break;
			}
		break;
		case 15://???? : ?????? ????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(16);//???? : ?????? ?????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y, z);
					}
				break;
			}
		break;
		case 18://???? ?? ????? ??????????
			switch(flagIndex)
			{
				case 10001:
					sq_SetVelocity(obj, 2, 1000.0);
				break;
				case 10002:
					sq_SetVelocity(obj, 2, 0.0);
					sq_SetCurrentPos(obj, x, y, 200);
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(21);//???? ?? ????? ?????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y, z);
					}
				break;
				case 10003:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(20);//???? ?? ????? ????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y, z);
					}
				break;
				case 10004:
					als_ani(obj, "passiveobject/shared_passive_object/thief/animation/skyroads/beam/hand_a.ani", -80, 0, 200, 45, 100, 0, 1, 1.0);
					als_ani(obj, "passiveobject/shared_passive_object/thief/animation/skyroads/beam/hand_b.ani", -80, 0, 200, 45, 100, 0, 1, 1.0);
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(22);//???? ?? ????? ?????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 300), y, 0);
					}
				break;
			}
		break;
		case 19://???? ?? ????? ??????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(21);//???? ?? ????? ?????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y, z);
					}
				break;
				case 10002:
					als_ani(obj, "passiveobject/shared_passive_object/thief/animation/skyroads/beam/hand_a.ani", -80, 0, 200, 45, 100, 0, 1, 1.0);
					als_ani(obj, "passiveobject/shared_passive_object/thief/animation/skyroads/beam/hand_b.ani", -80, 0, 200, 45, 100, 0, 1, 1.0);
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(22);//???? ?? ????? ?????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 300), y, 0);
					}
				break;
			}
		break;
		case 22://???? ?? ????? ?????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(23);//???? ?? ????? ????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y, 0);
					}
				break;
			}
		break;
		case 24://???? ?? ??chu?????? ??????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);//???? ?? ??chu??????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y, z);
					}
				break;
			}
		break;
		case 25://???? ?? ??chu??????
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? ?? ??chu?????? ??chu????
					switch(flagIndex)
					{
						case 10001:
							sq_SetMyShake(obj, 5, 300);
							obj.sq_PlaySound("GASOLINEFIRE_TOAD");
							sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
						break;
						case 10002:
							if(obj.isMyControlObject())
							{
								parentChr.sq_StartWrite();
								parentChr.sq_WriteDword(26);//???? ?? ??chu?????? ??????
								sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 400), y, z);
							}
						break;
					}
				break;
			}
		break;
		case 27://???? ?? ???????? ??????
			switch(flagIndex)
			{
				case 10001:
					obj.resetHitObjectList();
				break;
				case 10002:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(28);//???? ?? ???????? ??????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y - 1, z);
					}
				break;
				case 10003:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(29);//???? ?? ???????? ???????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y - 1, z);
					}
				break;
			}
		break;
		case 30://???? ?? ????????? ??????
			switch(flagIndex)
			{
				case 10001:
					local delay = pAni.getDelaySum(false);
					sq_flashScreen(obj, 0, delay, 0, 125, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
				break;
				case 10002:
					sq_MoveToNearMovablePos(obj, sq_GetDistancePos(x, obj.getDirection(), 400), y, z, x, y, z, 20, -1, 3);
				break;
				case 10003:
					sq_SetMyShake(obj, 5, 300);
					sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
				break;
				case 10004:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(33);//???? ?? ????????? ???????????1
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), -200), y - 100, z);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(34);//???? ?? ????????? ???????????2
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y - 130, z);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(35);//???? ?? ????????? ???????????3
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 200), y - 100, z);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(36);//???? ?? ????????? ???????????4
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 200), y, z);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(37);//???? ?? ????????? ???????????5
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y, z);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(38);//???? ?? ????????? ???????????6
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), -200), y, z);
					}
				break;
			}
		break;
		case 31://???? ?? ????????? ????
			switch(flagIndex)
			{
				case 10001:
					local attackInfo = sq_GetCustomAttackInfo(obj, 16);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);
				break;
				case 10002:
					if(sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD) >= 3)
					{
						obj.resetHitObjectList();
						local attackInfo = sq_GetCustomAttackInfo(obj, 16);
						sq_SetCurrentAttackInfo(obj, attackInfo);

						local pAttack = sq_GetCurrentAttackInfo(obj);
						local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_DOOMFIELD, -1, 5, 1.0);
						sq_SetCurrentAttackBonusRate(pAttack, damage);
					}
				break;
			}
		break;
		case 39://?????????????????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(41);//?????????????????shuo????
						parentChr.sq_WriteDword(-20);
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), -100), y, z + 100);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(42);//?????????????????????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 50), y, 0);
					}
					sq_MoveToNearMovablePos(obj, sq_GetDistancePos(x, obj.getDirection(), -200), y, 100, x, y, z, 20, -1, 3);
					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FLYINGSWALLOW, 0);
					sizeRate = sizeRate.tofloat() / 100.0;
					local xRan = sq_getRandom(0, 200);
					als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom1_normal.ani", xRan, 0, -100, 0, 100 * sizeRate, 0, 1, 1.0);
					als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom1_normal.ani", xRan, 0, -100, 0, 100 * sizeRate, 0, 1, 1.0);
				break;
				case 10002:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(41);//?????????????????shuo????
						parentChr.sq_WriteDword(-50);
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 100), y, z + 100);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(42);//?????????????????????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 250), y, 0);
					}
					sq_MoveToNearMovablePos(obj, sq_GetDistancePos(x, obj.getDirection(), 100), y, 200, x, y, z, 20, -1, 3);
					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FLYINGSWALLOW, 0);
					sizeRate = sizeRate.tofloat() / 100.0;
					local xRan = sq_getRandom(0, 200);
					als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom1_normal.ani", xRan, 0, -200, 0, 100 * sizeRate, 0, 1, 1.0);
					als_ani(obj, "passiveobject/shared_passive_object/thief/animation/flyingswallow/swallow_boom1_normal.ani", xRan, 0, -200, 0, 100 * sizeRate, 0, 1, 1.0);
				break;
			}
		break;
		case 46://????????
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 12://???????? ????
					switch(flagIndex)
					{
						case 10001:
							sq_SetMyShake(obj, 10, 300);
							sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
						break;
					}
				break;
			}
		break;
		case 48://???? ?? ???????????????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(50);//???? ?? ???????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 116), y, z + 66);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(51);//???? ?? ???????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 116), y, z + 66);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(52);//???? ?? ???????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 116), y, z + 66);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(53);//???? ?? ???????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 116), y, z + 66);
					}
				break;
				case 10002:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(54);//???? ?? ???????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 255), y, z + 58);
					}
				break;
			}
		break;
		case 49://???? ?? ???????????????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(56);//???? ?? ??????????? ????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 10), y, z + 66);
					}
				break;
			}
		break;
		case 59://????
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? ????
					switch(flagIndex)
					{
						case 10001:
							sq_SetMyShake(obj, 10, 300);
							sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
						break;
					}
				break;
				case 12://???? ????
					switch(flagIndex)
					{
						case 10001:
							sq_SetMyShake(obj, 10, 300);
							sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
						break;
					}
				break;
			}
		break;
		case 63://???????? ?? ?????? ?????? ??????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(64);//???????? ?? ?????? ??????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 400), y, 0);
					}
				break;
			}
		break;
		case 64://???????? ?? ?????? ??????
			switch(flagIndex)
			{
				case 10001:
					local attackInfo = sq_GetCustomAttackInfo(obj, 33);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_SWORDOFKUSANAGI, -1, 1, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);
					sq_SetMyShake(obj, 10, 300);
				break;
				case 10002:
					obj.resetHitObjectList();
					local attackInfo = sq_GetCustomAttackInfo(obj, 33);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_SWORDOFKUSANAGI, -1, 1, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);
					sq_SetMyShake(obj, 10, 300);
				break;
				case 10003:
					obj.resetHitObjectList();
					local attackInfo = sq_GetCustomAttackInfo(obj, 33);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_SWORDOFKUSANAGI, -1, 1, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);
					sq_SetMyShake(obj, 10, 300);
					sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
				break;
			}
		break;
		case 65://???? ?? ????????? ???????????????????
			switch(flagIndex)
			{
				case 10001:
					local attackInfo = sq_GetCustomAttackInfo(obj, 1);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(SKILL_FLAMEBALL, -1, 0, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local skill_level = sq_GetSkillLevel(parentChr, SKILL_FLAMEBALL);
					local act_rate = sq_GetLevelData(parentChr, SKILL_FLAMEBALL, 2, skill_level);
					local act_level = sq_GetLevelData(parentChr, SKILL_FLAMEBALL, 3, skill_level);
					local act_time = sq_GetLevelData(parentChr, SKILL_FLAMEBALL, 4, skill_level);
					local act_damage = sq_GetLevelData(parentChr, SKILL_FLAMEBALL, 5, skill_level);
					sq_SetChangeStatusIntoAttackInfo(pAttack, 0, ACTIVESTATUS_BURN, act_rate, act_level, act_time, act_damage);

					local size = 1.0;
					local sizeRate = sq_GetIntData(parentChr, SKILL_FLAMEBALL, 1);
					sizeRate = sizeRate.tofloat() / 100.0;
					als_ani(obj, "character/thief/effect/animation/flameball/mouthpieceflameball.ani", 0, 0, 0, 0, 100 * sizeRate, 0, 1, 1.0);
					als_ani(obj, "character/thief/effect/animation/flameball/loop/loop_flameball_normal.ani", 0, 0, 0, 0, 100 * sizeRate, 0, 0, 1.0);
					als_ani(obj, "character/thief/effect/animation/flameball/loop/loop_flameball_dodge.ani", 0, 0, 0, 0, 100 * sizeRate, 0, 1, 1.0);
					als_ani(obj, "character/thief/effect/animation/flameball/end/end_flameball_normal.ani", 0, 0, 0, 0, 100 * sizeRate, 0, 0, 1.0);
					als_ani(obj, "character/thief/effect/animation/flameball/end/end_flameball_dodge.ani", 0, 0, 0, 0, 100 * sizeRate, 0, 1, 1.0);
					als_ani(obj, "character/thief/effect/animation/flameball/end/end_flameball_end_normal.ani", 0, 0, 0, 0, 100 * sizeRate, 0, 0, 1.0);
					als_ani(obj, "character/thief/effect/animation/flameball/end/end_flameball_end_dodge.ani", 0, 0, 0, 0, 100 * sizeRate, 0, 1, 1.0);
				break;
				case 10002:
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
					sq_SetMyShake(obj, 5, 300);
				break;
			}
		break;
		case 66:////?????????????? ???????????????????
			switch(flagIndex)
			{
				case 10001:
					obj.sq_PlaySound("R_GHOSTKUNAI_THROW");
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_ILUSIONSHURIKEN);
					local ilusionCount = sq_GetLevelData(parentChr, SKILL_ILUSIONSHURIKEN, 1, skill_level);
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(6);//?????????????? ????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 60), y, z + 60);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(6);//?????????????? ????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 140), y + 50, z + 60);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(6);//?????????????? ????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 180), y - 50, z + 60);
						if(ilusionCount >= 3)
						{
							parentChr.sq_StartWrite();
							parentChr.sq_WriteDword(6);//?????????????? ????
							sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 30), y + 80, z + 60);
						}
						if(ilusionCount >= 4)
						{
							parentChr.sq_StartWrite();
							parentChr.sq_WriteDword(6);//?????????????? ????
							sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 80), y - 80, z + 60);
						}
					}
				break;
				case 10002:
					local skill_level = sq_GetSkillLevel(parentChr, SKILL_ILUSIONSHURIKEN);
					local ilusionCount = sq_GetLevelData(parentChr, SKILL_ILUSIONSHURIKEN, 1, skill_level);
			        als_ani(obj, "character/thief/animation/ilusionshuriken_shadow1.ani", 80, 50, 0, 0, 100, 0, 1, 1.0);
			        als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_boom.ani", 80, 51, 0, 0, 100, 0, 2, 1.0);
			        als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_glow.ani", 80, 51, 0, 0, 100, 0, 2, 1.0);
			        als_ani(obj, "character/thief/animation/ilusionshuriken_shadow1.ani", 120, -50, 0, 0, 100, 0, 1, 1.0);
			        als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_boom.ani", 120, -49, 0, 0, 100, 0, 2, 1.0);
			        als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_glow.ani", 120, -49, 0, 0, 100, 0, 2, 1.0);
			        if(ilusionCount >= 3)
			        {
			        	als_ani(obj, "character/thief/animation/ilusionshuriken_shadow1.ani", -30, 80, 0, 0, 100, 0, 1, 1.0);
			        	als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_boom.ani", -30, 81, 0, 0, 100, 0, 2, 1.0);
			        	als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_glow.ani", -30, 81, 0, 0, 100, 0, 2, 1.0);
			        }
			        if(ilusionCount >= 4)
			        {
			        	als_ani(obj, "character/thief/animation/ilusionshuriken_shadow1.ani", 20, -80, 0, 0, 100, 0, 1, 1.0);
			        	als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_boom.ani", 20, -79, 0, 0, 100, 0, 2, 1.0);
			        	als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_glow.ani", 20, -79, 0, 0, 100, 0, 2, 1.0);
			        }
				break;
			}
		break;
		case 67://?????????????? ?????????????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(7);//?????????????? ????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 60), y, z + 60);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(7);//?????????????? ????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), -10), y + 30, z + 60);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(7);//?????????????? ????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), -10), y - 30, z + 60);
					}
				break;
                case 10002:
				    als_ani(obj, "character/thief/animation/ilusionshuriken_shadow2.ani", -70, 30, 0, 0, 100, 0, 1, 1.0);
				    als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_boom.ani", -70, -29, 0, 0, 100, 0, 2, 1.0);
				    als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_glow.ani", -70, -29, 0, 0, 100, 0, 2, 1.0);
				    als_ani(obj, "character/thief/animation/ilusionshuriken_shadow2.ani", -70, -30, 0, 0, 100, 0, 1, 1.0);
				    als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_boom.ani", -70, -49, 0, 0, 100, 0, 2, 1.0);
				    als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_glow.ani", -70, -49, 0, 0, 100, 0, 2, 1.0);
                break;
			}
		break;
		case 68://???? ?? ju??? ???????????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(9);//???? ?? ju???
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 60), y, z);
					}
				break;
			}
		break;
		case 69://???? ?? ????????????????????????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(12);//???? ?? ?????????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 99), y, z + 53);
					}
				break;
			}
		break;
		case 70://???? ?? ??????????????????????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(13);//???? ?? ?????????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 90), y, z);
					}
				break;
			}
		break;
		case 71://???? : ?????? ???????????????
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? : ?????? ??????????
					switch(flagIndex)
					{
						case 10001:
							if(obj.isMyControlObject())
							{
								parentChr.sq_StartWrite();
								parentChr.sq_WriteDword(15);//???? : ?????? ????
								sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y, z);
							}
						break;
					}
				break;
			}
		break;
		case 72://???? ?? ????? ???????????????????
			switch(flagIndex)
			{
				case 10001:
					sq_SetVelocity(obj, 2, 1000.0);
				break;
				case 10002:
					sq_SetVelocity(obj, 2, 0.0);
					sq_SetCurrentPos(obj, x, y, 200);
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(21);//???? ?? ????? ?????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y, z);
					}
				break;
				case 10003:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(20);//???? ?? ????? ????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y, z);
					}
				break;
				case 10004:
					als_ani(obj, "passiveobject/shared_passive_object/thief/animation/skyroads/beam/hand_a.ani", -80, 0, 200, 45, 100, 0, 1, 1.0);
					als_ani(obj, "passiveobject/shared_passive_object/thief/animation/skyroads/beam/hand_b.ani", -80, 0, 200, 45, 100, 0, 1, 1.0);
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(22);//???? ?? ????? ?????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 300), y, 0);
					}
				break;
			}
		break;
		case 73://???? ?? ????? ?????????????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(21);//???? ?? ????? ?????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y, z);
					}
				break;
				case 10002:
					als_ani(obj, "passiveobject/shared_passive_object/thief/animation/skyroads/beam/hand_a.ani", -80, 0, 200, 45, 100, 0, 1, 1.0);
					als_ani(obj, "passiveobject/shared_passive_object/thief/animation/skyroads/beam/hand_b.ani", -80, 0, 200, 45, 100, 0, 1, 1.0);
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(22);//???? ?? ????? ?????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 300), y, 0);
					}
				break;
			}
		break;
		case 74://???? ?? ??chu?????? ???????????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);//???? ?? ??chu??????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y, z);
					}
				break;
			}
		break;
		case 75://???? ?? ??chu???????????????
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? ?? ??chu?????? ??chu????????????
					switch(flagIndex)
					{
						case 10001:
							sq_SetMyShake(obj, 5, 300);
							obj.sq_PlaySound("GASOLINEFIRE_TOAD");
							sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
						break;
						case 10002:
							if(obj.isMyControlObject())
							{
								parentChr.sq_StartWrite();
								parentChr.sq_WriteDword(26);//???? ?? ??chu?????? ??????
								sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 400), y, z);
							}
						break;
					}
				break;
			}
		break;
		case 76://???? ?? ???????? ???????????????
			switch(flagIndex)
			{
				case 10001:
					obj.resetHitObjectList();
				break;
				case 10002:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(28);//???? ?? ???????? ??????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y - 1, z);
					}
				break;
				case 10003:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(29);//???? ?? ???????? ???????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, x, y - 1, z);
					}
				break;
			}
		break;
		case 78://???? ?? ????????????????????????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(50);//???? ?? ???????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 116), y, z + 66);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(51);//???? ?? ???????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 116), y, z + 66);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(52);//???? ?? ???????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 116), y, z + 66);
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(53);//???? ?? ???????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 116), y, z + 66);
					}
				break;
				case 10002:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(54);//???? ?? ???????????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 255), y, z + 58);
					}
				break;
			}
		break;
		case 79://???? ?? ??????????????????????????
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(56);//???? ?? ??????????? ????
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(x, obj.getDirection(), 10), y, z + 66);
					}
				break;
			}
		break;
	}
	return true;
}



