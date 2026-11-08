




function onAfterSetState_mage_MagePokeThrow(vIJx6BPwOwIVCHdhK3Doj, MuAeaLp8eZGg, Xvm0X_PJ_M7MKhS8, HQduPQSXELLmMG7)
{
 if (!vIJx6BPwOwIVCHdhK3Doj) return;
 if(CNSquirrelAppendage.sq_IsAppendAppendage(vIJx6BPwOwIVCHdhK3Doj, "character/mage/avatar/ap_avatar.nut"))
 {
 local czZo2ZoOaMiRtzzmM = vIJx6BPwOwIVCHdhK3Doj.sq_GetVectorData(Xvm0X_PJ_M7MKhS8, 0); 
 local yt29qVG7i8Ku0w_zlVZKsZ = null; 
 switch (czZo2ZoOaMiRtzzmM) 
 {
 case 0:
 yt29qVG7i8Ku0w_zlVZKsZ = setCurrentAnimation_avatar_eff(vIJx6BPwOwIVCHdhK3Doj,"PokeThrowTry",true);
 break;
 case 1:
 yt29qVG7i8Ku0w_zlVZKsZ = setCurrentAnimation_avatar_eff(vIJx6BPwOwIVCHdhK3Doj,"PokeThrowSmash",true);
 break;
 }
 if(yt29qVG7i8Ku0w_zlVZKsZ!=null)
 vIJx6BPwOwIVCHdhK3Doj.setCurrentAnimation(yt29qVG7i8Ku0w_zlVZKsZ); 
 }
} ;
