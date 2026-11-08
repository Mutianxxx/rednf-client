



 
 
function procAppend_po_qq506807329new_atfighter_24375(obj)
{
 if(!obj) return;
 local skillindex = obj.getVar("skill").get_vector(0);
 switch(skillindex)
 {
 		case 20:
			local pAni = obj.getCurrentAnimation();
			local currentT = sq_GetCurrentTime(pAni);
			local parentChr = obj.getTopCharacter();
			parentChr = sq_GetCNRDObjectToSQRCharacter(parentChr);
			if (parentChr.sq_timer_.isOnEvent(currentT) == true) {
				obj.resetHitObjectList();
			}
			break;
		case 23:
			local pAni = obj.getCurrentAnimation();
			local currentT = sq_GetCurrentTime(pAni);
			local parentChr = obj.getTopCharacter();
			parentChr = sq_GetCNRDObjectToSQRCharacter(parentChr);
			if (parentChr.sq_timer_.isOnEvent(currentT) == true) {
				obj.resetHitObjectList();
			}
			if (parentChr.sq_timer_.isEnd()) {
				crethundertigerbottomend_00(obj, 0, 0, 0, sq_GetIntData(parentChr, 251, 0))
				sq_SendDestroyPacketPassiveObject(obj);
	
			}
			break;
		case 24:
			local pAni = obj.getCurrentAnimation();
			local currentT = sq_GetCurrentTime(pAni);
			local parentChr = obj.getTopCharacter();
			parentChr = sq_GetCNRDObjectToSQRCharacter(parentChr);
			if (parentChr.sq_timer_.isEnd()) {
				crethundertigerfrontend_00(obj, 0, 0, 0, sq_GetIntData(parentChr, 251, 0))
				sq_SendDestroyPacketPassiveObject(obj);
			}
			break;
 case 67: 
 if(obj.getParent().getState()!=45)
 sq_SendDestroyPacketPassiveObject(obj);	
 else
 {
 if(sq_GetCNRDObjectToCharacter(obj.getParent()).getSkillSubState()==3 && obj.getState()==12)
 obj.addSetStatePacket(13, null, STATE_PRIORITY_AUTO, false, "");
 }
 break;
 case 227: 
 local nhVgCvy_o4TUQqQSAYNF = obj.getVar("subType").get_vector(0); 
 switch(nhVgCvy_o4TUQqQSAYNF)
 {
 case 1:
 local Gt9CnhX696VZE = obj.getVar().get_timer_vector(1);
 if(Gt9CnhX696VZE)
 {
 local Cp_DhpdPRjPbbSz31U = obj.getCurrentAnimation(); 
 if(Gt9CnhX696VZE.isOnEvent(sq_GetCurrentTime(Cp_DhpdPRjPbbSz31U) - Cp_DhpdPRjPbbSz31U.getDelaySum(1, 1)) == true) 
 {
 obj.resetHitObjectList(); 
 local nOwFzf7sZ8B = obj.getVar("count").get_vector(0) + 1; 
 obj.getVar("count").set_vector(0, nOwFzf7sZ8B); 
 local HNWUkSZmxC2WPw0Z8T54 = Gt9CnhX696VZE.getEventMaxCount(); 
 if(!obj.getVar("count").getBool(0)
 && nOwFzf7sZ8B.tofloat() / HNWUkSZmxC2WPw0Z8T54.tofloat() >= 0.8)
 {
 obj.getVar("count").setBool(0, true); 
 obj.stopTimeEvent(0); 
 if(obj.isMyControlObject())
 {
 sq_BinaryStartWrite();
 sq_BinaryWriteDword(227); 
 sq_BinaryWriteDword(2); 
 local J9LObvgoNzQUU = obj.getVar(); 
 for(local TV51p98WnUQ3ofyry3Zc_GPB = 1; TV51p98WnUQ3ofyry3Zc_GPB < 7; TV51p98WnUQ3ofyry3Zc_GPB++)
 sq_BinaryWriteDword(J9LObvgoNzQUU.get_vector(TV51p98WnUQ3ofyry3Zc_GPB)); 
 sq_SendCreatePassiveObjectPacket(obj, 24375, 0, 0, 0, 600, obj.getDirection());
 }
 }
 }
 }
 local dcibllV2yjB3EFV6eEe7zt0 = obj.getVar("aniobj").get_obj_vector_size(); 
 if(obj.getVar("aniobj").getBool(0))
 if(dcibllV2yjB3EFV6eEe7zt0 > 0)
 {
 local FrvFeNDr76 = obj.getVar("aniobj"); 
 local IK46rY12Bo = obj.getVar().get_timer_vector(0);
 if(IK46rY12Bo.isOnEvent(sq_GetObjectTime(obj)) == true)
 {
 for(local TV51p98WnUQ3ofyry3Zc_GPB = 0; TV51p98WnUQ3ofyry3Zc_GPB < dcibllV2yjB3EFV6eEe7zt0; TV51p98WnUQ3ofyry3Zc_GPB++)
 {
 local dV8JoTPBcOoy8cMzlw4SW = FrvFeNDr76.get_obj_vector(TV51p98WnUQ3ofyry3Zc_GPB); 
 if(!dV8JoTPBcOoy8cMzlw4SW)continue; 
 local Cp_DhpdPRjPbbSz31U = dV8JoTPBcOoy8cMzlw4SW.getCurrentAnimation(); 
 if(sq_GetAniFrameNumber(Cp_DhpdPRjPbbSz31U, 0) == 1) 
 sq_AddDrawOnlyAniFromParent(dV8JoTPBcOoy8cMzlw4SW, "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/atruinrain/stonefalls_dust.ani", 0, -1, 0);
 }
 }
 for(local TV51p98WnUQ3ofyry3Zc_GPB = 0; TV51p98WnUQ3ofyry3Zc_GPB < dcibllV2yjB3EFV6eEe7zt0; TV51p98WnUQ3ofyry3Zc_GPB++)
 {
 local dV8JoTPBcOoy8cMzlw4SW = FrvFeNDr76.get_obj_vector(TV51p98WnUQ3ofyry3Zc_GPB); 
 if(!dV8JoTPBcOoy8cMzlw4SW)continue; 
 local Cp_DhpdPRjPbbSz31U = dV8JoTPBcOoy8cMzlw4SW.getCurrentAnimation(); 
 if(sq_GetAniFrameNumber(Cp_DhpdPRjPbbSz31U, 0) == 1) 
 {
 local o6rWt8TtmbpXvbH3JkOj = sq_GetCurrentTime(Cp_DhpdPRjPbbSz31U); 
 local hDr08fEwKSqljlAk6P8 = 300; 
 local EEL8FY8IJazND3Ls_W6S1 = 600; 
 local SF9k545RAO = 0; 
 local O7IC5tzyVsvieUdWgk = sq_GetUniformVelocity(EEL8FY8IJazND3Ls_W6S1, SF9k545RAO, o6rWt8TtmbpXvbH3JkOj, hDr08fEwKSqljlAk6P8);
 if(O7IC5tzyVsvieUdWgk == SF9k545RAO) 
 {
 local UfSxX5_sm3WrWSg7V = ""; 
 if(sq_GetXPos(dV8JoTPBcOoy8cMzlw4SW) % 2 == 0) 
 UfSxX5_sm3WrWSg7V = "atruinrainsmallstonea.ptl";
 else 
 UfSxX5_sm3WrWSg7V = "atruinrainsmallstoneb.ptl";
 sq_CreateParticle("passiveobject/script_sqr_nut_qq506807329/atfighter/particle/" + UfSxX5_sm3WrWSg7V, dV8JoTPBcOoy8cMzlw4SW, 0, 0, 10, false, 10, 0, 1); 
 dV8JoTPBcOoy8cMzlw4SW.setCurrentAnimation(sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/atruinrain/explosiona_dust.ani")); 
 local vXfRv6OwcBSP = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/atruinrain/explosionaground_shock.ani"); 
 local Awt6wCRGJ5ZXwa7Vv = sq_CreatePooledObject(vXfRv6OwcBSP, true); 
 sq_SetCurrentDirection(Awt6wCRGJ5ZXwa7Vv, obj.getDirection()); 
 Awt6wCRGJ5ZXwa7Vv.setCurrentPos(sq_GetXPos(dV8JoTPBcOoy8cMzlw4SW), sq_GetYPos(dV8JoTPBcOoy8cMzlw4SW), sq_GetZPos(dV8JoTPBcOoy8cMzlw4SW)); 
 Awt6wCRGJ5ZXwa7Vv = sq_SetEnumDrawLayer(Awt6wCRGJ5ZXwa7Vv, ENUM_DRAWLAYER_BOTTOM); 
 sq_AddObject(obj, Awt6wCRGJ5ZXwa7Vv, OBJECTTYPE_DRAWONLY, false); 
 return; 
 }
 else 
 sq_setCurrentAxisPos(dV8JoTPBcOoy8cMzlw4SW, 2, O7IC5tzyVsvieUdWgk); 
 }
 else 
 {
 if(sq_IsEnd(Cp_DhpdPRjPbbSz31U)) 
 dV8JoTPBcOoy8cMzlw4SW.setValid(false); 
 }
 }
 }
 else if(obj.isMyControlObject())
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 2:
 local RjkNn8_LTDOQ2QKQC2fYe = obj.getState(); 
 switch(RjkNn8_LTDOQ2QKQC2fYe)
 {
 case 0:
 local Cp_DhpdPRjPbbSz31U = obj.getCurrentAnimation(); 
 local o6rWt8TtmbpXvbH3JkOj = sq_GetCurrentTime(Cp_DhpdPRjPbbSz31U); 
 local hDr08fEwKSqljlAk6P8 = 400; 
 local O7IC5tzyVsvieUdWgk = sq_GetUniformVelocity(obj.getVar().get_vector(1), 0, o6rWt8TtmbpXvbH3JkOj, hDr08fEwKSqljlAk6P8);
 sq_setCurrentAxisPos(obj, 2, O7IC5tzyVsvieUdWgk); 
 if(o6rWt8TtmbpXvbH3JkOj >= hDr08fEwKSqljlAk6P8 && obj.isMyControlObject()) 
 obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, ""); 
 break;
 }
 break;
 }
 break;
 case 229: 
 local nhVgCvy_o4TUQqQSAYNF = obj.getVar("subType").get_vector(0); 
 if(nhVgCvy_o4TUQqQSAYNF != 1) break; 
 local RjkNn8_LTDOQ2QKQC2fYe = obj.getState(); 
 switch(RjkNn8_LTDOQ2QKQC2fYe)
 {
 case 11:
 local Gt9CnhX696VZE = obj.getVar().get_timer_vector(0);
 if(Gt9CnhX696VZE)
 {
 if(Gt9CnhX696VZE.isOnEvent(sq_GetObjectTime(obj)) == true) 
 {
 obj.getVar().set_vector(0, obj.getVar().get_vector(0) + 1); 
 local MLMV9JhwchelQ = obj.getVar().get_vector(0); 
 local KZtpgyl9gXaIx3HhcmL = sq_GetUniformVelocity(50, 0, MLMV9JhwchelQ, Gt9CnhX696VZE.getEventMaxCount()); 
 local yIGYnDJN9PWNrrTYX = obj.getVar("atkobj").get_obj_vector_size(); 
 local RPDHx5Wzsd = obj.getVar("atkobj"); 
 for(local TV51p98WnUQ3ofyry3Zc_GPB = 0; TV51p98WnUQ3ofyry3Zc_GPB < yIGYnDJN9PWNrrTYX; TV51p98WnUQ3ofyry3Zc_GPB++)
 {
 local zzih9cz0qPorP4 = sq_GetCNRDObjectToActiveObject(RPDHx5Wzsd.get_obj_vector(TV51p98WnUQ3ofyry3Zc_GPB)); 
 if(zzih9cz0qPorP4)
 if(!zzih9cz0qPorP4.isDead()) 
 {
 local vzW3HNg7ObQ = CNSquirrelAppendage.sq_GetAppendage(zzih9cz0qPorP4, "character/atfighter/cyclonecrash/ap_cyclonecrash.nut"); 
 if(vzW3HNg7ObQ && vzW3HNg7ObQ.isValid())
 sq_MoveToAppendageForce(zzih9cz0qPorP4, obj, obj, 0, 0, KZtpgyl9gXaIx3HhcmL + sq_GetHeightObject(zzih9cz0qPorP4), 0, true, vzW3HNg7ObQ); 
 if(obj.isMyControlObject())
 sq_SendHitObjectPacket(obj, zzih9cz0qPorP4, 0, 0, sq_GetHeightObject(zzih9cz0qPorP4) / -1); 
 sq_SetCurrentDirection(zzih9cz0qPorP4, sq_GetOppositeDirection(sq_GetDirection(zzih9cz0qPorP4))); 
 }
 }
 sq_CreateParticle("passiveobject/script_sqr_nut_qq506807329/atfighter/particle/atcyclonecrashgroundcrashloop_01.ptl", obj, 0, 0, 15, true, 10, 0, 12); 
 sq_CreateParticle("passiveobject/script_sqr_nut_qq506807329/atfighter/particle/atcyclonecrashgroundcrashloop_02.ptl", obj, 0, 0, 15, true, 10, 0, 3); 
 }
 }
 break;
 }
 break;
 case 230: 
 local nhVgCvy_o4TUQqQSAYNF = obj.getVar("subType").get_vector(0); 
 switch(nhVgCvy_o4TUQqQSAYNF)
 {
 case 1:
 if(!obj.isMyControlObject())return;
 local ztCdxUeBXNKsMdm = obj.getParent(); 
 if(!ztCdxUeBXNKsMdm || ztCdxUeBXNKsMdm.getState() != 230) 
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 }
 break;
 }
} ;
 
