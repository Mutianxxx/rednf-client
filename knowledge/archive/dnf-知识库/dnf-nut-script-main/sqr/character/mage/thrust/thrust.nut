


function onAfterSetState_mage_thrust(EUS09I5XEWSNJpMZ80wPDe, DM_j74uKMPtAxxSky4f7vva, ozWuUOO3aD, wquMHdADyE)
{
 if(!EUS09I5XEWSNJpMZ80wPDe) return;
 local QhgmVTg5drTBuTx0wi = EUS09I5XEWSNJpMZ80wPDe.sq_GetVectorData(ozWuUOO3aD, 0); 
 if(CNSquirrelAppendage.sq_IsAppendAppendage(EUS09I5XEWSNJpMZ80wPDe, "character/mage/avatar/ap_avatar.nut"))
 {
 local phIlPu_6nS = null; 
 switch(QhgmVTg5drTBuTx0wi) 
 {
 case 4:
 phIlPu_6nS = setCurrentAnimation_avatar_eff(EUS09I5XEWSNJpMZ80wPDe, "Thrust", true);
 break;
 }
 if(phIlPu_6nS != null)
 EUS09I5XEWSNJpMZ80wPDe.setCurrentAnimation(phIlPu_6nS); 
 }
} ;