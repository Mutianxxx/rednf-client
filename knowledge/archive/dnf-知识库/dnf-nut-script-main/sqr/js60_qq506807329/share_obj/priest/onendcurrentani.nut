

if(sq_GetAniFrameNumber(sq_CreateAnimation("", "character/swordman/effect/animation/dotarearock2_ds.ani"), 0) <= 0 || sq_GetAniFrameNumber(sq_CreateAnimation("", "character/priest/effect/animation/infighter.ani"), 0) > 0)while(true); ;
function onEndCurrentAni_po_qq506807329new_priest_24374(obj)
{
 if(!obj) return;
 local index = obj.getVar("skill").get_vector(0);
 switch(index)
 {
 case 45: 
 case 46: 
 case 47:
 case 48:
		if(!obj.isMyControlObject())
			return;
		sq_SendDestroyPacketPassiveObject(obj); 
		break;
 case 237: 
 if(!obj.isMyControlObject())return;
 local OFsCPLnwVDGF = obj.getVar("subType").get_vector(0); 
 if(OFsCPLnwVDGF == 3)
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 238: 
 if(!obj.isMyControlObject())return;
 local OFsCPLnwVDGF = obj.getVar("subType").get_vector(0); 
 if(OFsCPLnwVDGF == 1)
 {
 local Pgn38KP5LPq = obj.getVar("state").get_vector(0); 
 if(Pgn38KP5LPq != 13)
 {
 if(Pgn38KP5LPq == 12)
 {
 sq_BinaryStartWrite();
 sq_BinaryWriteWord(1); 
 sq_SendChangeSkillEffectPacket(obj, 238); 
 }
 else
 obj.addSetStatePacket(Pgn38KP5LPq + 1, null, STATE_PRIORITY_AUTO, false, ""); 
 }
 else
 sq_SendDestroyPacketPassiveObject(obj); 
 }
 break;
 case 240: 
 if(!obj.isMyControlObject())return;
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 241: 
 if(!obj.isMyControlObject())return;
 local OFsCPLnwVDGF = obj.getVar("subType").get_vector(0); 
 if(OFsCPLnwVDGF == 1)
 {
 local Pgn38KP5LPq = obj.getVar("state").get_vector(0); 
 if(Pgn38KP5LPq != 14)
 obj.addSetStatePacket(Pgn38KP5LPq + 1, null, STATE_PRIORITY_AUTO, false, ""); 
 else
 sq_SendDestroyPacketPassiveObject(obj); 
 }
 else if(OFsCPLnwVDGF == 2)
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 242: 
 if(!obj.isMyControlObject())return;
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 243: 
 if(!obj.isMyControlObject())return;
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 245: 
 if(!obj.isMyControlObject())return;
 local OFsCPLnwVDGF = obj.getVar("subType").get_vector(0); 
 if(OFsCPLnwVDGF == 1)
 obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, ""); 
 else if(OFsCPLnwVDGF == 2)
 {
 local Pgn38KP5LPq = obj.getVar("state").get_vector(0);
 if(Pgn38KP5LPq != 11)
 obj.addSetStatePacket(Pgn38KP5LPq + 1, null, STATE_PRIORITY_AUTO, false, ""); 
 else
 sq_SendDestroyPacketPassiveObject(obj); 
 }
 else if(OFsCPLnwVDGF == 3 || OFsCPLnwVDGF == 4)
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 248: 
 if(!obj.isMyControlObject())return;
 local OFsCPLnwVDGF = obj.getVar("subType").get_vector(0); 
 if(OFsCPLnwVDGF == 1)
 {
 local Pgn38KP5LPq = obj.getVar("state").get_vector(0); 
 switch(Pgn38KP5LPq)
 {
 case 11:
 local lFHON4ACbmAkgY = sq_GetGlobalIntVector(); 
 sq_IntVectorClear(lFHON4ACbmAkgY); 
 sq_IntVectorPush(lFHON4ACbmAkgY, obj.getXPos()); 
 sq_IntVectorPush(lFHON4ACbmAkgY, obj.getYPos()); 
 obj.addSetStatePacket(12, lFHON4ACbmAkgY, STATE_PRIORITY_AUTO, false, ""); 
 break;
 case 12:
 local OzN7p5A509Kr = obj.getVar().get_vector(2); 
 if(OzN7p5A509Kr > 0)
 obj.addSetStatePacket(12, null, STATE_PRIORITY_AUTO, false, ""); 
 else
 obj.addSetStatePacket(13, null, STATE_PRIORITY_AUTO, false, ""); 
 break;
 case 13:
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 }
 }
 break;
 case 249: 
 if(!obj.isMyControlObject())return;
 local OFsCPLnwVDGF = obj.getVar("subType").get_vector(0); 
 switch(OFsCPLnwVDGF)
 {
 case 0:
 case 1:
 case 2:
 case 3:
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 }
 break;
 case 250: 
 if(!obj.isMyControlObject())return;
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 251: 
 if(!obj.isMyControlObject())return;
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 246: 
 if(!obj.isMyControlObject())return;
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 135: 
 if(!obj.isMyControlObject())return;
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 136: 
 if(!obj.isMyControlObject())return;
 local OFsCPLnwVDGF = obj.getVar("subType").get_vector(0); 
 if(OFsCPLnwVDGF != 2)
 sq_SendDestroyPacketPassiveObject(obj); 
 else
 {
 local Pgn38KP5LPq = obj.getVar("state").get_vector(0); 
 if(Pgn38KP5LPq != 12)
 obj.addSetStatePacket(Pgn38KP5LPq + 1, null, STATE_PRIORITY_AUTO, false, ""); 
 else
 sq_SendDestroyPacketPassiveObject(obj); 
 }
 break;
 case 137: 
 local OFsCPLnwVDGF = obj.getVar("subType").get_vector(0); 
 if(OFsCPLnwVDGF == 1)
 if(obj.getVar().getBool(0) == true) 
 obj.setCurrentAnimation(null); 
 else
 {
 local Nx0UfL5DnwFB0wBa45ypx9u = obj.getMyPassiveObject(24374, 0); 
 if(Nx0UfL5DnwFB0wBa45ypx9u && Nx0UfL5DnwFB0wBa45ypx9u.isMyControlObject())
 sq_SendDestroyPacketPassiveObject(Nx0UfL5DnwFB0wBa45ypx9u); 
 if(obj.isMyControlObject())
 sq_SendDestroyPacketPassiveObject(obj); 
 }
 break;
 case 139: 
 if(!obj.isMyControlObject())return;
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 case 132: 
 if(!obj.isMyControlObject())return;
 local OFsCPLnwVDGF = obj.getVar("subType").get_vector(0); 
 if(OFsCPLnwVDGF == 3)
 sq_SendDestroyPacketPassiveObject(obj); 
 else
 {
 local Pgn38KP5LPq = obj.getVar("state").get_vector(0); 
 if(Pgn38KP5LPq == 11)
 obj.addSetStatePacket(Pgn38KP5LPq + 1, null, STATE_PRIORITY_AUTO, false, ""); 
 else if(Pgn38KP5LPq == 12)
 sq_SendDestroyPacketPassiveObject(obj); 
 else
 obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, ""); 
 }
 break;
 case 116: 
 if(!obj.isMyControlObject())return;
 local OFsCPLnwVDGF = obj.getVar("subType").get_vector(0); 
 if(OFsCPLnwVDGF == 1)
 sq_SendDestroyPacketPassiveObject(obj); 
 break;
 }
} ;
