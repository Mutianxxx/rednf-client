function setCustomData_po_hotlove(obj, receiveData)
{
	if(!obj)
		return;

	local attackBonusRate = receiveData.readDword();// ?????(%)	
    local id = receiveData.readDword();

    if (id == 0)
    {
        local attackCount = receiveData.readDword();
        attackCount = attackCount.tointeger();
        local time = receiveData.readDword();

        local attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackeHitStunTime(attackInfo, 0);


        obj.setTimeEvent(0, time/attackCount, 0, true);
        obj.setTimeEvent(1,time,0,false);
        
        obj.getVar("dama").clear_obj_vector();
        obj.getVar("blood").clear_vector();
        obj.getVar("blood").push_vector(receiveData.readDword());
        local size = receiveData.readDword();

        local currentAni = sq_GetCurrentAnimation(obj);

        local sizeRate = size.tofloat()/100.0;
        currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
        currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
        sq_SetAttackBoundingBoxSizeRate(currentAni, sizeRate, sizeRate, sizeRate);

        obj.getVar("size").clear_vector();
        obj.getVar("size").push_vector(size);


        obj.getVar("particleObj").clear_obj_vector();
        createBloodDanceLoopFloorEffect(obj,obj.getVar("size").get_vector(0) );

        obj.getVar().clear_vector();
        obj.getVar().push_vector(0);

    }else if (id == 1) //throwbat
    {
        local attackBonusRate2 = receiveData.readDword();
        local distance = receiveData.readDword();
        local sumTime = receiveData.readDword();
        local attTime = receiveData.readDword();
        local absortBlood = receiveData.readDword();
        local isBlood = receiveData.readDword();




        local time = receiveData.readDword();

        obj.getVar("tar").clear_obj_vector();

        obj.getVar("value").clear_vector();
        obj.getVar("value").push_vector(attackBonusRate2);
        obj.getVar("value").push_vector(distance);
        obj.getVar("value").push_vector(0);
        obj.getVar("value").push_vector(sumTime);
        obj.getVar("value").push_vector(attTime);
        obj.getVar("value").push_vector(absortBlood);
        obj.getVar("value").push_vector(isBlood);
        obj.getVar("value").push_vector(time);
        obj.getVar("value").push_vector( obj.getXPos() );

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);

//        local ani = obj.getCustomAnimation(0);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/atmage/animation/atliliac/liliac_batawake.ani"); 
        obj.setCurrentAnimation(ani);

		local attackInfo = sq_GetCustomAttackInfo(obj, 17);
		sq_SetCurrentAttackInfo(obj, attackInfo);

        obj.setTimeEvent(0,20,0,false);

        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

        obj.getVar().clear_vector();
        obj.getVar().push_vector(0);

        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackeHitStunTime(attackInfo, 0);


    }else if (id == 2)//icecraft
    {

        local movX = receiveData.readDword();
        local movY = receiveData.readDword();
        local movZ = receiveData.readDword();
        local shootT = receiveData.readDword();
        local size = receiveData.readDword();
        local rate1 = receiveData.readDword();
        local rate2 = receiveData.readDword();


        obj.getVar("pos").clear_vector();
        obj.getVar("pos").push_vector( movX );//x0
        obj.getVar("pos").push_vector( movY );//y1
        obj.getVar("pos").push_vector( movZ );//z2
        obj.getVar("pos").push_vector(obj.getXPos() );//3
        obj.getVar("pos").push_vector(obj.getYPos() );//4
        obj.getVar("pos").push_vector(obj.getZPos() );//5
        obj.getVar("pos").push_vector(shootT );//6
        obj.getVar("pos").push_vector(size );//7

        
        obj.getVar("atk").clear_vector();
        obj.getVar("atk").push_vector( (attackBonusRate /100) * rate1 );
        obj.getVar("atk").push_vector( (attackBonusRate /100) * rate2 );

//        local ani = obj.getCustomAnimation(3);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/atmage/animation/aticecraft/icecraft_make.ani"); 
        obj.setCurrentAnimation(ani);
        local attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, obj.getVar("atk").get_vector(0) );


        local currentAni = sq_GetCurrentAnimation(obj);
        local sizeRate = size.tofloat() / 100.0;
        currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
        currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
        sq_SetAttackBoundingBoxSizeRate(currentAni, sizeRate, sizeRate, sizeRate);

//        sq_SetCustomRotate(obj, -0.17);	

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
    }else if (id == 3)
    {
        local id2 = receiveData.readDword();
        local ani = null;
        if (id2 == 0)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/rage/rageloop01slash_00.ani"); 
        }else if (id2 == 1)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/rage/rageloop02slash_03.ani"); 
        }else if (id2 == 2)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/rage/rageloop03slash_00.ani"); 
        }else if (id2 == 3)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/rage/rageloop04slash_03.ani"); 
        }
        obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 1);
		sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, attackBonusRate);

    }else if (id == 4)
    {

        local atkT = receiveData.readDword();
        local movT = receiveData.readDword();
        local attackBonusRate2 = receiveData.readDword();
        local attackBonusRate3 = receiveData.readDword();
        obj.setTimeEvent(0,atkT,0,true);
//        local ani = obj.getCustomAnimation(10);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/bloodmarble/throwattack_floor_round.ani"); 
        obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 2);
		sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);

        obj.getVar("t").clear_vector();
        obj.getVar("t").push_vector(atkT);
        obj.getVar("t").push_vector(movT);

        obj.getVar("att").clear_vector();
        obj.getVar("att").push_vector(attackBonusRate2);
        obj.getVar("att").push_vector(attackBonusRate3);

        obj.getVar("speed").clear_vector();
        obj.getVar("speed").push_vector(10);

        obj.getVar("size").clear_vector();
        obj.getVar("size").push_vector(100);

    }else if (id == 5)
    {
//        local ani = obj.getCustomAnimation(13);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/bloodmarble/enegry.ani"); 
        obj.setCurrentAnimation(ani);
    }else if (id == 6)
    {
        local ani = obj.getCustomAnimation(14);
        obj.setCurrentAnimation(ani);
    }else if (id == 7)
    {
        local ani = obj.getCustomAnimation(15);
        obj.setCurrentAnimation(ani);
    }else if (id == 8)
    {
//16
//17
       local distance = receiveData.readDword();
        local time = receiveData.readDword();
        local chan = receiveData.readDword();
        local kuan = receiveData.readDword();
        local landTime = receiveData.readDword();
        local atkT = receiveData.readDword();

        local addTime = receiveData.readDword();

        local atkSped = receiveData.readDword();
        local movSped = receiveData.readDword();
        local casSped = receiveData.readDword(); 

        //local ani = obj.getCustomAnimation(18);
        local ani = obj.getVar().GetAnimationMap("1",  "passiveobject/zrr_skill/newmage/animation/hotlove/hotlove_move_doll.ani");
        
        obj.setCurrentAnimation(ani);
        obj.getVar("pos").clear_vector();
        obj.getVar("pos").push_vector(obj.getXPos() );
        obj.getVar("pos").push_vector(distance );
        obj.getVar("pos").push_vector(obj.getZPos() );

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);

        obj.getVar("v").clear_vector();
        obj.getVar("v").push_vector( time );
        obj.getVar("v").push_vector( chan );
        obj.getVar("v").push_vector( kuan );
        obj.getVar("v").push_vector( landTime );
        obj.getVar("v").push_vector( atkT );
        obj.getVar("v").push_vector( addTime );
        obj.getVar("v").push_vector( atkSped );//6
        obj.getVar("v").push_vector( movSped );//7
        obj.getVar("v").push_vector( casSped );//8


        local attackInfo = sq_GetCustomAttackInfo(obj, 4);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

    }else if (id == 9)
    {
        local id2 = receiveData.readDword();
        local ani = null;
        if (id2 == 0)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/dot/madthebig/claw01_00.ani"); 
        }else if (id2 == 1)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/dot/madthebig/claw02_00.ani"); 
        }else if (id2 == 2)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/dot/madthebig/claw03_00.ani"); 
        }else if (id2 == 3)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/dot/madthebig/claw04_00.ani"); 
        }else if (id2 == 4)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/dot/madthebig/claw05_00.ani"); 
        }else if (id2 == 5)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/dot/madthebig/claw06_00.ani"); 
        }
        obj.setCurrentAnimation(ani);
        local attackInfo = sq_GetCustomAttackInfo(obj, 5);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
    }else if (id == 10)
    {
//        local ani = obj.getCustomAnimation(25);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/dot/madthebig/attackend_00.ani"); 
        obj.setCurrentAnimation(ani);
        local attackInfo = sq_GetCustomAttackInfo(obj, 6);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
    }else if (id == 11)
    {
        local atkTime = receiveData.readDword();
        local savTime = receiveData.readDword();
//        local ani = obj.getCustomAnimation(26);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/dot/terribledot/atk.ani"); 
        obj.setCurrentAnimation(ani);
        local attackInfo = sq_GetCustomAttackInfo(obj, 7);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
        obj.setTimeEvent(0,atkTime,0,false);
        obj.setTimeEvent(1,savTime,0,false);

    }else if (id == 12)
    {
        local atkTime = receiveData.readDword();
//        local ani = obj.getCustomAnimation(27);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/dot/curseofdot/attackboxstart.ani"); 
        obj.setCurrentAnimation(ani);
        local attackInfo = sq_GetCustomAttackInfo(obj, 8);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
        obj.setTimeEvent(0,atkTime,0,false);
    }else if (id == 13)
    {
        local atkTime = receiveData.readDword();
        local savTime = receiveData.readDword();
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/dot/curseofdot/attackboxloop.ani"); 
        obj.setCurrentAnimation(ani);
        local attackInfo = sq_GetCustomAttackInfo(obj, 8);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
        obj.setTimeEvent(0,atkTime,0,false);
        obj.setTimeEvent(1,savTime,0,false);
    }else if (id == 14)
    {
        local atkTime = receiveData.readDword();
//        local ani = obj.getCustomAnimation(29);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/dot/curseofdot/attackboxend.ani"); 
        obj.setCurrentAnimation(ani);
        local attackInfo = sq_GetCustomAttackInfo(obj, 8);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
        obj.setTimeEvent(0,atkTime,0,false);
    }else if (id == 15)
    {


        local targetid = receiveData.readDword();
        local object = sq_GetObjectByObjectId(obj, targetid);
        local maxT = receiveData.readDword();

//        local ani = obj.getCustomAnimation(30);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/destinypuppet/run_zombie.ani"); 
        obj.setCurrentAnimation(ani);
        local attackInfo = sq_GetCustomAttackInfo(obj, 9);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, attackBonusRate);

        obj.getVar("pos").clear_vector();
        obj.getVar("pos").push_vector(obj.getXPos() );
        obj.getVar("pos").push_vector(obj.getYPos() );

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
        obj.getVar("values").clear_vector();
        obj.getVar("values").push_vector(maxT);
        obj.getVar("dama").clear_obj_vector();
        obj.getVar("dama").push_obj_vector(object);
        

        obj.getVar("pos").clear_vector();
        obj.getVar("pos").push_vector(obj.getXPos() );
        obj.getVar("pos").push_vector(obj.getYPos() );

    }
	else if (id == 16)
	{
		local ani = obj.getVar().GetAnimationMap("1","passiveobject/zrr_skill/newmage/animation/dot/maddotshoot/boby/atkb.ani"); 
		obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 10);
		sq_SetCurrentAttackInfo(obj, attackInfo);
		attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);
	}
    else if (id == 17)
    {
//        local ani = obj.getCustomAnimation(13);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/bloodmarble/enegry.ani"); 
        obj.setCurrentAnimation(ani);
        local posX = receiveData.readDword();
        local posY = receiveData.readDword();
        obj.getVar("pos").clear_vector();
        obj.getVar("pos").push_vector(posX);
        obj.getVar("pos").push_vector(posY);
        obj.getVar("pos").push_vector(0);
    }else if (id == 18)
    {   
        local id2 = receiveData.readDword();
//        local ani = obj.getCustomAnimation(33 + id2);
        local ani = null;
        if (id2 == 0)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/stateoflimit/meteorsword/bigswordboom1_sword_inner.ani"); 
        }else if (id2 == 1)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/stateoflimit/meteorsword/bigswordboom3_sword_inner.ani"); 
        }else if (id2 == 2)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/stateoflimit/meteorsword/bigswordboom4_sword_inner.ani"); 
        }else if (id2 == 3)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/stateoflimit/meteorsword/bigswordboom2_sword_inner.ani"); 
        }else if (id2 == 4)
        {

        }else if (id2 == 5)
        {
            ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/stateoflimit/meteorsword/bigswordboom5_sword_inner.ani"); 
        }

        obj.setCurrentAnimation(ani);
        local attackInfo = sq_GetCustomAttackInfo(obj, 11);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

        obj.getVar("id2").clear_vector();
        obj.getVar("id2").push_vector(id2);
        obj.getVar("id2").push_vector(obj.getZPos() );
        obj.getVar("id2").push_vector(100 );
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);

    }else if (id == 19)
    {
//        local ani = obj.getCustomAnimation(45);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/keepout/keepouta01_00.ani"); 
        obj.setCurrentAnimation(ani);
        local attackInfo = sq_GetCustomAttackInfo(obj, 12);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
    }else if (id == 20)
    {

        local swarC = receiveData.readDword();
        local summT = receiveData.readDword();
        local dashD = receiveData.readDword();
        local dashT = receiveData.readDword();

        obj.setTimeEvent(0,summT,0,false);		

//        local ani = obj.getCustomAnimation(48);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/atmage/animation/atswarm/loopgate_01.ani"); 

        obj.setCurrentAnimation(ani);

        obj.getVar("value").clear_vector();
        obj.getVar("value").push_vector(attackBonusRate);
        obj.getVar("value").push_vector(swarC);
        obj.getVar("value").push_vector(summT);
        obj.getVar("value").push_vector(dashD);
        obj.getVar("value").push_vector(dashT);

    }else if (id == 21)
    {
        local saveT = receiveData.readDword();
        local hitT = receiveData.readDword();
        local maxD = receiveData.readDword();

//        local ani = obj.getCustomAnimation(49);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/gunblader/animation/bladefalcon/projectile/bladefalcon01_20.ani"); 
        obj.setCurrentAnimation(ani);

//////////////////////////////////////////////
		local mage = obj.getTopCharacter();
		mage = sq_ObjectToSQRCharacter(mage);
		local sizeRate = mage.sq_GetIntData(SKILL_BLADE_STROM,10);
		local imageRate = sizeRate.tofloat() / 100.0;
		ani.setImageRateFromOriginal(imageRate, imageRate);
		ani.setAutoLayerWorkAnimationAddSizeRate(imageRate);
		sq_SetAttackBoundingBoxSizeRate(ani, imageRate, imageRate, imageRate);
//////////////////////////////////////////////

        local attackInfo = sq_GetCustomAttackInfo(obj,13);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

        obj.setTimeEvent(0,hitT,0,false);

        obj.getVar().clear_vector();
        obj.getVar().push_vector(obj.getXPos() );
        obj.getVar().push_vector(saveT);
        obj.getVar().push_vector(maxD);

    }else if (id == 22)
    {
        local saveT = receiveData.readDword();
        local hitT = receiveData.readDword();
        local maxD = receiveData.readDword();

//        local ani = obj.getCustomAnimation(50);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/gunblader/animation/bladefalcon/projectile/bladefalcon02_00.ani"); 
        obj.setCurrentAnimation(ani);

//////////////////////////////////////////////
		local mage = obj.getTopCharacter();
		mage = sq_ObjectToSQRCharacter(mage);
		local sizeRate = mage.sq_GetIntData(SKILL_BLADE_STROM,11);
		local imageRate = sizeRate.tofloat() / 100.0;
		ani.setImageRateFromOriginal(imageRate, imageRate);
		ani.setAutoLayerWorkAnimationAddSizeRate(imageRate);
		sq_SetAttackBoundingBoxSizeRate(ani, imageRate, imageRate, imageRate);
//////////////////////////////////////////////

        local attackInfo = sq_GetCustomAttackInfo(obj,14);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

        obj.setTimeEvent(0,hitT,0,false);

        obj.getVar().clear_vector();
        obj.getVar().push_vector(obj.getXPos() );
        obj.getVar().push_vector(saveT);
        obj.getVar().push_vector(maxD);

    }else if (id == 23)
    {
        local saveT = receiveData.readDword();
        local hitT = receiveData.readDword();

//        local ani = obj.getCustomAnimation(51);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/gunblader/animation/bladefalcon/projectile/bladefalcon03start_22.ani"); 
        obj.setCurrentAnimation(ani);

//////////////////////////////////////////////
		local mage = obj.getTopCharacter();
		mage = sq_ObjectToSQRCharacter(mage);
		local sizeRate = mage.sq_GetIntData(SKILL_BLADE_STROM,12);
		local imageRate = sizeRate.tofloat() / 100.0;
		ani.setImageRateFromOriginal(imageRate, imageRate);
		ani.setAutoLayerWorkAnimationAddSizeRate(imageRate);
		sq_SetAttackBoundingBoxSizeRate(ani, imageRate, imageRate, imageRate);
//////////////////////////////////////////////

        local attackInfo = sq_GetCustomAttackInfo(obj,15);

		local currentAttackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackeHitStunTime(currentAttackInfo, 0);

        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

        obj.setTimeEvent(0,hitT,0,false);

        obj.getVar().clear_vector();
        obj.getVar().push_vector(saveT);

    }

    obj.getVar("id").clear_vector();
    obj.getVar("id").push_vector(id);

}


function procAppend_po_hotlove(obj)
{
    local id = obj.getVar("id").get_vector(0);

    if (id == 23)
    {
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        if (mage && mage.sq_GetState() == STATE_BLADE_STROM && mage.getVar("state").get_vector(0) == 3)
        {
            createBladeStrom_BladeDisappearEffect(obj);
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 22)
    {
        local pAni = obj.getCurrentAnimation();
        local currentT = sq_GetCurrentTime(pAni);

        local startX = obj.getVar().get_vector(0);
        local maxT = obj.getVar().get_vector(1);
        local maxD = obj.getVar().get_vector(2);
    
        if (currentT < maxT)
        {
            local vx = sq_GetAccel(0, maxD, currentT, maxT , true);

            local dst = sq_GetDistancePos(startX,obj.getDirection() ,vx);
            obj.setCurrentPos(dst,obj.getYPos(),obj.getZPos());

        }else{

            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	
            if (!mage)
                return ;

            local attackBonusRate = mage.sq_GetBonusRateWithPassive(SKILL_BLADE_STROM, STATE_BLADE_STROM, 4, 1.0);


            mage.sq_StartWrite();
            mage.sq_WriteDword(attackBonusRate );	// attackBonusRate
            mage.sq_WriteDword(23);
            mage.sq_WriteDword( mage.sq_GetIntData(SKILL_BLADE_STROM, 4) );
            mage.sq_WriteDword( mage.sq_GetIntData(SKILL_BLADE_STROM, 3) );
            sq_SendCreatePassiveObjectPacketPos(mage,24364, 0, obj.getXPos(), obj.getYPos() + 1, 78 );

            sq_SendDestroyPacketPassiveObject(obj);

        }

    }else if (id == 21)
    {
        local pAni = obj.getCurrentAnimation();
        local currentT = sq_GetCurrentTime(pAni);

        local startX = obj.getVar().get_vector(0);
        local maxT = obj.getVar().get_vector(1);
        local maxD = obj.getVar().get_vector(2);
    
        if (currentT < maxT)
        {
            local vx = sq_GetAccel(0, maxD, currentT, maxT , true);

            local dst = sq_GetDistancePos(startX,obj.getDirection() ,vx);
            obj.setCurrentPos(dst,obj.getYPos(),obj.getZPos());

        }else{
            sq_SendDestroyPacketPassiveObject(obj);
        }

    }else if (id == 15)
    {


        local state = obj.getVar("state").get_vector(0);
        if (state == 0)
        {
            local pAni = obj.getCurrentAnimation();
            local currentT = sq_GetCurrentTime(pAni);
            if (currentT < obj.getVar("values").get_vector(0))
            {
                local startX = obj.getVar("pos").get_vector(0);
                local startY = obj.getVar("pos").get_vector(1);
                local tar = obj.getVar("dama").get_obj_vector(0);

                if (tar)
                {
                    local vx = sq_GetUniformVelocity(startX, tar.getXPos(), currentT, obj.getVar("values").get_vector(0));                        local vy = sq_GetUniformVelocity(startY, tar.getYPos(), currentT, obj.getVar("values").get_vector(0));
                    obj.setCurrentPos(vx,vy,0);

                    if (startX < tar.getXPos() )
                    {
                        obj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
                    }else{
                        obj.setCurrentDirection(ENUM_DIRECTION_LEFT);
                    }
                }
            }else{
                obj.getVar("state").set_vector(0,1);
//                local ani = obj.getCustomAnimation(31);
                local ani = obj.getVar().GetAnimationMap("3", 
                    "passiveobject/zrr_skill/newmage/animation/destinypuppet/success_zombie.ani"); 
                obj.setCurrentAnimation(ani);
                local tar = obj.getVar("dama").get_obj_vector(0);

                if (tar)
                {
                    obj.setCurrentPos(tar.getXPos(),tar.getYPos() + 1,0);
                    local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(tar, obj, SKILL_FATESLAVE, false, "character/new_mage/fateslave/ap_fateslave.nut", true);				 

                }


            }









        }else if (state == 1)
        {

            local pAni = obj.getCurrentAnimation();
            local currentT = sq_GetCurrentTime(pAni);
            if (currentT < 200)
            {
                local tar = obj.getVar("dama").get_obj_vector(0);

                if (tar)
                {
                    local vz = sq_GetUniformVelocity(0, tar.getObjectHeight() / 2, currentT, 200);    
                    obj.setCurrentPos(tar.getXPos(),tar.getYPos() + 1,vz);
                }
            }else{
                local tar = obj.getVar("dama").get_obj_vector(0);

                if (tar)
                {
                    obj.setCurrentPos(tar.getXPos(),tar.getYPos() + 1,tar.getObjectHeight() / 2);
                }
            }
        }

    }

    if (id == 18)
    {
        local pAni = obj.getCurrentAnimation();
        local currentT = sq_GetCurrentTime(pAni);
        
        if (currentT < obj.getVar("id2").get_vector(2) )
        {
                local startZ = obj.getVar("id2").get_vector(1);
                local vz = sq_GetAccel(0, startZ, currentT, obj.getVar("id2").get_vector(2) , true);
                obj.setCurrentPos(obj.getXPos(),obj.getYPos(),startZ - vz);
        }else{
                obj.setCurrentPos(obj.getXPos(),obj.getYPos(),0);
                if ( obj.getVar("state").get_vector(0) == 0)
                {
                    obj.getVar("state").clear_vector();
                    obj.getVar("state").push_vector(1);
//                    local ani = obj.getCustomAnimation(39 + obj.getVar("id2").get_vector(0) );
                    local id2 = obj.getVar("id2").get_vector(0);
                    local ani = null;
                    if (id2 == 0)
                    {
                        ani = obj.getVar().GetAnimationMap("2", 
                                "passiveobject/zrr_skill/newswordman/animation/stateoflimit/meteorsword/bigswordboom1_sword.ani"); 
                    }else if (id2 == 1)
                    {
                        ani = obj.getVar().GetAnimationMap("2", 
                                "passiveobject/zrr_skill/newswordman/animation/stateoflimit/meteorsword/bigswordboom3_sword.ani"); 
                    }else if (id2 == 2)
                    {
                        ani = obj.getVar().GetAnimationMap("2", 
                                "passiveobject/zrr_skill/newswordman/animation/stateoflimit/meteorsword/bigswordboom4_sword.ani"); 
                    }else if (id2 == 3)
                    {
                        ani = obj.getVar().GetAnimationMap("2", 
                                "passiveobject/zrr_skill/newswordman/animation/stateoflimit/meteorsword/bigswordboom2_sword.ani"); 
                    }else if (id2 == 4)
                    {

                    }else if (id2 == 5)
                    {
                        ani = obj.getVar().GetAnimationMap("2", 
                                "passiveobject/zrr_skill/newswordman/animation/stateoflimit/meteorsword/bigswordboom5_sword.ani"); 
                    }


                    createFrontSword80BigBoomAni(obj);
                    obj.setCurrentAnimation(ani);
                    sq_SetMyShake(obj, 3, 100);
                    sq_flashScreen(obj,100,0,100,53, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
                }
        }
    }else if (id == 8)
    {
        local state = obj.getVar("state").get_vector(0);
        if (state == 0)
        {
            local pAni = obj.getCurrentAnimation();
            local currentT = sq_GetCurrentTime(pAni);
            if (currentT <= obj.getVar("v").get_vector(3) )
            {
                local startX = obj.getVar("pos").get_vector(0);
                local distan = obj.getVar("pos").get_vector(1);
                local startZ = obj.getVar("pos").get_vector(2);

                local v0 = sq_GetAccel(0, distan, currentT, obj.getVar("v").get_vector(3) , true);
                local v1 = sq_GetAccel(0, startZ, currentT, obj.getVar("v").get_vector(3) , true);
                local dst = sq_GetDistancePos(startX,obj.getDirection() ,v0);

                obj.setCurrentPos(dst,obj.getYPos(),startZ - v1);

            }else{
                    //create

//                    sq_SendDestroyPacketPassiveObject(obj);

                obj.getVar("dama").clear_obj_vector();
                local objectManager = obj.getObjectManager();

                for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
                {
                    local object = objectManager.getCollisionObject(i);
                    if (object && object.isInDamagableState(obj) && object.isObjectType(OBJECTTYPE_ACTIVE))
                    {
                        if (abs(obj.getXPos() - object.getXPos())<= obj.getVar("v").get_vector(1) && abs(obj.getYPos() - object.getYPos())<= obj.getVar("v").get_vector(2) )
                        {
                            if ( obj.isEnemy(object) ) 
                            {

                                obj.getVar("dama").push_obj_vector( object );

                                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(object, obj, SKILL_HOTLOVE, false, "character/new_mage/hotlove/ap_hotlove_enemy.nut", true);				 
                                masterAppendage.sq_SetValidTime( obj.getVar("v").get_vector(0) );


//                                object.setCurrentPos(0,0,1000);
                            }else{


                                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(object, object, SKILL_HOTLOVE, false, "character/new_mage/hotlove/ap_hotlove_friend.nut", true);				 
                                masterAppendage.sq_SetValidTime( obj.getVar("v").get_vector(5) );

                                local change_appendage = masterAppendage.sq_getChangeStatus("break");
                                local atkSped = obj.getVar("v").get_vector(6) / 2;
                                local movSped = obj.getVar("v").get_vector(7) / 2;
                                local casSped = obj.getVar("v").get_vector(8) / 2;

                                if(!change_appendage)
                                {
                                    change_appendage = masterAppendage.sq_AddChangeStatusAppendageID(object, object, 0, 
                                    CHANGE_STATUS_TYPE_ATTACK_SPEED, 
                                    false, atkSped, APID_COMMON);

                                }
                                if(change_appendage)
                                {

                                    change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, false, atkSped.tofloat() );
                                    change_appendage.addParameter(CHANGE_STATUS_TYPE_CAST_SPEED, false, movSped.tofloat() );
                                    change_appendage.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED, false, casSped.tofloat() );
                                }
                            }



                        }

                    }
                }
                createHotLoveFloor(obj,100);
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(1);
                local ani = obj.getCustomAnimation(17);
                //local ani = obj.getVar().GetAnimationMap("2", "passiveobject/zrr_skill/newmage/animation/hotlove/hotlove_roof_doll.ani"); 
                obj.setCurrentAnimation(ani);
                obj.setTimeEvent(0,obj.getVar("v").get_vector(0),0,false);
                obj.setTimeEvent(2,obj.getVar("v").get_vector(4),0,false);


            }

        }
    }else if (id == 7)
    {
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        if (mage.getVar("state").get_vector(0) != 3)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 6)
    {
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        if (mage.getVar("state").get_vector(0) != 2 )
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 4)
    {
        local swordman = obj.getTopCharacter();
        swordman = sq_ObjectToSQRCharacter(swordman);	


        if (obj.getVar("state").get_vector(0) == 0)
        {


            if (!swordman || swordman.getVar("isDrop").get_vector(0) == 1 || obj.sq_GetParentState() == STATE_STAND )
            {
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(1);

                obj.getVar("z").clear_vector();
                obj.getVar("z").push_vector(obj.getXPos() );
                obj.getVar("z").push_vector(obj.getZPos() );

                obj.setTimeEvent(2,100,0,false);		

            }
        }else if ( obj.getVar("state").get_vector(0) == 1 )
        {
            local startX = obj.getVar("z").get_vector(0);
            local startZ = obj.getVar("z").get_vector(1);
            local pAni = obj.getCurrentAnimation();
            local currentT = sq_GetCurrentTime(pAni);
            local movT = obj.getVar("t").get_vector(1);


            if (obj.getZPos() > 0)
            {
//                local distX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),  obj.getVar("speed").get_vector(0) );
//                obj.setCurrentPos(distX,obj.getYPos(),obj.getZPos() - obj.getVar("speed").get_vector(0)  );
            }else{
                if (true)
                {
                    obj.setCurrentPos(obj.getXPos(),obj.getYPos(),0);
                    sq_SetMyShake(obj,5,400);
                    obj.getVar("state").clear_vector();
                    obj.getVar("state").push_vector(2);

                    local attackBonusRate = obj.getVar("att").get_vector(1);

//                    local ani = obj.getCustomAnimation(11);
                    local ani = obj.getVar().GetAnimationMap("2", 
                    "passiveobject/zrr_skill/newswordman/animation/bloodmarble/throwattack_floor_round.ani"); 

                    obj.setCurrentAnimation(ani);
                    local attackInfo = sq_GetCustomAttackInfo(obj, 3);
                    sq_SetCurrentAttackInfo(obj, attackInfo);
                    attackInfo = sq_GetCurrentAttackInfo(obj);
                    sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
                    obj.resetHitObjectList();
                    obj.getVar("flag").clear_vector();
                    obj.getVar("flag").push_vector(0);
                }



            }


        }
        local pAni = obj.getCurrentAnimation();
        local size = swordman.getVar("size").get_vector(0);
        local size2 = obj.getVar("size").get_vector(0);

        local sizeRate = size.tofloat()/100.0;
        local sizeRate2 = 100.0 / size2.tofloat();


        pAni.setImageRateFromOriginal(sizeRate, sizeRate);
        pAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
        sq_SetAttackBoundingBoxSizeRate(pAni, sizeRate2, sizeRate2, sizeRate2);
        sq_SetAttackBoundingBoxSizeRate(pAni, sizeRate, sizeRate, sizeRate);
        obj.getVar("size").set_vector(0,size);

    }
    else if (id == 2)
    {
        local pAni = obj.getCurrentAnimation();
        local currentT = sq_GetCurrentTime(pAni);
        if (obj.getVar("state").get_vector(0) == 1)
        {
            if (currentT < obj.getVar("pos").get_vector(6) )
            {

                local moveSX = obj.getVar("pos").get_vector(0);
                local moveSY = obj.getVar("pos").get_vector(1);
                local moveSZ = obj.getVar("pos").get_vector(2);
                local startX = obj.getVar("pos").get_vector(3);
                local startY = obj.getVar("pos").get_vector(4);
                local startZ = obj.getVar("pos").get_vector(5);
                local shootT = obj.getVar("pos").get_vector(6);

                local v1 = sq_GetAccel(0, moveSX, currentT, shootT, true);
                local v2 = sq_GetAccel(0, moveSY, currentT, shootT, true);
                local v3 = sq_GetAccel(0, moveSZ, currentT, shootT, true);


                sq_setCurrentAxisPos(obj, 0, startX + v1);
                sq_setCurrentAxisPos(obj, 1, startY + v2);
                sq_setCurrentAxisPos(obj, 2, startZ + v3);
            }else{

                if (obj.getVar("dama").get_obj_vector_size() <= 0)
                {
//                    local ani = obj.getCustomAnimation(5);
                    local ani = obj.getVar().GetAnimationMap("2", 
                    "passiveobject/zrr_skill/atmage/animation/aticecraft/icecraft_explosion.ani"); 
                    obj.setCurrentAnimation(ani);
                    obj.getVar("state").clear_vector();
                    obj.getVar("state").push_vector(2);
                    local attackInfo = sq_GetCurrentAttackInfo(obj);
                    sq_SetCurrentAttackBonusRate(attackInfo, obj.getVar("atk").get_vector(1) );
                }else{
                    sq_SendDestroyPacketPassiveObject(obj);
                }
            }

        }
    }
    else if (id == 1)
    {
        if (obj.getVar("tar").get_obj_vector_size() <= 0)
        {
            if (obj.getVar("flag").get_vector(0) == 1)
            {
                endThrowBat(obj);
            }

            local currentAni = sq_GetCurrentAnimation(obj);
            local currentT = sq_GetCurrentTime(currentAni);

            local maxD = obj.getVar("value").get_vector(1);
            local maxT = obj.getVar("value").get_vector(7);
            local startX = obj.getVar("value").get_vector(8);

            if (currentT < maxT )
            {


                local v = sq_GetAccel(0, maxD, currentT, maxT, true);
                local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
                obj.setCurrentPos(dstX,obj.getYPos(),obj.getZPos() );

            }else{

                endThrowBat(obj);

            }
        }else{

            local target = obj.getVar("tar").get_obj_vector(0);

            if (target) 
            {
                obj.setCurrentPos(target.getXPos(),target.getYPos()+1,target.getZPos() + target.getObjectHeight()/2);

            }
        }
    }


}


function onEndCurrentAni_po_hotlove(obj)
{
    local id = obj.getVar("id").get_vector(0);
    if (id == 0)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 2)
    {
        if (obj.getVar("state").get_vector(0) == 0)
        {

            obj.getVar("dama").clear_obj_vector();

            sq_SetMyShake(obj,1,50);

            local ani = obj.getVar().GetAnimationMap("444", 
                    "passiveobject/zrr_skill/atmage/animation/aticecraft/icecraft_spear.ani"); 
            obj.setCurrentAnimation(ani);
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);

            local currentAni = sq_GetCurrentAnimation(obj);
            local sizeRate = obj.getVar("pos").get_vector(7).tofloat() / 100.0;
            currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
            currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
            sq_SetAttackBoundingBoxSizeRate(currentAni, sizeRate, sizeRate, sizeRate);


            local moveSX = obj.getVar("pos").get_vector(0);
            local moveSY = obj.getVar("pos").get_vector(1);
            local moveSZ = obj.getVar("pos").get_vector(2);
            local startX = obj.getVar("pos").get_vector(3);
            local startY = obj.getVar("pos").get_vector(4);
            local startZ = obj.getVar("pos").get_vector(5);

            if (moveSX > 0)
            {
                obj.setCurrentDirection(1);
            }else{
                obj.setCurrentDirection(0);
 
            }
            local angle = getRorateAngleByCurrentPos(obj,startX,startY,startZ,
                                                    startX + moveSX,startY + moveSY,startZ + moveSZ);
            sq_SetCustomRotate(obj,angle);
            createIceCraftShootEffect(obj,angle);

//            sq_SetCustomRotate(obj, -0.45);	

        }else{
            sq_SendDestroyPacketPassiveObject(obj);
        }

    }else if (id == 3)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 4)
    {
        local state = obj.getVar("state").get_vector(0);
        if (state == 2)
        {

                obj.resetHitObjectList();
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(3);
                local size = obj.getVar("size").get_vector(0);
                local attackBonusRate = obj.getVar("att").get_vector(1);

//                local ani = obj.getCustomAnimation(12);
                local ani = obj.getVar().GetAnimationMap("2", 
                    "passiveobject/zrr_skill/newswordman/animation/bloodmarble/bloodmarbleexplosion_finish_front.ani"); 

                local sizeRate = size.tofloat()/100.0;
                ani.setImageRateFromOriginal(sizeRate, sizeRate);
                ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
                sq_SetAttackBoundingBoxSizeRate(ani, sizeRate, sizeRate, sizeRate);

                obj.setCurrentAnimation(ani);
                local attackInfo = sq_GetCustomAttackInfo(obj, 4);
                sq_SetCurrentAttackInfo(obj, attackInfo);
                attackInfo = sq_GetCurrentAttackInfo(obj);
                sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
                obj.setTimeEvent(1,2000,0,false);
        }else{
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 9)
    {
            sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 10)
    {
            sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 12)
    {
            sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 14)
    {
            sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 15)
    {

        local state = obj.getVar("state").get_vector(0);
        if (state == 1)
        {
            obj.getVar("state").set_vector(0,2);
//            local ani = obj.getCustomAnimation(46);
            local ani = obj.getVar().GetAnimationMap("2", 
                    "passiveobject/zrr_skill/newmage/animation/destinypuppet/explosion_11.ani"); 
            obj.setCurrentAnimation(ani);
            obj.setTimeEvent(0,2000,1,false);		
            sq_SetMyShake(obj,3,200);


        }else if (state == 2)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 16)
    {

            sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 18)
    {
            sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 19)
    {
            sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 20)
    {
        local ani = obj.getCustomAnimation(49);
        obj.setCurrentAnimation(ani);

    }else if (id == 23)
    {
//        local ani = obj.getCustomAnimation(52);
            local ani = obj.getVar().GetAnimationMap("2", 
                    "passiveobject/zrr_skill/gunblader/animation/bladefalcon/projectile/bladefalcon03loop_16.ani"); 
        obj.setCurrentAnimation(ani);

//////////////////////////////////////////////
		local mage = obj.getTopCharacter();
		mage = sq_ObjectToSQRCharacter(mage);
		local sizeRate = mage.sq_GetIntData(SKILL_BLADE_STROM,13);
		local imageRate = sizeRate.tofloat() / 100.0;
		ani.setImageRateFromOriginal(imageRate, imageRate);
		ani.setAutoLayerWorkAnimationAddSizeRate(imageRate);
		sq_SetAttackBoundingBoxSizeRate(ani, imageRate, imageRate, imageRate);
//////////////////////////////////////////////

        obj.setTimeEvent(1,obj.getVar().get_vector(0),0,false);		
    }
}



function endThrowBat(obj)
{
    if (obj.getVar("tar").get_obj_vector_size() <= 0)
    {
    }else{
        sq_SendCreatePassiveObjectPacketPos(obj,12313, 0, obj.getXPos(), obj.getYPos(), obj.getZPos());
    }
    sq_SendDestroyPacketPassiveObject(obj);
}

function onTimeEvent_po_hotlove(obj, timeEventIndex, timeEventCount)
{

    local id = obj.getVar("id").get_vector(0);
    if (id == 23)
    {

        if ( timeEventIndex == 0)
        {
            obj.resetHitObjectList();
        }else if ( timeEventIndex == 1)
        {
            createBladeStrom_BladeDisappearEffect(obj);
            sq_SendDestroyPacketPassiveObject(obj);
        }

    }else if (id == 22)
    {
        obj.resetHitObjectList();
    }else if (id == 21)
    {
        obj.resetHitObjectList();
    }else if (id == 20)
    {

            if (obj.getVar("value").get_vector(1) < timeEventCount)
            {
                createSwarmGateDisappear(obj,0,1,0);
                sq_SendDestroyPacketPassiveObject(obj);
            }else{

                sq_BinaryStartWrite();
                sq_BinaryWriteDword( obj.getVar("value").get_vector(0) );	// attackBonusRate
                sq_BinaryWriteDword(107);
                sq_BinaryWriteDword( obj.getVar("value").get_vector(3) );
                sq_BinaryWriteDword( obj.getVar("value").get_vector(4) );
                sq_SendCreatePassiveObjectPacketPos(obj,24357, 0,obj.getXPos() + sq_getRandom(-20,20).tointeger(), obj.getYPos() + sq_getRandom(-15,15).tointeger(), obj.getZPos() + sq_getRandom(40,150).tointeger() );


            }
    


    }else if (id == 15)
    {
            sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 14)
    {
        obj.resetHitObjectList();
    }else if (id == 13)
    {

        if (timeEventIndex == 0)
        {
            obj.resetHitObjectList();
        }else{
            sq_SendDestroyPacketPassiveObject(obj);
        }

    }else if (id == 12)
    {
        obj.resetHitObjectList();
    }else if (id == 11)
    {

        if (timeEventIndex == 0)
        {
            obj.resetHitObjectList();
        }else{
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 8)
    {
        local state = obj.getVar("state").get_vector(0);
        if (state == 1)
        {
            if (timeEventIndex == 0)
            {
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(2);
                //local ani = obj.getCustomAnimation(18);
                local ani = obj.getVar().GetAnimationMap("2", "passiveobject/zrr_skill/newmage/animation/hotlove/hotlove_end_doll.ani");
                obj.setCurrentAnimation(ani);
                obj.setTimeEvent(1,1500,0,false);
                //destroy self
            }else if (timeEventIndex == 2){
                local var = obj.getVar("dama");  		
                local objectsSize = var.get_obj_vector_size();
                if (objectsSize > 0)
                {
                    for(local i=0;i<objectsSize;++i)
                    {
                        local damager = var.get_obj_vector(i);
                        sq_SendHitObjectPacket(obj,damager,0,0,0);
                    }
                }

            }
        }else{
            local objectManager = obj.getObjectManager();

                for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
                {
                    local object = objectManager.getCollisionObject(i);
                    CNSquirrelAppendage.sq_RemoveAppendage(object, object, SKILL_HOTLOVE, false, "character/new_mage/hotlove/ap_hotlove_friend.nut", true);
                }
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 4)
    {
        if (timeEventIndex == 0)
        {
            local state = obj.getVar("state").get_vector(0);
            if (state == 0 || state == 1)
            {
                obj.resetHitObjectList();
            }
        }else if (timeEventIndex == 1){
            sq_SendDestroyPacketPassiveObject(obj);
        }else if (timeEventIndex == 2){
            local state = obj.getVar("state").get_vector(0);
            if ( state == 1)
            {
                local distX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),  obj.getVar("speed").get_vector(0) );
                obj.setCurrentPos(distX,obj.getYPos(),obj.getZPos() - obj.getVar("speed").get_vector(0)  );
            }
        }
    } else if (id == 1)
    {
        if (timeEventIndex == 1) 
        {
            endThrowBat(obj);
        }else if (timeEventIndex == 2)
        {
            local attackBonusRate = obj.getVar("value").get_vector(0);
            local attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

            local target = obj.getVar("tar").get_obj_vector(0);
            sq_SendHitObjectPacket(obj,target,0,0,target.getObjectHeight()/2 );
//            sq_SendCreatePassiveObjectPacketPos(obj,12214, 0, obj.getXPos(), obj.getYPos(), obj.getZPos());
            setCustomHitEffectBloodMageBlow(obj,target);
            createThrowBatHitEffect(obj,target);
            if (obj.getVar("value").get_vector(6) == 1)
            {

                if(obj.getVar().get_vector(0) == 0)
                {

                    obj.getVar().set_vector(0,1);


                    local mage = obj.getTopCharacter();
                    mage = sq_ObjectToSQRCharacter(mage);	

                    target = sq_GetCNRDObjectToActiveObject(target);
                    if (mage && target && !target.isDead() && !CNSquirrelAppendage.sq_IsAppendAppendage(target, 
                        "character/atmage/append_bloodmage/ap_throwbat.nut") )
                    {
                        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(target, mage, SKILL_THROWBAT, false, 
                        "character/atmage/append_bloodmage/ap_throwbat.nut", true);				 
                    }

                    if (mage && !CNSquirrelAppendage.sq_IsAppendAppendage(mage, 
                    "character/atmage/append_bloodmage/ap_throwbat_character.nut"))
                    {
                        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(mage, mage, SKILL_THROWBAT, false, 
                        "character/atmage/append_bloodmage/ap_throwbat_character.nut", true);				 
                    }




                }


//                local mage = obj.getTopCharacter();
//                mage = sq_ObjectToSQRCharacter(mage);	
//                setBloodValue(mage,obj.getVar("value").get_vector(5) );

            }



        }
    }else if (id == 0)
    {
        if (timeEventIndex == 0) 
        {
            if (obj.getDirection() == ENUM_DIRECTION_LEFT)
            {
                obj.setCurrentPos(obj.getXPos() - 3,obj.getYPos(),obj.getZPos());
            }else{
                obj.setCurrentPos(obj.getXPos() + 3,obj.getYPos(),obj.getZPos());
            }
            obj.resetHitObjectList();
//            obj.sq_PlaySound("BLOODBAT_LOOP");

        }
        
        if (timeEventIndex == 1)
        {
            setVliadEffectAtBloodDancePassiveobject(obj);
            createBloodDanceEndFloorEffect(obj,obj.getVar("size").get_vector(0) );
//            local ani = obj.getCustomAnimation(2);
            local ani = obj.getVar().GetAnimationMap("2", 
                    "passiveobject/zrr_skill/atmage/animation/atlilroi/lilroi_end_disappear_front.ani"); 
            obj.setCurrentAnimation(ani);

            local currentAni = sq_GetCurrentAnimation(obj);
            local size = obj.getVar("size").get_vector(0);
            local sizeRate = size.tofloat()/100.0;
            currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
            currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
            sq_SetMyShake(obj,5,360);
        }
    }
}

function onKeyFrameFlag_po_hotlove(obj, flagIndex)
{
    local id = obj.getVar("id").get_vector(0);

    if (id == 4)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {
            sq_SetMyShake(obj,10,360);
            sq_flashScreen(obj,0,200,600,178, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
                    obj.getVar("flag").clear_vector();
                    obj.getVar("flag").push_vector(1);
        }
    }

}

function onAttack_po_hotlove(obj,damager, boundingBox, isStuck)
{


    local id = obj.getVar("id").get_vector(0);
//    addMonsterDeadPassiveObject(obj,damager);
    if (id == 15)
    {
        local state = obj.getVar("state").get_vector(0);
        if (state == 2)
        {

            if(damager)
            {
                CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/new_mage/fateslave/ap_fateslave.nut");		
            }
        }
    }else if (id == 19)
    {
            sq_SetMyShake(obj,4,180);
                if(damager)
                {
                    CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/new_mage/keepout/ap_keepout.nut");		
                }

    }else if (id == 18)
    {
            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_SWORD80, false, 
            "character/newswordman/sword80/ap_sword80.nut", true);				 
    }else if (id == 16)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {
            createHitEffectMadDotShoot(obj,damager,0,-1,0);
            createHitEffectMadDotShoot2(obj,damager,0,1,0);
            sq_SetMyShake(obj,5,360);
            obj.getVar("flag").set_vector(0,1);

        }
    }
    else if (id == 2)
    {
        (obj.getVar("state").get_vector(0) == 1)
        {
            obj.getVar("dama").push_obj_vector(damager);
            iceCraftHitFront(obj,damager);
            iceCraftHitBehind(obj,damager);
            sq_EffectLayerAppendage(damager,sq_RGB(0,0,0),0,200,0,240);	

        }
    }
    else if (id == 1)
    {
        if (obj.getVar("tar").get_obj_vector_size() <= 0)
        {
            obj.getVar("tar").push_obj_vector(damager);

//            local ani = obj.getCustomAnimation(1);
            local ani = obj.getVar().GetAnimationMap("2", 
                    "passiveobject/zrr_skill/atmage/animation/atliliac/liliac_batspinawake_loop.ani"); 

            obj.setCurrentAnimation(ani);

            obj.setTimeEvent(1,obj.getVar("value").get_vector(3),0,false);
            obj.setTimeEvent(2,obj.getVar("value").get_vector(4),0,true);

            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);
        }
    }

    if (id == 0)
    {
        setCustomHitEffectBloodMageBlow(obj,damager);

        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        damager = sq_GetCNRDObjectToActiveObject(damager);
        if(mage)
        {
            if (!damager.isDead() && 
                !CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/append_bloodmage/ap_blooddance.nut"))
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, mage, SKILL_BLOODDOG, false, 
                "character/atmage/append_bloodmage/ap_blooddance.nut", true);				 

            }

            if (obj.getVar().get_vector(0) == 0 && !CNSquirrelAppendage.sq_IsAppendAppendage(mage, "character/atmage/append_bloodmage/ap_blooddance_character.nut"))
            {
                obj.getVar().set_vector(0,1);
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(mage, mage, SKILL_BLOODDANCE, false, 
                "character/atmage/append_bloodmage/ap_blooddance_character.nut", true);				 
            }

        }

    }
//    sq_SendCreatePassiveObjectPacketPos(obj,12333, 0, damager.getXPos(), damager.getYPos() + 7, damager.getZPos() + 50);

}
