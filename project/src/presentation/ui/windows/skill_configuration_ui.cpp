#include "dnf/skill_configuration_ui.hpp"
#include "dnf/progression.hpp"
#include "dnf/experimental_character.hpp"
#include <filesystem>

namespace dnf {
namespace {
std::string fitted(Renderer &render, std::string value, int width, int size = 13) {
    if (render.textWidth(value,size) <= width) return value;
    while (!value.empty() && render.textWidth(value + "…",size) > width) {
        size_t last = value.size()-1;
        while (last && (static_cast<unsigned char>(value[last]) & 0xc0) == 0x80) --last;
        value.erase(last);
    }
    return value + "…";
}
std::string bindingLabel(const ExperimentalSourceBinding &binding) {
    return binding.tag + " #" + std::to_string(binding.slot) + ": " +
        std::filesystem::u8path(binding.source.memberPath).filename().u8string();
}
int previewMaximum(const ExperimentalSkillRow &row,int growtype,bool allBranches) {
    int maximum=row.data?row.data->purchaseMaximum(growtype).value_or(1):1;
    if(allBranches&&row.data)for(const auto *tag:{"[growtype maximum level]","[second growtype maximum level]"})
        for(const auto &value:row.data->values(tag))if(value.is_number_integer())maximum=std::max(maximum,value.get<int>());
    return std::max(1,maximum);
}
}
void SkillConfigurationUi::reset() {
    identity_.reset();selected_.reset();page_=slot_=motion_=0;attack_=-1;level_=1;message_.clear();preview_=false;fighterSource_=false;view_=Json::object();
}
bool SkillConfigurationUi::draw(Renderer &render, World &world, int mx, int my, bool click, bool allowManualPreview) {
    if (!identity_ || !(*identity_ == world.identity())) { reset();identity_=world.identity(); }
    bool changed = false;
    auto *runtime = world.experimentalRuntime();
    const bool currentPreview=runtime&&world.experimentalSkillPreviewEnabled();
    if(preview_!=currentPreview){selected_.reset();page_=0;preview_=currentPreview;}
    const auto &labels = ExperimentalSkillConfiguration::slotLabels();
    const bool femaleGunner=runtime&&runtime->plan().identity.jobId==5;
    fighterSource_=allowManualPreview&&world.debugOverrides().enabled&&runtime&&runtime->plan().identity.jobId==1;
    // Normal slot assignment never edits levels, ANI/ATK or the preview
    // configuration. The World prepares and validates learned bindings.
    if(!currentPreview) {
        render.text("已学技能快捷栏",135,82,22);
        render.text(world.debugOverrides().enabled?"使用隔离测试学习的有效等级；正常SP和存档保持独立。":"快捷栏使用正常已学等级；在技能学习页升级技能。",125,112,13);
        for(size_t i=0;i<13;++i){const int x=125+int(i%7)*78,y=137+int(i/7)*30;
            if(render.button((slot_==i?"[":"")+std::string(labels[i])+(slot_==i?"]":""),x,y,73,26,mx,my,click))slot_=i;}
        struct LearnedRow {SkillKey key;std::string name;SkillLearningUseEligibility eligibility;};
        std::vector<LearnedRow> learnedRows;
        for(const auto key:world.learningSkillKeys()) {
            const auto policy=world.runtimeSkillPolicy(key);
            if(!policy.implemented||policy.kind!=SkillSourceKind::Active)continue;
            const auto &definition=world.characterCatalog().skillDefinition(key);
            auto name=definition.source.script.text("[name]");if(name.empty())name="技能 #"+std::to_string(key.skillId);
            learnedRows.push_back({key,std::move(name),world.skillUseEligibility(key)});
        }
        visibleCount_=learnedRows.size();sourceCount_=world.characterSource().skills.entries.size();
        const size_t pages=std::max(size_t(1),(learnedRows.size()+7)/8);page_=std::min(page_,pages-1);
        if(selected_&&std::none_of(learnedRows.begin(),learnedRows.end(),[&](const auto &row){return row.key==*selected_;}))selected_.reset();
        if(!selected_&&!learnedRows.empty())selected_=learnedRows[page_*8].key;
        view_={{"mode",world.debugOverrides().enabled?"test_effective_learned":"normal_learned"},{"rows",Json::array()},
            {"eligibility_queries_this_draw",learnedRows.size()}};
        for(const auto &row:learnedRows)view_["rows"].push_back({{"key",row.key.json()},{"name",row.name},{"eligibility",row.eligibility.json()}});
        for(size_t i=page_*8;i<std::min(learnedRows.size(),page_*8+8);++i){
            const auto &row=learnedRows[i];
            const std::string label=(selected_&&*selected_==row.key?"> ":"")+row.name+" Lv."+std::to_string(row.eligibility.learnedLevel);
            if(render.button(fitted(render,label,245),125,204+int(i-page_*8)*30,260,27,mx,my,click))selected_=row.key;
        }
        if(render.button("上一页",125,450,80,25,mx,my,click,page_>0))--page_;
        render.text(std::to_string(page_+1)+" / "+std::to_string(pages),215,455,13);
        if(render.button("下一页",310,450,75,25,mx,my,click,page_+1<pages))++page_;
        if(selected_){
            const auto row=std::find_if(learnedRows.begin(),learnedRows.end(),[&](const auto &candidate){return candidate.key==*selected_;});
            const auto &eligibility=row->eligibility;
            render.text(fitted(render,row->name,265,15),400,231,15);
            render.text("已学 Lv."+std::to_string(eligibility.learnedLevel),400,270,13);
            if(!eligibility.allowed())render.text(fitted(render,"暂不可绑定："+eligibility.error,265,12),400,304,12);
            if(render.button("绑定已学技能",400,355,175,28,mx,my,click,eligibility.allowed())){
                const auto result=world.assignLearnedSkillSlot(slot_,*selected_);message_=result.message;changed=result.ok;
            }
        }else render.text("本职业暂无可配置的已登记消费者。",400,240,12);
        if(render.button("清空此槽",585,465,85,25,mx,my,click)){
            const auto result=world.assignLearnedSkillSlot(slot_,std::nullopt);message_=result.message;changed=result.ok;
        }
        if(runtime&&render.button("手动预览（隔离测试）",400,410,220,28,mx,my,click,allowManualPreview)){
            const auto result=world.setExperimentalSkillPreviewEnabled(true);message_=result.message;changed=result.ok;
            if(result.ok){selected_.reset();page_=0;}
        }
        render.text(fitted(render,message_,540,12),125,503,12);return changed;
    }
    view_={{"mode","explicit_manual_preview"},{"editing_allowed",allowManualPreview}};
    if(!allowManualPreview){
        render.text("手动预览仅在隔离测试分支开放",135,82,22);
        render.text("返回正常学习后，按真实已学等级重新生成快捷栏。",125,120,13);
        if(render.button("返回已学快捷栏",400,410,220,28,mx,my,click)){
            const auto result=world.setExperimentalSkillPreviewEnabled(false);message_=result.message;changed=result.ok;
        }
        render.text(fitted(render,message_,540,12),125,503,12);return changed;
    }
    render.text(runtime?"技能配置 · PVF 实验角色":"技能快捷栏配置",135,82,22);
    render.text(fighterSource_?"女格斗全分支测试：源动作优先；等级/资源/武器门槛隔离，缺失链仅提示。":
        femaleGunner?"源技能阶段/被动等级测试；与正常SP学习账本隔离。":runtime?"选择技能、动作和 ATK 后绑定；专用机制仍待验证。":"选择已实现技能，再点目标快捷槽并保存。",125,112,13);
    for (size_t i=0;i<13;++i) {
        const int x=125+int(i%7)*78,y=137+int(i/7)*30;
        std::string label=(slot_==i?"[":"")+std::string(labels[i])+(slot_==i?"]":"");
        if(render.button(label,x,y,73,26,mx,my,click)) slot_=i;
    }
    std::vector<std::pair<SkillKey,std::string>> rows;
    if(runtime) {
        if(render.button(activeOnly_?"显示全部源技能":"只显示主动",550,82,120,25,mx,my,click)) {
            activeOnly_=!activeOnly_;page_=0;selected_.reset();
        }
        for(const auto &[key,row]:runtime->plan().skills) {
            if(activeOnly_&&row.kind!=SkillSourceKind::Active)continue;
            const std::string kind=row.kind==SkillSourceKind::Passive?" [被动]":row.kind==SkillSourceKind::Unknown?" [未知]":" [主动]";
            const auto status=fighterSource_?(runtime->plan().sourceSkillActions.count(key)?
                (runtime->configuration().binding(key)?" [源链]":" [源链待配]"):runtime->configuration().binding(key)?" [手动]":" [待选动作]"):"";
            rows.push_back({key,std::to_string(key.skillId)+" "+row.name+kind+status});
        }
    } else for(const auto &skill:world.skills) rows.push_back({skill.identity(),skill.name});
    visibleCount_=rows.size();sourceCount_=runtime?runtime->plan().skills.size():world.skills.size();
    const size_t pages=std::max(size_t(1),(rows.size()+7)/8);
    page_=std::min(page_,pages-1);
    if(selected_&&std::none_of(rows.begin(),rows.end(),[&](const auto &row){return row.first==*selected_;}))selected_.reset();
    if(!selected_&&!rows.empty())selected_=rows[page_*8].first;
    if(runtime)render.text("源条目 "+std::to_string(runtime->plan().skills.size())+" / 当前 "+std::to_string(rows.size()),125,188,11);
    for(size_t i=page_*8;i<std::min(rows.size(),page_*8+8);++i) {
        const int y=204+int(i-page_*8)*30;
        const bool current=selected_&&*selected_==rows[i].first;
        if(render.button(fitted(render,(current?"> ":"")+rows[i].second,245),125,y,260,27,mx,my,click)) {
            selected_=rows[i].first;motion_=0;attack_=-1;level_=1;message_.clear();
            if(runtime)if(const auto *binding=runtime->configuration().binding(*selected_)) {
                level_=binding->level;
                const auto &plan=runtime->plan();
                for(size_t j=0;j<plan.motions.size();++j)
                    if(plan.motions[j].source.json()==binding->motion.source.json()&&plan.motions[j].tag==binding->motion.tag&&plan.motions[j].slot==binding->motion.slot)motion_=j;
                if(binding->attack)for(size_t j=0;j<plan.attacks.size();++j)
                    if(plan.attacks[j].source.json()==binding->attack->source.json()&&plan.attacks[j].tag==binding->attack->tag&&plan.attacks[j].slot==binding->attack->slot)attack_=int(j);
            }
            if(femaleGunner) {
                const auto configured=runtime->configuration().femaleGunnerLevels();auto it=configured.find(*selected_);
                if(it!=configured.end())level_=std::max(1,it->second);
            }
        }
    }
    if(render.button("上一页",125,450,80,25,mx,my,click,page_>0))--page_;
    render.text(std::to_string(page_+1)+" / "+std::to_string(pages),215,455,13);
    if(render.button("下一页",300,450,85,25,mx,my,click,page_+1<pages))++page_;
    render.text("目标槽："+std::string(labels[slot_]),400,204,16);
    if(femaleGunner&&selected_) {
        const auto &plan=runtime->plan();auto it=plan.skills.find(*selected_);
        if(it!=plan.skills.end()) {
            const auto &row=it->second;const bool passive=row.kind==SkillSourceKind::Passive;
            render.text(fitted(render,row.name,265,15),400,231,15);
            render.text(fitted(render,row.source.memberPath,265,11),400,254,11);
            auto descriptor=plan.femaleGunnerSkills.find(*selected_);
            const bool supported=descriptor!=plan.femaleGunnerSkills.end()&&(passive||descriptor->second.dedicatedRuntime);
            if(descriptor!=plan.femaleGunnerSkills.end()) {
                render.text("来源分组："+descriptor->second.family,400,280,12);
                render.text("动作阶段 "+std::to_string(descriptor->second.stages.size())+" / 特效 "+std::to_string(descriptor->second.effectSources.size()),400,305,12);
            }
            render.text(passive?"被动实验等级，不占用快捷槽":"本职业SKL/CHR/OBJ推理控制器",400,333,12);
            int maximum=0;if(row.data)for(const auto &v:row.data->values("[growtype maximum level]"))if(v.is_number_integer())maximum=std::max(maximum,v.get<int>());
            maximum=std::max(1,maximum);level_=std::clamp(level_,1,maximum);
            if(render.button("-",400,362,28,25,mx,my,click,level_>1))--level_;
            if(render.button("+",640,362,28,25,mx,my,click,level_<maximum))++level_;
            render.text("实验等级 "+std::to_string(level_)+" / "+std::to_string(maximum),438,368,12);
            if(render.button(passive?"保存被动测试等级":"保存源技能并绑定",400,401,175,28,mx,my,click,supported)) {
                try {
                    auto prepared=runtime->configuration();prepared.configureFemaleGunnerSourceSkill(*selected_,level_,plan);
                    if(!passive)prepared.assignSlot(slot_,*selected_,plan);
                    runtime->configuration()=std::move(prepared);changed=true;
                    message_=passive?"被动实验等级已保存，正常学习账本未变。":"源技能已绑定；推理阶段与命中效果待用户验证。";
                }catch(const std::exception &error){message_=error.what();}
            }
            if(render.button("移除此技能覆盖",400,435,175,25,mx,my,click)) {
                auto prepared=runtime->configuration();
                for(size_t i=0;i<prepared.slots().size();++i)if(prepared.slots()[i]&&*prepared.slots()[i]==*selected_)prepared.assignSlot(i,std::nullopt,plan);
                prepared.clearSkillBinding(*selected_);runtime->configuration()=std::move(prepared);changed=true;message_="所选技能实验覆盖已移除。";
            }
            if(!supported)render.text("此条目缺少可执行来源，保留诊断。",400,470,11);
        }
    } else if(runtime&&selected_) {
        const auto &plan=runtime->plan();const auto found=plan.skills.find(*selected_);
        if(found!=plan.skills.end()) {
            const auto &row=found->second;
            const bool sourceAction=plan.sourceSkillActions.count(*selected_)!=0;
            render.text(fitted(render,row.name,265,15),400,231,15);
            render.text(fitted(render,row.source.memberPath,265,11),400,254,11);
            const bool canConfigure=row.kind==SkillSourceKind::Active&&!plan.motions.empty();
            if(!plan.motions.empty()) {
                motion_=std::min(motion_,plan.motions.size()-1);
                render.text(fighterSource_&&!sourceAction?"源链未闭合：手动选 ANI / ATK":"动作 ANI（本职业 CHR 原槽）",400,275,13);
                if(render.button("<",400,298,28,25,mx,my,click,motion_>0))--motion_;
                if(render.button(">",640,298,28,25,mx,my,click,motion_+1<plan.motions.size()))++motion_;
                render.text(fitted(render,bindingLabel(plan.motions[motion_]),202,11),432,304,11);
            }
            attack_=std::clamp(attack_,-1,int(plan.attacks.size())-1);
            render.text("攻击 ATK（可留空，仅播放动作）",400,330,13);
            if(render.button("<",400,353,28,25,mx,my,click,attack_>=0))--attack_;
            if(render.button(">",640,353,28,25,mx,my,click,attack_+1<int(plan.attacks.size())))++attack_;
            render.text(fitted(render,attack_<0?"无 ATK":bindingLabel(plan.attacks[size_t(attack_)]),202,11),432,359,11);
            const int maximum=previewMaximum(row,plan.identity.growtype,fighterSource_);
            level_=std::clamp(level_,1,maximum);
            if(render.button("-",400,390,28,25,mx,my,click,level_>1))--level_;
            if(render.button("+",640,390,28,25,mx,my,click,level_<maximum))++level_;
            render.text("实验技能等级 "+std::to_string(level_),441,395,13);
            if(render.button("保存到此快捷槽",400,429,175,28,mx,my,click,canConfigure)) {
                try {
                    auto prepared=runtime->configuration();
                    prepared.configureSkill(*selected_,plan.motions[motion_],attack_<0?std::nullopt:
                        std::optional<ExperimentalSourceBinding>(plan.attacks[size_t(attack_)]),level_,plan);
                    prepared.assignSlot(slot_,*selected_,plan);runtime->configuration()=std::move(prepared);
                    changed=true;message_="已保存实验绑定；按快捷键执行。";
                } catch(const std::exception &error) {message_=error.what();}
            }
            if(render.button(fighterSource_?"采用源动作":"普攻模板",585,429,85,28,mx,my,click,
                canConfigure&&(!fighterSource_||sourceAction))) {
                try {
                    auto prepared=runtime->configuration();
                    if(fighterSource_)prepared.configureSourceSkillAction(*selected_,level_,plan);
                    else prepared.configureBasicAttackTemplate(*selected_,level_,plan);
                    prepared.assignSlot(slot_,*selected_,plan);runtime->configuration()=std::move(prepared);
                    const auto *binding=runtime->configuration().binding(*selected_);
                    for(size_t j=0;j<plan.motions.size();++j)if(plan.motions[j].json()==binding->motion.json())motion_=j;
                    if(binding->attack)for(size_t j=0;j<plan.attacks.size();++j)
                        if(plan.attacks[j].json()==binding->attack->json())attack_=int(j);
                    changed=true;message_=fighterSource_?"已采用当前技能的源动作链；正常学习账本保持独立。":
                        "已套用本职业源普攻模板，使用所选技能MP/CD；专用技能仍待验证。";
                } catch(const std::exception &error) {message_=error.what();}
            }
            if(!canConfigure)render.text("被动或未知项保留来源，尚无专用消费者。",400,429,12);
            if(fighterSource_) {
                view_["fighter_selected"]={{"key",selected_->json()},{"source_action",sourceAction},
                    {"configured",runtime->configuration().binding(*selected_)!=nullptr},{"maximum",maximum},
                    {"normal_learning_unchanged",true}};
            }
        }
    } else if(selected_) {
        const auto selected=std::find_if(world.skills.begin(),world.skills.end(),[&](const Skill &skill){return skill.identity()==*selected_;});
        render.text(fitted(render,selected==world.skills.end()?"无可配置技能":selected->name,265,15),400,240,15);
        if(render.button("保存到此快捷槽",400,295,220,32,mx,my,click,!rows.empty())) {
            const auto found=std::find_if(world.skills.begin(),world.skills.end(),[&](const Skill &skill){return skill.identity()==*selected_;});
            if(found!=world.skills.end()) {
                const int index=int(found-world.skills.begin());
                const auto occupied=std::find(world.bindings.begin(),world.bindings.end(),index);
                if(occupied!=world.bindings.end())std::swap(*occupied,world.bindings[slot_]);
                else world.bindings[slot_]=index;
                changed=true;message_="快捷槽已保存。";
            }
        }
    }
    if(runtime&&!femaleGunner) {
        const auto &policy=runtime->configuration().weaponTypePolicy();
        const std::string label=policy=="physical"?"武器类型：物理（推理）":policy=="magical"?"武器类型：魔法（推理）":"武器类型：拒绝未明项";
        if(render.button(label,400,465,175,25,mx,my,click)) {
            runtime->configuration().setWeaponTypePolicy(policy=="physical"?"magical":policy=="magical"?"blocked":"physical");
            changed=true;message_="仅解释 ATK 的 [weapon] 类型；源 ATK 保留。";
        }
    }
    if(render.button("清空此槽",585,465,85,25,mx,my,click)) {
        if(runtime)runtime->configuration().assignSlot(slot_,std::nullopt,runtime->plan());
        else world.bindings[slot_]=-1;
        changed=true;message_="此快捷槽已清空。";
    }
    if(render.button("返回已学快捷栏",125,475,220,25,mx,my,click)){
        const auto result=world.setExperimentalSkillPreviewEnabled(false);message_=result.message;changed=changed||result.ok;
        if(result.ok){selected_.reset();page_=0;}
    }
    render.text(fitted(render,message_,540,12),125,503,12);
    return changed;
}
} // namespace dnf
