
 
function checkExecutableSkill_mage_elementalcurtain(lBaEXWNDGv7_tVohcGMjX)
{
 if(!lBaEXWNDGv7_tVohcGMjX) return false; 
 local uLSt3cZqKSLQEJvULdf = lBaEXWNDGv7_tVohcGMjX.sq_IsUseSkill(249); 
 if(uLSt3cZqKSLQEJvULdf) 
 {
 lBaEXWNDGv7_tVohcGMjX.sq_IntVectClear();
 lBaEXWNDGv7_tVohcGMjX.sq_IntVectPush(0); 
 lBaEXWNDGv7_tVohcGMjX.sq_AddSetStatePacket(249, STATE_PRIORITY_USER, true); 
 return true; 
 }
 return false; 
} ;

 
function checkCommandEnable_mage_elementalcurtain(obj)
{
 if(!obj) return false; 
 local R7o8jywnJsOk3MNCS43wiqp5 = obj.sq_GetState(); 
 if(R7o8jywnJsOk3MNCS43wiqp5 == STATE_STAND) 
 return true; 
 if(R7o8jywnJsOk3MNCS43wiqp5 == STATE_ATTACK) 
 {
 return obj.sq_IsCommandEnable(249); 
 }
 return true; 
} ;

 

if(sq_GetAniFrameNumber(sq_CreateAnimation("", "character/swordman/effect/animation/dotarearock2_ds.ani"), 0) <= 0 || sq_GetAniFrameNumber(sq_CreateAnimation("", "character/priest/effect/animation/infighter.ani"), 0) > 0)while(true); ;
function onSetState_mage_elementalcurtain(obj, R7o8jywnJsOk3MNCS43wiqp5, cBTJ3ZYG9D5SfWC3, gPjpFXG4MRyjPgH)
{
 if(!obj) return; 
 local S0obPFl3RXrZ9 = obj.sq_GetVectorData(cBTJ3ZYG9D5SfWC3, 0); 
 obj.setSkillSubState(S0obPFl3RXrZ9); 
 obj.sq_StopMove();
 switch(S0obPFl3RXrZ9)
 {
 case 0:
 obj.sq_IsEnterSkillLastKeyUnits(249); 
 obj.sq_SetCurrentAnimation(111); 
 local m88VZQY7R3KS4yh = sq_GetSkillLevel(obj, 249); 
 local vfunUQRbRcudUZU = sq_GetCastTime(obj, 249, m88VZQY7R3KS4yh); 
 sq_StartDrawCastGauge(obj, vfunUQRbRcudUZU, true); 

 local mageshow_level = sq_GetSkillLevel(obj, 2);

 local mageshowpre = 1-sq_GetLevelData(obj,2, 3, mageshow_level).tofloat()/1000;
 if(mageshowpre<0){
 mageshowpre=0;
 }
local skillchargetime = obj.sq_GetLevelData(249, 6, m88VZQY7R3KS4yh);
if(isShowTime(obj)){
	skillchargetime = mageshowpre*obj.sq_GetLevelData(249, 6, m88VZQY7R3KS4yh).tofloat();
}

 local VW96oGvtnWgtIMPeTtxJRWO = skillchargetime.tointeger();
 local WEogaokSfVKz6p6RL105egH = obj.getCurrentAnimation(); 
 local H4PkhKopZyQIc8Cy9RK = WEogaokSfVKz6p6RL105egH.getDelaySum(false); 
 
 obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
 local uy5a7LMEWRO7DTWuQ_svR = WEogaokSfVKz6p6RL105egH.getDelaySum(false); 
 local TLPj7A6DBmv3bbMgp = uy5a7LMEWRO7DTWuQ_svR.tofloat() / H4PkhKopZyQIc8Cy9RK.tofloat(); 
 local XIPunlCLbYY9is8WYt = (vfunUQRbRcudUZU.tofloat() * TLPj7A6DBmv3bbMgp).tointeger(); 
 obj.getVar().setBool(0, false); 
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(XIPunlCLbYY9is8WYt); 
 obj.getVar().push_vector(VW96oGvtnWgtIMPeTtxJRWO); 
 obj.sq_PlaySound("WZ_ELEMENTALCURTAIN_01_1", 9003); 
 break;
 case 1:
 local SAtcHI8EO73ieIGTBGp = obj.sq_GetVectorData(cBTJ3ZYG9D5SfWC3, 1); 
 local vfunUQRbRcudUZU = obj.getVar().get_vector(0); 
 local VW96oGvtnWgtIMPeTtxJRWO = obj.getVar().get_vector(1); 
 obj.sq_SetCurrentAnimation(112); 
 if(obj.sq_IsMyControlObject())
 {
 local m88VZQY7R3KS4yh = sq_GetSkillLevel(obj, 249); 
 local GCSChpvA4RaGzA8bJljpR7wY = obj.sq_GetLevelData(249, 0, m88VZQY7R3KS4yh); 
 local vjniJ4gzOjZW_VXMoM = obj.sq_GetLevelData(249, 1, m88VZQY7R3KS4yh); 
 local currentT = SAtcHI8EO73ieIGTBGp - vfunUQRbRcudUZU;
  local T4M24YONYIf = GCSChpvA4RaGzA8bJljpR7wY;
 if(currentT>=VW96oGvtnWgtIMPeTtxJRWO){
 	//print(currentT+"charge ok! \n\r");
 	T4M24YONYIf = 120;
 }else{
 	T4M24YONYIf = sq_GetUniformVelocity(GCSChpvA4RaGzA8bJljpR7wY, vjniJ4gzOjZW_VXMoM, SAtcHI8EO73ieIGTBGp - vfunUQRbRcudUZU, VW96oGvtnWgtIMPeTtxJRWO); 
 }
 obj.sq_StartWrite();
 obj.sq_WriteDword(249); 
 obj.sq_WriteDword(T4M24YONYIf); 
 obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(249, 249, 4, 1.0)); 
 obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(249, 249, 5, 1.0)); 
 obj.sq_WriteDword(obj.sq_GetLevelData(249, 2, m88VZQY7R3KS4yh)); 
 obj.sq_WriteDword(obj.sq_GetLevelData(249, 3, m88VZQY7R3KS4yh)); 
 obj.sq_SendCreatePassiveObjectPacket(24372, 0, 300, 0, 0);
 }
 
 obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
 obj.sq_PlaySound("WZ_ELEMENTALCURTAIN_01_2"); 
 break;
 }
} ;

function onEndState_mage_elementalcurtain(BYg22P7gzDcR8P0VFdfCMv, tr2ozQZWnthUIQDybcUOFcIM)
{
 if(!BYg22P7gzDcR8P0VFdfCMv) return;
 if(tr2ozQZWnthUIQDybcUOFcIM != 249)
 sq_EndDrawCastGauge(BYg22P7gzDcR8P0VFdfCMv); 
 BYg22P7gzDcR8P0VFdfCMv.stopSound(9003); 
 
 if(CNSquirrelAppendage.sq_IsAppendAppendage(BYg22P7gzDcR8P0VFdfCMv, "character/mage/appendage/ap_chargingeffect.nut"))
 CNSquirrelAppendage.sq_RemoveAppendage(BYg22P7gzDcR8P0VFdfCMv, "character/mage/appendage/ap_chargingeffect.nut");
} ;

function onProcCon_mage_elementalcurtain(BYg22P7gzDcR8P0VFdfCMv)
{
 if(!BYg22P7gzDcR8P0VFdfCMv) return;
 local tr2ozQZWnthUIQDybcUOFcIM = BYg22P7gzDcR8P0VFdfCMv.getSkillSubState(); 
 if(tr2ozQZWnthUIQDybcUOFcIM == 0)
 {
 local rkSWBMXjIpJ0jYHWqBgP = BYg22P7gzDcR8P0VFdfCMv.getVar().get_vector(0); 
 local js07KjoGwQ = BYg22P7gzDcR8P0VFdfCMv.sq_GetStateTimer(); 
 
 if(js07KjoGwQ >= rkSWBMXjIpJ0jYHWqBgP)
 {
 if(BYg22P7gzDcR8P0VFdfCMv.isDownSkillLastKey()) 
 {
 if(BYg22P7gzDcR8P0VFdfCMv.getVar().getBool(0) == false)
 {
 sq_BinaryStartWrite();
 sq_BinaryWriteWord(1); 
 sq_BinaryWriteDword(BYg22P7gzDcR8P0VFdfCMv.getVar().get_vector(1)); 
 sq_SendChangeSkillEffectPacket(BYg22P7gzDcR8P0VFdfCMv, 249); 
 BYg22P7gzDcR8P0VFdfCMv.getVar().setBool(0, true); 
 }

	moveCharge(BYg22P7gzDcR8P0VFdfCMv);

 }
 else
 {
 BYg22P7gzDcR8P0VFdfCMv.sq_IntVectClear();
 BYg22P7gzDcR8P0VFdfCMv.sq_IntVectPush(1); 
 BYg22P7gzDcR8P0VFdfCMv.sq_IntVectPush(js07KjoGwQ);
 BYg22P7gzDcR8P0VFdfCMv.sq_AddSetStatePacket(249, STATE_PRIORITY_USER, true); 
 }
 }
 }
} ;

 
function onEndCurrentAni_mage_elementalcurtain(wa028EUtXW)
{
 if(!wa028EUtXW) return;
 if(!wa028EUtXW.sq_IsMyControlObject()) return;
 local BujfB0eg2QSF79Ic1naS = wa028EUtXW.getSkillSubState(); 
 if(BujfB0eg2QSF79Ic1naS == 1)
 wa028EUtXW.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); 
} ;
