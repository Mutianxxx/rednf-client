



 
function checkExecutableSkill_atmage_overfreezeextension(wFIP1mA9lyqJj)
{
 
 
 
 
 
 
 
 
 
 
 if(!wFIP1mA9lyqJj) return false; 
 local ZEJlR93Xfq3u0L_E3MG4q = wFIP1mA9lyqJj.sq_IsUseSkill(247); 
 if(ZEJlR93Xfq3u0L_E3MG4q) 
 {
 wFIP1mA9lyqJj.sq_IntVectClear();
 wFIP1mA9lyqJj.sq_IntVectPush(0); 
 wFIP1mA9lyqJj.sq_AddSetStatePacket(247, STATE_PRIORITY_USER, true); 
 return true; 
 }
 return false; 
} ;

 
function checkCommandEnable_atmage_overfreezeextension(wFIP1mA9lyqJj)
{
 if(!wFIP1mA9lyqJj) return false; 
return true; 
 local ZEJlR93Xfq3u0L_E3MG4q = wFIP1mA9lyqJj.sq_GetState(); 
 if(ZEJlR93Xfq3u0L_E3MG4q == STATE_STAND) 
 return true; 
 if(ZEJlR93Xfq3u0L_E3MG4q == STATE_ATTACK) 
 {
 return wFIP1mA9lyqJj.sq_IsCommandEnable(247); 
 }
 return true; 
} ;

 
function onSetState_atmage_overfreezeextension(obj, gMENAd0ViZvuhrYLdIpS5s, fwOCOeFq9yr, Y70fQ_GxyKDyR67)
{
 if(!obj) return; 
 obj.sq_StopMove(); 
 local Ol8AVXsF1kpPcOd1w = obj.sq_GetVectorData(fwOCOeFq9yr, 0); 
 obj.setSkillSubState(Ol8AVXsF1kpPcOd1w); 
 switch(Ol8AVXsF1kpPcOd1w)
 {
 case 0:
 obj.sq_SetCurrentAnimation(105);
 break;
 case 1:
 obj.sq_SetCurrentAnimation(106);
 break;
 }
 local rSdaPSiLJjhzoE5ovO6zjU = obj.sq_GetDelaySum(); 
 obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); 
 local sd9I5MbxS3D2f7aPfz43C = obj.sq_GetDelaySum(); 
 obj.getVar("speedRate").setFloat(0, rSdaPSiLJjhzoE5ovO6zjU.tofloat() / sd9I5MbxS3D2f7aPfz43C.tofloat()); 
 obj.getVar("speedRate").setFloat(1, sd9I5MbxS3D2f7aPfz43C.tofloat() / rSdaPSiLJjhzoE5ovO6zjU.tofloat()); 
 switch(Ol8AVXsF1kpPcOd1w)
 {
 case 0:
 if(obj.sq_IsMyControlObject())
 {
 local R8ITeeYCPkf_9Nm = sq_flashScreen(obj, sd9I5MbxS3D2f7aPfz43C, 99999, 0, 150, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
 obj.getVar("flashobj").clear_obj_vector(); 
 obj.getVar("flashobj").push_obj_vector(R8ITeeYCPkf_9Nm); 
 local aZpVYhbmPw = obj.getObjectManager(); 
 
 CreateAniRate(obj, "character/mage/effect/animation/atoverfreezeextension/atoverfreezeextension_bgsnow.ani", ENUM_DRAWLAYER_COVER, aZpVYhbmPw.getFieldXPos((obj.getDirection() == ENUM_DIRECTION_RIGHT)?0:(800+2*CFG_SCREEN_WIDTH_OFFSETX), ENUM_DRAWLAYER_NORMAL), obj.getYPos(), aZpVYhbmPw.getFieldZPos(0, obj.getYPos(), ENUM_DRAWLAYER_NORMAL), false, obj.getVar("speedRate").getFloat(0) * 100.0); 
 }
 break;
 case 1:
 local MA0dRJJH0_kD = sq_GetSkillLevel(obj, 247); 
 local KJsaUgMf9aieS_O = obj.sq_GetLevelData(247, 2, MA0dRJJH0_kD)/100.0; 
 
 if(obj.sq_IsMyControlObject())
 {
 obj.sq_StartWrite();
 obj.sq_WriteDword(247); 
 obj.sq_WriteDword(1); 
 obj.sq_WriteFloat(KJsaUgMf9aieS_O); 
 obj.sq_WriteFloat(obj.getVar("speedRate").getFloat(0) * 100.0); 
 obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(247, 247, 0, 1.0)); 
 obj.sq_WriteDword(obj.sq_GetLevelData(247, 1, MA0dRJJH0_kD)); 
 obj.sq_SendCreatePassiveObjectPacket(24379, 0, 0, 0, 0);
 RemoveAllFlash(obj); 
 sq_flashScreen(obj, 0, 0, sd9I5MbxS3D2f7aPfz43C+200, 150, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 }
 CreateAniRate(obj, "character/mage/effect/animation/atoverfreezeextension/atoverfreezeextension_mist_01.ani", ENUM_DRAWLAYER_BOTTOM, obj.getXPos(), obj.getYPos(), obj.getZPos(), KJsaUgMf9aieS_O, false); 
 
 sq_myFlashScreen_qq506807329(obj, 0, 60, 0, 178, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM, false); 
 sq_mySetShake_qq506807329(obj, 15, 120, false); 
 
 break;
 }
} ;

 
function onEndCurrentAni_atmage_overfreezeextension(KTPV6RpNFZL8ZIefMPHgQ)
{
 if(!KTPV6RpNFZL8ZIefMPHgQ) return;
 if(!KTPV6RpNFZL8ZIefMPHgQ.sq_IsMyControlObject()) return;
 local JDoY8JKNkL_zr2HEdZNHDv = KTPV6RpNFZL8ZIefMPHgQ.getSkillSubState(); 
 switch(JDoY8JKNkL_zr2HEdZNHDv)
 {
 case 0:
 KTPV6RpNFZL8ZIefMPHgQ.sq_IntVectClear();
 KTPV6RpNFZL8ZIefMPHgQ.sq_IntVectPush(JDoY8JKNkL_zr2HEdZNHDv+1); 
 KTPV6RpNFZL8ZIefMPHgQ.sq_AddSetStatePacket(247, STATE_PRIORITY_USER, true); 
 break;
 case 1:
 KTPV6RpNFZL8ZIefMPHgQ.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); 
 break;
 }
} ;

function onEndState_atmage_overfreezeextension(KTPV6RpNFZL8ZIefMPHgQ, JDoY8JKNkL_zr2HEdZNHDv)
{
 if(!KTPV6RpNFZL8ZIefMPHgQ) return;
 if(JDoY8JKNkL_zr2HEdZNHDv != 247) 
 {
 RemoveAllFlash(KTPV6RpNFZL8ZIefMPHgQ); 
 }
} ;


