
function checkExecutableSkill_GluttonyVomit(obj) {
	if (!obj) return false;

	local isUse = obj.sq_IsUseSkill(SKILL_GLUTTONYVOMIT);

	if (isUse) {
		obj.getVar("damaGluttonyVomit").clear_obj_vector();
		obj.getVar("flagGluttonyVomit").clear_vector();
		obj.getVar("flagGluttonyVomit").push_vector(0);
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);
		obj.sq_IsEnterSkillLastKeyUnits(SKILL_GLUTTONYVOMIT);
		obj.addSetStatePacket(STATE_GLUTTONYVOMIT, pIntVec, STATE_PRIORITY_FORCE, false, "");
	}
}

function checkCommandEnable_GluttonyVomit(obj) {

	return true;
}



function onSetState_GluttonyVomit(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
	switch (state) {
		case 0:
			sq_StartDrawCastGauge(obj, sq_GetCastTime(obj, SKILL_GLUTTONYVOMIT, sq_GetSkillLevel(obj, SKILL_GLUTTONYVOMIT)), true);
			local ani = obj.getVar().GetAnimationMap("Seducer189", "Character/Priest/Seducer/ATAnimation/atgluttonyvomit_casting_body.ani");
			obj.setCurrentAnimation(ani);
			
			obj.sq_PlaySound("GLUTTONY_CAST");
			obj.getVar("GluttonyVomithitTime").clear_vector();
			obj.getVar("GluttonyVomithitTime").push_vector(0);
			local skillLevel = sq_GetSkillLevel(obj, SKILL_GLUTTONYVOMIT);
			local multiHit = sq_GetLevelData(obj, SKILL_GLUTTONYVOMIT, 1, skillLevel);
			obj.getVar("GluttonyVomit").clear_vector();
			obj.getVar("GluttonyVomit").push_vector(0);
			obj.getVar("GluttonyVomit").push_vector(multiHit);

			if (!Seducer(obj)){
				obj.sq_PlaySound("PW_GLUTTONY_01");
			}
			else{
				obj.sq_PlaySound("PW_GLUTTONY_DM_01");
			}
			break;
		case 1:
			local ani = obj.getVar().GetAnimationMap("Seducer190", "Character/Priest/Seducer/ATAnimation/atgluttonyvomit_att_body.ani");
			obj.setCurrentAnimation(ani);
			if (Seducer(obj)){
				obj.sq_PlaySound("PW_GLUTTONY_DM_02");
			}
			break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}


function onEndCurrentAni_GluttonyVomit(obj) {
	if (!obj) return;
	local state = obj.getSkillSubState();

	switch (state) {
		case 0:
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 1);

			obj.addSetStatePacket(STATE_GLUTTONYVOMIT, pIntVec, STATE_PRIORITY_FORCE, false, "");

			break;
		case 1:
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
			break;
	}
}


function onProc_GluttonyVomit(obj) {
	if (!obj) return;

	local state = obj.getSkillSubState(); //��������������SUB����
	local pAni = obj.sq_GetCurrentAni();
	local currentT = sq_GetCurrentTime(pAni);
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);


	switch (state) {
		case 0:
			local pAni = obj.sq_GetCurrentAni();
			local currentT = sq_GetCurrentTime(pAni);
			local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);

			local bDownKey = obj.isDownSkillLastKey();
			local stateTimer = obj.sq_GetStateTimer();
			local grabMaxTime = obj.sq_GetIntData(SKILL_GLUTTONYVOMIT, 4);
			if (!bDownKey || stateTimer >= grabMaxTime) {
				local pIntVec = sq_GetGlobalIntVector();
				sq_IntVectorClear(pIntVec);
				sq_IntVectorPush(pIntVec, 1);

				obj.addSetStatePacket(STATE_GLUTTONYVOMIT, pIntVec, STATE_PRIORITY_FORCE, false, "");
			}


			local encodeT1 = obj.getVar("GluttonyVomithitTime").get_vector(0);

			local curShoot = obj.getVar("GluttonyVomit").get_vector(0);
			local maxShoot = obj.getVar("GluttonyVomit").get_vector(1);

			if (currentT - encodeT1 >= obj.sq_GetIntData(SKILL_GLUTTONYVOMIT, 0)) {

				obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_ATGLUTTONYVOMITCAST);
				local damage = obj.sq_GetBonusRateWithPassive(SKILL_GLUTTONYVOMIT, -1, 0, 1.0);
				obj.sq_SetCurrentAttackBonusRate(damage);


				obj.resetHitObjectList();
				obj.getVar("GluttonyVomithitTime").set_vector(0, currentT);

				local curShoot = obj.getVar("GluttonyVomit").get_vector(0);
				obj.getVar("GluttonyVomit").set_vector(0, curShoot + 1);
			}
			if (obj.getVar("damaGluttonyVomit").get_obj_vector_size() > 0 && obj.getVar("flagGluttonyVomit").get_vector(0) == 0) {
				obj.getVar("flagGluttonyVomit").set_vector(0, 1);
				obj.sq_StartWrite();
				obj.sq_WriteDword(17);
				obj.sq_WriteDword(obj.sq_GetIntData(SKILL_FIRSTPRANA, 1));
				obj.sq_SendCreatePassiveObjectPacket(24384, 0, 0, 0, 0);
			}
			break;
	}
}


function onKeyFrameFlag_GluttonyVomit(obj, flagIndex) //����μ��������
{
	if (!obj) return;


	local state = obj.getSkillSubState(); //����������sub state����

	switch (state) {
		case 1:
			if (flagIndex == 0) {
				sq_flashScreen(obj, 0, 120, 0, 178, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
			} else if (flagIndex == 1) {
				obj.sq_SetShake(obj, 10, 420);
				obj.sq_StartWrite();
				obj.sq_WriteDword(13);
				obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(SKILL_GLUTTONYVOMIT, -1, 2, 1.0));
				obj.sq_WriteDword(obj.sq_GetIntData(SKILL_GLUTTONYVOMIT, 11));
				obj.sq_SendCreatePassiveObjectPacket(24384, 0, 0, 0, 100);
			}
			break;
	}
	return true;
}


function onAttack_GluttonyVomit(obj, damager, boundingBox, isStuck) {
	if (!obj)
		return false;
	local state = obj.getSkillSubState();

	switch (state) {
		case 0:
			if (damager && damager.isObjectType(OBJECTTYPE_ACTIVE))
				obj.getVar("damaGluttonyVomit").push_obj_vector(damager);
			if (!sq_IsFixture(damager)) {
				damager.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
				local hp = obj.sq_GetIntData(SKILL_GLUTTONYVOMIT, 2);
				local maxhp = obj.getHpMax();
				obj.setHp(obj.getHp() + maxhp * hp / 1000, null, true);
				obj.getVar("damaGluttonyVomit").push_obj_vector(damager);
			}
			break;
	}
}

function onEndState_GluttonyVomit(obj, new_state) {
	if (new_state != STATE_GLUTTONYVOMIT) {
		sq_EndDrawCastGauge(obj);
	}
}