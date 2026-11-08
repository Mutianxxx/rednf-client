function setCustomData_po_mytestgunner(obj, receiveData)
{
	if(!obj)
		return;

	local id = receiveData.readDword();
	local attackBonusRate = receiveData.readDword();
	local WeaponSubType = receiveData.readDword();
	if(id == 169)
	{
		local x = sq_GetXPos(obj);
		local y = sq_GetYPos(obj);
		local z = sq_GetZPos(obj);
		obj.getVar("pos").clear_vector();
		obj.getVar("pos").push_vector(x);
		obj.getVar("pos").push_vector(y);
		obj.getVar("pos").push_vector(z);
		sq_SetCustomRotate(obj, sq_ToRadian(-23.0));
		local attackInfo = sq_GetCustomAttackInfo(obj, 0);
		if(WeaponSubType == 0)//���
		{
			setCurrentAnimationFromCutomIndex(obj, 0);
			attackInfo = sq_GetCustomAttackInfo(obj, 0);//���䣻����
			obj.sq_SetMoveParticle("Particle/downattackrevolver.ptl", 0.0, -23.0);
			obj.sq_PlaySound("G_MREVOLVERB");
		}
		else if(WeaponSubType == 1)//����
		{
			setCurrentAnimationFromCutomIndex(obj, 0);
			attackInfo = sq_GetCustomAttackInfo(obj, 1);
			obj.sq_SetMoveParticle("Particle/downattackautomatic.ptl", 0.0, -23.0);
			obj.sq_PlaySound("G_SMALLGUNB");

		}
		else if(WeaponSubType == 2)
		{
			setCurrentAnimationFromCutomIndex(obj, 3);
			attackInfo = sq_GetCustomAttackInfo(obj, 4);
			obj.sq_SetMoveParticle("Particle/downattackmusket.ptl", 0.0, -23.0);
			obj.sq_PlaySound("G_MUSKETB");
		}
		else if(WeaponSubType == 3)
		{

			setCurrentAnimationFromCutomIndex(obj, 2);
			attackInfo = sq_GetCustomAttackInfo(obj, 3);
			obj.sq_SetMoveParticle("Particle/downattackhandcannon.ptl", 0.0, -30.0);
  	    		obj.sq_PlaySound("G_HCANNONB");
		}
		else if(WeaponSubType == 4)
		{
			setCurrentAnimationFromCutomIndex(obj, 1);
			attackInfo = sq_GetCustomAttackInfo(obj, 2);
			obj.sq_SetMoveParticle("Particle/downattackbowgun.ptl", 0.0, -23.0);
			obj.sq_PlaySound("G_BOWGUNB");
		}
	
		sq_SetCurrentAttackInfo(obj, attackInfo);
		local pAttack = sq_GetCurrentAttackInfo(obj);		
		sq_SetCurrentAttackBonusRate(pAttack, 0);
		sq_SetCurrentAttackPower(pAttack, 0);
		obj.getVar("atk").clear_vector(); 
		obj.getVar("atk").push_vector(attackBonusRate); 
		obj.getVar("atk").push_vector(WeaponSubType); 
	}
}

function onAttack_po_mytestgunner(obj,damager, boundingBox, isStuck)
{
	if(!obj)
		return 0;
	local parentChr = obj.getTopCharacter();
	if(!damager)
		return 0;
	damager.sq_PlaySound("R_DIFFUSION_GUNA_HIT");
	local WeaponSubType = obj.getVar("atk").get_vector(1);
	local aniPlayer = sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/headshotmonsterup.ani", -10, 0, 0); 
	sq_SetCustomRotate(aniPlayer, -0.349064);
	aniPlayer = sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/headshotdown.ani", 10, 0, 10); 
	sq_SetCustomRotate(aniPlayer, -0.349064);
}

function procAppend_po_mytestgunner(obj)
{
	if(!obj)
		return 0;
	local parentChr = obj.getTopCharacter();
	local WeaponSubType = obj.getVar("atk").get_vector(1);
	local pChr = sq_ObjectToSQRCharacter(parentChr);
	if(WeaponSubType == 0)//���
	{
		setbackstepheadshotatk(pChr,22002);
	}
	else if(WeaponSubType == 1)//����
	{
		setbackstepheadshotatk(pChr,22005);
	}
	else if(WeaponSubType == 2)//����
	{
		setbackstepheadshotatk(pChr,22008);
	}
	else if(WeaponSubType == 3)//�?
	{
		setbackstepheadshotatk(pChr,22011);
	}
	else if(WeaponSubType == 4)//���
	{
		setbackstepheadshotatk(pChr,22014);
	}
}

function setbackstepheadshotatk(obj,index)
{
	if(!obj) return;
	local Count = obj.getMyPassiveObjectCount(index);
	for(local i=0;i<Count;++i)
	{
		local object = obj.getMyPassiveObject(index, i);
		if(object)
		{
			local attackBonusRate = obj.sq_GetBonusRateWithPassive(5, -1, 0, 1.0);
			local attackInfo = sq_GetCurrentAttackInfo(object);
			sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		}
	}
}
