

function onAfterSetState_swordman_hundredsword(obj, state, datas, isResetTimer)
{
 if(!obj) return;
 
 obj.getVar("speedRate").clear_vector(); 
 obj.getVar("speedRate").push_vector(0); 
 obj.getVar("speedRate").push_vector(5); 
 obj.getVar("speedRate").push_vector(150); 
 obj.getVar("speedRate").push_vector(800); 
 obj.getVar("hundredsword").clear_obj_vector();
 local c5awBuiF8biZtrp = 240; 
 local YzAoZLxra8 = 75; 
 local mHcvKBLRvErgku9ROh8HoqMQ = 300; 
 local dZznE7LHpHNT1jVfQFhf4p1 = sq_GetDistancePos(sq_GetXPos(obj), obj.getDirection(), 150); 
 local dDHepToJCRR3g5XcdQ7k = sq_GetYPos(obj); 
 local _IMelOgQrHVJ = obj.getObjectManager();
 for(local jKpYvYv8PhGLMcZX0xwQb = 0; jKpYvYv8PhGLMcZX0xwQb < _IMelOgQrHVJ.getCollisionObjectNumber(); jKpYvYv8PhGLMcZX0xwQb++)
 {
 
 local damager = _IMelOgQrHVJ.getCollisionObject(jKpYvYv8PhGLMcZX0xwQb);
 if(!damager 
 || !obj.isEnemy(damager) 
 || !damager.isObjectType(OBJECTTYPE_ACTIVE) 
 || !damager.isInDamagableState(obj) 
 || !sq_IsHoldable(obj, damager) 
 || sq_IsFixture(damager) 
 || !sq_IsGrabable(obj, damager) 
 ) continue; 
 local aI4lV3uoqa = sq_GetXPos(damager); 
 local scUeaAue4DzYYPWZ1 = sq_GetYPos(damager); 
 local yYaAJOajPTxMFUUfPh = sq_GetZPos(damager); 
 if(sq_Abs(dZznE7LHpHNT1jVfQFhf4p1 - aI4lV3uoqa)> c5awBuiF8biZtrp
 || sq_Abs(dDHepToJCRR3g5XcdQ7k - scUeaAue4DzYYPWZ1) > YzAoZLxra8
 || yYaAJOajPTxMFUUfPh > mHcvKBLRvErgku9ROh8HoqMQ)
 continue; 
 
 if(!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/swordman/hundredsword/ap_hundredsword.nut"))
 {
 obj.getVar("hundredsword").push_obj_vector(damager);
 local append = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 86, true, "character/swordman/hundredsword/ap_hundredsword.nut", true);
 sq_HoldAndDelayDie(damager, obj, true, true, false, 0, 0, ENUM_DIRECTION_NEUTRAL, append); 
 append.getVar().clear_vector(); 
 local apVar = append.getVar(); 
 apVar.push_vector(aI4lV3uoqa); 
 apVar.push_vector(scUeaAue4DzYYPWZ1); 
 apVar.push_vector(yYaAJOajPTxMFUUfPh); 
 apVar.push_vector(dZznE7LHpHNT1jVfQFhf4p1); 
 apVar.push_vector(dDHepToJCRR3g5XcdQ7k); 
 apVar.push_vector(0); 
 apVar.push_vector(20); 
 }
 }
} ;


function onEndState_swordman_hundredsword(obj, new_state) {
	if(!obj )
		return;
	if (new_state != 47) {
		local sq_var = obj.getVar("hundredsword");
		local objectsSize = sq_var.get_obj_vector_size();
		for (local i = 0; i < objectsSize; ++i) {
			local damager = sq_var.get_obj_vector(i);
			if (CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/swordman/hundredsword/ap_hundredsword.nut")) {
				CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/swordman/hundredsword/ap_hundredsword.nut");
			}
		}
	}
}
