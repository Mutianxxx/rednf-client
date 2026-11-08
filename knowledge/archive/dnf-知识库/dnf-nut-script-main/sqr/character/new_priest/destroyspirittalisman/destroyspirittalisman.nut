




 
function checkExecutableSkill_priest_destroyspirittalisman(DkEHbbjx_24vxFBkGP)
{
 if(!DkEHbbjx_24vxFBkGP) return false; 
 local ChaLUV1_4iGNDnbLOh93py = DkEHbbjx_24vxFBkGP.sq_IsUseSkill(237); 
 if(ChaLUV1_4iGNDnbLOh93py) 
 {
 DkEHbbjx_24vxFBkGP.sq_AddSetStatePacket(237, STATE_PRIORITY_USER, false); 
 return true; 
 }
 return false; 
} ;

 
function checkCommandEnable_priest_destroyspirittalisman(obj)
{
	if(!obj) return false; 
	return true; 
}

 
function onSetState_priest_destroyspirittalisman(WoT2EQ_oaUS, BUpeB018Buoi9k6389sUAV, IkeAgpImVsA_eRrWr8owu0d, pxVqqa65_FYSSuRJyOdVjkX)
{
 if(!WoT2EQ_oaUS) return; 
 WoT2EQ_oaUS.sq_StopMove(); 
 WoT2EQ_oaUS.sq_SetCurrentAnimation(122);
 WoT2EQ_oaUS.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
} ;

function onKeyFrameFlag_priest_destroyspirittalisman(UNy1Ozn8ScM84f, sqK1unc7p55pR6Wc8vS)
{
 if(!UNy1Ozn8ScM84f) return false;
 if(sqK1unc7p55pR6Wc8vS == 1 && UNy1Ozn8ScM84f.sq_IsMyControlObject())
 {
 local jmcswVj4iTixt = sq_GetSkillLevel(UNy1Ozn8ScM84f, 237); 
 UNy1Ozn8ScM84f.sq_StartWrite();
 UNy1Ozn8ScM84f.sq_WriteDword(237); 
 UNy1Ozn8ScM84f.sq_WriteDword(1); 
 UNy1Ozn8ScM84f.sq_WriteDword(UNy1Ozn8ScM84f.sq_GetLevelData(237, 0, jmcswVj4iTixt)); 
 UNy1Ozn8ScM84f.sq_WriteDword(UNy1Ozn8ScM84f.sq_GetLevelData(237, 1, jmcswVj4iTixt)); 
 UNy1Ozn8ScM84f.sq_WriteDword(UNy1Ozn8ScM84f.sq_GetBonusRateWithPassive(237, 237, 2, 1.0)); 
 UNy1Ozn8ScM84f.sq_SendCreatePassiveObjectPacket(24374, 0, 60, 0, 60);
 }
 return true;
} ;

 
function onEndCurrentAni_priest_destroyspirittalisman(cHiyDb7B58Ykvi1Mp7rc4lb)
{
 if(!cHiyDb7B58Ykvi1Mp7rc4lb) return;
 if(!cHiyDb7B58Ykvi1Mp7rc4lb.sq_IsMyControlObject()) return;
 cHiyDb7B58Ykvi1Mp7rc4lb.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); 
} ;


