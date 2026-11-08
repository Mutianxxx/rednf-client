





 
 
function setCustomData_po_qq506807329new_fighter_24373(obj, receiveData)
{
 if(!obj)return;
 sq_IntVectorClear(sq_GetGlobalIntVector()); 
 local izsPP8AuIhnk = receiveData.readDword(); 
 obj.getVar("skill").clear_vector(); 
 obj.getVar("skill").push_vector(izsPP8AuIhnk);
 switch(izsPP8AuIhnk) 
 {
 case 225: 
 local NuQJ1u1MnEz = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(NuQJ1u1MnEz);
 switch(NuQJ1u1MnEz)
 {
 case 1: 
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 0); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 local qmp3kTtWKKLM5aXSeE = obj.getXPos();
 local dLQRvotmledk4VlhGR = obj.getYPos();
 local mtEcK5kSB8RW = obj.getZPos();
 obj.getVar().clear_vector(); 
 local vwmPkVFDr4 = obj.getVar(); 
 vwmPkVFDr4.push_vector(qmp3kTtWKKLM5aXSeE); 
 vwmPkVFDr4.push_vector(dLQRvotmledk4VlhGR); 
 vwmPkVFDr4.push_vector(mtEcK5kSB8RW); 
 vwmPkVFDr4.push_vector(sq_GetDistancePos(qmp3kTtWKKLM5aXSeE, obj.getDirection(), receiveData.readDword())); 
 vwmPkVFDr4.push_vector(dLQRvotmledk4VlhGR+receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 obj.getVar().setFloat(0, sq_ToRadian(receiveData.readFloat())); 
 if(obj.isMyControlObject())
 obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, ""); 
 break;
 case 2: 
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 1); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/lightdragonthirteen/explosion_l_normal1.ani");
 obj.setCurrentAnimation(ani); 
 
 sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/fighter/animation/lightdragonthirteen/explosion_l_normal2.ani", ENUM_DRAWLAYER_BOTTOM, true);
 break;
 }
 break;
 case 226: 
 local NuQJ1u1MnEz = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(NuQJ1u1MnEz);
 switch(NuQJ1u1MnEz)
 {
 case 1:
 
 sq_SetCurrentAttackBonusRate(sq_GetCustomAttackInfo(obj, 2), receiveData.readDword()); 
 obj.getVar().clear_vector(); 
 local vwmPkVFDr4 = obj.getVar(); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(obj.getXPos()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 if(obj.isMyControlObject())
 obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, ""); 
 break;
 case 2:
 local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/saintillusion/explode3_charge_explode.ani");
 obj.setCurrentAnimation(ani); 
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 2); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 local WyfBkIIZILinIA4 = receiveData.readDword(); 
 local qmp3kTtWKKLM5aXSeE = obj.getXPos(); 
 local dLQRvotmledk4VlhGR = obj.getYPos(); 
 local mtEcK5kSB8RW = obj.getYPos(); 
 local qZ8ApfUqpx09A1ji4nlDh9h = obj.getObjectManager(); 
 for(local THH14LdcDoVRgEtdqA7B = 0; THH14LdcDoVRgEtdqA7B < qZ8ApfUqpx09A1ji4nlDh9h.getCollisionObjectNumber(); THH14LdcDoVRgEtdqA7B++)
 {
 local y2SAz02iQl = qZ8ApfUqpx09A1ji4nlDh9h.getCollisionObject(THH14LdcDoVRgEtdqA7B); 
 if(y2SAz02iQl
 && !obj.isEnemy(y2SAz02iQl)
 && y2SAz02iQl.isObjectType(OBJECTTYPE_CHARACTER)) 
 {
 local mlqxmT6l8cgl6GZza6WU1lT = sq_GetCNRDObjectToActiveObject(y2SAz02iQl); 
 if(!mlqxmT6l8cgl6GZza6WU1lT.isDead())
 {
 if(sq_Abs(qmp3kTtWKKLM5aXSeE - sq_GetXPos(mlqxmT6l8cgl6GZza6WU1lT)) < 100
 && sq_Abs(dLQRvotmledk4VlhGR - sq_GetYPos(mlqxmT6l8cgl6GZza6WU1lT)) <= 40
 && sq_Abs(mtEcK5kSB8RW - sq_GetZPos(mlqxmT6l8cgl6GZza6WU1lT)) <= 120)
 mlqxmT6l8cgl6GZza6WU1lT.setHp(mlqxmT6l8cgl6GZza6WU1lT.getHp() + WyfBkIIZILinIA4, null, true); 
 }
 }
 }
 break;
 }
 break;
 case 227: 
 local H3oWLprwJ39BkAFv = obj.getParent(); 
 if(H3oWLprwJ39BkAFv)
 sq_moveWithParent(H3oWLprwJ39BkAFv, obj); 
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 3); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/absorbenergyball/lv1_start_shootinhaledenergy_00_normal.ani");
 obj.setCurrentAnimation(ani); 
 local currentAni = sq_GetCurrentAnimation(obj);
 currentAni.addLayerAnimation(6, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/absorbenergyball/lv1_loop_shootinhaledenergy_01_normal.ani"), true); 
 currentAni.addLayerAnimation(6, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/absorbenergyball/lv1_end_shootinhaledenergy_01_normal.ani"), true); 
 currentAni.addLayerAnimation(6, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/absorbenergyball/lv2_start_current_shot_normal.ani"), true); 
 sq_SetAttackBoundingBoxSizeRate(currentAni, 2.2, 1.0, 1.0); 
 local uAejd1pW2r2r89A3oq7 = receiveData.readDword(); 
 local qubNWiTv7LZ = currentAni.getDelaySum(0, 6); 
 obj.setCurrentAnimation(currentAni); 
 obj.setTimeEvent(0, qubNWiTv7LZ / uAejd1pW2r2r89A3oq7, (uAejd1pW2r2r89A3oq7-1<1)?1: uAejd1pW2r2r89A3oq7-1, false); 
 break;
 case 228: 
	local attackPower  = receiveData.readDword();
	local size = (receiveData.readDword()).tofloat() / 100.0; 
	local prob		   = receiveData.readDword();
	local level		   = receiveData.readDword();
	local duration	   = receiveData.readDword();
	local lightDamage = receiveData.readDword();
	local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/nenofbrilliance/ready_ex1_12.ani");
	ani.setImageRateFromOriginal(size, size); 
	ani.setAutoLayerWorkAnimationAddSizeRate(size); 
	sq_SetAttackBoundingBoxSizeRate(ani, size, size, size); 
	obj.setCurrentAnimation(ani); 
	local attackInfo = sq_GetCustomAttackInfo(obj, 4); 
	sq_SetCurrentAttackInfo(obj, attackInfo);
	attackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackBonusRate(attackInfo, attackPower); 
	sq_SetChangeStatusIntoAttackInfoWithEtc(attackInfo, 0, ACTIVESTATUS_LIGHTNING, prob.tointeger(), level, duration, lightDamage,0); 
 	sq_SetCurrentAttackeHitStunTime(attackInfo, 0);
 break;
 case 229: 
 local NuQJ1u1MnEz = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(NuQJ1u1MnEz);
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 4 + NuQJ1u1MnEz); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 
 local tY0vSE0rcPVN6hrRQVKAaHQ = sq_GetCNRDObjectToCollisionObject(obj.getParent()); 
 if(tY0vSE0rcPVN6hrRQVKAaHQ && tY0vSE0rcPVN6hrRQVKAaHQ.getState() == 229) 
 {
 local PzUXbG9DCFSgp1Gia8_G4 = "passiveobj" + NuQJ1u1MnEz.tostring(); 
 tY0vSE0rcPVN6hrRQVKAaHQ.getVar(PzUXbG9DCFSgp1Gia8_G4).push_obj_vector(obj); 
 local BXOEVgreni4yJoV7IIm9 = "atkobj"+ NuQJ1u1MnEz.tostring();
 local kTJan8mjeH = tY0vSE0rcPVN6hrRQVKAaHQ.getVar(BXOEVgreni4yJoV7IIm9).get_obj_vector_size(); 
 local A_bFwVZDmOtxa3wvdekot = tY0vSE0rcPVN6hrRQVKAaHQ.getVar(BXOEVgreni4yJoV7IIm9); 
 for(local THH14LdcDoVRgEtdqA7B = 0; THH14LdcDoVRgEtdqA7B < kTJan8mjeH; THH14LdcDoVRgEtdqA7B++)
 {
 local QufRrrSbnDfC = sq_GetCNRDObjectToCollisionObject(A_bFwVZDmOtxa3wvdekot.get_obj_vector(THH14LdcDoVRgEtdqA7B)); 
 if(QufRrrSbnDfC)sq_AddHitObject(obj, QufRrrSbnDfC); 
 }
 }
 local hRcvCCZ11vsDeuUxk = ["RisingUpperExHIT_A.ani", "RisingUpperExHIT_B.ani", "RisingUpperExHIT_C01.ani"];
 local ani = sq_CreateAnimation("passiveobject/script_sqr_nut_qq506807329/fighter/animation/oneelbowchainhit/", hRcvCCZ11vsDeuUxk[NuQJ1u1MnEz - 1]);
 obj.setCurrentAnimation(ani); 
 break;
 case 230: 
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 8); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/tigerstrike/tiger_endatk_c_eff_12.ani");
 obj.setCurrentAnimation(ani); 
 break;
 case 231: 
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 9); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/chaindestruction/atk04back_01.ani");
 obj.setCurrentAnimation(ani); 
 break;
 case 232: 
 local NuQJ1u1MnEz = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(NuQJ1u1MnEz);
 switch(NuQJ1u1MnEz)
 {
 case 1: 
 local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/finalheaven/frontduststart_10.ani");
 ani.setSpeedRate(receiveData.readFloat()); 
 obj.setCurrentAnimation(ani); 
 sq_SetCurrentAttackInfoFromCustomIndex(obj, 10); 
 break;
 case 2: 
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 11); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/finalheaven/finalheavenexpdummy.ani");
 ani.setSpeedRate(receiveData.readFloat()); 
 obj.setCurrentAnimation(ani); 
 break;
 case 3: 
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 12); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/finalheaven/finalheavensuccesshitdummy.ani");
 ani.setSpeedRate(receiveData.readFloat()); 
 obj.setCurrentAnimation(ani); 
 break;
 }
 break;
 case 233: 
 local NuQJ1u1MnEz = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(NuQJ1u1MnEz);
 switch(NuQJ1u1MnEz)
 {
 case 1: 
 obj.getVar().clear_obj_vector(); 
 local APOSOzx3T0dvPHjUlG = receiveData.readDword(); 
 local L3E9htT3t63 = receiveData.readDword(); 
 local qmp3kTtWKKLM5aXSeE = receiveData.readDword(); 
 local dLQRvotmledk4VlhGR = receiveData.readDword(); 
 local mtEcK5kSB8RW = receiveData.readDword(); 
 if(obj.isMyControlObject())
 {
 sq_BinaryStartWrite();
 sq_BinaryWriteDword(233); 
 sq_BinaryWriteDword(2); 
 sq_BinaryWriteDword(APOSOzx3T0dvPHjUlG); 
 sq_BinaryWriteDword(L3E9htT3t63); 
 sq_BinaryWriteDword(qmp3kTtWKKLM5aXSeE); 
 sq_BinaryWriteDword(dLQRvotmledk4VlhGR); 
 sq_BinaryWriteDword(mtEcK5kSB8RW); 
 sq_SendCreatePassiveObjectPacket(obj, 24373, 0, 0, 0, 0, obj.getDirection()); 
 sq_SetMyShake(obj, 10, 300); 
 sq_flashScreen(obj, 50, 50, 50, 200, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 }
 local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/poisonexplosion/explosion_00_shockwave_n.ani");
 obj.setCurrentAnimation(ani); 
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 13); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 obj.getVar().clear_vector(); 
 local vwmPkVFDr4 = obj.getVar(); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 sq_SetChangeStatusIntoAttackInfo(D3jdBeVLJ5IBpA2lvsu2DF, 0, ACTIVESTATUS_POISON, vwmPkVFDr4.get_vector(7), vwmPkVFDr4.get_vector(8), vwmPkVFDr4.get_vector(9), vwmPkVFDr4.get_vector(10)); 
 sq_SetChangeStatusIntoAttackInfo(D3jdBeVLJ5IBpA2lvsu2DF, 1, ACTIVESTATUS_BURN, vwmPkVFDr4.get_vector(11), vwmPkVFDr4.get_vector(12), vwmPkVFDr4.get_vector(13), vwmPkVFDr4.get_vector(14)); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 break;
 case 2:
 case 3:
 case 4: 
 local mlqxmT6l8cgl6GZza6WU1lT = sq_GetCNRDObjectToActiveObject(sq_GetObject(obj, receiveData.readDword(), receiveData.readDword())); 
 obj.setCurrentPos(receiveData.readDword(), receiveData.readDword(), receiveData.readDword()); 
 if(!mlqxmT6l8cgl6GZza6WU1lT.isDead()) 
 {
 obj.setCurrentPos(mlqxmT6l8cgl6GZza6WU1lT.getXPos(), mlqxmT6l8cgl6GZza6WU1lT.getYPos(), mlqxmT6l8cgl6GZza6WU1lT.getZPos() + sq_GetObjectHeight(mlqxmT6l8cgl6GZza6WU1lT) / 2); 
 sq_moveWithParent(mlqxmT6l8cgl6GZza6WU1lT, obj); 
 
 local H3oWLprwJ39BkAFv = sq_GetCNRDObjectToCollisionObject(obj.getParent()); 
 if(H3oWLprwJ39BkAFv)
 {
 H3oWLprwJ39BkAFv.getVar().push_obj_vector(mlqxmT6l8cgl6GZza6WU1lT); 
 sq_EffectLayerAppendage(mlqxmT6l8cgl6GZza6WU1lT, sq_RGB(0, 0, 0), 254, 1300, 0, 1300); 
 if(obj.isMyControlObject())
 sq_sendSetActiveStatusPacket(mlqxmT6l8cgl6GZza6WU1lT, H3oWLprwJ39BkAFv, ACTIVESTATUS_SLOW, 100.0, 120, false, 1300, H3oWLprwJ39BkAFv.getVar().get_vector(6), H3oWLprwJ39BkAFv.getVar().get_vector(5)); 
 }
 }
 if(obj.isMyControlObject())
 obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, ""); 
 break;
 }
 break;
 case 234: 
 local NuQJ1u1MnEz = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(NuQJ1u1MnEz);
 switch(NuQJ1u1MnEz)
 {
 case 1: 
 sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM); 
 local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/dragonmine/poisonloop_dragonmine_bottom.ani");
 obj.setCurrentAnimation(ani); 
 local VcbtZhLNRdXKLVweR9jR = receiveData.readDword(); 
 obj.setTimeEvent(1, VcbtZhLNRdXKLVweR9jR, 1, false); 
 local Wm4iAbtVrC7VaP = receiveData.readDword(); 
 obj.setTimeEvent(0, Wm4iAbtVrC7VaP, 0, false); 
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 15); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetChangeStatusIntoAttackInfo(D3jdBeVLJ5IBpA2lvsu2DF, 0, ACTIVESTATUS_SLOW, 100, 100, Wm4iAbtVrC7VaP, 0, receiveData.readDword()); 
 sq_SetChangeStatusIntoAttackInfo(D3jdBeVLJ5IBpA2lvsu2DF, 1, ACTIVESTATUS_POISON, receiveData.readDword(), receiveData.readDword(), receiveData.readDword(), receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 if(obj.isMyControlObject())
 sq_flashScreen(obj, 200, VcbtZhLNRdXKLVweR9jR - 200, 200, 60, sq_RGB(128, 0, 128), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
 break;
 case 2: 
 local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/dragonmine/explosion/boom_dragonmine_boom4.ani");
 obj.setCurrentAnimation(ani); 
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 16); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 local DatoSg9ynn620kNasIuHS = receiveData.readDword(); 
 local qubNWiTv7LZ = ani.getDelaySum(0, 13); 
 obj.setTimeEvent(0, qubNWiTv7LZ / DatoSg9ynn620kNasIuHS, DatoSg9ynn620kNasIuHS-1, false); 
 break;
 }
 break;
 case 237: 
 local mlqxmT6l8cgl6GZza6WU1lT = sq_GetCNRDObjectToActiveObject(sq_GetObject(obj, receiveData.readDword(), receiveData.readDword())); 
 if(mlqxmT6l8cgl6GZza6WU1lT)
 {
 obj.setCurrentPos(mlqxmT6l8cgl6GZza6WU1lT.getXPos(), mlqxmT6l8cgl6GZza6WU1lT.getYPos(), mlqxmT6l8cgl6GZza6WU1lT.getZPos()); 
 sq_moveWithParent(mlqxmT6l8cgl6GZza6WU1lT, obj); 
 }
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, receiveData.readDword()); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 break;
 case 238: 
 local NuQJ1u1MnEz = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(NuQJ1u1MnEz);
 switch(NuQJ1u1MnEz)
 {
 case 1:
 local mlqxmT6l8cgl6GZza6WU1lT = sq_GetCNRDObjectToActiveObject(sq_GetObject(obj, receiveData.readDword(), receiveData.readDword())); 
 if(mlqxmT6l8cgl6GZza6WU1lT && !mlqxmT6l8cgl6GZza6WU1lT.isDead())
 {
 obj.setCurrentPos(mlqxmT6l8cgl6GZza6WU1lT.getXPos(), mlqxmT6l8cgl6GZza6WU1lT.getYPos(), mlqxmT6l8cgl6GZza6WU1lT.getZPos() + sq_GetObjectHeight(mlqxmT6l8cgl6GZza6WU1lT) / 2); 
 sq_moveWithParent(mlqxmT6l8cgl6GZza6WU1lT, obj); 
 }
 obj.getVar().clear_vector(); 
 local vwmPkVFDr4 = obj.getVar(); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 vwmPkVFDr4.push_vector(receiveData.readDword()); 
 obj.setTimeEvent(0, 200, 0, true); 
 if(obj.isMyControlObject())
 {
 local SOHbsT6Dk0H226 = sq_flashScreen(obj, 0, 99990, 0, 150, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 sq_flashScreen(obj, 0, 0, 200, 100, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 obj.getVar("flashobj").clear_obj_vector(); 
 obj.getVar("flashobj").push_obj_vector(SOHbsT6Dk0H226); 
 }
 break;
 case 2:
 sq_SetCustomRotate(obj, sq_ToRadian(receiveData.readFloat())); 
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 19); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/torbellino/torbellino_hit_a.ani");
 ani.addLayerAnimation(-1, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/torbellino/torbellino_hit_b.ani"), true);
 obj.setCurrentAnimation(ani); 
 sq_SetMyShake(obj, 2, 100); 
 break;
 case 3:
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 20); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/torbellino/torbellino_hit_c_4.ani");
 ani.addLayerAnimation(-1, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/torbellino/torbellino_hit_c_2.ani"), true);
 ani.addLayerAnimation(-1, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/torbellino/torbellino_hit_c_3.ani"), true);
 ani.addLayerAnimation(-1, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/torbellino/torbellino_hit_c_1.ani"), true);
 obj.setCurrentAnimation(ani); 
 sq_SetMyShake(obj, 8, 300); 
 break;
 }
 break;
 case 239: 
 local NuQJ1u1MnEz = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(NuQJ1u1MnEz);
 switch(NuQJ1u1MnEz)
 {
 case 1:
 local D3jdBeVLJ5IBpA2lvsu2DF = sq_GetCustomAttackInfo(obj, 21); 
 sq_SetCurrentAttackBonusRate(D3jdBeVLJ5IBpA2lvsu2DF, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, D3jdBeVLJ5IBpA2lvsu2DF); 
 local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/fighter/animation/hurricanesupersuplex/boom_26.ani");
 obj.setCurrentAnimation(ani); 
 sq_SetMyShake(obj, 20, 650); 
 break;
 }
 break;
 default: 
 break;
 }
} ;
 
