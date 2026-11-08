


function sq_AddFunctionName(appendage)
{
    appendage.sq_AddFunctionName("proc", "proc_appendage_mage_avatardance")
}


function proc_appendage_mage_avatardance(zS3gTSiiEr04vRtWVLFBqe)
{
 if(!zS3gTSiiEr04vRtWVLFBqe) return;
 local pYvvg5V8V8 = zS3gTSiiEr04vRtWVLFBqe.getParent();
 local Xnt0MU6bASPRGLyKy = zS3gTSiiEr04vRtWVLFBqe.getSource(); 
 if(!pYvvg5V8V8
 || !Xnt0MU6bASPRGLyKy
 || Xnt0MU6bASPRGLyKy.getState() != 243
 || sq_GetCNRDObjectToSQRCharacter(Xnt0MU6bASPRGLyKy).getSkillSubState() >= 5)
 {
 zS3gTSiiEr04vRtWVLFBqe.setValid(false);
 return;
 }
} ;