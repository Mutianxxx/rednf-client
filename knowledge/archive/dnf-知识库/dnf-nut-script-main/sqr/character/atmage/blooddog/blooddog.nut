function checkExecutableSkill_blooddog(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_BLOODDOG);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_BLOODDOG , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}



function setCharacterFristAnimation_HellBerus(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_BLOODDOG );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/athellberus/hellberusbase_start.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/athellberus/hita_front_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/athellberus/hita_back_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/athellberus/hitb_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/athellberus/grow_eye.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/athellberus/awakening/awakeninghita_grow_hitsmoke.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/blooddog/blooddog_ready.ani");

    }
}



function checkCommandEnable_blooddog(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
    if (judgeSubBloodValue(obj,0))
    return false;
	return true;
}


function onSetState_BLOODDOG(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	obj.sq_StopMove();



    obj.getVar("jl").clear_vector();
    obj.getVar("jl").push_vector(280);
//    obj.sq_SetXScroll(50,200,200,0);	
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODDOG_READY);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);
}

function onEndCurrentAni_BLOODDOG(obj)
{
	if(!obj.isMyControlObject()) {
		return;
	}
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

function onProc_BLOODDOG(obj)
{

	local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
	local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);
    local len = obj.getVar("jl").get_vector(0);

	if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && leftPress) len = 100;
	if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && rightPress) len = 100;

    obj.getVar("jl").clear_vector();
    obj.getVar("jl").push_vector(len);

}

function onKeyFrameFlag_BLOODDOG(obj,flagIndex)
{


	if (flagIndex == 1 && obj.isMyControlObject() )
	{

        local attackBonusRate0 = obj.sq_GetBonusRateWithPassive(SKILL_BLOODDOG, STATE_BLOODDOG, 0, 1.0);
        local attackBonusRate1 = obj.sq_GetBonusRateWithPassive(SKILL_BLOODDOG, STATE_BLOODDOG, 1, 1.0);

		sq_BinaryStartWrite();
		sq_BinaryWriteDword(attackBonusRate0);	// attackBonusRate
        sq_BinaryWriteDword(attackBonusRate1);
        sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODDOG, 0));//time
        sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODDOG, 1));//oncetime
        if (obj.getVar("jl").get_vector(0) == 280)
        {
            sq_BinaryWriteDword(0);
            createHellBerus01_Eye(obj);
        }else{
            sq_BinaryWriteDword(1);
        }
		obj.sq_SendCreatePassiveObjectPacket(24365, 0, obj.getVar("jl").get_vector(0), 2, -10);
        createHellBerus01_Start(obj);
//-123  0  3
	}
	return true;
}



function createHellBerus01_Start(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athellberus/hellberusbase_start.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),300);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,obj.getObjectHeight()/2);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createHellBerus01_HitEffectFront01(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athellberus/hita_front_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),-100);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,67);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createHellBerus01_HitEffectBack01(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athellberus/hita_back_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),-100);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 1,67);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createHellBerus01_HitEffectHitB(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athellberus/hitb_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 1,67);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createHellBerus01_Eye(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athellberus/grow_eye.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),280);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 3,20 + obj.getObjectHeight()/2);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createHellBerus02_Smoke(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athellberus/awakening/awakeninghita_grow_hitsmoke.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 3,20 + obj.getObjectHeight()/2);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



