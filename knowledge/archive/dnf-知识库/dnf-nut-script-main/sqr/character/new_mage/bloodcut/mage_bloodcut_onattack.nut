




function onAttackEtc_po_mage_bloodcut(obj,damager, boundingBox, isStuck)
{

    local id = obj.getVar("id").get_vector(0 );

    if (id == 224)
    {
        createHitManBulletHitEffect(obj,damager);

        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 79 , false, 
       "character/gunblader/cuveringfire/ap_cuveringfire.nut", true);				
        masterAppendage.getVar("chrY").clear_vector();
        masterAppendage.getVar("chrY").push_vector( obj.getVar("chrY").get_vector(0) );

    }else if (id == 223)
    {
        createHitManBulletHitEffect(obj,damager);
    }else if (id == 218)
    {
        if (obj.getVar("var").get_vector(8) == 1)
        {
            if (damager.isObjectType(OBJECTTYPE_ACTIVE))
                sq_SendDestroyPacketPassiveObject(obj);	
        }
    }else if (id == 209)
    {

        if (obj.getVar("var").get_vector(0) == 1)
        {
            if ( damager.isObjectType(OBJECTTYPE_ACTIVE) )
            {

                local target = sq_GetObjectByObjectId(obj, obj.getVar("var").get_vector(1) );

                if (!isSameObject( damager , target ) )
                {

                    local maxCount = obj.getVar("currentNum").get_vector(0);
                    local currentCount = obj.getVar("currentNum").get_vector(1);

                    if (currentCount <= maxCount )
                    {

                        local chr = obj.getParent();

                        obj.getVar("currentNum").set_vector(1, currentCount + 1 );
                        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, chr , SKILL_POISON_EXPLOSION , 
                        false, 
                        "character/fighter/poisonexplosion/ap_poisonexplosion_second.nut", true);				



                        local subAttackSpeed = sq_GetLevelData(chr, SKILL_POISON_EXPLOSION, 7, sq_GetSkillLevel(chr, SKILL_POISON_EXPLOSION) );
                        local subMoveSpeed = sq_GetLevelData(chr, SKILL_POISON_EXPLOSION, 6,  sq_GetSkillLevel(chr, SKILL_POISON_EXPLOSION) );

               			local change_appendage = masterAppendage.sq_getChangeStatus("PoisonExplosion");
               			if(!change_appendage)
               			{
               				change_appendage = masterAppendage.sq_AddChangeStatusAppendageID(damager, damager, 0, 
               				CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, 
               				false, 1, APID_COMMON);
               			}
               			if (change_appendage){
               				change_appendage.clearParameter();
               				change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED , false, -subAttackSpeed.tofloat() );
               				change_appendage.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED   , false, -subMoveSpeed.tofloat() );

               			}

                    }else{



                    }
                }
            }
        }

    }else if (id == 204)
    {
        
        local id = sq_GetObjectId(damager);

        sq_BinaryStartWrite();
        sq_BinaryWriteDword( obj.getVar("var").get_vector(0) );	// attackBonusRate
        sq_BinaryWriteDword(205);	// attackBonusRate
        sq_BinaryWriteDword(id);	// attackBonusRate
        sq_BinaryWriteDword( obj.getVar("var").get_vector(1) );	// attackBonusRate
        sq_BinaryWriteDword( obj.getVar("var").get_vector(2) );	// attackBonusRate
        sq_BinaryWriteDword( obj.getVar("var").get_vector(3) );
        sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, 0, 0, 0 );


    }else if (id == 195)
    {
        if (checkIsHoldAndDelayEffectWithWarn(damager) && sq_IsGrabable(obj,damager) )
        {
            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	
            sq_SendHitObjectPacketWithNoStuck(mage,damager,0,0,0);
        }

    }else if (id == 188)
    {
        if(damager.getState() != STATE_HOLD )
        {

            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 79 , false, 
            "character/newswordman/bloodrave/ap_bloodrave.nut", true);				
        }


    }else if (id == 184)
    {
        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_ZWEIVOL_TAGGEX , false, 
        "character/atswordman/weivoltaggex/ap_weivoltaggex.nut", true);				


    }else if (id == 183)
    {
        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 60 , false, 
        "character/newswordman/ghoststepslash/ap_ghoststepslash.nut", true);				
        obj.getVar("dama").push_obj_vector(damager);


    }else if (id == 170)
    {
        createCoalBanHitEffect(obj,obj);
    }else if ( (id >= 148 && id <= 152) || id == 147)
    {
        setHitEffectSpriteSwordManCutBS2(obj,damager);
    }else if (id == 173)
    {
        CNSquirrelAppendage.sq_RemoveAppendage(damager, 
        "character/priest/invitofevil/ap_inviteofdevil.nut");
    }else if (id == 172 || id == 171)
    {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_INVITEOFEVIL, false, 
                "character/priest/invitofevil/ap_inviteofdevil.nut", true);				 
    }else if (id == 161)
    {
        
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	

        local mageState = mage.sq_GetState();
        if (mageState != STATE_AT_SWORDMAN_EXECUTION)
            return false;

		local ani = obj.getVar().GetAnimationMap("AtExectionHazeCreateEffect", 
        "passiveobject/zrr_skill/atswordman/animation/atexecution/haze_create_haze2.ani"); 
		obj.setCurrentAnimation(ani );
        createExecutionMdStartEffect(obj);
        damager.setCurrentPos( obj.getXPos(),obj.getYPos() - 1,0 );


        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_AT_SWORDMAN_EXECUTION, false, 
        "character/atswordman/execution/ap_execution.nut", true);				 

        if(damager.getState() != STATE_HOLD 
		&& sq_IsGrabable(obj,damager) 
		&& sq_IsHoldable(obj,damager) 
		&& !sq_IsFixture(damager))
        {
            sq_HoldAndDelayDie(damager, obj, true, false, false, 0, 0, ENUM_DIRECTION_NEUTRAL , masterAppendage);
        }
        obj.getVar("var").set_vector(1,-1);


        if (mage)
        {
            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 2);			
            mage.addSetStatePacket(STATE_AT_SWORDMAN_EXECUTION , pIntVec,  STATE_PRIORITY_USER, false, "");


        }

    }else if (id == 160)
    {
        createShootAniHitLightEffect(obj,damager);
    }else if (id == 133)
    {

        local flagIndex = obj.getVar("flagIndex").get_vector(0);
        if (flagIndex == 1)
        {
            createContinueFireBulletHitEffect1(obj,damager);
        }else if (flagIndex == 2)
        {
            createContinueFireBulletHitEffect2(obj,damager);
        }else if (flagIndex == 3)
        {
            createContinueFireBulletHitEffect3(obj,damager);
        }
    }else if (id == 132)
    {

       createSightingShootBulletHitEffect(obj,damager);
    }else if (id == 131)
    {
        if (obj.getVar("state").get_vector(0) == 0)
        {
            if( damager.isObjectType(OBJECTTYPE_ACTIVE) ) 
            {
                obj.getVar("dama").push_obj_vector(damager);
            }
        }
    }else if (id == 129)
    {
        createElementalCurtainInFinishHitEffect(obj,damager);
    }else if (id == 126)
    {
        if(damager.getState() != STATE_HOLD )
        {
            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_SUMMONZIG, false, 
            "character/newswordman/summonzig/ap_zig.nut", true);				 
            obj.getVar("dama").push_obj_vector(damager);
        }
    }else if (id == 75)
    {
		createWipeOutHitEffect(damager);
    }else if (id == 116)
    {
        if (damager)
        {
            setCustomHitEffectBloodMageCut(obj,damager,0);
            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	
            if (mage && !sq_IsFixture(damager) )
                mage.getVar("dama").push_obj_vector(damager);
        }
    }else if (id == 38)
    {
		if(!sq_IsFixture(damager)) 
        {
            obj.getVar("dama").push_obj_vector(damager);
        }
    }else if (id == 121)
    {
        setHitEffectWeaponMaster_InvisibleBladeSwordCut_LoopHitEffect(obj,damager);
    }else if (id == 70)
    {
        local attackBonusRate = obj.getVar().get_vector(0);
        if (!sq_IsHoldable(obj,damager) )
            attackBonusRate = obj.getVar().get_vector(1);

        local attackInfo = sq_GetCustomAttackInfo(obj, 95);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
    }else if (id == 19 || id == 20)
    {
        if(obj.isMyControlObject())
        {
            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	
            if (mage )
                secondWindHit_PassiveobjectAppendByCharacter(mage,damager);
        }
    }else if (id == 119 )
    {
            createKallaFireSmokeEffect(obj,damager, 0, 1, 0);
            sq_SendDestroyPacketPassiveObject(obj);	
    }else if (id == 81)
    {
        if (obj.getVar("state").get_vector(0) == 0)
        {
            obj.getVar("dama").push_obj_vector(damager);

        }
    }else if (id == 107)
    {
        if (obj.getVar("state").get_vector(0) == 0)
        {
            obj.getVar("state").set_vector(0,1);

            local ani = obj.getVar().GetAnimationMap("SwarmBoom", 
            "passiveobject/zrr_skill/atmage/animation/atswarm/swarmboom_01.ani"); 
            obj.setCurrentAnimation(ani);
            local attackInfo = sq_GetCustomAttackInfo(obj, 81);
            sq_SetCurrentAttackInfo(obj, attackInfo);

            attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackPower(attackInfo, obj.getVar("state").get_vector(1) );
            obj.resetHitObjectList();
            sq_SetMyShake(obj, 1, 30);

            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	
            if (mage)
            {

                local level = sq_GetSkillLevel(mage, SKILL_SWARM);		
                local useHp = sq_GetLevelData(mage, SKILL_SWARM, 8, level);
                mage.setHp( mage.getHp() + useHp, null, true);

            }
        }

    }else if (id == 101)
    {


        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	

		if(mage && !sq_IsFixture(damager)) 
        {



            local saveT = obj.getVar("sa").get_vector(0);
            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, mage, SKILL_TIMETAPE, false, "character/atmage/timetape/ap_timetape.nut", true);				 

            masterAppendage.sq_SetValidTime(saveT);
            createTimeTapHit_0(obj,damager);

        }

    }else if (id == 97)
    {
        if(damager)
        {
            CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/newthier/bloodshaowslash/ap_bloodshaowslash.nut");		
        }

    }else if (id == 51)
    {
        if(damager)
        {
            obj.getVar("dama").push_obj_vector(damager);

            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	

            if (mage && !CNSquirrelAppendage.sq_IsAppendAppendage(damager, 
                "character/atmage/append_bloodmage/ap_blood45.nut") )
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, mage, SKILL_BLOOD45, false, 
                "character/atmage/append_bloodmage/ap_blood45.nut", true);				 
            }
        }

    }else if (id == 68)
    {
		if( damager.isObjectType(OBJECTTYPE_ACTIVE) ) 
        {

            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	
            mage.getVar("dama").push_obj_vector(damager);

            if (sq_IsHoldable(obj,damager) )
            {
                mage.getVar("isGrab").set_vector(0,0);
            }

            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, mage, SKILL_CANCEL, false, "character/atmage/cancel/ap_cancel.nut", true);				 



        }
    }


    if (id == 65)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {
//            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_CIRRUSCUT, false, "character/mage/cirruscut/ap_cirruscut.nut", true);				 
//            sq_HoldAndDelayDie(damager, obj, true, true, true, 0, 0, ENUM_DIRECTION_NEUTRAL , masterAppendage);

            sq_SendCreatePassiveObjectPacketPos(obj,12257 +  sq_getRandom(0,3).tointeger(), 0, 
            damager.getXPos(), damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
        }else{
//            CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/mage/cirruscut/ap_cirruscut.nut");		
        }
    }
    if (id == 63)
    {
        if (damager.isObjectType(OBJECTTYPE_ACTIVE) && 
            !CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/shardmagnum/ap_shardmagnum.nut") )
        {
            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_ATMAGE_SHARDMAGNUM, false, "character/atmage/shardmagnum/ap_shardmagnum.nut", true);				 
            damager.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getZPos() );
        }

    }

    if (id == 59)
    {

        setCustomHitEffectBloodMageCut(obj,damager,0);

		if(damager.getState() != STATE_HOLD 
		     && sq_IsGrabable(obj,damager) 
		     && sq_IsHoldable(obj,damager) 
		     && !sq_IsFixture(damager)) 
        {

            //obj.getVar("value").get_vector(0); // len 
            //obj.getVar("value").get_vector(1); // xSpeed
            //obj.getVar("value").get_vector(2); // ySpeed


            obj.getVar("dama").push_obj_vector(damager);

//            addMonsterDeadPassiveObject(obj,damager);
        }
    }
    if (id == 54)
    {
        setCustomHitEffectBloodMageBlow(obj,damager);
    }

    if (id == 33)
    {
        if ( damager.isObjectType(OBJECTTYPE_ACTIVE) )
        {
            obj.getVar("dama").push_obj_vector(damager);
        }

    }


    if (id == 24)
    {
        if (obj.getVar("state").get_vector(0) == 0)
        {
            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	

            mage.getVar("state").clear_vector();
            mage.getVar("state").push_vector(2);
            mage.getVar("state").push_vector(damager.getXPos() );
            mage.getVar("state").push_vector(damager.getYPos() );
            mage.getVar("state").push_vector(damager.getObjectHeight());
            mage.sq_AddSetStatePacket(STATE_THROWATTACK , STATE_PRIORITY_USER, false);

            sq_SendDestroyPacketPassiveObject(obj);	
        }

    }

    if (id == 23)
    {
        CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/raginwind/ap_raginwind.nut");		
    }

    if (id == 22)
    {
        if (!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/raginwind/ap_raginwind.nut"))
        {


            if (!sq_IsFixture(damager))
            {


                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 136, false, "character/atmage/raginwind/ap_raginwind.nut", true);				 
                sq_HoldAndDelayDie(damager, obj, true, true, true, 0, 0, ENUM_DIRECTION_NEUTRAL , masterAppendage);


                if (obj.getDirection() == ENUM_DIRECTION_LEFT)
                {
                    damager.setCurrentPos(obj.getXPos() - 100,obj.getYPos(),obj.getZPos());
                }else{
                    damager.setCurrentPos(obj.getXPos() + 100,obj.getYPos(),obj.getZPos());
                }

            }
        }



    }

    if (id == 21)
    {


            if ( !sq_IsFixture(damager))
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 136, false, "character/atmage/raginwind/ap_raginwind.nut", true);				 
                sq_HoldAndDelayDie(damager, obj, true, true, true, 0, 0, ENUM_DIRECTION_NEUTRAL , masterAppendage);

                if (obj.getDirection() == ENUM_DIRECTION_LEFT)
                {
                    damager.setCurrentPos(obj.getXPos() - 100,obj.getYPos(),obj.getZPos());
                }else{
                    damager.setCurrentPos(obj.getXPos() + 100,obj.getYPos(),obj.getZPos());
                }
            }
    }

    if (id == 18)
    {
        local state = obj.getVar("state").get_vector(0);
        if (state == 0 || state == 1)
        {


            if ( !sq_IsFixture(damager) && sq_IsGrabable(obj,damager) && damager.getState() != STATE_HOLD)
            {
                obj.getVar("dama").push_obj_vector(damager);
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 134,
                false, "character/atmage/stormquake/ap_stormquake.nut", true);				 

                masterAppendage.getVar("stromObj").clear_obj_vector();
                masterAppendage.getVar("stromObj").push_obj_vector( obj );

            }



        }else{

                CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/stormquake/ap_stormquake.nut");		

        }
    }



    if (id == 15)
    {

        if (obj.getVar("flag").get_vector(0) == 0)
        {
            if(damager.getState() != STATE_HOLD)
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 123, false, 
                "character/newswordman/ghostout/ap_ghostout.nut", true);				 
            }
        }else{


            CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/newswordman/ghostout/ap_ghostout.nut");		

        }
    }


    if (id == 13)
    {
        if (!damager) return false;
        if ( damager.isObjectType(OBJECTTYPE_ACTIVE) && obj.isMyControlObject() )
        {

            if (!CNSquirrelAppendage.sq_IsAppendAppendage(damager, 
            "character/newswordman/hardattack_hell/ap_hardattack_hell_flag.nut"))
            {
                local id = sq_GetObjectId(damager);
                local lastAttack = obj.getVar("holdValue").get_vector(0);
                local liveTime = obj.getVar("holdValue").get_vector(1);

                sq_BinaryStartWrite();
                sq_BinaryWriteDword(lastAttack);	// attackBonusRate
                sq_BinaryWriteDword(14);	// attackBonusRate
                sq_BinaryWriteDword(id);	// attackBonusRate
                sq_BinaryWriteDword(liveTime);	// attackBonusRate

                sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, damager.getXPos(), damager.getYPos() + 1,
                damager.getZPos() + damager.getObjectHeight()/2 );
            }
        }
    }

    if (id == 11)
    {
        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_SWORD80, false, "character/newswordman/sword80/ap_sword80.nut", true);				 
        if(masterAppendage) 
        {
            sq_HoldAndDelayDie(damager, obj, true, true, true, 0, 0, ENUM_DIRECTION_NEUTRAL , masterAppendage);
            damager.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
        }

    }


    if (id == 0)
    {

        setCustomHitEffectBloodMageCut(obj,damager,0);
    }

    if (id == 4)
    {
        

        if (obj.getVar("4state").get_vector(0) == 0)
        {
            if (damager.getState() != STATE_HOLD 
		     && sq_IsGrabable(obj,damager) 
		     && sq_IsHoldable(obj,damager) 
		     && !sq_IsFixture(damager))
            {

                obj.getVar("dama").push_obj_vector(damager);
                //createPhantomBaleStart_HitEffect(obj,224,2,34);
                createPhantomBaleLoopHitEffect(obj,damager);


                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_NEWBLOODDOGHOLD, false, 
                "character/atmage/newblooddoghold/ap_newblooddoghold.nut", true);				 
                if(masterAppendage) 
                {
                    sq_HoldAndDelayDie(damager, obj, true, false, false, 0, 0, ENUM_DIRECTION_NEUTRAL , masterAppendage);
                    damager.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
                }

            }



        }else if (obj.getVar("4state").get_vector(0) == 1)
        {
            if (damager.getState() != STATE_HOLD )
            {

                damager = sq_GetCNRDObjectToActiveObject(damager);

                if (!damager.isDead() && 
                    !CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/newblooddoghold/ap_newblooddoghold.nut"))
                {

                    local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_NEWBLOODDOGHOLD, false, 
                    "character/atmage/newblooddoghold/ap_newblooddoghold.nut", true);				 

                }


            }



        }else{
                if (CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/newblooddoghold/ap_newblooddoghold.nut"))
                {
                    CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/newblooddoghold/ap_newblooddoghold.nut");		
                }
        }


        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        if (mage && damager.isObjectType(OBJECTTYPE_ACTIVE)  )
        {
            damager = sq_GetCNRDObjectToActiveObject(damager);
            if (!damager.isDead() && 
                !CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/append_bloodmage/ap_blooddoghold.nut"))
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, mage, SKILL_NEWBLOODDOGHOLD, false, 
                "character/atmage/append_bloodmage/ap_blooddoghold.nut", true);				 

            }

            if (!CNSquirrelAppendage.sq_IsAppendAppendage(mage, "character/atmage/append_bloodmage/ap_blooddoghold_character.nut"))
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(mage, mage, SKILL_NEWBLOODDOGHOLD, false, 
                "character/atmage/append_bloodmage/ap_blooddoghold_character.nut", true);				 
            }

        }

    }
}