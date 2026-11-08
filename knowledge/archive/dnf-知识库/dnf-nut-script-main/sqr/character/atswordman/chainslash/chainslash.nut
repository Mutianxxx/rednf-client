
//??多少次改女鬼?文件不要?自??式化再?式化我沙了你(╯°□°?╯? ???)
function checkExecutableSkill_Chainslash(obj)
{
	if (!obj) return false;
	local CQXcKYQXpVLpdXJg = obj.sq_IsUseSkill(32);
	if (CQXcKYQXpVLpdXJg)
	{
		CheckUseAddloadDrawsword(obj,143,{[0] = true,[108] = true,[14] = true},0);
		obj.sq_StopMove();
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(132, STATE_PRIORITY_IGNORE_FORCE, true);
		obj.getVar("Chainslash").clear_vector();
		obj.getVar("Chainslash").push_vector(sq_GetLevelData(obj,32, 2, sq_GetSkillLevel(obj, 32))-1);
		return true
	}
	return false
}

function checkCommandEnable_Chainslash(CQLtRTezm2qLYOdH)
{
	if (!CQLtRTezm2qLYOdH) return false
if(CQLtRTezm2qLYOdH.getZPos() > 2)
		return false
return CheckForceDrawsword(CQLtRTezm2qLYOdH,143,{[0] = true,[108] = true,[14] = true})
}


function onSetState_Chainslash(obj, CQIhfA1IzouivV9KtNH7, CQ74SMuwHM9qlQ8Fo, CQr5YhYkfvIxhM8XIDl)
{
	if(!obj) return;
	local CQCXVQ7KrAkfxs7J = obj.sq_GetVectorData(CQ74SMuwHM9qlQ8Fo, 0);
	obj.setSkillSubState(CQCXVQ7KrAkfxs7J);
	obj.endSkillCoolTime(32);
	obj.sq_IsEnterSkillLastKeyUnits(32);
	obj.getVar("Chainslash").setBool(0,false);
	obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	obj.sq_SetStaticMoveInfo(0, sq_GetIntData(obj, 32, 0), sq_GetIntData(obj, 32, 1), false);
	local CQcSrIKE3BH2jg6B1u = ["ChainSlash01_body","ChainSlash02_body","ChainSlash03_body","ChainSlash04_body","ChainSlash05_body","ChainSlashTP01_body","ChainSlashTP02_body"];
	BodyMagicSword(obj, CQcSrIKE3BH2jg6B1u[CQCXVQ7KrAkfxs7J]);
	local speed = sq_GetIntData(obj, 32, 2)/100+1;
	if(MagicSword_IsAppebd(obj))
		obj.sq_SetCurrentAnimation(202 + CQCXVQ7KrAkfxs7J);
	else
	{
		if(sq_GetSkillLevel(obj, 148) > 0)
		{
			BodyCalldaimus(obj, CQcSrIKE3BH2jg6B1u[CQCXVQ7KrAkfxs7J]);
			obj.sq_SetCurrentAnimation(374 + CQCXVQ7KrAkfxs7J);
		}
		else
			obj.sq_SetCurrentAnimation(26 + CQCXVQ7KrAkfxs7J);
	}


	obj.sq_SetCurrentAttackInfo(0);
	local CQAi7VoUbcbLdP6Z5NwP = obj.sq_GetBonusRateWithPassive(32, -1, 0, getATSwordmanBonus(obj,1.0,32));
	obj.sq_SetCurrentAttackBonusRate(CQAi7VoUbcbLdP6Z5NwP);
	if(obj.getWeaponSubType() == 3 && sq_GetSkillLevel(obj, 12) > 0)
		sq_SendMessage(obj, OBJECT_MESSAGE_SUPERARMOR, 1, 0);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speed.tofloat(), speed.tofloat());
}

function onEndCurrentAni_Chainslash(CQdmIRv2POVAkm519)
{
	if(!CQdmIRv2POVAkm519) return
CQdmIRv2POVAkm519.sq_IntVectClear()
CQdmIRv2POVAkm519.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
}

function onEnterFrame_Chainslash(CQyT7UVGj6eifB4VbDC, CQN7saIuuz4q6wjL)
{
	if(!CQyT7UVGj6eifB4VbDC) return
local CQgVTXqR7spxR1hMWubn = CQyT7UVGj6eifB4VbDC.getSkillSubState()
switch(CQgVTXqR7spxR1hMWubn)
	{
	case 3:

		break
case 4:

		break
}
}

function onEndState_Chainslash(obj, newstate) {
	if (!obj) return
	if (newstate != 132) {
		obj.startSkillCoolTime(32, sq_GetSkillLevel(obj, 32), -1)
		sq_SendMessage(obj, OBJECT_MESSAGE_SUPERARMOR, 0, 0)
	}
}

function onProcCon_Chainslash(CQmq3pPYxEz5VARN)
{
	if(!CQmq3pPYxEz5VARN) return
ForceUse_ATSwordman(CQmq3pPYxEz5VARN,247,[0],247)
}
function onAttack_Chainslash(CQJloKz9a2LC3qR6Nv, CQk8274C1nmDBNf23D32, CQaBocGrWiMELed9z, CQ5FguyzLMteNgd5vue)
{
	if(!CQJloKz9a2LC3qR6Nv) return false
local CQwpFHxXhv7YZP9R = CQJloKz9a2LC3qR6Nv.getSkillSubState()
MagicswordupOccur(CQJloKz9a2LC3qR6Nv, CQk8274C1nmDBNf23D32, CQaBocGrWiMELed9z, CQ5FguyzLMteNgd5vue)
}
function onProc_Chainslash(CQZwv45sAAshGk87eb)
{
	if(!CQZwv45sAAshGk87eb) return
local CQlxBzEQ5Vj5XB8hADsH = CQZwv45sAAshGk87eb.getSkillSubState()
local CQIcttn5icFCHQ7d = CQZwv45sAAshGk87eb.getCurrentAnimation()
local CQ7f9DdJVOYFAMTTZu = CQZwv45sAAshGk87eb.sq_GetCurrentFrameIndex(CQIcttn5icFCHQ7d)
local CQr1t2Cpl6CEJITgBfIR = CQZwv45sAAshGk87eb.getVar("Chainslash").get_vector(0)
if(CQ7f9DdJVOYFAMTTZu > 3 && (CQZwv45sAAshGk87eb.isDownSkillLastKey() || sq_IsKeyDown(OPTION_HOTKEY_SKILL, ENUM_SUBKEY_TYPE_ALL)))
		CQZwv45sAAshGk87eb.getVar("Chainslash").setBool(0,true)
if(CQ7f9DdJVOYFAMTTZu > 6 && CQlxBzEQ5Vj5XB8hADsH < 6 && CQr1t2Cpl6CEJITgBfIR >0)
	{
		if(CQZwv45sAAshGk87eb.getVar("Chainslash").getBool(0))
		{
			if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL))
				CQZwv45sAAshGk87eb.sq_SetDirection(ENUM_DIRECTION_LEFT)
else if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL))
				CQZwv45sAAshGk87eb.sq_SetDirection(ENUM_DIRECTION_RIGHT)
CQZwv45sAAshGk87eb.sq_IntVectClear()
CQZwv45sAAshGk87eb.sq_IntVectPush(CQlxBzEQ5Vj5XB8hADsH+1)
CQZwv45sAAshGk87eb.sq_AddSetStatePacket(132, STATE_PRIORITY_IGNORE_FORCE, true)
CQZwv45sAAshGk87eb.getVar("Chainslash").set_vector(0,CQr1t2Cpl6CEJITgBfIR - 1)
}
	}
}

function procAppend_ATSwordman_RunChainslash(obj){
	if (!obj) return false;
	local state = obj.sq_GetState();
	if(state!=14){
		return false;
	}
	local skill = sq_GetSkill(obj, 32);
	if(sq_GetSkillLevel(obj, 32) < 1||skill.isSealFunction()){
		return false;
	}
	local movekey = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL)||sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);
	local skillkey = sq_IsKeyDown(OPTION_HOTKEY_SKILL, ENUM_SUBKEY_TYPE_ALL);
	if(movekey&&skillkey){
		if(checkExecutableSkill_Chainslash(obj)){
			return true;
		}else{
			checkExecutableSkill_Liftslash(obj);
			return false;
		}
		
	}
	return false;
}










