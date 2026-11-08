function setCustomData_po_bloodcastle_dogs(obj, receiveData)
{
	if(!obj)
		return;

	local attackBonusRate = receiveData.readDword();// ?????(%)	
    local dirtion = receiveData.readDword();
    local ID = receiveData.readDword();
    local parentX = receiveData.readDword();
    local parentY = receiveData.readDword();
    local size = receiveData.readDword();

    local blood = receiveData.readDword();
    obj.getVar("locate").clear_vector();
    obj.getVar("locate").push_vector(parentX);
    obj.getVar("locate").push_vector(parentY);

    obj.getVar("dama").clear_obj_vector();

    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);

    obj.getVar("blood").clear_vector();
    obj.getVar("blood").push_vector(blood);
    
    obj.getVar().clear_vector();
    obj.getVar().push_vector(0);

    if (dirtion == -1) 
    {
        obj.setCurrentDirection(ENUM_DIRECTION_LEFT);
    }else{
        obj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
    }
    local ani = obj.getCustomAnimation( ID % 3);
	obj.setCurrentAnimation(ani);


    local currentAni = sq_GetCurrentAnimation(obj);
    local sizeRate = size.tofloat()/100.0;
    currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
    currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
    sq_SetAttackBoundingBoxSizeRate(currentAni, sizeRate, sizeRate, sizeRate);

	local attackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

    attackInfo = sq_GetCurrentAttackInfo(obj);
    sq_SetCurrentAttackeHitStunTime(attackInfo, 0);


}
function onAttack_po_bloodcastle_dogs(obj,damager, boundingBox, isStuck)
{
//    setCustomHitEffectBloodMageCut(obj,damager,0);


    local mage = obj.getTopCharacter();
    mage = sq_ObjectToSQRCharacter(mage);	
    damager = sq_GetCNRDObjectToActiveObject(damager);

    if (mage && damager && !damager.isDead() && !CNSquirrelAppendage.sq_IsAppendAppendage(damager, 
        "character/atmage/append_bloodmage/ap_bloodcastle.nut") )
    {
        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, mage, SKILL_BLOODCASTLE, false, 
        "character/atmage/append_bloodmage/ap_bloodcastle.nut", true);				 

    }else{

        return ;
    }

    if ( obj.getVar("flag").get_vector(0) == 0 )
    {
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(1);


            

        if (!CNSquirrelAppendage.sq_IsAppendAppendage(mage, "character/atmage/append_bloodmage/ap_bloodcastle_character.nut"))
        {
            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(mage, mage, SKILL_BLOODCASTLE, false, 
            "character/atmage/append_bloodmage/ap_bloodcastle_character.nut", true);				 
        }


//       setBloodValue(obj,obj.getVar("blood").get_vector(0) );
        
    }
}
function procAppend_po_bloodcastle_dogs(obj)
{
    local pAni = obj.getCurrentAnimation();
    local frmIndex = sq_GetAnimationFrameIndex(pAni);
    if (frmIndex >= 5 && obj.getVar().get_vector(0) == 0)
    {
        obj.getVar().set_vector(0,1);

        sq_SetMyShake(obj,1,10);
    }
    
}