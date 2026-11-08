



 
 
function onAttack_po_qq506807329new_atmage_24377(obj, damager, boundingBox, isStuck)
{
 if(!obj) return 0;
 local skillindex = obj.getVar("skill").get_vector(0);
 local subtype = obj.getVar("subType").get_vector(0); 
 local stateindex = obj.getVar("state").get_vector(0); 
 switch(skillindex)
 {
 case 243: 
 if(isStuck || !damager.isObjectType(OBJECTTYPE_ACTIVE))return; 
 
 if(subtype == 1 && stateindex == 10)
 {
 createPooledObjEff_qq506807329(obj, "passiveobject/script_sqr_nut_qq506807329/atmage/animation/atelementalfield/atelementalfield_hit001.ani", damager.getXPos(), damager.getYPos(), damager.getZPos() + sq_GetCenterZPos(boundingBox), ENUM_DRAWLAYER_NORMAL, obj.getDirection()); 
 }
 break;
 case 244: 
 if(!damager.isObjectType(OBJECTTYPE_ACTIVE))return; 
 if(subtype == 1 && stateindex == 11)
 {
 if(sq_IsHoldable(obj, damager))
 {
 if(CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/new_atmage/convergencecannon/ap_convergencecannon.nut"))
 CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/new_atmage/convergencecannon/ap_convergencecannon.nut");
 local A9yL4uSpZsRY9BGMY = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 244, false, "character/new_atmage/convergencecannon/ap_convergencecannon.nut", true); 
 sq_HoldAndDelayDie(damager, obj, true, true, false, 0, 0, ENUM_DIRECTION_NEUTRAL, A9yL4uSpZsRY9BGMY); 
 }
 }
 break;
 case 245: 
 if(isStuck || !damager.isObjectType(OBJECTTYPE_ACTIVE))return; 
 if(subtype == 1 && stateindex == 11)
 {
 if(sq_IsHoldable(obj, damager))
 {
 local hgQUvSbfN1qdSfzoikuqVbZj = obj.getParent(); 
 if(hgQUvSbfN1qdSfzoikuqVbZj)
 {
 if(CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/new_atmage/armageddonstrike/ap_armageddonstrike.nut"))
 CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/new_atmage/armageddonstrike/ap_armageddonstrike.nut");
 local A9yL4uSpZsRY9BGMY = CNSquirrelAppendage.sq_AppendAppendage(damager, hgQUvSbfN1qdSfzoikuqVbZj, 245, false, "character/new_atmage/armageddonstrike/ap_armageddonstrike.nut", true); 
 sq_HoldAndDelayDie(damager, hgQUvSbfN1qdSfzoikuqVbZj, true, true, false, 0, 0, ENUM_DIRECTION_NEUTRAL, A9yL4uSpZsRY9BGMY); 
 }
 }
 }
 break;
 case 246: 
 if(!damager.isObjectType(OBJECTTYPE_ACTIVE))return; 
 obj.getVar("dama").push_obj_vector(damager);
 switch(subtype)
 {
 case 1:
 	switch(stateindex)
 	{
 		case 10:
 			if(sq_IsHoldable(obj, damager) || sq_IsGrabable(obj, damager) || !sq_IsFixture(damager)) 
 			{
				if(CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/new_atmage/shardmagnum/ap_shardmagnum_damage.nut"))
 					CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/new_atmage/shardmagnum/ap_shardmagnum_damage.nut");
 				local A9yL4uSpZsRY9BGMY = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 246, true, "character/new_atmage/shardmagnum/ap_shardmagnum_damage.nut", true); 
 			}
 			break;
 		default:
 			if(sq_IsHoldable(obj, damager)) 
 			{
 				if(CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/new_atmage/shardmagnum/ap_shardmagnum.nut"))
 					CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/new_atmage/shardmagnum/ap_shardmagnum.nut");
 				local A9yL4uSpZsRY9BGMY = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 246, false, "character/new_atmage/shardmagnum/ap_shardmagnum.nut", true); 
 				sq_HoldAndDelayDie(damager, obj, true, true, false, 0, 0, ENUM_DIRECTION_NEUTRAL, A9yL4uSpZsRY9BGMY); 
 			}
 			break;
 	}
 	break;
 }
 break;
 case 247: 
 if(isStuck || !damager.isObjectType(OBJECTTYPE_ACTIVE))return; 
 if(subtype == 1)
 {
 if(sq_IsHoldable(obj, damager))
 {
 if(!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/new_atmage/overfreezeextension/ap_overfreezeextension.nut"))
 {
 local A9yL4uSpZsRY9BGMY = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 247, true, "character/new_atmage/overfreezeextension/ap_overfreezeextension.nut", true); 
 A9yL4uSpZsRY9BGMY.sq_SetValidTime(obj.getVar().get_vector(0)); 
 sq_HoldAndDelayDie(damager, obj, true, false, false, 0, 0, ENUM_DIRECTION_NEUTRAL, A9yL4uSpZsRY9BGMY); 
 }
 }
 }
 break;
 case 248: 
 if(isStuck)return; 
 if(subtype == 1)
 {
 switch(stateindex)
 {
 case 10:
 if(obj.getVar().getBool(0) != false)return;
 obj.getVar().setBool(0, true); 
 if(obj.isMyControlObject())
 {
 local LFm_4KnKkBm = sq_GetGlobalIntVector(); 
 sq_IntVectorClear(LFm_4KnKkBm); 
 sq_IntVectorPush(LFm_4KnKkBm, damager.getXPos()); 
 sq_IntVectorPush(LFm_4KnKkBm, damager.getYPos()); 
 sq_IntVectorPush(LFm_4KnKkBm, damager.getZPos()); 
 obj.addSetStatePacket(11, LFm_4KnKkBm, STATE_PRIORITY_AUTO, false, ""); 
 }
 break;
 case 14: 
 break;
 default:
 if(!damager.isObjectType(OBJECTTYPE_ACTIVE))return;
 if(sq_IsHoldable(obj, damager) 
 && !obj.getVar().is_obj_vector(damager)) 
 {
 obj.getVar().push_obj_vector(damager); 
 if(CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/new_atmage/judekatheeternal/ap_judekatheeternal.nut"))
 CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/new_atmage/judekatheeternal/ap_judekatheeternal.nut");
 local A9yL4uSpZsRY9BGMY = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 248, true, "character/new_atmage/judekatheeternal/ap_judekatheeternal.nut", true); 
 sq_HoldAndDelayDie(damager, obj, true, true, false, 0, 0, ENUM_DIRECTION_NEUTRAL, A9yL4uSpZsRY9BGMY); 
 }
 break;
 }
 }
 break;
 }
} ;
 

 
 
function onKeyFrameFlag_po_qq506807329new_atmage_24377(qMNVihjRTmuS, tVkhhJRGalKq)
{
 if(!qMNVihjRTmuS) return false;
 local RNDKDGb7Xh4tmzwoFrEmqi4B = qMNVihjRTmuS.getVar("skill").get_vector(0);
 local LqMdIv7SpKl = qMNVihjRTmuS.getVar("subType").get_vector(0); 
 local JFlt1wvdwKdlcbytEGuXGD = qMNVihjRTmuS.getVar("state").get_vector(0); 
 switch(RNDKDGb7Xh4tmzwoFrEmqi4B)
 {
 case 248: 
 switch(LqMdIv7SpKl)
 {
 case 1:
 switch(JFlt1wvdwKdlcbytEGuXGD)
 {
 case 11:
 if(tVkhhJRGalKq == 1 && qMNVihjRTmuS.isMyControlObject())
 sq_flashScreen(qMNVihjRTmuS, 0, 80, 300, 102, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_CLOSEBACK); 
 break;
 case 12:
 if(tVkhhJRGalKq == 1 && qMNVihjRTmuS.isMyControlObject())
 sq_flashScreen(qMNVihjRTmuS, 0, 80, 300, 102, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_CLOSEBACK); 
 break;
 case 13:
 if(tVkhhJRGalKq == 1 && qMNVihjRTmuS.isMyControlObject())
 sq_flashScreen(qMNVihjRTmuS, 0, 80, 300, 127, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_CLOSEBACK); 
 break;
 }
 break;
 }
 break;
 }
 return true;
} ;
 

 
 
function onTimeEvent_po_qq506807329new_atmage_24377(qMNVihjRTmuS, tVkhhJRGalKq, RNDKDGb7Xh4tmzwoFrEmqi4B)
{
 if(!qMNVihjRTmuS) return false;
 local LqMdIv7SpKl = qMNVihjRTmuS.getVar("skill").get_vector(0);
 switch(LqMdIv7SpKl)
 {
 case 243: 
 if(tVkhhJRGalKq == 0)
 if(qMNVihjRTmuS.isMyControlObject())
 qMNVihjRTmuS.addSetStatePacket(12, null, STATE_PRIORITY_AUTO, false, "");
 break;
 }
 return false;
} ;

 
 
function onDestroyObject_po_qq506807329new_atmage_24377(S9f9umlEnsSSziCqa, wSP12jlPzgYSMyBOWYMMTS)
{
 if(!S9f9umlEnsSSziCqa) return;
 local bWTO_jKwHiljwFU7NIb = S9f9umlEnsSSziCqa.getVar("skill").get_vector(0);
 switch(bWTO_jKwHiljwFU7NIb)
 {
 case -1:
 break;
 }
} ;


 
 
function destroy_po_qq506807329new_atmage_24377(S9f9umlEnsSSziCqa)
{
 if(!S9f9umlEnsSSziCqa) return;
 local wSP12jlPzgYSMyBOWYMMTS = S9f9umlEnsSSziCqa.getVar("skill").get_vector(0);
 switch(wSP12jlPzgYSMyBOWYMMTS)
 {
 case 243: 
 RemoveAllAni(S9f9umlEnsSSziCqa); 
 break;
 }
} ;


 

function onChangeSkillEffect_po_qq506807329new_atmage_24377(S9f9umlEnsSSziCqa, wSP12jlPzgYSMyBOWYMMTS, bWTO_jKwHiljwFU7NIb)
{
 if(!S9f9umlEnsSSziCqa) return;
 switch(skillType)
 {
 case -1:
 break;
 }
} ;

 






