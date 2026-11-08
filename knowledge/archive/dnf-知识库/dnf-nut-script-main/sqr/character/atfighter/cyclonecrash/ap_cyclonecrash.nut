


function sq_AddFunctionName(appendage)
{
 appendage.sq_AddFunctionName("proc", "proc_appendage_atfighter_cyclonecrash")
 appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_atfighter_cyclonecrash")
}



function proc_appendage_atfighter_cyclonecrash(Vp2CXoakpmt2lR1)
{
 if(!Vp2CXoakpmt2lR1) return;
 local Bm7DMxix1Vu6D8i9iiFPwnW = Vp2CXoakpmt2lR1.getParent(); 
 local HCO8Wy4ebnQ7YQgj2mZN2rYq = Vp2CXoakpmt2lR1.getSource(); 
 if(!Bm7DMxix1Vu6D8i9iiFPwnW || !HCO8Wy4ebnQ7YQgj2mZN2rYq)
 {
 Vp2CXoakpmt2lR1.setValid(false);
 return;
 }
} ;

function onEnd_appendage_atfighter_cyclonecrash(jGyI00KoJEBs)
 {
 if(!jGyI00KoJEBs) return;
 local ugttNVST1vNUH = jGyI00KoJEBs.getParent(); 
 if(!ugttNVST1vNUH)
 {
 jGyI00KoJEBs.setValid(false);
 return;
 }
 ugttNVST1vNUH.setCustomRotate(false, 0.0); 
 sq_setCurrentAxisPos(ugttNVST1vNUH, 2, 0); 
 sq_SimpleMoveToNearMovablePos(ugttNVST1vNUH, 200); 
} ;

