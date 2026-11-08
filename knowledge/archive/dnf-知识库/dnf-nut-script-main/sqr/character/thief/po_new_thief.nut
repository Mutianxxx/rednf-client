
function setCustomData_po_new_thief(obj, receiveData)
{
	if(!obj)
		return;
    setCustomDataEtc_po_new_thief(obj, receiveData);


}


function onKeyFrameFlag_po_new_thief(obj, flagIndex)
{

	if (!obj)
		return 0;

    return onKeyFrameFlagEtc_po_new_thief(obj, flagIndex);


}

function onAttack_po_new_thief(obj,damager, boundingBox, isStuck)
{

	if (!obj)
		return 0;
    onAttackEtc_po_new_thief(obj,damager, boundingBox, isStuck);
}




function onTimeEvent_po_new_thief(obj, timeEventIndex, timeEventCount)
{
	if (!obj)
		return 0;
    onTimeEventEtc_po_new_thief(obj, timeEventIndex, timeEventCount);
}





function procAppend_po_new_thief(obj)
{
//
	if (!obj)
		return 0;
    procAppendEtc_po_new_thief(obj);


}



function onEndCurrentAni_po_new_thief(obj)
{

	if (!obj)
		return 0;
    //onEndCurrentAniEtc_po_new_thief(obj);


}


function onKeyFrameFlagEtc_po_new_thief(obj, flagIndex)
{
    local id = obj.getVar("id").get_vector(0 );

	if (id == 217)
    {
        if (flagIndex == 999)
        {

            local isP = obj.getVar("var").get_vector(0);
            local saveT = obj.getVar("var").get_vector(1);
            local atkT = obj.getVar("var").get_vector(2);
            local pushA = obj.getVar("var").get_vector(3);

            local state = obj.getVar("state").get_vector(0);

            if (state == 0)
            {
                obj.getVar("state").set_vector(0,1);
                local ani = obj.getVar().GetAnimationMap("1", 
                "passiveobject/new_thief/animation/livingdead/attact1start_livingdead.ani"); 
                obj.setCurrentAnimation(ani);

                obj.getVar("magic").clear_obj_vector();
                obj.getVar("magic").push_obj_vector( createliliyaLoopMagicEffect(obj) );

            }else if (state == 1)
            {
                obj.getVar("state").set_vector(0,2);
                local ani = obj.getVar().GetAnimationMap("2", 
                "passiveobject/new_thief/animation/livingdead/attack2start_livingdead.ani"); 
                obj.setCurrentAnimation(ani);
            }else if (state == 2)
            {
                obj.getVar("state").set_vector(0,3);
                local ani = obj.getVar().GetAnimationMap("3", 
                "passiveobject/new_thief/animation/livingdead/attack2loop_livingdead.ani"); 
                obj.setCurrentAnimation(ani);

                obj.setTimeEvent(0,saveT, 0, false );
                obj.setTimeEvent(1,atkT, 0, false );

            }else if (state == 3)
            {

            }else if (state == 4)
            {
                local pooled = obj.getVar("magic").get_obj_vector(0);
                if (pooled)
                    pooled.setValid(false);
                sq_SendDestroyPacketPassiveObject(obj);
            }
        }
    }
    return true;
}


function onTimeEventEtc_po_new_thief(obj, timeEventIndex, timeEventCount)
{
	if (!obj)
		return 0;

    local id = obj.getVar("id").get_vector(0 );
	if (id == 217)
    {
        local isP = obj.getVar("var").get_vector(0);
        local saveT = obj.getVar("var").get_vector(1);
        local atkT = obj.getVar("var").get_vector(2);
        local pushA = obj.getVar("var").get_vector(3);

        local state = obj.getVar("state").get_vector(0);

        if (state == 3)
        {
            if (timeEventIndex == 0)
            {
                obj.getVar("state").set_vector(0,4);
                local ani = obj.getVar().GetAnimationMap("4", 
                "passiveobject/new_thief/animation/livingdead/end_livingdead.ani"); 
                obj.setCurrentAnimation(ani);

            }else if (timeEventIndex == 1)
            {



                local maxD = obj.getVar("var").get_vector(4);
                local minS = obj.getVar("var").get_vector(5);
                local maxS = obj.getVar("var").get_vector(6);
                local maxT = obj.getVar("var").get_vector(7);

                local y = obj.getVar("var").get_vector(8);

                sq_BinaryStartWrite();
                sq_BinaryWriteDword( pushA );
                sq_BinaryWriteDword(218);
                sq_BinaryWriteDword(maxD + sq_getRandom(0,50).tointeger() );
                sq_BinaryWriteDword(minS + sq_getRandom(0,5).tointeger());
                sq_BinaryWriteDword(maxS + sq_getRandom(0,5).tointeger());
                sq_BinaryWriteDword(maxT + sq_getRandom(0,25).tointeger());
                sq_BinaryWriteDword(0);
                sq_BinaryWriteDword(isP);
                sq_BinaryWriteDword( sq_getRandom(-y,y ));
                sq_SendCreatePassiveObjectPacketPos(obj,24388, 0, obj.getXPos() , obj.getYPos() + 1, 37);

                sq_BinaryStartWrite();
                sq_BinaryWriteDword( pushA );
                sq_BinaryWriteDword(218);
                sq_BinaryWriteDword(maxD + sq_getRandom(0,50).tointeger());
                sq_BinaryWriteDword(minS + sq_getRandom(0,5).tointeger());
                sq_BinaryWriteDword(maxS + sq_getRandom(0,5).tointeger());
                sq_BinaryWriteDword(maxT + sq_getRandom(0,25).tointeger());
                sq_BinaryWriteDword( obj.getVar("var").get_vector(9) );
                sq_BinaryWriteDword(isP);
                sq_BinaryWriteDword( sq_getRandom(-y,y ));
                sq_SendCreatePassiveObjectPacketPos(obj,24388, 0, obj.getXPos() , obj.getYPos() + 1, 37);

                sq_BinaryStartWrite();
                sq_BinaryWriteDword( pushA );
                sq_BinaryWriteDword(218);
                sq_BinaryWriteDword(maxD + sq_getRandom(0,50).tointeger());
                sq_BinaryWriteDword(minS + sq_getRandom(0,5).tointeger());
                sq_BinaryWriteDword(maxS + sq_getRandom(0,5).tointeger());
                sq_BinaryWriteDword(maxT + sq_getRandom(0,25).tointeger());
                sq_BinaryWriteDword( -obj.getVar("var").get_vector(9) );
                sq_BinaryWriteDword(isP);
                sq_BinaryWriteDword( sq_getRandom(-y,y ));
                sq_SendCreatePassiveObjectPacketPos(obj,24388, 0, obj.getXPos() , obj.getYPos() + 1, 37);


            }
        }

    }

}












function setCustomDataEtc_po_new_thief(obj, receiveData)
{


	local attackBonusRate = receiveData.readDword();// 占??占???(%)	
	local id = receiveData.readDword();

    obj.getVar("id").clear_vector();
    obj.getVar("id").push_vector(id);

	if (id == 218)
    {

        local rand = sq_getRandom(0,100).tointeger();

        if (rand < 33)
        {
            local ani = obj.getVar().GetAnimationMap("0", 
                    "passiveobject/new_thief/animation/livingdead/darkmatter/newdarkmatter2_01.ani"); 
            obj.setCurrentAnimation(ani);
        }else if (rand < 66)
        {
            local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/new_thief/animation/livingdead/darkmatter/newdarkmatter2_01.ani"); 
            obj.setCurrentAnimation(ani);
        }else{
            local ani = obj.getVar().GetAnimationMap("2", 
                    "passiveobject/new_thief/animation/livingdead/darkmatter/newdarkmatter3_01.ani"); 
            obj.setCurrentAnimation(ani);
        }

        if (rand <  50)
        {
            local attackInfo = sq_GetCustomAttackInfo(obj, 0);
            sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate );
            sq_SetCurrentAttackInfo(obj, attackInfo);
        }else
        {
            local attackInfo = sq_GetCustomAttackInfo(obj, 1);
            sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate );
            sq_SetCurrentAttackInfo(obj, attackInfo);
        }
        local maxD = receiveData.readDword();
        local minS = receiveData.readDword();
        local maxS = receiveData.readDword();
        local maxT = receiveData.readDword();

        local z = receiveData.readDword();
        local isP = receiveData.readDword();
        local y = receiveData.readDword();

        obj.getVar("var").clear_vector();
        obj.getVar("var").push_vector( obj.getXPos() );
        obj.getVar("var").push_vector( obj.getYPos() );
        obj.getVar("var").push_vector( obj.getZPos() );
        obj.getVar("var").push_vector( maxD );
        obj.getVar("var").push_vector( minS );
        obj.getVar("var").push_vector( maxS );
        obj.getVar("var").push_vector( maxT );
        obj.getVar("var").push_vector(z);
        obj.getVar("var").push_vector( isP );
        obj.getVar("var").push_vector( y );


    }else if (id == 217)
    {
        local isP = receiveData.readDword();
        local saveT = receiveData.readDword();
        local atkT = receiveData.readDword();
        local pushA = receiveData.readDword();

        local distance = receiveData.readDword();
        local minSmoke = receiveData.readDword();
        local maxSmoke = receiveData.readDword();
        local maxT = receiveData.readDword();

        local offsetY = receiveData.readDword();
        local offsetZ = receiveData.readDword();

		obj.getVar("var").clear_vector();
		obj.getVar("var").push_vector(isP);
		obj.getVar("var").push_vector(saveT);
		obj.getVar("var").push_vector(atkT);
		obj.getVar("var").push_vector(pushA);

		obj.getVar("var").push_vector(distance);
		obj.getVar("var").push_vector(minSmoke);
		obj.getVar("var").push_vector(maxSmoke);
		obj.getVar("var").push_vector(maxT);

		obj.getVar("var").push_vector(offsetY)
		obj.getVar("var").push_vector(offsetZ);

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);

        local ani = obj.getVar().GetAnimationMap("0", 
                    "passiveobject/new_thief/animation/livingdead/start_livingdead.ani"); 
        obj.setCurrentAnimation(ani);

    }

}


function onAttackEtc_po_new_thief(obj,damager, boundingBox, isStuck)
{

    local id = obj.getVar("id").get_vector(0 );
	if (id == 218)
    {
        if (obj.getVar("var").get_vector(8) == 1)
        {
            if (damager.isObjectType(OBJECTTYPE_ACTIVE))
                sq_SendDestroyPacketPassiveObject(obj);	
        }
    }
}


function procAppendEtc_po_new_thief(obj)
{

    local id = obj.getVar("id").get_vector(0 );
	if (id == 218)
    {

        local startX = obj.getVar("var").get_vector(0);
        local startY = obj.getVar("var").get_vector(1);
        local startZ = obj.getVar("var").get_vector(2);

        local maxD = obj.getVar("var").get_vector(3);
        local minS = obj.getVar("var").get_vector(4);
        local maxS = obj.getVar("var").get_vector(5);
        local maxT = obj.getVar("var").get_vector(6);
        local z = obj.getVar("var").get_vector(7);
        local y = obj.getVar("var").get_vector(9);
        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);
        if (currentT > maxT)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }else
        {
            local v = sq_GetUniformVelocity(0, maxD, currentT , maxT);
            local vy = sq_GetUniformVelocity(0, y, currentT , maxT);
            local vz = sq_GetUniformVelocity(0, z, currentT , maxT);
            local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
            sq_setCurrentAxisPos(obj, 0, dstX);
            sq_setCurrentAxisPos(obj, 1, startY + vy);
            sq_setCurrentAxisPos(obj, 2, startZ + vz);

            local size = sq_GetUniformVelocity( minS , maxS , currentT , maxT);

            local currentAni = sq_GetCurrentAnimation(obj);

            local sizeRate = size.tofloat()/100.0;
            currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
            currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
            sq_SetAttackBoundingBoxSizeRate(currentAni, sizeRate, sizeRate, sizeRate);

        }

    }
}