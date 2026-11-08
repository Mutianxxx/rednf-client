
function checkExecutableSkill_fullbody(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_FULLBODY);
	if (isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_FULLBODY , STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_fullbody(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_fullbody(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 0.8, 0.8);
	if(substate == 0)
	{
		obj.sq_PlaySound("SW_FULLBODY_02_B");
		obj.sq_SetShake(obj,1,100);
		obj.sq_SetXScrollStart(350, 200);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_fullbody_body_start);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_fullbodyattack1);
		local power =  obj.sq_GetPowerWithPassive(SKILL_FULLBODY, STATE_FULLBODY, 0, -1,1.0);
		obj.sq_SetCurrentAttackPower(power);
		
		local fullbody_09 = "character/swordman/effect/animation/3rd/atfullbody/start/fullbody_09.ani";
		ATSwordman_Create(obj,fullbody_09,ENUM_DRAWLAYER_NORMAL,0,0,0,0,100,0,100,"fullbody_09");
		local startsmokeback_00 = "character/swordman/effect/animation/3rd/atfullbody/start/startsmokeback_00.ani";
		ATSwordman_Create(obj,startsmokeback_00,ENUM_DRAWLAYER_NORMAL,0,0,0,0,100,0,100,"startsmokeback_00");
		local startsmokefront_00 = "character/swordman/effect/animation/3rd/atfullbody/start/startsmokefront_00.ani";
		ATSwordman_Create(obj,startsmokefront_00,ENUM_DRAWLAYER_NORMAL,0,0,0,0,100,0,100,"startsmokefront_00");
	}
	if(substate == 1)
	{
		obj.sq_SetShake(obj,2,300);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_fullbody_body_attack);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_fullbodyattack2multihit);
		local power =  obj.sq_GetPowerWithPassive(SKILL_FULLBODY, STATE_FULLBODY, 1, -1,1.0);
		obj.sq_SetCurrentAttackPower(power);

		local attackslashdustfront_00 = "character/swordman/effect/animation/3rd/atfullbody/attack/attackslashdustfront_00.ani";
		ATSwordman_Create(obj,attackslashdustfront_00,ENUM_DRAWLAYER_NORMAL,0,-10,0,0,100,0,100,"attackslashdustfront_00");
		local fullbody_27 = "character/swordman/effect/animation/3rd/atfullbody/attack/fullbody_27.ani";
		ATSwordman_Create(obj,fullbody_27,ENUM_DRAWLAYER_NORMAL,0,-10,0,0,100,0,100,"fullbody_27");
	}
	if(substate == 2)
	{
		obj.sq_SetShake(obj,2,300);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_fullbody_body_attack);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_fullbodyattack2multihit);
		local power =  obj.sq_GetPowerWithPassive(SKILL_FULLBODY, STATE_FULLBODY, 1, -1,1.0);
		obj.sq_SetCurrentAttackPower(power);

		local attackslashdustfront_00 = "character/swordman/effect/animation/3rd/atfullbody/attack/attackslashdustfront_00.ani";
		ATSwordman_Create(obj,attackslashdustfront_00,ENUM_DRAWLAYER_NORMAL,0,-10,0,0,100,0,100,"attackslashdustfront_00");
		local fullbody_27 = "character/swordman/effect/animation/3rd/atfullbody/attack/fullbody_27.ani";
		ATSwordman_Create(obj,fullbody_27,ENUM_DRAWLAYER_NORMAL,0,-10,0,0,100,0,100,"fullbody_27");
	}
	if(substate == 3)
	{
		obj.sq_PlaySound("SW_FULLBODY_01_B");
		obj.setObjectHeight(999);
		obj.sq_SetShake(obj,2,300);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_fullbody_body_hit);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_fullbodyattack3fastspeed);
		local power =  obj.sq_GetPowerWithPassive(SKILL_FULLBODY, STATE_FULLBODY, 2, -1,1.0);
		obj.sq_SetCurrentAttackPower(power);

		local fullbody_04 = "character/swordman/effect/animation/3rd/atfullbody/hit/fullbody_04.ani";
		ATSwordman_Create(obj,fullbody_04,ENUM_DRAWLAYER_NORMAL,0,-10,0,0,100,0,100,"fullbody_04");
		local hitback_00 = "character/swordman/effect/animation/3rd/atfullbody/hit/hitback_00.ani";
		ATSwordman_Create(obj,hitback_00,ENUM_DRAWLAYER_NORMAL,0,-10,0,0,100,0,100,"hitback_00");
		local hitfront_00 = "character/swordman/effect/animation/3rd/atfullbody/hit/hitfront_00.ani";
		ATSwordman_Create(obj,hitfront_00,ENUM_DRAWLAYER_NORMAL,0,-10,0,0,100,0,100,"hitfront_00");
	}
	if(substate == 4)
	{
		obj.sq_PlaySound("FULLBODY_FINISH");
		obj.sq_SetShake(obj,2,100);
		obj.sq_SetXScrollStop(200);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_fullbody_body_end);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_fullbodyattack4finish);
		local power =  obj.sq_GetPowerWithPassive(SKILL_FULLBODY, STATE_FULLBODY, 3, -1,1.0);
		obj.sq_SetCurrentAttackPower(power);

		local endback_00 = "character/swordman/effect/animation/3rd/atfullbody/end/endback_00.ani";
		ATSwordman_Create(obj,endback_00,ENUM_DRAWLAYER_NORMAL,0,0,0,0,80,0,100,"endback_00");
		local endfronta_00 = "character/swordman/effect/animation/3rd/atfullbody/end/endfronta_00.ani";
		ATSwordman_Create(obj,endfronta_00,ENUM_DRAWLAYER_NORMAL,0,0,0,0,80,0,100,"endfronta_00");
		local endfrontb_00 = "character/swordman/effect/animation/3rd/atfullbody/end/endfrontb_00.ani";
		ATSwordman_Create(obj,endfrontb_00,ENUM_DRAWLAYER_NORMAL,0,0,0,0,80,0,100,"endfrontb_00");
	}
}

function onEndCurrentAni_fullbody(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_FULLBODY, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 1)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_FULLBODY, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 2)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(3);
		obj.sq_AddSetStatePacket(STATE_FULLBODY, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 3)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(4);
		obj.sq_AddSetStatePacket(STATE_FULLBODY, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 4)
	{
		obj.setObjectHeight(110);
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
	}
}
