// Isolated views contain only fields touched by the original functions.
struct STSecondGrowTypeFitness { int m_fitness[2]; int m_maxLevel[2]; };
struct CSkill { int m_levelLimit, m_fieldC8; int m_typeMaxLevel[6]; STSecondGrowTypeFitness m_secondGrowTypeFitness[6];
bool can_learn(int,int,int,int) const; int get_type_max_level(int) const;
int get_second_growtype_max_level(int,int) const; int getMaxSkillLevel(int,int,int) const; };
float itemRepairCost_;
struct QuestParameter { int m_field18,m_field1c; };
struct CDataManager { QuestParameter m_questParameter; };
CDataManager manager; CDataManager* G_CDataManager() { return &manager; }
struct CUser { int compute_level_penalty(int); };
#include "D:/dnf-rebuild/dnf-result/imports/rednf/remake/source/DNFServer/GameServer/Game/CSkill/can_learn.inc"
#include "D:/dnf-rebuild/dnf-result/imports/rednf/remake/source/DNFServer/GameServer/Game/CSkill/get_type_max_level.inc"
#include "D:/dnf-rebuild/dnf-result/imports/rednf/remake/source/DNFServer/GameServer/Game/CSkill/get_second_growtype_max_level.inc"
#include "D:/dnf-rebuild/dnf-result/imports/rednf/remake/source/DNFServer/GameServer/Game/CSkill/getMaxSkillLevel.inc"
#include "D:/dnf-rebuild/dnf-result/imports/rednf/remake/source/DNFServer/GameServer/Game/Store/getEquipmentRepairPrice.inc"
#include "D:/dnf-rebuild/dnf-result/imports/rednf/remake/source/DNFServer/GameServer/Game/LinkClosureA_User/compute_level_penalty.inc"
extern "C" int run_skill(const int* a) { CSkill s; s.m_levelLimit=a[4];s.m_fieldC8=a[5];
for(int i=0;i<6;i++) {s.m_typeMaxLevel[i]=a[6];for(int j=0;j<2;j++)s.m_secondGrowTypeFitness[i].m_maxLevel[j]=a[7];}
return s.can_learn(a[0],a[1],a[2],a[3]); }
extern "C" int run_max(const int* a) { CSkill s;s.m_levelLimit=a[4];s.m_fieldC8=a[5];
for(int i=0;i<6;i++) {s.m_typeMaxLevel[i]=a[6];for(int j=0;j<2;j++)s.m_secondGrowTypeFitness[i].m_maxLevel[j]=a[7];}
return s.getMaxSkillLevel(a[0],a[1],a[2]); }
extern "C" int run_penalty(const int* a) { manager.m_questParameter.m_field18=a[1];manager.m_questParameter.m_field1c=a[2];CUser u;return u.compute_level_penalty(a[0]); }
extern "C" int run_repair(const int* a) { union Bits {int i;float f;};Bits c,r;c.i=a[4];r.i=a[5];itemRepairCost_=c.f;return getEquipmentRepairPrice(a[0],a[1],a[2],a[3],false,r.f); }
