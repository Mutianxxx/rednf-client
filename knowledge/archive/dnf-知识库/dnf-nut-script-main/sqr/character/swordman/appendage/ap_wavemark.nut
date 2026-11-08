
function sq_AddFunctionName(appendage)
{
 appendage.sq_AddFunctionName("proc" , "proc_appendage_wavemark")
}
function proc_appendage_wavemark(appendage)
{
 if (!appendage)
 return; 
 local JsValue1 = appendage.getParent();
 local JsValue2 = sq_GetCNRDObjectToSQRCharacter(JsValue1);
 
 if(!JsValue1 || JsValue2.getState() == STATE_DIE || JsValue2.isDead()) 
{
 appendage.setValid(false);
 return;
 
}
 
 if(appendage.getTimer().Get() < 10000) return;
 if(JsValue2.sq_IsEnterSkill(47) != -1)
 if(JsValue2.sq_IsUseSkill(47))
 
{
 appendage.setValid(false);
 return;
 
}
}
