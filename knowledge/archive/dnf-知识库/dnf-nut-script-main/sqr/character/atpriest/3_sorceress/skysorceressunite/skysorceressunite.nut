

function checkCommandEnable_SkySorceressUnite(obj)

{

	return true;

}

function checkExecutableSkill_SkySorceressUnite(obj)

{

	if(!obj) return false;

	local UncleBangValue1 =  obj.sq_IsUseSkill(SKILL_SKYSORCERESSUNITE);

	if(UncleBangValue1)

	

{

obj.sq_IntVectClear();

obj.sq_IntVectPush(0);

obj.sq_AddSetStatePacket(STATE_SKYSORCERESSUNITE ,  STATE_PRIORITY_IGNORE_FORCE ,  true);

return true;

	

}

	return false;

}

function onSetState_SkySorceressUnite(obj ,  state ,  datas ,  isResetTimer)

{

	if(!obj) return;

	local UncleBangValue1 =  obj.sq_GetVectorData(datas ,  0);

	obj.setSkillSubState(UncleBangValue1);

	obj.sq_StopMove();

	switch(UncleBangValue1)

	

{

case 0:

obj.sq_SetCurrentAnimation(CUSTOM_ANI_SKYSORCERESSUNITE1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene01background_00.ani" ,  0 ,  -1 ,  0 ,  100 ,  1.0 ,  0 ,  0 ,  0);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene01bottom_09.ani" ,  0 ,  0 ,  0 ,  100 ,  1.0 ,  0 ,  0 ,  1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene01front_00.ani" ,  0 ,  0 ,  0 ,  100 ,  1.0 ,  0 ,  0 ,  1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitestartfront_00.ani" ,  0 ,  0 ,  0 ,  100 ,  1.0 ,  0 ,  0 ,  1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysoreceressunitestartback_04.ani" ,  0 ,  0 ,  0 ,  100 ,  1.0 ,  0 ,  0 ,  1);


break;

case 1:

obj.sq_SetCurrentAnimation(CUSTOM_ANI_SKYSORCERESSUNITE2);

obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_INFO_RITUALFORDRAGON1);

local UncleBangValue2 =  obj.sq_GetBonusRateWithPassive(SKILL_SKYSORCERESSUNITE ,  -1 ,  0 ,  1.0);

obj.sq_SetCurrentAttackBonusRate(UncleBangValue2);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene02background_00.ani" ,  0 ,  -1 ,  0 ,  100 ,  1.0 ,  0 ,  0 ,  0);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene02back01_02.ani" ,  0 ,  0 ,  0 ,  70 ,  1.0 ,  0 ,  0 ,  1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene02back02_02.ani" ,  0 ,  0 ,  0 ,  70 ,  1.0 ,  0 ,  0 ,  1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene02back03_02.ani" ,  0 ,  0 ,  0 ,  70 ,  1.0 ,  0 ,  0 ,  1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene02back04_02.ani" ,  0 ,  0 ,  0 ,  70 ,  1.0 ,  0 ,  0 ,  1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene02back05_02.ani" ,  0 ,  0 ,  0 ,  70 ,  1.0 ,  0 ,  0 ,  1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene02screencover01_00.ani" ,  0 ,  0 ,  0 ,  70 ,  1.0 ,  0 ,  0 ,  1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene02screencover02_01.ani" ,  0 ,  0 ,  0 ,  70 ,  1.0 ,  0 ,  0 ,  1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene02screencover03_01.ani" ,  0 ,  0 ,  0 ,  70 ,  1.0 ,  0 ,  0 ,  1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene02screencover04_01.ani" ,  0 ,  0 ,  0 ,  70 ,  1.0 ,  0 ,  0 ,  1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene02screencover05_01.ani" ,  0 ,  0 ,  0 ,  70 ,  1.0 ,  0 ,  0 ,  1);

break;

case 2:

obj.sq_SetCurrentAnimation(CUSTOM_ANI_SKYSORCERESSUNITE3);

obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_INFO_RITUALFORDRAGON1);

local UncleBangValue2 =  obj.sq_GetBonusRateWithPassive(SKILL_SKYSORCERESSUNITE ,  -1 ,  0 ,  1.0);

obj.sq_SetCurrentAttackBonusRate(UncleBangValue2);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene03background_00.ani" ,  0 ,  -1 ,  0 ,  100 ,  1.0 ,  0 ,  0 ,  0);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene03back_00.ani" ,  0 ,  0 ,  0 ,  100 ,  1.0 ,  0 ,  0 ,  1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene03screencover_03.ani" ,  0 ,  0 ,  0 ,  100 ,  1.0 ,  0 ,  0 ,  1);

break;

case 3:

obj.sq_SetCurrentAnimation(CUSTOM_ANI_SKYSORCERESSUNITE4);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene03bottom_00.ani" ,  0 ,  0 ,  0 ,  70 ,  1.0 ,  0 ,  0 ,  1);

sq_createPooledObject(obj ,  "character/priest/effect/animation/atskysorceressunite/atskysorceressunitescene03front_20.ani" ,  0 ,  0 ,  0 ,  70 ,  1.0 ,  0 ,  0 ,  1);

break;

case 4:

obj.sq_SetCurrentAnimation(CUSTOM_ANI_SKYSORCERESSUNITE5);

break;

	

}

}

function onEndCurrentAni_SkySorceressUnite(obj)

{

	if(!obj || !obj.isMyControlObject()) return;

	local UncleBangValue1 =  obj.getSkillSubState();

	if(UncleBangValue1 <=  3)

	

{

obj.sq_IntVectClear();

obj.sq_IntVectPush(UncleBangValue1 + 1);

obj.sq_AddSetStatePacket(STATE_SKYSORCERESSUNITE ,  STATE_PRIORITY_IGNORE_FORCE ,  true);

	

}

	if(UncleBangValue1 >=  4)

	

{

obj.sq_IntVectClear();

obj.sq_AddSetStatePacket(STATE_STAND ,  STATE_PRIORITY_IGNORE_FORCE ,  true);

	

}

}

function onKeyFrameFlag_SkySorceressUnite(obj ,  flagIndex)

{

	if(!obj) return false;

	local UncleBangValue1 =  obj.getSkillSubState();

	switch(UncleBangValue1)

	

{

case 2:

switch(flagIndex)

{

case 10001:

obj.resetHitObjectList();

break;

}

break;

case 3:

switch(flagIndex)

{

case 10001:

obj.resetHitObjectList();

obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_INFO_RITUALFORDRAGON1);

local UncleBangValue2 =  obj.sq_GetBonusRateWithPassive(SKILL_SKYSORCERESSUNITE ,  -1 ,  1 ,  1.0);

obj.sq_SetCurrentAttackBonusRate(UncleBangValue2);

break;

case 10002:

obj.resetHitObjectList();

obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_INFO_RITUALFORDRAGON2);

local UncleBangValue2 =  obj.sq_GetBonusRateWithPassive(SKILL_SKYSORCERESSUNITE ,  -1 ,  2 ,  1.0);

obj.sq_SetCurrentAttackBonusRate(UncleBangValue2);

break;

}

break;

	

}

	return true;

}


