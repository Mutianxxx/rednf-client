




function onCreateObject_swordman_hellbenter(BDG7Zw9YR9pEdLh2Q7G, zg2mVaNKGPiNWW0s5DqnmL)
{
 if(!BDG7Zw9YR9pEdLh2Q7G) return;
 if(zg2mVaNKGPiNWW0s5DqnmL.isObjectType(OBJECTTYPE_PASSIVE))
 {
 local Lg5L09fqGboonPtenroLCL = sq_GetCNRDObjectToCollisionObject(zg2mVaNKGPiNWW0s5DqnmL); 
 if(Lg5L09fqGboonPtenroLCL && Lg5L09fqGboonPtenroLCL.getCollisionObjectIndex() == 20052)
 {
 
 if(Lg5L09fqGboonPtenroLCL.isMyControlObject())
 {
 sq_BinaryStartWrite();
 sq_BinaryWriteDword(85); 
 sq_BinaryWriteDword(1); 
 sq_SendCreatePassiveObjectPacket(Lg5L09fqGboonPtenroLCL, 24370, 0, 0, 0, 0, Lg5L09fqGboonPtenroLCL.getDirection());
 }
 }
 }
} ;
