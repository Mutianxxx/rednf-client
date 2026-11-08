function procAppend_AllGrowJob(obj)
{
	if(!obj) return;
	if (obj.isDead()) 
	{
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/atpriest/appendage/ap_zealoffaith_friend.nut");
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/atpriest/holylight/ap_holylight.nut");
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/atpriest/edification/ap_edification.nut");
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/atpriest/blessofangel/ap_blessofangel.nut");
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/new_mage/sorceressbuff/ap_sorceressbuff.nut");
	}
	if(!obj.isMyControlObject()) return;
	if(sq_isPVPMode()) return;
	newSkillKeyDown(obj);
}





