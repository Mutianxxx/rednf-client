


function sq_AddFunctionName(appendage)
{
 appendage.sq_AddFunctionName("proc", "proc_appendage_atmage_shardmagnum_damage")
 appendage.sq_AddFunctionName("getImmuneTypeDamageRate","getImmuneTypeDamageRate_appendage_atmage_shardmagnum_damage")
}


function proc_appendage_atmage_shardmagnum_damage(UxS9qUXD7cnlsQ)
{
 if(!UxS9qUXD7cnlsQ) return;
 local i7_1T7Frfv4uHIpHDq = UxS9qUXD7cnlsQ.getParent();
 local fMKY2N0O5phlVH5tpV6MeHu = UxS9qUXD7cnlsQ.getSource(); 
 if(!i7_1T7Frfv4uHIpHDq || !fMKY2N0O5phlVH5tpV6MeHu)
 {
 UxS9qUXD7cnlsQ.setValid(false);
 return;
 }
} ;

function getImmuneTypeDamageRate_appendage_atmage_shardmagnum_damage(UxS9qUXD7cnlsQ, i7_1T7Frfv4uHIpHDq, fMKY2N0O5phlVH5tpV6MeHu)
{
 if(!UxS9qUXD7cnlsQ) return i7_1T7Frfv4uHIpHDq;
 local I6j45GIFolsQilB = UxS9qUXD7cnlsQ.getParent();
 local IhOCM48kAz = UxS9qUXD7cnlsQ.getSource(); 
 if(!I6j45GIFolsQilB || !IhOCM48kAz)
 {
 UxS9qUXD7cnlsQ.setValid(false);
 return i7_1T7Frfv4uHIpHDq;
 }
 
 
 
 
 
 
 
 
 
 
 if(!isSameObject(IhOCM48kAz, fMKY2N0O5phlVH5tpV6MeHu)) 
 return i7_1T7Frfv4uHIpHDq;
 i7_1T7Frfv4uHIpHDq += IhOCM48kAz.getVar("damageRate").get_vector(0); 
 return i7_1T7Frfv4uHIpHDq;
} ;


