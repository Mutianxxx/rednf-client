
function onSetState_AtSwordman_Basic5(obj, state, datas, isResetTimer)
{
if(!obj) return;
local CQw6BDr943kvtV9Af = obj.sq_GetVectorData(datas, 0);
obj.setSkillSubState(CQw6BDr943kvtV9Af);
obj.sq_StopMove();
local pSkillBonusRate = obj.sq_GetBonusRateWithPassive(174, -1, 0, getATSwordmanBonus(obj,1.0,-1))/10+100;
switch(CQw6BDr943kvtV9Af)
{
case 0:
obj.sq_SetCurrentAttackInfo(0);
local CQzS8k2WCFb6yM8F = 100;
if(sq_GetSkillLevel(obj, 3) > 0)
{
BodyMagicSword(obj, "InnerBladeAttack1")
if(MagicSword_IsAppebd(obj))
obj.sq_SetCurrentAnimation(287);
else
obj.sq_SetCurrentAnimation(47);
}
else if(sq_GetSkillLevel(obj, 148) > 0)
{
BodyCalldaimus(obj, "CallDaimusAttack1");
obj.sq_SetCurrentAnimation(367);
}
else if(sq_GetSkillLevel(obj, 62) > 0)
{
obj.sq_SetCurrentAnimation(508);
obj.sq_SetCurrentAttackInfo(128);
local CQOiOeDxTRVVwr7Xtk = sq_GetLevelData(obj,62, 0, sq_GetSkillLevel(obj, 62));
pSkillBonusRate = pSkillBonusRate + CQOiOeDxTRVVwr7Xtk;
}
else if(sq_GetSkillLevel(obj, 202) > 0)
{
obj.sq_PlaySound("R_SW_1ATK");
local CQ8mzAt6obeGuh6Hoawn = checkAppend_Dualweapon(obj);
obj.sq_SetCurrentAnimation(SetChrAniIndex_Dualweapon(obj,CQ8mzAt6obeGuh6Hoawn));
obj.sq_SetCurrentAttackInfo(SetChrAtkIndex_Dualweapon(obj,CQ8mzAt6obeGuh6Hoawn));
local CQWTZN8I9S5aeATSs = sq_GetLevelData(obj,202, 0, sq_GetSkillLevel(obj, 202));
local CQVlzhLww9prUTkLSQV = sq_GetLevelData(obj,202, 8, sq_GetSkillLevel(obj, 202));
if(CQ8mzAt6obeGuh6Hoawn == 3)
pSkillBonusRate =0 + CQVlzhLww9prUTkLSQV + CQWTZN8I9S5aeATSs;
else
pSkillBonusRate = 0 + CQWTZN8I9S5aeATSs;
local attackInfo = sq_GetCurrentAttackInfo(obj);
sq_SetCurrentAttackBonusRate(attackInfo, pSkillBonusRate);
sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));

}
else if(sq_GetSkillLevel(obj, 127) > 0)
{
obj.sq_PlaySound("R_PROFESSIONAL_START");
obj.sq_SetCurrentAnimation(CAHNGQING_ATSWORDMAN_INFOS["A"][-1][0]);
}
else
{
obj.sq_SetCurrentAnimation(0);
obj.sq_PlaySound("R_SW_1ATK");
}
	if(sq_GetSkillLevel(obj, 127) > 0){
		
		local bsatk = obj.sq_GetPowerWithPassive(174, -1, 0, -1, getATSwordmanBonus(obj,1.0,174));
		bsatk = 45+bsatk*0.07;
		obj.sq_SetCurrentAttackPower(bsatk.tointeger());
		
	}
	else{
		obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);
		
	}
sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
obj.sq_SetStaticSpeedInfo(2, 2, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.8, 1.8);
break;
case 1:
obj.sq_SetCurrentAttackInfo(1);
local CQzS8k2WCFb6yM8F = 120;
if(sq_GetSkillLevel(obj, 3) > 0)
{
BodyMagicSword(obj, "InnerBladeAttack2")
if(MagicSword_IsAppebd(obj))
obj.sq_SetCurrentAnimation(288);
else
obj.sq_SetCurrentAnimation(48);
}
else if(sq_GetSkillLevel(obj, 148) > 0)
{
BodyCalldaimus(obj, "CallDaimusAttack2");
obj.sq_SetCurrentAnimation(368);
}
else if(sq_GetSkillLevel(obj, 62) > 0)
{
obj.sq_SetCurrentAnimation(509);
obj.sq_SetCurrentAttackInfo(129);
local CQOiOeDxTRVVwr7Xtk = sq_GetLevelData(obj,62, 0, sq_GetSkillLevel(obj, 62));
pSkillBonusRate = pSkillBonusRate + CQOiOeDxTRVVwr7Xtk;
}
else if(sq_GetSkillLevel(obj, 202) > 0)
{
obj.sq_PlaySound("R_SW_2ATK");
local CQ8mzAt6obeGuh6Hoawn = checkAppend_Dualweapon(obj);
obj.sq_SetCurrentAnimation(SetChrAniIndex_Dualweapon(obj,CQ8mzAt6obeGuh6Hoawn) + 1);
obj.sq_SetCurrentAttackInfo(SetChrAtkIndex_Dualweapon(obj,CQ8mzAt6obeGuh6Hoawn) + 1);
local CQWTZN8I9S5aeATSs = sq_GetLevelData(obj,202, 0, sq_GetSkillLevel(obj, 202));
local CQVlzhLww9prUTkLSQV = sq_GetLevelData(obj,202, 8, sq_GetSkillLevel(obj, 202));
if(CQ8mzAt6obeGuh6Hoawn == 3)
pSkillBonusRate = 0 + CQVlzhLww9prUTkLSQV + CQWTZN8I9S5aeATSs;
else
pSkillBonusRate = 0 + CQWTZN8I9S5aeATSs;

local attackInfo = sq_GetCurrentAttackInfo(obj);
sq_SetCurrentAttackBonusRate(attackInfo, pSkillBonusRate);
sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
}
else if(sq_GetSkillLevel(obj, 127) > 0)
{
obj.sq_PlaySound("R_PROFESSIONAL_SWORD");
obj.sq_SetCurrentAnimation(CAHNGQING_ATSWORDMAN_INFOS["A"][-1][1]);
}
else
{
obj.sq_PlaySound("R_SW_2ATK");
obj.sq_SetCurrentAnimation(1);
}
	if(sq_GetSkillLevel(obj, 127) > 0){
		
		local bsatk = obj.sq_GetPowerWithPassive(174, -1, 0, -1, getATSwordmanBonus(obj,1.0,174));
		bsatk = 45+bsatk*0.07;
		obj.sq_SetCurrentAttackPower(bsatk.tointeger());
		
	}
	else{
		obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);
		
	}
sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
obj.sq_SetStaticSpeedInfo(2, 2, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.2, 1.2);
break;
case 2:
obj.sq_SetCurrentAttackInfo(2);
local CQzS8k2WCFb6yM8F = 150;
if(sq_GetSkillLevel(obj, 3) > 0)
{
BodyMagicSword(obj, "InnerBladeAttack3")
if(MagicSword_IsAppebd(obj))
obj.sq_SetCurrentAnimation(289);
else
obj.sq_SetCurrentAnimation(49);
obj.sq_SetStaticSpeedInfo(2, 2, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.2, 1.2);
}
else if(sq_GetSkillLevel(obj, 148) > 0)
{
BodyCalldaimus(obj, "CallDaimusAttack3");
obj.sq_SetCurrentAnimation(369);
obj.sq_SetStaticSpeedInfo(2, 2, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.2, 1.2);
}
else if(sq_GetSkillLevel(obj, 62) > 0)
{
obj.sq_SetCurrentAnimation(510);
obj.sq_SetCurrentAttackInfo(130);
local CQOiOeDxTRVVwr7Xtk = sq_GetLevelData(obj,62, 0, sq_GetSkillLevel(obj, 62));
pSkillBonusRate = pSkillBonusRate + CQOiOeDxTRVVwr7Xtk;
}
else if(sq_GetSkillLevel(obj, 202) > 0)
{
obj.sq_PlaySound("R_SW_3ATK");
local CQ8mzAt6obeGuh6Hoawn = checkAppend_Dualweapon(obj);
obj.sq_SetCurrentAnimation(SetChrAniIndex_Dualweapon(obj,CQ8mzAt6obeGuh6Hoawn) + 2);
obj.sq_SetCurrentAttackInfo(SetChrAtkIndex_Dualweapon(obj,CQ8mzAt6obeGuh6Hoawn) + 2);
local CQWTZN8I9S5aeATSs = sq_GetLevelData(obj,202, 0, sq_GetSkillLevel(obj, 202));
local CQVlzhLww9prUTkLSQV = sq_GetLevelData(obj,202, 8, sq_GetSkillLevel(obj, 202));

if(CQ8mzAt6obeGuh6Hoawn == 3)
pSkillBonusRate = 0 + CQVlzhLww9prUTkLSQV + CQWTZN8I9S5aeATSs;
else
pSkillBonusRate = 0 + CQWTZN8I9S5aeATSs;

local attackInfo = sq_GetCurrentAttackInfo(obj);
sq_SetCurrentAttackBonusRate(attackInfo, pSkillBonusRate);
sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));

obj.sq_SetStaticSpeedInfo(2, 2, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.2, 1.2);
}
else if(sq_GetSkillLevel(obj, 127) > 0)
{
obj.sq_PlaySound("PROFESSIONAL_KICK");
obj.sq_SetCurrentAnimation(CAHNGQING_ATSWORDMAN_INFOS["A"][-1][2]);
}
else
{
obj.sq_SetCurrentAnimation(2);
obj.sq_SetStaticSpeedInfo(2, 2, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.2, 1.2);
obj.sq_PlaySound("R_SW_3ATK");
}
	if(sq_GetSkillLevel(obj, 127) > 0){
		
		local bsatk = obj.sq_GetPowerWithPassive(174, -1, 0, -1, getATSwordmanBonus(obj,1.0,174));
		bsatk = 45+bsatk*0.07;
		obj.sq_SetCurrentAttackPower(bsatk.tointeger());
		
	}
	else{
		obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);
		
	}
	sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
break;
case 3:
if(sq_GetSkillLevel(obj, 148) > 0)
{
BodyCalldaimus(obj, "CallDaimusAttack4");
obj.sq_SetCurrentAnimation(370);
}
else if(sq_GetSkillLevel(obj, 127) > 0)
{
obj.sq_PlaySound("PROFESSIONAL_END_SLASH");
obj.sq_SetCurrentAnimation(CAHNGQING_ATSWORDMAN_INFOS["A"][-1][3]);
}
obj.sq_SetCurrentAttackInfo(82);
local CQzS8k2WCFb6yM8F = 150;
	if(sq_GetSkillLevel(obj, 127) > 0){
		
		local bsatk = obj.sq_GetPowerWithPassive(174, -1, 0, -1, getATSwordmanBonus(obj,1.0,174));
		bsatk = 45+bsatk*0.07;
		obj.sq_SetCurrentAttackPower(bsatk.tointeger());
		
	}
	else{
		obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);
		
	}
sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
obj.sq_SetStaticSpeedInfo(2, 2, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.2, 1.2);
break;
case 4:
if(sq_GetSkillLevel(obj, 148) > 0)
{
BodyCalldaimus(obj, "CallDaimusAttack5");
obj.sq_SetCurrentAnimation(371);
}
obj.sq_SetCurrentAttackInfo(83);
local CQzS8k2WCFb6yM8F = 150;
obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);
sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));

break;
}

if(sq_GetSkillLevel(obj, 62) > 0)
{
local CQ5fAccAJbCJ6Dz7 = sq_GetCurrentAttackBonusRate(obj);
local CQw1cu6rRSwORwl3mT = obj.sq_GetLevelData(62, 0, sq_GetSkillLevel(obj, 62));
obj.sq_SetCurrentAttackBonusRate(CQ5fAccAJbCJ6Dz7 + CQw1cu6rRSwORwl3mT);
}

}

function onProcCon_AtSwordman_Basic5(CQZKXGJzI93y71TdeaLL)
{
if(!CQZKXGJzI93y71TdeaLL) return;

local CQzIx4iX3WiU2WT6y = CQZKXGJzI93y71TdeaLL.getSkillSubState();

local CQOOXzRsbPfl8jkRGEc = CQZKXGJzI93y71TdeaLL.getCurrentAnimation();
local CQ8teWVQX7Px3Sj8 = CQOOXzRsbPfl8jkRGEc.GetCurrentFrameIndex();

procSetIsMove(CQZKXGJzI93y71TdeaLL);

if(sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))
{
switch(CQzIx4iX3WiU2WT6y)
{
case 0:
if(CQZKXGJzI93y71TdeaLL.isCurrentCutomAniIndex(0) && CQ8teWVQX7Px3Sj8>3)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(1);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
else if(sq_GetSkillLevel(CQZKXGJzI93y71TdeaLL, 3) > 0 && CQ8teWVQX7Px3Sj8>5)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(1);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
else if(sq_GetSkillLevel(CQZKXGJzI93y71TdeaLL, 148) > 0 && CQ8teWVQX7Px3Sj8>2)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(1);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
else if(sq_GetSkillLevel(CQZKXGJzI93y71TdeaLL, 62) > 0 && CQ8teWVQX7Px3Sj8>3)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(1);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
else if(sq_GetSkillLevel(CQZKXGJzI93y71TdeaLL, 202) > 0 && CQ8teWVQX7Px3Sj8>2)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(1);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
else if(sq_GetSkillLevel(CQZKXGJzI93y71TdeaLL, 127) > 0 && CQ8teWVQX7Px3Sj8>5)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(1);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
break;
case 1:
if(CQZKXGJzI93y71TdeaLL.isCurrentCutomAniIndex(1) && CQ8teWVQX7Px3Sj8>3)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(2);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
else if(sq_GetSkillLevel(CQZKXGJzI93y71TdeaLL, 3) > 0 && CQ8teWVQX7Px3Sj8>5)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(2);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
else if(sq_GetSkillLevel(CQZKXGJzI93y71TdeaLL, 148) > 0 && CQ8teWVQX7Px3Sj8>3)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(2);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
else if(sq_GetSkillLevel(CQZKXGJzI93y71TdeaLL, 62) > 0 && CQ8teWVQX7Px3Sj8>2)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(2);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
else if(sq_GetSkillLevel(CQZKXGJzI93y71TdeaLL, 202) > 0 && CQ8teWVQX7Px3Sj8>3)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(2);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
else if(sq_GetSkillLevel(CQZKXGJzI93y71TdeaLL, 127) > 0 && CQ8teWVQX7Px3Sj8>3)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(2);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
break;
case 2:
if(sq_GetSkillLevel(CQZKXGJzI93y71TdeaLL, 148) > 0 && CQ8teWVQX7Px3Sj8>3)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(3);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
else if(sq_GetSkillLevel(CQZKXGJzI93y71TdeaLL, 127) > 0 && CQ8teWVQX7Px3Sj8>6)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(3);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
break;
case 3:
if(sq_GetSkillLevel(CQZKXGJzI93y71TdeaLL, 148) > 0 && CQ8teWVQX7Px3Sj8>2)
{
CQZKXGJzI93y71TdeaLL.sq_IntVectClear();
CQZKXGJzI93y71TdeaLL.sq_IntVectPush(4);
CQZKXGJzI93y71TdeaLL.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true);
}
break;
}
}

ForcePush_ATSwordman(CQZKXGJzI93y71TdeaLL,169,[1,1,200],6);
}


function onAttack_AtSwordman_Basic5(CQQ4IWpXdjobhTncBy, CQL5lSbseofj9Fnq2, CQlXL19lJMP74ebb6vT, CQIAQkZ5vRlBd2vx)
{
if(!CQQ4IWpXdjobhTncBy) return false;
local CQ7u3wEJOuJG5tvmUY = CQQ4IWpXdjobhTncBy.getSkillSubState();
MagicSword_BasiconAttack(CQQ4IWpXdjobhTncBy, CQL5lSbseofj9Fnq2, CQlXL19lJMP74ebb6vT, CQIAQkZ5vRlBd2vx);
Calldaimus_onAttack(CQQ4IWpXdjobhTncBy,CQL5lSbseofj9Fnq2, CQlXL19lJMP74ebb6vT, CQIAQkZ5vRlBd2vx);
}

function onEndCurrentAni_AtSwordman_Basic5(CQrUpPUqjBUKMjYvwSqG)
{
if(!CQrUpPUqjBUKMjYvwSqG) return;
CQrUpPUqjBUKMjYvwSqG.sq_IntVectClear();
CQrUpPUqjBUKMjYvwSqG.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true);
}

function onProcCon_AtSwordman_Basic3(CQblyucyMTcKBTqoxyt)
{
if(!CQblyucyMTcKBTqoxyt) return;
if(sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))
{
CQblyucyMTcKBTqoxyt.sq_IntVectClear();
CQblyucyMTcKBTqoxyt.sq_IntVectPush(0);
CQblyucyMTcKBTqoxyt.sq_AddSetStatePacket(115, STATE_PRIORITY_IGNORE_FORCE, true);
}
}

function onProcCon_AtSwordman_Basic6(CQblyucyMTcKBTqoxyt)
{
	if(!CQblyucyMTcKBTqoxyt) return;

CQblyucyMTcKBTqoxyt.sq_IntVectClear();
CQblyucyMTcKBTqoxyt.sq_IntVectPush(0);
CQblyucyMTcKBTqoxyt.sq_AddSetStatePacket(115, STATE_PRIORITY_IGNORE_FORCE, true);

}

function onSetState_AtSwordman_Basic4(CQWb6DI5kwlfBljjBq, CQVha1qJiLJ3LNhf2KWe, CQY4kkgp85UZNeglT, CQSZJeBjQqNAZ2ghcaN)
{

if(!CQWb6DI5kwlfBljjBq) return;

local CQfPmPW2MHWoGPRc = CQWb6DI5kwlfBljjBq.sq_GetVectorData(CQY4kkgp85UZNeglT, 0);
CQWb6DI5kwlfBljjBq.setSkillSubState(CQfPmPW2MHWoGPRc);

local CQuyHNloch6QXkYTQQ = sq_getGrowType(CQWb6DI5kwlfBljjBq);

local CQMnUh3nsUaxHDYbPKMz = CQWb6DI5kwlfBljjBq.sq_GetBonusRateWithPassive(174, -1, 0, getATSwordmanBonus(CQWb6DI5kwlfBljjBq,1.0,-1))/10+100;

switch(CQfPmPW2MHWoGPRc)
{
case 0:
CQWb6DI5kwlfBljjBq.sq_StopMove();
CQWb6DI5kwlfBljjBq.sq_PlaySound("SW_DASHATK");

CQWb6DI5kwlfBljjBq.sq_SetCurrentAttackInfo(0);
local CQnj1qFRgFhRAwcxF = CQMnUh3nsUaxHDYbPKMz;

if(CQuyHNloch6QXkYTQQ ==1)
{
local CQG5iIyDWfD3J1ckKJq = GetMagicSwordAppIndex(CQWb6DI5kwlfBljjBq);

	switch(CQG5iIyDWfD3J1ckKJq)
	{
		case 0:
			CQWb6DI5kwlfBljjBq.sq_SetCurrentAnimation(4);
		break;
		case 1:
			CQWb6DI5kwlfBljjBq.sq_SetCurrentAnimation(158);
		break;
		case 2:
			CQWb6DI5kwlfBljjBq.sq_SetCurrentAnimation(157);
		break;
		case 3:
			CQWb6DI5kwlfBljjBq.sq_SetCurrentAnimation(160);
		break;
		case 4:
			CQWb6DI5kwlfBljjBq.sq_SetCurrentAnimation(159);
		break;
	}
}
else if(CQuyHNloch6QXkYTQQ ==3)
{
	if(sq_GetSkillLevel(CQWb6DI5kwlfBljjBq, 148) > 0)
	{

		BodyCalldaimus(CQWb6DI5kwlfBljjBq, "CallDaimusDashAttack1");
		CQWb6DI5kwlfBljjBq.sq_SetCurrentAnimation(372);
	}
}
else if(CQuyHNloch6QXkYTQQ == 4)
{
	if(sq_GetSkillLevel(CQWb6DI5kwlfBljjBq, 62) > 0)
	{

		CQWb6DI5kwlfBljjBq.sq_SetCurrentAnimation(511);
		CQWb6DI5kwlfBljjBq.sq_SetCurrentAttackInfo(131);
		local CQhXRVxyLycZDrxv = sq_GetLevelData(CQWb6DI5kwlfBljjBq,62, 0, sq_GetSkillLevel(CQWb6DI5kwlfBljjBq, 62));
		CQMnUh3nsUaxHDYbPKMz = CQMnUh3nsUaxHDYbPKMz + CQhXRVxyLycZDrxv;
	}
}
else
{
	if(sq_GetSkillLevel(CQWb6DI5kwlfBljjBq, 127) > 0)
		CQWb6DI5kwlfBljjBq.sq_SetCurrentAnimation(CAHNGQING_ATSWORDMAN_INFOS["A"][-1][4]);
	else
		CQWb6DI5kwlfBljjBq.sq_SetCurrentAnimation(4);
}

	if(sq_GetSkillLevel(CQWb6DI5kwlfBljjBq, 127) > 0){
		local bsdatk = CQWb6DI5kwlfBljjBq.sq_GetPowerWithPassive(174, -1, 0, -1, getATSwordmanBonus(CQWb6DI5kwlfBljjBq,1.0,174));
		bsdatk = 45+bsdatk*0.07;
		CQWb6DI5kwlfBljjBq.sq_SetCurrentAttackPower(bsdatk.tointeger());
	}
	else{
		CQWb6DI5kwlfBljjBq.applyBasicAttackUp(sq_GetCurrentAttackInfo(CQWb6DI5kwlfBljjBq),15);
	}

sq_SetCurrentAttackInfo(CQWb6DI5kwlfBljjBq, sq_GetCurrentAttackInfo(CQWb6DI5kwlfBljjBq));

break;

case 1:
CQWb6DI5kwlfBljjBq.sq_SetCurrentAttackInfo(85);
local CQnj1qFRgFhRAwcxF = 120;
if(sq_GetSkillLevel(CQWb6DI5kwlfBljjBq, 148) > 0)
{
BodyCalldaimus(CQWb6DI5kwlfBljjBq, "CallDaimusDashAttack2");
CQWb6DI5kwlfBljjBq.sq_SetCurrentAnimation(373);
}
else if(sq_GetSkillLevel(CQWb6DI5kwlfBljjBq, 62) > 0)
{
CQWb6DI5kwlfBljjBq.sq_SetCurrentAnimation(512);
CQWb6DI5kwlfBljjBq.sq_SetCurrentAttackInfo(132);
local CQhXRVxyLycZDrxv = sq_GetLevelData(CQWb6DI5kwlfBljjBq,62, 0, sq_GetSkillLevel(CQWb6DI5kwlfBljjBq, 62));
CQMnUh3nsUaxHDYbPKMz = CQMnUh3nsUaxHDYbPKMz + CQhXRVxyLycZDrxv;
}
else if(sq_GetSkillLevel(CQWb6DI5kwlfBljjBq, 127) > 0)
{
CQWb6DI5kwlfBljjBq.sq_SetCurrentAnimation(CAHNGQING_ATSWORDMAN_INFOS["A"][-1][5]);
}
	if(sq_GetSkillLevel(CQWb6DI5kwlfBljjBq, 127) > 0){
		local bsdatk = CQWb6DI5kwlfBljjBq.sq_GetPowerWithPassive(174, -1, 0, -1, getATSwordmanBonus(CQWb6DI5kwlfBljjBq,1.0,174));
		bsdatk = 45+bsdatk*0.07;
		CQWb6DI5kwlfBljjBq.sq_SetCurrentAttackPower(bsdatk.tointeger());
	}
	else{
		CQWb6DI5kwlfBljjBq.applyBasicAttackUp(sq_GetCurrentAttackInfo(CQWb6DI5kwlfBljjBq),15);
	}
sq_SetCurrentAttackInfo(CQWb6DI5kwlfBljjBq, sq_GetCurrentAttackInfo(CQWb6DI5kwlfBljjBq));

break;
}
if(sq_GetSkillLevel(CQWb6DI5kwlfBljjBq, 62) > 0)
{
local CQqmVEnP6r2QOTlYx = sq_GetCurrentAttackBonusRate(CQWb6DI5kwlfBljjBq);
local CQsTYZdroPuxpFTQbK6 = CQWb6DI5kwlfBljjBq.sq_GetLevelData(62, 1, sq_GetSkillLevel(CQWb6DI5kwlfBljjBq, 62));
CQWb6DI5kwlfBljjBq.sq_SetCurrentAttackBonusRate(CQqmVEnP6r2QOTlYx + CQsTYZdroPuxpFTQbK6);
}
}

function onProcCon_AtSwordman_Basic4(CQ3v21Hv7A4FUEqc8)
{
if(!CQ3v21Hv7A4FUEqc8) return;
local CQXOdIgmyHIfuBvJnh = CQ3v21Hv7A4FUEqc8.getCurrentAnimation().GetCurrentFrameIndex();
local CQRVz9Qgs1ileiVc6f1 = CQ3v21Hv7A4FUEqc8.getSkillSubState();

if(sq_getGrowType(CQ3v21Hv7A4FUEqc8) == 3 && CQRVz9Qgs1ileiVc6f1 == 0)
{
if(CQXOdIgmyHIfuBvJnh < 4)
CQ3v21Hv7A4FUEqc8.sq_SetStaticMoveInfo(0, 200, 106, false, -500, true);
else
CQ3v21Hv7A4FUEqc8.sq_SetStaticMoveInfo(0,0,0,false);
CQ3v21Hv7A4FUEqc8.sq_SetMoveDirection(CQ3v21Hv7A4FUEqc8.getDirection(), ENUM_DIRECTION_NEUTRAL);
if(sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))
{
if(sq_GetSkillLevel(CQ3v21Hv7A4FUEqc8, 148) > 0 && CQXOdIgmyHIfuBvJnh>3)
{
CQ3v21Hv7A4FUEqc8.sq_IntVectClear();
CQ3v21Hv7A4FUEqc8.sq_IntVectPush(1);
CQ3v21Hv7A4FUEqc8.sq_AddSetStatePacket(115, STATE_PRIORITY_IGNORE_FORCE, true);
}
}
}
else if(sq_getGrowType(CQ3v21Hv7A4FUEqc8) == 4 && CQRVz9Qgs1ileiVc6f1 == 0)
{
if(CQXOdIgmyHIfuBvJnh < 5)
CQ3v21Hv7A4FUEqc8.sq_SetStaticMoveInfo(0, 200, 106, false, -500, true);
else
CQ3v21Hv7A4FUEqc8.sq_SetStaticMoveInfo(0,0,0,false);
CQ3v21Hv7A4FUEqc8.sq_SetMoveDirection(CQ3v21Hv7A4FUEqc8.getDirection(), ENUM_DIRECTION_NEUTRAL);
if(sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))
{
if(sq_GetSkillLevel(CQ3v21Hv7A4FUEqc8, 62) > 0 && CQXOdIgmyHIfuBvJnh>6)
{
CQ3v21Hv7A4FUEqc8.sq_IntVectClear();
CQ3v21Hv7A4FUEqc8.sq_IntVectPush(1);
CQ3v21Hv7A4FUEqc8.sq_AddSetStatePacket(115, STATE_PRIORITY_IGNORE_FORCE, true);
}
}
}
else if(sq_getGrowType(CQ3v21Hv7A4FUEqc8) == 0 && CQRVz9Qgs1ileiVc6f1 == 0)
{
if(CQXOdIgmyHIfuBvJnh < 7)
CQ3v21Hv7A4FUEqc8.sq_SetStaticMoveInfo(0, 200, 106, false, -500, true);
else
CQ3v21Hv7A4FUEqc8.sq_SetStaticMoveInfo(0,0,0,false);
CQ3v21Hv7A4FUEqc8.sq_SetMoveDirection(CQ3v21Hv7A4FUEqc8.getDirection(), ENUM_DIRECTION_NEUTRAL);
if(sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))
{
if(sq_GetSkillLevel(CQ3v21Hv7A4FUEqc8, 127) > 0 && CQXOdIgmyHIfuBvJnh>7)
{
CQ3v21Hv7A4FUEqc8.sq_IntVectClear();
CQ3v21Hv7A4FUEqc8.sq_IntVectPush(1);
CQ3v21Hv7A4FUEqc8.sq_AddSetStatePacket(115, STATE_PRIORITY_IGNORE_FORCE, true);
}
}
}
else
{
if(CQXOdIgmyHIfuBvJnh < 4)
CQ3v21Hv7A4FUEqc8.sq_SetStaticMoveInfo(0, 200, 106, false, -500, true);
else
CQ3v21Hv7A4FUEqc8.sq_SetStaticMoveInfo(0, 10, 106, false, -500, true);
CQ3v21Hv7A4FUEqc8.sq_SetMoveDirection(CQ3v21Hv7A4FUEqc8.getDirection(), ENUM_DIRECTION_NEUTRAL);
}

}

function onAttack_AtSwordman_Basic4(CQuWuXnbmhmwnyqKT, CQMvf9ddDo1ceTmFcyh, CQngAbXV8MyRUFUX, CQG3cpatEv84cxUJEv)
{
if(!CQuWuXnbmhmwnyqKT) return false;
MagicSword_BasiconAttack(CQuWuXnbmhmwnyqKT, CQMvf9ddDo1ceTmFcyh, CQngAbXV8MyRUFUX, CQG3cpatEv84cxUJEv);
Calldaimus_onAttack(CQuWuXnbmhmwnyqKT,CQMvf9ddDo1ceTmFcyh, CQngAbXV8MyRUFUX, CQG3cpatEv84cxUJEv);
}

function onEndCurrentAni_AtSwordman_Basic4(CQhLCKmxNysXk2nBPSU9)
{
if(!CQhLCKmxNysXk2nBPSU9) return;
CQhLCKmxNysXk2nBPSU9.sq_IntVectClear();
CQhLCKmxNysXk2nBPSU9.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true);
}


function onEnterFrame_AtSwordman_Basic2(CQpOr7R7eBjSYtnZF, CQ3P7cSOJcGGT5y13SL)
{
if(!CQpOr7R7eBjSYtnZF) return;
switch(CQ3P7cSOJcGGT5y13SL)
{
case 5:
CQpOr7R7eBjSYtnZF.resetHitObjectList();
break;
}
}

function onEnterFrame_AtSwordman_Basic2(CQpOr7R7eBjSYtnZF, CQ3P7cSOJcGGT5y13SL)
{
if(!CQpOr7R7eBjSYtnZF) return
switch(CQ3P7cSOJcGGT5y13SL)
{
case 5:
CQpOr7R7eBjSYtnZF.resetHitObjectList()
break
}
}

function onSetState_AtSwordman_Basic2(CQqueurwROvaRDtV, CQKU6HTTOXCrlzt4fy, CQkks42L4zwbhGWMjB4, CQw6TzDans4j9rr7ev)
{
if(!CQqueurwROvaRDtV) return
if(sq_GetSkillLevel(CQqueurwROvaRDtV, 62) > 0)
{
local CQZCKtWmCLo6j3r3ySr1 = sq_GetCurrentAttackBonusRate(CQqueurwROvaRDtV)
local CQzSmD73TkfVdyedp = CQqueurwROvaRDtV.sq_GetLevelData(62, 1, sq_GetSkillLevel(CQqueurwROvaRDtV, 62))
CQqueurwROvaRDtV.sq_SetCurrentAttackBonusRate(CQZCKtWmCLo6j3r3ySr1 + CQzSmD73TkfVdyedp)
}
}

function onAttack_AtSwordman_Basic2(CQOi22KHFEPG56w6IyN, CQ8moTpU92zafFw1, CQWT2ebgwhKr6xQ81v, CQV7oA9MMiUb1Jq46BfG)
{
if(!CQOi22KHFEPG56w6IyN) return false
Calldaimus_onAttack(CQOi22KHFEPG56w6IyN,CQ8moTpU92zafFw1, CQWT2ebgwhKr6xQ81v, CQV7oA9MMiUb1Jq46BfG)
}
