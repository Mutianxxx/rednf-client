





 
 
function setCustomData_po_qq506807329new_atfighter_24375(obj, receiveData)
{
 if(!obj) return;
 local skillindex = receiveData.readDword(); 
 obj.getVar("skill").clear_vector(); 
 obj.getVar("skill").push_vector(skillindex);
 switch(skillindex) 
 {
		case 20:
			local atkRate = receiveData.readDword();
			local size = receiveData.readDword();
			local lightProc = receiveData.readDword();
			local lightleve = receiveData.readDword();
			local lightTime = receiveData.readDword();
			local lightPower = receiveData.readDword();
			local hitCnt = receiveData.readDword();

			local ani = obj.getVar().GetAnimationMap("thundercannon", "passiveobject/zrr_skill/atfighter/animation/atthundercannon/atthundercannon_front20.ani");
			obj.setCurrentAnimation(ani);
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);

			local attackInfo = sq_GetCustomAttackInfo(obj, 16);
			sq_SetCurrentAttackInfo(obj, attackInfo);
			local attackInfo = sq_GetCurrentAttackInfo(obj);
			sq_SetCurrentAttackBonusRate(attackInfo, atkRate);

			sq_SetChangeStatusIntoAttackInfoWithEtc(attackInfo, 0, ACTIVESTATUS_LIGHTNING, lightProc, lightleve, lightTime, lightPower, 0);
			local imageRate = size.tofloat() / 100.0;
			ani = obj.getCurrentAnimation();
			ani.setImageRateFromOriginal(imageRate, imageRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(imageRate);
			sq_SetAttackBoundingBoxSizeRate(ani, imageRate, imageRate, imageRate);

			local parentChr = obj.getTopCharacter();
			parentChr = sq_GetCNRDObjectToSQRCharacter(parentChr);

			local pAni = obj.getCurrentAnimation();
			local delay = pAni.getDelaySum(false);
			local initDelay = 0;
			local term = delay / hitCnt;
			parentChr.sq_timer_.setParameter(term, hitCnt);
			parentChr.sq_timer_.resetInstant(initDelay);
			break;
		case 21:
			local power = receiveData.readDword();
			local size = receiveData.readDword();
			local lightProc = receiveData.readDword();
			local lightleve = receiveData.readDword();
			local lightTime = receiveData.readDword();
			local lightPower = receiveData.readDword();
			local ani = obj.getVar().GetAnimationMap("thunderkicklighting", "passiveobject/zrr_skill/atfighter/animation/atthunderkick/thunderkickhit_lighting.ani");
			obj.setCurrentAnimation(ani);
			
			local attackInfo = sq_GetCustomAttackInfo(obj, 17);
			sq_SetCurrentAttackInfo(obj, attackInfo);
			attackInfo = sq_GetCurrentAttackInfo(obj);
			sq_SetCurrentAttackPower(attackInfo, power);
			//sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, ACTIVESTATUS_LIGHTNING, lightProc, lightleve, lightTime, lightPower);
			sq_SetChangeStatusIntoAttackInfoWithEtc(attackInfo, 0, ACTIVESTATUS_LIGHTNING, lightProc, lightleve, lightTime, lightPower, 0);
			local imageRate = size.tofloat() / 100.0;
			ani = obj.getCurrentAnimation();
			ani.setImageRateFromOriginal(imageRate, imageRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(imageRate);
			sq_SetAttackBoundingBoxSizeRate(ani, imageRate, imageRate, imageRate);
			crethunderkickfloor_light(obj, 0, 0, 0, size);
			break;
		case 22:
			local atkRate = receiveData.readDword();
			local size = receiveData.readDword();
			local lightProc = receiveData.readDword();
			local lightleve = receiveData.readDword();
			local lightTime = receiveData.readDword();
			local lightPower = receiveData.readDword();
			crethundertigerattback_00(obj, 0, 0, 0, size)
			local ani = obj.getVar().GetAnimationMap("thundertiger1", "passiveobject/zrr_skill/atfighter/animation/atthundertiger/thundertigerattfront_00.ani");
			obj.setCurrentAnimation(ani);
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);

			local attackInfo = sq_GetCustomAttackInfo(obj, 19);
			sq_SetCurrentAttackInfo(obj, attackInfo);
			attackInfo = sq_GetCurrentAttackInfo(obj);
			sq_SetCurrentAttackBonusRate(attackInfo, atkRate);
			sq_SetChangeStatusIntoAttackInfoWithEtc(attackInfo, 0, ACTIVESTATUS_LIGHTNING, lightProc, lightleve, lightTime, lightPower, 0);
			local imageRate = size.tofloat() / 100.0;
			ani = obj.getCurrentAnimation();
			ani.setImageRateFromOriginal(imageRate, imageRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(imageRate);
			sq_SetAttackBoundingBoxSizeRate(ani, imageRate, imageRate, imageRate);
			crethundertigerattbottom_00(obj, 0, 0, 0, size)
			break;
		case 23:
			local atkRate = receiveData.readDword();
			local size = receiveData.readDword();
			local bloodProc = receiveData.readDword();
			local bloodleve = receiveData.readDword();
			local bloodTime = receiveData.readDword();
			local bloodRate = receiveData.readDword();
			local hitCnt = 	receiveData.readDword();
			local term = receiveData.readDword();

			local ani = obj.getVar().GetAnimationMap("thundertiger2", "passiveobject/zrr_skill/atfighter/animation/atthundertiger/thundertigerbottomloop_00.ani");
			obj.setCurrentAnimation(ani);
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);

			local attackInfo = sq_GetCustomAttackInfo(obj, 20);
			sq_SetCurrentAttackInfo(obj, attackInfo);
			attackInfo = sq_GetCurrentAttackInfo(obj);
			sq_SetCurrentAttackBonusRate(attackInfo, atkRate);
			sq_SetChangeStatusIntoAttackInfoWithEtc(attackInfo, 0, ACTIVESTATUS_LIGHTNING, bloodProc, bloodleve, bloodTime, bloodRate, 0);
			local imageRate = size.tofloat() / 100.0;
			ani = obj.getCurrentAnimation();
			ani.setImageRateFromOriginal(imageRate, imageRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(imageRate);
			sq_SetAttackBoundingBoxSizeRate(ani, imageRate, imageRate, imageRate);

			local parentChr = obj.getTopCharacter();
			parentChr = sq_GetCNRDObjectToSQRCharacter(parentChr);

			local initDelay = 0;
			parentChr.sq_timer_.setParameter(term, hitCnt);
			parentChr.sq_timer_.resetInstant(initDelay);
			break;
		case 24:
			local size = receiveData.readDword();	
			local hitCnt = 	receiveData.readDword();
			local term = receiveData.readDword();
		
			local ani = obj.getVar().GetAnimationMap("thundertiger3", "character/fighter/effect/animation/atthundertiger/thundertigerfrontloop_00.ani"); 
			obj.setCurrentAnimation(ani);
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
			
			local imageRate = size.tofloat() / 100.0;
			ani = obj.getCurrentAnimation();
			ani.setImageRateFromOriginal(imageRate, imageRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(imageRate);
			sq_SetAttackBoundingBoxSizeRate(ani, imageRate, imageRate, imageRate);
		
			local parentChr = obj.getTopCharacter();
			parentChr = sq_GetCNRDObjectToSQRCharacter(parentChr);	
			
			local initDelay = 0;
			parentChr.sq_timer_.setParameter(term, hitCnt);
			parentChr.sq_timer_.resetInstant(initDelay);
			break;
	case 117:
		local CMV7SABu7A55w42 = receiveData.readDword();
		local C7ui6tdHtec1MGdkL = receiveData.readBool();
		obj.getVar().setBool(0,C7ui6tdHtec1MGdkL);
		obj.getVar("bonus").clear_vector();
		obj.getVar("bonus").push_vector(CMV7SABu7A55w42);
		obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, "");
		break;
	case 67:
		local CjPXeyt2nEMQL3 = sq_GetCustomAttackInfo(obj, 0);
		local CEyePc9vDgKnu = receiveData.readDword();
		local C4n6N6CZdSOx6gb = receiveData.readDword();
		local CQkagaOjtcyUoReUW = receiveData.readDword();
		local CL65qUzSAZUcxR = receiveData.readDword();
		sq_moveWithParent(obj.getParent(), obj);
		if(obj.isMyControlObject())
		{
			obj.getVar("bonus").clear_vector();
			obj.getVar("bonus").push_vector(CEyePc9vDgKnu);
			obj.getVar("bonus").push_vector(C4n6N6CZdSOx6gb);
			obj.getVar("bonus").push_vector(CQkagaOjtcyUoReUW);
			obj.getVar("bonus").push_vector(CL65qUzSAZUcxR);
			obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, "");
		}
		break;
	case 90:
		local ClCaIf678qlkJftP = sq_CreateAnimation("", "passiveobject/chang_qing_skill/atfighter/animation/atspiralgaleforce/forcel_loop_09.ani");
		obj.setCurrentAnimation(ClCaIf678qlkJftP);
		local CjPXeyt2nEMQL3 = sq_GetCustomAttackInfo(obj, 0);
		local CMV7SABu7A55w42 = receiveData.readDword();
		sq_SetCurrentAttackBonusRate(CjPXeyt2nEMQL3, CMV7SABu7A55w42);
		sq_SetCurrentAttackInfo(obj, CjPXeyt2nEMQL3);
		break;
	case 15:
		local ClCaIf678qlkJftP = sq_CreateAnimation("", "passiveobject/chang_qing_skill/atfighter/animation/atspiralgaleforce/spiralroarstun_02.ani");
		obj.setCurrentAnimation(ClCaIf678qlkJftP);
		local CjPXeyt2nEMQL3 = sq_GetCustomAttackInfo(obj, 0);
		local CMV7SABu7A55w42 = receiveData.readDword();
		sq_SetCurrentAttackBonusRate(CjPXeyt2nEMQL3, CMV7SABu7A55w42);
		sq_SetCurrentAttackInfo(obj, CjPXeyt2nEMQL3);
		break;
	case 16:
		local CjPXeyt2nEMQL3 = sq_GetCustomAttackInfo(obj, 0);
		local damagebonus = receiveData.readDword() + receiveData.readDword();
		sq_SetCurrentAttackBonusRate(CjPXeyt2nEMQL3, damagebonus);
		sq_SetChangeStatusIntoAttackInfoWithEtc(CjPXeyt2nEMQL3, 0, 6 ,receiveData.readDword(),receiveData.readDword() ,receiveData.readDword(), receiveData.readDword(), 0);
		sq_SetCurrentAttackInfo(obj, CjPXeyt2nEMQL3);
		obj.getVar("Size").setInt(0,receiveData.readDword());
		local N = receiveData.readDword();
		obj.setTimeEvent(3,1500/N,N,false);
		obj.setTimeEvent(0,700,2,false);
		obj.setTimeEvent(1,2900,1,false);
		obj.addSetStatePacket(11, null, STATE_PRIORITY_AUTO, false, "");
		break;
	case 120:
		local ClCaIf678qlkJftP = sq_CreateAnimation("", "passiveobject/chang_qing_skill/atfighter/animation/atspiralgaleforce/Cast2_effect_01.ani");
		obj.setCurrentAnimation(ClCaIf678qlkJftP);
		local CjPXeyt2nEMQL3 = sq_GetCustomAttackInfo(obj, 0);
		local CMV7SABu7A55w42 = receiveData.readDword();
		sq_SetCurrentAttackBonusRate(CjPXeyt2nEMQL3, CMV7SABu7A55w42);
		sq_SetCurrentAttackInfo(obj, CjPXeyt2nEMQL3);
		local CozVc8NiDoZ59jP = "passiveobject/chang_qing_skill/atfighter/animation/atspiralgaleforce/draweffect_02.ani";
		local C2dryLAVdRSMJhE6c = createAnimationPooledEx(obj, CozVc8NiDoZ59jP,1, true,obj.getXPos(), obj.getYPos(), obj.getZPos(),false);
		obj.getVar("Pooledobj").clear_obj_vector();
		obj.getVar("Pooledobj").push_obj_vector(C2dryLAVdRSMJhE6c);
		obj.setTimeEvent(0,700,2,false);
		obj.setTimeEvent(1,2000,1,false);
		obj.setTimeEvent(2,1400,1,false);
		break;
 case 220: 
 local DCLAuL0zyiL1S1eIh = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/atspiralemperorslap/spiralemperorslap_boom_explosion.ani");
 obj.setCurrentAnimation(DCLAuL0zyiL1S1eIh); 
 local wWNge5FZR9Rw = sq_GetCustomAttackInfo(obj, 0); 
 sq_SetCurrentAttackBonusRate(wWNge5FZR9Rw, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wWNge5FZR9Rw); 
 sq_SetMyShake(obj, 5, 300); 
 if(obj.isMyControlObject())
 sq_flashScreen(obj, 0, 120, 320, 153, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 break;
 case 223: 
 local DCLAuL0zyiL1S1eIh = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/atdropfire/atdropfire_boom_06.ani");
 obj.setCurrentAnimation(DCLAuL0zyiL1S1eIh); 
 local wWNge5FZR9Rw = sq_GetCustomAttackInfo(obj, 1); 
 sq_SetCurrentAttackBonusRate(wWNge5FZR9Rw, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wWNge5FZR9Rw); 
 sq_SetMyShake(obj, 15, 180); 
 if(obj.isMyControlObject())
 sq_flashScreen(obj, 0, 60, 120, 178, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 
 sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/atdropfire/atdropfire_shockwave.ani", ENUM_DRAWLAYER_BOTTOM, true);
 break;
 case 226: 
 local CpL5DiiIFkMlDUxbtl = 0.72; 
 local DCLAuL0zyiL1S1eIh = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/atchaindrive/finish_dust1.ani");
 DCLAuL0zyiL1S1eIh.setImageRateFromOriginal(CpL5DiiIFkMlDUxbtl, CpL5DiiIFkMlDUxbtl); 
 DCLAuL0zyiL1S1eIh.setAutoLayerWorkAnimationAddSizeRate(CpL5DiiIFkMlDUxbtl); 
 sq_SetAttackBoundingBoxSizeRate(DCLAuL0zyiL1S1eIh, CpL5DiiIFkMlDUxbtl, CpL5DiiIFkMlDUxbtl, CpL5DiiIFkMlDUxbtl); 
 obj.setCurrentAnimation(DCLAuL0zyiL1S1eIh); 
 local wWNge5FZR9Rw = sq_GetCustomAttackInfo(obj, 2); 
 sq_SetCurrentAttackBonusRate(wWNge5FZR9Rw, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wWNge5FZR9Rw); 
 sq_CreateParticle("passiveobject/script_sqr_nut_qq506807329/atfighter/particle/atchaindriveexplosion.ptl", obj, 0, 0, 10, true, 5, 0, 5); 
 local ecjs1NhXUIpQHgy = sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/atchaindrive/finish_shock1.ani", ENUM_DRAWLAYER_BOTTOM, true); 
 local Yzi2YFgfKV = ecjs1NhXUIpQHgy.getCurrentAnimation(); 
 Yzi2YFgfKV.setImageRateFromOriginal(CpL5DiiIFkMlDUxbtl, CpL5DiiIFkMlDUxbtl); 
 Yzi2YFgfKV.setAutoLayerWorkAnimationAddSizeRate(CpL5DiiIFkMlDUxbtl); 
 break;
 case 227: 
 local Ow4A3jQtA3oNIOYhPDaM7M = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(Ow4A3jQtA3oNIOYhPDaM7M);
 switch(Ow4A3jQtA3oNIOYhPDaM7M)
 {
 case 1: 
 local DCLAuL0zyiL1S1eIh = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/atruinrain/atruinrainattackbox.ani");
 obj.setCurrentAnimation(DCLAuL0zyiL1S1eIh); 
 obj.getVar().clear_vector(); 
 local W_pcQa0fUEvB = obj.getVar(); 
 for(local OEReO1LNR0GZnBBGDcwP = 0; OEReO1LNR0GZnBBGDcwP < 7; OEReO1LNR0GZnBBGDcwP++)
 W_pcQa0fUEvB.push_vector(receiveData.readDword()); 
 obj.getVar("count").clear_vector(); 
 obj.getVar("count").push_vector(0); 
 obj.getVar("aniobj").clear_obj_vector(); 
 obj.setTimeEvent(0, 50, -1, false); 
 
 obj.getVar().clear_timer_vector();
 obj.getVar().push_timer_vector();
 local mm82S4OXklN7z66MAn7geZ_c = obj.getVar().get_timer_vector(0);
 mm82S4OXklN7z66MAn7geZ_c.setParameter(20, -1); 
 mm82S4OXklN7z66MAn7geZ_c.resetInstant(0); 
 break;
 case 2: 
 local DCLAuL0zyiL1S1eIh = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/atruinrain/bigstone/stonec_stone.ani");
 obj.setCurrentAnimation(DCLAuL0zyiL1S1eIh); 
 local wWNge5FZR9Rw = sq_GetCustomAttackInfo(obj, 4); 
 sq_SetCurrentAttackBonusRate(wWNge5FZR9Rw, receiveData.readDword()); 
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(receiveData.readDword()); 
 sq_SetChangeStatusIntoAttackInfo(wWNge5FZR9Rw, 0, ACTIVESTATUS_BLEEDING, receiveData.readDword(), receiveData.readDword(), receiveData.readDword(), receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wWNge5FZR9Rw); 
 obj.getVar().push_vector(obj.getZPos()); 
 break;
 }
 break;
 case 228: 
 local V3xQWqr7IkUJNbrSK9oLV = obj.getTopCharacter();
 if(V3xQWqr7IkUJNbrSK9oLV)
 V3xQWqr7IkUJNbrSK9oLV.getVar().setBool(0, true); 
 local DCLAuL0zyiL1S1eIh = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/atfireworks/fireworks_end_explosion.ani");
 
 
 sq_ClearAttackBox(DCLAuL0zyiL1S1eIh); 
 sq_AddAttackBox(DCLAuL0zyiL1S1eIh,
 -319, 80, 0
 625, 200, 237); 
 obj.setCurrentAnimation(DCLAuL0zyiL1S1eIh); 
 local wWNge5FZR9Rw = sq_GetCustomAttackInfo(obj, 6); 
 sq_SetCurrentAttackBonusRate(wWNge5FZR9Rw, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wWNge5FZR9Rw); 
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(receiveData.readDword()); 
 
 obj.getVar("atkobj").clear_vector(); 
 local JaWRKdCId3 = obj.getVar("atkobj"); 
 local nNREjjgGjPiOp = receiveData.readDword(); 
 for(local OEReO1LNR0GZnBBGDcwP = 0; OEReO1LNR0GZnBBGDcwP < nNREjjgGjPiOp; OEReO1LNR0GZnBBGDcwP += 2)
 {
 local _9ogCobEoPPZGW95eQ = receiveData.readDword(); 
 local y0tOFHliMZf = receiveData.readDword(); 
 local mdm73YTNm__C_Z7q = sq_GetObject(obj, _9ogCobEoPPZGW95eQ, y0tOFHliMZf); 
 if(mdm73YTNm__C_Z7q)
 {
 local iAAXn1nSkvQz0nACoybyx6 = CNSquirrelAppendage.sq_GetAppendage(mdm73YTNm__C_Z7q, "character/atfighter/fireworks/ap_fireworks.nut"); 
 if(iAAXn1nSkvQz0nACoybyx6)
 {
 
 iAAXn1nSkvQz0nACoybyx6.sq_var.clear_obj_vector(); 
 iAAXn1nSkvQz0nACoybyx6.sq_var.push_obj_vector(obj); 
 
 local RRb70aPXIokJ8TbC = iAAXn1nSkvQz0nACoybyx6.getTimer(); 
 RRb70aPXIokJ8TbC.Reset(); 
 RRb70aPXIokJ8TbC.Start(10000, 0); 
 iAAXn1nSkvQz0nACoybyx6.getVar("state").clear_vector();
 iAAXn1nSkvQz0nACoybyx6.getVar("state").push_vector(2); 
 }
 }
 JaWRKdCId3.push_vector(_9ogCobEoPPZGW95eQ); 
 JaWRKdCId3.push_vector(y0tOFHliMZf); 
 }
 sq_SetMyShake(obj, 5, 300); 
 break;
 case 229: 
 local Ow4A3jQtA3oNIOYhPDaM7M = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(Ow4A3jQtA3oNIOYhPDaM7M);
 switch(Ow4A3jQtA3oNIOYhPDaM7M)
 {
 case 1:
 local wWNge5FZR9Rw = sq_GetCustomAttackInfo(obj, 7); 
 sq_SetCurrentAttackBonusRate(wWNge5FZR9Rw, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wWNge5FZR9Rw); 
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(0); 
 obj.getVar().push_vector(receiveData.readDword()); 
 obj.getVar().push_vector(receiveData.readDword()); 
 obj.getVar().push_vector(receiveData.readDword()); 
 obj.getVar("atkobj").clear_obj_vector(); 
 local V3xQWqr7IkUJNbrSK9oLV = obj.getTopCharacter(); 
 if(V3xQWqr7IkUJNbrSK9oLV)
 {
 local nNREjjgGjPiOp = V3xQWqr7IkUJNbrSK9oLV.getVar("atkobj").get_obj_vector_size(); 
 local CkxCZnwpMSYPX = V3xQWqr7IkUJNbrSK9oLV.getVar("atkobj"); 
 local JaWRKdCId3 = obj.getVar("atkobj"); 
 for(local OEReO1LNR0GZnBBGDcwP = 0; OEReO1LNR0GZnBBGDcwP < nNREjjgGjPiOp; OEReO1LNR0GZnBBGDcwP++)
 {
 local mdm73YTNm__C_Z7q = sq_GetCNRDObjectToActiveObject(CkxCZnwpMSYPX.get_obj_vector(OEReO1LNR0GZnBBGDcwP)); 
 if(mdm73YTNm__C_Z7q)
 {
 if(!mdm73YTNm__C_Z7q.isDead()) 
 {
 if(obj.isMyControlObject())
 sq_SendHitObjectPacket(obj, mdm73YTNm__C_Z7q, 0, 0, 0); 
 sq_AddHitObject(obj, mdm73YTNm__C_Z7q); 
 }
 JaWRKdCId3.push_obj_vector(mdm73YTNm__C_Z7q); 
 }
 }
 }
 local VhLRC3Npgp2sUvWd36PUM3f = obj.getVar().GetparticleCreaterMap("atcyclonecrashgroundcrashloop", "passiveobject/script_sqr_nut_qq506807329/atfighter/particle/atcyclonecrashgroundcrashloop.ptl", obj); 
 VhLRC3Npgp2sUvWd36PUM3f.Restart(0); 
 VhLRC3Npgp2sUvWd36PUM3f.SetPos(obj.getXPos(), obj.getYPos(), obj.getZPos() + 15); 
 sq_AddParticleObject(obj, VhLRC3Npgp2sUvWd36PUM3f); 
 if(obj.isMyControlObject())
 obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, ""); 
 break;
 case 2:
 local CpL5DiiIFkMlDUxbtl = 0.82; 
 local DCLAuL0zyiL1S1eIh = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/atcyclonecrash/grabcannonexplosion/grabcannonhit_02.ani");
 DCLAuL0zyiL1S1eIh.setImageRateFromOriginal(CpL5DiiIFkMlDUxbtl, CpL5DiiIFkMlDUxbtl); 
 DCLAuL0zyiL1S1eIh.setAutoLayerWorkAnimationAddSizeRate(CpL5DiiIFkMlDUxbtl); 
 sq_SetAttackBoundingBoxSizeRate(DCLAuL0zyiL1S1eIh, CpL5DiiIFkMlDUxbtl, CpL5DiiIFkMlDUxbtl, CpL5DiiIFkMlDUxbtl); 
 obj.setCurrentAnimation(DCLAuL0zyiL1S1eIh); 
 local wWNge5FZR9Rw = sq_GetCustomAttackInfo(obj, 10); 
 sq_SetCurrentAttackBonusRate(wWNge5FZR9Rw, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wWNge5FZR9Rw); 
 sq_SetMyShake(obj, 6, 300); 
 if(obj.isMyControlObject())
 sq_flashScreen(obj, 0, 80, 0, 178, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 break;
 }
 break;
 case 230: 
 local Ow4A3jQtA3oNIOYhPDaM7M = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(Ow4A3jQtA3oNIOYhPDaM7M);
 switch(Ow4A3jQtA3oNIOYhPDaM7M)
 {
 case 1:
 sq_SetCurrentAttackInfoFromCustomIndex(obj, 11); 
 if(obj.isMyControlObject())
 obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, ""); 
 break;
 case 2:
 local DCLAuL0zyiL1S1eIh = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/chainbrake/nnfinish_ready_eff.ani");
 obj.setCurrentAnimation(DCLAuL0zyiL1S1eIh); 
 local wWNge5FZR9Rw = sq_GetCustomAttackInfo(obj, 13); 
 sq_SetCurrentAttackBonusRate(wWNge5FZR9Rw, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wWNge5FZR9Rw); 
 break;
 case 3:
 local DCLAuL0zyiL1S1eIh = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/chainbrake/finishefftop_02.ani");
 obj.setCurrentAnimation(DCLAuL0zyiL1S1eIh); 
 local wWNge5FZR9Rw = sq_GetCustomAttackInfo(obj, 12); 
 sq_SetCurrentAttackBonusRate(wWNge5FZR9Rw, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wWNge5FZR9Rw); 
 sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/chainbrake/finisheffbot_03.ani", ENUM_DRAWLAYER_BOTTOM, true); 
 sq_SetMyShake(obj, 5, 160); 
 if(obj.isMyControlObject())
 sq_flashScreen(obj, 40, 160, 400, 204, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 if(receiveData.readBool()) 
 {
 local Ytus_eosiYiLM = obj.getObjectManager(); 
 local B1yWNFw93pol9xUSgxqx5 = Ytus_eosiYiLM.getCollisionObjectNumber(); 
 for(local OEReO1LNR0GZnBBGDcwP = 0; OEReO1LNR0GZnBBGDcwP < B1yWNFw93pol9xUSgxqx5; OEReO1LNR0GZnBBGDcwP++)
 {
 local KYbuGOvYNL = Ytus_eosiYiLM.getCollisionObject(OEReO1LNR0GZnBBGDcwP); 
 if(KYbuGOvYNL
 && obj.isEnemy(KYbuGOvYNL) 
 && KYbuGOvYNL.isInDamagableState(obj)
 && KYbuGOvYNL.isObjectType(OBJECTTYPE_ACTIVE)
 && sq_IsHoldable(obj, KYbuGOvYNL)
 && sq_IsGrabable(obj, KYbuGOvYNL)
 && !sq_IsFixture(KYbuGOvYNL))
 {
 sq_AddHitObject(obj, KYbuGOvYNL); 
 }
 }
 }
 break;
 }
 break;
 case 231: 
 local Ow4A3jQtA3oNIOYhPDaM7M = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(Ow4A3jQtA3oNIOYhPDaM7M);
 switch(Ow4A3jQtA3oNIOYhPDaM7M)
 {
 case 1:
 local wWNge5FZR9Rw = sq_GetCustomAttackInfo(obj, 14); 
 sq_SetCurrentAttackBonusRate(wWNge5FZR9Rw, receiveData.readDword()); 
 obj.getVar("state").clear_vector(); 
 obj.getVar("state").push_vector(2); 
 obj.getVar("speed").clear_vector(); 
 obj.getVar("speed").push_vector(receiveData.readDword()); 
 if(obj.isMyControlObject())
 {
 local ocHyIpxkN5p = sq_GetGlobalIntVector(); 
 sq_IntVectorClear(ocHyIpxkN5p); 
 sq_IntVectorPush(ocHyIpxkN5p, 2); 
 obj.addSetStatePacket(10, ocHyIpxkN5p, STATE_PRIORITY_AUTO, false, ""); 
 }
 break;
 case 2:
 local DCLAuL0zyiL1S1eIh = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/finalextremestrike/e1_blueline.ani");
 obj.setCurrentAnimation(DCLAuL0zyiL1S1eIh); 
 local wWNge5FZR9Rw = sq_GetCustomAttackInfo(obj, 15); 
 sq_SetCurrentAttackBonusRate(wWNge5FZR9Rw, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wWNge5FZR9Rw); 
 sq_SetMyShake(obj, 15, 500); 
 
 if(obj.isMyControlObject())
 {
 sq_flashScreen(obj, 0, 200, 100, 255, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 local b6CJOhpKtAriS8YUaPu6iqU7 = sq_AddDrawOnlyAniFromParent(obj, "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/finalextremestrike/worda_normal1.ani", 0, 0, 190);
 local kZNVMx6jah8IcYx6UKoNfd = sq_AddDrawOnlyAniFromParent(obj, "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/finalextremestrike/wordb_normal1.ani", 0, 0, 220);
 sq_SetCurrentDirection(b6CJOhpKtAriS8YUaPu6iqU7, ENUM_DIRECTION_RIGHT); 
 sq_SetCurrentDirection(kZNVMx6jah8IcYx6UKoNfd, ENUM_DIRECTION_RIGHT); 
 local nOXOehIijF0gvsVuy7LkAv_G = obj.getXPos(); 
 sq_setCurrentAxisPos(b6CJOhpKtAriS8YUaPu6iqU7, 0, sq_GetDistancePos(nOXOehIijF0gvsVuy7LkAv_G, ENUM_DIRECTION_RIGHT, -195)); 
 sq_setCurrentAxisPos(kZNVMx6jah8IcYx6UKoNfd, 0, sq_GetDistancePos(nOXOehIijF0gvsVuy7LkAv_G, ENUM_DIRECTION_RIGHT, 215)); 
 }
 break;
 }
 break;
 default: 
 break;
 }
} ;
 
