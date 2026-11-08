

function checkCommandEnable_SwallowSkyDrgon(obj)

{

	return true;

}

function checkExecutableSkill_SwallowSkyDrgon(obj)

{

	if(!obj) return false;

	local UncleBangValue1 =  obj.sq_IsUseSkill(SKILL_SWALLOWSKYDRAGON);

	if(UncleBangValue1)

	

{

obj.sq_IntVectClear();

obj.sq_IntVectPush(0);

obj.sq_AddSetStatePacket(STATE_SWALLOWSKYDRAGON ,  STATE_PRIORITY_IGNORE_FORCE ,  true);

return true;

	

}

	return false;

}

function onSetState_SwallowSkyDrgon(obj ,  state ,  datas ,  isResetTimer)

{

	if(!obj) return;

	local UncleBangValue1 =  obj.sq_GetVectorData(datas ,  0);

	obj.setSkillSubState(UncleBangValue1);

	obj.sq_StopMove();

	switch(UncleBangValue1)

	

{

case 0:

obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWALLOWSKYDRAGON);

local UncleBangValue2 =  obj.getCurrentAnimation().getDelaySum(false);

obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

local UncleBangValue3 =  obj.getCurrentAnimation().getDelaySum(false);

local UncleBangValue4 =  UncleBangValue2.tofloat()  /  UncleBangValue3.tofloat();

obj.getVar("swallowskydrgonSpeed").setFloat(0 ,  0.0);

obj.getVar("swallowskydrgonSpeed").setFloat(0 ,  UncleBangValue4);

break;

	

}

}

function onEndCurrentAni_SwallowSkyDrgon(obj)

{

	if(!obj || !obj.isMyControlObject()) return;

	local UncleBangValue1 =  obj.getSkillSubState();

	if(UncleBangValue1 >=  0)

	

{

obj.sq_IntVectClear();

obj.sq_AddSetStatePacket(STATE_STAND ,  STATE_PRIORITY_IGNORE_FORCE ,  true);

	

}

}

function onKeyFrameFlag_SwallowSkyDrgon(obj ,  flagIndex)

{

	if(!obj) return false;

	local UncleBangValue1 =  obj.getSkillSubState();

	switch(UncleBangValue1)

	

{

case 0:

switch(flagIndex)

{

case 10001:

if(obj.isMyControlObject())

{

obj.sq_StartWrite();

obj.sq_WriteDword(3);

obj.sq_WriteDword(14);

obj.sq_WriteDword(0);

obj.sq_WriteFloat(obj.getVar("swallowskydrgonSpeed").getFloat(0));

obj.sq_SendCreatePassiveObjectPacket(24338 ,  0 ,  0 ,  0 ,  0);

}

break;

case 10002:

if(obj.isMyControlObject())

{

obj.sq_StartWrite();

obj.sq_WriteDword(3);

obj.sq_WriteDword(14);

obj.sq_WriteDword(1);

obj.sq_SendCreatePassiveObjectPacket(24338 ,  0 ,  400 ,  0 ,  0);

}

break;

}

break;

	

}

	return true;

}

