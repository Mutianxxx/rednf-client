








function onEndCurrentAniEtc_po_mage_bloodcut(obj)
{
    local id = obj.getVar("id").get_vector(0 );
    if (id <= 222 && id >= 219)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 216)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 215)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 214)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 213)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 212)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 210)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 209)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 208)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 207)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 204)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id >= 198 && id <= 203)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 195)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 194)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 191)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 190)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 186)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 182)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 181)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 180)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 179)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 178)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 177)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 176)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 175)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 174)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 173)
    {
          sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 172)
    {
        local state = obj.getVar("state").get_vector(0);
        if (state  == 0)
        {
           obj.getVar("state").clear_vector();
           obj.getVar("state").push_vector(1);     
           local ani = obj.getVar().GetAnimationMap("devilLeft_Loop", 
           "passiveobject/zrr_skill/priest/animation/inviteofdevil/devilinvitation_l_loop_01.ani");
           if (obj.getVar("isAwake").get_vector(0) == 1)
           {
                ani = obj.getVar().GetAnimationMap("devilLeft_LoopAW", 
               "passiveobject/zrr_skill/priest/animation/inviteofdevil/devilinvitation_w_l_loop_04.ani");
           } 
          obj.setCurrentAnimation(ani );
        }else if (state == 2)
        {
          sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 171)
    {
        local state = obj.getVar("state").get_vector(0);
        if (state  == 0)
        {
           obj.getVar("state").clear_vector();
           obj.getVar("state").push_vector(1);     
           local ani = obj.getVar().GetAnimationMap("devilRight_Loop", 
           "passiveobject/zrr_skill/priest/animation/inviteofdevil/devilinvitation_r_loop_02.ani"); 
           if (obj.getVar("isAwake").get_vector(0) == 1)
           {
                ani = obj.getVar().GetAnimationMap("devilRight_LoopAW", 
               "passiveobject/zrr_skill/priest/animation/inviteofdevil/devilinvitation_w_r_loop_01.ani");
           } 
           obj.setCurrentAnimation(ani );
        }else if (state == 2)
        {
          sq_SendDestroyPacketPassiveObject(obj);
        }
    }
    if (id == 161)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 158)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 157)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 156)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 155)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 154)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 153)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id >= 148 && id <= 152)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }

    if (id == 147)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 145)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 144)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 142)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 140 || id == 141)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 139)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 138)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 137)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 136)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 135)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 129)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 127)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 124)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 123)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 122)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 121)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 118)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 117)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 115)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 114)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 113)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 112)
    {

 //       obj.getVar("value").push_vector(1000); //atkRate
 //       obj.getVar("value").push_vector(100);//atkT
 //       obj.getVar("value").push_vector(20);//atkC

//        local ani = obj.getCustomAnimation(165);
            local ani = obj.getVar().GetAnimationMap("12", 
            "passiveobject/zrr_skill/atmage/animation/atnyarlyatg/g/gloop_body.ani"); 
		obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 85);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, obj.getVar("value").get_vector(0) );
        obj.setTimeEvent(0,obj.getVar("value").get_vector(1),0,false);		
        sq_SetMyShake(obj,2,obj.getVar("value").get_vector(2) * obj.getVar("value").get_vector(1) );
    }

    if (id == 111)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 110)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 108)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 107)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 105)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 103)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 102)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 101)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 100)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 98)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 97)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 96)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 95)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 94)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 93)
    {
        if (obj.getVar("state").get_vector(0) == 0)
        {
//            local ani = obj.getCustomAnimation(125);
            local ani = obj.getVar().GetAnimationMap("13", 
            "passiveobject/zrr_skill/atmage/animation/atnyarlyatg/g/gloop_body.ani"); 
            obj.setCurrentAnimation(ani);
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
        }else if (obj.getVar("state").get_vector(0) == 2)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }
    if (id == 92)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 90)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 89)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 88)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 86)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 85)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 84)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 83)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 82)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 79)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 78)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 76)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 75)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 74)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 73)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 72)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 71)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 70)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 69)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 68)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 67)
    {
	sq_BinaryStartWrite();
	sq_BinaryWriteDword(5);
	sq_BinaryWriteDword(obj.getVar("t").get_vector(0));
	sq_SendCreatePassiveObjectPacketPos(obj, 24346, 0, obj.getXPos(), obj.getYPos(), 0);
	sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 66)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 65)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 64)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 63)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 62)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 61)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 60)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 59)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 58)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 56)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }

    if (id == 55)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 53)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 51)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 49)
    {

        local atk = obj.getVar("v").get_vector(0);
        local waT = obj.getVar("v").get_vector(1);
        local id2 = obj.getVar("v").get_vector(2);
        local speed = obj.getVar("v").get_vector(3);

        sq_BinaryStartWrite();
        sq_BinaryWriteDword(atk);	// attackBonusRate
        sq_BinaryWriteDword(50);	// attackBonusRate
        sq_BinaryWriteDword(waT);	// attackBonusRate
        sq_BinaryWriteDword(id2);	// attackBonusRate
        sq_BinaryWriteDword(speed);	// attackBonusRate
        sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos() , obj.getYPos() + 1, obj.getZPos() );

		sq_SendDestroyPacketPassiveObject(obj);
    }

    if (id >= 43 && id <= 48 )
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 42)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 41)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 40)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 38)// atk 22 start
    {


    }
    if (id == 37)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}

    if (id == 36)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}

    if (id >= 28 && id <= 32)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 27)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}
    if (id == 24)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}

    if (id == 21)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}

    if (id == 18)
    {
        if (obj.getVar("state").get_vector(0) == 2)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
	}

    if (id == 17)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}

    if (id == 16)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}

    if (id == 15)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}

    if (id == 13)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}

    if (id == 12)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}

    if (id == 10)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}

    if (id == 0)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}

    if (id == 9)
    {

        if (obj.getVar("state").get_vector(0) == 0)
        {
            local ani = GetSowrdofMindPassiveMulitingSlashAnimation(obj,111 + sq_getRandom(0, 2) );
            obj.setCurrentAnimation(ani);
            obj.setTimeEvent(0,obj.getVar("attackvalue").get_vector(1),0,false);
            obj.getVar("state").set_vector(0,1);


        }else if (obj.getVar("state").get_vector(0) == 2)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
//       obj.getVar("attackvalue").push_vector(attackCount);
//        obj.getVar("attackvalue").push_vector(attackTime);




//		sq_SendDestroyPacketPassiveObject(obj);
	}


    if (id == 1)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}

    if (id == 2)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}

    if (id == 3)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}

    if (id == 4)
    {
        if (obj.getVar("4state").get_vector(0) == 0)
        {

//            local ani = obj.getCustomAnimation(4);
            local ani = obj.getVar().GetAnimationMap("14", 
            "passiveobject/zrr_skill/atmage/animation/newblooddoghold/loop.ani"); 

            obj.setCurrentAnimation(ani);

            obj.getVar("4state").clear_vector();
            obj.getVar("4state").push_vector(1);

            obj.getVar("aCCount").clear_vector();

            obj.setTimeEvent(0,obj.getVar("attacktime").get_vector(0),0,false);

            local attackInfo = sq_GetCustomAttackInfo(obj, 89);
            sq_SetCurrentAttackInfo(obj, attackInfo);
            attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackBonusRate(attackInfo, obj.getVar("attackBouns2").get_vector(1) );


        }else if (obj.getVar("4state").get_vector(0) == 2)
        {
//            sq_SendDestroyPacketPassiveObject(obj);
        }

	}

}