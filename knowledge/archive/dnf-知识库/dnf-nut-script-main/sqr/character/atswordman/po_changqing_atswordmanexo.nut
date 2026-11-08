
function setCustomData_po_ChangQing_751675335_ATSwordmanexo(obj, CQrZv4CjXxMizMeM)
{
if(!obj) return;
local CQCPVze1kOtqhIeCpV = CQrZv4CjXxMizMeM.readDword();
local CQcyWtkFD68e9hw = sq_ObjectToSQRCharacter(obj.getTopCharacter());
obj.getVar("skill").clear_vector();
obj.getVar("skill").push_vector(CQCPVze1kOtqhIeCpV);
switch(CQCPVze1kOtqhIeCpV)
{
case -1:
local CQAn8D1n8lsYjAwNV = CQrZv4CjXxMizMeM.readDword();
switch(CQAn8D1n8lsYjAwNV)
{
case 0:

break;
}
break;
case 232:
local CQAn8D1n8lsYjAwNV = CQrZv4CjXxMizMeM.readDword();
switch(CQAn8D1n8lsYjAwNV)
{
case 0:
local CQy5zTWBM4F55Bq2 = CQrZv4CjXxMizMeM.readDword();
local CQNXLelycmvCfwqBxV = CQrZv4CjXxMizMeM.readDword();
obj.getVar().clear_vector();
obj.getVar().push_vector(CQNXLelycmvCfwqBxV);

local CQbAQAKYspCD6Rm = sq_GetCustomAttackInfo(obj, 4);
sq_SetAddWeaponDamage(CQbAQAKYspCD6Rm,true);
sq_SetCurrentAttackPower(CQbAQAKYspCD6Rm, CQy5zTWBM4F55Bq2);
sq_SetCurrentAttackInfo(obj, CQbAQAKYspCD6Rm);
obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, "");
break;
case 1:
local CQFuLNo8g1wE1OU1Q = CQrZv4CjXxMizMeM.readDword();
obj.getVar().clear_vector();
obj.getVar().push_vector(CQFuLNo8g1wE1OU1Q);
obj.addSetStatePacket(11, null, STATE_PRIORITY_AUTO, false, "");
break;
}
break;
case 241:
local CQAn8D1n8lsYjAwNV = CQrZv4CjXxMizMeM.readDword();
switch(CQAn8D1n8lsYjAwNV)
{
case 0:
local CQy5zTWBM4F55Bq2 = CQrZv4CjXxMizMeM.readDword();
setCurrentAnimationFromCutomIndex(obj,11);
local CQbAQAKYspCD6Rm = sq_GetCustomAttackInfo(obj, 8);
sq_SetAddWeaponDamage(CQbAQAKYspCD6Rm,true);
sq_SetCurrentAttackPower(CQbAQAKYspCD6Rm, CQy5zTWBM4F55Bq2);
sq_SetCurrentAttackInfo(obj, CQbAQAKYspCD6Rm);
break;
}
break;
case 240:
local CQAn8D1n8lsYjAwNV = CQrZv4CjXxMizMeM.readDword();
switch(CQAn8D1n8lsYjAwNV)
{
case 0:
local CQy5zTWBM4F55Bq2 = CQrZv4CjXxMizMeM.readDword();
local CQNXLelycmvCfwqBxV = CQrZv4CjXxMizMeM.readDword();
local CQvd7ZJkRjcrbJnj85 = 500/CQNXLelycmvCfwqBxV;
obj.setTimeEvent(0,CQvd7ZJkRjcrbJnj85,CQNXLelycmvCfwqBxV,true);
setCurrentAnimationFromCutomIndex(obj,10);
local CQbAQAKYspCD6Rm = sq_GetCustomAttackInfo(obj, 11);
sq_SetAddWeaponDamage(CQbAQAKYspCD6Rm,true);
sq_SetCurrentAttackPower(CQbAQAKYspCD6Rm, CQy5zTWBM4F55Bq2);
sq_SetCurrentAttackInfo(obj, CQbAQAKYspCD6Rm);
obj.sq_SetMoveParticle("particle/stri.ptl", 0.0, 0.0);
sq_SetSpeedToMoveParticle(obj, 0, 1800);
obj.setTimeEvent(1,1000,1,false);
break;
}
break;
case 244:
local CQAn8D1n8lsYjAwNV = CQrZv4CjXxMizMeM.readDword();
switch(CQAn8D1n8lsYjAwNV)
{
case 0:
local CQy5zTWBM4F55Bq2 = CQrZv4CjXxMizMeM.readDword();
setCurrentAnimationFromCutomIndex(obj,12);
local CQbAQAKYspCD6Rm = sq_GetCustomAttackInfo(obj, 9);
sq_SetAddWeaponDamage(CQbAQAKYspCD6Rm,true);
sq_SetCurrentAttackPower(CQbAQAKYspCD6Rm, CQy5zTWBM4F55Bq2);
sq_SetCurrentAttackInfo(obj, CQbAQAKYspCD6Rm);
break;
}
break;
case 249:
local CQAn8D1n8lsYjAwNV = CQrZv4CjXxMizMeM.readDword();
switch(CQAn8D1n8lsYjAwNV)
{
case 0:
local CQy5zTWBM4F55Bq2 = CQrZv4CjXxMizMeM.readDword();
local CQNXLelycmvCfwqBxV = CQrZv4CjXxMizMeM.readDword();
local CQvd7ZJkRjcrbJnj85 = 500/CQNXLelycmvCfwqBxV;
obj.setTimeEvent(0,CQvd7ZJkRjcrbJnj85,CQNXLelycmvCfwqBxV,true);
setCurrentAnimationFromCutomIndex(obj,14);
local CQbAQAKYspCD6Rm = sq_GetCustomAttackInfo(obj, 11);
sq_SetAddWeaponDamage(CQbAQAKYspCD6Rm,true);
sq_SetCurrentAttackPower(CQbAQAKYspCD6Rm, CQy5zTWBM4F55Bq2);
sq_SetCurrentAttackInfo(obj, CQbAQAKYspCD6Rm);
break;
}
break;
case 235:
local CQAn8D1n8lsYjAwNV = CQrZv4CjXxMizMeM.readDword();
switch(CQAn8D1n8lsYjAwNV)
{
case 0:
local CQy5zTWBM4F55Bq2 = CQrZv4CjXxMizMeM.readDword();
setCurrentAnimationFromCutomIndex(obj,7);
local CQbAQAKYspCD6Rm = sq_GetCustomAttackInfo(obj, 6);
sq_SetAddWeaponDamage(CQbAQAKYspCD6Rm,true);
sq_SetCurrentAttackPower(CQbAQAKYspCD6Rm, CQy5zTWBM4F55Bq2);
sq_SetCurrentAttackInfo(obj, CQbAQAKYspCD6Rm);
break;
}
break;
case 238:
local CQAn8D1n8lsYjAwNV = CQrZv4CjXxMizMeM.readDword();
obj.getVar("ObjType").clear_vector();
obj.getVar("ObjType").push_vector(CQAn8D1n8lsYjAwNV);
switch(CQAn8D1n8lsYjAwNV)
{
case 0:
obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, "");
break;
case 1:
local CQy5zTWBM4F55Bq2 = CQrZv4CjXxMizMeM.readDword();
local CQovUkIZRx1IwQtr3 = obj.getCustomAnimation(8);
local CQ2gHeTwWIytnM = 0.8;
CQovUkIZRx1IwQtr3.setImageRateFromOriginal(CQ2gHeTwWIytnM, CQ2gHeTwWIytnM);
CQovUkIZRx1IwQtr3.setAutoLayerWorkAnimationAddSizeRate(CQ2gHeTwWIytnM);
sq_SetAttackBoundingBoxSizeRate(CQovUkIZRx1IwQtr3, CQ2gHeTwWIytnM, CQ2gHeTwWIytnM, CQ2gHeTwWIytnM);
obj.setCurrentAnimation(CQovUkIZRx1IwQtr3);
local CQbAQAKYspCD6Rm = sq_GetCustomAttackInfo(obj, 7);
sq_SetAddWeaponDamage(CQbAQAKYspCD6Rm,true);
sq_SetCurrentAttackPower(CQbAQAKYspCD6Rm, CQy5zTWBM4F55Bq2);
sq_SetCurrentAttackInfo(obj, CQbAQAKYspCD6Rm);
local CQJL1ND4nQITUhrekc = "passiveobject/changqing_atswordman/animation/athangover/attack_front_00.ani";
CreatePooledObjectAni(obj,CQJL1ND4nQITUhrekc,1,obj.getXPos(), obj.getYPos(), 0,obj.getDirection(),false,true,false,false);
break;
}
break;
case 230:
local CQAn8D1n8lsYjAwNV = CQrZv4CjXxMizMeM.readDword();
switch(CQAn8D1n8lsYjAwNV)
{
case 0:
local CQy5zTWBM4F55Bq2 = CQrZv4CjXxMizMeM.readDword();
local CQNXLelycmvCfwqBxV = CQrZv4CjXxMizMeM.readDword();
local CQovUkIZRx1IwQtr3 = obj.getCustomAnimation(1);
obj.setCurrentAnimation(CQovUkIZRx1IwQtr3);
local CQO4VfbiQ1ePv1E = CQovUkIZRx1IwQtr3.getDelaySum(false);
local CQvd7ZJkRjcrbJnj85 = 420/CQNXLelycmvCfwqBxV;
obj.setTimeEvent(0,CQvd7ZJkRjcrbJnj85,CQNXLelycmvCfwqBxV,true);

local CQbAQAKYspCD6Rm = sq_GetCustomAttackInfo(obj, 3);
sq_SetAddWeaponDamage(CQbAQAKYspCD6Rm,true);
sq_SetCurrentAttackPower(CQbAQAKYspCD6Rm, CQy5zTWBM4F55Bq2);
sq_SetCurrentAttackInfo(obj, CQbAQAKYspCD6Rm);
break;
}
break;
case 229:
local CQAn8D1n8lsYjAwNV = CQrZv4CjXxMizMeM.readDword();
switch(CQAn8D1n8lsYjAwNV)
{
case 0:
local CQy5zTWBM4F55Bq2 = CQrZv4CjXxMizMeM.readDword();
local CQFuLNo8g1wE1OU1Q = CQrZv4CjXxMizMeM.readDword();
local CQLFnJK973FAEo = CQrZv4CjXxMizMeM.readDword();
obj.getVar().clear_vector();
obj.getVar().push_vector(CQFuLNo8g1wE1OU1Q);
obj.getVar().push_vector(CQLFnJK973FAEo);

local CQbAQAKYspCD6Rm = sq_GetCustomAttackInfo(obj, 2);
sq_SetAddWeaponDamage(CQbAQAKYspCD6Rm,true);
sq_SetCurrentAttackPower(CQbAQAKYspCD6Rm, CQy5zTWBM4F55Bq2);
sq_SetCurrentAttackInfo(obj, CQbAQAKYspCD6Rm);
obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, "");
break;
}
break;
case 233:
local CQAn8D1n8lsYjAwNV = CQrZv4CjXxMizMeM.readDword();
switch(CQAn8D1n8lsYjAwNV)
{
case 0:
local CQy5zTWBM4F55Bq2 = CQrZv4CjXxMizMeM.readDword();
setCurrentAnimationFromCutomIndex(obj,6);
local CQbAQAKYspCD6Rm = sq_GetCustomAttackInfo(obj, 5);
sq_SetAddWeaponDamage(CQbAQAKYspCD6Rm,true);
sq_SetCurrentAttackPower(CQbAQAKYspCD6Rm, CQy5zTWBM4F55Bq2);
sq_SetCurrentAttackInfo(obj, CQbAQAKYspCD6Rm);
break;
}
break;
case 247:
local CQAn8D1n8lsYjAwNV = CQrZv4CjXxMizMeM.readDword();
switch(CQAn8D1n8lsYjAwNV)
{
case 0:
local CQy5zTWBM4F55Bq2 = CQrZv4CjXxMizMeM.readDword();
setCurrentAnimationFromCutomIndex(obj,13);
local CQbAQAKYspCD6Rm = sq_GetCustomAttackInfo(obj, 10);
sq_SetAddWeaponDamage(CQbAQAKYspCD6Rm,true);
sq_SetCurrentAttackPower(CQbAQAKYspCD6Rm, CQy5zTWBM4F55Bq2);
sq_SetCurrentAttackInfo(obj, CQbAQAKYspCD6Rm);
break;
}
break;
case 243:
local CQAn8D1n8lsYjAwNV = CQrZv4CjXxMizMeM.readDword();
switch(CQAn8D1n8lsYjAwNV)
{
case 0:
local CQovUkIZRx1IwQtr3 = obj.getCustomAnimation(5);
obj.setCurrentAnimation(CQovUkIZRx1IwQtr3);
local CQTEBg823bQpNlEXS = CQcyWtkFD68e9hw.getVar("Rustynail").getObject(0);
if(CQTEBg823bQpNlEXS)
{
CQTEBg823bQpNlEXS = sq_GetCNRDObjectToActiveObject(CQTEBg823bQpNlEXS);
procRustynail(obj,CQTEBg823bQpNlEXS);
}
break;
}
break;
case 91:
local CQAn8D1n8lsYjAwNV = CQrZv4CjXxMizMeM.readDword();
switch(CQAn8D1n8lsYjAwNV)
{
case 0:
local CQy5zTWBM4F55Bq2 = CQrZv4CjXxMizMeM.readDword();
local CQzdtXgRkYdgP2pZN = CQrZv4CjXxMizMeM.readDword();
local CQOM8dBNuPO5Hto1 = CQrZv4CjXxMizMeM.readDword();
local CQ8HOnOu78lCAkiVl9 = CQrZv4CjXxMizMeM.readDword();
local CQWazpQYqxJDaDD = sq_GetSkillLevel(CQcyWtkFD68e9hw, 174);
setCurrentAnimationFromCutomIndex(obj,15)
local CQbAQAKYspCD6Rm = sq_GetCustomAttackInfo(obj, 12);
sq_SetCurrentAttackPower(CQbAQAKYspCD6Rm, CQy5zTWBM4F55Bq2);
sq_SetChangeStatusIntoAttackInfo(CQbAQAKYspCD6Rm, 0, 11, CQOM8dBNuPO5Hto1, CQWazpQYqxJDaDD, CQ8HOnOu78lCAkiVl9,CQzdtXgRkYdgP2pZN);
sq_SetCurrentAttackInfo(obj, CQbAQAKYspCD6Rm);
break;
case 1:
local CQy5zTWBM4F55Bq2 = CQrZv4CjXxMizMeM.readDword();
local CQzdtXgRkYdgP2pZN = CQrZv4CjXxMizMeM.readDword();
local CQOM8dBNuPO5Hto1 = CQrZv4CjXxMizMeM.readDword();
local CQ8HOnOu78lCAkiVl9 = CQrZv4CjXxMizMeM.readDword();
local CQWazpQYqxJDaDD = sq_GetSkillLevel(CQcyWtkFD68e9hw, 174);
setCurrentAnimationFromCutomIndex(obj,16)
local CQbAQAKYspCD6Rm = sq_GetCustomAttackInfo(obj, 13);
sq_SetCurrentAttackPower(CQbAQAKYspCD6Rm, CQy5zTWBM4F55Bq2);
sq_SetChangeStatusIntoAttackInfo(CQbAQAKYspCD6Rm, 0, 11, CQOM8dBNuPO5Hto1, CQWazpQYqxJDaDD, CQ8HOnOu78lCAkiVl9,CQzdtXgRkYdgP2pZN);
sq_SetCurrentAttackInfo(obj, CQbAQAKYspCD6Rm);
break;
case 2:
local CQy5zTWBM4F55Bq2 = CQrZv4CjXxMizMeM.readDword();
local CQzdtXgRkYdgP2pZN = CQrZv4CjXxMizMeM.readDword();
local CQOM8dBNuPO5Hto1 = CQrZv4CjXxMizMeM.readDword();
local CQ8HOnOu78lCAkiVl9 = CQrZv4CjXxMizMeM.readDword();
local CQWazpQYqxJDaDD = sq_GetSkillLevel(CQcyWtkFD68e9hw, 174);
setCurrentAnimationFromCutomIndex(obj,17)
local CQbAQAKYspCD6Rm = sq_GetCustomAttackInfo(obj, 14);
sq_SetCurrentAttackPower(CQbAQAKYspCD6Rm, CQy5zTWBM4F55Bq2);
sq_SetChangeStatusIntoAttackInfo(CQbAQAKYspCD6Rm, 0, 11, CQOM8dBNuPO5Hto1, CQWazpQYqxJDaDD, CQ8HOnOu78lCAkiVl9,CQzdtXgRkYdgP2pZN);
sq_SetCurrentAttackInfo(obj, CQbAQAKYspCD6Rm);
break;
}
break;
}
}

function setState_po_ChangQing_751675335_ATSwordmanexo(obj, CQNwK7wgCzNZZa, CQbxqYjMkeWSGRlR)
{
if(!obj) return;
obj.getVar("state").clear_vector();
obj.getVar("state").push_vector(CQNwK7wgCzNZZa);
local CQod3iGSDZ7oXZTzlV = obj.getVar("skill").get_vector(0);
local CQ2MoHyv8TaQHUTjv = sq_ObjectToSQRCharacter(obj.getTopCharacter());
switch(CQod3iGSDZ7oXZTzlV)
{
case -1:
switch(CQNwK7wgCzNZZa)
{
case 10:

break;
}
break;
case 232:
switch(CQNwK7wgCzNZZa)
{
case 10:
local CQmHg5xdQEhcAV = "passiveobject/changqing_atswordman/animation/atcatharsis/tonado/tonadofront_04.ani";
local CQJaFx5CMJDRaEjl = sq_CreateAnimation("",CQmHg5xdQEhcAV);
obj.setCurrentAnimation(CQJaFx5CMJDRaEjl);
obj.setTimeEvent(0,90,1,false);
local CQkebtHWcjc3SdjhAP = "character/atswordman/5_bladeshadows/catharsis/ap_catharsis.nut";
local CQacBFuxsoX6ssh = CNSquirrelAppendage.sq_AppendAppendage(CQ2MoHyv8TaQHUTjv, obj, 232, false,CQkebtHWcjc3SdjhAP , false);
local CQ5vv3d7gMQVibgTL = obj.getCurrentAnimation();
local CQwgBTCItR2FIX = sq_GetAttackBoundRect(CQ5vv3d7gMQVibgTL);
local CQZ3trsw5uuaomvx = sq_GetBoundingBoxXSize(CQwgBTCItR2FIX);
local CQzL9AmTUBdrWBvmTA = 800;
if(CQacBFuxsoX6ssh)
{
CNSquirrelAppendage.sq_Append(CQacBFuxsoX6ssh, obj, obj);
local CQOOOMRKScOvpaY = CQacBFuxsoX6ssh.sq_getAuraMaster("CatharsisTar");
if(!CQOOOMRKScOvpaY)
{
CQOOOMRKScOvpaY = CQacBFuxsoX6ssh.sq_AddAuraMaster("CatharsisTar",CQ2MoHyv8TaQHUTjv, obj, 1200, 18, 5, 0);
CQOOOMRKScOvpaY.setAttractionInfo(300, 150, CQzL9AmTUBdrWBvmTA.tointeger(), 100);
}
}
break;
case 11:
local CQJaFx5CMJDRaEjl = obj.getCustomAnimation(5);
CQJaFx5CMJDRaEjl.setImageRateFromOriginal(0.01, 1.0);
obj.setCurrentAnimation(CQJaFx5CMJDRaEjl);
local CQWbZQrkoCH6QO = obj.getVar().get_vector(0);
local CQVhwOT2BzbVynxW = sq_GetObjectByObjectId(CQ2MoHyv8TaQHUTjv, CQWbZQrkoCH6QO);
if(CQVhwOT2BzbVynxW)
{
CQVhwOT2BzbVynxW = sq_GetCNRDObjectToActiveObject(CQVhwOT2BzbVynxW);
procCatharsis(obj,CQVhwOT2BzbVynxW);
}
break;
}
break;
case 238:
switch(CQNwK7wgCzNZZa)
{
case 10:
local CQJaFx5CMJDRaEjl = obj.getCustomAnimation(9);
local CQSZQRDUHLranqz = 150/100.0;
CQJaFx5CMJDRaEjl.setImageRateFromOriginal(1.0, CQSZQRDUHLranqz);
obj.setCurrentAnimation(CQJaFx5CMJDRaEjl);
break;
}
break;
case 229:
switch(CQNwK7wgCzNZZa)
{
case 10:

break;
case 11:
if(obj.isMyControlObject())
sq_SetMyShake(obj,5,200);
local CQfP4mWgfT5redlr7 = obj.getVar().get_vector(1);
local CQJaFx5CMJDRaEjl = obj.getCustomAnimation(0);
local CQSZQRDUHLranqz = CQfP4mWgfT5redlr7/100.0;
CQJaFx5CMJDRaEjl.setImageRateFromOriginal(CQSZQRDUHLranqz, CQSZQRDUHLranqz);
CQJaFx5CMJDRaEjl.setAutoLayerWorkAnimationAddSizeRate(CQSZQRDUHLranqz);
sq_SetAttackBoundingBoxSizeRate(CQJaFx5CMJDRaEjl, CQSZQRDUHLranqz, CQSZQRDUHLranqz, CQSZQRDUHLranqz);
obj.setCurrentAnimation(CQJaFx5CMJDRaEjl);
break;
}
break;
}
}

function procAppend_po_ChangQing_751675335_ATSwordmanexo(obj)
{
if(!obj) return;
local CQp6nbb9Xox9Ymjiy = obj.getVar("skill").get_vector(0);
local CQ2CGp9AkMLMlV = obj.getVar("state").get_vector(0);
local CQmSnLZWSRqJgEn = sq_ObjectToSQRCharacter(obj.getTopCharacter());
switch(CQp6nbb9Xox9Ymjiy)
{
case -1:
switch(CQ2CGp9AkMLMlV)
{
case 10:

break;
}
break;
case 232:
switch(CQ2CGp9AkMLMlV)
{
case 11:
local CQJiM7Ez7y1OzfbuS = [0,0,60,21,0,0,0];
local CQkoyYhXqByyhI = [0,0,0,0,0,0,0];
local CQaqdiNINc8U9hvp = CQmSnLZWSRqJgEn.getSkillSubState();
if(CQmSnLZWSRqJgEn.getState() != CHANGQING_BLADE_STATE4 || CQaqdiNINc8U9hvp > 3)
sq_SendDestroyPacketPassiveObject(obj);
else
{
sq_setCurrentAxisPos(obj, 0,CQmSnLZWSRqJgEn.getXPos());
sq_setCurrentAxisPos(obj, 2,CQmSnLZWSRqJgEn.getZPos() + CQJiM7Ez7y1OzfbuS[CQaqdiNINc8U9hvp]);
local CQ5lAHPlxWsTjCvAdC = obj.getVar().get_vector(0);
local CQw8c5e5JCk9dqY = sq_GetObjectByObjectId(CQmSnLZWSRqJgEn, CQ5lAHPlxWsTjCvAdC);
if(CQw8c5e5JCk9dqY)
{
CQw8c5e5JCk9dqY = sq_GetCNRDObjectToActiveObject(CQw8c5e5JCk9dqY);
procCatharsis(obj,CQw8c5e5JCk9dqY);
}
}
break;
}
break;
case 238:
switch(CQ2CGp9AkMLMlV)
{
case 10:
sq_setCurrentAxisPos(obj, 2,CQmSnLZWSRqJgEn.getZPos() + 420);
if(CQmSnLZWSRqJgEn.getState() != CHANGQING_BLADE_STATE9 || CQmSnLZWSRqJgEn.getSkillSubState() != 1)
sq_SendDestroyPacketPassiveObject(obj);
break;
}
break;
case 229:
switch(CQ2CGp9AkMLMlV)
{
case 10:
local CQ5lAHPlxWsTjCvAdC = obj.getVar().get_vector(0);
local CQw8c5e5JCk9dqY = sq_GetObjectByObjectId(CQmSnLZWSRqJgEn, CQ5lAHPlxWsTjCvAdC);
if(CQw8c5e5JCk9dqY)
{
if(CQw8c5e5JCk9dqY.getZPos() <= 3)
{
sq_SetCurrentPos(obj, CQw8c5e5JCk9dqY.getXPos(), CQw8c5e5JCk9dqY.getYPos()-1, 0);
obj.addSetStatePacket(11, null, STATE_PRIORITY_AUTO, false, "");
}
}
else
sq_SendDestroyPacketPassiveObject(obj);
break;
}
break;
case 243:
local CQaqdiNINc8U9hvp = CQmSnLZWSRqJgEn.getSkillSubState();
if(CQmSnLZWSRqJgEn.getState() != CHANGQING_BLADE_STATE13 || CQaqdiNINc8U9hvp == 3)
sq_SendDestroyPacketPassiveObject(obj);
else
{
sq_setCurrentAxisPos(obj, 0,CQmSnLZWSRqJgEn.getXPos());
sq_setCurrentAxisPos(obj, 1,CQmSnLZWSRqJgEn.getYPos());
local CQ8Qe2c2nTey1OzDaV = 54;
if(CQaqdiNINc8U9hvp == 2)
CQ8Qe2c2nTey1OzDaV = 74;
sq_setCurrentAxisPos(obj, 2,CQmSnLZWSRqJgEn.getZPos() + CQ8Qe2c2nTey1OzDaV);
local CQw8c5e5JCk9dqY = CQmSnLZWSRqJgEn.getVar("Rustynail").getObject(0);
if(CQw8c5e5JCk9dqY)
{
CQw8c5e5JCk9dqY = sq_GetCNRDObjectToActiveObject(CQw8c5e5JCk9dqY);
procRustynail(obj,CQw8c5e5JCk9dqY);
}
else
sq_SendDestroyPacketPassiveObject(obj);
}
break;
}
}

function onAttack_po_ChangQing_751675335_ATSwordmanexo(obj, CQYMkAiRihf9VQ, CQSHJMYFVoPMKfqL, CQfamjVyQMz3BImFR8)
{
if(!obj || CQfamjVyQMz3BImFR8) return;
local CQueJQIYGvKZLhU = obj.getVar("skill").get_vector(0);
local CQMcmOqBcyUAFCUJr = obj.getVar("state").get_vector(0);
local CQhf1VgPsBNoZm = sq_ObjectToSQRCharacter(obj.getTopCharacter());
switch(CQueJQIYGvKZLhU)
{
case -1:

break;
case 238:
CQhf1VgPsBNoZm.getVar("DeepduskLicense").setBool(0,true);
break;
case 247:
CQhf1VgPsBNoZm.getVar("DeepduskLicense").setBool(0,true);
break;
}
}

function onEndCurrentAni_po_ChangQing_751675335_ATSwordmanexo(obj)
{
if(!obj) return;
local CQ3JRmO8tW7xPwb = obj.getVar("skill").get_vector(0);
local CQqKDalXZXaRHRvVB = obj.getVar("state").get_vector(0);
local CQKIYX3ejzh3AO = sq_ObjectToSQRCharacter(obj.getTopCharacter());
switch(CQ3JRmO8tW7xPwb)
{
case -1:
switch(CQqKDalXZXaRHRvVB)
{
case 10:

break;
}
break;
case 232:
switch(CQqKDalXZXaRHRvVB)
{
case 10:
sq_SendDestroyPacketPassiveObject(obj);
break;
}
break;
case 241:
sq_SendDestroyPacketPassiveObject(obj);
break;
case 240:
sq_SendDestroyPacketPassiveObject(obj);
break;
case 244:
sq_SendDestroyPacketPassiveObject(obj);
break;
case 249:
sq_SendDestroyPacketPassiveObject(obj);
break;
case 235:
sq_SendDestroyPacketPassiveObject(obj);
break;
case 238:
sq_SendDestroyPacketPassiveObject(obj);
break;
case 230:
sq_SendDestroyPacketPassiveObject(obj);
break;
case 229:
sq_SendDestroyPacketPassiveObject(obj);
break;
case 233:
sq_SendDestroyPacketPassiveObject(obj);
break;
case 247:
sq_SendDestroyPacketPassiveObject(obj);
break;
case 91:
sq_SendDestroyPacketPassiveObject(obj);
break;
}
}

function onTimeEvent_po_ChangQing_751675335_ATSwordmanexo(obj, CQsvYbt57LYSSVcCYC, CQ6gVpxamkXosQr)
{
if(!obj) return;
local CQe3WL5qBEQQoNeNw = obj.getVar("skill").get_vector(0);
local CQXZ77Ejz22cWs = obj.getVar("state").get_vector(0);
local CQxPIYnHHhiRpgw2 = sq_ObjectToSQRCharacter(obj.getTopCharacter());
switch(CQe3WL5qBEQQoNeNw)
{
case -1:
switch(CQsvYbt57LYSSVcCYC)
{
case 0:
sq_SendDestroyPacketPassiveObject(obj);
break;
case 1:
obj.resetHitObjectList();
break;
}
break;
case 232:
switch(CQsvYbt57LYSSVcCYC)
{
case 0:
local CQPyludofid3tPQ9LV = obj.getVar().get_vector(0);
local CQ9nLHXnrMOZQmq = 760/CQPyludofid3tPQ9LV;
obj.setTimeEvent(1,CQ9nLHXnrMOZQmq,CQPyludofid3tPQ9LV,true);
obj.setTimeEvent(2,240,1,false);
obj.setTimeEvent(3,440,1,false);
obj.setTimeEvent(4,640,1,false);
if(obj.isMyControlObject())
{
sq_SetMyShake(obj,1,840);
sq_flashScreen(obj,50,50,0,25,sq_RGB(255,255,255),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM);
}
break;
case 1:
obj.resetHitObjectList();
break;
case 2:
if(obj.isMyControlObject())
sq_flashScreen(obj,50,50,0,25,sq_RGB(255,255,255),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM);
break;
case 3:
if(obj.isMyControlObject())
sq_flashScreen(obj,50,50,0,25,sq_RGB(255,255,255),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM);
break;
case 4:
if(obj.isMyControlObject())
sq_flashScreen(obj,50,50,0,25,sq_RGB(255,255,255),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM);
break;
}
break;
case 240:
switch(CQsvYbt57LYSSVcCYC)
{
case 0:
obj.resetHitObjectList();
break;
case 1:
sq_SendDestroyPacketPassiveObject(obj);
break;
}
break;
case 249:
switch(CQsvYbt57LYSSVcCYC)
{
case 0:
obj.resetHitObjectList();
break;
}
break;
case 230:
switch(CQsvYbt57LYSSVcCYC)
{
case 0:
obj.resetHitObjectList();
break;
}
break;
}
return false;
}

function destroy_po_ChangQing_751675335_ATSwordmanexo(obj)
{
local CQB5KzUDbyJFww = obj.getVar("skill").get_vector(0);
local CQvXqtMyPVnEnRUh = obj.getVar("state").get_vector(0);
local CQDA3FAfkcBreOUdbV = sq_ObjectToSQRCharacter(obj.getTopCharacter());

switch(CQB5KzUDbyJFww)
{
case -1:

break;
case 232:
CNSquirrelAppendage.sq_RemoveAppendage(CQDA3FAfkcBreOUdbV, "character/atswordman/5_bladeshadows/catharsis/ap_catharsis.nut");
break;
}
}
