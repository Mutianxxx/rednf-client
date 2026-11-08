function setCustomData_po_shaowarea(obj, receiveData)
{
	local time = receiveData.readDword();
	obj.getVar("state").clear_vector();
	obj.getVar("state").push_vector(0);
	local ani = obj.getCustomAnimation(0);
	obj.setCurrentAnimation(ani);
	obj.getVar("assassinTargetList").clear_obj_vector();
	obj.getVar("values").clear_vector();
//	obj.getVar("values").push_vector(200);
	obj.getVar("values").push_vector(time);

	obj.getVar("attackRate").clear_vector();
	obj.getVar("attackRate").push_vector(0);

}




function findAllNoHitEnemy_ShaowArea(obj)
{
	local objectManager = obj.getObjectManager();
	obj.getVar("assassinTargetList").clear_obj_vector();
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE)&&object.isInDamagableState(obj) )
		{
			local activeObj = sq_GetCNRDObjectToActiveObject(object);
            
            if ( !CNSquirrelAppendage.sq_IsAppendAppendage(activeObj, "character/thief/4_shadow/shaowarea/ap_shaowarea_enemy.nut") )
            {
                obj.getVar("assassinTargetList").push_obj_vector(activeObj);
            }
		}
	}
    
    if (obj.getVar("assassinTargetList").get_obj_vector_size() > 0)
    {
        obj.setTimeEvent(0,obj.getVar("values").get_vector(0),obj.getVar("assassinTargetList").get_obj_vector_size(),false);
        local dama = obj.getVar("attackRate").get_vector(0);

        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	

        local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_SHAOWAREA);
        sq_SetCurrentAttackInfo(obj, atk );

        local attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, dama);
    }

}

function onTimeEvent_po_shaowarea(obj, timeEventIndex, timeEventCount)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {
        if (timeEventIndex == 0)
        {
            local tarMaxCount = obj.getVar("assassinTargetList").get_obj_vector_size();

            if (timeEventCount <= tarMaxCount)
            {
                local tar = obj.getVar("assassinTargetList").get_obj_vector(timeEventCount - 1);
                if (tar)
                {

                    local posX = sq_GetDistancePos(tar.getXPos(), tar.getDirection(), -100);
                    local posY = tar.getYPos();
                    local posZ = tar.getZPos();

                    sq_BinaryStartWrite();
                    sq_BinaryWriteDword(0);
                    sq_BinaryWriteDword(96);
                    sq_BinaryWriteDword( timeEventCount % 4 );
                    sq_BinaryWriteDword( tar.getDirection() );
//CUSTOM_ANI_SHAOWAREA_NORMALATTACK <- 150
//151
//152
//153
//154
                    sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, posX, posY,posZ);
                    createShaowAreaHitEffect(obj,tar);
                    createShaowArea5HitShockEffect(obj,tar);
                    createShaowArea3HitGround(obj,tar);
                    createShaowArea6BlackDust(obj,tar);

                    if (timeEventCount >= 2)
                    {
//                        local tar1 = obj.getVar("assassinTargetList").get_obj_vector(timeEventCount - 2);
//                        createShaowAreaSpeedLine(obj,tar1,tar);

                    }

                    sq_SendHitObjectPacket(obj,tar,0,0,0);


                }



                
            }else{



            }
        }
    }
}


function createShaowAreaSpeedLine(obj,tar1,tar2)
{

	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/shadowdancing/shadowmove_speedlinenormal.ani");




    local lenX = abs(tar1.getXPos() - tar2.getXPos() );
    local lenY = ( (tar1.getYPos() - tar2.getYPos() ) *29 ) / 100;
    local tanAngle = lenY.tofloat() / lenX.tofloat();


	ani.setImageRate(1.0, 1.0);

    ani.setImageRate(lenX.tofloat() / 730.0, 1.0);
    //ani len = 730
	local pooledObj = sq_CreatePooledObject(ani,true);

    sq_SetCustomRotate(pooledObj,tanAngle);

//	pAni.setImageRate(wRate.tofloat(), hRate.tofloat());


	pooledObj.setCurrentPos(tar1.getXPos() ,tar1.getYPos()+1,tar1.getZPos() );// + tar1.getObjectHeight()/2);

    if (tar1.getXPos() < tar2.getXPos() )
    {
        pooledObj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
    }else{
        pooledObj.setCurrentDirection(ENUM_DIRECTION_LEFT);
    }
	sq_AddObject(obj,pooledObj,2,false);	
}

function createShaowAreaHitEffect(obj,damager)
{

	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/shadowdancing/shadowattack_shadowhitnormal.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos()+1,damager.getZPos());
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createShaowArea5HitShockEffect(obj,damager)
{

	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/shadowdancing/dattack_5hitshocknormal.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos()+1,damager.getZPos());
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createShaowArea3HitGround(obj,damager)
{

	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/shadowdancing/bstart2_3hitgroundnormal.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos()-1,damager.getZPos());
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createShaowArea6BlackDust(obj,damager)
{


	local ani = sq_CreateAnimation("","character/thief/animation/als_ani/shadowdancing/bstart2_6blackdust.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos()-2,damager.getZPos());
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}
function procAppend_po_shaowarea(obj)
{
    local state = obj.getVar("state").get_vector(0);
    local mage = obj.getTopCharacter();
    mage = sq_ObjectToSQRCharacter(mage);	
    if (mage )
    {
        obj.setCurrentPos(mage.getXPos(),mage.getYPos(),0); 
        if (state == 1)
        {


            if (!CNSquirrelAppendage.sq_IsAppendAppendage(mage, "character/thief/4_shadow/shaowarea/ap_shaowarea.nut"))
            {
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(2);
                local ani = obj.getCustomAnimation(2);
                obj.setCurrentAnimation(ani);
//                sq_SendDestroyPacketPassiveObject(obj);	
            }



        }
    }else{
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(2);
                local ani = obj.getCustomAnimation(2);
                obj.setCurrentAnimation(ani);
    }


}
function onEndCurrentAni_po_shaowarea(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        local ani = obj.getCustomAnimation(1);
        obj.setCurrentAnimation(ani);
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);

    }else if (state == 2)
    {
        //destroy
        sq_SendDestroyPacketPassiveObject(obj);	
    }
}