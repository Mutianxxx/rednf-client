function setCustomData_po_qq506807329new_mage_24372(obj, receiveData) {
	if (!obj) return;
	sq_IntVectorClear(sq_GetGlobalIntVector());
	local qGHQHL0tRsTnm = receiveData.readDword();
	obj.getVar("skill").clear_vector();
	obj.getVar("skill").push_vector(qGHQHL0tRsTnm);
	switch (qGHQHL0tRsTnm) {
	case 242:

		sq_SetCurrentAttackBonusRate(sq_GetCustomAttackInfo(obj, 0), receiveData.readDword());
		obj.getVar().clear_vector();
		obj.getVar().push_vector(receiveData.readDword());
		obj.setTimeEvent(0, receiveData.readDword(), 1, false);
		if (obj.isMyControlObject()) obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
		break;
	case 245:
		local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 1);
		sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
		sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);
		obj.getVar().clear_vector();
		obj.getVar().push_vector(receiveData.readDword());
		local Cq5TQagvAzlc484 = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/mage/animation/avatar/avatarfinish_star_b.ani");
		Cq5TQagvAzlc484.setSpeedRate(receiveData.readFloat());
		obj.setCurrentAnimation(Cq5TQagvAzlc484);
		obj.getVar().clear_obj_vector();
		obj.getVar("aniobj").clear_obj_vector();
		break;
	case 247:
		local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 2);
		sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
		sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);
		local Cq5TQagvAzlc484 = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/mage/animation/quasarexplosion/qcexpa_exp_00.ani");
		obj.setCurrentAnimation(Cq5TQagvAzlc484);
		break;
	case 249:
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
		local XQnYRgQWQWRi6J = receiveData.readDword();
		local Cq5TQagvAzlc484 = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/mage/animation/elementalcurtain/elementalcurtain_groundcircle.ani");
		local N1rcKLgw8_j1w = XQnYRgQWQWRi6J.tofloat() / 100.0;
		Cq5TQagvAzlc484.setImageRateFromOriginal(N1rcKLgw8_j1w, N1rcKLgw8_j1w);
		Cq5TQagvAzlc484.setAutoLayerWorkAnimationAddSizeRate(N1rcKLgw8_j1w);
		sq_SetAttackBoundingBoxSizeRate(Cq5TQagvAzlc484, N1rcKLgw8_j1w, N1rcKLgw8_j1w, N1rcKLgw8_j1w);
		obj.setCurrentAnimation(Cq5TQagvAzlc484);
		local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 3);
		sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
		sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);

		sq_SetCurrentAttackBonusRate(sq_GetCustomAttackInfo(obj, 4), receiveData.readDword());

		obj.setTimeEvent(0, receiveData.readDword(), 0, false);
		obj.getVar().clear_vector();
		obj.getVar().push_vector(XQnYRgQWQWRi6J);
		obj.getVar().push_vector(receiveData.readDword());

		local hfzYnU3jrqLJmA9MpbZtle42 = sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/mage/animation/elementalcurtain/elementalcurtain_aurorabehind_aurora1.ani", ENUM_DRAWLAYER_NORMAL, true);
		local xAlHKXXfXQ1OxlANSXNrtFV = hfzYnU3jrqLJmA9MpbZtle42.getCurrentAnimation();
		xAlHKXXfXQ1OxlANSXNrtFV.addLayerAnimation(1, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/mage/animation/elementalcurtain/elementalcurtain_aurora.ani"), true);
		xAlHKXXfXQ1OxlANSXNrtFV.setImageRateFromOriginal(N1rcKLgw8_j1w, N1rcKLgw8_j1w);
		xAlHKXXfXQ1OxlANSXNrtFV.setAutoLayerWorkAnimationAddSizeRate(N1rcKLgw8_j1w);

		local bGWkCc5ojS9V = sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/mage/animation/elementalcurtain/elementalcurtain_aurorafront_sky1.ani", ENUM_DRAWLAYER_NORMAL, true);
		sq_setCurrentAxisPos(bGWkCc5ojS9V, 1, obj.getYPos() - 1);
		local UfuNzYq8uJ58uOp7JUE = (330.0 * N1rcKLgw8_j1w).tointeger();
		sq_setCurrentAxisPos(bGWkCc5ojS9V, 2, UfuNzYq8uJ58uOp7JUE);
		local ff2ozlgxPiPoGd9bOuS7D = bGWkCc5ojS9V.getCurrentAnimation();
		ff2ozlgxPiPoGd9bOuS7D.setImageRateFromOriginal(N1rcKLgw8_j1w, N1rcKLgw8_j1w);
		ff2ozlgxPiPoGd9bOuS7D.setAutoLayerWorkAnimationAddSizeRate(N1rcKLgw8_j1w);
		obj.getVar("aniobj").clear_obj_vector();
		obj.getVar("aniobj").push_obj_vector(hfzYnU3jrqLJmA9MpbZtle42);
		obj.getVar("aniobj").push_obj_vector(bGWkCc5ojS9V);
		break;
	case 250:
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
		local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 5);
		sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
		sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);
		obj.getVar().clear_vector();
		obj.getVar().push_vector(receiveData.readDword());
		obj.getVar().push_vector(receiveData.readDword());
		obj.getVar().clear_obj_vector();
		if (obj.isMyControlObject()) obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
		break;
	case 105:
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
		local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 23);
		sq_SetCurrentAttackPower(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
		//sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
		sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);
		local parentChr = obj.getTopCharacter();
		local skilllevel = sq_GetSkillLevel(parentChr, 105);
		local prob = sq_GetLevelData(parentChr, 105, 6, skilllevel);
		local level = sq_GetLevelData(parentChr, 105, 7, skilllevel);
		local duration = sq_GetLevelData(parentChr, 105, 8, skilllevel);
		local lightDamage = sq_GetLevelData(parentChr, 105, 9, skilllevel);
		local attackInfo = sq_GetCurrentAttackInfo(obj, 0);
		if (!attackInfo) return;
		sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, ACTIVESTATUS_LIGHTNING, prob.tointeger(), level, duration, lightDamage);
		obj.setTimeEvent(0, 400, 400, false);
		//obj.setTimeEvent(0,400,400,false);
		obj.getVar().clear_vector();
		obj.getVar().push_vector(receiveData.readDword());
		obj.getVar().push_vector(receiveData.readDword());
		obj.getVar().clear_obj_vector();
		if (obj.isMyControlObject()) obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
		break;
	case 251:
		obj.getVar().clear_vector();
		obj.getVar().push_vector(receiveData.readDword());
		local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 6);
		sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
		sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);
		if (obj.isMyControlObject()) obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
		break;
	case 252:
		local Vc0rw5FwGWIbIYDT1X = receiveData.readDword();
		obj.getVar("subType").clear_vector();
		obj.getVar("subType").push_vector(Vc0rw5FwGWIbIYDT1X);
		switch (Vc0rw5FwGWIbIYDT1X) {
		case 1:
			local DDSK6TeLANSy0 = sq_GetCNRDObjectToActiveObject(sq_GetObject(obj, receiveData.readDword(), receiveData.readDword()));
			if (DDSK6TeLANSy0 && !DDSK6TeLANSy0.isDead()) {
				obj.setCurrentPos(DDSK6TeLANSy0.getXPos(), DDSK6TeLANSy0.getYPos(), DDSK6TeLANSy0.getZPos() + sq_GetObjectHeight(DDSK6TeLANSy0) + 120);
				sq_moveWithParent(DDSK6TeLANSy0, obj);
			}
			obj.getVar().clear_vector();
			local wq2983twpeU_Zol1ILTmU = obj.getVar();
			wq2983twpeU_Zol1ILTmU.push_vector(receiveData.readWord());
			wq2983twpeU_Zol1ILTmU.push_vector(receiveData.readDword());
			wq2983twpeU_Zol1ILTmU.push_vector(receiveData.readDword());
			wq2983twpeU_Zol1ILTmU.push_vector(receiveData.readDword());
			if (obj.isMyControlObject()) obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
			break;
		case 2:
			obj.setDirection(receiveData.readWord());
			local oYXm_t3r2dUDYxPcXLMmz = receiveData.readWord();
			local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 7);
			L9vHkUd1313at9pgcW2TS2pg.setElement(oYXm_t3r2dUDYxPcXLMmz);
			sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
			sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);
			local tqaa6TNowMF = receiveData.readFloat();
			obj.sq_SetMoveParticle("particle/thegate_move.ptl", 0.0, tqaa6TNowMF);
			local uaEzFG6HsB9StUjxsu = ["fire/fire_crystal.ani", "ice/ice_crystal.ani", "dark/dark_crystal.ani", "light/light_crystal.ani"];
			local Cq5TQagvAzlc484 = sq_CreateAnimation("passiveobject/script_sqr_nut_qq506807329/mage/animation/thegate/", uaEzFG6HsB9StUjxsu[oYXm_t3r2dUDYxPcXLMmz]);
			obj.setCurrentAnimation(Cq5TQagvAzlc484);
			local MCgClSBeD80m6ktzNVTMRU = ["thegatefiretail.ptl", "thegateicetail.ptl", "thegatedarktail.ptl", "thegatelighttail.ptl"];

			sq_CreateParticle("passiveobject/script_sqr_nut_qq506807329/mage/particle/" + MCgClSBeD80m6ktzNVTMRU[oYXm_t3r2dUDYxPcXLMmz], obj, 0, 0, 0, true, 80, 0, 15);
			obj.getVar().setBool(0, false);
			obj.getVar().clear_vector();
			obj.getVar().push_vector(oYXm_t3r2dUDYxPcXLMmz);
			break;
		}
		break;
	case 253:
		local Cq5TQagvAzlc484 = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/mage/animation/sestoelemento/start_main.ani");
		obj.setCurrentAnimation(Cq5TQagvAzlc484);
		local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 8);
		sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
		sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);

		sq_SetCurrentAttackBonusRate(sq_GetCustomAttackInfo(obj, 9), receiveData.readDword());
		local LKiDWPPPfb7 = receiveData.readDword() - 1;
		if (LKiDWPPPfb7 < 1) LKiDWPPPfb7 = 1;
		local uL0OKpoVKfl = Cq5TQagvAzlc484.getDelaySum(0, 1);
		obj.setTimeEvent(0, uL0OKpoVKfl / LKiDWPPPfb7, 0, false);
		obj.getVar().clear_vector();
		obj.getVar().push_vector(receiveData.readDword());
		obj.sq_PlaySound("SESTOELEMENTO");
		if (obj.isMyControlObject()) {
			local M88jvV8sNFCHNEINcoEV = sq_flashScreen(obj, 300, 99990, 0, 255, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
			obj.getVar("flashobj").clear_obj_vector();
			obj.getVar("flashobj").push_obj_vector(M88jvV8sNFCHNEINcoEV);
		}
		break;
	case 131:
		obj.getVar().clear_vector();
		obj.getVar().push_vector(receiveData.readDword());
		local pOdiiaMqIt = receiveData.readDword();
		local xQFzWprkgF7aBeAt = receiveData.readDword();
		local kjmSbYGkD8yE9winlkf = receiveData.readDword();
		local dfe4wnu4fj5b5fJuUOKV_1 = receiveData.readDword();
		local oNHyWJFxSfjgNrxQ_gP3d3 = receiveData.readDword();
		local EFd0LSWkJem27doUtWVa = sq_GetCustomAttackInfo(obj, 10);
		local P_Z3e7LnuMl6 = sq_GetCustomAttackInfo(obj, 11);
		sq_SetCurrentAttackBonusRate(EFd0LSWkJem27doUtWVa, pOdiiaMqIt);
		sq_SetCurrentAttackBonusRate(P_Z3e7LnuMl6, xQFzWprkgF7aBeAt);
		sq_SetChangeStatusIntoAttackInfo(EFd0LSWkJem27doUtWVa, 0, ACTIVESTATUS_LIGHTNING, kjmSbYGkD8yE9winlkf, 100, oNHyWJFxSfjgNrxQ_gP3d3, dfe4wnu4fj5b5fJuUOKV_1);
		sq_SetChangeStatusIntoAttackInfo(P_Z3e7LnuMl6, 0, ACTIVESTATUS_LIGHTNING, kjmSbYGkD8yE9winlkf, 100, oNHyWJFxSfjgNrxQ_gP3d3, dfe4wnu4fj5b5fJuUOKV_1);
		if (obj.isMyControlObject()) obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
		break;
	case 133:
		local gzyJCAqVWwgqd = receiveData.readDword();
		local SPxzkPmZGxBUE = receiveData.readDword();
		local L9vHkUd1313at9pgcW2TS2pg = null;
		if (gzyJCAqVWwgqd == 1) {
			L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 13);
			sq_SetChangeStatusIntoAttackInfo(L9vHkUd1313at9pgcW2TS2pg, 0, ACTIVESTATUS_LIGHTNING, receiveData.readDword(), 100, receiveData.readDword(), receiveData.readDword());
		}
		else {
			L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 12);
			sq_SetChangeStatusIntoAttackInfo(L9vHkUd1313at9pgcW2TS2pg, 0, ACTIVESTATUS_BLIND, receiveData.readDword(), receiveData.readDword(), receiveData.readDword(), 50, receiveData.readDword());
		}
		sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, SPxzkPmZGxBUE);
		sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);
		obj.getVar().clear_vector();
		obj.getVar().push_vector(gzyJCAqVWwgqd);
		if (obj.isMyControlObject()) obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
		break;
	case 134:
		local Vc0rw5FwGWIbIYDT1X = receiveData.readDword();
		obj.getVar("subType").clear_vector();
		obj.getVar("subType").push_vector(Vc0rw5FwGWIbIYDT1X);
		switch (Vc0rw5FwGWIbIYDT1X) {
		case 1:
			local w2Nitc8Zo5FumsGM = receiveData.readDword();
			local uaEzFG6HsB9StUjxsu = ["Fire_Dodge.ani", "Ice_Dodge.ani", "Dark_Dodge.ani", "Light_Dodge.ani"];
			local Cq5TQagvAzlc484 = sq_CreateAnimation("passiveobject/script_sqr_nut_qq506807329/mage/animation/uroboros/explosion_", uaEzFG6HsB9StUjxsu[w2Nitc8Zo5FumsGM]);
			obj.setCurrentAnimation(Cq5TQagvAzlc484);
			local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 14);
			sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
			L9vHkUd1313at9pgcW2TS2pg.setElement(w2Nitc8Zo5FumsGM);
			sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);
			obj.sq_PlaySound("R_UROBOROS_SPARK_EXP");
			break;
		case 2:
			local Cq5TQagvAzlc484 = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/mage/animation/uroboros/explosion_dodge.ani");
			obj.setCurrentAnimation(Cq5TQagvAzlc484);
			local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 15);
			sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
			sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);
			sq_CreateParticle("passiveobject/script_sqr_nut_qq506807329/mage/particle/uroborossub.ptl", obj, 0, 0, 20, false, 5, 0, 1);
			break;
		}
		break;
	case 132:
		local Vc0rw5FwGWIbIYDT1X = receiveData.readDword();
		obj.getVar("subType").clear_vector();
		obj.getVar("subType").push_vector(Vc0rw5FwGWIbIYDT1X);
		switch (Vc0rw5FwGWIbIYDT1X) {
		case 1:
			local bkWPRBYFFTuBXa5eiDRjr = sq_GetCNRDObjectToCollisionObject(obj.getTopCharacter());
			if (bkWPRBYFFTuBXa5eiDRjr) {
				bkWPRBYFFTuBXa5eiDRjr.getVar().clear_obj_vector();
				bkWPRBYFFTuBXa5eiDRjr.getVar().push_obj_vector(obj);
			}
			local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 17);
			sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
			sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);

			sq_SetCurrentAttackBonusRate(sq_GetCustomAttackInfo(obj, 18), receiveData.readDword());
			obj.getVar().clear_vector();
			local wq2983twpeU_Zol1ILTmU = obj.getVar();
			wq2983twpeU_Zol1ILTmU.push_vector(receiveData.readDword());
			wq2983twpeU_Zol1ILTmU.push_vector(receiveData.readDword());
			wq2983twpeU_Zol1ILTmU.push_vector(receiveData.readDword());
			break;
		case 2:
			local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 16);
			sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
			sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);
			break;
		}
		if (obj.isMyControlObject()) obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
		break;
	case 135:
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
		local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 19);
		sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
		sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);
		obj.getVar().clear_vector();
		local wq2983twpeU_Zol1ILTmU = obj.getVar();
		wq2983twpeU_Zol1ILTmU.push_vector(receiveData.readDword());
		wq2983twpeU_Zol1ILTmU.push_vector(receiveData.readDword());
		if (obj.isMyControlObject()) obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
		obj.getVar("subType").clear_vector();
		obj.getVar("subType").push_vector(0);
		break;
	case 136:
		local Vc0rw5FwGWIbIYDT1X = receiveData.readDword();
		obj.getVar("subType").clear_vector();
		obj.getVar("subType").push_vector(Vc0rw5FwGWIbIYDT1X);
		switch (Vc0rw5FwGWIbIYDT1X) {
		case 1:
			obj.setTimeEvent(0, 1000, 1, false);
			break;
		case 2:
			local Cq5TQagvAzlc484 = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/mage/animation/kruta/ragefinisheff_01.ani");
			obj.setCurrentAnimation(Cq5TQagvAzlc484);
			local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 20);
			sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
			sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);
			sq_CreateDrawOnlyObject(obj, "monster/character/mage/kruta/animation/ragefinishfloor_f01.ani", ENUM_DRAWLAYER_BOTTOM, true);
			break;
		}
		break;
	case 139:
		local Vc0rw5FwGWIbIYDT1X = receiveData.readDword();
		obj.getVar("subType").clear_vector();
		obj.getVar("subType").push_vector(Vc0rw5FwGWIbIYDT1X);
		switch (Vc0rw5FwGWIbIYDT1X) {
		case 1:
			obj.getVar().clear_vector();
			obj.getVar().push_vector(obj.getXPos());
			obj.getVar().push_vector(receiveData.readDword());
			if (obj.isMyControlObject()) obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
			break;
		case 2:
			obj.setDirection(receiveData.readWord());
			obj.setTimeEvent(0, 1000, 1, false);
			break;
		case 3:
			local L9vHkUd1313at9pgcW2TS2pg = sq_GetCustomAttackInfo(obj, 21);
			sq_SetCurrentAttackBonusRate(L9vHkUd1313at9pgcW2TS2pg, receiveData.readDword());
			sq_SetCurrentAttackInfo(obj, L9vHkUd1313at9pgcW2TS2pg);

			sq_SetCurrentAttackBonusRate(sq_GetCustomAttackInfo(obj, 22), receiveData.readDword());
			obj.getVar().clear_vector();
			obj.getVar().push_vector(receiveData.readDword());
			if (obj.isMyControlObject()) obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
			break;
		}
		break;
	case 138:
		local Vc0rw5FwGWIbIYDT1X = receiveData.readDword();
		obj.getVar("subType").clear_vector();
		obj.getVar("subType").push_vector(Vc0rw5FwGWIbIYDT1X);
		switch (Vc0rw5FwGWIbIYDT1X) {
		case 1:
			obj.setTimeEvent(0, 1000, 1, false);
			break;
		}
		break;
	default:
		break;
	}
};