function checkExecutableSkill_gonewiththepetal(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_GONEWITHTHEPETAL);
	GetFindMapArea_Enemy(obj, "Enemy_C34", -500, 500, 200);
	local damager = obj.getVar("Enemy_C34").get_obj_vector(0);
	local state = obj.sq_GetState();
	if (isUse)
	{
		if (state == 0 || state == 8 || state == 14)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_GONEWITHTHEPETAL, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}
		else if (state == 6 || state == 7)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(2);
			obj.sq_AddSetStatePacket(STATE_GONEWITHTHEPETAL, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}
	}
	return false;
}

function checkCommandEnable_gonewiththepetal(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	GetFindMapArea_Enemy(obj, "Enemy_C34", -500, 500, 200);
	local damager = obj.getVar("Enemy_C34").get_obj_vector(0);
	if (!damager)
	return false;
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_gonewiththepetal(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	local sq_var = obj.getVar();
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);

	obj.getVar("pos").clear_vector();
	obj.getVar("pos").push_vector(x);
	obj.getVar("pos").push_vector(y);
	obj.getVar("pos").push_vector(z);

	if(substate == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_GoneWithThePetalReady_Body);
		ATSwordman_Als_Ani(obj,"character/swordman/effect/animation/3rd/atgonewiththepetal/rangecheck_01.ani", 0, 0, 0, 0, 100, 1, 1.0);
	}
	else if(substate == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_GoneWithThePetalAttack_Body);
		obj.sq_SetShake(obj,5,150);
		sq_flashScreen(obj, 0, 0, 50, 185, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
		sq_flashScreen(obj, 10, 85, 100, 185, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_GoneWithThePetalAttack);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_GONEWITHTHEPETAL , -1, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);

		GetFindMapArea_Enemy(obj, "Enemy_C34", -500, 500, 200);
		local damager = obj.getVar("Enemy_C34").get_obj_vector(0);
		if(damager)
		{
			local x = sq_GetXPos(damager);
			local y = sq_GetYPos(damager);
			local z = sq_GetZPos(damager);

			obj.getVar("pos").clear_vector();
			obj.getVar("pos").push_vector(x);
			obj.getVar("pos").push_vector(y);
			obj.getVar("pos").push_vector(z);

			local Xpos = sq_GetDistancePos(x, obj.getDirection(), -85);
			obj.sq_SetCurrentPos(obj, Xpos, y, 0);
		}
	}
	else if(substate == 2)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_GoneWithThePetalJumpReady_Body);
	}
	else if(substate == 3)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_GoneWithThePetalJumpAttack_Body);
	}
}


function onEndState_gonewiththepetal(obj, newState)
{
	if(!obj) return;
	local sq_var = obj.getVar();
	if(newState != STATE_GONEWITHTHEPETAL)
	{
		obj.getVar("Enemy_C34").clear_obj_vector();
	}
}

function onProc_gonewiththepetal(obj)
{
	local substate = obj.getSkillSubState();
	obj.setCustomOutline(false, sq_RGBA(0, 0, 0, 0), false, 0);
	if(substate == 2)
	{
		local zpos = obj.getVar("pos").get_vector(2);
		sq_setCurrentAxisPos(obj, 2, zpos);
	}
}

function onAttack_gonewiththepetal(obj, damager, boundingBox, isStuck)
{
	if (!obj) return;
	local substate = obj.getSkillSubState();
	if(substate == 1)
	{
		obj.sq_StartWrite();
		obj.sq_WriteDword(8);
		obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);
	}
}


function onEndCurrentAni_gonewiththepetal(obj)
{
	local substate = obj.getSkillSubState();
	local sq_var = obj.getVar();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_GONEWITHTHEPETAL, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 1)
	{
		local posX = obj.getXPos();
		local posY = obj.getYPos();
		local posZ = obj.getZPos();
		if (!obj.isMovablePos(posX, posY))
		{
			sq_MoveToNearMovablePos(obj, posX, posY, 0, posX, posY, posZ, 1000, -1, 3);
		}
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	else if(substate == 2)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_GONEWITHTHEPETAL, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 3)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onKeyFrameFlag_gonewiththepetal(obj,flagIndex)
{
	if(!obj)
		return false;
	if (flagIndex == 1)
	{

	}
	return true;
}
