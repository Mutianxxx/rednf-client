#include "dnf/dungeon_difficulty.hpp"
#include "dnf/monster_event_ai.hpp"
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *policyId = "inferred-mob-event-ai-integral-chance-v1";
void problem(Json &target, const std::string &kind, Json details = Json::object()) {
    details["kind"] = kind;
    details["severity"] = "error";
    target.push_back(std::move(details));
}
std::optional<int64_t> integral(const Json &value, int64_t low, int64_t high) {
    if (!value.is_number()) return std::nullopt;
    if (value.is_number_integer()) {
        if (value < low || value > high) return std::nullopt;
        return value.get<int64_t>();
    }
    const auto number = value.get<double>();
    // The supported numeric operands are bounded by uint32/int32, so a double
    // range test is exact at both accepted boundaries before narrowing.
    if (!std::isfinite(number) || std::floor(number) != number || number < double(low) || number > double(high)) return std::nullopt;
    return int64_t(number);
}
SourceRef ref(const Script &script, size_t offset, size_t length, size_t ordinal, const std::string &scope) {
    if (offset > script.rawBytes.size() || length > script.rawBytes.size() - offset) throw std::runtime_error("AI source range outside member");
    SourceRef result;
    result.packageIdentity = script.source.at("package_identity").get<std::string>();
    result.memberPath = script.path;
    result.memberSha256 = sha256(script.rawBytes);
    result.literalPath = script.source.value("literal_path", script.path);
    result.byteOffset = offset; result.byteLength = length;
    result.ordinal = ordinal; result.scope = scope;
    return result;
}
void validate(const Pvf &pvf, const Script &script, const MonsterEventAiLimits &limits) {
    if (!limits.maxSourceBytes || !limits.maxFields || !limits.maxNodes || !limits.maxDepth ||
        !limits.maxEvaluationSteps || !limits.maxRandomDraws || limits.maxDepth > 64 ||
        limits.maxSourceBytes > 1048576 || limits.maxFields > 65536 || limits.maxNodes > 16384 ||
        limits.maxEvaluationSteps > 65536 || limits.maxRandomDraws > 65536)
        throw std::runtime_error("Invalid or excessive AI budget");
    if (script.path.empty() || !script.source.is_object() || !script.source.contains("package_identity") ||
        script.source.at("package_identity") != pvf.identity() || script.rawBytes.size() < 2 ||
        script.rawBytes.size() > limits.maxSourceBytes || (script.rawBytes.size() - 2) % 5 ||
        script.fields.empty() || script.fields.size() > limits.maxFields || !script.tokens.is_array() ||
        script.tokens.size() != (script.rawBytes.size() - 2) / 5)
        throw std::runtime_error("Invalid, foreign or over-budget AI source document");
    if (script.source.contains("member_sha256") && script.source["member_sha256"] != sha256(script.rawBytes))
        throw std::runtime_error("AI source bytes no longer match their member identity");
    if(!pvf.has(script.path)) throw std::runtime_error("AI source is not a current PVF member");
    const auto original=pvf.script(script.path);
    if(original.rawBytes!=script.rawBytes || original.tokens!=script.tokens || original.fields.size()!=script.fields.size())
        throw std::runtime_error("AI source document differs from current decoded member bytes/tokens");
    for(size_t i=0;i<script.fields.size();++i)
        if(original.fields[i].tag!=script.fields[i].tag || original.fields[i].values!=script.fields[i].values ||
            original.fields[i].offset!=script.fields[i].offset)
            throw std::runtime_error("AI field semantics do not match current decoded source member");
    size_t fieldIndex = 0, operand = 0;
    bool haveField = false;
    for (size_t i = 0; i < script.tokens.size(); ++i) {
        const auto &token = script.tokens[i];
        const auto offset = 2 + i * 5;
        if (!token.is_object() || !token.contains("offset") || token["offset"] != offset ||
            !token.contains("type") || !token["type"].is_number_integer() || token["type"] < 0 || token["type"] > 255 ||
            !token.contains("value") || !token.contains("raw") || !token["raw"].is_number_integer() ||
            token["raw"] < INT32_MIN || token["raw"] > INT32_MAX ||
            script.rawBytes[offset] != token["type"].get<uint8_t>()) throw std::runtime_error("AI token identity or ordering mismatch");
        int32_t raw = 0;
        std::memcpy(&raw, script.rawBytes.data() + offset + 1, 4);
        if (raw != token["raw"].get<int32_t>()) throw std::runtime_error("AI raw operand mismatch");
        const auto type = token["type"].get<int>();
        if (type == 2) {
            if (!token["value"].is_number_integer() || token["value"] != raw) throw std::runtime_error("AI integer decode mismatch");
        } else if (type == 4) {
            float decoded = 0;
            std::memcpy(&decoded, &raw, 4);
            if (!std::isfinite(decoded) || !token["value"].is_number() || token["value"].get<double>() != double(decoded))
                throw std::runtime_error("AI float32 decode mismatch");
        } else if (type != 5 && type != 6 && type != 7 && type != 8) {
            throw std::runtime_error("Unsupported AI token kind (including translation selectors)");
        } else if (!token["value"].is_string()) throw std::runtime_error("AI string token decode mismatch");
        if (type == 5) {
            if (haveField) {
                if (operand != script.fields.at(fieldIndex).values.size()) throw std::runtime_error("Incomplete AI field operand list");
                ++fieldIndex;
            }
            if (fieldIndex >= script.fields.size() || script.fields[fieldIndex].offset != offset ||
                script.fields[fieldIndex].tag != token["value"].get<std::string>() || !script.fields[fieldIndex].values.is_array())
                throw std::runtime_error("AI field/tag mismatch");
            operand = 0; haveField = true;
        } else {
            if (!haveField || operand >= script.fields[fieldIndex].values.size() || script.fields[fieldIndex].values[operand] != token["value"])
                throw std::runtime_error("AI complete values disagree with source tokens");
            ++operand;
        }
    }
    if (!haveField || fieldIndex + 1 != script.fields.size() || operand != script.fields[fieldIndex].values.size())
        throw std::runtime_error("AI fields do not cover ordered source tokens");
}
} // namespace

Json MonsterEventAiRoute::json() const {
    return {{"configured",configured},{"ok",ok},{"difficulty",difficulty},{"literal_path",literalPath},
        {"resolved_path",resolvedPath},{"monster_source",monsterSource.json()},{"field_source",fieldSource.json()},
        {"operand_source",operandSource.json()},{"resolved_source",resolvedSource.json()},
        {"ordered_ai_fields",orderedAiFields},{"field_tokens",fieldTokens},{"diagnostics",diagnostics},
        {"event_return_mapping","inferred-mob-ai-return-to-authored-action-slot-v1"},{"whole_ai_capability",false}};
}
MonsterEventAiRoute selectMonsterEventAi(const Pvf &pvf,const Script &monster,const std::string &difficulty) {
    MonsterEventAiRoute result;result.difficulty=normalize(difficulty);
    try {
        if(result.difficulty.empty() || result.difficulty.find_first_not_of("abcdefghijklmnopqrstuvwxyz_")!=std::string::npos)
            throw std::runtime_error("Explicit authored AI difficulty is required");
        if(monster.path.empty() || !pvf.has(monster.path) || monster.source.value("package_identity",std::string())!=pvf.identity())
            throw std::runtime_error("Foreign or missing MOB for Event.ai selection");
        const auto current=pvf.script(monster.path);
        if(current.rawBytes!=monster.rawBytes || current.tokens!=monster.tokens || current.fields.size()!=monster.fields.size())
            throw std::runtime_error("MOB AI source semantics differ from current member");
        for(size_t i=0;i<monster.fields.size();++i) if(current.fields[i].tag!=monster.fields[i].tag ||
            current.fields[i].values!=monster.fields[i].values || current.fields[i].offset!=monster.fields[i].offset)
            throw std::runtime_error("MOB AI field mismatch");
        result.monsterSource=ref(monster,0,monster.rawBytes.size(),0,"monster_event_ai/monster");
        size_t begin=monster.fields.size(),end=monster.fields.size();
        for(size_t i=0;i<monster.fields.size();++i) if(normalize(monster.fields[i].tag)=="[ai pattern]") {
            result.configured=true;
            if(begin!=monster.fields.size() || !monster.fields[i].values.empty()) throw std::runtime_error("Repeated or operand-bearing MOB AI block");
            begin=i;
        }
        if(!result.configured) return result;
        for(size_t i=begin+1;i<monster.fields.size();++i) if(normalize(monster.fields[i].tag)=="[/ai pattern]") {end=i;break;}
        if(end==monster.fields.size() || !monster.fields[end].values.empty()) throw std::runtime_error("MOB AI block is unterminated");
        const auto difficultySelection=resolveDungeonDifficulty(monster,result.difficulty);
        const std::string selected="["+difficultySelection.selected+"]",close="[/"+difficultySelection.selected+"]";
        size_t selectedOrdinal=monster.fields.size();
        for(size_t i=begin;i<=end;++i) {
            const auto &field=monster.fields[i];
            const size_t next=i+1<monster.fields.size()?monster.fields[i+1].offset:monster.rawBytes.size();
            result.orderedAiFields.push_back({{"tag",field.tag},{"values",field.values},
                {"source",ref(monster,field.offset,next-field.offset,i,"monster_event_ai/retained_mob_ai").json()}});
            if(normalize(field.tag)==selected) {
                result.orderedAiFields.back()["difficulty_selection"]=difficultySelection.json();
                if(selectedOrdinal!=monster.fields.size()) throw std::runtime_error("Repeated selected MOB difficulty");
                selectedOrdinal=i;
            }
        }
        if(selectedOrdinal==monster.fields.size()) throw std::runtime_error("Selected MOB AI difficulty is absent; no fallback");
        const auto &field=monster.fields[selectedOrdinal];
        if(selectedOrdinal+1>=end || normalize(monster.fields[selectedOrdinal+1].tag)!=close ||
            !monster.fields[selectedOrdinal+1].values.empty() || field.values.size()<4)
            throw std::runtime_error("Selected MOB AI difficulty needs one complete ordered path row and closing delimiter");
        for(const auto &value:field.values) if(!value.is_string()) throw std::runtime_error("MOB AI path row has a non-string operand");
        result.literalPath=field.values[0].get<std::string>();
        const auto literal=normalize(result.literalPath);
        if(literal.empty() || literal.front()=='/' || literal.front()=='\\' || literal.find(':')!=std::string::npos ||
            literal.find('\0')!=std::string::npos || literal.size()<4 || literal.substr(literal.size()-3)!=".ai")
            throw std::runtime_error("Invalid explicit Event.ai operand");
        const auto canonical=[](const std::string &path) {
            return normalize(std::filesystem::u8path(path).lexically_normal().generic_u8string());
        };
        std::set<std::string> candidates;
        for(const auto &path:{canonical((std::filesystem::u8path(monster.path).parent_path()/std::filesystem::u8path(literal)).generic_u8string()),
            canonical(literal),canonical("monster/"+literal)}) {
            if(path==".." || path.rfind("../",0)==0) throw std::runtime_error("Event.ai operand escapes content root");
            if(pvf.has(path)) candidates.insert(path);
        }
        if(candidates.size()!=1) throw std::runtime_error("Event.ai path is absent or ambiguous");
        result.resolvedPath=*candidates.begin();
        result.fieldSource=ref(monster,field.offset,5,selectedOrdinal,"monster_event_ai/difficulty_tag");
        result.operandSource=ref(monster,field.offset+5,5,selectedOrdinal,"monster_event_ai/event_path_operand");
        result.resolvedSource=makeSourceRef(pvf,result.resolvedPath);
        const auto rowEnd=monster.fields[selectedOrdinal+1].offset;
        for(const auto &token:monster.tokens) if(token.at("offset")>=field.offset && token.at("offset")<rowEnd) result.fieldTokens.push_back(token);
        result.ok=true;
    } catch(const std::exception &error) {
        problem(result.diagnostics,"monster_event_ai_route_rejected",{{"reason",error.what()},{"path",monster.path},{"difficulty",result.difficulty}});
    }
    return result;
}

MonsterEventAiPolicy MonsterEventAiPolicy::inferredIntegralChanceV1() { return {policyId}; }
Json MonsterEventAiPolicy::json() const {
    return {{"id", id}, {"classification", "inferred_beta"},
        {"random", "bounded PCG32 integral ratio, threshold rejection with a draw budget; draw even for reached zero/full chance"},
        {"hit", "presence of typed accepted-hit record, compared to authored0/1"},
        {"cooldown", "readonly validated authored action-index query at the same preparation boundary"},
        {"native_pc_rng_and_phase", "unconfirmed"}, {"whole_ai_capability", false}};
}

struct MonsterEventAiCompiler {
    const Script &script;
    MonsterEventAiProgram &program;
    size_t at = 0;
    SourceRef current() const {
        if (at >= script.fields.size()) return ref(script, script.rawBytes.size(), 0, at, "monster_event_ai/end");
        const auto &field = script.fields[at];
        const auto end = at + 1 < script.fields.size() ? script.fields[at + 1].offset : script.rawBytes.size();
        return ref(script, field.offset, end - field.offset, at, "monster_event_ai/field");
    }
    const Field &take(const std::string &wanted, bool empty = true) {
        if (at >= script.fields.size() || normalize(script.fields[at].tag) != wanted ||
            (empty && !script.fields[at].values.empty())) throw std::runtime_error("Expected AI field " + wanted);
        return script.fields[at++];
    }
    size_t statement(size_t depth) {
        if (depth > program.limits_.maxDepth || at >= script.fields.size() || program.nodes_.size() >= program.limits_.maxNodes)
            throw std::runtime_error("AI grammar depth/node/field budget exceeded");
        const size_t index = program.nodes_.size();
        program.nodes_.push_back({});
        if (normalize(script.fields[at].tag) == "[return]") {
            auto &node = program.nodes_[index];
            node.source = current();
            const auto &field = take("[return]", false);
            const auto result = field.values.size() == 1 ? integral(field.values[0], -1, INT32_MAX) : std::nullopt;
            if (!result) throw std::runtime_error("Unsupported AI return (requires integral action index or -1)");
            node.kind = MonsterEventAiProgram::Kind::Return;
            node.value = int(*result);
            node.operands.push_back(ref(script, field.offset + 5, 5, at - 1, "monster_event_ai/return_operand").json());
            return index;
        }
        take("[think]");
        const auto conditionSource = current();
        if (at >= script.fields.size()) throw std::runtime_error("AI think has no condition");
        const auto conditionOrdinal = at;
        const auto &condition = script.fields[at++];
        auto node = program.nodes_[index];
        node.source = conditionSource;
        for (size_t i = 0; i < condition.values.size(); ++i)
            node.operands.push_back(ref(script, condition.offset + 5 + i * 5, 5, conditionOrdinal, "monster_event_ai/condition_operand").json());
        const auto tag = normalize(condition.tag);
        if (tag == "[hit]") {
            const auto expected = condition.values.size() == 1 ? integral(condition.values[0], 0, 1) : std::nullopt;
            if (!expected) throw std::runtime_error("Unsupported AI hit condition");
            node.kind = MonsterEventAiProgram::Kind::Hit; node.value = int(*expected);
        } else if (tag == "[void]" && !condition.values.empty() && condition.values[0].is_string()) {
            const auto function = condition.values[0].get<std::string>();
            if (function == "check random()" && condition.values.size() == 3) {
                const auto numerator = integral(condition.values[1], 0, UINT32_MAX), denominator = integral(condition.values[2], 1, UINT32_MAX);
                if (!numerator || !denominator || *numerator > *denominator) throw std::runtime_error("Unsupported fractional or invalid AI chance ratio");
                node.kind = MonsterEventAiProgram::Kind::Chance;
                node.numerator = uint32_t(*numerator); node.denominator = uint32_t(*denominator);
            } else if (function == "is the skill in cooltime()" && condition.values.size() == 2) {
                const auto action = integral(condition.values[1], 0, INT32_MAX);
                if (!action) throw std::runtime_error("Invalid AI cooldown action index");
                node.kind = MonsterEventAiProgram::Kind::Cooldown; node.value = int(*action);
            } else if(function=="damage check()" && condition.values.size()==2) {
                const auto threshold=integral(condition.values[1],0,INT32_MAX);
                if(!threshold)throw std::runtime_error("Invalid AI damage-check threshold");
                node.kind=MonsterEventAiProgram::Kind::DamageCheck;node.value=int(*threshold);
            } else throw std::runtime_error("Unsupported AI void function or operand shape: " + function);
        } else throw std::runtime_error("Unsupported AI condition: " + condition.tag);
        take("[true]");
        node.yes = statement(depth + 1);
        take("[false]");
        node.no = statement(depth + 1);
        take("[/think]");
        // Recursion may reallocate nodes_; retain an index and a local copy.
        program.nodes_[index] = std::move(node);
        return index;
    }
    void compile() {
        const auto &header = take("[ai pattern]", false);
        if (header.values.size() > 1 || (header.values.size() == 1 && !header.values[0].is_string()))
            throw std::runtime_error("Unsupported AI pattern header operands");
        program.root_ = statement(1);
        take("[/ai pattern]");
        if (at != script.fields.size()) throw std::runtime_error("Trailing or repeated AI statements need a separate grammar policy");
    }
};

MonsterEventAiCompilation compileMonsterEventAi(const Pvf &pvf, const Script &script,
    const MonsterEventAiPolicy &policy, const MonsterEventAiLimits &limits) {
    MonsterEventAiCompilation result;
    try {
        if (policy.id != policyId) throw std::runtime_error("AI policy is disabled or unknown");
        validate(pvf, script, limits);
        auto program = std::shared_ptr<MonsterEventAiProgram>(new MonsterEventAiProgram);
        program->script_ = script;
        program->policy_ = policy;
        program->limits_ = limits;
        program->source_ = ref(script, 0, script.rawBytes.size(), 0, "monster_event_ai/document");
        for (size_t i = 0; i < script.fields.size(); ++i) {
            const auto &field = script.fields[i];
            const auto end = i + 1 < script.fields.size() ? script.fields[i + 1].offset : script.rawBytes.size();
            program->retainedFields_.push_back({{"tag", field.tag}, {"values", field.values},
                {"offset", field.offset}, {"source", ref(script, field.offset, end - field.offset, i, "monster_event_ai/retained_field").json()}});
        }
        MonsterEventAiCompiler compiler{script, *program};
        try { compiler.compile(); }
        catch (const std::exception &error) {
            problem(result.diagnostics, "unsupported_or_malformed_monster_event_ai",
                {{"reason", error.what()}, {"source", compiler.current().json()}, {"ordered_fields", program->retainedFields_}});
            return result;
        }
        result.program = std::move(program); result.ok = true;
    } catch (const std::exception &error) {
        problem(result.diagnostics, "invalid_monster_event_ai_source_or_policy", {{"reason", error.what()}, {"path", script.path}});
    }
    return result;
}

Json MonsterEventAiProgram::json() const {
    return {{"source", source_.json()}, {"policy", policy_.json()}, {"nodes", nodes_.size()},
        {"ordered_fields", retainedFields_}, {"world_binding_required", true}, {"whole_ai_capability", false}};
}
Json MonsterEventAiCompilation::json() const {
    return {{"ok", ok}, {"program", program ? program->json() : Json()}, {"diagnostics", diagnostics}};
}
Json MonsterEventAiEvaluation::json() const {
    return {{"ok", ok}, {"returned_action_index", returnedActionIndex ? Json(*returnedActionIndex) : Json()},
        {"return_source", returnSource ? returnSource->json() : Json()}, {"trace", trace}, {"diagnostics", diagnostics},
        {"random_before", randomBefore}, {"candidate_random", candidateRandom ? candidateRandom->snapshot() : Json()}};
}

MonsterEventAiEvaluation evaluateMonsterEventAi(const MonsterEventAiProgram &program,
    const MonsterEventAiContext &context, const Pcg32 &random, const MonsterEventCooldownQuery &cooldown) {
    MonsterEventAiEvaluation result;
    result.randomBefore = random.snapshot();
    auto candidate = random;
    size_t index = program.root_, draws = 0;
    try {
        if (!context.owner || (context.acceptedHit && (!context.acceptedHit->eventId || !context.acceptedHit->attacker)))
            throw std::runtime_error("AI needs a typed owner and valid accepted-hit identity");
        for (size_t step = 0; step < program.limits_.maxEvaluationSteps; ++step) {
            const auto &node = program.nodes_.at(index);
            Json trace = {{"source", node.source.json()}, {"operand_sources", node.operands},
                {"owner", context.owner.json()}, {"tick", context.tick}};
            if (node.kind == MonsterEventAiProgram::Kind::Return) {
                trace["kind"] = "return"; trace["value"] = node.value;
                result.trace.push_back(std::move(trace));
                result.returnedActionIndex = node.value; result.returnSource = node.source;
                result.candidateRandom = std::move(candidate); result.ok = true;
                return result;
            }
            bool selected = false;
            if (node.kind == MonsterEventAiProgram::Kind::Hit) {
                const bool hit = context.acceptedHit.has_value();
                selected = int(hit) == node.value;
                trace["kind"] = "hit"; trace["expected"] = node.value;
                trace["accepted_event"] = context.acceptedHit ? Json(context.acceptedHit->eventId) : Json();
                trace["attacker"] = context.acceptedHit ? context.acceptedHit->attacker.json() : Json();
            } else if (node.kind == MonsterEventAiProgram::Kind::Chance) {
                const auto threshold = (uint32_t(0) - node.denominator) % node.denominator;
                Json attempted = Json::array();
                uint32_t value = 0;
                for (;;) {
                    if (draws >= program.limits_.maxRandomDraws) throw std::runtime_error("AI random draw budget exceeded");
                    ++draws;
                    value = candidate.next(); attempted.push_back(value);
                    if (value >= threshold) break;
                }
                const auto sample = value % node.denominator;
                selected = sample < node.numerator;
                trace["kind"] = "chance"; trace["numerator"] = node.numerator;
                trace["denominator"] = node.denominator; trace["draws"] = attempted;
                trace["sample"] = sample; trace["comparison"] = "sample<numerator";
            } else if (node.kind == MonsterEventAiProgram::Kind::Cooldown) {
                if (!cooldown) throw std::runtime_error("Missing AI cooldown query");
                const auto inCooldown = cooldown(context.owner, node.value);
                if (!inCooldown) throw std::runtime_error("AI cooldown action index is unavailable");
                selected = *inCooldown;
                trace["kind"] = "cooldown"; trace["source_action_index"] = node.value;
            } else if(node.kind==MonsterEventAiProgram::Kind::DamageCheck) {
                if(!context.acceptedHit || context.acceptedHit->actualHpLoss<0 || context.acceptedHit->damageWindowAmount<0)
                    throw std::runtime_error("AI damage-check needs typed accepted-damage window");
                const auto &hit=*context.acceptedHit;
                selected=hit.damageCheckEnabled && hit.damageWindowAmount>=node.value;
                trace["kind"]="damage_check";trace["policy"]="inferred-source-damage-window-rolling-v1";
                trace["classification"]="inferred_beta";trace["enabled"]=hit.damageCheckEnabled;trace["window_configuration"]=hit.damageWindowConfiguration;
                trace["accepted_actual_hp_loss"]=hit.actualHpLoss;trace["window_amount"]=hit.damageWindowAmount;
                trace["authored_threshold"]=node.value;trace["comparison"]="window_amount>=threshold";
            } else throw std::runtime_error("Invalid compiled AI node");
            trace["result"] = selected;
            result.trace.push_back(std::move(trace));
            index = selected ? node.yes : node.no;
        }
        throw std::runtime_error("AI evaluation step budget exceeded");
    } catch (const std::exception &error) {
        problem(result.diagnostics, "monster_event_ai_evaluation_rejected", {{"reason", error.what()}, {"source", program.source_.json()}});
    }
    return result;
}
} // namespace dnf
