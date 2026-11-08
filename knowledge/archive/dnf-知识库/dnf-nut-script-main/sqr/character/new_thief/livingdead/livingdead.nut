


function checkExecutableSkill_thief_livingdead(Gkw9pohRwqv3cNajUA2LqM)
{
 if (!Gkw9pohRwqv3cNajUA2LqM || Gkw9pohRwqv3cNajUA2LqM.getZPos()> 0) return false; 
 
 
 local gVUoLVj3RYgXaD2r1Iij0gNZ = Gkw9pohRwqv3cNajUA2LqM.getState();
 switch (gVUoLVj3RYgXaD2r1Iij0gNZ)
 {
 case 0:
 case 8:
 case 14:
 local pbCzh6YSxXtR_bO = Gkw9pohRwqv3cNajUA2LqM.sq_IsUseSkill(SKILL_THIEF_LIVINGDEAD); 
 if (pbCzh6YSxXtR_bO) 
 {
 Gkw9pohRwqv3cNajUA2LqM.sq_IsEnterSkillLastKeyUnits(SKILL_THIEF_LIVINGDEAD); 
 Gkw9pohRwqv3cNajUA2LqM.sq_IntVectClear();
 Gkw9pohRwqv3cNajUA2LqM.sq_IntVectPush(0); 
 Gkw9pohRwqv3cNajUA2LqM.sq_AddSetStatePacket(STATE_THIEF_LIVINGDEAD, STATE_PRIORITY_USER, true); 
 return true; 
 }
 break;
 default:
 if (gVUoLVj3RYgXaD2r1Iij0gNZ > 17)
 {
 local pbCzh6YSxXtR_bO = Gkw9pohRwqv3cNajUA2LqM.sq_IsUseSkill(SKILL_THIEF_LIVINGDEAD); 
 if (pbCzh6YSxXtR_bO) 
 CreatePassiveObject_thief_livingdead(Gkw9pohRwqv3cNajUA2LqM, true);
 }
 break;
 }
 return false; 
} 

 
function checkCommandEnable_thief_livingdead(Gkw9pohRwqv3cNajUA2LqM)
{
 if (!Gkw9pohRwqv3cNajUA2LqM) return false; 
 local gVUoLVj3RYgXaD2r1Iij0gNZ = Gkw9pohRwqv3cNajUA2LqM.sq_GetState(); 
 if (gVUoLVj3RYgXaD2r1Iij0gNZ == STATE_STAND || gVUoLVj3RYgXaD2r1Iij0gNZ == 14) 
 return true; 
 if (gVUoLVj3RYgXaD2r1Iij0gNZ == STATE_ATTACK) 
 {
 return Gkw9pohRwqv3cNajUA2LqM.sq_IsCommandEnable(SKILL_THIEF_LIVINGDEAD); 
 }
 if (gVUoLVj3RYgXaD2r1Iij0gNZ <= 17 || Gkw9pohRwqv3cNajUA2LqM.getZPos() > 0)
 return false;
 return true; 
} 

 
function onSetState_thief_livingdead(Gkw9pohRwqv3cNajUA2LqM, gVUoLVj3RYgXaD2r1Iij0gNZ, pbCzh6YSxXtR_bO, yXh630YTb1qZQBZMDVIhc)
{
 if (!Gkw9pohRwqv3cNajUA2LqM) return; 
 Gkw9pohRwqv3cNajUA2LqM.sq_StopMove(); 
 local snP8JLGQ29QYXcnGpq = Gkw9pohRwqv3cNajUA2LqM.sq_GetVectorData(pbCzh6YSxXtR_bO, 0); 
 Gkw9pohRwqv3cNajUA2LqM.setSkillSubState(snP8JLGQ29QYXcnGpq); 
 switch (snP8JLGQ29QYXcnGpq)
 {
 case 0:
 Gkw9pohRwqv3cNajUA2LqM.sq_SetCurrentAnimation(CUSTOM_ANI_THIEF_LIVINGDEAD);
 break;
 }
 
} 


 
function onEndCurrentAni_thief_livingdead(Gkw9pohRwqv3cNajUA2LqM)
{
 if (!Gkw9pohRwqv3cNajUA2LqM) return;
 if (!Gkw9pohRwqv3cNajUA2LqM.sq_IsMyControlObject()) return;
 local gVUoLVj3RYgXaD2r1Iij0gNZ = Gkw9pohRwqv3cNajUA2LqM.getSkillSubState(); 
 if (gVUoLVj3RYgXaD2r1Iij0gNZ == 0)
 Gkw9pohRwqv3cNajUA2LqM.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); 
} 




 
function onKeyFrameFlag_thief_livingdead(Gkw9pohRwqv3cNajUA2LqM, gVUoLVj3RYgXaD2r1Iij0gNZ)
{
 if (!Gkw9pohRwqv3cNajUA2LqM) return false;
 local pbCzh6YSxXtR_bO = Gkw9pohRwqv3cNajUA2LqM.getSkillSubState(); 
 switch (pbCzh6YSxXtR_bO)
 {
 case 0:
 switch (gVUoLVj3RYgXaD2r1Iij0gNZ)
 {
 case 0:
 CreatePassiveObject_thief_livingdead(Gkw9pohRwqv3cNajUA2LqM,false);
 break;
 }
 break;
 }
 return true;
} 

 
 
 
 
 

function CreatePassiveObject_thief_livingdead(Gkw9pohRwqv3cNajUA2LqM,gVUoLVj3RYgXaD2r1Iij0gNZ)
{
 if (Gkw9pohRwqv3cNajUA2LqM.isMyControlObject()) 
 {
 local pbCzh6YSxXtR_bO = gVUoLVj3RYgXaD2r1Iij0gNZ; 
 if (!gVUoLVj3RYgXaD2r1Iij0gNZ) 
 {
 pbCzh6YSxXtR_bO = Gkw9pohRwqv3cNajUA2LqM.isDownSkillLastKey(); 
 }
 local yXh630YTb1qZQBZMDVIhc = Gkw9pohRwqv3cNajUA2LqM.sq_GetIntData(SKILL_THIEF_LIVINGDEAD, 2) / 100.0; 
 local snP8JLGQ29QYXcnGpq = Gkw9pohRwqv3cNajUA2LqM.sq_GetBonusRateWithPassive(SKILL_THIEF_LIVINGDEAD, STATE_THIEF_LIVINGDEAD, 0, pbCzh6YSxXtR_bO ? 1.0 + yXh630YTb1qZQBZMDVIhc : 1.0 );
 Gkw9pohRwqv3cNajUA2LqM.sq_StartWrite();
 Gkw9pohRwqv3cNajUA2LqM.sq_WriteDword(SKILL_THIEF_LIVINGDEAD);
 Gkw9pohRwqv3cNajUA2LqM.sq_WriteDword(1);
 Gkw9pohRwqv3cNajUA2LqM.sq_WriteBool(pbCzh6YSxXtR_bO); 
 Gkw9pohRwqv3cNajUA2LqM.sq_WriteDword(Gkw9pohRwqv3cNajUA2LqM.sq_GetIntData(SKILL_THIEF_LIVINGDEAD, 0)); 
 Gkw9pohRwqv3cNajUA2LqM.sq_WriteDword(Gkw9pohRwqv3cNajUA2LqM.sq_GetIntData(SKILL_THIEF_LIVINGDEAD, 1)); 
 Gkw9pohRwqv3cNajUA2LqM.sq_WriteDword(snP8JLGQ29QYXcnGpq); 
 Gkw9pohRwqv3cNajUA2LqM.sq_WriteDword(Gkw9pohRwqv3cNajUA2LqM.sq_GetIntData(SKILL_THIEF_LIVINGDEAD, 3)); 
 sq_SendCreatePassiveObjectPacket(Gkw9pohRwqv3cNajUA2LqM, 24378, 0, 50, 0, 0, Gkw9pohRwqv3cNajUA2LqM.getDirection()); 
 }
} 

