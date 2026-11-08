//2020-10-20

function checkExecutableSkill_bloodcastle(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_BLOODCASTLE);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_BLOODCASTLE , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}

function checkCommandEnable_bloodcastle(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
    if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_BLOODCASTLE, 3)))
    return false;


	return true;
}


function setCharacterFristAnimation_RumbleDog(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_BLOODCASTLE );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atrumbledog/rumbledog_floor_cast01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atrumbledog/rumbledog_floor_end01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atrumbledog/rumbledog_floor_loop01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atrumbledog/rumbledog_floor_shot01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atrumbledog/dog/a/doga01_dog01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atrumbledog/dog/b/dogb01_dog01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atrumbledog/dog/c/dogc01_dog01.ani");


    }
}



function onSetState_BLOODCASTLE(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	obj.sq_StopMove();
    setBloodValue(obj,-obj.sq_GetIntData(SKILL_BLOODCASTLE, 3));
    if (obj.isMyControlObject())
        sq_flashScreen(obj,150,0,1500,230, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

	obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODCASTLE_READY);
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
//    onKeyFrameFlag_BLOODCASTLE(obj,1);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);

}


function onEndCurrentAni_BLOODCASTLE(obj)
{
	if(!obj.isMyControlObject()) {
		return;
	}
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}



function onKeyFrameFlag_BLOODCASTLE(obj,flagIndex)
{
	if(!obj)
		return false;

	if (flagIndex == 1 && obj.isMyControlObject() )
	{

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(1);

        local len = obj.sq_GetIntData(SKILL_BLOODCASTLE, 2);

		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

		local upPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL);
		local downPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL);

		if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && rightPress) len = obj.sq_GetIntData(SKILL_BLOODCASTLE, 6);
		if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && leftPress) len = obj.sq_GetIntData(SKILL_BLOODCASTLE, 6);


        local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOODCASTLE, STATE_BLOODCASTLE, 0, 1.0);
		sq_BinaryStartWrite();
		sq_BinaryWriteDword(attackBonusRate);	// attackBonusRate
        sq_BinaryWriteDword(0);
        sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODCASTLE, 0));
        sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODCASTLE, 1));
        sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODCASTLE, 4));
        sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODCASTLE, 5));
		obj.sq_SendCreatePassiveObjectPacket(24366, 0, len , 1, 0);
        return true;
	}
}
