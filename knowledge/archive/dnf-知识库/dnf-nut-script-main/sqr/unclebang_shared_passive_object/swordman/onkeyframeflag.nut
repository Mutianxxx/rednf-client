











function onKeyFrameFlag_po_swordman_shared(obj, flagIndex)
{
	if(!obj) return false;

	local id = obj.getVar("id").get_vector(0);
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	local parentChr = sq_ObjectToSQRCharacter(obj.getTopCharacter());

	switch(id)
	{
		case 24:
			switch(flagIndex)
			{
				case 10001:
					sq_SetMyShake(obj, 12, 400);
				break;
			}
		break;
		case 25:
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 12:
					switch(flagIndex)
					{
						case 10001:
							local attackInfo = sq_GetCustomAttackInfo(obj, 19);
							sq_SetCurrentAttackInfo(obj, attackInfo);

							local pAttack = sq_GetCurrentAttackInfo(obj);
							local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 14, 1.0);
							sq_SetCurrentAttackBonusRate(pAttack, damage);
						break;
						case 10002:
							obj.resetHitObjectList();
							local attackInfo = sq_GetCustomAttackInfo(obj, 20);
							sq_SetCurrentAttackInfo(obj, attackInfo);

							local pAttack = sq_GetCurrentAttackInfo(obj);
							local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 15, 1.0);
							sq_SetCurrentAttackBonusRate(pAttack, damage);
						break;
						case 10003:
							obj.resetHitObjectList();
							local attackInfo = sq_GetCustomAttackInfo(obj, 20);
							sq_SetCurrentAttackInfo(obj, attackInfo);

							local pAttack = sq_GetCurrentAttackInfo(obj);
							local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 16, 1.0);
							sq_SetCurrentAttackBonusRate(pAttack, damage);
						break;
					}
				break;
				case 13:
					switch(flagIndex)
					{
						case 10001:
							local attackInfo = sq_GetCustomAttackInfo(obj, 19);
							sq_SetCurrentAttackInfo(obj, attackInfo);

							local pAttack = sq_GetCurrentAttackInfo(obj);
							local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 14, 1.0);
							sq_SetCurrentAttackBonusRate(pAttack, damage);
						break;
						case 10002:
							sq_SetMyShake(obj, 5, 200);
						break;
						case 10003:
							obj.resetHitObjectList();
							local attackInfo = sq_GetCustomAttackInfo(obj, 21);
							sq_SetCurrentAttackInfo(obj, attackInfo);

							local pAttack = sq_GetCurrentAttackInfo(obj);
							local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 16, 1.0);
							sq_SetCurrentAttackBonusRate(pAttack, damage);

							if(obj.isMyControlObject())
							{
								parentChr.sq_StartWrite();
								parentChr.sq_WriteDword(27);
								sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
							}
						break;
					}
				break;
				case 15:
					switch(flagIndex)
					{
						case 10001:
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/soulcutter/soulcutter_normal.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/soulcutter/soulcutter_normal2.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/soulcutter/soulcutter_dodge.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/soulcutter/soulcutter_dodge2.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/soulcutter/soulcutter_dodge3.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
						break;
						case 10002:
							sq_flashScreen(obj, 140, 620, 140, 160, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
						break;
						case 10003:
							local attackInfo = sq_GetCustomAttackInfo(obj, 22);
							sq_SetCurrentAttackInfo(obj, attackInfo);

							local pAttack = sq_GetCurrentAttackInfo(obj);
							local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 17, 0.5);
							sq_SetCurrentAttackBonusRate(pAttack, damage);
						break;
						case 10004:
							local pAni = obj.getCurrentAnimation();
							sq_AddAttackBox(pAni, -500, -500, 0, 1000, 1000, 500);
							local attackInfo = sq_GetCustomAttackInfo(obj, 22);
							sq_SetCurrentAttackInfo(obj, attackInfo);

							local pAttack = sq_GetCurrentAttackInfo(obj);
							local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 17, 1.0);
							sq_SetCurrentAttackBonusRate(pAttack, damage);
						break;
						case 10005:
							local pAni = obj.getCurrentAnimation();
							sq_ClearAttackBox(pAni);
						break;
					}
				break;
				case 20:
					switch(flagIndex)
					{
						case 10001:
							sq_SetMyShake(obj, 5, 200);
							sq_flashScreen(obj, 10, 70, 10, 100, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_kazan_shock2.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_kazan_circle2.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_kazan_shock1.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
						break;
					}
				break;
				case 21:
					switch(flagIndex)
					{
						case 10001:
							sq_SetMyShake(obj, 5, 200);
							sq_flashScreen(obj, 10, 70, 10, 100, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_bremen_shock2.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_bremen_circle2.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_bremen_shock1.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
						break;
					}
				break;
				case 22:
					switch(flagIndex)
					{
						case 10001:
							sq_SetMyShake(obj, 5, 200);
							sq_flashScreen(obj, 10, 70, 10, 100, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_saya_shock2.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_saya_circle2.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_saya_shock1.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
						break;
					}
				break;
				case 23:
					switch(flagIndex)
					{
						case 10001:
							sq_SetMyShake(obj, 5, 200);
							sq_flashScreen(obj, 10, 70, 10, 100, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_saya_shock2.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_saya_circle2.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_saya_shock1.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
						break;
					}
				break;
				case 24:
					switch(flagIndex)
					{
						case 10001:
							sq_SetMyShake(obj, 5, 200);
							sq_flashScreen(obj, 10, 70, 10, 100, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_rasa_shock2.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_rasa_circle2.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
							als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/scream/scream_rasa_shock1.ani", 0, 0, 0, 0, 100, 0, 0, 1.0);
						break;
					}
				break;
			}
		break;
		case 26:
			switch(flagIndex)
			{
				case 10001:
					sq_SetMyShake(obj, 2, 200);
					als_ani(obj, "passiveobject/actionobject/monster/zig/animation/stonefall01_dodge.ani", 0, 0, 0, 0, 100, 0, 2, 1.0);
				break;
			}
		break;
	}
	return true;
}



