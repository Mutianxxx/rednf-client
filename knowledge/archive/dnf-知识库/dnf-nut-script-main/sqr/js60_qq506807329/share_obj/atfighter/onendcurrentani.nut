



 
 
function onEndCurrentAni_po_qq506807329new_atfighter_24375(obj)
{
 if(!obj) return;
 local skillindex = obj.getVar("skill").get_vector(0);
 switch(skillindex)
 {
		case 20:
			sq_SendDestroyPacketPassiveObject(obj);
			break;
		case 21:
			sq_SendDestroyPacketPassiveObject(obj);
			break;
		case 22:
			sq_SendDestroyPacketPassiveObject(obj);
			break;
 case 220: 
 if(obj.isMyControlObject())
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 117: 
 if(obj.getState()==10)
 obj.addSetStatePacket(11, null, STATE_PRIORITY_AUTO, false, "");
 break;
 case 67: 
 if(obj.getState()==10)
 obj.addSetStatePacket(11, null, STATE_PRIORITY_AUTO, false, "");
 else if(obj.getState()==11)
 obj.addSetStatePacket(12, null, STATE_PRIORITY_AUTO, false, "");
 else if(obj.getState()==12)
 {
 local pCount = obj.getVar("bonus").get_vector(3);
 if(pCount>0)
 {
 obj.getVar("bonus").set_vector(3,pCount - 1);
 obj.addSetStatePacket(12, null, STATE_PRIORITY_AUTO, false, "");
 }
 else
 obj.addSetStatePacket(13, null, STATE_PRIORITY_AUTO, false, "");
 }
 else if(obj.getState()==13)
 {
 local Path = "passiveobject/chang_qing_skill/atfighter/animation/atspiralgaleforce/forcel_end_15.ani";
 createAnimationPooledEx(obj, Path,1, false,obj.getXPos(), obj.getYPos(), obj.getZPos(),false);
 sq_SendDestroyPacketPassiveObject(obj); 
 }
 break;
 case 90: 
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 15: 

 //local Path = "passiveobject/chang_qing_skill/atfighter/animation/atspiralgaleforce/forcem_loop_12.ani";
 //createAnimationPooledEx(obj, Path,1, false,obj.getXPos(), obj.getYPos(), obj.getZPos(),false);
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 16: 
 if(obj.getState()==11)
 {
 obj.addSetStatePacket(12, null, STATE_PRIORITY_AUTO, false, "");
 }
 break;
 case 223: 
 if(obj.isMyControlObject())
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 226: 
 if(obj.isMyControlObject())
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 227: 
 local nhVgCvy_o4TUQqQSAYNF = obj.getVar("subType").get_vector(0); 
 switch(nhVgCvy_o4TUQqQSAYNF)
 {
 case 1:
 local Gt9CnhX696VZE = sq_GetCustomAttackInfo(obj, 3); 
 sq_SetCurrentAttackBonusRate(Gt9CnhX696VZE, obj.getVar().get_vector(0)); 
 sq_SetCurrentAttackInfo(obj, Gt9CnhX696VZE); 
 local Cp_DhpdPRjPbbSz31U = 10; 
 local nOwFzf7sZ8B = 200; 
 obj.getVar().push_timer_vector();
 local HNWUkSZmxC2WPw0Z8T54 = obj.getVar().get_timer_vector(1);
 HNWUkSZmxC2WPw0Z8T54.setParameter(nOwFzf7sZ8B, Cp_DhpdPRjPbbSz31U); 
 HNWUkSZmxC2WPw0Z8T54.resetInstant(0); 
 HNWUkSZmxC2WPw0Z8T54.setEventOnStart(true); 
 break;
 case 2:
 local J9LObvgoNzQUU = obj.getState(); 
 switch(J9LObvgoNzQUU)
 {
 case 10:
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 }
 break;
 }
 break;
 case 228: 
 if(obj.isMyControlObject())
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 229: 
 if(!obj.isMyControlObject())return;
 local nhVgCvy_o4TUQqQSAYNF = obj.getVar("subType").get_vector(0); 
 switch(nhVgCvy_o4TUQqQSAYNF)
 {
 case 1:
 local J9LObvgoNzQUU = obj.getState(); 
 if(J9LObvgoNzQUU != 13)
 obj.addSetStatePacket(J9LObvgoNzQUU + 1, null, STATE_PRIORITY_AUTO, false, ""); 
 else
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 2:
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 }
 break;
 case 230: 
 if(!obj.isMyControlObject())return;
 local nhVgCvy_o4TUQqQSAYNF = obj.getVar("subType").get_vector(0); 
 switch(nhVgCvy_o4TUQqQSAYNF)
 {
 case 2:
 case 3:
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 }
 break;
 case 231: 
 if(!obj.isMyControlObject())return;
 local nhVgCvy_o4TUQqQSAYNF = obj.getVar("subType").get_vector(0); 
 switch(nhVgCvy_o4TUQqQSAYNF)
 {
 case 1:
 if(obj.getState() != 10)break;
 local IiNgFevJl1cr = obj.getVar("state").get_vector(0); 
 if(IiNgFevJl1cr != 15)
 {
 local dV8JoTPBcOoy8cMzlw4SW = IiNgFevJl1cr + 1; 
 obj.getVar("state").set_vector(0, dV8JoTPBcOoy8cMzlw4SW); 
 local fJGqQOiY39RoLibwSo = sq_GetGlobalIntVector(); 
 sq_IntVectorClear(fJGqQOiY39RoLibwSo); 
 sq_IntVectorPush(fJGqQOiY39RoLibwSo, dV8JoTPBcOoy8cMzlw4SW); 
 obj.addSetStatePacket(10, fJGqQOiY39RoLibwSo, STATE_PRIORITY_AUTO, false, ""); 
 }
 else
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 2:
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 }
 break;
 }
} ;

 
