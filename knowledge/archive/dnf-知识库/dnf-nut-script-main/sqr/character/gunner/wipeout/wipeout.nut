



 
function checkExecutableSkill_gunner_wipeout(_teXW7KIjhfe5Igv)
{
 if(!_teXW7KIjhfe5Igv) return false; 
 local w1gIC7ZCnmyIfqlLgpYoNS2 = _teXW7KIjhfe5Igv.sq_IsUseSkill(237); 
 if(w1gIC7ZCnmyIfqlLgpYoNS2) 
 {
 _teXW7KIjhfe5Igv.sq_AddSetStatePacket(237, STATE_PRIORITY_USER, false); 
 return true; 
 }
 return false; 
} ;

 
function checkCommandEnable_gunner_wipeout(obj)
{
 if(!obj) return false; 
 local flagIndex = obj.sq_GetState(); 
 if(flagIndex == STATE_STAND) 
 return true; 
 if(flagIndex == STATE_ATTACK) 
 {
 return obj.sq_IsCommandEnable(237); 
 }
 return true; 
} ;

 
function onSetState_gunner_wipeout(obj, flagIndex, faU0lOPUA8, Jq4OqVuHr52GMVj)
{
	if(!obj) return; 
	obj.sq_StopMove(); 
	obj.sq_SetCurrentAnimation(118); 
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	
		local skill_level = sq_GetSkillLevel(obj, SKILL_GUNNER_WIPEOUT);
	local count = sq_GetLevelData(obj, SKILL_GUNNER_WIPEOUT, 1, skill_level)
	local ani = obj.sq_GetCurrentAni();
	local delay = ani.getDelaySum(8, 9);
	obj.getVar().clear_timer_vector();
	obj.getVar().push_timer_vector();
	local t = obj.getVar().get_timer_vector(0);
	t.setParameter((delay-10) / count, -1);
	t.resetInstant(0);
} ;

function onProc_gunner_wipeout(obj)
{
	if (!obj) return;
	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	if (frmIndex >= 8 && frmIndex < 10)
	{
		local t = obj.getVar().get_timer_vector(0);
		if (t)
		{
		if (t.isOnEvent(obj.sq_GetStateTimer()) == true)
			{
				local particleCreater = obj.getVar("wipeout").GetparticleCreaterMap("wipeout", "character/gunner/particle/deadlyapproach.ptl", obj);
				particleCreater.Restart(0);
				particleCreater.SetPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(),0),obj.getYPos()-1, obj.getZPos());
				sq_AddParticleObject(obj, particleCreater);
			}
		}
	}
	
	local Count = obj.getMyPassiveObjectCount(22001);
	for(local i=0;i<Count;++i)
	{
		local object = obj.getMyPassiveObject(22001, i);
		local objecttt = obj.getVar("wipeout").is_obj_vector(object);
		if(object && objecttt)
		{
			setCurrentAnimationFromCutomIndex(object, 3);
			local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_GUNNER_WIPEOUT, STATE_GUNNER_WIPEOUT, 0, 1.0)
			local attackInfo = sq_GetCurrentAttackInfo(object);
			sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		}
	}
}
 
 function onCreateObject_gunner_wipeout(obj, createObject)
{
	if(!obj) return;
	local state = obj.sq_GetState();
	if(state == STATE_GUNNER_WIPEOUT)
	{
		local Object = sq_GetCNRDObjectToCollisionObject(createObject); 
		if(Object && Object.getCollisionObjectIndex() == 22001)
		{
			obj.getVar("wipeout").push_obj_vector(Object);
		}
	}
}
 
function onKeyFrameFlag_gunner_wipeout(obj, flagIndex)
{
 	if(!obj) return false;
 	switch(flagIndex)
 	{
		 case 1:
			 sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/wipeout/wipeoutattack01back_11.ani", ENUM_DRAWLAYER_BOTTOM, true);
			 sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/wipeout/wipeoutfront_06.ani", ENUM_DRAWLAYER_NORMAL, true);
			 if(obj.sq_IsMyControlObject())
			 {
				 sq_SetMyShake(obj, 10, 300); 
				 obj.sq_StartWrite();
				 obj.sq_WriteDword(SKILL_GUNNER_WIPEOUT); 
				 obj.sq_WriteDword(1); 
				 obj.sq_SendCreatePassiveObjectPacket(24371, 0, 0, 0, 0); 
			 }
		 break;
		 case 5:
				sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/wipeout/wipeoutglowback_01.ani", ENUM_DRAWLAYER_NORMAL, true);
				sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/wipeout/wipeoutattack02back_01.ani", 0, -1, 0);
				sq_AddDrawOnlyAniFromParent(obj, "passiveobject/character/gunner/animation/wipeout/wipeoutattack02_hitf_02.ani", 0, 0, 0);
		 break;
	 }
	return true;
} ;




function onEndCurrentAni_gunner_wipeout(obj)
{
	if(!obj) return;
	if(obj.sq_IsMyControlObject())
	//obj.getVar("wipeout").clear_obj_vector();
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); 
}
