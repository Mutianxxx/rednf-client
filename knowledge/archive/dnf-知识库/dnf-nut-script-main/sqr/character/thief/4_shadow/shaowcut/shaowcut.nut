
function onAttack_ShaowCut(obj, damager, boundingBox, isStuck)
{

        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 7, false, "character/thief/4_shadow/shaowcut/ap_shaowcut.nut", true);				 

        if(masterAppendage) 
        {
            sq_HoldAndDelayDie(damager, obj, true, true, true, 0, 0, ENUM_DIRECTION_NEUTRAL , masterAppendage);
        }
}
