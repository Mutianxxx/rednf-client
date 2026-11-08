#include "dnf/character_advancement.hpp"
#include <algorithm>
#include <climits>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *advancementCachePolicy="pvf-owner-advancement-source-cache-v1";
void countRequest(uint64_t &value) noexcept {
    if(value<std::numeric_limits<uint64_t>::max())++value;
}
Json cacheRegistration(const CharacterRegistration &r) {
    return {{"id",r.id},{"ordinal",r.ordinal},{"offset",r.offset},{"path_offset",r.pathOffset},
        {"literal",r.literal},{"path",r.path},{"exists",r.exists}};
}
Json one(const std::vector<Field> &fields,const std::string &tag) {
    const Field *match=nullptr;
    for(const auto &f:fields)if(normalize(f.tag)==tag) {
        if(match)throw std::invalid_argument("Repeated advancement source field: "+tag);
        match=&f;
    }
    return match?match->values:Json::array();
}
int exactInt(const Json &v,const char *name) {
    if(!v.is_number_integer()||(v.is_number_unsigned()&&v.get<uint64_t>()>uint64_t(INT_MAX)))
        throw std::invalid_argument(std::string("Noninteger/out-of-range advancement ")+name);
    const auto n=v.get<int64_t>();if(n<INT_MIN||n>INT_MAX)throw std::invalid_argument("Advancement integer overflow");
    return int(n);
}
std::string optionName(const CharacterDefinition &definition,CharacterIdentity identity) {
    std::string name="分支 "+std::to_string(identity.growtype);
    if(size_t(identity.growtype)<definition.growtypeNames.size()&&definition.growtypeNames[identity.growtype].is_string())
        name=definition.growtypeNames[identity.growtype].get<std::string>();
    if(identity.awakening) {
        for(const auto &block:definition.stats)if(block.growtype==identity.growtype+1&&block.awakening==0) {
            const auto names=block.values("[awakening name]");
            if(size_t(identity.awakening)<=names.size()&&names[identity.awakening-1].is_string())
                return names[identity.awakening-1].get<std::string>();
        }
        name+=" · 觉醒 "+std::to_string(identity.awakening);
    }
    return name;
}
class SourceAdvancementAdapter final:public CharacterController {
    CharacterIdentity identity_;
    CharacterControllerServices services_;
    int64_t lastMs_=-1;
  public:
    SourceAdvancementAdapter(CharacterIdentity identity,CharacterControllerServices services)
        :identity_(identity),services_(std::move(services)) {
        if(!services_.request||!services_.tick||!services_.cancel)throw std::invalid_argument("Advancement adapter needs World consumers");
    }
    CharacterIdentity identity() const override { return identity_; }
    bool request(const CharacterActionRequest &r) override {
        if(r.simulationMs<0||(r.skill&&r.skill->jobId!=identity_.jobId))return false;
        return services_.request(r);
    }
    void tick(int64_t ms) override {
        if(ms<0||ms<lastMs_)throw std::invalid_argument("Advancement adapter clock moved backwards");
        if(ms==lastMs_)return;services_.tick(ms);lastMs_=ms;
    }
    void cancel(ControllerCancelReason r) override { services_.cancel(r);lastMs_=-1; }
};
}
Json characterAdvancementSourceContext(const Pvf &pvf,const CharacterCatalog &characters) {
    if(&characters.sourcePvf()!=&pvf||pvf.identity().empty())
        throw std::invalid_argument("Advancement source cache requires this Pvf's CharacterCatalog and a bound identity");
    Json registrations=Json::array(),definitions=Json::array();
    for(const auto &r:characters.characters.entries)registrations.push_back(cacheRegistration(r));
    for(const auto &d:characters.definitions) {
        Json blocks=Json::array();
        for(const auto &block:d.stats) {
            Json names=Json::array();
            for(const auto &field:block.fields)if(normalize(field.tag)=="[awakening name]")
                names.push_back({{"tag",field.tag},{"offset",field.offset},{"values",field.values}});
            blocks.push_back({{"tag",block.tag},{"growtype",block.growtype},{"awakening",block.awakening},
                {"offset",block.offset},{"end_offset",block.endOffset},{"ordered_awakening_names",names}});
        }
        definitions.push_back({{"registration",cacheRegistration(d.registration)},{"job",d.job},
            {"source_path",d.source.script.path},{"source_provenance",d.source.provenance},
            {"runtime_deferred_by_user",d.runtimeDeferredByUser},{"growtype_names",d.growtypeNames},
            {"ordered_stat_identity_blocks",blocks}});
    }
    return {{"cache_policy",advancementCachePolicy},{"source_parser_contract","token5-fieldview-v1"},
        {"catalog_policy","user-gsd-source-level-v1"},{"chr_identity_contract","runtime-g-to-source-g-plus-one-v1"},
        {"package_identity",pvf.identity()},{"registry_path",characters.characters.source.script.path},
        {"registry_provenance",characters.characters.source.provenance},{"ordered_registrations",registrations},
        {"ordered_definitions",definitions}};
}
std::shared_ptr<const CharacterAdvancementCatalog> sharedCharacterAdvancementCatalog(Pvf &pvf,const CharacterCatalog &characters) {
    // Canonical content, rather than a pointer or digest alone, decides a hit.
    // Public CharacterCatalog interpretation changes cannot reuse stale data.
    auto context=characterAdvancementSourceContext(pvf,characters).dump();
    auto &slot=pvf.advancementSourceCache_;countRequest(slot.requests);
    if(slot.value&&slot.context==context) {countRequest(slot.hits);return slot.value;}
    auto candidate=std::make_shared<CharacterAdvancementCatalog>(pvf,characters);
    auto digest=sha256(Bytes(context.begin(),context.end()));
    // All parsing, allocations and evidence preparation precede publication.
    // Swaps cannot expose a half-built entry; exceptions retain the old entry.
    slot.context.swap(context);slot.contextSha256.swap(digest);slot.value=std::move(candidate);
    countRequest(slot.builds);return slot.value;
}
Json characterAdvancementCacheSnapshot(const Pvf &pvf) {
    const auto &slot=pvf.advancementSourceCache_;
    return {{"policy",advancementCachePolicy},{"package_identity",pvf.identity()},{"entry_present",bool(slot.value)},
        {"context_sha256",slot.contextSha256},{"requests",slot.requests},{"hits",slot.hits},{"builds",slot.builds},
        {"ownership","Pvf holds one strong immutable payload; World holds its own reference; payload owns no Pvf/CharacterCatalog"},
        {"copy_move_policy","copy resets destination slot; move resets both slots; existing external const payloads remain valid"},
        {"threading","same single-threaded owner contract as existing Pvf parser caches"}};
}
Json CharacterAdvancementOption::snapshot() const {
    Json refs=Json::array();for(const auto &s:sources)refs.push_back(s.json());
    return {{"identity",identity.json()},{"required_level",requiredLevel},{"name",name},{"sources",refs},
        {"policy","user-gsd-source-level-v1"},{"native_skill_complete",false}};
}
CharacterAdvancementCatalog::CharacterAdvancementCatalog(Pvf &pvf,const CharacterCatalog &characters):pvfIdentity_(pvf.identity()) {
    if(pvfIdentity_.empty())throw std::invalid_argument("Advancement catalog requires bound PVF identity");
    const auto npcs=loadCharacterList(pvf,"npc/npc.lst","npc");
    for(const auto &n:npcs.entries)if(n.path=="npc/gsd.npc") {
        if(trainerId_>=0)throw std::invalid_argument("Ambiguous GSD registration");
        if(!n.exists)throw std::invalid_argument("GSD source is missing");
        trainerId_=n.id;trainerPath_=n.path;trainerSource_=makeSourceRef(pvf,n.path);
    }
    if(trainerId_<0)diagnostics_.push_back({{"code","gsd_registration_unavailable"}});
    const auto quests=loadCharacterList(pvf,"n_quest/quest.lst","n_quest");
    questRegistry_=makeSourceRef(pvf,"n_quest/quest.lst");
    std::set<CharacterIdentity> conflicts;
    for(const auto &q:quests.entries) {
        if(!q.exists){diagnostics_.push_back({{"code","missing_registered_quest"},{"path",q.path}});continue;}
        ++scanned_;
        try {
            const auto view=pvf.fieldView(q.path,{"[reward type]","[reward int data]","[job]","[grow type]","[level]"});
            const auto reward=one(view.fields,"[reward type]");
            if(reward.size()!=1||!reward[0].is_string()||
               (reward[0]!="[grow type]"&&reward[0]!="[awakening type]"))continue;
            evidence_.push_back(pvf.script(q.path));
            const auto job=one(view.fields,"[job]"),grow=one(view.fields,"[grow type]"),
                       value=one(view.fields,"[reward int data]"),levels=one(view.fields,"[level]");
            if(job.size()!=1||!job[0].is_string()||grow.size()!=1||value.size()!=1||levels.size()!=2)
                throw std::invalid_argument("Incomplete source identity reward");
            const CharacterDefinition *definition=nullptr;
            for(const auto &d:characters.definitions)if(normalize(d.job)==normalize(job[0].get<std::string>())) {
                if(definition)throw std::invalid_argument("Ambiguous source job");definition=&d;
            }
            if(!definition||definition->runtimeDeferredByUser)throw std::invalid_argument("Unknown/deferred source job");
            const int sourceGrow=exactInt(grow[0],"growtype"),destination=exactInt(value[0],"reward");
            CharacterIdentity identity{definition->registration.id,reward[0]=="[grow type]"?destination:sourceGrow,
                reward[0]=="[awakening type]"?destination:0};
            if(identity.growtype<=0||identity.awakening<0||destination<=0||
               (reward[0]=="[grow type]"&&sourceGrow!=-1))throw std::invalid_argument("Unreviewed source identity transition");
            const auto low=exactInt(levels[0],"minimum level"),high=exactInt(levels[1],"maximum level");
            if(low<1||high<low)throw std::invalid_argument("Invalid source advancement level range");
            bool sourceBlock=false;
            // CHR growth labels are one-based: source growtype1 is the base,
            // source growtype2 is reward branch1. Reuse the arithmetic contract.
            for(const auto &block:definition->stats)if(block.growtype==identity.growtype+1&&block.awakening==identity.awakening)sourceBlock=true;
            if(!sourceBlock)throw std::invalid_argument("Identity reward has no matching CHR growth block");
            auto [it,inserted]=options_.emplace(identity,CharacterAdvancementOption{identity,low,optionName(*definition,identity),{}});
            if(!inserted&&it->second.requiredLevel!=low)conflicts.insert(identity);
            it->second.sources.push_back(makeSourceRef(pvf,q.path,0,0,q.ordinal,"identity reward and level; task/material bypass by user policy"));
        }catch(const std::exception &e){diagnostics_.push_back({{"code","advancement_quest_unresolved"},{"path",q.path},{"error",e.what()}});}
    }
    for(const auto &identity:conflicts) {
        options_.erase(identity);diagnostics_.push_back({{"code","conflicting_identity_level"},{"identity",identity.json()}});
    }
    for(auto it=options_.begin();it!=options_.end();) {
        const auto identity=it->first;
        if(identity.awakening&&!options_.count({identity.jobId,identity.growtype,0})) {
            diagnostics_.push_back({{"code","awakening_without_source_branch"},{"identity",identity.json()}});it=options_.erase(it);
        }else ++it;
    }
}
const CharacterAdvancementOption *CharacterAdvancementCatalog::find(CharacterIdentity identity) const {
    const auto it=options_.find(identity);return it==options_.end()?nullptr:&it->second;
}
bool CharacterAdvancementCatalog::supports(CharacterIdentity identity) const { return find(identity)!=nullptr; }
Json CharacterAdvancementCatalog::snapshot() const {
    Json rows=Json::array();for(const auto &[id,option]:options_)rows.push_back(option.snapshot());
    return {{"policy","user-gsd-source-level-v1"},{"classification","user_requested_rule"},{"pvf_identity",pvfIdentity_},
        {"trainer_id",trainerId_},{"trainer_source",trainerSource_.json()},{"quest_registry",questRegistry_.json()},
        {"scanned_registered_quests",scanned_},{"identity_reward_sources",evidence_.size()},{"options",rows},{"diagnostics",diagnostics_},
        {"task_material_and_native_trainer_conditions","preserved in source; bypassed explicitly"},
        {"unproven_awakening_levels","not admitted"},{"skill_implementation_independent",true}};
}
void registerSourceAdvancementAdapters(CharacterControllerRegistry &registry,const CharacterCatalog &characters,
    const CharacterAdvancementCatalog &advancements,const std::string &pvfIdentity) {
    for(const auto &[identity,option]:advancements.options()) {
        if(characters.at(identity.jobId).runtimeDeferredByUser||!registry.supports({identity.jobId,0,0})||registry.supports(identity))continue;
        CharacterControllerInfo info;info.identity=identity;info.name=option.name;info.pvfSha256=pvfIdentity;
        info.implementation="source-advancement-existing-actions-v1";info.readiness=ControllerReadiness::UserAdvancementPartial;
        info.limitation="User GSD identity policy: same-job existing actions only. Exact source identity/level gates; unsupported skills remain unavailable; complete/native fidelity not established";
        const auto target=identity;
        registry.registerController(std::move(info),[target](CharacterControllerServices s){return std::make_unique<SourceAdvancementAdapter>(target,std::move(s));});
    }
}
} // namespace dnf
