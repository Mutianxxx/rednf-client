



 
 
function onEndCurrentAni_po_qq506807329new_thief_24378(RbDrK9ySg_Q3h81qY5)
{
 if(!RbDrK9ySg_Q3h81qY5) return;
 local tkwqbnh_6DKOWEvSWO = RbDrK9ySg_Q3h81qY5.getVar("skill").get_vector(0);
 local KaJdml3vwiuvAl2E8fdyYl9 = RbDrK9ySg_Q3h81qY5.getVar("subType").get_vector(0); 
 local _bi_lZgklAuy = RbDrK9ySg_Q3h81qY5.getVar("state").get_vector(0); 
 switch(tkwqbnh_6DKOWEvSWO)
 {
  case 226: 
 	if (!RbDrK9ySg_Q3h81qY5.isMyControlObject()) return;
 	switch (KaJdml3vwiuvAl2E8fdyYl9)
 	{
		case 1:
			switch (_bi_lZgklAuy)
 			{
 				case PASSIVEOBJ_SUB_STATE_1:
 					RbDrK9ySg_Q3h81qY5.addSetStatePacket(PASSIVEOBJ_SUB_STATE_3, null, STATE_PRIORITY_AUTO, false, "");
 					break;
 				default:
 					RbDrK9ySg_Q3h81qY5.addSetStatePacket(_bi_lZgklAuy+1, null, STATE_PRIORITY_AUTO, false, "");
					break;
 			}
 		break;
 	}
 break;
 case 221: 
 if(!RbDrK9ySg_Q3h81qY5.isMyControlObject()) return;
 switch(KaJdml3vwiuvAl2E8fdyYl9)
 {
 case 1:
 case 2:
 sq_SendDestroyPacketPassiveObject(RbDrK9ySg_Q3h81qY5); 
 break;
 }
 break;
 case 222: 
 if(!RbDrK9ySg_Q3h81qY5.isMyControlObject()) return;
 switch(KaJdml3vwiuvAl2E8fdyYl9)
 {
 case 1:
 case 2:
 case 3:
 sq_SendDestroyPacketPassiveObject(RbDrK9ySg_Q3h81qY5); 
 break;
 }
 break;
 case 225: 
 if(!RbDrK9ySg_Q3h81qY5.isMyControlObject()) return;
 switch(KaJdml3vwiuvAl2E8fdyYl9)
 {
 case 1:
 case 2:
 case 3:
 sq_SendDestroyPacketPassiveObject(RbDrK9ySg_Q3h81qY5); 
 break;
 }
 break;
 }
} 

 
