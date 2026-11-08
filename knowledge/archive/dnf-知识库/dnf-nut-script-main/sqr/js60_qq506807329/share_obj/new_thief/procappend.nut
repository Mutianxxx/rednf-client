 
function procAppend_po_qq506807329new_thief_24378(obj)
{
 if(!obj) return;
 local oXvTDV106lKRYCEivfZ9Nk = obj.getVar("skill").get_vector(0); 
 local xgB4oGQfN5WUjS5bK23EXq = obj.getVar("subType").get_vector(0); 
 local VEqBKvZBZP38uG = obj.getVar("state").get_vector(0); 
 switch(oXvTDV106lKRYCEivfZ9Nk)
 {
 
  case 226: 
 switch (xgB4oGQfN5WUjS5bK23EXq)
 {
 case 1:
 local FwjQn24pOJryRh_g1i4R = obj.getParent(); 
 if (!FwjQn24pOJryRh_g1i4R)
 {
 if (obj.isMyControlObject())
 obj.addSetStatePacket(PASSIVEOBJ_SUB_STATE_5, null, STATE_PRIORITY_AUTO, false, "");
 }
 else if (obj.getState() == PASSIVEOBJ_SUB_STATE_5)
 {
 local oBTtFI0PP86Qd = obj.getVar("aniObj").get_obj_vector(0);
 if (oBTtFI0PP86Qd)
 {
 local DVgU1LdTeiCUDrj0zujx = obj.getCurrentAnimation(); 
 local dFsSs4Q_I6UuOulRW2 = sq_GetCurrentTime(DVgU1LdTeiCUDrj0zujx); 
 local XvAdp7CGpOUK9Z7x83CUD = DVgU1LdTeiCUDrj0zujx.getDelaySum(0,14); 

 local Pvqyj3BMgLrTR4cj1Tkii = oBTtFI0PP86Qd.getCurrentAnimation();
 local quvfWDpQUd_5Kt = sq_GetUniformVelocity(255, 0, dFsSs4Q_I6UuOulRW2, XvAdp7CGpOUK9Z7x83CUD);
 Pvqyj3BMgLrTR4cj1Tkii.setRGBA(255, 255, 255, quvfWDpQUd_5Kt);
 }
 }
 break;
 case 2:
 local FwjQn24pOJryRh_g1i4R = obj.getParent();
 if (!FwjQn24pOJryRh_g1i4R) 
 {
 if (obj.isMyControlObject())
 sq_SendDestroyPacketPassiveObject(obj);
 return;
 }
 else 
 {
 local bT5kCdMr3VYd2cqoweH2Aa3 = obj.getState();
 switch (bT5kCdMr3VYd2cqoweH2Aa3)
 {
 case PASSIVEOBJ_SUB_STATE_0:
 local dFsSs4Q_I6UuOulRW2 = sq_GetObjectTime(obj) - obj.getVar().getInt(0); 
 local XvAdp7CGpOUK9Z7x83CUD = obj.getVar().getInt(1); 

 local Pvqyj3BMgLrTR4cj1Tkii = obj.getCurrentAnimation();
 local quvfWDpQUd_5Kt = sq_GetUniformVelocity(255, 0, dFsSs4Q_I6UuOulRW2, XvAdp7CGpOUK9Z7x83CUD);
 Pvqyj3BMgLrTR4cj1Tkii.setRGBA(255, 255, 255, quvfWDpQUd_5Kt);
 local w2l0RSlyRyK2UD5e = sq_AniLayerListSize(Pvqyj3BMgLrTR4cj1Tkii);
 for (local v4cooNPjbcydVDAoS = 0; v4cooNPjbcydVDAoS < w2l0RSlyRyK2UD5e; v4cooNPjbcydVDAoS++)
 {
 local S5B0vPbRrPHcREKW4MV7P4O = sq_getAniLayerListObject(Pvqyj3BMgLrTR4cj1Tkii, v4cooNPjbcydVDAoS); 
 if (S5B0vPbRrPHcREKW4MV7P4O) S5B0vPbRrPHcREKW4MV7P4O.setRGBA(255, 255, 255, quvfWDpQUd_5Kt);
 }
 if (quvfWDpQUd_5Kt == 0 && obj.isMyControlObject())
 {
 sq_SendDestroyPacketPassiveObject(obj);
 }
 break;
 default:
 if (FwjQn24pOJryRh_g1i4R.getState() == PASSIVEOBJ_SUB_STATE_5 && obj.isMyControlObject()) 
 {
 obj.addSetStatePacket(PASSIVEOBJ_SUB_STATE_0, null, STATE_PRIORITY_AUTO, false, "");
 }
 break;
 }
 }
 break;
 }
 break;
 
 case 223: 
 switch(xgB4oGQfN5WUjS5bK23EXq)
 {
 case 1:
 if(obj.getVar().getBool(2) != true)return; 
 local Feb4Xb4tebjK16CHNr61l7 = obj.getParent(); 
 if(!Feb4Xb4tebjK16CHNr61l7)
 { 
 if(obj.isMyControlObject())
 sq_SendDestroyPacketPassiveObject(obj);
 return;
 }
 if(Feb4Xb4tebjK16CHNr61l7.getState() == 10) 
 {
 if(Feb4Xb4tebjK16CHNr61l7.isCurrentAnimationIndex(22) == false) 
 {
 local DK49ONdEHO0pK5HiAKgMhkY = sq_GetCNRDObjectToCollisionObject(Feb4Xb4tebjK16CHNr61l7); 
 if(DK49ONdEHO0pK5HiAKgMhkY)
 {
 sq_SetVelocity(DK49ONdEHO0pK5HiAKgMhkY, 0, 0.0); 
 sq_moveWithParent(obj, DK49ONdEHO0pK5HiAKgMhkY); 
 
 setCurrentAnimationFromCutomIndex(DK49ONdEHO0pK5HiAKgMhkY, 22); 
 sq_SetCurrentAttackInfoFromCustomIndex(DK49ONdEHO0pK5HiAKgMhkY, 15); 
 local LMX6VqFgEsHtHgdiJVW81F = DK49ONdEHO0pK5HiAKgMhkY.getCurrentAnimation(); 
 sq_Rewind(LMX6VqFgEsHtHgdiJVW81F); 
 LMX6VqFgEsHtHgdiJVW81F.setSpeedRate(obj.getVar().getFloat(1)); 
 local F8Vdw49ziw = sq_GetCurrentAttackInfo(DK49ONdEHO0pK5HiAKgMhkY); 
 sq_SetCurrentAttackBonusRate(F8Vdw49ziw, obj.getVar().getInt(0)); 
 }
 }
 else
 {
 local LMX6VqFgEsHtHgdiJVW81F = Feb4Xb4tebjK16CHNr61l7.getCurrentAnimation(); 
 if(sq_IsEnd(LMX6VqFgEsHtHgdiJVW81F)) 
 {
 sq_moveWithParent(obj, obj); 
 if(obj.isMyControlObject())
 {
 sq_GetCNRDObjectToCollisionObject(Feb4Xb4tebjK16CHNr61l7).sendStateOnlyPacket(3); 
 sq_SendDestroyPacketPassiveObject(obj); 
 }
 return;
 }
 if(obj.isMyControlObject())
 {
 local Q68xJbH2X9N_GEp = sq_GetAnimationFrameIndex(LMX6VqFgEsHtHgdiJVW81F); 
 if(Q68xJbH2X9N_GEp >= 4 && obj.getVar().getBool(3) == false)
 {
 obj.getVar().setBool(3, true);
 sq_SetMyShake(obj, 3, 120);
 local Xb2Q4ErmyVrj6nzn = sq_flashScreen(obj, 100, 99990, 0, 255, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
 obj.getVar("flashobj").clear_obj_vector(); 
 obj.getVar("flashobj").push_obj_vector(Xb2Q4ErmyVrj6nzn); 
 }
 else if(Q68xJbH2X9N_GEp >= 16 && obj.getVar().getBool(4) == false)
 {
 obj.getVar().setBool(4, true);
 RemoveAllFlash(obj); 
 sq_SetMyShake(obj, 5, 240);
 sq_flashScreen(obj, 0, 60, 300, 204, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER); 
 }
 }
 }
 }
 else if(obj.isMyControlObject())
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 }
 break;
 case 224: 
 switch(xgB4oGQfN5WUjS5bK23EXq)
 {
 case 1:
 local qUN0MlYhiJXpULoot = sq_GetObjectTime(obj);
 local FnZoZZmyCpgBsIhbGBs = obj.getVar("atkobj").get_obj_vector_size(); 
 if(FnZoZZmyCpgBsIhbGBs > 0)
 {
 if(obj.getVar().getBool(2) == false)
 {
 obj.getVar().setBool(2, true); 
 }
 for(local C5gwGDpum3C8KCP0 = 0; C5gwGDpum3C8KCP0 < FnZoZZmyCpgBsIhbGBs; C5gwGDpum3C8KCP0++)
 {
 local SF5kAbs0sxrX94dBFA = sq_GetCNRDObjectToActiveObject(obj.getVar("atkobj").get_obj_vector(C5gwGDpum3C8KCP0)); 
 if(SF5kAbs0sxrX94dBFA)
 {
 local pOc7QpUKhu5kNhV59i0 = CNSquirrelAppendage.sq_GetAppendage(SF5kAbs0sxrX94dBFA, "character/new_thief/nicolasblackarachnia/ap_nicolasblackarachnia.nut");
 if(pOc7QpUKhu5kNhV59i0)
 {
 local E2qzi6fh_me3 = pOc7QpUKhu5kNhV59i0.getVar().get_timer_vector(0);
 if(!E2qzi6fh_me3)
 {
 pOc7QpUKhu5kNhV59i0.getVar().clear_timer_vector();
 pOc7QpUKhu5kNhV59i0.getVar().push_timer_vector();
 E2qzi6fh_me3 = pOc7QpUKhu5kNhV59i0.getVar().get_timer_vector(0);
 E2qzi6fh_me3.setParameter(obj.getVar().getInt(1), -1); 
 E2qzi6fh_me3.resetInstant(0); 
 }
 if(E2qzi6fh_me3.isOnEvent(qUN0MlYhiJXpULoot) == true && SF5kAbs0sxrX94dBFA.isDead() == false)
 {
 sq_SendHitObjectPacket(obj, SF5kAbs0sxrX94dBFA, 0, 0, sq_GetObjectHeight(SF5kAbs0sxrX94dBFA) / 2); 
 }
 }
 else 
 {
 obj.getVar("atkobj").remove_obj_vector(SF5kAbs0sxrX94dBFA);
 return;
 }
 }
 }
 }
 else 
 {
 if(obj.getVar().getBool(2) == false) 
 {
 local SF5kAbs0sxrX94dBFA = sq_GetCNRDObjectToActiveObject(obj.getParent()); 
 if(SF5kAbs0sxrX94dBFA.getState() != 8||SF5kAbs0sxrX94dBFA.getAttackIndex() != 8) 
 {
 if(obj.isMyControlObject())
 sq_SendDestroyPacketPassiveObject(obj);
 }
 } 
 else
 {
 if(obj.isMyControlObject())
 sq_SendDestroyPacketPassiveObject(obj);
 }
 }
 break;
 }
 break;
 case 225: 
 switch(xgB4oGQfN5WUjS5bK23EXq)
 {
 case 2:
 local LMX6VqFgEsHtHgdiJVW81F = obj.getCurrentAnimation();
 local Q68xJbH2X9N_GEp = sq_GetAnimationFrameIndex(LMX6VqFgEsHtHgdiJVW81F); 
 if(Q68xJbH2X9N_GEp >= 15 && Q68xJbH2X9N_GEp < 30) 
 {
 setRangeObjectPosEx(obj, 600, sq_GetDistancePos(0, obj.getDirection(), 220), 0, ENUM_DIRECTION_NEUTRAL, 0, 400, 300, 5); 
 }
 else if(Q68xJbH2X9N_GEp > 30 && Q68xJbH2X9N_GEp < 58)
 {
 local E2qzi6fh_me3 = obj.getVar().get_timer_vector(0);
 if(E2qzi6fh_me3.isOnEvent(sq_GetCurrentTime(LMX6VqFgEsHtHgdiJVW81F)) == true)
 {
 obj.resetHitObjectList(); 
 }
 }
 if(Q68xJbH2X9N_GEp < 26)
 {
 local RBOdqK1eGJ6ItD = obj.getVar("aniobj").get_obj_vector(0); 
 if(!RBOdqK1eGJ6ItD.isCurrentAnimationIndex(0)) 
 {
 local Vw6SXCvu17JWR34 = RBOdqK1eGJ6ItD.getCurrentAnimation();
 if(sq_IsEnd(Vw6SXCvu17JWR34)) 
 setCurrentAnimationFromCutomIndex(RBOdqK1eGJ6ItD, 0); 
 else if(obj.getVar("aniobj").get_obj_vector_size()<2 && sq_GetAnimationFrameIndex(Vw6SXCvu17JWR34)>=11) 
 {
 local QbAONZUOEAUi1_AMkxB0XQ = sq_AddDrawOnlyAniFromParent(RBOdqK1eGJ6ItD, "passiveobject/script_sqr_nut_qq506807329/thief/animation/ballacreadvent/ballacrebeadfocus/beadfocusa_05.ani", 0, 0, 0); 
 obj.getVar("aniobj").push_obj_vector(QbAONZUOEAUi1_AMkxB0XQ); 
 }
 }
 else
 {
 local Vw6SXCvu17JWR34 = RBOdqK1eGJ6ItD.getCurrentAnimation();
 if(sq_IsEnd(Vw6SXCvu17JWR34)) 
 sq_Rewind(Vw6SXCvu17JWR34); 
 }
 }
 if(obj.isMyControlObject() && Q68xJbH2X9N_GEp < 56)
 {
 local RBOdqK1eGJ6ItD = obj.getVar("aniobj2").get_obj_vector(0); 
 if(RBOdqK1eGJ6ItD && !RBOdqK1eGJ6ItD.isCurrentAnimationIndex(0))
 {
 if(sq_IsEnd(RBOdqK1eGJ6ItD.getCurrentAnimation())) 
 setCurrentAnimationFromCutomIndex(RBOdqK1eGJ6ItD, 0); 
 }
 }
 break;
 }
 break;
 default:
 
 if(obj.getVar("isProc").getBool(0) == true)return;
 obj.getVar("isProc").setBool(0, true); 
 local Feb4Xb4tebjK16CHNr61l7 = obj.getParent(); 
 if(!Feb4Xb4tebjK16CHNr61l7.isObjectType(OBJECTTYPE_MONSTER))return; 
 local vTLc6u1U_Oy7j6K31DJOIw = obj.getTopCharacter(); 
 if(!vTLc6u1U_Oy7j6K31DJOIw || sq_getJob(vTLc6u1U_Oy7j6K31DJOIw) != ENUM_CHARACTERJOB_THIEF) 
 {
 if(Feb4Xb4tebjK16CHNr61l7.isMyControlObject())
 Feb4Xb4tebjK16CHNr61l7.sendDestroyPacket(true); 
 if(obj.isMyControlObject())
 sq_SendDestroyPacketPassiveObject(obj); 
 return;
 }
 local JdF2rnzkkyJLmQLu4cL = obj.getZPos(); 
 switch(JdF2rnzkkyJLmQLu4cL)
 {
 case 10000 + 1111: 
 if(Feb4Xb4tebjK16CHNr61l7.getCollisionObjectIndex() == 61531) 
 if(vTLc6u1U_Oy7j6K31DJOIw.isMyControlObject())
 {
 sq_BinaryStartWrite();
 sq_BinaryWriteWord(1); 
 sq_BinaryWriteDword(sq_GetGroup(Feb4Xb4tebjK16CHNr61l7)); 
 sq_BinaryWriteDword(sq_GetUniqueId(Feb4Xb4tebjK16CHNr61l7)); 
 sq_SendChangeSkillEffectPacket(vTLc6u1U_Oy7j6K31DJOIw, 224); 
 }
 break;
 }
 if(obj.isMyControlObject())
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 }
} 
 
