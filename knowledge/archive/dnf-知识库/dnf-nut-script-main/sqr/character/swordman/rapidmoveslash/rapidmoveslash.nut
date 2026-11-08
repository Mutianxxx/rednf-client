


function onAfterSetState_swordman_rapidmoveslash(DEJsBtPxNF0X, GSGPg05Xalq9A4JY4YLD_3, uHKRED8ED4EEfH, N6Oph9Yer9XJX88)
{
 if(!DEJsBtPxNF0X) return;
 local JPxICbgz7eKg = DEJsBtPxNF0X.sq_GetVectorData(uHKRED8ED4EEfH, 0); 
 if(JPxICbgz7eKg == 1) 
 {
 
 if(CNSquirrelAppendage.sq_IsAppendAppendage(DEJsBtPxNF0X, "character/swordman/appendage/ap_stateoflimit.nut"))
 {
 if(DEJsBtPxNF0X.sq_IsMyControlObject())
 {
 DEJsBtPxNF0X.sq_StartWrite();
 DEJsBtPxNF0X.sq_WriteDword(248); 
 DEJsBtPxNF0X.sq_WriteDword(3); 
 DEJsBtPxNF0X.sq_WriteDword(DEJsBtPxNF0X.sq_GetBonusRateWithPassive(248, GSGPg05Xalq9A4JY4YLD_3, 3, 1.0)); 
 DEJsBtPxNF0X.sq_WriteDword(DEJsBtPxNF0X.sq_GetDelaySum()); 
 DEJsBtPxNF0X.sq_SendCreatePassiveObjectPacket(24370, 0, 0, 0, 0); 
 }
 }
 }
} ;




function checkExecutableSkill_RapidMoveSlash(obj)
{
	if (!obj) return false;

        local isUse = obj.sq_IsUseSkill(72);
        if (isUse) 
        {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_IntVectPush(1);
            obj.sq_AddSetStatePacket(39,STATE_PRIORITY_USER, true);
            return true;
        }

	return false;
}



function checkCommandEnable_RapidMoveSlash(obj)
{

	return true;
}

