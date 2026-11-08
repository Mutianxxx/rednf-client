function checkExecutableSkill_maddefance(obj)  
{
	if (!obj) return false;
    if (!isDollState(obj) )
    {
        local tar = findRoundNearTarget(obj,obj.sq_GetIntData(SKILL_MADDEFANCE, 0), obj.sq_GetIntData(SKILL_MADDEFANCE, 1) );
        if (tar)
        {
            local state = getDotObj(obj).getVar("state").get_vector(0);
            if (state == 0 || state == 1 || state == 2)
            {
                local isUseSkill = obj.sq_IsUseSkill(SKILL_MADDEFANCE);
                
                if (isUseSkill) 
                {
                    sendDotMadDefance(obj,tar );
                    return true;
                }
            }
        }
        return false;
    }else{
        local isUseSkill = obj.sq_IsUseSkill(SKILL_MADDEFANCE);
        if (isUseSkill) 
        {
            obj.sq_AddSetStatePacket(STATE_MADDEFANCE, STATE_PRIORITY_USER, true);
        }
    }
}
function checkCommandEnable_maddefance(obj)
{
    if (!isDollState(obj) )
    {
        return true;
    }else{
        local state = obj.sq_GetState();
        if (state == 0 || state == 8 || state == 14)
        {
            return true;
        }
        return false;
    }
}
function onSetState_MADDEFANCE(obj, state, datas, isResetTimer)
{
    local ani = obj.getVar().GetAnimationMap("maddefance", "passiveobject/zrr_skill/newmage/animation/dot/maddefance/maddyguard_body.ani"); 
	obj.setCurrentAnimation(ani);
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
}
function onKeyFrameFlag_MADDEFANCE(obj, flagIndex)
{
       if (obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);

            sq_SetMyShake(obj,3,120);
            sq_BinaryStartWrite();
            sq_BinaryWriteDword(obj.sq_GetPowerWithPassive(SKILL_MADDEFANCE, -1, 0, -1, 1.0));
            sq_BinaryWriteDword(90 );
            sq_SendCreatePassiveObjectPacketPos(obj, 24357, 0, obj.getXPos(), obj.getYPos() + 1,0);

        }
}
function onEndCurrentAni_MADDEFANCE(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}
function findRoundNearTarget(obj,chang,kuan)
{
	local objectManager = obj.getObjectManager();
    local target = null;
    local currDistance = 10000000000;
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isInDamagableState(obj) && object.isObjectType(OBJECTTYPE_ACTIVE))
        {
            if (chang + kuan < 0 )
            {
                return object;
            }else{
                if (abs(obj.getXPos() - object.getXPos())<= chang && abs(obj.getYPos() - object.getYPos())<= kuan)
                {
                    local distance = abs(obj.getXPos() - object.getXPos() ) * abs(obj.getXPos() - object.getXPos() ) + 
                                     abs(obj.getYPos() - object.getYPos() ) * abs(obj.getYPos() - object.getYPos() );
                    if (currDistance > distance)
                    {
                        currDistance = distance;
                        target = object;
                    }

                }

            }

        }
    }
    return target;
}

function sendDotMadDefance(obj,tar)
{
    local dot = getDotObj(obj);
    {

        local damage = obj.sq_GetPowerWithPassive(SKILL_MADDEFANCE, -1, 0, -1, 1.0);
        dot.getVar("state").clear_vector();
        dot.getVar("state").push_vector(5);
        dot.getVar("subState").clear_vector();
        dot.getVar("subState").push_vector(0);
        dot.getVar("value").clear_vector();
        dot.getVar("value").push_vector(damage);

        dot.getVar("tar").clear_obj_vector();
        dot.getVar("tar").push_obj_vector(tar);

        local pIntVec = sq_GetGlobalIntVector();
        dot.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
    }

}

