


function sq_AddFunctionName(appendage)
{
 appendage.sq_AddFunctionName("onStart", "onStart_appendage_priest_buff_chakraofpassion")
    appendage.sq_AddFunctionName("onVaildTimeEnd", "onVaildTimeEnd_appendage_priest_buff_chakraofpassion")
}

function onStart_appendage_priest_buff_chakraofpassion(fCQTuWpa5SVneWuU5MHAzl)
{
 if (!fCQTuWpa5SVneWuU5MHAzl) return;
 local x_1vZNEqM6zjpsGQO0z0 = fCQTuWpa5SVneWuU5MHAzl.getParent(); 
 if(!x_1vZNEqM6zjpsGQO0z0) {
 fCQTuWpa5SVneWuU5MHAzl.setValid(false);
 return;
 }
 
 x_1vZNEqM6zjpsGQO0z0 = sq_GetCNRDObjectToSQRCharacter(x_1vZNEqM6zjpsGQO0z0);
 if(x_1vZNEqM6zjpsGQO0z0)
 x_1vZNEqM6zjpsGQO0z0.setSkillCommandEnable(241,ture);
} ;


function onVaildTimeEnd_appendage_priest_buff_chakraofpassion(lQeRdxL9vQ)
{
 if(!lQeRdxL9vQ) return;
 local ZaoROpHHK4I = lQeRdxL9vQ.getParent(); 
 if(!ZaoROpHHK4I) {
 lQeRdxL9vQ.setValid(false);
 return;
 }
 
 ZaoROpHHK4I = sq_GetCNRDObjectToSQRCharacter(ZaoROpHHK4I);
 if(ZaoROpHHK4I)
 ZaoROpHHK4I.setSkillCommandEnable(241,false);
} ;