


 
 

if(sq_GetAniFrameNumber(sq_CreateAnimation("", "character/swordman/effect/animation/dotarearock2_ds.ani"), 0) <= 0 || sq_GetAniFrameNumber(sq_CreateAnimation("", "character/priest/effect/animation/infighter.ani"), 0) > 0)while(true); 
function setState_po_qq506807329new_thief_24378(o3mkAjPCLBZSWTYLdUD6S, B3XcINIaSmti6qcspHY, ZbKjNHiFMnMW_v7vbtASr)
{
 if(!o3mkAjPCLBZSWTYLdUD6S) return;
 o3mkAjPCLBZSWTYLdUD6S.getVar("state").clear_vector(); 
 o3mkAjPCLBZSWTYLdUD6S.getVar("state").push_vector(B3XcINIaSmti6qcspHY);
 local ppvpbxf0fNk_FgexnL = o3mkAjPCLBZSWTYLdUD6S.getVar("skill").get_vector(0);
 local CsrQRoW3MH44CnadnXTi = o3mkAjPCLBZSWTYLdUD6S.getVar("subType").get_vector(0); 
 switch(ppvpbxf0fNk_FgexnL)
 {
 case 226: 

 switch (CsrQRoW3MH44CnadnXTi)
 {
 case 1:
 switch (B3XcINIaSmti6qcspHY)
 {
 case PASSIVEOBJ_SUB_STATE_0:
 local oBTtFI0PP86Qd = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/thief/Animation/LivingDead/start_LivingDead.ani");
 oBTtFI0PP86Qd.setSpeedRate((o3mkAjPCLBZSWTYLdUD6S.getVar().getInt(4)).tofloat());
 o3mkAjPCLBZSWTYLdUD6S.setCurrentAnimation(oBTtFI0PP86Qd);
 break;
 case PASSIVEOBJ_SUB_STATE_1:
 local oBTtFI0PP86Qd = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/thief/Animation/LivingDead/Attact1Start_LivingDead.ani");
 oBTtFI0PP86Qd.setSpeedRate((o3mkAjPCLBZSWTYLdUD6S.getVar().getInt(4)).tofloat());
 o3mkAjPCLBZSWTYLdUD6S.setCurrentAnimation(oBTtFI0PP86Qd);
 
 local dFsSs4Q_I6UuOulRW2 = sq_CreateDrawOnlyObject(o3mkAjPCLBZSWTYLdUD6S, "passiveobject/script_sqr_nut_qq506807329/thief/animation/livingdead/loopmagiccircle.ani", ENUM_DRAWLAYER_BOTTOM, true);
 o3mkAjPCLBZSWTYLdUD6S.getVar("aniObj").clear_obj_vector(); 
 o3mkAjPCLBZSWTYLdUD6S.getVar("aniObj").push_obj_vector(dFsSs4Q_I6UuOulRW2);
 sq_moveWithParent(o3mkAjPCLBZSWTYLdUD6S, dFsSs4Q_I6UuOulRW2);
 break;
 case PASSIVEOBJ_SUB_STATE_2:
 local oBTtFI0PP86Qd = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/thief/Animation/LivingDead/Attack1Loop_LivingDead.ani");
 oBTtFI0PP86Qd.setSpeedRate((o3mkAjPCLBZSWTYLdUD6S.getVar().getInt(4)).tofloat());
 o3mkAjPCLBZSWTYLdUD6S.setCurrentAnimation(oBTtFI0PP86Qd);
 break;
 case PASSIVEOBJ_SUB_STATE_3:
 local oBTtFI0PP86Qd = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/thief/Animation/LivingDead/Attack2Start_LivingDead.ani");
 oBTtFI0PP86Qd.setSpeedRate((o3mkAjPCLBZSWTYLdUD6S.getVar().getInt(4)).tofloat());
 o3mkAjPCLBZSWTYLdUD6S.setCurrentAnimation(oBTtFI0PP86Qd);
 break;
 case PASSIVEOBJ_SUB_STATE_4:
 local oBTtFI0PP86Qd = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/thief/Animation/LivingDead/Attack2Loop_LivingDead.ani");
 oBTtFI0PP86Qd.setSpeedRate((o3mkAjPCLBZSWTYLdUD6S.getVar().getInt(4)).tofloat());
 o3mkAjPCLBZSWTYLdUD6S.setCurrentAnimation(oBTtFI0PP86Qd);
 if (o3mkAjPCLBZSWTYLdUD6S.isMyControlObject()) 
 {
 sq_BinaryStartWrite();
 sq_BinaryWriteDword(SKILL_THIEF_LIVINGDEAD);
 sq_BinaryWriteDword(2);
 sq_BinaryWriteBool(o3mkAjPCLBZSWTYLdUD6S.getVar().getBool(0)); 
 sq_BinaryWriteDword(o3mkAjPCLBZSWTYLdUD6S.getVar().getInt(3)); 
 sq_SendCreatePassiveObjectPacket(o3mkAjPCLBZSWTYLdUD6S, 24378, 0, 50 , 0, 40, o3mkAjPCLBZSWTYLdUD6S.getDirection()); 
 }
 o3mkAjPCLBZSWTYLdUD6S.setTimeEvent(0, o3mkAjPCLBZSWTYLdUD6S.getVar().getInt(1), 1, false); 
 o3mkAjPCLBZSWTYLdUD6S.setTimeEvent(1, o3mkAjPCLBZSWTYLdUD6S.getVar().getInt(2), 0, false); 
 
 break;
 case PASSIVEOBJ_SUB_STATE_5:
 o3mkAjPCLBZSWTYLdUD6S.removeAllTimeEvent(); 
 local oBTtFI0PP86Qd = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/thief/Animation/LivingDead/End_LivingDead.ani");
 oBTtFI0PP86Qd.setSpeedRate((o3mkAjPCLBZSWTYLdUD6S.getVar().getInt(4)).tofloat());
 o3mkAjPCLBZSWTYLdUD6S.setCurrentAnimation(oBTtFI0PP86Qd);
 break;
 }
 break;
 case 2:
 switch (B3XcINIaSmti6qcspHY)
 {
 case PASSIVEOBJ_SUB_STATE_0:
 local wiyvcgcCA2zwYHwKYbru = sq_GetObjectTime(o3mkAjPCLBZSWTYLdUD6S);
 o3mkAjPCLBZSWTYLdUD6S.getVar().setInt(0, wiyvcgcCA2zwYHwKYbru); 
 o3mkAjPCLBZSWTYLdUD6S.getVar().setInt(1, 500); 
 break;
 }
 break;
 }
 break;
 }
} 
 

