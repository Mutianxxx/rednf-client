function checkExecutableSkill_cirruscut(obj)  
{
	if (!obj) return false;

    local isUseSkill = obj.sq_IsUseSkill(SKILL_CIRRUSCUT);
    if (isUseSkill) 
    {
        obj.sq_AddSetStatePacket(STATE_CIRRUSCUT, STATE_PRIORITY_USER, true);
        return true;
    }
	return false;
}


function checkCommandEnable_cirruscut(obj)
{

	return true;
}




function setCharacterFristAnimation_CIRRUSCUT(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_CIRRUSCUT );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/newmage/animation/rosewhip/rose01_00.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/newmage/animation/rosewhip/rose02_00.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/newmage/animation/rosewhip/rose03_00.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/newmage/animation/rosewhip/rose04_00.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/newmage/animation/rosewhip/rosewhipfailfront_02.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/newmage/animation/rosewhip/rosewhipsuccessback_00.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/newmage/animation/rosewhip/rosewhipsuccessfront_00.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/newmage/animation/rosewhip/marionette/rosewhipbearfailfront_00.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/newmage/animation/rosewhip/marionette/rosewhipbearsuccessback_00.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/newmage/animation/rosewhip/marionette/rosewhipbearsuccessfront_19.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/newmage/animation/thornvinehold/vine/vinerose1/vinerosestart01_00.ani");


    }
}


function onKeyFrameFlag_CIRRUSCUT(obj,flagIndex)
{
    if (flagIndex == 1 &&  obj.getVar("flag").get_vector(0) == 0 )
    {

        setBobyNumber(obj,getBobyNumber(obj) + obj.sq_GetIntData(SKILL_CIRRUSCUT, 0) );

        local sizeX = obj.sq_GetIntData(SKILL_CIRRUSCUT, 1);
        local sizeY = obj.sq_GetIntData(SKILL_CIRRUSCUT, 2);
        local sizeZ = obj.sq_GetIntData(SKILL_CIRRUSCUT, 3);

        local damage = obj.sq_GetPowerWithPassive(SKILL_CIRRUSCUT , STATE_CIRRUSCUT, 0,-1, 1.0);
        local damage2 = obj.sq_GetPowerWithPassive(SKILL_CIRRUSCUT , STATE_CIRRUSCUT, 1,-1, 1.0);
        
        local z = 0;
        
        if (isDollState(obj))
        {
          z = 0;
          obj.sq_SendCreatePassiveObjectPacket(12255, 0, obj.getVar("len").get_vector(0), 2, z);
        }
        
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(1);
        obj.sq_StartWrite();
        obj.sq_WriteDword(damage);	// attackBonusRate
        obj.sq_WriteDword(65);	// attackBonusRate
        obj.sq_WriteDword(damage2);	// attackBonusRate
        obj.sq_WriteDword(sizeX);
        obj.sq_WriteDword(sizeY);
        obj.sq_WriteDword(sizeZ);
        
        obj.sq_SendCreatePassiveObjectPacket(24357, 0, obj.getVar("len").get_vector(0), 1, z);
        obj.sq_SendCreatePassiveObjectPacket(12254, 0, obj.getVar("len").get_vector(0), -1, z);
        //obj.sq_SendCreatePassiveObjectPacket(12255, 0, obj.getVar("len").get_vector(0), 2, z);
        obj.sq_SendCreatePassiveObjectPacket(12256, 0, obj.getVar("len").get_vector(0), -2, z);
    }
}

function onSetState_CIRRUSCUT(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
    if (!isDollState(obj) )
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_CIRRUSCUT);
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        obj.getVar("len").clear_vector();
        obj.getVar("len").push_vector(0);
    }else{
        local ani = obj.getVar().GetAnimationMap("cirruscut", "passiveobject/zrr_skill/newmage/animation/rosewhip/marionette/rosewhipbearready_body.ani"); 
		obj.setCurrentAnimation(ani);
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        obj.getVar("len").clear_vector();
        obj.getVar("len").push_vector(0);
    }
    
}

function onEndCurrentAni_CIRRUSCUT(obj)
{
    obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}