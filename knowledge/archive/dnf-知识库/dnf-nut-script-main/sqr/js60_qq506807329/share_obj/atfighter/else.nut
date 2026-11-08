function onAttack_po_qq506807329new_atfighter_24375(obj, damager, boundingBox, isStuck) {
	if (!obj || !damager) return 0;
	local skillIndex = obj.getVar("skill").get_vector(0);
	switch (skillIndex) {
		case 22:
			if (!obj || isStuck)
				break;
			local parentChr = obj.getTopCharacter();
			parentChr = sq_GetCNRDObjectToSQRCharacter(parentChr);
			if (!parentChr)
				break;
			local append = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
			local appendage = CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, append);
			if (!appendage)
				break;
			local skill_level = sq_GetSkillLevel(parentChr, SKILL_SPIRALGALEFORCE);
			local levelDataA = parentChr.sq_GetLevelData(SKILL_SPIRALGALEFORCE, 1, skill_level) / 1000.0;
			local damagerXPos = damager.getXPos();
			local damagerYPos = damager.getYPos();
			local damagerZPos = sq_GetCenterZPos(boundingBox);
			parentChr.sq_StartWrite();
			parentChr.sq_WriteDword(117);
			parentChr.sq_WriteDword(parentChr.sq_GetBonusRateWithPassive(251, -1, 0, levelDataA) + parentChr.sq_GetBonusRateWithPassive(251, -1, 1, levelDataA));
			parentChr.sq_WriteBool(sq_IsGrabable(damager, parentChr));
			sq_SendCreatePassiveObjectPacketPos(parentChr, 24375, 0, damagerXPos, damagerYPos + 1, damagerZPos);
			break;
		case 231:
			local A2bXpDFwjEE = obj.getVar("subType").get_vector(0);
			switch (A2bXpDFwjEE) {
				case 1:
					if (isStuck || !damager.isObjectType(OBJECTTYPE_ACTIVE)) break;
					local DZoRl1CMsq = obj.getXPos();
					local l6THarWHXdhxiQ0EpWNN = obj.getYPos();
					local yTM22gx2PyFvpwFY = sq_GetXPos(damager);
					local bNJFPTah03khWgfeiylUDoJ6 = sq_GetYPos(damager);
					local p6EMNgrBd8_9Yf0TT1a3R = obj.getDirection();
					local Zha2Bs_wq8O = -20;
					local EbPj2Urzty = -3;
					if (DZoRl1CMsq < yTM22gx2PyFvpwFY) Zha2Bs_wq8O = sq_Abs(DZoRl1CMsq - yTM22gx2PyFvpwFY) + Zha2Bs_wq8O;
					else Zha2Bs_wq8O = (sq_Abs(DZoRl1CMsq - yTM22gx2PyFvpwFY) + Zha2Bs_wq8O) / -1;
					if (l6THarWHXdhxiQ0EpWNN < bNJFPTah03khWgfeiylUDoJ6) EbPj2Urzty = sq_Abs(l6THarWHXdhxiQ0EpWNN - bNJFPTah03khWgfeiylUDoJ6) + EbPj2Urzty;
					else EbPj2Urzty = (sq_Abs(l6THarWHXdhxiQ0EpWNN - bNJFPTah03khWgfeiylUDoJ6) + EbPj2Urzty) / -1;
					if (p6EMNgrBd8_9Yf0TT1a3R == ENUM_DIRECTION_LEFT) {
						Zha2Bs_wq8O = Zha2Bs_wq8O / -1;
						EbPj2Urzty = EbPj2Urzty / -1;
					}

					if (CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atfighter/finalextremestrike/ap_finalextremestrike_move.nut")) CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atfighter/finalextremestrike/ap_finalextremestrike_move.nut");
					local eELl18uc382yeTC = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 231, false, "character/atfighter/finalextremestrike/ap_finalextremestrike_move.nut", true);
					eELl18uc382yeTC.sq_SetValidTime(70);
					sq_MoveToAppendage(damager, obj, obj, Zha2Bs_wq8O, EbPj2Urzty, 0, 70, true, eELl18uc382yeTC);
					break;
			}
			break;
	}
};

function onKeyFrameFlag_po_qq506807329new_atfighter_24375(obj, vYLqjywITECXyUw1) {
	if (!obj) return false;
	local aeuBP7YV_yNKhy = obj.getVar("skill").get_vector(0);
	switch (aeuBP7YV_yNKhy) {
	case 228:
		switch (vYLqjywITECXyUw1) {
		case 2:
		case 3:
		case 4:
		case 5:
			if (vYLqjywITECXyUw1 == 3) {
				local D88uNX2g9JGeMlrXn = sq_GetCurrentAttackInfo(obj);
				sq_SetCurrentAttackBonusRate(D88uNX2g9JGeMlrXn, obj.getVar().get_vector(0));
			}
			else if (vYLqjywITECXyUw1 == 5) {
				local D88uNX2g9JGeMlrXn = sq_GetCurrentAttackInfo(obj);
				sq_SetCurrentAttacknUpForce(D88uNX2g9JGeMlrXn, 130);
			}
			obj.resetHitObjectList();
			break;
		case 6:
			sq_SetMyShake(obj, 3, 500);
			break;
		case 7:
			local Ltdgq6bC3f9H6 = obj.getVar("atkobj").size_vector();
			local VCIxDshD5V2 = obj.getVar("atkobj");
			for (local PkPSUEgCMmKQi7fR1 = 0; PkPSUEgCMmKQi7fR1 < Ltdgq6bC3f9H6; PkPSUEgCMmKQi7fR1 += 2) {
				local oY7dGEbATYH49ksIj5epObkw = sq_GetObject(obj, VCIxDshD5V2.get_vector(PkPSUEgCMmKQi7fR1), VCIxDshD5V2.get_vector(PkPSUEgCMmKQi7fR1 + 1));
				if (!oY7dGEbATYH49ksIj5epObkw) continue;
				if (CNSquirrelAppendage.sq_IsAppendAppendage(oY7dGEbATYH49ksIj5epObkw, "character/atfighter/fireworks/ap_fireworks.nut")) CNSquirrelAppendage.sq_RemoveAppendage(oY7dGEbATYH49ksIj5epObkw, "character/atfighter/fireworks/ap_fireworks.nut");
			}
			break;
		}
		break;
	case 230:
		local l46eYNDS9Dgd = obj.getVar("subType").get_vector(0);
		switch (l46eYNDS9Dgd) {
		case 3:
			if (vYLqjywITECXyUw1 == 1) sq_SetMyShake(obj, 2, 160);
			break;
		}
		break;
	}
	return true;
};

function onTimeEvent_po_qq506807329new_atfighter_24375(iQ30byZ0uepv5rLGok7s, VLR_BxOVtU3cH_jI, LACQH4kJryZYhczuitPj) {
	if (!iQ30byZ0uepv5rLGok7s) return;
	local YDw51bu1ir = iQ30byZ0uepv5rLGok7s.getVar("skill").get_vector(0);
	switch (YDw51bu1ir) {
	case 227:
		if (VLR_BxOVtU3cH_jI == 0) {

			local yQWfkL6FeqPyHiHq = ["stonea01_stone.ani", "stonea02_stone.ani", "stoneb01_stone.ani", "stoneb02_stone.ani"];
			local dbDOoOyMAcFnwGB2kn = sq_getRandom(0, yQWfkL6FeqPyHiHq.len() - 1);
			local C6Hj7VtKLbdGrdIFAlAHLd = 0;
			if (dbDOoOyMAcFnwGB2kn > 1) C6Hj7VtKLbdGrdIFAlAHLd = 1;
			local Sdpy0dFegPMixj7R = iQ30byZ0uepv5rLGok7s.getXPos() + sq_getRandom(-180, 180);
			local rLflfIQwc1eQIAMnI63HU = iQ30byZ0uepv5rLGok7s.getYPos() + sq_getRandom(-50, 50);
			while (Sdpy0dFegPMixj7R % 2 != C6Hj7VtKLbdGrdIFAlAHLd)
			Sdpy0dFegPMixj7R += 1;
			local m5aN4t5rdEGNA = sq_CreateDrawOnlyObject(iQ30byZ0uepv5rLGok7s, "passiveobject/script_sqr_nut_qq506807329/atfighter/animation/atruinrain/smallstone/" + yQWfkL6FeqPyHiHq[dbDOoOyMAcFnwGB2kn], ENUM_DRAWLAYER_NORMAL, false);
			m5aN4t5rdEGNA.setCurrentPos(Sdpy0dFegPMixj7R, rLflfIQwc1eQIAMnI63HU, 600);
			iQ30byZ0uepv5rLGok7s.getVar("aniobj").push_obj_vector(m5aN4t5rdEGNA);
			if (!iQ30byZ0uepv5rLGok7s.getVar("aniobj").getBool(0)) iQ30byZ0uepv5rLGok7s.getVar("aniobj").setBool(0, true);
		}
		break;
	case 117:
	case 16:
		if (VLR_BxOVtU3cH_jI == 0) {
			local Path = "passiveobject/chang_qing_skill/atfighter/animation/atspiralgaleforce/forcem_end_15.ani";
			createAnimationPooledEx(iQ30byZ0uepv5rLGok7s, Path, 1, true, iQ30byZ0uepv5rLGok7s.getXPos(), iQ30byZ0uepv5rLGok7s.getYPos(), iQ30byZ0uepv5rLGok7s.getZPos(), false);
		}
		else if (VLR_BxOVtU3cH_jI == 1) sq_SendDestroyPacketPassiveObject(iQ30byZ0uepv5rLGok7s);
		else if (VLR_BxOVtU3cH_jI == 2) destroyObjectByVar(iQ30byZ0uepv5rLGok7s, "Pooledobj");
		else if (VLR_BxOVtU3cH_jI == 3) {
			iQ30byZ0uepv5rLGok7s.resetHitObjectList();
		}
		break;
	case 120:
		if (VLR_BxOVtU3cH_jI == 0) {
			local Path = "passiveobject/chang_qing_skill/atfighter/animation/atspiralgaleforce/forcem_end_15.ani";
			createAnimationPooledEx(iQ30byZ0uepv5rLGok7s, Path, 1, true, iQ30byZ0uepv5rLGok7s.getXPos(), iQ30byZ0uepv5rLGok7s.getYPos(), iQ30byZ0uepv5rLGok7s.getZPos(), false);
		}
		else if (VLR_BxOVtU3cH_jI == 1) sq_SendDestroyPacketPassiveObject(iQ30byZ0uepv5rLGok7s);
		else if (VLR_BxOVtU3cH_jI == 2) destroyObjectByVar(iQ30byZ0uepv5rLGok7s, "Pooledobj");
		break;
	}
};

function onDestroyObject_po_qq506807329new_atfighter_24375(R4yDTMhLFu1JXOy7WJ, k7l66TJFK0DR5Z3TKVodu4q) {
	if (!R4yDTMhLFu1JXOy7WJ) return;
	local _TVlOLgqhbuk5N98F = R4yDTMhLFu1JXOy7WJ.getVar("skill").get_vector(0);
	switch (_TVlOLgqhbuk5N98F) {
	case 227:
		break;
	}
};

function destroy_po_qq506807329new_atfighter_24375(fyY_R8kKI2vJrCtJvi7z2qU) {
	if (!fyY_R8kKI2vJrCtJvi7z2qU) return;
	local BWIuXUJviTs6J1knvaah = fyY_R8kKI2vJrCtJvi7z2qU.getVar("skill").get_vector(0);
	switch (BWIuXUJviTs6J1knvaah) {
	case 227:
		local xOiMug1FzL5m_41lqB0eM = fyY_R8kKI2vJrCtJvi7z2qU.getVar("subType").get_vector(0);
		if (xOiMug1FzL5m_41lqB0eM == 1) RemoveAllAni(fyY_R8kKI2vJrCtJvi7z2qU);
		break;
	case 229:
		break;
	}
};

function onDestroyObject_po_qq506807329new_atfighter_24375(fyY_R8kKI2vJrCtJvi7z2qU, BWIuXUJviTs6J1knvaah) {
	if (!fyY_R8kKI2vJrCtJvi7z2qU) return;
	local xOiMug1FzL5m_41lqB0eM = fyY_R8kKI2vJrCtJvi7z2qU.getVar("skill").get_vector(0);
	switch (xOiMug1FzL5m_41lqB0eM) {
	case 231:
		local Tm80xJQBPJiVmZjoTi = fyY_R8kKI2vJrCtJvi7z2qU.getVar("subType").get_vector(0);
		if (Tm80xJQBPJiVmZjoTi != 1) return;
		if (isSameObject(fyY_R8kKI2vJrCtJvi7z2qU, BWIuXUJviTs6J1knvaah)) {
			local DHDynJNh5dfprAH7OKyXee = sq_ObjectToSQRCharacter(fyY_R8kKI2vJrCtJvi7z2qU.getTopCharacter());
			if (DHDynJNh5dfprAH7OKyXee && DHDynJNh5dfprAH7OKyXee.getState() == 231 && DHDynJNh5dfprAH7OKyXee.sq_IsMyControlObject()) {

				local iyi4c91ZpPgiAGaQq = null;
				local vxWdb3wADOkggRvoR = DHDynJNh5dfprAH7OKyXee.getVar().get_obj_vector_size();
				if (vxWdb3wADOkggRvoR > 0) {
					local gDlu3x3QHz = DHDynJNh5dfprAH7OKyXee.getVar();
					local jgu5fSPVDPr = 80;
					local HfakCsDSlqpph4qj7oByPYk = DHDynJNh5dfprAH7OKyXee.getXPos();
					local op0LGfLi2ZIZA2 = DHDynJNh5dfprAH7OKyXee.getYPos();
					local f2PR94BUpWoG = 0;
					for (local HMq7V_iEaCN4p2ivf = 0; HMq7V_iEaCN4p2ivf < vxWdb3wADOkggRvoR; HMq7V_iEaCN4p2ivf++) {
						local A59Ie01pyrROuc = gDlu3x3QHz.get_obj_vector(HMq7V_iEaCN4p2ivf);
						if (A59Ie01pyrROuc && sq_GetDistance(HfakCsDSlqpph4qj7oByPYk, op0LGfLi2ZIZA2, sq_GetXPos(A59Ie01pyrROuc), sq_GetYPos(A59Ie01pyrROuc), true) <= jgu5fSPVDPr && sq_GetZPos(A59Ie01pyrROuc) <= 110) {
							local xx4PmNSSbV8SmK2UqC = sq_GetCNRDObjectToActiveObject(A59Ie01pyrROuc);
							if (!xx4PmNSSbV8SmK2UqC) continue;
							local UPa6F96RA3MRTk = xx4PmNSSbV8SmK2UqC.getHp();
							if (UPa6F96RA3MRTk > f2PR94BUpWoG) {
								f2PR94BUpWoG = UPa6F96RA3MRTk;
								iyi4c91ZpPgiAGaQq = A59Ie01pyrROuc;
							}
						}
					}
				}
				DHDynJNh5dfprAH7OKyXee.sq_IntVectClear();
				DHDynJNh5dfprAH7OKyXee.sq_IntVectPush(6);
				if (iyi4c91ZpPgiAGaQq != null) {
					DHDynJNh5dfprAH7OKyXee.sq_IntVectPush(sq_GetGroup(iyi4c91ZpPgiAGaQq));
					DHDynJNh5dfprAH7OKyXee.sq_IntVectPush(sq_GetUniqueId(iyi4c91ZpPgiAGaQq));
				}
				DHDynJNh5dfprAH7OKyXee.sq_AddSetStatePacket(231, STATE_PRIORITY_USER, true);
			}
		}
		break;
	}
};

function onChangeSkillEffect_po_qq506807329new_atfighter_24375(w6IrIe0Y1Ue8UGQQ, RaOQ67iq0HyS1rjl3f2, t7RQrTe8fkLePmwdLZV_j3) {
	if (!w6IrIe0Y1Ue8UGQQ) return;
	switch (RaOQ67iq0HyS1rjl3f2) {
	case 231:
		break;
	}
};

function getCustomHitEffectFileName_po_qq506807329new_atfighter_24375(w6IrIe0Y1Ue8UGQQ, RaOQ67iq0HyS1rjl3f2) {
	if (!w6IrIe0Y1Ue8UGQQ) return "";
	local t7RQrTe8fkLePmwdLZV_j3 = w6IrIe0Y1Ue8UGQQ.getVar("skill").get_vector(0);
};