function setCustomData_po_spearattack(obj, receiveData)
{

   
    local randXZ0 = receiveData.readDword();
    local randXZ1 = receiveData.readDword();
    local jl = receiveData.readDword();
    local at = receiveData.readDword();

    obj.getVar("dama").clear_obj_vector();

    obj.getVar("state").clear_vector();
    obj.getVar("state").push_vector(0);

    obj.getVar("jl").clear_vector();
    obj.getVar("jl").push_vector(jl);

    obj.getVar("jl1").clear_vector();
    obj.getVar("jl1").push_vector(0);

    local rand = sq_getRandom(randXZ0 , randXZ1).tofloat();

    obj.getVar("ud").clear_vector();
    obj.getVar("ud").push_vector(randXZ1);

    if (at == 1)
    {
		local attackInfo = sq_GetCustomAttackInfo(obj, 0);
		sq_SetCurrentAttackInfo(obj, attackInfo);
    }
    if (at == 2)
    {
		local attackInfo = sq_GetCustomAttackInfo(obj, 1);
		sq_SetCurrentAttackInfo(obj, attackInfo);
    }
    if (at == 3)
    {
		local attackInfo = sq_GetCustomAttackInfo(obj, 2);
		sq_SetCurrentAttackInfo(obj, attackInfo);
    }
    sq_SetCustomRotate(obj,1.57 + rand /100.0);



	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/lancer/animation/spearattack/light.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
    pooledObj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());

    sq_SetCustomRotate(pooledObj,rand /100.0);

	sq_AddObject(obj,pooledObj,2,false);	

}


function onTimeEvent_po_spearattack(obj, timeEventIndex, timeEventCount)
{
    if (obj.getVar("state").get_vector(0) == 1)
    {
        if (timeEventIndex == 0)
        {
            break_spearattack(obj);
        }
    }
}

function onAttack_po_spearattack(obj,damager, boundingBox, isStuck)
{
    if (obj.getVar("state").get_vector(0) == 0)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
        obj.getVar("dama").push_obj_vector(damager);
        obj.getVar("height").clear_vector();
        obj.getVar("height").push_vector(sq_getRandom(0 , damager.getObjectHeight()/2));

        obj.setTimeEvent(0,3000,0,false);
        
        if (sq_GetDirection(obj) == sq_GetDirection(damager))
        {
            obj.getVar("direc").clear_vector();
            obj.getVar("direc").push_vector(1);//back
        }else{
            obj.getVar("direc").clear_vector();
            obj.getVar("direc").push_vector(0);//behind
        }

        sq_SendCreatePassiveObjectPacketPos(obj,12180, 0, damager.getXPos(), damager.getYPos() - 1, damager.getZPos() );

    }

}

function break_spearattack(obj)
{
    sq_SendDestroyPacketPassiveObject(obj);
}

function procAppend_po_spearattack(obj)
{
    local cujl = obj.getVar("jl1").get_vector(0);
    local maxjl = obj.getVar("jl").get_vector(0);
    local y = obj.getVar("ud").get_vector(0);
    local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {
        if (cujl > maxjl)
        {
            break_spearattack(obj);
        }

        if (sq_GetDirection(obj) == ENUM_DIRECTION_LEFT)
        {
            obj.setCurrentPos(obj.getXPos() - 15,obj.getYPos(),obj.getZPos());
        }else{
            obj.setCurrentPos(obj.getXPos() + 15,obj.getYPos(),obj.getZPos());
        }

        if (y>0)
        {
            obj.setCurrentPos(obj.getXPos(),obj.getYPos() -1 ,obj.getZPos());
        }else{
            obj.setCurrentPos(obj.getXPos(),obj.getYPos() +1 ,obj.getZPos());
        }

        obj.getVar("jl1").clear_vector();
        obj.getVar("jl1").push_vector(cujl + 15);
    }

    if (state == 1)
    {
        local damager = obj.getVar("dama").get_obj_vector(0);

        local posX = sq_GetDistancePos(damager.getXPos(), obj.getDirection(), 123);

        if (obj.getVar("direc").get_vector(0) == 1)
        {
            obj.setCurrentDirection(damager.getDirection());
        }else{
			obj.setCurrentDirection(sq_GetOppositeDirection(damager.getDirection()));
        }

        obj.setCurrentPos(posX,damager.getYPos() -1  ,damager.getZPos() + damager.getObjectHeight()/4 + obj.getVar("height").get_vector(0) );

    }



//    obj.setCurrentPos(obj.getXPos() + xSpeed/75,obj.getYPos() / 50,obj.getZPos());
}