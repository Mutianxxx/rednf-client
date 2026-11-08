











function setState_po_swordman_shared(obj, state, datas)
{
	if(!obj) return;

	local id = obj.getVar("id").get_vector(0);
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	local parentChr = sq_ObjectToSQRCharacter(obj.getTopCharacter());
	switch(id)
	{
		case 25:
			switch(state)
			{
				case 10:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(10);

					local ani = obj.getCustomAnimation(34);
					obj.setCurrentAnimation(ani);

					local enemyObj = obj.sq_FindFirstTarget(-1000, 1000, 2000, 200);
					if(!enemyObj && sq_GetDistanceObject(obj, parentChr, false) >= 50)
					{
						als_ani(obj, "monster/newmonsters/zig/animation/teleport_disappear_body.ani", 0, 0, 0, 0, 100, 1, 1, 1.0);
						obj.setCurrentPos(parentChr.getXPos(), parentChr.getYPos() - 1, 0);
						obj.setCurrentDirection(parentChr.getDirection());
					}
				break;
				case 11:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(11);

					local ani = obj.getCustomAnimation(35);
					obj.setCurrentAnimation(ani);

					local enemyObj = obj.sq_FindFirstTarget(-1000, 1000, 2000, 200);
					local enemyXPos = sq_GetXPos(enemyObj);
					local enemyYPos = sq_GetYPos(enemyObj);
					obj.getVar("enemyPos").clear_vector();
					obj.getVar("enemyPos").push_vector(enemyXPos);
					obj.getVar("enemyPos").push_vector(enemyYPos);
					setZigDirection(obj);
				break;
				case 12:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(12);

					local ani = obj.getCustomAnimation(36);
					obj.setCurrentAnimation(ani);
				break;
				case 13:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(13);

					local ani = obj.getCustomAnimation(37);
					obj.setCurrentAnimation(ani);
				break;
				case 14:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(14);

					local ani = obj.getCustomAnimation(38);
					obj.setCurrentAnimation(ani);

					local pAni = obj.getCurrentAnimation();
					local delay = pAni.getDelaySum(false);
					local count = sq_GetIntData(parentChr, 241, 1);
					obj.setTimeEvent(2, delay / count, count, false);
				break;
				case 15:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(15);

					local ani = obj.getCustomAnimation(39);
					obj.setCurrentAnimation(ani);

					local xDistance = sq_GetDistancePos(x, obj.getDirection(), 300);
					obj.getVar("zigMove").clear_vector();
					obj.getVar("zigMove").push_vector(xDistance);
				break;
				case 16:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(16);

					local ani = obj.getCustomAnimation(41);
					obj.setCurrentAnimation(ani);

					als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/teleport/teleport_disappear_body.ani", 0, 0, 0, 0, 100, 0, 1, 1.0);
					obj.setCurrentPos(parentChr.getXPos(), parentChr.getYPos() - 1, 0);
					obj.setCurrentDirection(parentChr.getDirection());
				break;
				case 17:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(17);

					local ani = obj.getCustomAnimation(42);
					obj.setCurrentAnimation(ani);

					als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/teleport/teleport_disappear_body.ani", 0, 0, 0, 0, 100, 0, 1, 1.0);
					obj.setCurrentPos(parentChr.getXPos(), parentChr.getYPos() - 1, 0);
					obj.setCurrentDirection(parentChr.getDirection());
				break;
				case 18:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(18);

					local ani = obj.getCustomAnimation(43);
					obj.setCurrentAnimation(ani);

					als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/teleport/teleport_disappear_body.ani", 0, 0, 0, 0, 100, 0, 1, 1.0);
					obj.setCurrentPos(parentChr.getXPos(), parentChr.getYPos() - 1, 0);
					obj.setCurrentDirection(parentChr.getDirection());
					sq_moveWithParent(parentChr, obj);
				break;
				case 19:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(19);

					local ani = obj.getCustomAnimation(44);
					obj.setCurrentAnimation(ani);

					als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/teleport/teleport_disappear_body.ani", 0, 0, 0, 0, 100, 0, 1, 1.0);
					obj.setCurrentPos(parentChr.getXPos(), parentChr.getYPos() - 1, 0);
					obj.setCurrentDirection(parentChr.getDirection());

					local pAni = obj.getCurrentAnimation();
					local delay = pAni.getDelaySum(false);
					local count = sq_GetIntData(parentChr, 241, 1);
					obj.setTimeEvent(2, delay / count, count, false);
				break;
				case 20:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(20);

					local ani = obj.getCustomAnimation(45);
					obj.setCurrentAnimation(ani);

					als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/teleport/teleport_disappear_body.ani", 0, 0, 0, 0, 100, 0, 1, 1.0);
					obj.setCurrentPos(parentChr.getXPos(), parentChr.getYPos() - 1, 0);
					obj.setCurrentDirection(parentChr.getDirection());

					local attackInfo = sq_GetCustomAttackInfo(obj, 24);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 19, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local objectManager = obj.getObjectManager();
					for(local i = 0; i < objectManager.getCollisionObjectNumber(); ++ i)
					{
						local object = objectManager.getCollisionObject(i);
						if(object && !obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) && sq_GetDistance(x, y, object.getXPos(), object.getYPos(), true) <= 800)
						{
							local appendage = CNSquirrelAppendage.sq_AppendAppendage(object, object, -1, false, "character/swordman/zigadvent/ap_scream_kazan_friend.nut", true);
							local change_appendage = appendage.sq_getChangeStatus("scream_kazan_friend");
							if(!change_appendage)
							{
								change_appendage = appendage.sq_AddChangeStatus("scream_kazan_friend",object, object, sq_GetIntData(parentChr, 241, 2), CHANGE_STATUS_TYPE_PHYSICAL_ATTACK_BONUS, true, sq_GetIntData(parentChr, 241, 3));
								change_appendage = appendage.sq_AddChangeStatus("scream_kazan_friend",object, object, sq_GetIntData(parentChr, 241, 2), CHANGE_STATUS_TYPE_MAGICAL_ATTACK_BONUS, true, sq_GetIntData(parentChr, 241, 3));
								change_appendage = appendage.sq_AddChangeStatus("scream_kazan_friend",object, object, sq_GetIntData(parentChr, 241, 2), CHANGE_STATUS_TYPE_ADDITIONAL_PHYSICAL_GENUINE_ATTACK, true, sq_GetIntData(parentChr, 241, 3));
								change_appendage = appendage.sq_AddChangeStatus("scream_kazan_friend",object, object, sq_GetIntData(parentChr, 241, 2), CHANGE_STATUS_TYPE_ADDITIONAL_MAGICAL_GENUINE_ATTACK, true, sq_GetIntData(parentChr, 241, 3));
							}
							if(change_appendage)
							{
								local registValue = sq_GetIntData(parentChr, 241, 4);
								change_appendage.clearParameter();
								change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK_BONUS, true, registValue.tofloat());
								change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK_BONUS, true, registValue.tofloat());
								change_appendage.addParameter(CHANGE_STATUS_TYPE_ADDITIONAL_PHYSICAL_GENUINE_ATTACK, true, registValue.tofloat());
								change_appendage.addParameter(CHANGE_STATUS_TYPE_ADDITIONAL_MAGICAL_GENUINE_ATTACK, true, registValue.tofloat());
							}
						}
					}
				break;
				case 21:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(21);

					local ani = obj.getCustomAnimation(45);
					obj.setCurrentAnimation(ani);

					als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/teleport/teleport_disappear_body.ani", 0, 0, 0, 0, 100, 0, 1, 1.0);
					obj.setCurrentPos(parentChr.getXPos(), parentChr.getYPos() - 1, 0);
					obj.setCurrentDirection(parentChr.getDirection());

					local attackInfo = sq_GetCustomAttackInfo(obj, 24);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 20, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local appendage_f = CNSquirrelAppendage.sq_AppendAppendage(parentChr, parentChr, -1, false, "character/swordman/zigadvent/ap_scream_bremen_friend.nut", true);
					appendage_f.sq_SetValidTime(1000);
					
					local objectManager = obj.getObjectManager();
					for(local i = 0; i < objectManager.getCollisionObjectNumber(); ++ i)
					{
						local object = objectManager.getCollisionObject(i);
						if(object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) && sq_GetDistance(x, y, object.getXPos(), object.getYPos(), true) <= 800)
						{
							local appendage = CNSquirrelAppendage.sq_AppendAppendage(object, object, -1, false, "character/swordman/zigadvent/ap_scream_bremen_enemy.nut", true);
							local change_appendage = appendage.sq_getChangeStatus("scream_bremen_enemy");
							if(!change_appendage){
								change_appendage = appendage.sq_AddChangeStatus("scream_bremen_enemy",object, object, sq_GetIntData(parentChr, 241, 2), CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_DEFENSE, true, sq_GetIntData(parentChr, 241, 4));
								change_appendage = appendage.sq_AddChangeStatus("scream_bremen_enemy",object, object, sq_GetIntData(parentChr, 241, 2), CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_DEFENSE, true, sq_GetIntData(parentChr, 241, 4));
							}
							if(change_appendage){
								local registValue = sq_GetIntData(parentChr, 241, 4);
								change_appendage.clearParameter();
								change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_DEFENSE, true, registValue.tofloat());
								change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_DEFENSE, true, registValue.tofloat());
							}
						}
					}
				break;
				case 22:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(22);

					local ani = obj.getCustomAnimation(45);
					obj.setCurrentAnimation(ani);

					als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/teleport/teleport_disappear_body.ani", 0, 0, 0, 0, 100, 0, 1, 1.0);
					obj.setCurrentPos(parentChr.getXPos(), parentChr.getYPos() - 1, 0);
					obj.setCurrentDirection(parentChr.getDirection());

					local attackInfo = sq_GetCustomAttackInfo(obj, 25);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 21, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local objectManager = obj.getObjectManager();
					for(local i = 0; i < objectManager.getCollisionObjectNumber(); ++ i)
					{
						local object = objectManager.getCollisionObject(i);
						if(object && !obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) && sq_GetDistance(x, y, object.getXPos(), object.getYPos(), true) <= 800)
						{
							
							local appendage = CNSquirrelAppendage.sq_AppendAppendage(object, object, -1, false, "character/swordman/zigadvent/ap_scream_saya_friend.nut", true);
							local change_appendage = appendage.sq_getChangeStatus("scream_saya_friend");
							if(!change_appendage){
								change_appendage = appendage.sq_AddChangeStatus("scream_saya_friend",object, object, sq_GetIntData(parentChr, 241, 2), CHANGE_STATUS_TYPE_ELEMENT_ATTACK_WATER, false, sq_GetIntData(parentChr, 241, 5));
							}
							if(change_appendage)
							{
								local registValue = sq_GetIntData(parentChr, 241, 5);
								change_appendage.clearParameter();
								change_appendage.addParameter(CHANGE_STATUS_TYPE_ELEMENT_ATTACK_WATER, true, registValue.tofloat());
							}
								
						}
					}
				break;
				case 23:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(23);

					local ani = obj.getCustomAnimation(45);
					obj.setCurrentAnimation(ani);

					als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/teleport/teleport_disappear_body.ani", 0, 0, 0, 0, 100, 0, 1, 1.0);
					obj.setCurrentPos(parentChr.getXPos(), parentChr.getYPos() - 1, 0);
					obj.setCurrentDirection(parentChr.getDirection());

					local attackInfo = sq_GetCustomAttackInfo(obj, 25);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 22, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);

					local objectManager = obj.getObjectManager();
					for(local i = 0; i < objectManager.getCollisionObjectNumber(); ++ i)
					{
						local object = objectManager.getCollisionObject(i);
						if(object && !obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) && sq_GetDistance(x, y, object.getXPos(), object.getYPos(), true) <= 800)
						{
							local appendage = CNSquirrelAppendage.sq_AppendAppendage(object, object, -1, false, "character/swordman/zigadvent/ap_scream_sayaex_friend.nut", true);
							local change_appendage = appendage.sq_getChangeStatus("scream_sayaex_friend");
							if(!change_appendage)
								change_appendage = appendage.sq_AddChangeStatus("scream_sayaex_friend",object, object, sq_GetIntData(parentChr, 241, 2), CHANGE_STATUS_TYPE_ELEMENT_ATTACK_WATER, false, sq_GetIntData(parentChr, 241, 5));
							if(change_appendage)
							{
								local registValue = sq_GetIntData(parentChr, 241, 5);
								change_appendage.clearParameter();
								change_appendage.addParameter(CHANGE_STATUS_TYPE_ELEMENT_ATTACK_WATER, true, registValue.tofloat());
							}
						}
					}
				break;
				case 24:
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(24);

					local ani = obj.getCustomAnimation(45);
					obj.setCurrentAnimation(ani);

					als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/teleport/teleport_disappear_body.ani", 0, 0, 0, 0, 100, 0, 1, 1.0);
					obj.setCurrentPos(parentChr.getXPos(), parentChr.getYPos() - 1, 0);
					obj.setCurrentDirection(parentChr.getDirection());

					local attackInfo = sq_GetCustomAttackInfo(obj, 26);
					sq_SetCurrentAttackInfo(obj, attackInfo);

					local pAttack = sq_GetCurrentAttackInfo(obj);
					local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 23, 1.0);
					sq_SetCurrentAttackBonusRate(pAttack, damage);
					
					local appendage_f = CNSquirrelAppendage.sq_AppendAppendage(parentChr, parentChr, -1, false, "character/swordman/zigadvent/ap_scream_rasa_friend.nut", true);
					appendage_f.sq_SetValidTime(1000);
					local objectManager = obj.getObjectManager();
					for(local i = 0; i < objectManager.getCollisionObjectNumber(); ++ i)
					{
						local object = objectManager.getCollisionObject(i);
						if(object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) && sq_GetDistance(x, y, object.getXPos(), object.getYPos(), true) <= 800)
						{
							
							local skill_level = sq_GetSkillLevel(parentChr, 75);
							sq_sendSetActiveStatusPacket(object, object, ACTIVESTATUS_POISON, sq_GetLevelData(parentChr, 75, 6, skill_level).tofloat(), sq_GetLevelData(parentChr, 75, 7, skill_level).tointeger(), false, sq_GetLevelData(parentChr, 75, 8, skill_level).tointeger());
							sq_sendSetActiveStatusPacket(object, object, ACTIVESTATUS_BLIND, sq_GetLevelData(parentChr, 75, 10, skill_level).tofloat(), sq_GetLevelData(parentChr, 75, 11, skill_level).tointeger(), false, sq_GetLevelData(parentChr, 75, 12, skill_level).tointeger());
							sq_sendSetActiveStatusPacket(object, object, ACTIVESTATUS_BLEEDING, sq_GetLevelData(parentChr, 75, 15, skill_level).tofloat(), sq_GetLevelData(parentChr, 75, 16, skill_level).tointeger(), false, sq_GetLevelData(parentChr, 75, 17, skill_level).tointeger());
							local appendage = CNSquirrelAppendage.sq_AppendAppendage(object, object, -1, false, "character/swordman/zigadvent/ap_scream_rasa_enemy.nut", true);
							local change_appendage = appendage.sq_getChangeStatus("scream_rasa_enemy");
							if(!change_appendage)
								change_appendage = appendage.sq_AddChangeStatus("scream_rasa_enemy",object, object, sq_GetIntData(parentChr, 241, 2), CHANGE_STATUS_TYPE_ACTIVESTATUS_TOLERANCE_ALL, false, sq_GetIntData(parentChr, 241, 6));
							if(change_appendage)
							{
								local registValue = sq_GetIntData(parentChr, 241, 6);
								change_appendage.clearParameter();
								change_appendage.addParameter(CHANGE_STATUS_TYPE_ACTIVESTATUS_TOLERANCE_ALL, true, registValue.tofloat());
							}
						}
					}
				break;
			}
		break;
	}
}



