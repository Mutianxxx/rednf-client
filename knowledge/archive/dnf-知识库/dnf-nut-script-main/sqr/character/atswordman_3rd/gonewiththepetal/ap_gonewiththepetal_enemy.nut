function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_gonewiththepetal_enemy")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_gonewiththepetal_enemy")
}

function sq_AddEffect(appendage)
{
}

function proc_appendage_gonewiththepetal_enemy(appendage)
{
	if(!appendage) {
		return;
	}
	local DamageMonster = appendage.getParent();
	local ChrMater = appendage.getSource();
	local SqrChr = sq_GetCNRDObjectToSQRCharacter(ChrMater);
	local ChrState = ChrMater.getState();
	local ChrSubState = SqrChr.getSkillSubState();
	local pAni = SqrChr.getCurrentAnimation();
	local frmIndex = sq_GetAnimationFrameIndex(pAni);

	local t = appendage.getVar().get_timer_vector(0);
	local CurrentT = appendage.getTimer().Get();
	if(CurrentT >= 1000)
	{
		if(t.isOnEvent(CurrentT) == true)
		{
			local ObjectHeight = sq_GetObjectHeight(DamageMonster);
			local exp02 = "passiveobject/atswordman_3rd/atanimation/atgonewiththepetal/explosiona2_02.ani";
			ATSwordman_Create(DamageMonster,exp02,ENUM_DRAWLAYER_NORMAL,0,1,0,0,100,0,100,"exp02");
			local Damage = SqrChr.sq_GetBonusRateWithPassive(SKILL_GONEWITHTHEPETAL, SKILL_GONEWITHTHEPETAL, 1, 1.0);
			local max = 3;

			local ap = sq_getNewAttackInfoPacket();
			ap.power = Damage;
			ap.powerRate = Damage;
			ap.element = ENUM_ELEMENT_NONE;
			ap.useWeapon = true;
			ap.eType = ATTACKTYPE_PHYSICAL;
			ap.hitStunTimeAttackerDamager = 15000;

			for (local i = 0; i < max ; i++)
			{
				sq_SendHitObjectPacketByAttackInfo(SqrChr, DamageMonster, ap);
			}
		}
	}
}

function onStart_appendage_gonewiththepetal_enemy(appendage)
{
	if(!appendage)
	{
		return;
	}
	ATSwordmanGetVarTimer(appendage, 1, 150, 1);
}
