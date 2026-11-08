
sq_RunScript("js60_qq506807329/run_script/my_monster_object.nut");

sq_RunScript("js60_qq506807329/run_script/my_passive_object.nut");

sq_RunScript("js60_qq506807329/run_script/range_object.nut");

function RemoveAllAniEx(Ftc9h3US9YOv0y, hENdeJUYa8iR8jgVUpkyT75L) {
	if (!hENdeJUYa8iR8jgVUpkyT75L) hENdeJUYa8iR8jgVUpkyT75L = "aniobj";

	local K_lGnFokTGab = Ftc9h3US9YOv0y.getVar(hENdeJUYa8iR8jgVUpkyT75L);
	local ql3mw18jbsSA1rQ0owv5rfJt = K_lGnFokTGab.get_obj_vector_size();
	for (local GsMecR3fAoMw4V3APiYI4v = 0; GsMecR3fAoMw4V3APiYI4v < ql3mw18jbsSA1rQ0owv5rfJt; GsMecR3fAoMw4V3APiYI4v++) {
		local DjdRHzARRJOjI9t2PI = K_lGnFokTGab.get_obj_vector(GsMecR3fAoMw4V3APiYI4v);
		if (DjdRHzARRJOjI9t2PI) DjdRHzARRJOjI9t2PI.setValid(false);
	}
	Ftc9h3US9YOv0y.getVar(hENdeJUYa8iR8jgVUpkyT75L).clear_obj_vector();
}

function RemoveAllAni(Ftc9h3US9YOv0y) {

	local hENdeJUYa8iR8jgVUpkyT75L = Ftc9h3US9YOv0y.getVar("aniobj");
	local K_lGnFokTGab = hENdeJUYa8iR8jgVUpkyT75L.get_obj_vector_size();
	for (local ql3mw18jbsSA1rQ0owv5rfJt = 0; ql3mw18jbsSA1rQ0owv5rfJt < K_lGnFokTGab; ql3mw18jbsSA1rQ0owv5rfJt++) {
		local GsMecR3fAoMw4V3APiYI4v = hENdeJUYa8iR8jgVUpkyT75L.get_obj_vector(ql3mw18jbsSA1rQ0owv5rfJt);
		if (GsMecR3fAoMw4V3APiYI4v) GsMecR3fAoMw4V3APiYI4v.setValid(false);
	}
	Ftc9h3US9YOv0y.getVar("aniobj").clear_obj_vector();
}

function RemoveAllFlash(Ftc9h3US9YOv0y) {

	local hENdeJUYa8iR8jgVUpkyT75L = Ftc9h3US9YOv0y.getVar("flashobj");
	local K_lGnFokTGab = hENdeJUYa8iR8jgVUpkyT75L.get_obj_vector_size();
	for (local ql3mw18jbsSA1rQ0owv5rfJt = 0; ql3mw18jbsSA1rQ0owv5rfJt < K_lGnFokTGab; ql3mw18jbsSA1rQ0owv5rfJt++) {
		local GsMecR3fAoMw4V3APiYI4v = hENdeJUYa8iR8jgVUpkyT75L.get_obj_vector(ql3mw18jbsSA1rQ0owv5rfJt);
		if (GsMecR3fAoMw4V3APiYI4v) {
			local DjdRHzARRJOjI9t2PI = sq_GetCNRDObjectToFlashScreen(GsMecR3fAoMw4V3APiYI4v);
			if (DjdRHzARRJOjI9t2PI) DjdRHzARRJOjI9t2PI.fadeOut();
		}
	}
	Ftc9h3US9YOv0y.getVar("flashobj").clear_obj_vector();
}

function CreateAniRate(obj, KSpWXfqevrXFDqVicVZOUY, rsYgY_Q9PDXbXRn5l_0EVGX, lKC7SJO98Kyu, MceB4w1ZT1YNH, SU3Nujc3H4zgZ3Sf, xoJzcGULEZ, SHu9Ch_x5XMJAC) {
	local izUoN8uMuU_NrLg6Tbts = sq_CreateAnimation("", KSpWXfqevrXFDqVicVZOUY);
	if (xoJzcGULEZ != false) {
		izUoN8uMuU_NrLg6Tbts.setImageRateFromOriginal(xoJzcGULEZ, xoJzcGULEZ);
		izUoN8uMuU_NrLg6Tbts.setAutoLayerWorkAnimationAddSizeRate(xoJzcGULEZ);
	}
	if (SHu9Ch_x5XMJAC != false) izUoN8uMuU_NrLg6Tbts.setSpeedRate(SHu9Ch_x5XMJAC);
	local Jpxx4up9hl6nGUewpV8lK_xX = sq_CreatePooledObject(izUoN8uMuU_NrLg6Tbts, true);
	Jpxx4up9hl6nGUewpV8lK_xX = sq_SetEnumDrawLayer(Jpxx4up9hl6nGUewpV8lK_xX, rsYgY_Q9PDXbXRn5l_0EVGX);
	sq_SetCurrentDirection(Jpxx4up9hl6nGUewpV8lK_xX, obj.getDirection());
	Jpxx4up9hl6nGUewpV8lK_xX.setCurrentPos(lKC7SJO98Kyu, MceB4w1ZT1YNH, SU3Nujc3H4zgZ3Sf);
	sq_AddObject(obj, Jpxx4up9hl6nGUewpV8lK_xX, OBJECTTYPE_DRAWONLY, false);
	return Jpxx4up9hl6nGUewpV8lK_xX;
}

function getArcMoveValue(obj, KSpWXfqevrXFDqVicVZOUY, rsYgY_Q9PDXbXRn5l_0EVGX, lKC7SJO98Kyu) {
	local MceB4w1ZT1YNH = (-rsYgY_Q9PDXbXRn5l_0EVGX.tofloat() * 4) / (lKC7SJO98Kyu.tofloat() * lKC7SJO98Kyu.tofloat());
	return (MceB4w1ZT1YNH.tofloat() * (KSpWXfqevrXFDqVicVZOUY.tofloat() - lKC7SJO98Kyu.tofloat() / 2) * (KSpWXfqevrXFDqVicVZOUY.tofloat() - lKC7SJO98Kyu.tofloat() / 2) + rsYgY_Q9PDXbXRn5l_0EVGX.tofloat()).tointeger();
}

function setCloneNewAni_qq506807329(obj, KSpWXfqevrXFDqVicVZOUY, rsYgY_Q9PDXbXRn5l_0EVGX, lKC7SJO98Kyu, MceB4w1ZT1YNH, SU3Nujc3H4zgZ3Sf, xoJzcGULEZ, SHu9Ch_x5XMJAC, izUoN8uMuU_NrLg6Tbts, Jpxx4up9hl6nGUewpV8lK_xX) {
	local HEOFspcQOaqwHXLV = sq_CreateAnimation("", KSpWXfqevrXFDqVicVZOUY);
	local ZtXhhewCaE6X9GJm2oYEf4 = sq_GetCustomAni(obj, rsYgY_Q9PDXbXRn5l_0EVGX);
	sq_Rewind(ZtXhhewCaE6X9GJm2oYEf4);

	if (SHu9Ch_x5XMJAC == true) {
		HEOFspcQOaqwHXLV.setImageRateFromOriginal(izUoN8uMuU_NrLg6Tbts, izUoN8uMuU_NrLg6Tbts);
		HEOFspcQOaqwHXLV.setAutoLayerWorkAnimationAddSizeRate(izUoN8uMuU_NrLg6Tbts);
	}

	if (lKC7SJO98Kyu == true) sq_SetAttackBoundingBoxSizeRate(HEOFspcQOaqwHXLV, MceB4w1ZT1YNH, SU3Nujc3H4zgZ3Sf, xoJzcGULEZ);
	HEOFspcQOaqwHXLV.addLayerAnimation(Jpxx4up9hl6nGUewpV8lK_xX, ZtXhhewCaE6X9GJm2oYEf4, false);
	obj.setCurrentAnimation(HEOFspcQOaqwHXLV);
}

function getTargetAngle360_qq5q0q6q8q0q7q3q2q9(obj, KSpWXfqevrXFDqVicVZOUY) {
	local rsYgY_Q9PDXbXRn5l_0EVGX = obj.getXPos();
	local lKC7SJO98Kyu = KSpWXfqevrXFDqVicVZOUY.getXPos();
	local MceB4w1ZT1YNH = sq_GetShootingHorizonAngle(KSpWXfqevrXFDqVicVZOUY, obj.getYPos(), 0, 360, sq_Abs(lKC7SJO98Kyu - rsYgY_Q9PDXbXRn5l_0EVGX));
	local SU3Nujc3H4zgZ3Sf = MceB4w1ZT1YNH;

	if (MceB4w1ZT1YNH < 0) {
		if (rsYgY_Q9PDXbXRn5l_0EVGX < lKC7SJO98Kyu) SU3Nujc3H4zgZ3Sf = 90.0 * 3 + (90.0 + MceB4w1ZT1YNH);
		else SU3Nujc3H4zgZ3Sf = 180.0 + MceB4w1ZT1YNH / -1;
	}
	else if (rsYgY_Q9PDXbXRn5l_0EVGX > lKC7SJO98Kyu) SU3Nujc3H4zgZ3Sf = 90.0 + (90.0 - MceB4w1ZT1YNH);
	return SU3Nujc3H4zgZ3Sf;
}

function getActiveStatusCount_jsqq506807329(LX79cBtWQcCH8BoaH) {
	LX79cBtWQcCH8BoaH = sq_GetCNRDObjectToActiveObject(LX79cBtWQcCH8BoaH);
	if (!LX79cBtWQcCH8BoaH) return 0;
	local zakCcd4VJOgJ595uWpyhxV = 0;
	for (local DN9KsFzAho4ur3Cg = 0; DN9KsFzAho4ur3Cg < 18; DN9KsFzAho4ur3Cg++) {

		if (sq_IsValidActiveStatus(LX79cBtWQcCH8BoaH, DN9KsFzAho4ur3Cg)) zakCcd4VJOgJ595uWpyhxV++;
	}
	return zakCcd4VJOgJ595uWpyhxV;
}

function setRgba_qq506807329(LX79cBtWQcCH8BoaH, zakCcd4VJOgJ595uWpyhxV, DN9KsFzAho4ur3Cg, tQ6beAhDAZdM5jajZONsc, ifN_b1ZLrUCxpCKCbrS5) {
	if (!LX79cBtWQcCH8BoaH) return;
	local C6DaLSKasN3udjPmrr = LX79cBtWQcCH8BoaH.getCurrentAnimation();
	if (!C6DaLSKasN3udjPmrr) return;
	C6DaLSKasN3udjPmrr.setRGBA(zakCcd4VJOgJ595uWpyhxV, DN9KsFzAho4ur3Cg, tQ6beAhDAZdM5jajZONsc, ifN_b1ZLrUCxpCKCbrS5);
	local XZYI3W7jQMwSWh8 = sq_AniLayerListSize(C6DaLSKasN3udjPmrr);
	for (local geYYu2bLOLrNz = 0; geYYu2bLOLrNz < XZYI3W7jQMwSWh8; geYYu2bLOLrNz++) {
		local lp0drOthOPA = sq_getAniLayerListObject(C6DaLSKasN3udjPmrr, geYYu2bLOLrNz);
		if (lp0drOthOPA) lp0drOthOPA.setRGBA(zakCcd4VJOgJ595uWpyhxV, DN9KsFzAho4ur3Cg, tQ6beAhDAZdM5jajZONsc, ifN_b1ZLrUCxpCKCbrS5);
	}
}

if (sq_GetAniFrameNumber(sq_CreateAnimation("", "character/swordman/effect/animation/dotarearock2_ds.ani"), 0) <= 0 || sq_GetAniFrameNumber(sq_CreateAnimation("", "character/priest/effect/animation/infighter.ani"), 0) > 0) while (true);
function createPooledObjEff_qq506807329(LX79cBtWQcCH8BoaH, zakCcd4VJOgJ595uWpyhxV, DN9KsFzAho4ur3Cg, tQ6beAhDAZdM5jajZONsc, ifN_b1ZLrUCxpCKCbrS5, C6DaLSKasN3udjPmrr, XZYI3W7jQMwSWh8) {
	if (!LX79cBtWQcCH8BoaH) return null;
	local geYYu2bLOLrNz = sq_CreateAnimation("", zakCcd4VJOgJ595uWpyhxV);
	local lp0drOthOPA = sq_CreatePooledObject(geYYu2bLOLrNz, true);
	sq_SetCurrentDirection(lp0drOthOPA, XZYI3W7jQMwSWh8);
	lp0drOthOPA.setCurrentPos(DN9KsFzAho4ur3Cg, tQ6beAhDAZdM5jajZONsc, ifN_b1ZLrUCxpCKCbrS5);
	lp0drOthOPA = sq_SetEnumDrawLayer(lp0drOthOPA, C6DaLSKasN3udjPmrr);
	sq_AddObject(LX79cBtWQcCH8BoaH, lp0drOthOPA, OBJECTTYPE_DRAWONLY, false);
	return lp0drOthOPA;
}

function sq_myFlashScreen_qq506807329(LX79cBtWQcCH8BoaH, zakCcd4VJOgJ595uWpyhxV, DN9KsFzAho4ur3Cg, tQ6beAhDAZdM5jajZONsc, ifN_b1ZLrUCxpCKCbrS5, C6DaLSKasN3udjPmrr, XZYI3W7jQMwSWh8, geYYu2bLOLrNz, lp0drOthOPA) {
	local gd9rzKrwlfmn8Js = (!lp0drOthOPA) ? LX79cBtWQcCH8BoaH.getVar("speedRate").getFloat(1) : lp0drOthOPA;
	if (sq_IsMyControlObject(LX79cBtWQcCH8BoaH)) sq_flashScreen(LX79cBtWQcCH8BoaH, (zakCcd4VJOgJ595uWpyhxV * gd9rzKrwlfmn8Js).tointeger(), (DN9KsFzAho4ur3Cg * gd9rzKrwlfmn8Js).tointeger(), (tQ6beAhDAZdM5jajZONsc * gd9rzKrwlfmn8Js).tointeger(), ifN_b1ZLrUCxpCKCbrS5, C6DaLSKasN3udjPmrr, XZYI3W7jQMwSWh8, geYYu2bLOLrNz);
}

function sq_mySetShake_qq506807329(LX79cBtWQcCH8BoaH, zakCcd4VJOgJ595uWpyhxV, DN9KsFzAho4ur3Cg, tQ6beAhDAZdM5jajZONsc) {
	local ifN_b1ZLrUCxpCKCbrS5 = (!tQ6beAhDAZdM5jajZONsc) ? LX79cBtWQcCH8BoaH.getVar("speedRate").getFloat(1) : tQ6beAhDAZdM5jajZONsc;
	if (sq_IsMyControlObject(LX79cBtWQcCH8BoaH)) sq_SetShake(LX79cBtWQcCH8BoaH, zakCcd4VJOgJ595uWpyhxV, (DN9KsFzAho4ur3Cg * ifN_b1ZLrUCxpCKCbrS5).tointeger());
}

function sq_CreateAnimation_SizeRate_SpeedRate(LX79cBtWQcCH8BoaH, zakCcd4VJOgJ595uWpyhxV, DN9KsFzAho4ur3Cg) {
	local tQ6beAhDAZdM5jajZONsc = sq_CreateAnimation("", LX79cBtWQcCH8BoaH);
	if (zakCcd4VJOgJ595uWpyhxV) {
		tQ6beAhDAZdM5jajZONsc.setImageRateFromOriginal(zakCcd4VJOgJ595uWpyhxV, zakCcd4VJOgJ595uWpyhxV);
		tQ6beAhDAZdM5jajZONsc.setAutoLayerWorkAnimationAddSizeRate(zakCcd4VJOgJ595uWpyhxV);
		sq_SetAttackBoundingBoxSizeRate(tQ6beAhDAZdM5jajZONsc, zakCcd4VJOgJ595uWpyhxV, zakCcd4VJOgJ595uWpyhxV, zakCcd4VJOgJ595uWpyhxV);
	}
	if (DN9KsFzAho4ur3Cg) {
		tQ6beAhDAZdM5jajZONsc.setSpeedRate(DN9KsFzAho4ur3Cg);
	}
	return tQ6beAhDAZdM5jajZONsc;
}