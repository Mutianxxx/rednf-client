

function checkCommandEnable_ContractSpaceByMagic(obj)

{

	return true;

}

function checkExecutableSkill_ContractSpaceByMagic(obj)

{

	if(!obj) return false;

	local UncleBangValue1 =  obj.sq_IsUseSkill(SKILL_CONTRACTSPACEBYMAGIC);

	if(UncleBangValue1)

	

{

obj.sq_IntVectClear();

obj.sq_IntVectPush(0);

obj.sq_AddSetStatePacket(STATE_CONTRACTSPACEBYMAGIC ,  STATE_PRIORITY_IGNORE_FORCE ,  true);

return true;

	

}

	return false;

}

function onSetState_ContractSpaceByMagic(obj ,  state ,  datas ,  isResetTimer)

{

	if(!obj) return;

	local UncleBangValue1 =  obj.sq_GetVectorData(datas ,  0);

	obj.setSkillSubState(UncleBangValue1);

	obj.sq_StopMove();

	switch(UncleBangValue1)

	

{

case 0:

obj.sq_SetCurrentAnimation(CUSTOM_ANI_CONTRACTSPACEBYMAGIC1);

break;

case 1:

obj.sq_SetCurrentAnimation(CUSTOM_ANI_CONTRACTSPACEBYMAGIC2);

local UncleBangValue2 =  -sq_GetIntData(obj ,  SKILL_CONTRACTSPACEBYMAGIC ,  0);

if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT ,  ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() ==  ENUM_DIRECTION_LEFT)

UncleBangValue2 =  -UncleBangValue2;

if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT ,  ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() ==  ENUM_DIRECTION_RIGHT)

UncleBangValue2 =  -UncleBangValue2;

local UncleBangValue3 =  0;

if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP ,  ENUM_SUBKEY_TYPE_ALL))

UncleBangValue3 =  -sq_GetIntData(obj ,  SKILL_CONTRACTSPACEBYMAGIC ,  1);

if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN ,  ENUM_SUBKEY_TYPE_ALL))

UncleBangValue3 =  sq_GetIntData(obj ,  SKILL_CONTRACTSPACEBYMAGIC ,  1);

sq_MoveToNearMovablePos(obj ,  sq_GetDistancePos(sq_GetXPos(obj) ,  obj.getDirection() ,  UncleBangValue2) ,  sq_GetYPos(obj) + UncleBangValue3 ,  sq_GetZPos(obj) ,  sq_GetXPos(obj) ,  sq_GetYPos(obj) ,  sq_GetZPos(obj) ,  20 ,  -1 ,  3);

sq_createPooledObject(obj ,  "passiveobject/unclebang_shared_passive_object/atpriest/animation/3_sorceress/atcontractspacebymagic/contractspacebymagicappear_02.ani" ,  0 ,  0 ,  0 ,  100 ,  1.0 ,  0 ,  0 ,  1);

break;

	

}

	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

}

function onEndCurrentAni_ContractSpaceByMagic(obj)

{

	if(!obj || !obj.isMyControlObject()) return;

	local UncleBangValue1 =  obj.getSkillSubState();

	switch(UncleBangValue1)

	

{

case 0:

obj.sq_IntVectClear();

obj.sq_IntVectPush(1);

obj.sq_AddSetStatePacket(STATE_CONTRACTSPACEBYMAGIC ,  STATE_PRIORITY_IGNORE_FORCE ,  true);

break;

case 1:

obj.sq_IntVectClear();

obj.sq_AddSetStatePacket(STATE_STAND ,  STATE_PRIORITY_IGNORE_FORCE ,  true);

break;

	

}

}

