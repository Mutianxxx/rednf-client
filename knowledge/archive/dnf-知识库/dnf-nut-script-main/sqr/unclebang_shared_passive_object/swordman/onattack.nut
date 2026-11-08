











function onAttack_po_swordman_shared(obj, damager, boundingBox, isStuck)
{
	if(!obj) return;

	local id = obj.getVar("id").get_vector(0);
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	local parentChr = sq_ObjectToSQRCharacter(obj.getTopCharacter());



	switch(id)
	{
		case 25:
			switch(state)
			{
				case 5:
					local Appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, parentChr, -1, false, "character/swordman/zigadvent/ap_zig_soulcutter.nut", true);
					Appendage.sq_SetValidTime(650);
					if(Appendage)
					{
					}
				break;
			}
		break;
		case 40:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 41:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 42:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 43:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 44:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 45:
			als_ani(damager, "character/swordman/effect/animation/ghostpierce/hit_02.ani", 0, 0, damager.getZPos() + sq_GetCenterZPos(boundingBox), 0, 100, 0, 1, 1.0);
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, parentChr, -1, false, "character/swordman/5_ghostsword/ghostpierce/ap_ghostpierce.nut", true);
		break;
		case 46:
			als_ani(damager, "character/swordman/effect/animation/ghostpierce/hit_02.ani", 0, 0, damager.getZPos() + sq_GetCenterZPos(boundingBox), 0, 100, 0, 1, 1.0);
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, parentChr, -1, false, "character/swordman/5_ghostsword/ghostpierce/ap_ghostpierce.nut", true);
		break;
		case 47:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 48:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 49:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 50:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 51:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 52:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 53:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 54:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 55:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 56:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 57:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
		break;
		case 60:
			//GhostSword_Attack_Effect(obj, damager, boundingBox, isStuck);
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, parentChr, SKILL_TERRIBLEKILLING, false, "character/swordman/5_ghostsword/terriblekilling/ap_terriblekilling.nut", true);
			appendage.sq_SetValidTime(900);
		break;
	}
}



