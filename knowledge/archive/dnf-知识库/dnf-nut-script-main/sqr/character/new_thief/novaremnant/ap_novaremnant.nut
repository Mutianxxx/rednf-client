


function sq_AddFunctionName(appendage)
{
 appendage.sq_AddFunctionName("proc", "proc_appendage_thief_novaremnant")
}




function proc_appendage_thief_novaremnant(RbDrK9ySg_Q3h81qY5)
{
 if(!RbDrK9ySg_Q3h81qY5) return;
 local tkwqbnh_6DKOWEvSWO = RbDrK9ySg_Q3h81qY5.getParent();
 local KaJdml3vwiuvAl2E8fdyYl9 = sq_GetCNRDObjectToSQRCharacter(RbDrK9ySg_Q3h81qY5.getSource()); 
 if(!tkwqbnh_6DKOWEvSWO || !KaJdml3vwiuvAl2E8fdyYl9 || KaJdml3vwiuvAl2E8fdyYl9.getSkillSubState() == 5)
 {
 RbDrK9ySg_Q3h81qY5.setValid(false);
 return;
 }
} 
