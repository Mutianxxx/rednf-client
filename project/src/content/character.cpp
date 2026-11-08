#include "dnf/character.hpp"
#include <limits>
#include <set>
#include <stdexcept>
namespace dnf {
namespace {
CharacterScript loadSource(Pvf &pvf, const std::string &path) {
    CharacterScript result;
    result.bytes = pvf.read(path);
    result.script = pvf.script(path);
    result.provenance = pvf.reads().at(normalize(path));
    return result;
}
std::string relativeTo(const std::string &base, const std::string &literal) {
    return normalize((std::filesystem::u8path(base) / std::filesystem::u8path(literal)).generic_u8string());
}
bool motionTag(const std::string &tag) {
    return tag.size() >= 8 && tag[1] != '/' && tag.compare(tag.size() - 8, 8, " motion]") == 0;
}
bool attackInfoTag(const std::string &tag) {
    return tag == "[attack info]" || tag == "[etc attack info]" ||
           tag == "[jumpattack info]" || tag == "[dashattack info]";
}
int identityInteger(const Json &object, const char *key, int fallback, int minimum) {
    if (!object.contains(key)) return fallback;
    const auto &value = object.at(key);
    if (!value.is_number_integer() || (value.is_number_unsigned() &&
        value.get<uint64_t>() > uint64_t(std::numeric_limits<int>::max())))
        throw std::runtime_error(std::string("Invalid character identity integer: ") + key);
    const auto number = value.get<int64_t>();
    if (number < minimum || number > std::numeric_limits<int>::max())
        throw std::runtime_error(std::string("Out-of-range character identity integer: ") + key);
    return int(number);
}
bool skillModeTag(const std::string &tag) {
    return tag == "[dungeon]" || tag == "[pvp]" || tag == "[death tower]" || tag == "[warroom]";
}
bool indexedTag(const std::string &tag, const std::string &prefix, int &value) {
    if (tag.rfind(prefix, 0) || tag.back() != ']') return false;
    auto digits = tag.substr(prefix.size(), tag.size() - prefix.size() - 1);
    if (digits.empty() || digits.find_first_not_of("0123456789") != std::string::npos) return false;
    try { value = std::stoi(digits); } catch (...) { return false; }
    return true;
}
Json fieldJson(const Field &field) {
    return {{"tag", field.tag}, {"offset", field.offset}, {"values", field.values}};
}
Json sourceJson(const CharacterScript &source, bool includeSource) {
    Json result = {{"path", source.script.path}, {"byte_count", source.bytes.size()},
                   {"provenance", source.provenance}};
    if (includeSource) {
        result["fields"] = Json::array();
        for (const auto &field : source.script.fields) result["fields"].push_back(fieldJson(field));
        result["tokens"] = source.script.tokens;
        // Include bytes in explicit source exports, including token5 header.
        result["bytes"] = source.bytes;
    }
    return result;
}
Json registrationJson(const CharacterRegistration &entry) {
    return {{"id", entry.id}, {"ordinal", entry.ordinal}, {"offset", entry.offset},
            {"path_offset", entry.pathOffset}, {"literal", entry.literal},
            {"path", entry.path}, {"exists", entry.exists}};
}
Json listJson(const CharacterList &list, bool includeSource) {
    Json result = {{"source", sourceJson(list.source, includeSource)},
                   {"entries", Json::array()}, {"issues", list.issues}};
    for (const auto &entry : list.entries) result["entries"].push_back(registrationJson(entry));
    return result;
}
std::vector<int> sdCancelFrames(const std::vector<CharacterScript> &sources, const std::string &path) {
    std::vector<int> result;
    for (int index = 1; index <= 3; ++index) {
        const auto key = "attack" + std::to_string(index) + " cancel";
        bool found = false;
        for (const auto &source : sources) if (source.script.path == path)
            for (const auto &field : source.script.fields) if (normalize(field.tag) == "[int]")
                for (size_t at = 0; at + 1 < field.values.size(); at += 2)
                    if (field.values[at].is_string() && field.values[at].get<std::string>() == key) {
                        if (found || !field.values[at+1].is_number_integer())
                            throw std::runtime_error("Ambiguous/invalid native cancel frame: " + path + ":" + key);
                        result.push_back(field.values[at+1].get<int>());
                        found = true;
                    }
        if (!found) throw std::runtime_error("Missing confirmed native cancel key: " + path + ":" + key);
    }
    return result;
}
} // namespace
Json CharacterIdentity::json() const {
    return {{"job_id", jobId}, {"growtype", growtype}, {"awakening", awakening}};
}
CharacterIdentity CharacterIdentity::fromJson(const Json &value) {
    if (!value.is_object()) throw std::runtime_error("Character identity must be an object");
    return {identityInteger(value, "job_id", 0, 0), identityInteger(value, "growtype", 0, 0),
            identityInteger(value, "awakening", 0, 0)};
}
Json SkillKey::json() const { return {{"job_id", jobId}, {"skill_id", skillId}}; }
SkillKey SkillKey::fromJson(const Json &value) {
    if (!value.is_object()) throw std::runtime_error("Skill key must be an object");
    return {identityInteger(value, "job_id", 0, 0), identityInteger(value, "skill_id", -1, -1)};
}
std::vector<const ScopedSkillField *> CharacterSkillDefinition::fieldsInScope(
    const std::string &wanted, const std::string &scope) const {
    std::vector<const ScopedSkillField *> result;
    for (const auto &field : fields)
        if (normalize(field.field.tag) == normalize(wanted) && field.scope == normalize(scope))
            result.push_back(&field);
    return result;
}
Json CharacterSkillDefinition::values(const std::string &tag, const std::string &scope) const {
    const auto selected = fieldsInScope(tag, scope);
    if (selected.size() > 1) throw std::runtime_error("Repeated scoped skill field: " + source.script.path +
        ":" + scope + ":" + tag);
    return selected.empty() ? Json::array() : selected.front()->field.values;
}
CharacterSkillDefinition parseCharacterSkillSource(SkillKey key,
    CharacterRegistration registration, CharacterScript source) {
    CharacterSkillDefinition result;
    result.key = key; result.registration = std::move(registration); result.source = std::move(source);
    std::string scope = "common";
    for (const auto &field : result.source.script.fields) {
        const auto tag = normalize(field.tag);
        if (skillModeTag(tag)) {
            if (scope != "common") result.issues.push_back({{"kind", "unclosed_skill_mode"},
                {"previous_scope", scope}, {"offset", field.offset}, {"tag", field.tag}});
            scope = tag.substr(1, tag.size() - 2);
        }
        result.fields.push_back({field, scope, result.fields.size()});
        if (tag.rfind("[/", 0) == 0 && skillModeTag("[" + tag.substr(2))) {
            const auto closing = tag.substr(2, tag.size() - 3);
            if (scope != closing) result.issues.push_back({{"kind", "mismatched_skill_mode_close"},
                {"scope", scope}, {"offset", field.offset}, {"tag", field.tag}});
            scope = "common";
        }
    }
    if (scope != "common") result.issues.push_back({{"kind", "unclosed_skill_mode_at_eof"}, {"scope", scope}});
    const auto types = result.fieldsInScope("[type]");
    if (types.size() == 1 && types.front()->field.values.size() == 1 &&
        types.front()->field.values[0].is_string()) {
        const auto value = normalize(types.front()->field.values[0].get<std::string>());
        if (value == "[active]") result.kind = SkillSourceKind::Active;
        else if (value == "[passive]") result.kind = SkillSourceKind::Passive;
    }
    if (result.kind == SkillSourceKind::Unknown)
        result.issues.push_back({{"kind", "unresolved_skill_type"}, {"field_count", types.size()}});
    return result;
}
Json CharacterSkillDefinition::snapshot(bool includeSource) const {
    Json result = {{"key", key.json()}, {"registration", registrationJson(registration)},
        {"source", sourceJson(source, includeSource)},
        {"declared_kind", kind == SkillSourceKind::Active ? "active" : kind == SkillSourceKind::Passive ? "passive" : "unknown"},
        {"runtime_role", runtimeRole}, {"ordered_fields", Json::array()}, {"issues", issues},
        {"evidence", {{"source", "preserved"}, {"native_qualification", "not_recovered_by_source_model"},
            {"runtime_controller", "not_assessed_by_source_model"}, {"native_parity", "not_verified"}}}};
    for (const auto &field : fields) {
        auto value = fieldJson(field.field); value["scope"] = field.scope; value["ordinal"] = field.ordinal;
        result["ordered_fields"].push_back(std::move(value));
    }
    return result;
}
Json SkillLearningEvidence::snapshot() const {
    return {{"state", state == SourceLearningState::ExplicitLearningCandidate ? "explicit_learning_candidate" :
        state == SourceLearningState::ExplicitlyExcluded ? "explicitly_excluded" : "unresolved"},
        {"purchase_ceiling", purchaseCeiling}, {"has_fitness", hasFitness},
        {"fitness_includes_growtype", fitnessIncludesGrowtype}, {"grants_runtime_use", grantsRuntimeUse},
        {"evidence", evidence}};
}
Json DefaultAppearanceSources::snapshot(bool includeSource) const {
    Json result = {{"job_id", jobId}, {"job", job}, {"body_image_templates", bodyImageTemplates},
        {"settings", sourceJson(settings, includeSource)}, {"equipment", Json::array()}, {"issues", issues},
        {"scope", "Unmodified authored references; no slot-position or native rendering parity inference"}};
    for (const auto &entry : equipment) result["equipment"].push_back({{"field_offset", entry.fieldOffset},
        {"value_index", entry.valueIndex}, {"equipment_id", entry.equipmentId}, {"path", entry.path},
        {"registered", entry.registered}, {"exists", entry.exists}, {"has_animation_job", entry.hasAnimationJob},
        {"source", sourceJson(entry.source, includeSource)}});
    return result;
}
const CharacterRegistration *CharacterList::unique(int id) const {
    const CharacterRegistration *result = nullptr;
    for (const auto &entry : entries) if (entry.id == id) {
        if (result) return nullptr;
        result = &entry;
    }
    return result;
}
CharacterList loadCharacterList(Pvf &pvf, const std::string &path, const std::string &base) {
    CharacterList result;
    result.source = loadSource(pvf, path);
    const auto &tokens = result.source.script.tokens;
    std::set<int> ids;
    for (size_t i = 0; i < tokens.size();) {
        const auto &id = tokens[i];
        if (i + 1 >= tokens.size() || id.at("type") != 2 || !id.at("value").is_number_integer() ||
            tokens[i+1].at("type") != 7 || !tokens[i+1].at("value").is_string()) {
            result.issues.push_back({{"kind", "unparsed_registration_token"}, {"token_index", i},
                                     {"offset", id.at("offset")}});
            ++i;
            continue;
        }
        const auto &name = tokens[i+1];
        CharacterRegistration entry;
        entry.id = id.at("value").get<int>(); entry.ordinal = result.entries.size();
        entry.offset = id.at("offset").get<size_t>(); entry.pathOffset = name.at("offset").get<size_t>();
        entry.literal = name.at("value").get<std::string>();
        entry.path = relativeTo(base, entry.literal); entry.exists = pvf.has(entry.path);
        if (!ids.insert(entry.id).second)
            result.issues.push_back({{"kind", "duplicate_registration_id"}, {"id", entry.id}, {"offset", entry.offset}});
        if (!entry.exists)
            result.issues.push_back({{"kind", "missing_registered_resource"}, {"path", entry.path}, {"offset", entry.pathOffset}});
        result.entries.push_back(std::move(entry));
        i += 2;
    }
    return result;
}
Json CharacterStatBlock::values(const std::string &wanted) const {
    const auto key = normalize(wanted);
    // Refuse ambiguous repeats; callers can inspect the preserved field span.
    const Field *result = nullptr;
    for (const auto &field : fields) if (normalize(field.tag) == key) {
        if (result) throw std::runtime_error("Repeated stat field in " + tag + ": " + wanted);
        result = &field;
    }
    return result ? result->values : Json::array();
}
std::vector<const CharacterResource *> CharacterDefinition::motions(const std::string &wanted) const {
    std::vector<const CharacterResource *> result;
    const auto key = normalize(wanted);
    for (const auto &resource : resources) if (normalize(resource.tag) == key) result.push_back(&resource);
    return result;
}
const CharacterResource *CharacterDefinition::resource(const std::string &wanted, size_t slot, size_t occurrence) const {
    const auto key = normalize(wanted);
    for (const auto &field : source.script.fields) if (normalize(field.tag) == key) {
        if (occurrence) { --occurrence; continue; }
        for (const auto &candidate : resources)
            if (candidate.fieldOffset == field.offset && candidate.valueIndex == slot && normalize(candidate.tag) == key)
                return &candidate;
        return nullptr;
    }
    return nullptr;
}
std::string CharacterDefinition::motion(const std::string &tag, size_t slot, size_t occurrence) const {
    const auto key = normalize(tag);
    if (!motionTag(key) && key.rfind("[throw motion ", 0) != 0 && key.rfind("[damage motion ", 0) != 0)
        throw std::runtime_error("Not a CHR motion tag: " + tag);
    const auto *binding = resource(tag, slot, occurrence);
    if (!binding || binding->literal.empty() || !binding->exists)
        throw std::runtime_error("Unresolved CHR motion slot: " + source.script.path + ":" + tag + ":" + std::to_string(slot));
    return binding->path;
}
std::string CharacterDefinition::attackInfo(const std::string &tag, size_t slot, size_t occurrence) const {
    if (!attackInfoTag(normalize(tag))) throw std::runtime_error("Not a CHR attack-info tag: " + tag);
    const auto *binding = resource(tag, slot, occurrence);
    if (!binding || binding->literal.empty() || !binding->exists)
        throw std::runtime_error("Unresolved CHR attack-info slot: " + source.script.path + ":" + tag + ":" + std::to_string(slot));
    return binding->path;
}
std::string CharacterDefinition::motionByStem(const std::string &wanted) const {
    const auto key = normalize(wanted);
    std::string result;
    for (const auto &resource : resources) {
        if (!motionTag(normalize(resource.tag)) && resource.tag.rfind("[throw motion ", 0) != 0 &&
            resource.tag.rfind("[damage motion ", 0) != 0) continue;
        if (normalize(std::filesystem::u8path(resource.path).stem().u8string()) != key) continue;
        if (!resource.exists) throw std::runtime_error("Missing CHR motion: " + resource.path);
        if (!result.empty() && result != resource.path) throw std::runtime_error("Ambiguous CHR motion stem: " + wanted);
        result = resource.path;
    }
    if (result.empty()) throw std::runtime_error("Unbound CHR motion: " + source.script.path + ": " + wanted);
    return result;
}
CharacterCatalog::CharacterCatalog(Pvf &pvf) : pvf_(pvf) {
    characters = loadCharacterList(pvf, "character/character.lst", "character");
    skillLists = loadCharacterList(pvf, "skill/skilllist.lst", "skill");
    defaultSettings = loadSource(pvf, "character/characteretc/default.etc");
    for (const auto &path : pvf.paths("data/skill/", ".sd")) nativeSkillData.push_back(loadSource(pvf, path));
    for (const auto &entry : characters.entries) {
        CharacterDefinition definition;
        definition.registration = entry;
        if (!entry.exists) { definitions.push_back(std::move(definition)); continue; }
        definition.source = loadSource(pvf, entry.path);
        const auto &script = definition.source.script;
        const auto settingsPath = "character/characteretc/" + std::filesystem::u8path(entry.path).stem().u8string() + ".etc";
        if (pvf.has(settingsPath)) definition.settings = loadSource(pvf, settingsPath);
        else definition.issues.push_back({{"kind", "missing_character_settings"}, {"path", settingsPath}});
        definition.job = script.text("[job]");
        definition.growtypeNames = script.values("[growtype name]");
        definition.bodyImageTemplates = script.values("[body image path]");
        definition.runtimeDeferredByUser = normalize(definition.job) == "[creator mage]";
        // Recovered from this exact 1031 EXE. Native defaults are not SKL
        // controller implementations and are not inferred from box-free tails.
        switch (entry.id) {
        case 0:
            definition.basicAttackCancelFrames = {5,4};
            definition.basicAttackCancelEvidence = "1031 EXE CAE400 -> CAE4DB/CAE4F1; zero-based getter 67E970; state8 consumer 869EB0";
            break;
        case 1:
            definition.basicAttackCancelFrames = {1,1,4};
            definition.basicAttackCancelEvidence = "1031 EXE BC5330; job1 constructor D15A00 -> D16026; state8 consumer 869EB0";
            break;
        case 3:
            definition.basicAttackCancelFrames = {3,4};
            definition.basicAttackCancelEvidence = "1031 EXE C44670; constructor D18AD0 -> D19276; state8 consumer 869EB0";
            break;
        case 4:
            definition.basicAttackCancelFrames = {1,3,6};
            definition.basicAttackCancelEvidence = "1031 EXE C78D50; job4 constructor D19D80 -> D1A155; state8 consumer 869EB0";
            break;
        case 6:
            definition.basicAttackCancelFrames = sdCancelFrames(nativeSkillData, "data/skill/thief.sd");
            definition.basicAttackCancelEvidence = "data/skill/thief.sd [int]; EXE CE56AB loader -> CE89 append; state8 consumer 869EB0";
            break;
        case 7:
            definition.basicAttackCancelFrames = sdCancelFrames(nativeSkillData, "data/skill/atfighter.sd");
            definition.basicAttackCancelEvidence = "data/skill/atfighter.sd [int]; EXE BA2F7C loader -> B86A append; state8 consumer 869EB0";
            break;
        case 8:
            definition.basicAttackCancelFrames = {3,3,3};
            definition.basicAttackCancelEvidence = "current PVF sqr/init_character.nut sq_InitFrameIndices job8; sq_AddAttackCancelStartFrame(3) x3; sqr/character/atmage/atmage_common.nut may restrict count to2";
            break;
        }
        const auto base = std::filesystem::u8path(entry.path).parent_path().generic_u8string();
        int growtype = 0;
        for (const auto &field : script.fields) {
            const auto tag = normalize(field.tag);
            int index = 0;
            const bool initial = tag == "[initial value]", growth = indexedTag(tag, "[growtype ", index);
            int awakeningIndex = 0;
            const bool awakening = indexedTag(tag, "[awakening ", awakeningIndex);
            if (initial || growth || awakening) {
                if (!definition.stats.empty()) definition.stats.back().endOffset = field.offset;
                if (initial) growtype = 0;
                if (growth) growtype = index;
                definition.stats.push_back({field.tag, growtype, awakening ? awakeningIndex : 0,
                                            field.offset, definition.source.bytes.size(), {}});
            }
            // The CHR's motion section follows its stat spans. Preserve the
            // full source too; spans do not invent missing closing tags.
            const bool resourceField = motionTag(tag) || tag.rfind("[throw motion ", 0) == 0 ||
                tag.rfind("[damage motion ", 0) == 0 || tag == "[attack info]" || tag == "[etc attack info]" ||
                tag == "[jumpattack info]" || tag == "[dashattack info]";
            if (resourceField && !definition.stats.empty() && definition.stats.back().endOffset == definition.source.bytes.size())
                definition.stats.back().endOffset = field.offset;
            if (!initial && !growth && !awakening && !definition.stats.empty() &&
                field.offset < definition.stats.back().endOffset)
                definition.stats.back().fields.push_back(field);
            if (resourceField) for (size_t i = 0; i < field.values.size(); ++i) {
                if (!field.values[i].is_string()) continue;
                CharacterResource resource;
                resource.tag = field.tag; resource.fieldOffset = field.offset; resource.valueIndex = i;
                resource.literal = field.values[i].get<std::string>();
                resource.path = resource.literal.empty() ? "" : relativeTo(base, resource.literal);
                resource.exists = !resource.path.empty() && pvf.has(resource.path);
                if (!resource.exists && !resource.literal.empty()) definition.issues.push_back({{"kind", "unresolved_chr_resource"},
                    {"tag", field.tag}, {"offset", field.offset}, {"value_index", i}, {"literal", resource.literal}, {"path", resource.path}});
                definition.resources.push_back(std::move(resource));
            }
        }
        const auto *list = skillLists.unique(entry.id);
        if (list && list->exists) definition.skills = loadCharacterList(pvf, list->path, "skill");
        else definition.issues.push_back({{"kind", "missing_or_ambiguous_skill_list"}, {"character_id", entry.id}});
        definitions.push_back(std::move(definition));
    }
    for (const auto &entry : skillLists.entries)
        if (!characters.unique(entry.id)) issues.push_back({{"kind", "orphan_or_ambiguous_character_skill_list"}, {"id", entry.id}});
}
const CharacterDefinition &CharacterCatalog::at(int id) const {
    if (!characters.unique(id)) throw std::runtime_error("Missing or ambiguous character ID: " + std::to_string(id));
    for (const auto &definition : definitions) if (definition.registration.id == id) return definition;
    throw std::runtime_error("Missing character definition: " + std::to_string(id));
}
CharacterScript CharacterCatalog::skill(int characterId, int skillId) const {
    const auto *entry = at(characterId).skills.unique(skillId);
    if (!entry || !entry->exists) throw std::runtime_error("Missing or ambiguous registered skill: " +
        std::to_string(characterId) + ":" + std::to_string(skillId));
    return loadSource(pvf_, entry->path);
}
const CharacterSkillDefinition &CharacterCatalog::skillDefinition(SkillKey key) const {
    auto found = skillDefinitions_.find(key);
    if (found != skillDefinitions_.end()) return found->second;
    const auto *registration = at(key.jobId).skills.unique(key.skillId);
    if (!registration || !registration->exists) throw std::runtime_error("Missing or ambiguous registered skill: " +
        std::to_string(key.jobId) + ":" + std::to_string(key.skillId));
    return skillDefinitions_.emplace(key, parseCharacterSkillSource(key, *registration,
        loadSource(pvf_, registration->path))).first->second;
}
SkillLearningEvidence CharacterCatalog::skillEligibility(CharacterIdentity identity, SkillKey key,
    const std::string &requestedScope) const {
    SkillLearningEvidence result;
    if (identity.jobId != key.jobId || identity.growtype < 0 || identity.awakening < 0) {
        result.state = SourceLearningState::ExplicitlyExcluded;
        result.evidence.push_back({{"reason", "mismatched_job_or_negative_identity"},
            {"identity", identity.json()}, {"key", key.json()}});
        return result;
    }
    const auto &definition = skillDefinition(key);
    auto select = [&](const char *tag) -> const ScopedSkillField * {
        auto fields = definition.fieldsInScope(tag, normalize(requestedScope));
        if (fields.empty() && normalize(requestedScope) != "common") fields = definition.fieldsInScope(tag, "common");
        if (fields.size() != 1) {
            result.evidence.push_back({{"tag", tag}, {"reason", fields.empty() ? "absent" : "ambiguous_repeat"}});
            return nullptr;
        }
        result.evidence.push_back({{"tag", tag}, {"scope", fields.front()->scope},
            {"offset", fields.front()->field.offset}, {"values", fields.front()->field.values}});
        return fields.front();
    };
    const auto *fitness = select("[skill fitness growtype]");
    const auto *maximum = select("[growtype maximum level]");
    result.hasFitness = fitness != nullptr;
    bool validFitness = fitness != nullptr;
    if (fitness) for (const auto &value : fitness->field.values) {
        if (!value.is_number_integer()) { validFitness = false; continue; }
        if (value == identity.growtype) result.fitnessIncludesGrowtype = true;
    }
    if (maximum && size_t(identity.growtype) < maximum->field.values.size()) {
        const auto &ceiling = maximum->field.values[size_t(identity.growtype)];
        if (ceiling.is_number_integer() && ceiling.get<int64_t>() >= 0 &&
            ceiling.get<int64_t>() <= std::numeric_limits<int>::max()) result.purchaseCeiling = ceiling.get<int>();
    }
    if ((validFitness && !result.fitnessIncludesGrowtype) || result.purchaseCeiling == 0)
        result.state = SourceLearningState::ExplicitlyExcluded;
    else if (validFitness && result.fitnessIncludesGrowtype && result.purchaseCeiling > 0)
        result.state = SourceLearningState::ExplicitLearningCandidate;
    result.evidence.push_back({{"native_state_awakening_and_use_transaction", "not_evaluated"},
        {"named_branch_is_open", "not_established_by_skill_fitness"}});
    return result;
}
Json CharacterCatalog::identityEvidence(CharacterIdentity identity) const {
    Json result = {{"identity", identity.json()}, {"registered_job", false}, {"growtype_name_present", false},
        {"runtime_branch_open", "not_established_by_source_model"},
        {"native_awakening_gate", "not_recovered_by_source_model"}};
    if (!characters.unique(identity.jobId)) return result;
    const auto &definition = at(identity.jobId);
    result["registered_job"] = true; result["job"] = definition.job;
    result["runtime_deferred_by_user"] = definition.runtimeDeferredByUser;
    if (identity.growtype >= 0 && size_t(identity.growtype) < definition.growtypeNames.size()) {
        result["growtype_name_present"] = true;
        result["source_name"] = definition.growtypeNames[size_t(identity.growtype)];
    }
    result["source_stat_blocks"] = Json::array();
    for (const auto &block : definition.stats) result["source_stat_blocks"].push_back({{"tag", block.tag},
        {"growtype", block.growtype}, {"awakening", block.awakening}, {"offset", block.offset}});
    result["stat_block_to_name_index_mapping"] = "not_inferred";
    return result;
}
CharacterScript CharacterCatalog::equipment(int equipmentId) const {
    if (equipmentRegistry_.source.script.path.empty())
        equipmentRegistry_ = loadCharacterList(pvf_, "equipment/equipment.lst", "equipment");
    const auto *entry = equipmentRegistry_.unique(equipmentId);
    if (!entry || !entry->exists) throw std::runtime_error("Unresolved registered equipment: " + std::to_string(equipmentId));
    return loadSource(pvf_, entry->path);
}
DefaultAppearanceSources CharacterCatalog::defaultAppearanceSources(int jobId) const {
    const auto &definition = at(jobId);
    DefaultAppearanceSources result;
    result.jobId = jobId; result.job = definition.job;
    result.bodyImageTemplates = definition.bodyImageTemplates; result.settings = definition.settings;
    if (equipmentRegistry_.source.script.path.empty())
        equipmentRegistry_ = loadCharacterList(pvf_, "equipment/equipment.lst", "equipment");
    for (const auto &field : definition.settings.script.fields) {
        if (normalize(field.tag) != "[equipment index]" || field.values.empty() ||
            !field.values[0].is_string() || field.values[0].get<std::string>() != "defaultEquipment") continue;
        for (size_t index = 1; index < field.values.size(); ++index) {
            if (!field.values[index].is_number_integer()) {
                result.issues.push_back({{"kind", "noninteger_default_equipment_value"},
                    {"field_offset", field.offset}, {"value_index", index}, {"value", field.values[index]}});
                continue;
            }
            DefaultEquipmentSource entry;
            entry.fieldOffset = field.offset; entry.valueIndex = index; entry.equipmentId = field.values[index].get<int>();
            if (entry.equipmentId >= 0) {
                const auto *registered = equipmentRegistry_.unique(entry.equipmentId);
                if (registered) {
                    entry.registered = true; entry.path = registered->path; entry.exists = registered->exists;
                    if (entry.exists) {
                        entry.source = loadSource(pvf_, entry.path);
                        for (const auto &value : entry.source.script.fields)
                            if (normalize(value.tag) == "[animation job]" && !value.values.empty() &&
                                value.values[0].is_string() && normalize(value.values[0].get<std::string>()) == normalize(definition.job))
                                entry.hasAnimationJob = true;
                    }
                }
                if (!entry.registered || !entry.exists || !entry.hasAnimationJob)
                    result.issues.push_back({{"kind", !entry.registered ? "unresolved_default_equipment_number" :
                        !entry.exists ? "missing_default_equipment_source" : "default_equipment_has_no_current_animation_job"},
                        {"field_offset", field.offset}, {"value_index", index}, {"equipment_id", entry.equipmentId},
                        {"path", entry.path}, {"job", definition.job}});
            }
            result.equipment.push_back(std::move(entry));
        }
    }
    if (result.equipment.empty()) result.issues.push_back({{"kind", "missing_default_equipment_block"}});
    return result;
}
Json CharacterCatalog::skillSourceSnapshot(bool includeSource) const {
    Json result = {{"scope", "Per-job registered SKL source and qualification fields; controller/native parity not inferred"},
        {"skills", Json::array()}};
    for (const auto &definition : definitions) for (const auto &entry : definition.skills.entries)
        if (entry.exists) result["skills"].push_back(skillDefinition({definition.registration.id, entry.id}).snapshot(includeSource));
    return result;
}
Json CharacterCatalog::snapshot(bool includeSource) const {
    Json result = {{"scope", "PVF registrations and source bindings; no implicit combat controller implementation"},
        {"native_default_exe_sha256", "246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264"},
        {"characters", listJson(characters, includeSource)}, {"skill_lists", listJson(skillLists, includeSource)},
        {"default_settings", sourceJson(defaultSettings, includeSource)}, {"native_skill_data", Json::array()},
        {"definitions", Json::array()}, {"issues", issues}};
    for (const auto &data : nativeSkillData) result["native_skill_data"].push_back(sourceJson(data, includeSource));
    for (const auto &definition : definitions) {
        Json item = {{"registration", registrationJson(definition.registration)}, {"job", definition.job},
            {"runtime_deferred_by_user", definition.runtimeDeferredByUser}, {"growtype_names", definition.growtypeNames},
            {"body_image_templates", definition.bodyImageTemplates},
            {"basic_attack_cancel_frames", definition.basicAttackCancelFrames},
            {"basic_attack_cancel_evidence", definition.basicAttackCancelEvidence},
            {"source", sourceJson(definition.source, includeSource)}, {"settings", sourceJson(definition.settings, includeSource)},
            {"skills", listJson(definition.skills, includeSource)},
            {"resources", Json::array()}, {"stat_blocks", Json::array()}, {"issues", definition.issues}};
        for (const auto &resource : definition.resources) item["resources"].push_back({{"tag", resource.tag},
            {"field_offset", resource.fieldOffset}, {"value_index", resource.valueIndex}, {"literal", resource.literal},
            {"path", resource.path}, {"exists", resource.exists}});
        for (const auto &block : definition.stats) {
            Json span = {{"tag", block.tag}, {"growtype", block.growtype}, {"awakening", block.awakening},
                {"offset", block.offset}, {"end_offset", block.endOffset}, {"fields", Json::array()}};
            for (const auto &field : block.fields) span["fields"].push_back(fieldJson(field));
            item["stat_blocks"].push_back(std::move(span));
        }
        result["definitions"].push_back(std::move(item));
    }
    return result;
}
} // namespace dnf
