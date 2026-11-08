



 
 
function setState_po_qq506807329new_atmage_24377(obj, hRuY8re0Cr, N3rkQZvFCZuWvUN5)
{
 if(!obj) return;
 obj.getVar("state").clear_vector(); 
 obj.getVar("state").push_vector(hRuY8re0Cr);
 local wBYSXC9udAMy6OrtL1JZVmY = obj.getVar("skill").get_vector(0);
 local vAw11S_w7iMNnY384qt9bnGq = obj.getVar("subType").get_vector(0); 
 switch(wBYSXC9udAMy6OrtL1JZVmY)
 {
 case 243: 
 switch(vAw11S_w7iMNnY384qt9bnGq)
 {
 case 1:
 switch(hRuY8re0Cr)
 {
 case 10:
 local zTT7r_ziIs = obj.getVar().getFloat(0); 
 local D7yWSG8JPyUe = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atmage/animation/atelementalfield/magiccirclebttomstart_00.ani"); 
 D7yWSG8JPyUe.setImageRateFromOriginal(zTT7r_ziIs, zTT7r_ziIs); 
 D7yWSG8JPyUe.setAutoLayerWorkAnimationAddSizeRate(zTT7r_ziIs); 
 sq_SetAttackBoundingBoxSizeRate(D7yWSG8JPyUe, zTT7r_ziIs, zTT7r_ziIs, zTT7r_ziIs); 
 obj.setCurrentAnimation(D7yWSG8JPyUe);
 local SGSabkZV0NU6d4XivIKaZhBC = CreateAniRate(obj, "passiveobject/script_sqr_nut_qq506807329/atmage/animation/atelementalfield/magiccirclebackstart_00.ani", ENUM_DRAWLAYER_NORMAL, obj.getXPos(), obj.getYPos(), obj.getZPos(), zTT7r_ziIs, false); 
 CreateAniRate(obj, "character/mage/effect/animation/atelementalfield/atelementalfield_begin_front_buster001.ani", ENUM_DRAWLAYER_NORMAL, obj.getXPos(), obj.getYPos(), obj.getZPos(), zTT7r_ziIs, false); 
 local xAhMkHUkUjjt8SulyPq = CreateAniRate(obj, "passiveobject/script_sqr_nut_qq506807329/atmage/animation/atelementalfield/background/atelementalfield_background_starforce001.ani", ENUM_DRAWLAYER_BOTTOM, obj.getXPos(), obj.getYPos(), obj.getZPos(), zTT7r_ziIs, false); 
 CreateAniRate(obj, "passiveobject/script_sqr_nut_qq506807329/atmage/animation/atelementalfield/begin_spark01.ani", ENUM_DRAWLAYER_BOTTOM, obj.getXPos(), obj.getYPos(), obj.getZPos(), zTT7r_ziIs, false); 
 RemoveAllAni(obj); 
 obj.getVar("aniobj").push_obj_vector(SGSabkZV0NU6d4XivIKaZhBC); 
 obj.getVar("aniobj").push_obj_vector(xAhMkHUkUjjt8SulyPq); 
 local mhAtnrmHZ5oKJI8IzV = obj.getVar().get_vector(0); 
 obj.setTimeEvent(0, mhAtnrmHZ5oKJI8IzV, 1, false); 
 if(obj.isMyControlObject())
 if(mhAtnrmHZ5oKJI8IzV>=400)
 sq_flashScreen(obj, 0, mhAtnrmHZ5oKJI8IzV-400, 400, 76, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 else
 sq_flashScreen(obj, 0, 0, mhAtnrmHZ5oKJI8IzV, 76, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 break;
 case 11:
 local zTT7r_ziIs = obj.getVar().getFloat(0); 
 local D7yWSG8JPyUe = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atmage/animation/atelementalfield/magiccirclebottomloop01_00.ani"); 
 D7yWSG8JPyUe.setImageRateFromOriginal(zTT7r_ziIs, zTT7r_ziIs); 
 D7yWSG8JPyUe.setAutoLayerWorkAnimationAddSizeRate(zTT7r_ziIs); 
 obj.setCurrentAnimation(D7yWSG8JPyUe);
 local SGSabkZV0NU6d4XivIKaZhBC = CreateAniRate(obj, "passiveobject/script_sqr_nut_qq506807329/atmage/animation/atelementalfield/magiccirclebackloop_00.ani", ENUM_DRAWLAYER_NORMAL, obj.getXPos(), obj.getYPos(), obj.getZPos(), zTT7r_ziIs, false); 
 sq_moveWithParent(obj, SGSabkZV0NU6d4XivIKaZhBC); 
 RemoveAllAni(obj); 
 obj.getVar("aniobj").push_obj_vector(SGSabkZV0NU6d4XivIKaZhBC); 
 break;
 case 12:
 obj.getVar("time").clear_vector(); 
 obj.getVar("time").push_vector(sq_GetObjectTime(obj)); 
 obj.getVar("time").push_vector(300); 
 break;
 }
 break;
 }
 break;
 case 244: 
 switch(vAw11S_w7iMNnY384qt9bnGq)
 {
 case 1:
 switch(hRuY8re0Cr)
 {
 case 10:
 setCurrentAnimationFromCutomIndex(obj, 0);
 break;
 case 11:
 setCurrentAnimationFromCutomIndex(obj, 1);
 sq_SetCurrentAttackInfoFromCustomIndex(obj, 1); 
 obj.getVar("move").push_vector(sq_GetObjectTime(obj)); 
 break;
 case 12:
 setCurrentAnimationFromCutomIndex(obj, 2);
 sq_SetCurrentAttackInfoFromCustomIndex(obj, 2); 
 sq_SetMyShake(obj, 6, 240); 
 if(obj.isMyControlObject())
 sq_flashScreen(obj, 60, 60, 600, 204, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 break;
 }
 break;
 }
 break;
 case 245: 
 switch(vAw11S_w7iMNnY384qt9bnGq)
 {
 case 1:
 switch(hRuY8re0Cr)
 {
 case 10: 
 setCurrentAnimationFromCutomIndex(obj, 0);
 break;
 case 11: 
 sq_SetCurrentAttackInfoFromCustomIndex(obj, 3); 
 local y6vCTBa0Lab = sq_GetCurrentAnimation(obj);
 if(y6vCTBa0Lab)
 {
 local HaiCkChTRb6cvBZzXOFF7 = sq_CreateAnimation_SizeRate_SpeedRate("character/mage/effect/animation/atarmageddonstrike/p1/nnaddasatkeff1.ani", obj.getVar("sizeRate").getFloat(0) * 0.5714285714285714, false); 
 
 y6vCTBa0Lab.addLayerAnimation(10000, HaiCkChTRb6cvBZzXOFF7, true); 
 }
 break;
 case 12: 
 sq_setCurrentAxisPos(obj, 2, 0); 
 setCurrentAnimationFromCutomIndex(obj, 1);
 sq_SetCurrentAttackInfoFromCustomIndex(obj, 4); 
 local SEmJLZir994iItLS = sq_GetVectorData(N3rkQZvFCZuWvUN5, 0); 
 if(!SEmJLZir994iItLS)SEmJLZir994iItLS = 100;
 local y6vCTBa0Lab = sq_GetCurrentAnimation(obj);
 y6vCTBa0Lab.setSpeedRate(SEmJLZir994iItLS.tofloat()); 
 
 sq_SetMyShake(obj, 8, 900); 
 break;
 }
 break;
 }
 break;
 case 246: 
 switch(vAw11S_w7iMNnY384qt9bnGq)
 {
 case 1:
 switch(hRuY8re0Cr)
 {
 case 10: 
 sq_setCurrentAxisPos(obj, 2, 60); 
 setCurrentAnimationFromCutomIndex(obj, 1); 
 sq_SetCurrentAttackInfoFromCustomIndex(obj, 7); 
 local zhfNktuYE8KwHZB8E = sq_GetCurrentAttackInfo(obj);
 local attack_rate = sq_GetVectorData(N3rkQZvFCZuWvUN5, 0)
 sq_SetCurrentAttackBonusRate(zhfNktuYE8KwHZB8E, attack_rate); 
 sq_SetChangeStatusIntoAttackInfo(zhfNktuYE8KwHZB8E, 0, ACTIVESTATUS_FREEZE, sq_GetVectorData(N3rkQZvFCZuWvUN5, 1), sq_GetVectorData(N3rkQZvFCZuWvUN5, 2), sq_GetVectorData(N3rkQZvFCZuWvUN5, 3)); 
 obj.getVar("damageRate").clear_vector(); 
 obj.getVar("damageRate").push_vector(sq_GetVectorData(N3rkQZvFCZuWvUN5, 4)); 
 obj.getVar("parentObj").clear_vector(); 
 obj.getVar("parentObj").push_vector(sq_GetVectorData(N3rkQZvFCZuWvUN5, 5)); 
 obj.getVar("parentObj").push_vector(sq_GetVectorData(N3rkQZvFCZuWvUN5, 6)); 
 obj.getVar("damaRate").clear_vector();
 obj.getVar("damaRate").push_vector(attack_rate);
 obj.getVar("dama").clear_obj_vector();
 break;
 }
 break;
 }
 break;
 case 248: 
 switch(vAw11S_w7iMNnY384qt9bnGq)
 {
 case 1:
 switch(hRuY8re0Cr)
 {
 case 10:
 setCurrentAnimationFromCutomIndex(obj, 0); 
 sq_SetCurrentAttackInfoFromCustomIndex(obj, 9); 
 sq_SetVelocity(obj, 0, sq_GetDistancePos(0, obj.getDirection(), 3000).tofloat()); 
 break;
 case 11:
 sq_SetVelocity(obj, 0, 0.0); 
 obj.setCurrentPos(sq_GetVectorData(N3rkQZvFCZuWvUN5, 0), sq_GetVectorData(N3rkQZvFCZuWvUN5, 1)+1, sq_GetVectorData(N3rkQZvFCZuWvUN5, 2)); 
 setCurrentAnimationFromCutomIndex(obj, 1); 
 sq_SetCurrentAttackInfoFromCustomIndex(obj, 10); 
 if(obj.isMyControlObject())
 {
 sq_SetShake(obj, 10, 500); 
 sq_flashScreen(obj, 0, 120, 200, 255, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 }
 break;
 case 12:
 setCurrentAnimationFromCutomIndex(obj, 2); 
 sq_SetCurrentAttackInfoFromCustomIndex(obj, 10); 
 local zhfNktuYE8KwHZB8E = sq_GetCurrentAttackInfo(obj);
 sq_SetCurrentAttackBonusRate(zhfNktuYE8KwHZB8E, obj.getVar().get_vector(0)); 
 if(obj.isMyControlObject())
 sq_SetShake(obj, 3, 400); 
 break;
 case 13:
 setCurrentAnimationFromCutomIndex(obj, 3); 
 sq_SetCurrentAttackInfoFromCustomIndex(obj, 10); 
 if(obj.isMyControlObject())
 sq_SetShake(obj, 7, 300); 
 break;
 case 14:
 setCurrentAnimationFromCutomIndex(obj, 4); 
 sq_SetCurrentAttackInfoFromCustomIndex(obj, 11); 
 if(obj.isMyControlObject())
 {
 sq_SetShake(obj, 10, 500); 
 sq_flashScreen(obj, 0, 80, 500, 204, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 }
 break;
 }
 break;
 }
 break;
 }
} ;
 

