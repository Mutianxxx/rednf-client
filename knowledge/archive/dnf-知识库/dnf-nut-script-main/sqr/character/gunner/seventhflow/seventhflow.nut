function checkExecutableSkill_seventhflow(obj)
{
	if(!obj) return false; 
	local UseSkill = obj.sq_IsUseSkill(SKILL_SEVENTHFLOW); 
	if(UseSkill) 
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0); 
		obj.sq_AddSetStatePacket(STATE_SEVENTHFLOW, STATE_PRIORITY_USER, true); 
		return true; 
	}
	return false; 
}

 
function checkCommandEnable_seventhflow(obj)
{
	if(!obj) return false; 
	local state = obj.sq_GetState(); 
	if(state == STATE_STAND) 
		return true; 
	if(state == STATE_ATTACK) 
	{
		return obj.sq_IsCommandEnable(SKILL_SEVENTHFLOW); 
	}
	return true; 
}

function onSetState_seventhflow(obj, state, datas, isResetTimer)
{
	if(!obj) return; 
	local substate0 = obj.sq_GetVectorData(datas, 0); 
	obj.setSkillSubState(substate0); 
	local substate1 = obj.sq_GetVectorData(datas, 1); 
	if(substate1 != -1)obj.setDirection(substate1); 
	local substate2 = obj.sq_GetVectorData(datas, 2); 
	obj.getVar("state").clear_vector(); 
	obj.getVar("state").push_vector(substate2); 
	
	if(substate2 == -1)
	obj.sq_StopMove(); 
	obj.getVar("move").clear_vector(); 
	obj.getVar("move").push_vector(obj.getXPos()); 
	obj.getVar("move").push_vector(obj.getYPos()); 

	switch(substate0)
	{
		case 0: 
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SEVENTHFLOWCAST); 
			local skilllevel = sq_GetSkillLevel(obj, SKILL_SEVENTHFLOW); 
			obj.getVar().clear_vector(); 
			obj.getVar().push_vector(100); 
			obj.getVar().push_vector(sq_GetLevelData(obj, SKILL_SEVENTHFLOW, 2, skilllevel)); 
			obj.getVar().push_vector(sq_GetLevelData(obj, SKILL_SEVENTHFLOW, 3, skilllevel)); 
		break;
		case 1: 
			switch(substate2)
			{
				case 0: 
					obj.sq_SetCurrentAnimation(CUSTOM_ANI_SEVENTHFLOW1DASH); 
					obj.getVar("move").push_vector(100); 
					obj.getVar("move").push_vector(-100); 
					
					sq_CreateParticle("character/gunner/effect/animation/seventhflow/dust_particle/dust.ptl", obj, 0, 0, 0, true, 250, 0, 25);
				break;
				case 1: 
					obj.sq_SetCurrentAnimation(CUSTOM_ANI_SEVENTHFLOW1SHOOT); 
				break;
			}
		break;
		case 2: 
			switch(substate2)
			{
				case 0: 
					obj.sq_SetCurrentAnimation(CUSTOM_ANI_SEVENTHFLOW2DASH); 
					obj.getVar("move").push_vector(100); 
					obj.getVar("move").push_vector(200); 
				break;
				case 1: 
					obj.sq_SetCurrentAnimation(CUSTOM_ANI_SEVENTHFLOW2SHOOT); 
				break;
			}
		break;
		case 3: 
			switch(substate2)
			{
				case 0: 
					obj.sq_SetCurrentAnimation(CUSTOM_ANI_SEVENTHFLOW3DASH); 
					obj.getVar("move").push_vector(100); 
					obj.getVar("move").push_vector(-200); 
				break;
				case 1: 
					obj.sq_SetCurrentAnimation(CUSTOM_ANI_SEVENTHFLOW3SHOOT); 
				break;
			}
		break;
		case 4: 
			switch(substate2)
			{
				case 0: 
					obj.sq_SetCurrentAnimation(CUSTOM_ANI_SEVENTHFLOW4DASH); 
					obj.getVar("move").push_vector(100); 
					obj.getVar("move").push_vector(150); 
				break;
				case 1: 
					obj.sq_SetCurrentAnimation(CUSTOM_ANI_SEVENTHFLOW4SHOOT); 
				break;
			}
		break;
		case 5: 
			switch(substate2)
			{
				case 0: 
					obj.sq_SetCurrentAnimation(CUSTOM_ANI_SEVENTHFLOW5DASH); 
					obj.getVar("move").push_vector(100); 
					obj.getVar("move").push_vector(-150); 
				break;
				case 1: 
					obj.sq_SetCurrentAnimation(CUSTOM_ANI_SEVENTHFLOW5SHOOT); 
				break;
			}
		break;
		case 6: 
			switch(substate2)
			{
				case 0: 
					obj.sq_SetCurrentAnimation(CUSTOM_ANI_SEVENTHFLOW6DASH); 
					obj.getVar("move").push_vector(25); 
					obj.getVar("move").push_vector(20); 
				break;
				case 1: 
					obj.sq_SetCurrentAnimation(CUSTOM_ANI_SEVENTHFLOW6SHOOT); 
					obj.getVar("move").push_vector(75); 
					obj.getVar("move").push_vector(55); 
					if(obj.sq_IsMyControlObject())
					sq_flashScreen(obj, 0, obj.sq_GetDelaySum(), 200, 120, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
				break;
			}
		break;
		case 7: 
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SEVENTHFLOWLAST); 
			
			sq_RemoveParticle("character/gunner/effect/animation/seventhflow/dust_particle/dust.ptl", obj); 
		break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

 
function onKeyFrameFlag_seventhflow(obj, flagIndex)
{
	if(!obj) return false;
	local substate = obj.getSkillSubState(); 
	switch(substate)
	{
		case 0: 
			if(obj.sq_IsMyControlObject())
			if(flagIndex == 1) 
			sq_flashScreen(obj, 0, 60, 0, 255, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
			else if(flagIndex == 2) 
			sq_flashScreen(obj, 0, 60, 180, 255, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		break;
		case 1: 
		case 2: 
		case 3: 
		case 4: 
		case 5: 
			if(flagIndex == 1)
			if(obj.sq_IsMyControlObject())
			{
				sq_SetMyShake(obj, 2, 80); 
				sq_flashScreen(obj, 0, 0, 80, 70, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
				local particleCreater = obj.getVar("seventhflow1").GetparticleCreaterMap("seventhflow1", "character/gunner/particle/deadlyapproach.ptl", obj);
				particleCreater.Restart(0);
				particleCreater.SetPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(),0),obj.getYPos()-1, obj.getZPos());
				sq_AddParticleObject(obj, particleCreater); 
			}
		break;
		case 6: 
			local angle = 0.0; 
			switch(flagIndex)
			{
				case 1: angle = 2.6179799999999998; break;
				case 2: angle = 2.094384; break;
				case 3: angle = 1.5707879999999999; break;
				case 4: angle = 1.047192; break;
				case 5: angle = 0.8726599999999999; break;
			}
			
			local AddDraw = sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/seventhflow/6/6_shoot_2.ani", 0, 0, 120);
			sq_SetCustomRotate(AddDraw, angle); 
			
			if(obj.sq_IsMyControlObject())
			{
				sq_SetMyShake(obj, 5, 80); 
				sq_flashScreen(obj, 0, 0, 30, 100, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
				local particleCreater = obj.getVar("seventhflow1").GetparticleCreaterMap("seventhflow1", "character/gunner/particle/deadlyapproach.ptl", obj);
				particleCreater.Restart(0);
				particleCreater.SetPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(),0),obj.getYPos()-1, obj.getZPos());
				sq_AddParticleObject(obj, particleCreater); 
			}
		break;
		case 7: 
			if(flagIndex == 2)
			if(obj.sq_IsMyControlObject())
			{
				sq_flashScreen(obj, 0, 150, 200, 120, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
				local particleCreater = obj.getVar("seventhflow7").GetparticleCreaterMap("seventhflow7", "character/gunner/particle/deadlyapproach.ptl", obj);
				particleCreater.Restart(0);
				particleCreater.SetPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(),0),obj.getYPos()-1, obj.getZPos());
				sq_AddParticleObject(obj, particleCreater); 
			}
		break;
	}
	return true;
}

 
function onProc_seventhflow(obj)
{
	if(!obj) return;
	local substate = obj.getSkillSubState(); 
	local Count = obj.getMyPassiveObjectCount(22001);
	for(local i=0;i<Count;++i)
	{
		if (substate < 7)
		{
			local object = obj.getMyPassiveObject(22001, i);
			local objecttt = obj.getVar("seventhflow1").is_obj_vector(object);
			if(object && objecttt)
			{
				setCurrentAnimationFromCutomIndex(object, 7+substate);
				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SEVENTHFLOW, SKILL_SEVENTHFLOW, 0, 1.0);
				local attackInfo = sq_GetCurrentAttackInfo(object);
				sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
			}
		}
		else if (substate == 7)
		{
			local object = obj.getMyPassiveObject(22001, i);
			local objecttt = obj.getVar("seventhflow7").is_obj_vector(object);
			if(object && objecttt)
			{
				setCurrentAnimationFromCutomIndex(object, 7+substate);
				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SEVENTHFLOW, SKILL_SEVENTHFLOW, 1, 1.0);
				local attackInfo = sq_GetCurrentAttackInfo(object);
				sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
				sq_SetCurrentAttackeDamageAct(attackInfo, 2); 
				sq_SetCurrentAttacknUpForce(attackInfo, 300); 
				sq_SetCurrentAttacknBackForce(attackInfo, 300); 
			}
		}
	}
	if(obj.getVar("move").size_vector() != 4) return; 
	local ani = obj.getCurrentAnimation(); 
	local anitime = sq_GetCurrentTime(ani); 
	local delay = ani.getDelaySum(false); 
	local move = obj.getVar("move"); 
	local DistanceX = sq_GetDistancePos(move.get_vector(0), obj.getDirection(), 
	sq_GetUniformVelocity(0, move.get_vector(2), anitime, delay));
	local DistanceY = move.get_vector(1) + sq_GetUniformVelocity(0, move.get_vector(3), anitime, delay);
	if(obj.isMovablePos(DistanceX, DistanceY)) 
	{
		sq_setCurrentAxisPos(obj, 0, DistanceX); 
		sq_setCurrentAxisPos(obj, 1, DistanceY); 
	}else
	obj.getVar("move").clear_vector(); 
}

function onCreateObject_seventhflow(obj, createObject)
{
	if(!obj) return;
	local state = obj.sq_GetState();
	local substate = obj.getSkillSubState(); 
	if(state == STATE_SEVENTHFLOW)
	{
		local Object = sq_GetCNRDObjectToCollisionObject(createObject); 
		if(Object && Object.getCollisionObjectIndex() == 22001)
		{
			if (substate < 7)
			{
				obj.getVar("seventhflow1").push_obj_vector(Object);
			}
			local objecttt = obj.getVar("seventhflow1").is_obj_vector(Object);
			if (substate == 7 && !objecttt)
			{
				obj.getVar("seventhflow7").push_obj_vector(Object);
			}
		}
	}
}
 
function onProcCon_seventhflow(obj)
{
	if(!obj) return;
	sq_SetKeyxEnable(obj, E_DASH_COMMANDS_1, true); 
	sq_SetKeyxEnable(obj, E_DASH_COMMANDS_2, true); 
	if(sq_IsEnterCommand(obj, E_DASH_COMMANDS_1) || sq_IsEnterCommand(obj, E_DASH_COMMANDS_2))
	{
		local skillIndex = obj.getVar().get_vector(0); 
		if(skillIndex < obj.getVar().get_vector(2))
		{
			sq_BinaryStartWrite();
			sq_BinaryWriteWord(1);
			sq_BinaryWriteDword(skillIndex + obj.getVar().get_vector(1)); 
			sq_SendChangeSkillEffectPacket(obj, SKILL_SEVENTHFLOW); 
		}
	}
}

function onChangeSkillEffect_seventhflow(obj, skillIndex, reciveData)
{
	if(!obj) return;
	local statesub = obj.getVar("state").get_vector(0); 
	if(statesub == 0 && skillIndex == SKILL_SEVENTHFLOW)
	{
		local open = reciveData.readWord(); 
		switch(open)
		{
			case 1:
			local speed = reciveData.readDword(); 
			obj.sq_SetStaticSpeedInfo(0, 0, 0, (1000 * speed/ 100.0).tointeger(), 0.0, 0.0); 
			obj.getVar().set_vector(0, speed); 
			break;
		}
	}
}

 
function onEndCurrentAni_seventhflow(obj)
{
	if(!obj) return;
	if(!obj.sq_IsMyControlObject()) return;
	local substate = obj.getSkillSubState(); 
	switch(substate)
	{
		case 0: 
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1); 
			obj.sq_IntVectPush(onGetMoveDirection_seventhflow(obj)); 
			obj.sq_IntVectPush(0); 
			obj.sq_AddSetStatePacket(STATE_SEVENTHFLOW, STATE_PRIORITY_USER, true); 
		break;
		case 7: 
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); 
		break;
		default: 
			local amznhsssceI = -1; 
			local Direction = -1; 
			
			switch(obj.getVar("state").get_vector(0))
			{
				case 0: 
					amznhsssceI = 1; 
				break;
				case 1: 
					if(substate != 6) 
					amznhsssceI = 0; 
					Direction = onGetMoveDirection_seventhflow(obj); 
					substate += 1; 
				break;
			}
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(substate); 
			obj.sq_IntVectPush(Direction); 
			obj.sq_IntVectPush(amznhsssceI); 
			obj.sq_AddSetStatePacket(STATE_SEVENTHFLOW, STATE_PRIORITY_USER, true); 
		break;
	}
}

function onEndState_seventhflow(obj, new_state)
{
	if(!obj) return;
	if(new_state != STATE_SEVENTHFLOW)
	sq_RemoveParticle("character/gunner/effect/animation/seventhflow/dust_particle/dust.ptl", obj); 
}

 
function onGetMoveDirection_seventhflow(obj)
{
	if(!obj) return;
	local new_state = obj.getDirection(); 
	if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL)) 
		new_state = ENUM_DIRECTION_LEFT; 
	else if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL)) 
		new_state = ENUM_DIRECTION_RIGHT; 
	return new_state;
}
