 
function procSkill_Mage(obj) {
	if (!obj) return;
	if (sq_GetSkillLevel(obj, 168) > 0 && sq_getGrowType(obj) == 4) {
		getMonsterObject(obj);
	}
	if (sq_getGrowType(obj) == 0) {
		proc_bobybox(obj);
		proc_controldoll(obj);
		proc_bestommaster(obj);
		proc_evilcuriosity(obj);
		proc_cirrusindark(obj);
	}
	if (obj.getCurrentSkillIndex() == 2) {
		obj.getVar("isShowTime").setInt(0, 1);
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 2, false, "character/mage/magicaltempoup/ap_magicaltempoup.nut", true);
		local time = sq_GetLevelData(obj, 2, 0, sq_GetSkillLevel(obj, 2));
		appendage.getAppendageInfo().setValidTime(time);
	}
}

function SetMageStatePlaySound(obj)
{
	if(!obj) return;
	if(sq_GetSkillLevel(obj, 208) > 0)
	{
		obj.sq_SetSoundTagCreatureCommand("WZ_CMDPET_EN");
		obj.sq_SetSoundTagLackMp("WZ_NOMANA_EN");
		obj.sq_SetSoundTagCoolTime("R_WZ_COOLTIME_EN");
		obj.sq_SetSoundTagDie("R_WZ_DIE_EN");
	}
	else if (isDollState(obj))
	{
		obj.sq_SetSoundTagCreatureCommand("WZ_CMDPET_EN");
		obj.sq_SetSoundTagLackMp("WZ_NOMANA_EN_MN");
		obj.sq_SetSoundTagCoolTime("WZ_COOLTIME_EN_MN");
		obj.sq_SetSoundTagDie("WZ_DIE_EN_MN");
	}
	else
	{
		obj.sq_SetSoundTagCreatureCommand("WZ_CMDPET");
		obj.sq_SetSoundTagLackMp("WZ_NOMANA");
		obj.sq_SetSoundTagCoolTime("WZ_NOMANA");
		obj.sq_SetSoundTagDie("WZ_DIE");
	}
}

function setEvolutionChaserAnimation(obj, size) {
	if (!obj) return;
	if(!obj.isValid())
		return;
	obj.getVar("evolution").setInt(0, 1);
	local sizeRate = size.tofloat() / 100.0;
	local defaultAni = obj.getDefaultAnimation();
	//local newDefaultAni = sq_CreateAnimation("", "passiveobject/character/mage/animation/evolutionchaser/evolutionchaserstart01_02.ani");
	local newDefaultAni = obj.getVar().GetAnimationMap("chaserstarta", "passiveobject/character/mage/animation/evolutionchaser/evolutionchaserstart01_02.ani");
	newDefaultAni.setImageRateFromOriginal(sizeRate, sizeRate);
	newDefaultAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
	defaultAni.addLayerAnimation(6, newDefaultAni, false);
	
	
	local stayAni = obj.getCustomAnimation(0);
	//local newStayAni = sq_CreateAnimation("", "passiveobject/character/mage/animation/evolutionchaser/evolutionchaserloop_02.ani");
	local newStayAni = obj.getVar().GetAnimationMap("chaserloop", "passiveobject/character/mage/animation/evolutionchaser/evolutionchaserloop_01.ani");
	
	newStayAni.setEffectLayer(true, GRAPHICEFFECT_LINEARDODGE, true, sq_RGB(255, 255, 255), sq_ALPHA(200), true, false);
	newStayAni.Proc();
	newStayAni.setImageRateFromOriginal(sizeRate, sizeRate);
	newStayAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
	stayAni.addLayerAnimation(6, newStayAni, false);
	

	local disappearAni = obj.getCustomAnimation(1);
	disappearAni.addLayerAnimation(6, newDefaultAni, false);

	local attackAni = obj.getCustomAnimation(2);
	attackAni.addLayerAnimation(6, newStayAni, false);

	local bombAni = obj.getCustomAnimation(3);
	//local newBombAni = sq_CreateAnimation("", "passiveobject/character/mage/animation/evolutionchaser/evolutionchaserend_00.ani");
	local newBombAni = obj.getVar().GetAnimationMap("chaserend", "passiveobject/character/mage/animation/evolutionchaser/evolutionchaserend_00.ani");
	newBombAni.setImageRateFromOriginal(sizeRate, sizeRate);
	newBombAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
	
	//sq_SetAttackBoundingBoxSizeRate(bombAni, 1.5*sizeRate, 1.5*sizeRate, 1.5*sizeRate);
	bombAni.addLayerAnimation(6, newBombAni, false);
	
	
	local attackInfo = sq_GetCurrentAttackInfo(obj);
	if (attackInfo) {
		attackInfo.setElement(0);
		attackInfo.setElement(1);
		attackInfo.setElement(2);
		attackInfo.setElement(3);
	}
}

function proc_evolutionchaser(obj) {
	if (!obj) return;
	if (!obj.isMyControlObject()) return false;
	//23005	23002	23003	23006	23004
	local countDefault = obj.getMyPassiveObjectCount(23002);
	local countFire = obj.getMyPassiveObjectCount(23003);
	local countIce = obj.getMyPassiveObjectCount(23004);
	local countDark = obj.getMyPassiveObjectCount(23005);
	local countLight = obj.getMyPassiveObjectCount(23006);
	for (local i = 0; i < countDefault; ++i) {
		local chaser = obj.getMyPassiveObject(23002, i);
		if (!chaser) continue;
		if (chaser.getVar("evolution").getInt(0) == 1) continue;
		setEvolutionChaserAnimation(chaser, 100);
	}
	for (local i = 0; i < countFire; ++i) {
		local chaser = obj.getMyPassiveObject(23003, i);
		if (!chaser) continue;
		if (chaser.getVar("evolution").getInt(0) == 1) continue;
		setEvolutionChaserAnimation(chaser, 100);
	}
	for (local i = 0; i < countIce; ++i) {
		local chaser = obj.getMyPassiveObject(23004, i);
		if (!chaser) continue;
		if (chaser.getVar("evolution").getInt(0) == 1) continue;
		setEvolutionChaserAnimation(chaser, 100);
	}
	for (local i = 0; i < countDark; ++i) {
		local chaser = obj.getMyPassiveObject(23005, i);
		if (!chaser) continue;
		if (chaser.getVar("evolution").getInt(0) == 1) continue;
		setEvolutionChaserAnimation(chaser, 100);
	}
	for (local i = 0; i < countLight; ++i) {
		local chaser = obj.getMyPassiveObject(23006, i);
		if (!chaser) continue;
		if (chaser.getVar("evolution").getInt(0) == 1) continue;
		setEvolutionChaserAnimation(chaser, 100);
	}
}

function sendState_EclipseHive(obj, skillIndex){
	if (!obj) return false;
	if (!obj.isMyControlObject()) return false;
	local state = obj.sq_GetState();
	local skillLevel = obj.sq_GetSkillLevel(skillIndex);
	local monIndex = obj.sq_GetIntData(skillIndex, 2);
	local numMax = sq_GetLevelData(obj, skillIndex, 2, skillLevel);
	local monObj = getMyControlMonsterObject_Character(obj, monIndex, numMax);
	local skill = sq_GetSkill(obj, skillIndex);
	local isCool =  false;
	if (skill)
	{
		isCool = skill.isInCoolTime();
	}
	if (isCool)
	{
		monObj = getMyControlMonsterObject_Character(obj, monIndex, 1);
	}
	if(!monObj) return false;
	if (state == STATE_STAND || state == STATE_ATTACK || state == STATE_DASH) {

		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0); // throwState
		obj.sq_IntVectPush(0); // throwType
		obj.sq_IntVectPush(170); // throwIndex
		obj.sq_IntVectPush(800); // throwChargeTime
		obj.sq_IntVectPush(500); // throwShootTime
		obj.sq_IntVectPush(3); // throwAnimationIndex
		obj.sq_IntVectPush(4); // chargeSpeedType
		obj.sq_IntVectPush(4); // throwShootSpeedType
		obj.sq_IntVectPush(1000); // chargeSpeedValue
		obj.sq_IntVectPush(1000); // throwShootSpeedValue
		obj.sq_IntVectPush(-1); // personalCastRange
		obj.sq_AddSetStatePacket(STATE_THROW, STATE_PRIORITY_USER, true);
		
		local posX = obj.getXPos();
		local posY = obj.getYPos();
		local posZ = obj.getZPos();
		
		local fx = posX;
		local fy = posY;
		local fz = posZ;
		
		if(!sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL))
		{
			fx = sq_GetDistancePos(posX, obj.getDirection(), 70);
		}
		
		local ani = sq_AddDrawOnlyAniFromParent(monObj, "character/mage/effect/animation/eclipsehive/teleportdown.ani", 0, 1, 0);
 		sq_moveWithParent(monObj, ani);
		
		if(!sq_IsValidActiveStatus(monObj, ACTIVESTATUS_HOLD))
			sq_MoveToNearMovablePos(monObj, fx, fy, fz, monObj.getXPos(), monObj.getYPos(), monObj.getZPos(), 200, -1, 3);
		
		sq_IntVectorClear(sq_GetGlobalIntVector()); 
		switch(monIndex)
		{
			case 900:
				sq_IntVectorPush(sq_GetGlobalIntVector(), 2); 
			break;
			case 901:
			case 61256:
				sq_IntVectorPush(sq_GetGlobalIntVector(), 1); 
			break;
			case 60030:
				sq_IntVectorPush(sq_GetGlobalIntVector(), 3); 
			break;
			case 60020:
				sq_IntVectorPush(sq_GetGlobalIntVector(), 2); 
			break;
			case 60021:
				sq_IntVectorPush(sq_GetGlobalIntVector(), 2); 
			break;
			case 60022:
				sq_IntVectorPush(sq_GetGlobalIntVector(), 1); 
			break;
			case 60023:
				sq_IntVectorPush(sq_GetGlobalIntVector(), 1); 
			break;
			case 61259:
				sq_IntVectorPush(sq_GetGlobalIntVector(), 5); 
			break;
			case 61257:
				sq_IntVectorPush(sq_GetGlobalIntVector(), 2); 
			break;
			case 909:
				sq_IntVectorPush(sq_GetGlobalIntVector(), 7); 
			break;
			default:
				return false;
			break;
		}
		sq_AddSetStatePacketActiveObject(monObj, STATE_ATTACK, sq_GetGlobalIntVector(), STATE_PRIORITY_FORCE);
		monObj.flushSetStatePacket(); 
		monObj.setDirection(obj.getDirection());
		//obj.startSkillCoolTime(skillIndex, 1, 5000);
		return true;
	}
	return false;
}

function playNoDollSound(obj) {
	if (!obj) return false;
 	obj.startCantUseSkillWarning();
 	if (obj.isMessage())
 		sq_AddMessage(29002); 
 	if (isDollState(obj)) {
 		obj.sq_PlaySound("R_WZ_NODOLL_MN");
 	}
 	else{
 		obj.sq_PlaySound("R_WZ_NODOLL");
 	}
}

function playAttackSound_Mage(obj) {
	if (!obj) return;
	obj.sq_PlaySound("R_ICE_WALK_LOOP", SOUND_ID_MOVE);
}

function sendDotDollStand(obj) {
	if (!obj) return;
	local dot = getDotObj(obj); 
	if (dot) 
	{
		dot.getVar("state").clear_vector();
		dot.getVar("state").push_vector(0);
		local pIntVec = sq_GetGlobalIntVector();
		dot.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
	}
}

//????O?_?O?@?????A?]?^
//?}???I?H???@??

function isShowTime(obj) {
	if (!obj) return false;
	return CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/magicaltempoup/ap_magicaltempoup.nut");
}

function isElementalPotential(obj) {
	if (!obj) return false;
	if(sq_GetSkillLevel(obj, 167)<1)
	{
		return false;
	}
	local skill = sq_GetSkill(obj, 167);
	if(!skill){
		return false;
	}
	if(skill.isSealFunction()){
		return false;
	}
	return true;
}

function coolTimeDec_Mage(obj,skillIndex,currentCoolTime)
{
	if (!obj) return currentCoolTime;
	local newCoolTime = currentCoolTime;
	if(!isShowTime(obj))
		return currentCoolTime;
	switch(skillIndex)
	{
		case SKILL_CIRRUSAREA:
		case SKILL_PAINFUGRADEN:
		case SKILL_CIRRUSCUT:
		case SKILL_KEEPOUT:
		case SKILL_ROSECIRRUS:
			local decRate = 1.0 - sq_GetLevelData(obj, 2, 1, sq_GetSkillLevel(obj, 2))/1000.0;
			newCoolTime = currentCoolTime * decRate;
		break;
	}
	return newCoolTime;
}

function isDollState(obj) {
	if (!obj) return false;
	return CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/doll/ap_doll.nut");
}

function isReliveState(obj) {
	if (!obj) return false;
	return CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/relive/ap_eternalpossession.nut");
}
//????O?_?O?G????A?]?^
//??{???
function isZFAwakeing(obj) {
	if (!obj) return false;
	return CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut");

}
function getDotState(obj) {
	if (!obj) return  -1;
	local dot = getDotObj(obj);
	if (dot) {
		return dot.getVar("state").get_vector(0);
	}
	return -1;
}
//??oui????????q????rani
function returnBobyNumber(obj, num) {
	if (!obj) return;
	local numImage = null;
	local sq_var = obj.getVar();
	if (num == 0) {
		numImage = sq_var.GetAnimationMap("num0", "character/mage/animation/ani_als/bobybox_ui/0.ani");
	} else if (num == 1) {
		numImage = sq_var.GetAnimationMap("num1", "character/mage/animation/ani_als/bobybox_ui/1.ani");
	} else if (num == 2) {
		numImage = sq_var.GetAnimationMap("num2", "character/mage/animation/ani_als/bobybox_ui/2.ani");
	} else if (num == 3) {
		numImage = sq_var.GetAnimationMap("num3", "character/mage/animation/ani_als/bobybox_ui/3.ani");
	} else if (num == 4) {
		numImage = sq_var.GetAnimationMap("num4", "character/mage/animation/ani_als/bobybox_ui/4.ani");
	} else if (num == 5) {
		numImage = sq_var.GetAnimationMap("num5", "character/mage/animation/ani_als/bobybox_ui/5.ani");
	} else if (num == 6) {
		numImage = sq_var.GetAnimationMap("num6", "character/mage/animation/ani_als/bobybox_ui/6.ani");
	} else if (num == 7) {
		numImage = sq_var.GetAnimationMap("num7", "character/mage/animation/ani_als/bobybox_ui/7.ani");
	} else if (num == 8) {
		numImage = sq_var.GetAnimationMap("num8", "character/mage/animation/ani_als/bobybox_ui/8.ani");
	} else {
		numImage = sq_var.GetAnimationMap("num9", "character/mage/animation/ani_als/bobybox_ui/9.ani");
	}

	return numImage;
}

//?e?X??????q??ui
function drawBobyUi(obj) {
	if (!obj) return;
	if (isOpenBobyBox(obj) && CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/controldoll/ap_controldoll.nut")) {

		local x = 75;
		local y = 450;

		local sq_var = obj.getVar();
		local gaugebar_normal_base = sq_var.GetAnimationMap("back", "character/mage/animation/ani_als/bobybox_ui/main.ani");

		sq_AnimationProc(gaugebar_normal_base);
		sq_drawCurrentFrame(gaugebar_normal_base, x, y, false);

		local numImage = null;
		local numImage2 = null;
		local num = getBobyNumber(obj);
		local geNum = num % 10;
		local shiNum = num / 10;
		numImage = returnBobyNumber(obj, geNum);
		numImage2 = returnBobyNumber(obj, shiNum);
		sq_AnimationProc(numImage);
		sq_drawCurrentFrame(numImage, x + 48, y + 23, false);
		sq_AnimationProc(numImage2);
		sq_drawCurrentFrame(numImage2, x + 40, y + 23, false);
	}
}
//?s??S??A?S??Omage?s????A???O?|V?Oobj??
function createPassiveAndDirection(mage, obj, passId, value, x, y, z) {
	if (!obj) return;
	if (!mage) return;
	local posX = mage.getXPos();
	local posY = mage.getYPos();

	local distanceX = x - posX;
	local lastX = 0;
	local lastY = 0;
	local lastZ = -mage.getZPos();
	if (obj.getDirection() == ENUM_DIRECTION_LEFT) {
		lastX = -distanceX;
	} else {
		lastX = distanceX;
	}
	lastY = y - posY;
	lastZ = lastZ + z;

	sq_SendCreatePassiveObjectPacket(mage, passId, 0, lastX, lastY, lastZ, obj.getDirection());
}

function sendOneSmallEvilAppendAdd(obj) {
	if (!obj) return;
	local objectManager = obj.getObjectManager();
	local skill_level = sq_GetSkillLevel(obj, SKILL_SMALLEVIL);
	if (skill_level <1) {
		return false;
	}
	if (sq_getGrowType(obj) != 0){
		return false;
	}
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i += 1) {

		local object = objectManager.getCollisionObject(i);

		if (object && !obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_CHARACTER)) {
			try
			{
				object = sq_GetCNRDObjectToSQRCharacter(object);
				obj = sq_ObjectToSQRCharacter(obj);
			}
			catch(ex)
			{
			}
			local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(object, obj, SKILL_SMALLEVIL, false, "character/new_mage/smallevil/ap_smallevil.nut", true);
			
			local value0 = sq_GetLevelData(obj, SKILL_SMALLEVIL, 0, skill_level) / 2; //ll
			local value1 = sq_GetLevelData(obj, SKILL_SMALLEVIL, 1, skill_level) / 2; //zl
			local value2 = sq_GetLevelData(obj, SKILL_SMALLEVIL, 2, skill_level);
			local value3 = sq_GetLevelData(obj, SKILL_SMALLEVIL, 3, skill_level); //atk sd
			
			masterAppendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, ENUM_CHARACTERJOB_MAGE, SKILL_SMALLEVIL, skill_level);
			CNSquirrelAppendage.sq_AppendAppendageID(masterAppendage, object, obj, SKILL_SMALLEVIL, true);
			
			local change_appendage = masterAppendage.sq_getChangeStatus("smallevil");

			if (!change_appendage) {
				change_appendage = masterAppendage.sq_AddChangeStatus("smallevil",object, obj, 0, 0, false, 0);
			}

			if (change_appendage) {

				change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, false, value0.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED, false, value1.tofloat());

				change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, false, value2.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, value2.tofloat());

				change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_DEFENSE, false, value3.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_DEFENSE, false, value3.tofloat());

			}

		}
	}
}

//?]?w??????q??value
function setBobyNumber(obj, value) {
	if (!obj) return;
	if (isOpenBobyBox(obj)) {
		local apd = obj.GetSquirrelAppendage("character/new_mage/controldoll/ap_controldoll.nut");
		apd.getVar("num").set_vector(0, value);
	}
}
//??o??e????????q
//?p?G?B?_?@?????A?U?A?N???|?????????q?]??^-1?^
function getBobyNumber(obj) {
	if (!obj) return;
	if (isOpenBobyBox(obj)) {
		local apd = obj.GetSquirrelAppendage("character/new_mage/controldoll/ap_controldoll.nut");
		return apd.getVar("num").get_vector(0);
	} else {
		return -1;
	}
}

function getDotObj(obj) {
	if(!obj) {
		return null;
	}
	local dot = obj.getMyPassiveObject(24332, 0);
	if (dot) {
		return dot;
	}
	return null;
}

function createHotLoveFloor(obj, size) {
	if (!obj) return;
	local ani = sq_CreateAnimation("", "character/mage/animation/ani_als/hotlove/hotlove_floor_00.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj.setCurrentPos(obj.getXPos(), obj.getYPos() - 1, obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 2, false);
}

function proc_cirrusindark(obj) {
	if (!obj) return;
	local skill_level = sq_GetSkillLevel(obj, SKILL_CIRRUSINDARK);
	if (skill_level > 0) {
		if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/cirrusindark/ap_cirrusindark.nut")) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_CIRRUSINDARK, false, "character/new_mage/cirrusindark/ap_cirrusindark.nut", true);

			local value0 = sq_GetLevelData(obj, SKILL_CIRRUSINDARK, 0, skill_level) / 2; //ll

			local change_appendage = appendage.sq_getChangeStatus("cirrusindark");

			if (!change_appendage) {
				change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, value0, APID_COMMON);

			}
			if (change_appendage) {

				change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, value0.tofloat());
			}

			//           appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_CIRRUSINDARK, skill_level);
			//            CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_CIRRUSINDARK, true);

		}
	}
}

function proc_evilcuriosity(obj) {
	if (!obj) return;
	local skill_level = sq_GetSkillLevel(obj, SKILL_EVILCURIOSITY);
	if (skill_level > 0) {
		if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/evilcuriosity/ap_evilcuriosity.nut")) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_EVILCURIOSITY, false, "character/new_mage/evilcuriosity/ap_evilcuriosity.nut", true);

			//appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_EVILCURIOSITY, skill_level);
			CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_EVILCURIOSITY, true);

			local value0 = sq_GetLevelData(obj, SKILL_EVILCURIOSITY, 1, skill_level) / 20; //ll
			local change_appendage = appendage.sq_getChangeStatus("controldoll");
			if (!change_appendage) {
				change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_HIT_RATE, false, value0, APID_COMMON);
			}

			if (change_appendage) {
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_HIT_RATE, false, value0.tofloat());
			}

		}
	}
}

function proc_bestommaster(obj) {
	if (!obj) return;
	local skill_level = sq_GetSkillLevel(obj, SKILL_BESTOMASTER);
	if (skill_level > 0) {
		if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/bestommaster/ap_bestommaster.nut")) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BESTOMASTER, false, "character/new_mage/bestommaster/ap_bestommaster.nut", true);

			//appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_BESTOMASTER, skill_level);
			CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_BESTOMASTER, true);

		}
	}
}

function proc_mgequipbroom(obj) {
	if (!obj) return;
	local skill_level = sq_GetSkillLevel(obj, SKILL_BESTOMASTER);
	if (skill_level > 0) {
		if (obj.getWeaponSubType()==4)
		{
			if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/equipbroom/ap_mgequipbroom.nut")) {
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "character/new_mage/equipbroom/ap_mgequipbroom.nut", true);

				local change_appendage = appendage.sq_getChangeStatus("mgequipbroom");//üòö¢Ü¨ûùßÒ÷¾
				local aimbonus	  = sq_GetLevelData(obj, SKILL_BESTOMASTER, 1, skill_level);
				aimbonus		  = aimbonus.tofloat();
				local spdbonus	  = sq_GetLevelData(obj, SKILL_BESTOMASTER, 0, skill_level)/10;
				spdbonus		  = spdbonus.tofloat();
			
				if(!change_appendage)//Ó×Üô?ßÒ÷¾Ü¨ûùãÁ£¬ôÕÊ¥ßÒ÷¾Ü¨ûùîÜID
				{
					change_appendage = appendage.sq_AddChangeStatus("mgequipbroom",obj, obj, 0, 0, true, 0);
				}
				if(change_appendage) //Ó×?ßÒ÷¾Ü¨ûùãÁ
				{
					change_appendage.clearParameter();//?ð¶óÑâ¦
					change_appendage.addParameter(CHANGE_STATUS_TYPE_CAST_SPEED,true, spdbonus);
					change_appendage.addParameter(CHANGE_STATUS_TYPE_STUCK, false, -aimbonus);//Ù¤ñé
				}
			}
		}
		else
		{
			CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/new_mage/equipbroom/ap_mgequipbroom.nut");
		}
	}
}

function proc_controldoll(obj) {
	if (!obj) return;
	local skill_level = sq_GetSkillLevel(obj, SKILL_CONTROLDOLL);
	if (skill_level > 0) {
		if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/controldoll/ap_controldoll.nut")) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_CONTROLDOLL, false, "character/new_mage/controldoll/ap_controldoll.nut", true);

			appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_CONTROLDOLL, skill_level);
			CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_CONTROLDOLL, true);

			local value0 = sq_GetLevelData(obj, SKILL_CONTROLDOLL, 0, skill_level) / 2; //ll
			local change_appendage = appendage.sq_getChangeStatus("controldoll");
			if (!change_appendage) {
				change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, value0, APID_COMMON);
			}

			if (change_appendage) {
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, value0.tofloat());
			}

		}
	}
}

function isOpenBobyBox(obj) {
	if (!obj) return;
	local skill = sq_GetSkill(obj, SKILL_BOBYBOX);
	return !skill.isSealFunction();
}

function proc_bobybox(obj) {
	if (!obj) return;

	local skill_level = sq_GetSkillLevel(obj, SKILL_BOBYBOX);

	if (skill_level > 0) {
		if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/bobybox/ap_bobybox.nut")) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BOBYBOX, false, "character/new_mage/bobybox/ap_bobybox.nut", true);

			appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_BOBYBOX, skill_level);
			CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_BOBYBOX, true);
		}
	}
}
//sq_GetCustomAttackInfo
//sq_GetCustomAni

function getDashAttackInfo_Mage(obj) {
	if (!obj) return;
	local attackInfo = obj.sq_GetDashAttackInfo();
	if (isDollState(obj)) {
		attackInfo = sq_GetCustomAttackInfo(obj,ATTACKINFO_DOLL_MAD_DASHATK);
 		sq_SetCurrentAttackInfo(obj,attackInfo);
             obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);
		attackInfo = sq_GetCurrentAttackInfo(obj);
	}
	
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/bestommaster/ap_bestommaster.nut"))
	{
		if(attackInfo){
			attackInfo.setAttackType(ATTACKTYPE_MAGICAL);
		}
	}
	
	return attackInfo;
}

function getJumpAttackInfo_Mage(obj) {
	if (!obj) return;
	local attackInfo = obj.sq_GetJumpAttackInfo();
	if (isDollState(obj)) {
		attackInfo = sq_GetCustomAttackInfo(obj,ATTACKINFO_DOLL_MAD_JUMPATK);
 		sq_SetCurrentAttackInfo(obj,attackInfo);
             obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),7);
		attackInfo = sq_GetCurrentAttackInfo(obj);
	}
	
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/bestommaster/ap_bestommaster.nut"))
	{
		if(attackInfo){
			attackInfo.setAttackType(ATTACKTYPE_MAGICAL);
		}
	}
	
	return attackInfo;
}

function getDefaultAttackInfo_Mage(obj, index) {
	if (!obj) return;
	local attackInfo = obj.sq_GetDefaultAttackInfo(index);
	if (isDollState(obj)) {
		attackInfo = sq_GetCustomAttackInfo(obj,ATTACKINFO_DOLL_MAD_ATK + index);
		sq_SetCurrentAttackInfo(obj,attackInfo);
             obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);		
		attackInfo = sq_GetCurrentAttackInfo(obj);
	}
	
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/bestommaster/ap_bestommaster.nut"))
	{
		if(attackInfo){
			attackInfo.setAttackType(ATTACKTYPE_MAGICAL);
		}
	}
	
	return attackInfo;
}

function getAttackAni_Mage(obj, index) {
	if (!obj) return null;

	local sq_var = obj.getVar();
	local animation = obj.sq_GetAttackAni(index);

	if (isDollState(obj)) {
		animation = obj.sq_GetCustomAni(CUSTOM_ANI_DOLL_MAD_ATK + index);
	}
	return animation;
}

function getMoveAni_Mage(obj) {
	if (!obj) return null;

	local sq_var = obj.getVar();
	local ani = obj.sq_GetMoveAni();
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		ani = setCurrentAnimationMap_avatar_eff(obj, "Move", false);
	}
	else if (isDollState(obj)) {
		ani = obj.sq_GetCustomAni(CUSTOM_ANI_DOLL_MAD_MOVE);
	}
	else {
		ani = obj.sq_GetMoveAni();
	}
	return ani;
}

function getSitAni_Mage(obj) {
	if (!obj) return null;

	local ani = obj.sq_GetSitAni();
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		ani = setCurrentAnimationMap_avatar_eff(obj, "Sit", false);
	}
	else if (isDollState(obj)) {
		ani = obj.sq_GetCustomAni(CUSTOM_ANI_DOLL_MAD_SIT);
	}
	else {
		ani = obj.sq_GetSitAni();
	}

	return ani;
}

function getDownAni_Mage(obj) {
	if (!obj) return null;

	local ani = obj.sq_GetDownAni();
	local sq_var = obj.getVar();
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		ani = setCurrentAnimationMap_avatar_eff(obj, "Down", false);
	}
	else if (isDollState(obj)) {
		ani = obj.sq_GetCustomAni(CUSTOM_ANI_DOLL_MAD_DOWN);
	}
	else {
		ani = obj.sq_GetDownAni();
	}

	return ani;
}

function getAttackCancelStartFrameSize_Mage(obj) {
	if (!obj) return;
	local maxAttackNumber = obj.sq_GetAttackCancelStartFrameSize();
	if (isDollState(obj)) {
		maxAttackNumber = 1;
	}
	return maxAttackNumber;
}

function getDamageAni_Mage(obj, index) {
	if (!obj) return null;

	local ani = obj.sq_GetDamageAni(index);
	local sq_var = obj.getVar();
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		if (index == 0) ani = setCurrentAnimationMap_avatar_eff(obj, "Damage1", false);
		else if (index == 1) ani = setCurrentAnimationMap_avatar_eff(obj, "Damage2", false);
	}
	else if (isDollState(obj)) {
		ani = obj.sq_GetCustomAni(CUSTOM_ANI_DOLL_MAD_DAM + index);
	}
	else {
		ani = obj.sq_GetDamageAni(index);
	}

	return ani;
}

function getBuffAni_Mage(obj) {
	if (!obj) return null;

	local ani = obj.sq_GetBuffAni();
	local sq_var = obj.getVar();
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		ani = setCurrentAnimationMap_avatar_eff(obj, "Buff", false);
	}
	else if (isDollState(obj)) {
		ani = obj.sq_GetCustomAni(CUSTOM_ANI_DOLL_MAD_BUFF);
	}
	else {
		ani = obj.sq_GetBuffAni();
	}

	return ani;
}

function getGetItemAni_Mage(obj) {
	if (!obj) return null;

	local ani = obj.sq_GetGetItemAni();
	local sq_var = obj.getVar();
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		ani = setCurrentAnimationMap_avatar_eff(obj, "GetItem", false);
	}
	else if (isDollState(obj)) {
		ani = obj.sq_GetCustomAni(CUSTOM_ANI_DOLL_MAD_SIT);
	}
	else {
		ani = obj.sq_GetGetItemAni();
	}

	return ani;
}
function getDashAttackAni_Mage(obj) {
	if (!obj) return null;
	local ani = obj.sq_GetDashAttackAni();
	local sq_var = obj.getVar();
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		ani = setCurrentAnimationMap_avatar_eff(obj, "DashAttack", false);
	}
	else if (isDollState(obj)) {
		ani = obj.sq_GetCustomAni(CUSTOM_ANI_DOLL_MAD_DASHATK);
	}
	else {
		ani = obj.sq_GetDashAttackAni();
	}

	return ani;
}

function getJumpAttackAni_Mage(obj) {
	if (!obj) return null;

	local ani = obj.sq_GetJumpAttackAni();
	local sq_var = obj.getVar();
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		ani = setCurrentAnimationMap_avatar_eff(obj, "JumpAttack", false);
	}
	else if (isDollState(obj)) {
		ani = obj.sq_GetCustomAni(CUSTOM_ANI_DOLL_MAD_ATK2);
	}
	else {
		ani = obj.sq_GetJumpAttackAni();
	}

	return ani;
}

function getJumpAni_Mage(obj) {
	if (!obj) return null;

	local ani = obj.sq_GetJumpAni();
	local sq_var = obj.getVar();
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		ani = setCurrentAnimationMap_avatar_eff(obj, "Jump", false);
	}
	else if (isDollState(obj)) {
		ani = obj.sq_GetCustomAni(CUSTOM_ANI_DOLL_MAD_JUMP);
	}
	else {
		ani = obj.sq_GetJumpAni();
	}

	return ani;
}

function getDashAni_Mage(obj) {
	if (!obj) return null;
	local sq_var = obj.getVar();
	local ani = obj.sq_GetDashAni();
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		ani = setCurrentAnimationMap_avatar_eff(obj, "Dash", false);
	}
	else if (isDollState(obj)) {
		ani = obj.sq_GetCustomAni(CUSTOM_ANI_DOLL_MAD_DASH);
	}
	else {
		ani = obj.sq_GetDashAni();
	}

	return ani;
}

function getRestAni_Mage(obj) {
	if (!obj) return null;
	local currentani = null;
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		currentani = setCurrentAnimationMap_avatar_eff(obj, "Rest", false);
	}
	else if (isDollState(obj)) {
		currentani = obj.sq_GetCustomAni(CUSTOM_ANI_DOLL_MAD_STAY);
	}
	else {
		currentani = obj.sq_GetRestAni();
	}
	return currentani;
};

function getStayAni_Mage(obj) {
	if (!obj) return;
	local ani = obj.sq_GetStayAni();
	local sq_var = obj.getVar();
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		ani = setCurrentAnimationMap_avatar_eff(obj, "Stay", false);
	}
	else if (isDollState(obj)) {
		ani = obj.sq_GetCustomAni(CUSTOM_ANI_DOLL_MAD_STAY);
	}
	else {
		ani = obj.sq_GetStayAni();
	}

	return ani;
}

function setObj_MAGE_SIZE(obj, objID, sizeRate) {
	if (!obj) return;
	local passiveobject = obj.getMyPassiveObject(objID, 0);
	if (passiveobject) {
		local animation = sq_GetCurrentAnimation(passiveobject);
		local size = sizeRate.tofloat() / 100.0;
		animation.setImageRateFromOriginal(size, size);
		animation.setAutoLayerWorkAnimationAddSizeRate(size);
		local hitInterval = 60000;
		if (IsInterval(passiveobject, hitInterval)) {
			sq_SetAttackBoundingBoxSizeRate(animation, size, size, size);
		}
	}
}

function setATKinfo_SKILL_MAGE_ATTACK(obj, skill, index, passiveobjectID, sizeRate) {
	if (!obj) return;
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			local atk = sq_GetCurrentAttackInfo(passiveobject);

			local level = sq_GetSkillLevel(obj, skill);
			local attackPower = obj.sq_GetBonusRateWithPassive(skill, -1, index, 1);

			sq_SetCurrentAttackBonusRate(atk, attackPower);
			//setObj_MAGE_SIZE(obj, passiveobjectID, sizeRate);
		}
	}
}

function setATKinfo_SKILL_MAGE_POWER(obj, skill, index, passiveobjectID, sizeRate) {
	if (!obj) return;
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			local atk = sq_GetCurrentAttackInfo(passiveobject);

			local level = sq_GetSkillLevel(obj, skill);
			sq_SetCurrentAttackPower(obj.sq_GetPowerWithPassive(skill, -1, index, -1, 2.0));
			//sq_SetCurrentAttacknUpForce(sq_GetCurrentAttackInfo(passiveobject), 600);
			//setObj_MAGE_SIZE(obj, passiveobjectID, sizeRate);
		}
	}
}

function enable_FanZhongLi(obj) {
	if (!obj) return;
	if (sq_getJob(obj) == ENUM_CHARACTERJOB_MAGE && sq_getGrowType(obj) == 4) {
		local skillLevel = sq_GetSkillLevel(obj, 168);
		if (skillLevel <= 0) return;
		if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/appendage/ap_antigravitystarter.nut")) {
			CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 103, false, "character/mage/appendage/ap_antigravitystarter.nut", true);
		}
	}
}

function setEnableCancelSkill_Mage(PQTqYWyoPjv4ektK, vQHyclEdSW) {
	if (!PQTqYWyoPjv4ektK) return false;

	if (!PQTqYWyoPjv4ektK.isMyControlObject()) return false;
	if (!vQHyclEdSW) return true;
	if (!CNSquirrelAppendage.sq_IsAppendAppendage(PQTqYWyoPjv4ektK, "character/mage/appendage/ap_bellatrix.nut")) {
		PQTqYWyoPjv4ektK.setSkillCommandEnable(242, vQHyclEdSW);
		PQTqYWyoPjv4ektK.setSkillCommandEnable(243, vQHyclEdSW);
		PQTqYWyoPjv4ektK.setSkillCommandEnable(117, vQHyclEdSW);
		PQTqYWyoPjv4ektK.setSkillCommandEnable(245, vQHyclEdSW);
	}
	PQTqYWyoPjv4ektK.setSkillCommandEnable(246, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(247, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(249, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(250, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(251, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(252, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(253, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(131, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(132, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(133, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(134, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(135, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(136, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(137, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(138, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(139, vQHyclEdSW);
	PQTqYWyoPjv4ektK.setSkillCommandEnable(126, vQHyclEdSW);
	return true;
};

function addSetStatePacket_Mage(rBzERVpuv_c4, KrpKoM45CRSBujGMJsdn6m, iA3NnInwH43kdPzOKb59p) {
	if (!rBzERVpuv_c4) return -1;
	switch (KrpKoM45CRSBujGMJsdn6m) {
	case 27:
		local PdcciUT9bAyjq6t0bhdk = rBzERVpuv_c4.sq_GetVectorData(iA3NnInwH43kdPzOKb59p, 0);
		if (CNSquirrelAppendage.sq_IsAppendAppendage(rBzERVpuv_c4, "character/mage/appendage/ap_bellatrix.nut")) {
			if (PdcciUT9bAyjq6t0bhdk == 0) {

				rBzERVpuv_c4.sq_IntVectClear();
				rBzERVpuv_c4.sq_IntVectPush(4);
				rBzERVpuv_c4.sq_IntVectPush(1);
				rBzERVpuv_c4.sq_AddSetStatePacket(248, STATE_PRIORITY_USER, true);
				return -1;
			}
		}
		break;
	case 25:
		local PdcciUT9bAyjq6t0bhdk = rBzERVpuv_c4.sq_GetVectorData(iA3NnInwH43kdPzOKb59p, 0);
		local EfzK_UFLFG9c21p0TvPJBS1 = rBzERVpuv_c4.sq_GetVectorData(iA3NnInwH43kdPzOKb59p, 1);
		if (CNSquirrelAppendage.sq_IsAppendAppendage(rBzERVpuv_c4, "character/mage/appendage/ap_bellatrix.nut")) {
			if (PdcciUT9bAyjq6t0bhdk == 0 && EfzK_UFLFG9c21p0TvPJBS1 == 68) {

				rBzERVpuv_c4.sq_IntVectClear();
				rBzERVpuv_c4.sq_IntVectPush(3);
				rBzERVpuv_c4.sq_IntVectPush(1);
				rBzERVpuv_c4.sq_AddSetStatePacket(248, STATE_PRIORITY_USER, true);
				return -1;
			}
		}
		break;
	case 31:
		local PdcciUT9bAyjq6t0bhdk = rBzERVpuv_c4.sq_GetVectorData(iA3NnInwH43kdPzOKb59p, 0);
		if (PdcciUT9bAyjq6t0bhdk == 0) {

			rBzERVpuv_c4.sq_IntVectClear();
			rBzERVpuv_c4.sq_IntVectPush(1);
			rBzERVpuv_c4.sq_AddSetStatePacket(31, STATE_PRIORITY_USER, true);
			return -1;
		}
		break;
	case 29:
		local PdcciUT9bAyjq6t0bhdk = rBzERVpuv_c4.sq_GetVectorData(iA3NnInwH43kdPzOKb59p, 0);
		if (PdcciUT9bAyjq6t0bhdk == 0) {

			if (!CNSquirrelAppendage.sq_IsAppendAppendage(rBzERVpuv_c4, "character/mage/dragondance/ap_dragondance_proc_skill.nut")) return 1;

			rBzERVpuv_c4.sq_IntVectClear();
			if (CNSquirrelAppendage.sq_IsAppendAppendage(rBzERVpuv_c4, "character/mage/avatar/ap_avatar.nut")) rBzERVpuv_c4.sq_IntVectPush(1);
			else if (CNSquirrelAppendage.sq_IsAppendAppendage(rBzERVpuv_c4, "character/mage/appendage/ap_bellatrix.nut")) {
				rBzERVpuv_c4.sq_IntVectPush(2);
				rBzERVpuv_c4.sq_IntVectPush(1);
			}
			else rBzERVpuv_c4.sq_IntVectPush(0);
			rBzERVpuv_c4.sq_AddSetStatePacket(248, STATE_PRIORITY_USER, true);
			return -1;
		}
		break;
	}
	return 1;
};

function flushCommandEnable_Mage(R6ogHnfBxZjID) {
	if (!R6ogHnfBxZjID) return 0;
	if (!R6ogHnfBxZjID.isInBattle()) {
		sq_SetAllCommandEnable(R6ogHnfBxZjID, false);
		return 2;
	}
	local NTdbFwfIOu = null;

	if (CNSquirrelAppendage.sq_IsAppendAppendage(R6ogHnfBxZjID, "character/mage/appendage/ap_bellatrix.nut")) {

		for (local KVv1HzKIqmXxRwia0 = 242; KVv1HzKIqmXxRwia0 <= 244; KVv1HzKIqmXxRwia0++) {
			NTdbFwfIOu = sq_GetSkill(R6ogHnfBxZjID, KVv1HzKIqmXxRwia0);
			if (NTdbFwfIOu) NTdbFwfIOu.setCommandEnable(false);
		}
		NTdbFwfIOu = sq_GetSkill(R6ogHnfBxZjID, 66);
		if (NTdbFwfIOu) NTdbFwfIOu.setCommandEnable(true);
		NTdbFwfIOu = sq_GetSkill(R6ogHnfBxZjID, 68);
		if (NTdbFwfIOu) NTdbFwfIOu.setCommandEnable(true);

		if (CNSquirrelAppendage.sq_IsAppendAppendage(R6ogHnfBxZjID, "character/mage/dragondance/ap_dragondance_proc_skill.nut")) {
			NTdbFwfIOu = sq_GetSkill(R6ogHnfBxZjID, 69);
			if (NTdbFwfIOu) NTdbFwfIOu.setCommandEnable(true);
		}
		return 2;
	}
	return 0;
};

function onChangeSkillEffect_Mage(obj, skillIndex, reciveData) {
	if (!obj) return;
	switch (skillIndex) {
	case 245:
		local OmUe5zbG63a = reciveData.readWord();
		switch (OmUe5zbG63a) {
		case 1:
			onAppendApEff_qq506807329_mage_avatar(obj);
			break;
		}
		break;
	case 249:
	case 250:
	case 251:
	case 253:
		local OmUe5zbG63a = reciveData.readWord();
		switch (OmUe5zbG63a) {
		case 1:
			local yHQfXP8eAAJheQ8Mvsh = reciveData.readDword();

			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/appendage/ap_chargingeffect.nut")) CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/mage/appendage/ap_chargingeffect.nut");
			local H80Jrjjg5R4OJkfOtPqE5OM = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, true, "character/mage/appendage/ap_chargingeffect.nut", true);
			H80Jrjjg5R4OJkfOtPqE5OM.getVar("state").clear_vector();
			H80Jrjjg5R4OJkfOtPqE5OM.getVar("state").push_vector(1);
			H80Jrjjg5R4OJkfOtPqE5OM.getVar("limitTime").clear_vector();
			H80Jrjjg5R4OJkfOtPqE5OM.getVar("limitTime").push_vector(yHQfXP8eAAJheQ8Mvsh);
			break;
		}
		break;
	case 136:
		local OmUe5zbG63a = reciveData.readWord();
		switch (OmUe5zbG63a) {
		case 1:
			local FrkAGqHJ49wF7moJ38 = sq_GetCNRDObjectToActiveObject(sq_GetObject(obj, reciveData.readDword(), reciveData.readDword()));
			if (FrkAGqHJ49wF7moJ38.isDead()) return;
			FrkAGqHJ49wF7moJ38.setMapFollowParent(obj);
			FrkAGqHJ49wF7moJ38.setMapFollowType(1);
			local H80Jrjjg5R4OJkfOtPqE5OM = CNSquirrelAppendage.sq_AppendAppendage(FrkAGqHJ49wF7moJ38, FrkAGqHJ49wF7moJ38, 136, true, "character/mage/summonkruta/ap_summonkruta.nut", false);
			CNSquirrelAppendage.sq_Append(H80Jrjjg5R4OJkfOtPqE5OM, FrkAGqHJ49wF7moJ38, FrkAGqHJ49wF7moJ38, false);
			setStartInfo_appendage_mage_summonkruta(obj, H80Jrjjg5R4OJkfOtPqE5OM);
			break;
		}
		break;
	case 138:
		local OmUe5zbG63a = reciveData.readWord();
		switch (OmUe5zbG63a) {
		case 1:
			local FrkAGqHJ49wF7moJ38 = sq_GetCNRDObjectToActiveObject(sq_GetObject(obj, reciveData.readDword(), reciveData.readDword()));
			if (!FrkAGqHJ49wF7moJ38 || FrkAGqHJ49wF7moJ38.isDead()) return;
			FrkAGqHJ49wF7moJ38.setMapFollowParent(obj);
			FrkAGqHJ49wF7moJ38.setMapFollowType(1);
			local YybvDiknVfBfC6m3lvy6s = sq_GetSkillLevel(obj, 138);
			local H80Jrjjg5R4OJkfOtPqE5OM = CNSquirrelAppendage.sq_AppendAppendage(FrkAGqHJ49wF7moJ38, FrkAGqHJ49wF7moJ38, 138, true, "character/mage/summonheilrom/ap_summonheilrom.nut", false);
			H80Jrjjg5R4OJkfOtPqE5OM.sq_SetValidTime(obj.sq_GetLevelData(138, 0, YybvDiknVfBfC6m3lvy6s));
			CNSquirrelAppendage.sq_Append(H80Jrjjg5R4OJkfOtPqE5OM, FrkAGqHJ49wF7moJ38, FrkAGqHJ49wF7moJ38, false);

			H80Jrjjg5R4OJkfOtPqE5OM.getVar("sqrChr").clear_obj_vector();
			H80Jrjjg5R4OJkfOtPqE5OM.getVar("sqrChr").push_obj_vector(obj);

			H80Jrjjg5R4OJkfOtPqE5OM.getVar("buffPx").clear_timer_vector();
			H80Jrjjg5R4OJkfOtPqE5OM.getVar("buffPx").push_timer_vector();
			local CaYCrno9IM = H80Jrjjg5R4OJkfOtPqE5OM.getVar("buffPx").get_timer_vector(0);
			CaYCrno9IM.setParameter(500, -1);
			CaYCrno9IM.resetInstant(0);
			break;
		case 2:
			local FrkAGqHJ49wF7moJ38 = sq_GetCNRDObjectToActiveObject(sq_GetObject(obj, reciveData.readDword(), reciveData.readDword()));
			if (!FrkAGqHJ49wF7moJ38 || FrkAGqHJ49wF7moJ38.isDead()) return;
			local YybvDiknVfBfC6m3lvy6s = sq_GetSkillLevel(obj, 138);
			sq_SendMessage(FrkAGqHJ49wF7moJ38, OBJECT_MESSAGE_GHOST, 1, 0);
			sq_PostDelayedMessage(FrkAGqHJ49wF7moJ38, OBJECT_MESSAGE_GHOST, 0, 0, obj.sq_GetLevelData(138, 1, YybvDiknVfBfC6m3lvy6s));
			break;
		}
		break;
	case 139:
		local OmUe5zbG63a = reciveData.readWord();
		switch (OmUe5zbG63a) {
		case 1:
			local FrkAGqHJ49wF7moJ38 = sq_GetCNRDObjectToActiveObject(sq_GetObject(obj, reciveData.readDword(), reciveData.readDword()));
			if (!FrkAGqHJ49wF7moJ38 || FrkAGqHJ49wF7moJ38.isDead()) return;
			FrkAGqHJ49wF7moJ38.setMapFollowParent(obj);
			FrkAGqHJ49wF7moJ38.setMapFollowType(1);
			local H80Jrjjg5R4OJkfOtPqE5OM = CNSquirrelAppendage.sq_AppendAppendage(FrkAGqHJ49wF7moJ38, FrkAGqHJ49wF7moJ38, 139, true, "character/mage/summonramos/ap_summonramos.nut", false);
			CNSquirrelAppendage.sq_Append(H80Jrjjg5R4OJkfOtPqE5OM, FrkAGqHJ49wF7moJ38, FrkAGqHJ49wF7moJ38, false);
			setStartInfo_appendage_mage_summonramos(obj, H80Jrjjg5R4OJkfOtPqE5OM);
			break;
		}
		break;
	}
};

function getOverturnAni_Mage(Dcju7DIrGgeVQRdU) {
	if (!Dcju7DIrGgeVQRdU) return null;
	local IQqclgIlljkktMlhHPREHVW = null;
	if (CNSquirrelAppendage.sq_IsAppendAppendage(Dcju7DIrGgeVQRdU, "character/mage/avatar/ap_avatar.nut") == true) {
		IQqclgIlljkktMlhHPREHVW = setCurrentAnimationMap_avatar_eff(Dcju7DIrGgeVQRdU, "Overturn", false);
	}
	else {
		IQqclgIlljkktMlhHPREHVW = Dcju7DIrGgeVQRdU.sq_GetOverturnAni();
	}
	return IQqclgIlljkktMlhHPREHVW;
};

function getThrowChargeAni_Mage(obj, index) {
	if (!obj) return null;
	local ani = null;
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		switch (index) {
		case 0:
			ani = setCurrentAnimationMap_avatar_eff(obj, "OneHandThrow1", false);
			break;
		case 1:
			ani = setCurrentAnimationMap_avatar_eff(obj, "TwoHandThrow1", false);
			break;
		case 2:
			ani = setCurrentAnimationMap_avatar_eff(obj, "Cast1", false);
			break;
		case 3:
			ani = setCurrentAnimationMap_avatar_eff(obj, "Wink1", false);
			break;
		}
	}
	else if (isDollState(obj)) {
		ani = obj.sq_GetCustomAni(CUSTOM_ANI_DOLL_MAD_BUFF);
	}
	else {
		ani = obj.sq_GetThrowChargeAni(index);
	}
	return ani;
};

function getThrowShootAni_Mage(WdlxwJi181Zy2vOk3XFh1hGo, ZbjiQddQrSmTLEIElssi) {
	if (!WdlxwJi181Zy2vOk3XFh1hGo) return null;
	local nZcd7C6FB7mqGaoKAmT = null;
	if (CNSquirrelAppendage.sq_IsAppendAppendage(WdlxwJi181Zy2vOk3XFh1hGo, "character/mage/avatar/ap_avatar.nut") == true) {
		switch (ZbjiQddQrSmTLEIElssi) {
		case 0:
			nZcd7C6FB7mqGaoKAmT = setCurrentAnimationMap_avatar_eff(WdlxwJi181Zy2vOk3XFh1hGo, "OneHandThrow2", false);
			break;
		case 1:
			nZcd7C6FB7mqGaoKAmT = setCurrentAnimationMap_avatar_eff(WdlxwJi181Zy2vOk3XFh1hGo, "TwoHandThrow2", false);
			break;
		case 2:
			nZcd7C6FB7mqGaoKAmT = setCurrentAnimationMap_avatar_eff(WdlxwJi181Zy2vOk3XFh1hGo, "Cast2", false);
			break;
		case 3:
			nZcd7C6FB7mqGaoKAmT = setCurrentAnimationMap_avatar_eff(WdlxwJi181Zy2vOk3XFh1hGo, "Wink2", false);
			break;
		}
	}
	else {
		nZcd7C6FB7mqGaoKAmT = WdlxwJi181Zy2vOk3XFh1hGo.sq_GetThrowShootAni(ZbjiQddQrSmTLEIElssi);
	}
	return nZcd7C6FB7mqGaoKAmT;
};

function moveCharge(obj) {
	if (!obj) return;
	local movecast_level = sq_GetSkillLevel(obj, 38);
	if (movecast_level < 1) return;
	local time = obj.getVar("time").getInt(0); //ÙÒ?ÓðüòÔðãÁÊàîÜÛ°Ûö£¬á¶ì¤ö¦îÏåÆñ¾üÀ?£¬Ó×ÍªãÁÐï
	time = time + 1;
	obj.getVar("time").setInt(0, time);
	//üòÔðñ¦øöÕÎãùúÞì¹ÔÑ
	local x = obj.getXPos();
	local x1 = x;
	local y = obj.getYPos();
	local y1 = y;
	local z = obj.getZPos();
	//îñõøãÁÜÁò¥îÜäÎËõ
	local dashKey = obj.getVar("dashKey").getInt(0);
	if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL)) {
		//ôÕÊ¥Û°ú¾äÎËõîÜøöãÛ£¬éÄÕÎ÷÷Ó¨ÙÒìòù¼äÎËõãÁÐåß¾stay.ani
		obj.getVar("rightKey").setInt(0, OPTION_HOTKEY_MOVE_RIGHT);
		obj.setCurrentDirection(ENUM_DIRECTION_RIGHT); //àâöÇìÑÚªðÈú¾
		//éÄÕÎ÷÷Ó¨îñõø
		if (isDash(obj, OPTION_HOTKEY_MOVE_RIGHT, time) || dashKey == OPTION_HOTKEY_MOVE_RIGHT) {
			obj.sq_SetCurrentAnimation(145); //dash.ani
			obj.sq_SetAnimationSpeedRate(obj.sq_GetCurrentAni(), 130.0);
			x1 = x1 + 3;
		} else {
			obj.sq_SetCurrentAnimation(144); //move.ani
			obj.sq_SetAnimationSpeedRate(obj.sq_GetCurrentAni(), 130.0);
			x1 = x1 + 1;
		}
		//ôÕÊ¥äÎËõûúäÎù»îÜãÁÊà£¬éÄÕÎ÷÷Ó¨îñõø
		obj.getVar("keydown").setInt(0, OPTION_HOTKEY_MOVE_RIGHT);
		obj.getVar("keydownTime").setInt(0, time);
	}
	if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL)) {
		obj.getVar("leftKey").setInt(0, OPTION_HOTKEY_MOVE_LEFT);
		obj.setCurrentDirection(ENUM_DIRECTION_LEFT);
		if (isDash(obj, OPTION_HOTKEY_MOVE_LEFT, time) || dashKey == OPTION_HOTKEY_MOVE_LEFT) {
			obj.sq_SetCurrentAnimation(145);
			obj.sq_SetAnimationSpeedRate(obj.sq_GetCurrentAni(), 130.0);
			x1 = x1 - 3;
		} else {
			obj.sq_SetCurrentAnimation(144);
			obj.sq_SetAnimationSpeedRate(obj.sq_GetCurrentAni(), 130.0);
			x1 = x1 - 1;
		}

		obj.getVar("keydown").setInt(0, OPTION_HOTKEY_MOVE_LEFT);
		obj.getVar("keydownTime").setInt(0, time);
	}
	if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL)) {
		obj.getVar("upKey").setInt(0, OPTION_HOTKEY_MOVE_UP);
		//äÎß¾ù»ËõÜôç¯úÂîñõø
		if (!obj.isCurrentCutomAniIndex(145)) {
			obj.sq_SetCurrentAnimation(144);
			obj.sq_SetAnimationSpeedRate(obj.sq_GetCurrentAni(), 130.0);
		}
		y1 = y1 - 1;
	}
	if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL)) {
		obj.getVar("downKey").setInt(0, OPTION_HOTKEY_MOVE_DOWN);
		if (!obj.isCurrentCutomAniIndex(145)) {
			obj.sq_SetCurrentAnimation(144);
			obj.sq_SetAnimationSpeedRate(obj.sq_GetCurrentAni(), 130.0);
		}
		y1 = y1 + 1;
	}
	if (sq_IsKeyUp(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL)) {
		//áæÓüäÎËõãÁÐåÝ·?4£¬Û°ú¾Ëõï¿Öõ0123
		obj.getVar("rightKey").setInt(0, 4);
		//áæÓüäÎËõãÁ?ð¶îñõøîÜäÎËõ
		removeDashKey(obj, OPTION_HOTKEY_MOVE_RIGHT);
	}
	if (sq_IsKeyUp(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL)) {
		obj.getVar("leftKey").setInt(0, 4);
		removeDashKey(obj, OPTION_HOTKEY_MOVE_LEFT);
	}
	if (sq_IsKeyUp(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL)) {
		obj.getVar("upKey").setInt(0, 4);
	}
	if (sq_IsKeyUp(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL)) {
		obj.getVar("downKey").setInt(0, 4);
	}
	//Û°ú¾ËõÔ´ãÀ4ý¨Ðåstay.ani
	if (obj.getVar("rightKey").getInt(0) == 4 && obj.getVar("leftKey").getInt(0) == 4 && obj.getVar("upKey").getInt(0) == 4 && obj.getVar("downKey").getInt(0) == 4) {

		if (sq_GetCurrentAnimation(obj).isLoop()) {
			obj.sq_SetCurrentAnimation(146);
			obj.sq_SetAnimationSpeedRate(obj.sq_GetCurrentAni(), 110.0);
		}

	}
	//ìÑÚªÐÆËàñ¦øöì¹ÔÑ
	sq_MoveToNearMovablePos(obj, x1, y1, z, x, y, z, 1, 1, 1);
}

//÷÷Ó¨ãÀÜúõºÛ¡îñõø
function isDash(obj, keyNum, time) {
	local downKey = obj.getVar("keydown").getInt(0);
	local downKeyTime = obj.getVar("keydownTime").getInt(0);
	//ÛÉð¶Óüôøã·??0îÜï×üÏ
	if (downKeyTime <= 1) {
		return false;
	}
	//ì×?ÜÁò¥äÎËõüåìéòÁõºÛ¡keydown£¬á¶ì¤ÊàÌ°é©ÓÞéÍ1
	if (downKey == keyNum && time - downKeyTime > 1 && time - downKeyTime < 20) {
		obj.getVar("dashKey").setInt(0, keyNum);
		obj.sq_PlaySound("WIZ_DASH");
		return true;
	}
	return false;
}
//?ð¶ÜÁò¥îñõøîÜäÎËõ
function removeDashKey(obj, keyNum) {
	local dashKey = obj.getVar("dashKey").getInt(0);
	if (dashKey == keyNum) {
		obj.getVar("dashKey").setInt(0, 4);
	}
}

function getBoolByPossibility(prob, baseNum)
{
	local randomNum = sq_getRandom(0, baseNum);
	local isTrue;

	if(randomNum <= prob)
	{
		isTrue = true;
	}

	else if(randomNum > prob)
	{
		isTrue = false;
	}

	return isTrue;
}

function setHalloweenBusterPotential(obj, state, datas)
{
	if(obj.getCurrentSkillIndex()!=27)
		return;
	local skillLevel = obj.sq_GetSkillLevel(167);
	if(isElementalPotential(obj) && getBoolByPossibility(sq_GetLevelData(obj, 167, 1, skillLevel) , 1000) ){
		local substate0 = obj.sq_GetVectorData(datas, 0);
		local substate1 = obj.sq_GetVectorData(datas, 1);
		local substate2 = obj.sq_GetVectorData(datas, 2);
		local substate3 = obj.sq_GetVectorData(datas, 3);
		local substate4 = obj.sq_GetVectorData(datas, 4);
		local substate5 = obj.sq_GetVectorData(datas, 5);
		local substate6 = obj.sq_GetVectorData(datas, 6);
		local substate7 = obj.sq_GetVectorData(datas, 7);
		local substate8 = obj.sq_GetVectorData(datas, 8);
		if(substate0 ==0 && substate1==0 && substate2==27 &&  state==13)
		{
			sq_IntVectorClear(datas);
			sq_IntVectorPush(datas, 0);
			sq_IntVectorPush(datas, 0);
			sq_IntVectorPush(datas, 27);
			sq_IntVectorPush(datas, substate3);
			sq_IntVectorPush(datas, 1200);
			sq_IntVectorPush(datas, substate5);
			sq_IntVectorPush(datas, substate6);
			sq_IntVectorPush(datas, substate7);
			sq_IntVectorPush(datas, substate8);
		}
	}
}

function setState_Mage(obj, state, datas, isResetTimer) {
	setState_AllGrowJob(obj, state, datas, isResetTimer);
	return;
}

function isDistanceOfTarget(obj,target,distance)
{
    local objX = obj.getXPos();
    local objY = obj.getYPos();
    local tarX = target.getXPos();
    local tarY = target.getYPos();

    local lenX = objX - tarX;
    local lenY = objY - tarY;

    if (lenX * lenX + lenY * lenY <= distance * distance)
        return true;
    return false;

}
