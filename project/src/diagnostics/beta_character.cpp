#include "dnf/beta_character.hpp"
#include <algorithm>
#include <stdexcept>
namespace dnf {
Json selectBetaTestCharacter(CharacterStore &store,int slot,World &world,Progression &progress,CharacterIdentity identity) {
    if(!store.data.contains("beta_branch")||store.data.at("beta_branch").value("kind",std::string())!="isolated-beta-test"||
       !world.debugOverrides().enabled||world.combat||world.player.dead)
        throw std::runtime_error("Test character selection requires the isolated beta branch in a living town");
    if(store.hasPendingCommit())throw std::runtime_error("Retry the pending test checkpoint before switching character");
    if(!world.supportsCharacter(identity))throw std::runtime_error("The selected source branch has no executable controller");
    const auto old=store.data.at("characters").at(slot);
    const auto overrides=world.debugOverrides();
    Json candidate={{"name",old.value("name",std::string("Beta"))},{"uuid",old.at("uuid")},
        {"identity",identity.json()},{"class",std::filesystem::u8path(world.characterCatalog().at(identity.jobId).registration.path).stem().u8string()},
        {"level",progress.level()},{"weapon",0},{"skill_initialization","source-v1"},
        {"test_identity_selection",{{"normal_record_preserved",true},{"classification","user_requested_temporary"}}}};
    store.data["characters"][slot]=std::move(candidate);
    try {
        // CharacterStore preflights this job's actual default EQU, appearance,
        // source skill initialization and attributes before selecting it.
        store.apply(slot,world,progress);
        world.applyDebugOverrides(overrides,progress.level());
    } catch(...) {store.data["characters"][slot]=old;throw;}
    return {{"identity",world.identity().json()},{"normal_record_preserved",true},
        {"store_directory_scope","isolated-beta-test"},{"normal_level",progress.level()}};
}
Json unlockExecutableBetaSkills(World &world) {
    if(!world.debugOverrides().enabled||world.combat||world.player.dead)
        throw std::runtime_error("Open executable test skills only in a living beta-test town");
    Json opened=Json::array(),blocked=Json::array();
    if(auto *runtime=world.experimentalRuntime()) {
        const auto preview=world.setExperimentalSkillPreviewEnabled(true);
        if(!preview.ok)throw std::runtime_error("Explicit beta skill preview unavailable: "+preview.message);
        auto prepared=runtime->configuration();const auto &plan=runtime->plan();size_t slot=0;
        for(const auto &[key,row]:plan.skills)if(row.kind==SkillSourceKind::Active) {
            try {
                if(plan.identity.jobId==1) {
                    if(!plan.sourceSkillActions.count(key))throw std::runtime_error("Source action chain unavailable; choose an explicit ANI/ATK in skill configuration");
                    if(!prepared.binding(key))prepared.configureSourceSkillAction(key,1,plan);
                }else prepared.configureBasicAttackTemplate(key,1,plan);
                if(plan.identity.jobId==1) {
                    const auto &slots=prepared.slots();
                    if(std::find(slots.begin(),slots.end(),std::optional<SkillKey>(key))==slots.end()) {
                        while(slot<slots.size()&&slots[slot])++slot;
                        if(slot<slots.size())prepared.assignSlot(slot++,key,plan);
                    }
                }else if(slot<prepared.slots().size())prepared.assignSlot(slot++,key,plan);
                opened.push_back({{"skill",key.json()},{"name",row.name},
                    {"classification",key.jobId==1?"40jp_source_action_preview":key.jobId==5?"inferred_source_controller":"user_requested_basic_template"}});
            }catch(const std::exception &error){blocked.push_back({{"skill",key.json()},{"reason",error.what()}});}
        }
        runtime->configuration()=std::move(prepared);
    } else {
        // Reuse the real isolated learning service, including prerequisite,
        // source fitness, level and test SP checks. Revisit earlier rows after
        // another row grants a prerequisite; never fabricate a normal level.
        for(size_t pass=0;pass<world.skills.size();++pass) {
            bool changed=false;
            for(const auto &skill:world.skills)if(skill.level==0) {
                const auto quote=world.quoteTestSkillLearning(skill.identity());if(!quote.accepted())continue;
                const auto result=world.learnTestSkill({"beta-open:"+std::to_string(quote.revision)+":"+std::to_string(skill.id),
                    skill.identity(),quote.revision,quote.targetLevel});
                if(result.ok){opened.push_back({{"skill",skill.identity().json()},{"name",skill.name},
                    {"classification","isolated_source_learning"}});changed=true;}
            }
            if(!changed)break;
        }
        for(const auto &skill:world.skills)if(skill.level==0)
            blocked.push_back({{"skill",skill.identity().json()},{"quote",world.quoteTestSkillLearning(skill.identity()).json()}});
    }
    return {{"opened",opened},{"blocked",blocked},{"normal_learning_unchanged",true},
        {"fighter_all_source_catalog",world.identity().jobId==1},{"missing_chain_policy","diagnose and preserve explicit user ANI/ATK choices; no automatic upper fallback"},
        {"scope","Only actual executable consumers, or explicitly marked user-authorized basic templates; no new native branch claim"}};
}
}
