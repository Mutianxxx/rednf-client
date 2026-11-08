#include "dnf/walk_geometry.hpp"
#include "dnf/combat.hpp"
#include "dnf/local_pause_clock.hpp"
#include "dnf/character_advancement.hpp"
#include "dnf/character_attack.hpp"
#include "dnf/progression.hpp"
#include "dnf/effect_plan.hpp"
#include "dnf/collision.hpp"
#include "dnf/axis_motion.hpp"
#include "dnf/skill_cost.hpp"
#include "dnf/act_world_host.hpp"
#include "dnf/squirrel_action_service.hpp"
#include "dnf/female_gunner_world.hpp"
#include <cmath>
#include <limits>
namespace dnf {
namespace {
double rampIntegral(double t) { return t * t * t - 0.5 * t * t * t * t; }
}
double MotionProfile::velocity(double elapsedMs, double durationMs, double peakSpeed) const {
    if (elapsedMs <= 0 || elapsedMs >= durationMs || durationMs <= 0) return 0;
    const double up = std::min(double(accelerationMs), durationMs * 0.4);
    const double down = std::min(double(decelerationMs), durationMs * 0.4);
    double t = 1;
    if (up > 0 && elapsedMs < up) t = elapsedMs / up;
    if (down > 0 && elapsedMs > durationMs - down) t = (durationMs - elapsedMs) / down;
    return peakSpeed * t * t * (3 - 2 * t);
}
double MotionProfile::distance(double elapsedMs, double durationMs, double peakSpeed) const {
    if (durationMs <= 0) return 0;
    const double t = std::clamp(elapsedMs, 0.0, durationMs);
    const double up = std::min(double(accelerationMs), durationMs * 0.4);
    const double down = std::min(double(decelerationMs), durationMs * 0.4);
    double integral = up > 0 ? up * rampIntegral(std::min(t / up, 1.0)) : 0;
    if (t > up) integral += std::min(t, durationMs - down) - up;
    if (down > 0 && t > durationMs - down) {
        const double remaining = (durationMs - t) / down;
        integral += down * (0.5 - rampIntegral(remaining));
    }
    return integral * peakSpeed / 1000.0;
}
double Skill::parameter(int col) const {
    return skillLevelValue(levelInfo, level, col).value_or(0);
}

World::World(Pvf &p, Assets &a, WorldRules rules) : pvf_(p), assets_(a), characters_(p), rules_(rules),
    controllers_(CharacterControllerRegistry::currentCandidate(characters_)),
    statuses_(p.identity(),StunStatusPolicy::inferredFlatChanceStunV1()) {
    auto sourceSkill = [&](int id, SkillSourceKind kind) {
        const auto &definition = characters_.skillDefinition({identity_.jobId, id});
        if (definition.kind != kind) throw std::runtime_error("Controller/SKL type mismatch: " + definition.source.script.path);
        auto data = std::make_shared<SkillSourceData>(readSkillSourceData(definition, "dungeon"));
        Skill s;
        s.jobId = definition.key.jobId; s.id = definition.key.skillId;
        s.source = definition.source.script.path;
        s.key = std::filesystem::u8path(s.source).stem().u8string();
        s.name = data->name();
        if (s.name.empty()) throw std::runtime_error("Missing skill source name: " + s.source);
        auto firstEndpoint = [&](const char *tag) {
            const auto number = data->firstNumber(tag);
            if (!number) {
                if (data->ambiguousFields.count(normalize(tag)))
                    throw std::runtime_error("Ambiguous skill source endpoint: " + s.source + ":" + tag);
                if (data->selected.count(normalize(tag)))
                    throw std::runtime_error("Invalid skill source endpoint: " + s.source + ":" + tag);
                return 0; // Absent field, not a fabricated MP/cooldown content value.
            }
            if (*number < 0 || *number > std::numeric_limits<int>::max())
                throw std::runtime_error("Out-of-range skill source endpoint: " + s.source + ":" + tag);
            return int(*number); // Existing candidate uses the first endpoint only.
        };
        s.cooldown = firstEndpoint("[cool time]");
        s.casting = firstEndpoint("[casting time]");
        s.mp = firstEndpoint("[consume MP]");
        s.levelInfo = data->values("[level info]");
        s.command = data->values("[command]");
        const auto maximum = data->purchaseMaximum(identity_.growtype);
        if (!maximum) throw std::runtime_error("Missing/invalid skill purchase ceiling: " + s.source);
        s.maxLevel = *maximum;
        s.sourceData = std::move(data);
        return s;
    };
    auto add = [&](int id, std::vector<Stage> stages, std::string fx = "",
                   bool continuation = false, bool air = false) {
        auto s = sourceSkill(id, SkillSourceKind::Active);
        s.stages = std::move(stages);
        s.effect = fx;
        s.continuation = continuation;
        s.airOnly = air;
        skills.push_back(s);
    };
    add(46, {{"attack3", 0, true}});
    add(5, {{"hardattack"}});
    add(8, {{"tripleslash1", 360}, {"tripleslash2", 360}, {"tripleslash3", 300}}, "",
        true);
    add(11, {{"dashattackmultihit", 180}});
    add(16, {{"jumpattack"}},
        "passiveobject/character/swordman/animation/ashenforksub.ani", false, true);
    add(17, {{"jumpattackmultislash1"}, {"jumpattackmultislash2"}}, "", true,
        true);
    add(20, {{"wave"}},
        "passiveobject/character/swordman/animation/normalwavefire.ani");
    add(25, {{"summon2"}},
        "passiveobject/character/swordman/animation/khazanareastay.ani");
    add(58, {{"vaneslashtry"}, {"vaneslash", 0, false, true}});
    add(64, {{"gorecross"}},
        "passiveobject/character/swordman/animation/gorecross1.ani");
    add(65, {{"hopsmashready"}, {"hopsmash"}});
    add(77, {{"moonlightslash1"}, {"moonlightslash2"}}, "", true);
    add(1, {{"guard"}});
    for (auto &stage : skills[5].stages) stage.movement = MovementPolicy::AirControl;
    for (const char *key : {"basicattackup", "shortswordmastery", "blademastery", "heavyswordmastery",
                            "bluntmastery", "armormasterylight"}) {
        const CharacterRegistration *registration = nullptr;
        for (const auto &entry : characterSource().skills.entries)
            if (std::filesystem::u8path(entry.path).stem().u8string() == key) {
            if (registration) throw std::runtime_error("Ambiguous passive skill source: " + std::string(key));
            registration = &entry;
        }
        if (!registration) throw std::runtime_error("Unregistered passive skill source: " + std::string(key));
        passives.push_back(sourceSkill(registration->id, SkillSourceKind::Passive));
    }
    swordmanSkills_=skills; swordmanPassives_=passives;
    resetBindings();
    createController();
    reset();
    if (usesSourceGrowth()) applyBaseAttributes(prepareBaseAttributes(identity_, characterLevel), AttributeRebuildReason::CharacterRestore);
}
CharacterControllerServices World::controllerServices() {
    return {
        [this](const CharacterActionRequest &request) {
            if(pickupAction_&&request.inputDown)return false;
            if (experimentalRuntime_) return experimentalRuntime_->request(request);
            if (request.inputKey < 0 || request.inputKey >= int(held_.size())) return false;
            applyInput({0, request.inputKey, request.inputDown});
            return true;
        },
        [this](int64_t) { simulateTick(); },
        [this](ControllerCancelReason reason) {
            if(experimentalRuntime_)experimentalRuntime_->cancel(reason);
            idle();
        }
    };
}
void World::createController() {
    controller_ = controllers_.create(identity_,controllerServices());
}
void World::resetBindings() {
    for (int i = 0; i < int(bindings.size()); i++) bindings[i] =
        !experimentalRuntime_ && i<int(skills.size()) ? i : -1;
}
void World::releaseInputs() {
    clearSkillInputTransients();
    if(experimentalRuntime_)experimentalRuntime_->releaseInputs();
    held_.fill(false);
    inputs_.clear();
    commandHistory_.clear();
    running_ = false;
    lastLeft_ = lastRight_ = -100000;
    queued_ = false;
    bufferedSkill_ = -1;
    bufferedSkillCommand_ = false;
}
void World::selectCharacter(CharacterIdentity identity) {
    selectCharacter(identity,{});
}
void World::selectCharacter(CharacterIdentity identity,std::unique_ptr<ExperimentalCharacterRuntime> preparedExperiment) {
    if(skillProjectionRevision_==UINT64_MAX)throw std::overflow_error("Skill projection revision exhausted");
    characters_.at(identity.jobId); // Validate against the actual source registry.
    if (!supportsCharacter(identity))
        throw std::runtime_error("Character controller not restored: job=" + std::to_string(identity.jobId) +
            ", growtype=" + std::to_string(identity.growtype) + ", awakening=" + std::to_string(identity.awakening));
    std::unique_ptr<ExperimentalWorldAdapter> preparedAdapter;
    if(preparedExperiment && (!(preparedExperiment->plan().identity==identity) || identity.jobId==0))
        throw std::invalid_argument("Prepared character runtime belongs to another identity");
    if(identity.jobId!=0) {
        if(!experimentalEnabled_)throw std::runtime_error("Experimental entry is not enabled");
        if(!preparedExperiment)preparedExperiment=prepareExperimentalRuntime(identity,Json());
        preparedExperiment->setAnimationClockPolicy(animationClockPolicy_);
        preparedExperiment->setBasicAttackMovementEnabled(basicMovementPolicy_.enabled);
        preparedAdapter=std::make_unique<ExperimentalWorldAdapter>(*this);
    }
    std::optional<CharacterBaseAttributes> preparedAttributes;
    if (usesSourceGrowth()) preparedAttributes = prepareBaseAttributes(identity, 1);
    validateCharacterRestoreCapacity();
    cancelSquirrelActions("character_change");
    if (controller_) controller_->cancel(ControllerCancelReason::CharacterChange);
    identity_ = identity;
    experimentalRuntime_=std::move(preparedExperiment);
    experimentalAdapter_=std::move(preparedAdapter);
    experimentalDiagnostics_=Json::array();
    if(experimentalRuntime_){skills.clear();passives.clear();}
    else {
        skills=swordmanSkills_;passives=swordmanPassives_;
        // Re-entering an admitted exact branch uses that source purchase
        // ceiling, including after save/reload. Source use eligibility remains
        // separate from this runtime ceiling and learned-level projection.
        if(identity.growtype>0)for(auto *list:{&skills,&passives})for(auto &skill:*list)
            if(skill.sourceData)skill.maxLevel=skill.sourceData->purchaseMaximum(identity.growtype).value_or(0);
    }
    resetBindings();
    speedAttributes_.reset();
    equipmentResources_.reset();
    combatAttributes_.reset();
    basicLocalAge_=0; basicClockMs_=nowMs();
    equippedAppearance_.reset();
    skillCostCache_.clear();
    diagnosticAppearances_.clear();
    skillState_ = CharacterSkillState(identity);
    skillTestOverlay_ = {};
    experimentalSkillPreviewEnabled_=false;
    normalSkillConfiguration_.reset();testSkillConfiguration_.reset();previewSkillConfiguration_.reset();
    ++skillProjectionRevision_;
    lastSkillLearningTrace_=Json::object();
    createController();
    reset();
    if (preparedAttributes) applyBaseAttributes(std::move(*preparedAttributes), AttributeRebuildReason::CharacterRestore);
}
const CharacterAppearance &World::characterAppearance() const {
    if (equippedAppearance_) return *equippedAppearance_;
    auto found = diagnosticAppearances_.find(weapon);
    if (found == diagnosticAppearances_.end())
        found = diagnosticAppearances_.emplace(weapon,
            diagnosticWeaponAppearance(pvf_, characters_, identity_, weapon)).first;
    return found->second;
}
CharacterAppearance World::prepareEquipmentAppearance(const Progression &progression, CharacterIdentity identity) const {
    return progression.appearance(pvf_, characters_, identity);
}
CharacterBaseAttributes World::prepareBaseAttributes(CharacterIdentity identity, int level) const {
    auto attributes = buildCharacterBaseAttributes(characters_.at(identity.jobId), identity, level,
        CharacterGrowthPolicy::inferredChrGrowthV1());
    if (!attributes.usable() || attributes.integer(ChrAttribute::HpMax) <= 0 || attributes.integer(ChrAttribute::MpMax) < 0)
        throw std::runtime_error("Character source growth cannot produce usable resource limits: " + attributes.snapshot().dump());
    return attributes;
}
void World::applyBaseAttributes(CharacterBaseAttributes attributes, AttributeRebuildReason reason) {
    if (!usesSourceGrowth() || !(attributes.identity == identity_) || !attributes.usable())
        throw std::invalid_argument("Prepared attributes do not belong to this character/rule profile");
    const int hpMax = attributes.integer(ChrAttribute::HpMax), mpMax = attributes.integer(ChrAttribute::MpMax);
    if (hpMax <= 0 || mpMax < 0 || attributeRevision_ == std::numeric_limits<uint64_t>::max())
        throw std::runtime_error("Invalid character resource limit or exhausted attribute revision");
    const auto old = Json{{"hp",player.hp},{"mp",player.mp},{"max_hp",player.maxHp},{"max_mp",player.maxMp},{"level",characterLevel}};
    const bool alive = !player.dead && player.life == ActorLife::Alive;
    const bool preserveLoss = reason == AttributeRebuildReason::NormalLevelUp;
    const bool restoreFull = reason == AttributeRebuildReason::CharacterRestore;
    const auto bounded = [](int64_t value, int maximum) { return int(std::clamp<int64_t>(value,0,maximum)); };
    const int hp = !alive ? 0 : restoreFull ? hpMax : preserveLoss ?
        bounded(int64_t(hpMax) - (int64_t(player.maxHp) - player.hp),hpMax) : bounded(player.hp,hpMax);
    const int mp = restoreFull && alive ? mpMax : preserveLoss && alive ?
        bounded(int64_t(mpMax) - (int64_t(player.maxMp) - player.mp),mpMax) : bounded(player.mp,mpMax);
    const char *name = restoreFull ? "character_restore" : preserveLoss ? "normal_level_up" :
        reason == AttributeRebuildReason::DebugLevelOverride ? "debug_level_override" : "equipment_change";
    lastAttributeChange_ = {{"reason",name},{"before",old},{"after",{{"hp",hp},{"mp",mp},
        {"max_hp",hpMax},{"max_mp",mpMax},{"level",attributes.level}}},
        {"classification","inferred_beta"},{"tick",tick},{"revision",attributeRevision_+1}};
    baseAttributes_ = std::move(attributes);
    equipmentResources_.reset();
    ++attributeRevision_;
    characterLevel = baseAttributes_->level;
    if(reason!=AttributeRebuildReason::DebugLevelOverride) normalCharacterLevel_=characterLevel;
    player.maxHp = hpMax; player.maxMp = mpMax; player.hp = hp; player.mp = mp;
}
void World::setCharacterAppearance(CharacterAppearance appearance) {
    if (!(appearance.identity == identity_) || appearance.job != characterSource().job)
        throw std::invalid_argument("Equipment appearance belongs to another character identity");
    equippedAppearance_ = std::move(appearance);
    skillCostCache_.clear();
}
void World::applyEquipment(const Progression &progression) {
    std::optional<CharacterBaseAttributes> attributes;
    std::optional<CharacterSpeeds> speeds;
    std::optional<EquipmentResourceAttributes> resources;
    std::optional<CombatAttributeSnapshot> combatAttributes;
    const int effectiveLevel = debugOverrides_.enabled && debugOverrides_.level ? *debugOverrides_.level : progression.level();
    if (usesSourceGrowth()) attributes = prepareBaseAttributes(identity_, effectiveLevel);
    if (attributes) speeds = prepareCharacterSpeeds(*attributes,progression);
    if (attributes) resources = prepareEquipmentResources(*attributes,progression);
    if (attributes) combatAttributes = prepareCombatAttributes(*attributes,progression);
    auto appearance = progression.appearance(pvf_, characters_, identity_);
    const int nextWeapon = progression.equippedWeapon(), attack = progression.attackBonus(), defense = progression.defenseBonus();
    // The publication methods below also protect their standalone callers.
    // Check all of their fallible domain preconditions before the first live
    // update so a source/qualification failure cannot leave half an outfit.
    if (!(appearance.identity == identity_) || appearance.job != characterSource().job)
        throw std::invalid_argument("Equipment appearance belongs to another character identity");
    if (resources && (!usesSourceGrowth() || !(resources->adjusted.identity == identity_) || !resources->usable() ||
        resources->adjusted.integer(ChrAttribute::HpMax) <= 0 || resources->adjusted.integer(ChrAttribute::MpMax) < 0 ||
        attributeRevision_ == std::numeric_limits<uint64_t>::max()))
        throw std::runtime_error("Prepared equipment attributes cannot be published");
    if (speeds && (!usesSourceGrowth() || !(speeds->identity == identity_) || !speeds->usable()))
        throw std::invalid_argument("Prepared equipment speeds cannot be published");
    if (resources) applyEquipmentResources(std::move(*resources), debugOverrides_.enabled && debugOverrides_.level ?
        AttributeRebuildReason::DebugLevelOverride : progression.level() > normalCharacterLevel_ ?
        AttributeRebuildReason::NormalLevelUp : AttributeRebuildReason::EquipmentChange);
    setCharacterAppearance(std::move(appearance));
    weapon = nextWeapon;
    equipmentAttack = attack;
    equipmentDefense = defense;
    normalCharacterLevel_ = progression.level();
    characterLevel = effectiveLevel;
    if (speeds) applyCharacterSpeeds(std::move(*speeds));
    if (combatAttributes) applyCombatAttributes(std::move(*combatAttributes));
}
Operation World::changeEquipment(Progression &progression, int inventoryIndex, bool unequip) {
    Json diagnostic = {{"operation",unequip ? "unequip" : "equip"},{"inventory_index",inventoryIndex},
        {"tick",tick},{"phase","inventory_qualification"},{"status","rejected"}};
    try {
        Progression candidate(progression);
        auto result = unequip ? candidate.unequip(inventoryIndex) : candidate.equip(inventoryIndex,characterSource());
        if (!result) {
            diagnostic["message"] = result.message;
            lastEquipmentChange_ = std::move(diagnostic);
            return result;
        }
        diagnostic["before"] = progression.state.at("equipped");
        diagnostic["after"] = candidate.state.at("equipped");
        diagnostic["phase"] = "source_preflight";
        // Build the success diagnostic before publishing. applyEquipment reads
        // and validates all resources before changing live attributes; the
        // same-catalog candidate then publishes through nonthrowing swaps.
        auto committed = diagnostic;
        committed["status"] = "applied";
        committed["phase"] = "committed";
        applyEquipment(candidate);
        progression.commitPrepared(std::move(candidate));
        lastEquipmentChange_ = std::move(committed);
        return result;
    } catch (const std::exception &error) {
        diagnostic["status"] = "rejected";
        diagnostic["error"] = error.what();
        lastEquipmentChange_ = std::move(diagnostic);
        return {false,unequip ? "卸装失败：来源或属性校验未通过" : "装备失败：来源或属性校验未通过",0,0};
    }
}
CharacterSpeeds World::prepareCharacterSpeeds(const CharacterBaseAttributes &attributes, const Progression &progression) const {
    auto speeds=evaluateCharacterSpeeds(attributes,progression,characters_.at(attributes.identity.jobId),
                                       CharacterSpeedPolicy::inferredFlatEquipmentV1());
    if(!speeds.usable()) throw std::runtime_error("Source equipment speed cannot be evaluated: "+speeds.snapshot().dump());
    return speeds;
}
EquipmentResourceAttributes World::prepareEquipmentResources(const CharacterBaseAttributes &base, const Progression &progression) const {
    auto resources=evaluateEquipmentResourceAttributes(base,progression,characters_.at(base.identity.jobId),
                                                       EquipmentResourcePolicy::inferredFlatAndRateV1());
    if (!resources.usable()) throw std::runtime_error("Source equipment resources cannot be evaluated: "+resources.snapshot().dump());
    return resources;
}
CombatAttributeSnapshot World::prepareCombatAttributes(const CharacterBaseAttributes &base, const Progression &progression) const {
    auto result=evaluateCombatAttributes(base,progression,characters_.at(base.identity.jobId),
        CombatAttributePolicy::inferredEquipmentCombatStatV1(pvf_.script("etc/etcparameter.etc")));
    if (!result.usable()) throw std::runtime_error("Source combat attributes cannot be evaluated: "+
        Json{{"policy",result.policy},{"identity",result.identity.json()},{"level",result.level},{"diagnostics",result.diagnostics}}.dump());
    const auto resistance=evaluateCharacterStatusResistances(result.pureChr,characters_.at(base.identity.jobId),
        result.equipmentSources,result.qualificationLevel);
    if(!resistance.usable()) throw std::runtime_error("Source status resistances cannot be evaluated: "+resistance.snapshot().dump());
    return result;
}
void World::applyCombatAttributes(CombatAttributeSnapshot attributes) {
    if (!usesSourceGrowth() || !(attributes.identity==identity_) || !attributes.usable())
        throw std::invalid_argument("Prepared combat attributes belong to another character or are unusable");
    combatAttributes_=std::move(attributes);
}
void World::applyEquipmentResources(EquipmentResourceAttributes resources, AttributeRebuildReason reason) {
    if (!resources.usable()) throw std::invalid_argument("Prepared equipment resource result is unavailable");
    // Publish limits through the same resource/death/rebuild policy used by
    // growth. The owned receipt is retained for debug rebuild and feedback.
    applyBaseAttributes(resources.adjusted,reason);
    equipmentResources_=std::move(resources);
}
void World::applyCharacterSpeeds(CharacterSpeeds speeds) {
    if(!usesSourceGrowth() || !(speeds.identity==identity_) || !speeds.usable())
        throw std::invalid_argument("Prepared character speed belongs to another character/rule profile");
    // A multiplier change preserves consumed local phase, source frames and
    // event/hit registrations. Only subsequent simulation time uses the rate.
    speedAttributes_=std::move(speeds);
}
void World::applyDebugOverrides(const DebugOverrides &overrides, int normalLevel) {
    if (overrides.monsterAiDifficulty.size() > 64 ||
        overrides.monsterAiDifficulty.find_first_not_of("abcdefghijklmnopqrstuvwxyz_") != std::string::npos)
        throw std::invalid_argument("Monster AI difficulty must be an exact source row name or empty");
    const int effectiveLevel = overrides.enabled && overrides.level ? *overrides.level : normalLevel;
    if (normalLevel < 1 || normalLevel > 99 || (overrides.level && (*overrides.level < 1 || *overrides.level > 99)))
        throw std::invalid_argument("Debug level exceeds the implemented 1..99 growth policy range");
    std::optional<CharacterBaseAttributes> attributes;
    if (usesSourceGrowth()) attributes = prepareBaseAttributes(identity_,effectiveLevel);
    else if (overrides.enabled && overrides.level)
        throw std::invalid_argument("Level override requires the source-growth beta rule profile");
    std::optional<CharacterSpeeds> speeds;
    std::optional<EquipmentResourceAttributes> resources;
    std::optional<CombatAttributeSnapshot> combatAttributes;
    if(attributes && speedAttributes_) {
        speeds=evaluateCharacterSpeeds(*attributes,characterSource(),speedAttributes_->equipmentSources,normalLevel,
                                       CharacterSpeedPolicy::inferredFlatEquipmentV1());
        if(!speeds->usable()) throw std::runtime_error("Debug source speed reconstruction failed: "+speeds->snapshot().dump());
    }
    if (attributes && equipmentResources_) {
        resources=evaluateEquipmentResourceAttributes(*attributes,characterSource(),equipmentResources_->equipmentSources,normalLevel,
                                                       EquipmentResourcePolicy::inferredFlatAndRateV1());
        if (!resources->usable()) throw std::runtime_error("Debug equipment resource reconstruction failed: "+resources->snapshot().dump());
    }
    if (attributes && combatAttributes_) {
        combatAttributes=evaluateCombatAttributes(*attributes,characterSource(),combatAttributes_->equipmentSources,normalLevel,
            CombatAttributePolicy::inferredEquipmentCombatStatV1(combatAttributes_->damageConstants));
        if (!combatAttributes->usable()) throw std::runtime_error("Debug combat attribute reconstruction failed: "+combatAttributes->snapshot().dump());
    }
    // Build the projection before publishing attributes so a stale test overlay
    // cannot leave a partially applied debug command.
    auto preparedOverlay=skillTestOverlay_;
    if (hasLearningLedger() && overrides.enabled) preparedOverlay.upgradeNormalBinding(skillState_,nowMs());
    std::unique_ptr<PreparedSkillRuntime> preparedSkillRuntime;
    if(hasLearningLedger()) {
        auto context=currentSkillProjectionContext(overrides.enabled,normalLevel,effectiveLevel);
        context.previewEnabled=overrides.enabled&&experimentalSkillPreviewEnabled_;
        preparedSkillRuntime=prepareSkillRuntime(skillState_,preparedOverlay,context);
    }
    if(preparedSkillRuntime)publishPreparedSkillRuntime(*preparedSkillRuntime);
    // All source reads and numeric validation precede live publication. No
    // progression, purchase, XP or skill-ledger service is called here.
    if (resources) applyEquipmentResources(std::move(*resources),AttributeRebuildReason::DebugLevelOverride);
    else if (attributes) applyBaseAttributes(std::move(*attributes),AttributeRebuildReason::DebugLevelOverride);
    if(speeds) applyCharacterSpeeds(std::move(*speeds));
    if(combatAttributes) applyCombatAttributes(std::move(*combatAttributes));
    skillTestOverlay_=std::move(preparedOverlay);
    debugOverrides_ = overrides;
    if(!preparedSkillRuntime)projectSkillLevels();
    normalCharacterLevel_ = normalLevel;
    if (overrides.enabled && overrides.hpLock && !player.dead && player.life == ActorLife::Alive)
        player.hp = player.maxHp;
    if (overrides.enabled && overrides.mpLock) player.mp = player.maxMp;
}
std::string World::actorAni() const {
    if(pickupAction_)return pickupAction_->path;
    if(experimentalRuntime_&&!player.animationPath.empty())return player.animationPath;
    const auto &character = characterSource();
    static const std::map<std::string, std::string> tags = {
        {"stay", "[waiting motion]"}, {"move", "[move motion]"}, {"dash", "[dash motion]"},
        {"jump", "[jump motion]"}, {"jumpattack", "[jumpattack motion]"},
        {"dashattack", "[dashattack motion]"}, {"damage1", "[damage motion 1]"},
        {"damage2", "[damage motion 2]"}, {"down", "[down motion]"}, {"sit", "[sit motion]"}};
    const auto bound = tags.find(player.animation);
    if (bound != tags.end()) return character.motion(bound->second);
    if (player.animation == "attack1" || player.animation == "attack2" || player.animation == "attack3")
        return character.motion("[attack motion]", size_t(player.animation.back() - '1'));
    if (active_ >= 0 && skills[active_].id == 64) return character.motion("[etc motion]", 25);
    if (active_ >= 0 && skills[active_].id == 11) return character.motion("[etc motion]", 11);
    // Existing Swordman skill stages still have explicit authored ANI stems.
    // Their native etc-motion slot consumers are restored per controller.
    return character.motionByStem(player.animation);
}
void World::reset() {
    changeScene();
    skillState_.clearCooldowns();
    god = freeCd = freezeAi = false;
    debugOverrides_ = {};
    skillTestOverlay_ = {};
    projectSkillLevels();
    normalCharacterLevel_ = characterLevel;
    bloodVigorousLevel = 0;
    lastSkillCostTrace_ = Json::object();
    monsters.clear();
    player.hp = player.maxHp;
    player.mp = player.maxMp;
    player.dead = false;
    player.life = ActorLife::Alive;
    player.animationPath.clear();
    player.z = player.vz = 0;
    player.x = player.px = 240;
    player.y = player.py = 260;
    basicLocalAge_=0; basicClockMs_=nowMs();
}
void World::changeScene() {
    auto entities=entities_;
    entities.retireAll();
    const auto playerHandle=entities.create();
    clearSceneTransients();
    entities_=std::move(entities);
    player.handle=playerHandle;
    for (auto &m : monsters) m.handle = {};
}
void World::clearSceneTransients() {
    if (femaleGunnerWorld_) femaleGunnerWorld_->clear("scene_change_or_restore");
    cancelSquirrelActions("scene_change_or_restore");
    cancelSourceActions("scene_change");
    clearMonsterEventAi("scene_change");
    explorationConsumers_.clear();
    mapExplorationActive_ = mapExplorationGeometryAvailable_ = false;
    statuses_.clearAll(uint64_t(nowMs()),"scene_change");
    if (controller_) controller_->cancel(ControllerCancelReason::RoomChange);
    attackVolumes.clear();
    idle();
    effects.clear();
    pendingEffects_.clear();
    inputs_.clear();
    held_.fill(false);
    commandHistory_.clear();
    guardUntil_ = 0;
    player.z = player.vz = 0;
    player.pz = 0;
    player.stunUntil = 0;
    player.hitStopTicks = 0;
    player.hitStopped = false;
    player.vx = player.vy = 0;
    running_ = false;
    lastLeft_ = lastRight_ = -100000;
    player.px = player.x;
    player.py = player.y;
    for (auto &m : monsters) {
        m.capturedBy = -1;
        m.hitStopTicks = 0;
        m.hitStopped = false;
    }
    captured_ = -1;
}
void World::idle(bool preserveExperimentalMovement) {
    clearPickupAction();
    player.sourceSkillCameraFeedback={};
    dashAttackGlide_.reset();
    clearBasicPlayback();
    clearSkillInputTransients();
    cancelSquirrelActions("idle_or_hit_interrupt");
    if(experimentalRuntime_) {
        if(preserveExperimentalMovement && player.hp>0 && !player.dead && player.life==ActorLife::Alive)
            experimentalRuntime_->interruptActionPreservingMovement();
        else experimentalRuntime_->cancel(ControllerCancelReason::ExplicitReset);
        player.animationPath.clear();
    }
    effects.erase(std::remove_if(effects.begin(), effects.end(), [](auto &e) { return e.attached; }),
                  effects.end());
    if (active_ >= 0 && skills[active_].id == 8)
        skillState_.startCooldown(skills[active_].identity(), nowMs(), activeCooldownMs_);
    if (captured_ >= 0)
        for (auto &m : monsters)
            if (m.id == captured_)
                m.capturedBy = -1;
    captured_ = -1;
    active_ = -1;
    activeCooldownMs_ = 0;
    actionInstance_ = 0;
    running_ = false;
    lastLeft_ = lastRight_ = -100000;
    goreCrossPhase_ = 0;
    goreCrossPhaseTick_ = -1;
    goreCrossEventEffect_ = -1;
    goreCrossEvents_.reset();
    stage_ = 0;
    queued_ = false;
    bufferedSkill_ = -1;
    player.poseFrame = -1;
    player.animation = "stay";
    player.animStart = nowMs();
    player.vx = player.vy = 0;
    hits_.clear();
    hitCounts_.clear();
    hopFinalHits_.clear();
}
bool World::tryPickupAction() {
    const auto reject=[&](const std::string &reason) {
        lastPickupActionTrace_={{"accepted",false},{"code",reason},{"policy","source-getitem-action-v1"},
            {"classification","source-binding-with-inferred-neutral-admission"},{"identity",identity_.json()}};
        return false;
    };
    if(pickupAction_||player.dead||player.life!=ActorLife::Alive||player.z!=0||player.vz!=0||
       player.recovery!=0||player.hitStopped||nowMs()<player.stunUntil||statusStunned(player.handle)||
       active_>=0||basicAttacking()||(experimentalRuntime_&&experimentalRuntime_->attacking())||
       (player.animation!="stay"&&player.animation!="move"&&player.animation!="dash"))return reject("pickup_actor_busy");
    try {
        PickupActionState prepared;
        prepared.path=characterSource().motion("[getitem motion]");
        const auto &appearance=characterAppearance();
        const auto *binding=appearanceBodyMotion(appearance,prepared.path);
        if(!binding)throw std::invalid_argument("Pick up has no exact own CHR appearance motion");
        const auto body=assets_.animation(prepared.path);
        if(body->frames.empty()||body->duration<=0)throw std::invalid_argument("Invalid own GetItem ANI duration");
        Json resources=Json::array();std::set<std::string> visited;
        const auto preflight=[&](const auto &self,const std::string &path,const std::array<int,2> &variation,bool isBody,size_t depth)->void {
            if(depth>12||visited.size()>=4096)throw std::length_error("Pickup visual source closure budget");
            const auto key=path+":"+std::to_string(variation[0])+":"+std::to_string(variation[1])+":"+std::to_string(isBody);
            if(!visited.insert(key).second)return;
            const auto animation=assets_.animation(path);
            if(animation->frames.empty())throw std::invalid_argument("Pickup source animation has no frames: "+path);
            for(const auto &frame:animation->frames)if(!frame.image.empty()) {
                const auto image=appearanceImage(frame.image,variation,isBody);
                if(image.find('%')!=std::string::npos)throw std::invalid_argument("Unresolved pickup IMG pattern: "+image);
                // A legitimate transparent 0x0 equipment frame is permitted.
                // Decoding still verifies existence/source bytes for every IMG.
                assets_.pixels(image,frame.imageFrame);
            }
            resources.push_back(makeSourceRef(pvf_,path).json());
            const auto events=animationEffectEvents(pvf_,assets_,path);
            if(!events.diagnostics.empty())throw std::invalid_argument("Unsupported pickup ALS: "+events.diagnostics.dump());
            for(const auto &event:events.events)if(event.kind!=EffectEventKind::Remove)
                self(self,event.animation,variation,isBody,depth+1);
        };
        preflight(preflight,prepared.path,{0,appearance.bodyVariation()},true,0);
        for(const auto &layer:appearance.orderedLayers()) {
            const auto path=appearanceLayerMotion(layer,*binding);
            if(!path.empty())preflight(preflight,path,layer.variation,false,0);
        }
        const auto installed=prepared.playback.install(*body,false,100,ani_clock::ClockPolicy::SourceDelay100,uint64_t(tick));
        prepared.source={{"accepted",true},{"policy","source-getitem-action-v1"},
            {"classification","current1031-source-with-inferred-neutral-admission"},{"identity",identity_.json()},
            {"body",makeSourceRef(pvf_,prepared.path).json()},{"duration_ms",body->duration},{"resources",resources},
            {"source_delays_unchanged",true},{"clock","fixed-tick source delay100; pickup has no attack-speed scaling"},
            {"damage_consumer",false},{"native_admission_parity",false}};
        auto trace=prepared.source;
        // Every fallible source preparation above precedes pose publication.
        // Clear pre-existing physical holds so pickup X cannot become an attack.
        idle();releaseInputs();pickupAction_=std::move(prepared);lastPickupActionTrace_=std::move(trace);
        player.animation="getitem";player.animationPath=pickupAction_->path;player.animStart=nowMs();
        player.poseFrame=-1;player.vx=player.vy=0;
        player.animationClock=installed.snapshot;player.animationClockSource=pickupAction_->path;
        events.push_back({tick,"pickup_action","source-getitem",identity_.jobId});
        return true;
    }catch(const std::exception &error){return reject(std::string("pickup_source_preflight_rejected: ")+error.what());}
}
void World::clearPickupAction() noexcept {
    if(!pickupAction_)return;
    const auto &path=pickupAction_->path;
    if(player.animationClockSource==path){player.animationClock.reset();player.animationClockSource.clear();}
    if(player.animationPath==path)player.animationPath.clear();
    if(player.animation=="getitem"){player.animation="stay";player.animStart=nowMs();player.poseFrame=-1;}
    pickupAction_.reset();
}
void World::advancePickupAction() {
    if(!pickupAction_)return;
    if(player.dead||player.life!=ActorLife::Alive||player.z!=0||player.recovery!=0||
       nowMs()<player.stunUntil||statusStunned(player.handle)) {clearPickupAction();return;}
    auto &action=*pickupAction_;
    const auto clock=action.playback.snapshot().lastTick<uint64_t(tick)?
        action.playback.advance(uint64_t(tick),player.hitStopped).snapshot:action.playback.snapshot();
    if(clock.ended){clearPickupAction();return;}
    player.animation="getitem";player.animationPath=action.path;player.poseFrame=-1;
    player.animationClock=clock;player.animationClockSource=action.path;
    player.animationControllerDelays.reset();player.skillAnimationLayers.clear();player.vx=player.vy=0;
}
void World::clearBasicPlayback() {
    basicPlayback_.clear(); basicFrameVisits_.clear();
    locomotionPlayback_.clear(); locomotionClockSource_.clear(); locomotionClockStart_=-1;
    player.animationClock.reset(); player.animationClockSource.clear();
    player.animationControllerDelays.reset();
    player.skillAnimationLayers.clear();
}
void World::configureAnimationClock(std::optional<ani_clock::ClockPolicy> policy) {
    if (policy == animationClockPolicy_) return;
    idle();
    animationClockPolicy_ = policy;
    if (experimentalRuntime_) experimentalRuntime_->setAnimationClockPolicy(policy);
}
void World::configureRenderProfile(ani_render::RenderProfile profile) {
    if(profile!=ani_render::RenderProfile::Legacy1031&&profile!=ani_render::RenderProfile::Inferred60Us1031)
        throw std::invalid_argument("Unknown World render profile");
    if(profile==renderProfile_)return;
    if(experimentalRuntime_&&experimentalRuntime_->attacking())
        throw std::invalid_argument("Render profile switch requires an idle action boundary");
    for(const auto &effect:effects)if(effect.phase=="female-gunner:ordinary_bullet"&&effect.expires>nowMs())
        throw std::invalid_argument("Render profile switch requires source projectiles to retire");
    renderProfile_=profile;
}
Json World::animationClockReport() const {
    return {{"policy", animationClockPolicy_ ? ani_clock::policyName(*animationClockPolicy_) : "legacy-scaled-local-age"},
        {"classification", animationClockPolicy_ ? "inferred" : "legacy"},
        {"arithmetic", ani_clock::arithmeticProfileName()}, {"simulation_hz", 60},
        {"source_rate_mapping", "attackPerMille truncated int32 Sani; install then refresh only on stat change"},
        {"equipment_binding", animationClockPolicy_ ? "root-elapsed-min-decoded-delays" : "body-index-or-local-age"},
        {"skill_stage_clock", "source-milliseconds-controller-reconstruction"},
        {"monster_object_clock", "independent-source-milliseconds"},
        {"effect_clock", animationClockPolicy_ ? "independent-source-rate100; follow-position/pause separate" : "legacy-born-offset"},
        {"als_events", animationClockPolicy_ ? "ordered-parent-frame-visits-add-remove-draw-only; actual-body-equipment-hosts" : "precompiled-source-timeline"},
        {"native_1031_clock_verified", false}, {"transient_restore", "cancel-on-scene-character-or-save-restore"}};
}
void World::installBasicPlayback() {
    clearBasicPlayback();
    if (!animationClockPolicy_) return;
    const double stat = speedAttributes_ ? speedAttributes_->attackPerMille :
        baseAttributes_ ? baseAttributes_->value(ChrAttribute::AttackSpeed) : 1000.0;
    if (!std::isfinite(stat) || stat < 1 || stat > INT32_MAX) throw std::invalid_argument("ANI attack speed stat outside positive int32");
    basicSpeedStat_ = int32_t(stat);
    const auto rate = *animationClockPolicy_ == ani_clock::ClockPolicy::SourceDelay100 ? 100.0f :
        ani_clock::resolveRate(basicSpeedStat_, ani_clock::RatePath::Installation);
    const auto path = actorAni();
    const auto installed = basicPlayback_.install(*assets_.animation(path), false, rate, *animationClockPolicy_, uint64_t(tick));
    player.animationClock = installed.snapshot; player.animationClockSource = path;
    basicFrameVisits_ = installed.visits; player.poseFrame = -1;
}
void World::advanceBasicPlayback(bool paused) {
    if (!animationClockPolicy_ || !basicAttacking() || active_ >= 0) return;
    if (!basicPlayback_.installed()) installBasicPlayback();
    const auto &previous = basicPlayback_.snapshot();
    if (previous.lastTick == uint64_t(tick)) return;
    const double stat = speedAttributes_ ? speedAttributes_->attackPerMille :
        baseAttributes_ ? baseAttributes_->value(ChrAttribute::AttackSpeed) : 1000.0;
    if (!std::isfinite(stat) || stat < 1 || stat > INT32_MAX) throw std::invalid_argument("ANI attack speed stat outside positive int32");
    if (!paused && *animationClockPolicy_ == ani_clock::ClockPolicy::Inferred60UsPercentDeadlines && int32_t(stat) != basicSpeedStat_) {
        basicPlayback_.setRate(ani_clock::resolveRate(int32_t(stat), ani_clock::RatePath::Refresh));
        basicSpeedStat_ = int32_t(stat);
    }
    if (!paused && !previous.ended && basicFrameVisits_.empty())
        basicFrameVisits_.push_back({previous.frame, previous.visit, previous.loopCount, previous.frameStartMs, previous.nextDeadlineMs});
    const auto advanced = basicPlayback_.advance(uint64_t(tick), paused);
    basicFrameVisits_.insert(basicFrameVisits_.end(), advanced.visits.begin(), advanced.visits.end());
    player.animationClock = advanced.snapshot; player.poseFrame = -1;
}
void World::advanceLocomotionPlayback() {
    const auto release = [&] {
        locomotionPlayback_.clear(); locomotionClockSource_.clear(); locomotionClockStart_=-1;
    };
    if (pickupAction_ || !animationClockPolicy_ || player.dead || player.life!=ActorLife::Alive || active_>=0 || basicAttacking() ||
        (experimentalRuntime_&&experimentalRuntime_->attacking()) || player.poseFrame>=0) {
        // Combat owns the published Actor snapshot. Discard only our dormant
        // cursor so returning to the same source cannot resume across a tick gap.
        release(); return;
    }
    const auto &motion=player.animation;
    if(motion!="stay"&&motion!="move"&&motion!="dash"&&motion!="jump"&&motion!="damage1"&&motion!="damage2"&&motion!="down"&&motion!="sit") {
        release(); return;
    }
    const auto path=actorAni();if(path.empty()){release();return;}
    const bool loop=motion=="stay"||motion=="move"||motion=="dash";
    const auto delta=int64_t(ani_clock::millisecondsAtTick(uint64_t(tick))-ani_clock::millisecondsAtTick(uint64_t(tick-1)));
    if(player.hitStopped&&locomotionPlayback_.installed()&&locomotionClockSource_==path&&
        player.animStart==locomotionClockStart_+delta)locomotionClockStart_=player.animStart;
    if(!locomotionPlayback_.installed()||locomotionClockSource_!=path||locomotionClockStart_!=player.animStart) {
        const auto installed=locomotionPlayback_.install(*assets_.animation(path),loop,100,ani_clock::ClockPolicy::SourceDelay100,uint64_t(tick));
        player.animationClock=installed.snapshot;locomotionClockSource_=path;locomotionClockStart_=player.animStart;
    } else if(locomotionPlayback_.snapshot().lastTick<uint64_t(tick)) {
        player.animationClock=locomotionPlayback_.advance(uint64_t(tick),player.hitStopped).snapshot;
        locomotionClockStart_=player.animStart;
    }
    player.animationClockSource=path;
    player.animationControllerDelays.reset();
    player.skillAnimationLayers.clear();
}
void World::enqueue(Input i) {
    if (i.key < 0 || i.key >= int(held_.size())) throw std::invalid_argument("Invalid logical input key");
    const auto target = FixedStepClock::targetTickForNanoseconds(i.ns);
    const auto sequence = inputs_.enqueue(target, i);
    inputLog_.push_back({{"ns", i.ns}, {"key", i.key}, {"down", i.down},
                        {"sequence", sequence}, {"target_tick", target}});
}
void World::advance(int64_t ns, size_t maxTicks) {
    if (tick < 0) throw std::invalid_argument("Negative simulation tick");
    FixedStepClock nextClock = clock_;
    // Compatibility with existing diagnostic fixtures that set public tick.
    // Runtime restore uses restoreSimulationCheckpoint instead.
    if (uint64_t(tick) != nextClock.tick()) {
        auto checkpoint = nextClock.snapshot();
        checkpoint["tick"] = uint64_t(tick);
        nextClock.restore(checkpoint);
    }
    nextClock.addNanoseconds(ns);
    clock_ = nextClock;
    attackVolumes.clear();
    size_t processed = 0;
    while (processed < maxTicks && clock_.pendingTicks()) {
        if (tick == std::numeric_limits<int64_t>::max() ||
            FixedStepClock::millisecondsAtTick(uint64_t(tick) + 1) > uint64_t(std::numeric_limits<int64_t>::max()))
            throw std::overflow_error("World simulation time overflow");
        if (beforeTick_) beforeTick_(*this);
        prepareSourceActionBoundary();
        prepareMonsterEventAiBoundary();
        clock_.popTick();
        attackVolumes.clear();
        synchronizeEntityHandles();
        tickOnce();
        if (objectTick_) objectTick_(*this);
        advanceSourceActions({uint64_t(tick),uint64_t(nowMs()),
            uint32_t(uint64_t(nowMs())-FixedStepClock::millisecondsAtTick(uint64_t(tick)-1))});
        synchronizeEntityHandles();
        ++processed;
    }
}
void World::advanceSingleTick() {
    advance(0,0); // Reconcile legacy fixtures' public tick before counting debt.
    const auto debt = clock_.accumulatedUnits();
    const auto missing = debt >= FixedStepClock::unitsPerTick ? 0 : FixedStepClock::unitsPerTick - debt;
    advance(int64_t((missing + FixedStepClock::frequency - 1) / FixedStepClock::frequency),1);
}
int64_t World::nowMs() const {
    if (tick < 0) throw std::invalid_argument("Negative simulation tick");
    const auto ms = FixedStepClock::millisecondsAtTick(uint64_t(tick));
    if (ms > uint64_t(std::numeric_limits<int64_t>::max())) throw std::overflow_error("World time overflow");
    return int64_t(ms);
}
int64_t World::simulationNanoseconds() const {
    if (tick < 0) throw std::invalid_argument("Negative simulation tick");
    const uint64_t seconds = uint64_t(tick) / FixedStepClock::frequency;
    const uint64_t units = clock_.accumulatedUnits();
    // Evaluate floor((tick * 1e9 + units) / 60) without either long product.
    const uint64_t fraction = ((uint64_t(tick) % FixedStepClock::frequency) * FixedStepClock::unitsPerTick +
                               units % FixedStepClock::frequency) / FixedStepClock::frequency;
    const uint64_t accumulated = units / FixedStepClock::frequency;
    const uint64_t maximum = uint64_t(std::numeric_limits<int64_t>::max());
    if (seconds > maximum / FixedStepClock::unitsPerTick)
        throw std::overflow_error("World nanosecond timestamp overflow");
    const uint64_t whole = seconds * FixedStepClock::unitsPerTick;
    if (accumulated > maximum - whole || fraction > maximum - whole - accumulated)
        throw std::overflow_error("World nanosecond timestamp overflow");
    return int64_t(whole + accumulated + fraction);
}
int World::nextEffectId() {
    if (!effectIds_.nextValue() || effectIds_.nextValue() > uint64_t(std::numeric_limits<int>::max()))
        throw std::overflow_error("Legacy effect identity storage exhausted");
    return int(effectIds_.next());
}
void World::synchronizeEntityHandles() {
    std::set<EntityHandle> present;
    auto attach = [&](Actor &actor) {
        if (actor.life == ActorLife::Removed) {
            if(actor.handle) statuses_.retireTarget(actor.handle,uint64_t(nowMs()),"removed_actor");
            entities_.retire(actor.handle);
            return;
        }
        if (!entities_.valid(actor.handle) || present.count(actor.handle)) actor.handle = entities_.create();
        present.insert(actor.handle);
    };
    attach(player);
    for (auto &actor : monsters) attach(actor);
    for (const auto handle : entities_.active()) if (!present.count(handle)) {
        statuses_.retireTarget(handle,uint64_t(nowMs()),"entity_retired");
        entities_.retire(handle);
    }
}
const Actor *World::resolveActor(EntityHandle handle) const {
    if (!entities_.valid(handle)) return nullptr;
    if (player.handle == handle && player.life != ActorLife::Removed) return &player;
    for (const auto &actor : monsters)
        if (actor.handle == handle && actor.life != ActorLife::Removed) return &actor;
    return nullptr;
}
Actor *World::resolveActor(EntityHandle handle) {
    synchronizeEntityHandles();
    return const_cast<Actor *>(static_cast<const World *>(this)->resolveActor(handle));
}
Json World::simulationCheckpoint() const {
    nowMs(); // Reject invalid legacy public tick assignments before capture.
    auto clock = clock_.snapshot();
    // Keep legacy diagnostics that directly assign tick serializable too.
    clock["tick"] = uint64_t(tick);
    const auto pending = inputs_.snapshot([](const Input &input) {
        return Json{{"ns", input.ns}, {"key", input.key}, {"down", input.down}};
    });
    Json out={{"schema", 1}, {"clock", clock}, {"ids", ids_.snapshot()}, {"effects", effectIds_.snapshot()},
            {"status_instance_ids",statuses_.instanceWatermark()},
            {"inputs", pending}, {"entities", entities_.snapshot()}, {"random", random_.snapshot()},
            {"restore_policy", "cancel-transient-actions-input-and-effect-instances-v1"}};
    if(player.handle && !player.dead) {
        auto status=statusCheckpoint(player.handle);
        if(!status.at("contacts").empty() || !status.at("active").empty()) {
            out["status_owner"]=player.handle.json();out["player_status"]=std::move(status);
            out["status_restore_policy"]="explicit-target-remap-stun-v1";
        }
    }
    out["source_monster_think"]=monsterActionAiCheckpoint();
    return out;
}
void World::validateCharacterRestoreCapacity(const Json &checkpoint) const {
    auto live=entities_;
    live.create(); // selectCharacter -> reset -> changeScene
    if(checkpoint.is_null()) return;
    EntityRegistry prepared;prepared.restore(checkpoint.at("entities"));
    prepared.mergeAllocationWatermark(live);
    prepared.retireAll();
    prepared.create(); // The selected character has no retained monsters.
}
void World::restoreSimulationCheckpoint(const Json &checkpoint) {
    if (!checkpoint.is_object() || checkpoint.at("schema") != 1 ||
        checkpoint.at("restore_policy") != "cancel-transient-actions-input-and-effect-instances-v1")
        throw std::invalid_argument("Unsupported World simulation checkpoint");
    FixedStepClock clock; clock.restore(checkpoint.at("clock"));
    if (clock.tick() > uint64_t(std::numeric_limits<int64_t>::max()) ||
        clock.milliseconds() > uint64_t(std::numeric_limits<int64_t>::max()))
        throw std::invalid_argument("World checkpoint time exceeds signed storage");
    SimulationIdSources ids; ids.restore(checkpoint.at("ids"));
    MonotonicIds effects; effects.restore(checkpoint.at("effects"));
    if (!effects.nextValue() || effects.nextValue() > uint64_t(std::numeric_limits<int>::max()) + 1)
        throw std::invalid_argument("World checkpoint effect ID exceeds legacy storage");
    SequencedCommandQueue<Input> inputs;
    inputs.restore(checkpoint.at("inputs"), [](const Json &value) {
        if (!value.at("ns").is_number_integer() || !value.at("key").is_number_integer() ||
            !value.at("down").is_boolean()) throw std::invalid_argument("Invalid saved input payload");
        Input input{value.at("ns").get<int64_t>(), value.at("key").get<int>(), value.at("down").get<bool>()};
        if (input.ns < 0 || input.key < 0 || input.key >= 512) throw std::invalid_argument("Invalid saved input value");
        return input;
    });
    RandomStreams random; random.restore(checkpoint.at("random"));
    EntityRegistry entities; entities.restore(checkpoint.at("entities"));
    entities.mergeAllocationWatermark(entities_);
    entities.retireAll();
    const auto playerHandle=entities.create();
    std::vector<EntityHandle> monsterHandles;
    for(const auto &actor:monsters)
        monsterHandles.push_back(actor.life==ActorLife::Removed?EntityHandle{}:entities.create());
    auto monsterThinkRestore=prepareMonsterActionAiRestore(checkpoint.value("source_monster_think",Json()));
    StatusHost statuses(pvf_.identity(),StunStatusPolicy::inferredFlatChanceStunV1());
    statuses.mergeInstanceWatermark(statuses_.instanceWatermark());
    if(checkpoint.contains("status_instance_ids")) statuses.mergeInstanceWatermark(checkpoint.at("status_instance_ids"));
    if(checkpoint.contains("player_status")) {
        if(checkpoint.at("status_restore_policy")!="explicit-target-remap-stun-v1")
            throw std::invalid_argument("Unknown status restoration policy");
        const auto &saved=checkpoint.at("player_status");
        if(checkpoint.contains("status_instance_ids")) {
            MonotonicIds global,bundle;
            global.restore(checkpoint.at("status_instance_ids"));bundle.restore(saved.at("instance_ids"));
            if(global.nextValue() && (!bundle.nextValue() || global.nextValue()<bundle.nextValue()))
                throw std::invalid_argument("Global status watermark is behind the player bundle");
        }
        statuses.mergeTarget(saved,EntityHandle::fromJson(checkpoint.at("status_owner")),playerHandle,
            clock.milliseconds(),saved.at("commit_generation").get<uint64_t>(),
            [this](const std::string &path){return pvf_.script(path);},
            [playerHandle](EntityHandle target){return target==playerHandle;});
    }
    // Current controllers/effects have no continuation serializer yet. Their
    // safe cancellation is explicit; no saved key edge is replayed as a fresh
    // skill, and old instance handles cannot target newly loaded actors.
    clearSceneTransients();
    clock_ = std::move(clock);
    tick = int64_t(clock_.tick());
    if(actHost_) actHost_->resetCancelledClock();
    ids_ = std::move(ids);
    effectIds_ = std::move(effects);
    inputs_ = std::move(inputs);
    inputs_.clear();
    random_ = std::move(random);
    entities_ = std::move(entities);
    statuses_=std::move(statuses);
    player.handle = playerHandle;
    for(size_t i=0;i<monsters.size();++i) monsters[i].handle=monsterHandles[i];
    publishMonsterActionAiRestore(std::move(monsterThinkRestore));
    objectAttackSerial_ = 0;
    player.animStart = nowMs();
}
int World::remainingCd(int idx) const {
    if (idx < 0 || idx >= int(skills.size()))
        return 0;
    return int(std::min<int64_t>(std::numeric_limits<int>::max(),
        skillState_.remainingCooldown(skills[idx].identity(), nowMs())));
}
bool World::armor() const {
    return (!player.dead&&player.life==ActorLife::Alive&&experimentalRuntime_&&experimentalRuntime_->sourceFrameSuperArmor())||
           (active_>=0&&skills[active_].stages[stage_].armor);
}
bool World::invincible() const {
    return nowMs() < guardUntil_ || captured_ >= 0 ||
           (active_ >= 0 && skills[active_].stages[stage_].invincible);
}
bool World::basicAttacking() const {
    return player.animation.rfind("attack", 0) == 0 ||
           player.animation == "dashattack" || player.animation == "jumpattack";
}
void World::requestHitStop(Actor &actor, double milliseconds, const std::string &source) {
    if (actor.dead || !std::isfinite(milliseconds) || milliseconds <= 0) return;
    // Source hit-pause values are interpreted as milliseconds here. The native
    // unit conversion and damager/attacker split have not been recovered.
    LocalPauseClock clock;
    clock.restore(actor.hitStopTicks, actor.hitStopped);
    clock.setCountdown(milliseconds);
    actor.hitStopTicks = clock.remainingTicks();
    actor.hitStopped = clock.frozen();
    events.push_back({tick, "hit_stop", source, 0, actor.id, actor.hitStopTicks});
}
void World::advanceHitStop(Actor &actor) {
    LocalPauseClock clock;
    clock.restore(actor.hitStopTicks, actor.hitStopped);
    actor.hitStopped = clock.advance(actor.dead);
    actor.hitStopTicks = clock.remainingTicks();
    if (!actor.hitStopped) return;
    const int64_t delta = nowMs() - int64_t(FixedStepClock::millisecondsAtTick(uint64_t(tick - 1)));
    actor.animStart += delta;
    if (actor.stunUntil > nowMs() - delta) actor.stunUntil += delta;
    if (actor.nextAttack > nowMs() - delta) actor.nextAttack += delta;
    if (actor.hitFlashUntil > nowMs() - delta) actor.hitFlashUntil += delta;
    if (&actor == &player) {
        stageStart_ += delta;
        for (auto &hit : hits_) hit.second += int(delta);
        for (auto &effect : effects) if (effect.attached) {
            effect.born += delta;
            // Character ALS hosts live until their owner retires them and use
            // INT64_MAX as that deadline. Hitstop must preserve this sentinel;
            // overflowing it would remove/recreate the host and replay frame0.
            const auto maximum = std::numeric_limits<int64_t>::max();
            effect.expires = effect.expires > maximum - delta ? maximum : effect.expires + delta;
        }
    }
}
const SkillCostResult &World::skillCosts(int index, bool command) const {
    if (index < 0 || index >= int(skills.size())) throw std::out_of_range("Skill cost index");
    const auto &skill = skills[index];
    if (!skill.sourceData) throw std::runtime_error("Skill cost requires source data");
    const auto &appearance = characterAppearance();
    const auto part = appearance.parts.find("[weapon]");
    int subtype = -1;
    const Field *selected = nullptr;
    size_t ordinal = 0, count = 0;
    if (part != appearance.parts.end()) {
        for (size_t n = 0; n < part->second.source.fields.size(); ++n) {
            const auto &field = part->second.source.fields[n];
            if (normalize(field.tag) == "[sub type]") { selected = &field; ordinal = n; ++count; }
        }
        if (count == 1 && selected->values.size() == 1 && selected->values[0].is_number_integer()) {
            const auto &value = selected->values[0];
            if (!(value.is_number_unsigned() && value.get<uint64_t>() > uint64_t(std::numeric_limits<int>::max()))) {
                const auto number = value.get<int64_t>();
                if (number >= 0 && number <= std::numeric_limits<int>::max()) subtype = int(number);
            }
        }
    }
    const std::string equipmentKey = std::to_string(subtype) + ":" + std::to_string(count) + ":" +
        (part == appearance.parts.end() ? std::string() : part->second.source.path);
    auto &cached = skillCostCache_[{index,command}];
    if (cached.source == skill.sourceData && cached.level == skill.level && cached.equipmentKey == equipmentKey)
        return cached.result;
    auto result = evaluateCharacterSkillCosts(*skill.sourceData, skill.level, characterSource(), subtype, command,
        {}, {}, inferred1031SkillCostAbsencePolicy());
    Json weapon = {{"kind", "equipped_weapon_subtype"}, {"subtype", subtype},
        {"source_field_count", count}, {"classification", "source_field_selection"},
        {"appearance", equippedAppearance_ ? "progression_equipment" : "diagnostic_equipment"}};
    if (selected && part != appearance.parts.end()) {
        weapon["source"] = makeSourceRef(pvf_, part->second.source.path, selected->offset, 0, ordinal, "common").json();
        weapon["authored_values"] = selected->values;
    }
    if (subtype < 0) weapon["reason"] = "No unique nonnegative integral EQU subtype; no category fallback";
    result.consumerDiagnostics.push_back(std::move(weapon));
    cached.source = skill.sourceData; cached.level = skill.level; cached.equipmentKey = equipmentKey;
    cached.result = std::move(result);
    return cached.result;
}
void World::activate(int i, bool command) {
    requestSkill(i,command,false);
}
void World::requestSkill(int i,bool command,bool afterCurrentAction) {
    if(pickupAction_){rejectSkillFeedback("pickup_action_busy");return;}
    if(experimentalRuntime_)return; // Experimental source configuration owns its independent activation path.
    if(i<0||i>=int(skills.size())){rejectSkillFeedback("empty_or_unavailable_skill");return;}
    if(player.dead||player.life!=ActorLife::Alive){bufferedDefaultSkill_.reset();return;}
    auto &s = skills[i];
    const auto fail=[&](const char *reason){rejectSkillFeedback(reason,s.identity());};
    if(statusStunned(player.handle)){fail("status_stunned");return;}
    if (active_ == i && s.continuation) {
        queued_ = true;
        return;
    }
    // Native base useSkill reads learned level at skill+59C and rejects
    // exactly zero (86D9D5..86D9F4). This is only that start gate, not the
    // complete protected qualification/MP/CD transaction. Continuation above
    // is an existing-stage request rather than another useSkill transaction.
    // Check before admitting any contact-pause input buffer as well.
    if(s.level==0){fail("unlearned_skill");return;}
    if (usesSourceGrowth() && hasLearningLedger()) {
        const auto eligibility=skillUseEligibility(s.identity());
        if (!eligibility.allowed()) {
            lastSkillLearningTrace_=eligibility.json();
            events.push_back({tick,"skill_level_blocked",s.key,0,0,s.id});
            fail("source_learning_qualification");
            return;
        }
    }
    if(nowMs()<player.stunUntil||player.recovery!=0){fail("actor_recovery_or_stun");return;}
    if(active_>=0&&!afterCurrentAction){fail("current_action_busy");return;}
    if(s.airOnly&&player.z<=0){fail("air_state_required");return;}
    if (s.id == 11) {
        if(player.animation!="dashattack"){fail("source_dash_state_required");return;}
        // Native CC52CB..CC5419 checks source "damh start frame" before
        // invoking useSkill(11,1,1,1). The current SD stores this as key/value
        // tokens rather than a bracket field. Do not invent a missing value.
        const auto parameters = pvf_.script("data/skill/swordman.sd");
        int startFrame = -1;
        for (size_t token = 0; token + 1 < parameters.tokens.size(); ++token) {
            const auto &key = parameters.tokens[token];
            const auto &value = parameters.tokens[token + 1];
            if (key["value"] == "damh start frame" && value["type"] == 2 && value["value"].is_number_integer()) {
                if (startFrame >= 0) throw std::runtime_error("Ambiguous damh start frame source");
                startFrame = value["value"].get<int>();
            }
        }
        const auto currentFrame = player.animationClock ? player.animationClock->frame :
            assets_.animation(actorAni())->frameAt(usesSourceGrowth() ? int64_t(basicLocalAge_) : nowMs() - player.animStart, false);
        if (startFrame < 0 || int(currentFrame) < startFrame)
            {fail("source_dash_frame_required");return;}
    }
    if(s.id!=17&&s.id!=16&&player.z>0){fail("ground_state_required");return;}
    if(!(freeCd||(debugOverrides_.enabled&&debugOverrides_.noCooldown))&&remainingCd(i)>0){fail("skill_cooldown");return;}
    const auto costs = skillCosts(i, command);
    lastSkillCostTrace_ = costs.json();
    lastSkillCostTrace_["request"] = {{"tick", tick}, {"command", command}, {"classification", "inferred_beta"}};
    if (!costs.consumeMp() || !costs.cooldownMs()) {
        events.push_back({tick, "skill_cost_blocked", s.key, 0, 0, s.id});
        fail("source_skill_cost_unavailable");
        return;
    }
    const int consumeMp = *costs.consumeMp();
    if (*costs.cooldownMs() > std::numeric_limits<int>::max() || *costs.cooldownMs() < 0) {
        events.push_back({tick, "skill_cost_blocked", s.key, 0, 0, s.id});
        fail("source_skill_cooldown_out_of_range");
        return;
    }
    const int cooldownMs = int(std::ceil(*costs.cooldownMs()));
    if(debugOverrides_.enabled&&debugOverrides_.mpLock&&consumeMp>player.maxMp){fail("skill_cost_exceeds_locked_mp");return;}
    if(player.mp<consumeMp&&!god&&!(debugOverrides_.enabled&&debugOverrides_.mpLock)){fail("insufficient_mp");return;}
    if(afterCurrentAction&&(active_>=0||basicAttacking())) {
        bufferedDefaultSkill_=BufferedDefaultSkill{s.identity(),active_>=0?actionInstance_:objectAttackSerial_,active_<0};
        events.push_back({tick,"skill_buffered",UserRequestedSkillFeedbackV1::bufferPolicy,0,0,s.id});
        return;
    }
    if (player.hitStopped) {
        // Preserve a skill pressed during an ordinary melee contact pause.
        // This 200ms buffer is controller policy, not a recovered cancel window;
        // normal eligibility is checked again when the pause ends.
        if (basicAttacking()) { bufferedSkill_ = i; bufferedSkillCommand_ = command; bufferedSkillUntil_ = nowMs() + 200; }
        return;
    }
    bufferedDefaultSkill_.reset();player.skillFailureFeedback={};
    player.mp = debugOverrides_.enabled && debugOverrides_.mpLock ? player.maxMp : std::max(0, player.mp - consumeMp);
    activeCooldownMs_ = cooldownMs;
    lastSkillCostTrace_["commit"] = {{"tick", tick}, {"consume_mp", consumeMp}, {"cooldown_ms", cooldownMs},
        {"cooldown_conversion", "ceil source milliseconds for integral runtime deadline"},
        {"cooldown_start", s.id == 8 ? "controller_exit" : "controller_start"}};
    if (s.id != 8)
        skillState_.startCooldown(s.identity(), nowMs(), cooldownMs);
    events.push_back({tick, "skill_cost", s.key, consumeMp, cooldownMs});
    active_ = i;
    skillPeakHeight_ = player.z;
    hopHeldMs_ = 0;
    stage_ = 0;
    queued_ = false;
    startStage(0);
}
void World::startStage(int n) {
    clearBasicPlayback();
    if(n==0){bufferedDefaultSkill_.reset();actionInstance_=ids_.actions.next();}
    objectAttackSerial_ = ids_.attacks.next();
    stage_ = n;
    stageStart_ = nowMs();
    lastAttackFrame_ = -1;
    hits_.clear();
    hitCounts_.clear();
    running_ = false;
    lastLeft_ = lastRight_ = -100000;
    hopFinalHits_.clear();
    player.poseFrame = 0;
    auto &s = skills[active_];
    if (s.id == 64) {
        goreCrossPhase_ = 0;
        goreCrossPhaseTick_ = -1;
        goreCrossEventEffect_ = -1;
        goreCrossEvents_.reset();
    }
    player.animation = s.stages[n].animation;
    player.animStart = stageStart_;
    events.push_back({tick, "stage", s.key + ":" + std::to_string(n), 0, 0, s.id});
    if (s.id == 65 && n == 1) {
        const auto data = s.sourceData->values("[static data]");
        const double amount = std::clamp(hopHeldMs_ / 200.0, 0.0, 1.0);
        auto endpoint = [&](size_t i, double fallback) { return i < data.size() ? data[i].get<double>() : fallback; };
        hopTravel_ = endpoint(2, 50) + amount * (endpoint(3, 200) - endpoint(2, 50));
        hopHeight_ = endpoint(4, 50) + amount * (endpoint(5, 120) - endpoint(4, 50));
        hopStartX_ = player.x;
        player.vz = 0;
        player.z = 0;
        // Source endpoints and frame contact are preserved. Mapping held time
        // to the internal scalar and this arc remain reconstruction policies.
        events.push_back({tick, "motion_policy", "hopsmash:hold-to-source-endpoints", 0, 0, hopHeldMs_});
    }
    if (s.id == 58 && n == 1) {
        for (auto &m : monsters)
            if (m.id == captured_) {
                m.z = 45;
                m.vz = 0;
                m.x = player.x + player.dir * 65;
                m.y = player.y;
            }
    }
    if (s.id == 16)
        player.vz = -560;
    stageEffects(-1);
}
void World::configureBasicAttackMovement(bool enabled) {
    if(basicAttacking()||active_>=0||(experimentalRuntime_&&experimentalRuntime_->attacking()))
        throw std::logic_error("Basic attack movement policy changes require an idle action boundary");
    if(experimentalRuntime_)experimentalRuntime_->setBasicAttackMovementEnabled(enabled);
    basicMovementPolicy_.enabled=enabled;dashAttackGlide_.reset();
}
void World::normalAttack() {
    if(pickupAction_)return;
    if(experimentalRuntime_) {
        CharacterActionRequest request;request.action=CharacterAction::BasicAttack;
        request.inputKey=4;request.inputDown=true;request.simulationMs=nowMs();
        experimentalRuntime_->request(request);return;
    }
    if (player.dead || nowMs() < player.stunUntil || statusStunned(player.handle))
        return;
    if (active_ >= 0) {
        if (skills[active_].id == 11 || skills[active_].id == 17)
            queued_ = true;
        return;
    }
    if (player.animation == "dashattack") {
        activate(3);
        return;
    }
    if (player.z > 0 && player.animation == "jumpattack") {
        activate(5);
        return;
    }
    if (player.animation.rfind("attack", 0) == 0) {
        queued_ = true;
        return;
    }
    // Native state14, not an old double-tap flag, selects state15. A new
    // descriptor event is required after returning to idle from an attack.
    const bool dashAttack = player.z == 0 && player.animation == "dash" && running_;
    std::optional<BasicAttackGlide> preparedGlide;
    if(dashAttack&&usesSourceGrowth()&&basicMovementPolicy_.enabled) {
        const auto clip=assets_.animation(characterSource().motion("[dashattack motion]"));
        const auto move=speedAttributes_?speedAttributes_->movePerMille/1000.0:baseAttributes_?baseAttributes_->value(ChrAttribute::MoveSpeed)/1000.0:1.0;
        const auto rate=speedAttributes_?speedAttributes_->attackPerMille:baseAttributes_?baseAttributes_->value(ChrAttribute::AttackSpeed):1000.0;
        const auto dx=player.dir,dy=int(held_[3])-int(held_[2]);
        const auto span=basicAttackMovementClipMs(*clip,rate,animationClockPolicy_);
        preparedGlide=BasicAttackGlide::begin(dx*runSpeed*move*(speedAttributes_?speedAttributes_->dashXRatio:1),
            dy*runSpeed*move*.65*(speedAttributes_?speedAttributes_->dashYRatio:1),span,basicMovementPolicy_);
    }
    actionInstance_ = ids_.actions.next();
    player.animation = player.z > 0 ? "jumpattack" : dashAttack ? "dashattack" : "attack1";
    running_ = false;
    lastLeft_ = lastRight_ = -100000;
    combo_ = 0;
    bufferedDefaultSkill_.reset();
    objectAttackSerial_ = ids_.attacks.next();
    player.animStart = nowMs();
    stageStart_ = nowMs();
    basicLocalAge_=0;
    basicClockMs_=nowMs();
    lastAttackFrame_ = -1;
    hits_.clear();
    hitCounts_.clear();
    hopFinalHits_.clear();
    player.poseFrame = 0;
    installBasicPlayback();
    dashAttackGlide_.reset();player.vx=player.vy=0;
    dashAttackGlide_.swap(preparedGlide);
    if(dashAttackGlide_) {
        events.push_back({tick,"basic_attack_movement","inferred-user-basic-attack-movement-v1"});
    }
    events.push_back({tick, "sound", "SM_ATK_01"});
}
bool World::matchCommand(int key) {
    if (key != 4 && key != 6 && key != 7)
        return false;
    if (active_ >= 0 && skills[active_].continuation && key == 6) {
        queued_ = true;
        return true;
    }
    int chosen = -1, best = -1;
    for (int i = 0; i < int(skills.size()); i++) {
        auto &sk = skills[i];
        if (sk.command.empty() || sk.id == 11 || sk.id == 17)
            continue;
        if (sk.airOnly != (player.z > 0))
            continue;
        std::vector<int> required;
        bool chord = false;
        for (auto &item : sk.command) {
            if (!item.is_string())
                continue;
            std::string v = item.get<std::string>();
            if (v == "&")
                chord = true;
            else if (v == "(LEFT)")
                required.push_back(player.dir > 0 ? 0 : 1);
            else if (v == "(RIGHT)")
                required.push_back(player.dir > 0 ? 1 : 0);
            else if (v == "(UP)")
                required.push_back(2);
            else if (v == "(DOWN)")
                required.push_back(3);
            else if (v == "(ATTACK)")
                required.push_back(4);
            else if (v == "(SKILL)")
                required.push_back(6);
            else if (v == "(BUFF)")
                required.push_back(7);
        }
        if (required.empty() || required.back() != key)
            continue;
        bool matches = true;
        if (chord) {
            for (size_t n = 0; n + 1 < required.size(); n++)
                if (!held_[required[n]])
                    matches = false;
        } else {
            int at = int(required.size()) - 1;
            for (auto it = commandHistory_.rbegin(); it != commandHistory_.rend() && at >= 0; it++) {
                if (nowMs() - it->first > 500)
                    break;
                if (it->second == required[at])
                    --at;
            }
            matches = at < 0;
        }
        if (matches && int(required.size()) > best) {
            chosen = i;
            best = int(required.size());
        }
    }
    if(chosen<0){if(key==6)rejectSkillFeedback("no_eligible_source_skill_command");return false;}
    const bool defaultZ=key==6&&skills[chosen].sourceData&&sourceBaseDefaultSkillCommand(*skills[chosen].sourceData,identity_.growtype);
    requestSkill(chosen,true,defaultZ);
    if(active_==chosen||(bufferedDefaultSkill_&&bufferedDefaultSkill_->skill==skills[chosen].identity())) {
        commandHistory_.clear();
        return true;
    }
    return false;
}
void World::input(const Input &in) {
    ids_.requests.next();
    // Physical KEYUP still reaches its controller owner. No fresh press can
    // queue an attack/skill or turn the owned pickup pose into locomotion.
    if(pickupAction_&&in.down)return;
    CharacterActionRequest request;
    request.inputKey = in.key;
    request.inputDown = in.down;
    request.horizontal = (in.key == 0 ? -1 : in.key == 1 ? 1 : 0);
    request.vertical = (in.key == 2 ? -1 : in.key == 3 ? 1 : 0);
    request.simulationMs = nowMs();
    if (in.key >= 0 && in.key <= 3) request.action = CharacterAction::Move;
    else if (in.key == 5) request.action = CharacterAction::Jump;
    else if (in.key == 4) request.action = player.z > 0 ? CharacterAction::JumpAttack :
        player.animation == "dash" ? CharacterAction::DashAttack : CharacterAction::BasicAttack;
    else if (in.key == 6) request.action = CharacterAction::CommandInput;
    else if (in.key == 7) {
        request.action = CharacterAction::Skill;
        const auto index=bindings[12];
        if (index>=0&&index<int(skills.size())) request.skill=skills[index].identity();
    } else if (in.key >= 20 && in.key < 20 + int(bindings.size())) {
        const int slot = in.key - 20;
        const int index = bindings[slot];
        if (index >= 0 && index < int(skills.size())) {
            request.action = CharacterAction::Skill;
            request.skill = skills[index].identity();
        } else request.action = CharacterAction::CommandInput;
    }
    const bool accepted = controller_ && controller_->request(request);
    if(!accepted) {
        events.push_back({tick,"controller_request_rejected",skillGateName(SkillGate::MissingImplementation)});
        if(in.down&&(in.key==6||in.key==7||(in.key>=20&&in.key<33)))rejectSkillFeedback("controller_skill_request_rejected",request.skill);
    }
}
void World::applyInput(const Input &in) {
    if (in.key < 0 || in.key >= 512)
        return;
    if(pickupAction_&&in.down)return;
    const bool wasHeld = held_[in.key];
    held_[in.key] = in.down;
    if (!in.down) {
        if ((in.key == 32 || in.key == 6 || in.key == 4 || in.key == 7) && active_ >= 0 &&
            skills[active_].id == 1)
            idle();
        return;
    }
    if(statusStunned(player.handle)) {
        if(in.key==6||in.key==7||(in.key>=20&&in.key<33))rejectSkillFeedback("status_stunned");return;
    }
    auto ms = nowMs();
    const bool canRequestDash = !wasHeld && active_ < 0 && !basicAttacking() && !player.hitStopped &&
                               !player.dead && player.z == 0 && ms >= player.stunUntil;
    commandHistory_.push_back({ms, in.key});
    while (!commandHistory_.empty() && ms - commandHistory_.front().first > 600)
        commandHistory_.pop_front();
    if (in.key == 0) {
        if (canRequestDash) {
            if (ms - lastLeft_ < 230) running_ = true;
            lastLeft_ = ms;
        }
        if (!player.hitStopped && ((active_ < 0 && !basicAttacking()) ||
                                  (active_ >= 0 && skills[active_].id == 8)))
            player.dir = -1;
    }
    if (in.key == 1) {
        if (canRequestDash) {
            if (ms - lastRight_ < 230) running_ = true;
            lastRight_ = ms;
        }
        if (!player.hitStopped && ((active_ < 0 && !basicAttacking()) ||
                                  (active_ >= 0 && skills[active_].id == 8)))
            player.dir = 1;
    }
    bool matched = matchCommand(in.key);
    if (in.key == 4 && !matched)
        normalAttack();
    if (in.key == 7 && !matched)
        activate(bindings[12]);
    if (in.key == 5 && active_ < 0 && !basicAttacking() && !player.hitStopped &&
        ms >= player.stunUntil && player.z == 0 && !player.dead) {
        player.vz = 430;
        player.z = 1;
        if (held_[3]) {
            double nx = player.x - player.dir * 36;
            if (canWalk(nx, player.y))
                player.x = nx;
            player.vz = 200;
        }
        player.animation = "jump";
        player.animStart = ms;
        player.poseFrame = -1;
        events.push_back({tick, "sound", held_[3] ? "SM_BACKSTEP" : "SM_JUMP"});
    }
    if (in.key >= 20 && in.key < 33)
        activate(bindings[in.key - 20]);
}
bool World::canWalk(double x, double y) const {
    return WalkGeometryView{mapWidth,walkRects,blockedRects,
        mapExplorationActive_ && (!mapExplorationGeometryAvailable_ || walkRects.empty())}.canWalk(x,y);
}
std::array<double, 2> World::nearestWalkable(double x, double y) const {
    return WalkGeometryView{mapWidth,walkRects,blockedRects,
        mapExplorationActive_ && (!mapExplorationGeometryAvailable_ || walkRects.empty())}.nearestWalkable(x,y);
}
void World::recoverPosition(Actor &a) {
    if(mapExplorationActive_ && (!mapExplorationGeometryAvailable_ || walkRects.empty())) return;
    if (canWalk(a.x, a.y)) return;
    auto p = nearestWalkable(a.x, a.y);
    events.push_back({tick, "position_recovery", "nearest source walk cell", a.id, 0,
                      int(std::lround(std::hypot(p[0] - a.x, p[1] - a.y)))});
    a.x = a.px = p[0]; a.y = a.py = p[1];
}
void World::initializeMonsterAttributes(Actor &actor,int resolvedLevel,const std::string &frozenPolicy,const std::string &combatPolicy) {
    if (!actor.sourceStats.is_object() || !actor.sourceStats.empty() || actor.dead || actor.life!=ActorLife::Alive || bool(actor.handle))
        throw std::invalid_argument("Monster attribute initialization requires a fresh detached living actor");
    const std::string selectedPolicy=frozenPolicy.empty() ?
        (usesSourceGrowth()?MonsterHpPolicy::inferredMobTableHpV1().id:"legacy-demo-v1") : frozenPolicy;
    if (selectedPolicy!="legacy-demo-v1" && selectedPolicy!=MonsterHpPolicy::inferredMobTableHpV1().id)
        throw std::invalid_argument("Unknown frozen monster HP policy: "+selectedPolicy);
    if (selectedPolicy=="legacy-demo-v1") {
        // main/legacy fixture owns the frozen historical DemoBalance values.
        // This adapter never recreates 65/240 or 2x/3x as source content.
        actor.sourceStats={{"policy","legacy-demo-v1"},{"classification","user_requested_demo_tuning"},
            {"level",resolvedLevel},{"hp",actor.maxHp},{"source_hp_applied",false}};
        return;
    }
    if (!usesSourceGrowth()) throw std::invalid_argument("Source monster HP requires the beta World rule profile");
    if (actor.monsterPath.empty()) throw std::invalid_argument("Source monster HP requires an explicit MOB path");
    const auto key=std::make_pair(normalize(actor.monsterPath),actor.boss);
    auto found=monsterAttributeSources_.find(key);
    if (found==monsterAttributeSources_.end())
        found=monsterAttributeSources_.emplace(key,readMonsterAttributeSource(pvf_,key.first,key.second)).first;
    const auto result=evaluateMonsterHp(found->second,resolvedLevel,actor.boss,MonsterHpPolicy::inferredMobTableHpV1());
    if (!result.usable()) throw std::runtime_error("Monster source HP initialization blocked: " + result.snapshot().dump());
    std::optional<MonsterCombatAttributes> combatAttributes;
    if(combatPolicy==MonsterCombatAttributePolicy::inferredMobCombatTableV1().id) {
        combatAttributes=evaluateMonsterCombatAttributes(found->second,resolvedLevel,actor.boss,
            MonsterCombatAttributePolicy::inferredMobCombatTableV1());
        if(!combatAttributes->usable()) throw std::runtime_error("Monster combat initialization blocked: "+combatAttributes->snapshot().dump());
    } else if(combatPolicy!="legacy-snapshot-damage-v1") throw std::invalid_argument("Unknown frozen monster combat policy: "+combatPolicy);
    Json receipt=result.snapshot();
    if(combatAttributes) receipt["combat"]=combatAttributes->snapshot();
    actor.hp=actor.maxHp=*result.hp;
    actor.sourceStats=std::move(receipt);
    actor.combatAttributes=std::move(combatAttributes);
}
void World::restoreMonsterAttributes(Actor &actor) {
    if(!actor.sourceStats.contains("combat")) { actor.combatAttributes.reset(); return; }
    if(!usesSourceGrowth() || actor.monsterPath.empty()) throw std::runtime_error("Frozen monster combat attributes require a beta source monster");
    const auto source=readMonsterAttributeSource(pvf_,normalize(actor.monsterPath),actor.boss);
    auto combatAttributes=restoreMonsterCombatAttributes(actor.sourceStats.at("combat"),source);
    if(!combatAttributes.usable() || combatAttributes.boss!=actor.boss ||
        !actor.sourceStats.contains("level") || actor.sourceStats.at("level")!=combatAttributes.level)
        throw std::runtime_error("Saved monster combat attributes conflict with their HP initialization receipt");
    actor.combatAttributes=std::move(combatAttributes);
}
std::shared_ptr<const MonsterMotion> World::monsterMotion(const Actor &actor, const std::string &state) const {
    if(mapExplorationActive_ && actor.monsterPath.empty()) {
        auto absent=std::make_shared<MonsterMotion>();
        absent->state=state;absent->error="Exploration actor has no explicit source MOB; no default motion is available";
        return absent;
    }
    const auto path = actor.monsterPath.empty() ? "monster/goblin/goblin.mob" : actor.monsterPath;
    const auto key = normalize(path) + "|" + state;
    auto found = monsterMotions_.find(key);
    if (found == monsterMotions_.end())
        found = monsterMotions_.emplace(key, compileMonsterMotion(pvf_, assets_, path, state)).first;
    if (state == actor.animation && !actor.animationPath.empty() &&
        (!found->second->valid() || found->second->base->path != normalize(actor.animationPath))) {
        const auto overrideKey = key + "|" + normalize(actor.animationPath);
        auto selected = monsterMotions_.find(overrideKey);
        if (selected == monsterMotions_.end())
            selected = monsterMotions_.emplace(overrideKey,
                compileMonsterAnimationForMob(pvf_, assets_, actor.monsterPath, actor.animationPath, state)).first;
        return selected->second;
    }
    return found->second;
}
std::string World::monsterAnimation(const Actor &actor, const std::string &tag) const {
    const auto motion = monsterMotion(actor, tag);
    return motion->valid() ? motion->base->path : "";
}
AttackResponse World::attackResponse(int skill, int phase) const {
    std::string key;
    switch (skill) {
    case 0: key = player.animation; break;
    case 46: key = "upperslash"; break;
    case 5: key = "hardattack"; break;
    case 8: key = "tripleslash" + std::to_string(phase + 1); break;
    case 11: key = "dashattackmultihit"; break;
    case 16: key = "ashenfork"; break;
    case 17: key = "jumpattack"; break;
    case 20: key = "normalwave"; break;
    case 58: key = phase == 0 ? "vaneslashtry" : "vaneslashsmash"; break;
    case 64: key = "gorecross1"; break;
    case 65: key = phase == 1 ? "hopsmashfinal" : "hopsmash"; break;
    case 77: key = "moonlightslash" + std::to_string(phase + 1); break;
    default: break;
    }
    AttackResponse out;
    out.source = "character/swordman/attackinfo/" + key + ".atk";
    if (skill == 58 && phase >= 2) out.source = "passiveobject/character/swordman/attackinfo/vaneslash.atk";
    if (skill == 64 && phase > 0) out.source = "passiveobject/character/swordman/attackinfo/gorecross.atk";
    if (skill == 65 && phase >= 2) out.source = "passiveobject/character/swordman/attackinfo/hopsmashsub.atk";
    if (skill == 20) out.source = "passiveobject/character/swordman/attackinfo/normalwave.atk";
    if (!pvf_.has(out.source)) return out;
    return characterAttackResponse(pvf_.script(out.source));
}
void World::beginDeath(Actor &actor) {
    if(&actor==&player){clearSkillInputTransients();clearPickupAction();}
    if (actor.life != ActorLife::Alive) return;
    if(actor.handle) statuses_.clearTarget(actor.handle,uint64_t(nowMs()),"death");
    actor.dead = true;
    actor.hitStopTicks = 0;
    actor.hitStopped = false;
    actor.hitReaction = {};
    actor.life = ActorLife::Dying;
    actor.deathStart = actor.lifeStart = nowMs();
    actor.deathPoseTime = std::max<int64_t>(0, nowMs() - actor.animStart);
    actor.deathAnchorX = actor.x; actor.deathAnchorY = actor.y; actor.deathHeight = actor.z;
    actor.deathLoop = actor.animation == "stay" || actor.animation == "move";
    actor.independentDeath = false; actor.deathFragments.clear();
    if (!actor.monsterPath.empty()) {
        const auto independent = monsterMotion(actor, "death");
        if (independent->valid()) {
            actor.independentDeath = true;
            actor.deathMotion = independent;
            actor.deathPoseTime = 0; actor.deathLoop = false;
            actor.deathDuration = int(std::ceil(independent->duration));
            actor.deathRoute = "last-action";
        } else {
            // Freeze the entire current composition, including attack variant
            // and ALS instances, before changing any living damage animation.
            actor.deathMotion = monsterMotion(actor, actor.animation);
            if (!actor.animationPath.empty() &&
                (!actor.deathMotion->valid() || actor.deathMotion->base->path != actor.animationPath))
                actor.deathMotion = compileMonsterAnimationForMob(pvf_, assets_, actor.monsterPath, actor.animationPath, actor.animation);
            actor.deathProfile = readMonsterDeathProfile(pvf_, assets_, actor.monsterPath);
            actor.deathRoute = "diagnostic-fade";
            actor.deathDuration = 450;
            // An explicit but invalid last action must not silently become a
            // shared death; retain the error and safely fade the frozen body.
            if (!independent->configured && actor.deathMotion->valid() && actor.deathProfile.valid) {
                try {
                    actor.deathBounds = monsterMotionBounds(assets_, *actor.deathMotion,
                        actor.deathPoseTime, actor.deathLoop, actor.dir);
                    actor.deathFragments = monsterDeathFragments(
                        random_.stream(RandomDomain::Particles, actor.handle.id).next(), actor.deathProfile,
                        actor.deathBounds, actor.deathHeight, actor.lastImpact);
                    actor.deathRoute = "shared-source-palette";
                    actor.deathDuration = monsterDeathBurstMs + monsterFragmentDisplayMs(actor.deathProfile);
                } catch (const std::exception &e) {
                    events.push_back({tick, "monster_visual_issue", e.what(), actor.id});
                }
            }
            if (independent->configured && !independent->valid())
                events.push_back({tick, "monster_visual_issue", independent->error, actor.id});
            if (!actor.deathProfile.valid && !independent->configured)
                events.push_back({tick, "monster_visual_issue", actor.deathProfile.issues.dump(), actor.id});
        }
        events.push_back({tick, "death_route", actor.deathRoute, actor.id, 0, actor.deathDuration});
    }
    actor.capturedBy = -1;
    actor.vx = actor.vy = 0;
    events.push_back({tick, "death_phase", "dying", actor.id});
    if (&actor != &player) events.push_back({tick, "killed", actor.monsterPath, 0, actor.id, actor.sourceId});
}
void World::advanceLife(Actor &actor) {
    if (!actor.dead) {
        actor.life = ActorLife::Alive; // F5/restored characters do not retain death rendering.
        actor.deathMotion.reset(); actor.deathFragments.clear(); actor.deathRoute.clear();
        actor.independentDeath = false; actor.deathProfile = {};
        return;
    }
    if (actor.life == ActorLife::Alive) beginDeath(actor);
    if (!actor.monsterPath.empty()) {
        const auto elapsed = nowMs() - actor.deathStart;
        if (elapsed >= actor.deathDuration) {
            if (actor.life != ActorLife::Removed) {
                actor.life = ActorLife::Removed; actor.lifeStart = nowMs();
                events.push_back({tick, "death_phase", "removed", actor.id});
            }
        } else if (!actor.independentDeath && actor.deathRoute == "shared-source-palette" &&
                   actor.life == ActorLife::Dying && elapsed >= monsterDeathBurstMs) {
            actor.life = ActorLife::DeathEffect; actor.lifeStart = actor.deathStart + monsterDeathBurstMs;
            events.push_back({tick, "death_phase", "effect", actor.id});
        }
        return;
    }
    if (actor.life == ActorLife::Dying && actor.z == 0 && nowMs() - actor.deathStart >= 180) {
        actor.life = ActorLife::DeathEffect;
        actor.lifeStart = nowMs();
        events.push_back({tick, "death_phase", "effect", actor.id});
    } else if (actor.life == ActorLife::DeathEffect && nowMs() - actor.lifeStart >= 320) {
        actor.life = ActorLife::Removed;
        actor.lifeStart = nowMs();
        events.push_back({tick, "death_phase", "removed", actor.id});
    }
}
void World::airMovement() {
    const int dx = int(held_[1]) - int(held_[0]), dy = int(held_[3]) - int(held_[2]);
    const double sourceMove=usesSourceGrowth()&&basicMovementPolicy_.enabled?
        (speedAttributes_?speedAttributes_->movePerMille/1000.0:baseAttributes_?baseAttributes_->value(ChrAttribute::MoveSpeed)/1000.0:1.0):1.0;
    player.vx = dx * walkSpeed * sourceMove;
    player.vy = dy * walkSpeed * 0.65 * sourceMove;
    const double nx = player.x + player.vx / 60, ny = player.y + player.vy / 60;
    if (canWalk(nx, player.y)) player.x = nx;
    if (canWalk(player.x, ny)) player.y = ny;
}
bool World::damage(Actor &m, int value, double launch, const std::string &cause,
                   int responseSkill, int phase, int direction, const ImpactContext &impact, bool meleeContact,
                   uint64_t attackInstance,uint32_t hitIndex,const CombatBox *contact) {
    CombatPipelineTrace pipeline;
    pipeline.requestedDamage=value;
    const auto reject=[&](CombatPipelineOutcome outcome) {
        pipeline.outcome=outcome;
        lastCombatPipelineTrace_=pipeline;
        return false;
    };
    pipeline.add(CombatPipelineStage::Qualification);
    if (m.dead)
        return reject(CombatPipelineOutcome::TargetDead);
    if(!explorationAllowsIncoming(m)) {
        events.push_back({tick,"damage_blocked","exploration_incoming_consumer_unavailable",0,m.id});
        return reject(CombatPipelineOutcome::QualificationRejected);
    }
    if (responseSkill < 0) { responseSkill = active_ >= 0 ? skills[active_].id : 0; phase = stage_; }
    pipeline.add(CombatPipelineStage::ResponseSelection);
    const auto response = attackResponse(responseSkill, phase);
    pipeline.add(CombatPipelineStage::AcceptancePreflight);
    auto acceptedEvent=prepareMonsterAcceptedHit(m,cause);
    if(!acceptedEvent.ready) {
        events.push_back({tick,"damage_blocked",acceptedEvent.error,0,m.id});
        return reject(CombatPipelineOutcome::AcceptancePreflightRejected);
    }
    pipeline.add(CombatPipelineStage::Damage);
    bool critical=false;
    if(usesSourceGrowth() && m.combatAttributes && cause!="diagnostic-fixture") {
        if(!combatAttributes_) throw std::runtime_error("Source damage needs prepared character combat attributes");
        const auto policy=DamageResolutionPolicy::inferredPveDamageV1(combatAttributes_->damageConstants);
        synchronizeEntityHandles();
        DamageRequest request;
        request.attacker=player.handle; request.target=m.handle;
        request.attackInstance=attackInstance?attackInstance:objectAttackSerial_?objectAttackSerial_:ids_.attacks.next();
        request.hitIndex=hitIndex;
        request.attackerStats=makeDamageCombatant(*combatAttributes_);
        request.targetStats=makeDamageCombatant(*m.combatAttributes,policy);
        request.attack=readAttackDamage(pvf_.script(response.source),AttackStatusConsumer::StunHostV1);
        request.skill=damageSkillModifiers(responseSkill,phase);
        if(request.attack.source.path.rfind("character/",0)==0) {
            request.contactRange=DamageContactRange::Melee;
            request.contactRangeSource={{"policy","inferred-body-attack-contact-range-v1"},{"classification","inferred_beta"},
                {"basis","Current root character-body type15 contact, distinct from spawned projectile/area entities"},{"attack",request.attack.source.path}};
        }
        const auto result=resolveActorContact(request,makeMonsterStatusResistances(*m.combatAttributes));
        lastDamageTrace_=result.snapshot();
        pipeline.add(CombatPipelineStage::StatusTransaction);
        if(!result.usable()) {
            events.push_back({tick,"damage_blocked","source_damage_inputs",0,m.id});
            return reject(CombatPipelineOutcome::DamageInputsUnavailable);
        }
        value=*result.hpDamage;
        critical=result.critical;
        if(result.missed) {
            events.push_back({tick,"miss",request.attack.source.path,0,m.id});
            return reject(CombatPipelineOutcome::Missed);
        }
    } else if(usesSourceGrowth() && cause!="diagnostic-fixture") {
        // Historical snapshots predate combat inputs. Keep their named legacy
        // rule and saved HP instead of deriving new values during restoration.
        value=legacySkillDamage(responseSkill,phase);
        lastDamageTrace_={{"policy","legacy-snapshot-damage-v1"},{"reason","saved actor has no frozen combat attributes"}};
    }
    const int acceptedHpLoss=std::min(m.hp,value);
    pipeline.add(CombatPipelineStage::HpCommit);
    m.hp = std::max(0, m.hp - value);
    if (!direction) direction = player.dir;
    const double sx = std::isfinite(impact.sourceX) ? impact.sourceX : player.x;
    const double sy = std::isfinite(impact.sourceY) ? impact.sourceY : player.y;
    const double speed = impact.travelSpeed > 0 ? impact.travelSpeed : std::hypot(player.vx, player.vy);
    m.lastImpact = monsterDeathImpulse(m.x - sx, m.y - sy, direction, speed, value, m.maxHp,
                                      response.push, std::max(response.lift, launch));
    m.hitFlashUntil = nowMs() + 80;
    if (m.hp == 0) beginDeath(m); // Freeze the lethal pose before changing hit animation.
    pipeline.add(CombatPipelineStage::DeathTransition);
    pipeline.add(CombatPipelineStage::HitStop);
    // 40JP sub_4E5DC0 consumes hit-info pause independently of the hurt
    // motion multiplier. Multiplying these froze the target for the wrong time.
    requestHitStop(m, response.hitPause, response.source);
    if (meleeContact) requestHitStop(player, response.hitPause, response.source);
    pipeline.add(CombatPipelineStage::Reaction);
    if (!m.dead) applyResponse(m, response, direction);
    // 40JP's reaction executor owns lift and hard-stun. A second controller
    // impulse after it would double-launch targets and bypass weight/height.
    applyMonsterHurtMotion(m, response);
    pipeline.add(CombatPipelineStage::Status);
    if (!m.dead) interruptStatusTarget(m);
    if (m.hp == 0) {
        m.stunUntil = nowMs() + 800;
    }
    pipeline.add(CombatPipelineStage::HitFeedback);
    events.push_back({tick, "hit", cause.empty() ? player.animation : cause, 0, m.id, value});
    publishMonsterHitFeedback(m,response,direction,value,identity_.jobId==0,contact,critical);
    pipeline.add(CombatPipelineStage::Notification);
    publishMonsterAcceptedHit(std::move(acceptedEvent),acceptedHpLoss);
    pipeline.outcome=CombatPipelineOutcome::Accepted;
    pipeline.lethal=m.dead;
    pipeline.acceptedDamage=acceptedHpLoss;
    lastCombatPipelineTrace_=pipeline;
    return true;
}
void World::diagnosticHit(int targetId, int value, int responseSkill, int phase,
                          int direction, const ImpactContext &impact) {
    synchronizeEntityHandles();
    for (auto &m : monsters) if (m.id == targetId) {
        damage(m, value, 0, "diagnostic-fixture", responseSkill, phase, direction, impact);
        return;
    }
}
void World::strike(const Box &b, int index) {
    attackVolumes.push_back({objectAttackSerial_,player.x,player.y,player.z,player.dir,
                             skillDamage(active_>=0?skills[active_].id:0,stage_),b});
    attackVolumes.back().skillId=active_>=0?skills[active_].id:0;
    attackVolumes.back().skillPhase=attackVolumes.back().skillId==65?
        (stage_==1 && index>=4?1:0):stage_;
    if (usesSourceGrowth()) {
        auto &volume=attackVolumes.back();
        volume.sourceAttack=readAttackDamage(pvf_.script(attackResponse(volume.skillId,volume.skillPhase).source));
        volume.sourceModifiers=damageSkillModifiers(volume.skillId,volume.skillPhase);
    }
    for (auto &m : monsters) {
        if (m.dead || !explorationAllowsIncoming(m))
            continue;
        if (active_ >= 0 && skills[active_].id == 58 && (stage_ != 0 || captured_ >= 0 ||
            (mapExplorationActive_ && !explorationConsumers_.at(m.handle).captureAllowed)))
            continue;
        bool multi = active_ >= 0 && skills[active_].id == 65;
        const bool hopFinal = multi && stage_ == 1 && index >= 4;
        if (hopFinal) {
            if (hopFinalHits_.count(m.id) || hitCounts_[m.id] >= 3) continue;
        } else if (hits_.count(m.id) &&
                   (!multi || nowMs() - hits_[m.id] < 120 || hitCounts_[m.id] >= 2)) continue;
        auto attack = combatBox(b, std::min(player.x, player.px), player.y, player.z, player.dir);
        // Existing X sweep remains a reconstruction policy, separate from
        // the confirmed instantaneous box intersection contract.
        attack.w += std::abs(player.x - player.px);
        bool overlap = false;
        CombatBox contact;
        const auto motion = monsterMotion(m, m.animation);
        if (!motion->valid()) continue;
        auto ma = motion->base;
        const auto motionTime = monsterMotionTime(*motion, nowMs() - m.animStart,
                                                 m.animation == "stay" || m.animation == "move");
        if (!ma->frames.empty())
            for (auto &hurt : ma->frames[ma->frameAt(motionTime, false)].boxes)
                if (hurt.type == 14) {
                    if (intersectCombatBoxes(attack, combatBox(hurt, m.x, m.y, m.z, m.dir), &contact)) {
                        overlap = true;
                        break;
                    }
                }
        if (!overlap)
            continue;
        hits_[m.id] = int(nowMs());
        hitCounts_[m.id]++;
        if (hopFinal) hopFinalHits_.insert(m.id);
        int skill = active_ >= 0 ? skills[active_].id : 0;
        double launch = skill == 46 ? 280 : skill == 58 ? 200 : 0;
        int dmg = skillDamage(skill, stage_);
        // Contact-speed proxy from authored reach / actual playback duration.
        // The native attack-speed-to-particle formula is not yet recovered.
        auto action = assets_.animation(actorAni());
        int playbackMs = action->duration;
        if (active_ >= 0) {
            const auto &current = skills[active_].stages[stage_];
            if (current.duration) playbackMs = current.duration;
            else if (skill == 20 && !action->frames.empty())
                playbackMs += skills[active_].casting - action->frames[0].duration;
        }
        const double contactSpeed = std::abs(b.w) * 1000.0 / std::max(1, playbackMs);
        // Body-stage indices are not ATK indices. The hop's frame-4 contact
        // changes to its final slash, whereas only the passive-owned wave uses
        // hopsmashsub. This switch is source/ANI-supported reconstruction.
        const int responsePhase = skill == 65 ? (stage_ == 1 && index >= 4 ? 1 : 0) : stage_;
        const bool accepted=damage(m,dmg,launch,skill==58?"vaneslash:capture":"",skill,responsePhase,player.dir,
            {player.x,player.y,std::hypot(player.vx,player.vy)+contactSpeed},index<200,
            objectAttackSerial_,uint32_t(hitCounts_[m.id]-1),&contact);
        if(accepted && !m.dead && skill==58 && stage_==0) { captured_=m.id;m.capturedBy=0; }
    }
}
void World::attackFrames(int64_t from, int64_t to) {
    const auto sourceMotion = readCharacterAttackMotion(assets_, characterAppearance(), actorAni());
    const auto &a = sourceMotion.body;
    int elapsed = 0;
    int id = active_ >= 0 ? skills[active_].id : 0;
    const bool clocked = active_ < 0 && basicPlayback_.installed() && player.animationClock.has_value();
    // Visits include every crossed short/zero frame. Holding the current frame
    // still checks new targets while the action's hit ledger prevents repeats.
    for (size_t i = 0; i < a->frames.size(); i++) {
        auto &f = a->frames[i];
        int delay = f.duration;
        if (id == 20 && i == 0 && delay >= 1000)
            delay = std::max(1, skills[active_].casting);
        int end = elapsed + delay;
        const auto visit = std::find_if(basicFrameVisits_.begin(), basicFrameVisits_.end(),
            [&](const auto &v) { return v.frame == i; });
        if (clocked ? (visit != basicFrameVisits_.end() || player.animationClock->frame == i) : (to >= elapsed && from < end)) {
            player.poseFrame = clocked ? -1 : int(i);
            if (int(i) > lastAttackFrame_) {
                lastAttackFrame_ = int(i);
                if (f.properties.contains("16"))
                    events.push_back({tick, "sound", f.properties["16"].get<std::string>()});
                stageEffects(int(i));
            }
            // Process the frame6 setter before this frame's collision volumes,
            // after any old-frame interval sample. Do not reset the ANI clock
            // or replay its earlier sounds/layers when the hit list is cleared.
            if (id == 64 && goreCrossPhase_ == 0 && i >= 6)
                updateGoreCross(int(i));
            std::vector<Box> boxes;
            if (clocked) {
                auto sample = *player.animationClock;
                if (visit != basicFrameVisits_.end() && sample.frame != i) {
                    sample.frame = i; sample.nextFrame = i + 1 < a->frames.size() ? i + 1 : i;
                    sample.elapsedMs = sample.frameStartMs = visit->startMs;
                    sample.nextDeadlineMs = visit->deadlineMs; sample.localMs = 0;
                    sample.spanMs = visit->deadlineMs - visit->startMs; sample.ended = false;
                }
                boxes = sourceMotion.boxesAt(sample);
            } else boxes = sourceMotion.boxesAt(i);
            for (const auto &b : boxes) strike(b, int(i));
            // These native-controller volumes are reconstructed, not source ANI boxes. Keep them explicit for
            // later PC replay comparison.
            if (id == 5 && i >= 3 && i <= 5)
                strike({15, -20, -20, 0, 160, 40, 110}, int(i));
            if (id == 8 && stage_ == 1 && i >= 1 && i <= 2)
                strike({15, -25, -25, 20, 130, 40, 70}, int(i));
            if (id == 17 && i >= 2 && i <= 3)
                strike({15, 13, -13, -11, 88, 26, 167}, int(i));
        }
        elapsed = end;
    }
    if (clocked) basicFrameVisits_.clear();
}
void World::stageEffects(int frame) {
    if (active_ < 0)
        return;
    int id = skills[active_].id;
    const auto first = effects.size();
    std::string prefix = "character/swordman/effect/animation/";
    auto add = [&](std::string path, double ox = 0, double oy = 0, bool attached = true, int life = 0) {
        if (!pvf_.has(path))
            return;
        auto ani = assets_.animation(path);
        addEffect(path, id, player.x + player.dir * ox, player.y + oy,
                  life ? life : std::max(1, ani->duration));
        auto &e = effects.back();
        e.attached = attached;
        e.parentId = attached ? 0 : -1;
        e.offsetX = ox;
        e.offsetY = oy;
        e.z = player.z;
    };
    if (frame == -1) {
        if (id == 5) {
            add(prefix + "hardattack1.ani");
            add(prefix + "hardattack2.ani");
            events.push_back({tick, "sound", "SM_GUE_ATK_01"});
        } else if (id == 8) {
            add(prefix + "tripleslash/slash" + std::to_string(stage_ + 1) + ".ani",
                stage_ == 0   ? -25
                : stage_ == 1 ? -22
                              : 0,
                stage_ == 0   ? 10
                : stage_ == 1 ? -25
                              : 0);
            add(prefix + "tripleslash/move1.ani", -70, -25);
            events.push_back({tick, "sound", "SM_TRIPLE" + std::to_string(stage_ + 1)});
        } else if (id == 77) {
            add(prefix + "moonlightslash" + std::to_string(stage_ + 1) + ".ani", stage_ == 0 ? -2 : -5,
                stage_ == 0 ? -20 : -35);
            events.push_back({tick, "sound", stage_ == 0 ? "MOON_ATK_01" : "MOON_ATK_02"});
        } else if (id == 58 && stage_ == 1) {
            add(prefix + "vaneslash/smash.ani");
            add(prefix + "vaneslash/dust.ani");
            add("passiveobject/character/swordman/animation/vaneslash.ani", 60, -30, false, 1430);
            auto &e = effects.back();
            e.z = 45;
            e.interval = 250;
            e.firstPulse = 350; // First original ANI attack box, frame 5.
            e.pulseWindow = 1000;
            auto data = pvf_.script(skills[active_].source).values("[static data]");
            e.maxPulses = data.size() > 1 ? data[1].get<int>() : 3;
        } else if (id == 46) {
            events.push_back({tick, "sound", "UPPER_SLASH_01"});
            events.push_back({tick, "sound", "SM_UPPER_SLASH"});
        } else if (id == 64) {
            // CD4A20 attaches all four sqr/common.nut bindings. Keep distinct
            // instances and source durations; state exit releases attachments.
            for (int index = 0; index < 4; ++index) {
                add(prefix + "gorecross/slash" + std::to_string(index + 1) + ".ani");
                effects.back().damageEnabled = false;
                effects.back().phase = "gorecross:attached-" + std::to_string(index);
                if (index == 1) goreCrossEventEffect_ = effects.back().id;
            }
        } else if (id == 65 && stage_ == 1) {
            add(prefix + "hopsmash/sword.ani");
            add(prefix + "hopsmash/smash.ani");
        } else if (id == 16) {
            add(prefix + "jumpattackhold.ani");
        } else if (id == 58 && stage_ == 0) {
            add(prefix + "vaneslash/upper.ani");
        }
        expandEffectLayers(first);
        return;
    }
    if (id == 46 && frame == 2) {
        add(prefix + "upperslash1.ani", 50, -30);
    }
    if (id == 25 && frame == 2) {
        events.push_back({tick, "sound", "SM_GHOST_KAZHAN"});
        effects.erase(std::remove_if(effects.begin(), effects.end(), [](auto &e) { return e.skill == 25; }),
                      effects.end());
        const std::string base = "passiveobject/character/swordman/animation/";
        const int appearMs = assets_.animation(base + "khazanareaappear2.ani")->duration;
        const int stayMs = std::max(appearMs + 1, int(skills[active_].parameter(1)));
        auto schedule = [&](const char *name, int delay, int life, bool loop, int layer, const char *phase) {
            add(base + name + ".ani", 80, 0, false, life);
            auto &fx = effects.back();
            fx.born += delay;
            fx.expires = fx.born + life;
            fx.loop = loop;
            fx.layer = layer;
            fx.damageEnabled = false;
            fx.phase = phase;
        };
        schedule("khazanareaappear1", 0, appearMs, false, -100, "khazan:appear");
        schedule("khazanareaappear2", 0, appearMs, false, -100, "khazan:appear");
        schedule("khazanareastay", appearMs, stayMs - appearMs, true, -100, "khazan:stay");
        schedule("khazan1", appearMs, stayMs - appearMs, true, 1, "khazan:ghost");
        schedule("khazan2", appearMs, stayMs - appearMs, true, 1, "khazan:ghost");
        schedule("khazanareadisappear", stayMs, assets_.animation(base + "khazanareadisappear.ani")->duration,
                 false, -100, "khazan:disappear");
    }
    if (id == 20 && frame == 4) {
        add(prefix + "normalwaveslash.ani");
        const auto object = pvf_.script("passiveobject/character/swordman/normalwave.obj");
        const auto path = effectResource(pvf_, object.path, object.text("[basic motion]"));
        addEffect(path, id, player.x + player.dir * 30, player.y,
                  assets_.animation(path)->duration, 500);
        effects.back().sourceObject = object.path;
        effects.back().phase = "normalwave:projectile";
        events.push_back({tick, "sound", "SM_WAVE"});
    }
    if (id == 58 && stage_ == 1 && frame == 5) {
        // SKL: downward slash is restricted to the captured enemy.
        for (auto &m : monsters)
            if (m.id == captured_ && !m.dead)
                damage(m, skillDamage(58, 1), 0, "vaneslash:downslash");
    }
    if (id == 65 && stage_ == 1 && frame == 4) {
        events.push_back({tick, "sound", "SM_BOONGSAN"});
        if (bloodVigorousLevel <= 0) { expandEffectLayers(first); return; }
        add("passiveobject/character/swordman/animation/hopsmashsubback1.ani", 123, 1, false);
        effects.back().z = 0;
        effects.back().layer = -100;
        effects.back().groundRender = true;
        effects.back().damageEnabled = false;
        add("passiveobject/character/swordman/animation/hopsmashsubback2.ani", 123, 1, false);
        effects.back().z = 0;
        effects.back().layer = -100;
        effects.back().groundRender = true;
        effects.back().damageEnabled = false;
        add("passiveobject/character/swordman/animation/hopsmashsubfront1.ani", 123, 1, false);
        effects.back().z = 0;
        effects.back().phase = "hopsmash:impact";
        effects.back().damageEnabled = true;
        effects.back().sourceObject = "passiveobject/character/swordman/hopsmashsub.obj";
    }
    expandEffectLayers(first);
}
void World::updateGoreCross(int bodyFrame) {
    if (active_ < 0 || skills[active_].id != 64 || player.hitStopped || goreCrossPhaseTick_ == tick) return;
    // Independent playback cursor for skill64 index1, not the body frame.
    for (const auto &effect : effects) if (effect.id == goreCrossEventEffect_) {
        const auto animation = assets_.animation(effect.animation);
        goreCrossEvents_.update(*animation, int(animation->frameAt(nowMs() - effect.born, false)));
        break;
    }
    // The native proc returns after each phase transition. Preserve that
    // separation instead of cascading multiple phases during one simulation tick.
    if (goreCrossPhase_ == 0) {
        if (bodyFrame >= 6) {
            // CD480A/CBCD9C both request protected selector(24). A nonnull
            // setATK goes through CB41F0..443350 and clears hit-object lists.
            // Exact selector translation remains unknown: retain the existing
            // explicit GoreCross1 reconstruction for BOTH body slashes.
            if (pvf_.has(attackResponse(64, 0).source)) {
                hits_.clear();
                hitCounts_.clear();
                objectAttackSerial_ = ids_.attacks.next();
                events.push_back({tick, "attack_reset", "gorecross:selector24-body-frame6", 0, 0, 24});
            }
            goreCrossPhase_ = 1;
            goreCrossPhaseTick_ = tick;
            events.push_back({tick, "skill_phase", "gorecross:second-slash", 0, 0, 1});
        }
        return;
    }
    if (goreCrossPhase_ == 1) {
        if (goreCrossEvents_.consume(1)) {
            goreCrossPhase_ = 2;
            goreCrossPhaseTick_ = tick;
            events.push_back({tick, "animation_event", "gorecross:skill64-layer1", 0, 0, 1});
        }
        return;
    }
    if (goreCrossPhase_ != 2) return;
    const auto first = effects.size();
    const auto &skill = skills[active_];
    const auto animation = assets_.animation(skill.effect);
    const auto trajectory = pvf_.script("character/swordman/particle/gorecross.ptl");
    const double speed = trajectory.number("[move variable 1]", 400);
    const int motionMs = int(trajectory.number("[changing term]", 280));
    // Current 1031 CBD44B..CBD499 uses object20028 and local XYZ(85,0,82)
    // for job0. PTL speed changes/full passive-object integration remain local
    // reconstruction; the source descriptor is not rewritten.
    addEffect(skill.effect, 64, player.x + player.dir * 85, player.y, animation->duration, speed);
    auto &projectile = effects.back();
    projectile.trajectoryMs = motionMs;
    projectile.trajectoryStartX = projectile.x;
    projectile.phase = "gorecross:projectile";
    projectile.z = 82;
    projectile.sourceObject = "passiveobject/character/swordman/gorecross.obj";
    goreCrossPhase_ = 3;
    goreCrossPhaseTick_ = tick;
    events.push_back({tick, "skill_phase", "gorecross:projectile", 0, 0, 3});
    // Sound scheduling here remains local until its native consumer is traced.
    events.push_back({tick, "sound", "GORECROSS_CROSS"});
    events.push_back({tick, "sound", "SM_GORECROSS"});
    expandEffectLayers(first);
}
void World::expandEffectLayers(size_t first) {
    if (animationClockPolicy_) {
        // ALS is now consumed by parent frame visits. Object-declared parallel
        // motions remain independent roots, without pre-expanding their ALS.
        const size_t count = effects.size();
        for (size_t index = first; index < count; ++index) {
            const auto root = effects[index];
            if (root.sourceObject.empty()) continue;
            const auto object = pvf_.script(root.sourceObject);
            for (const auto &field : object.fields) {
                if (field.tag != "[add object effect]" || field.values.empty() || !field.values[0].is_string()) continue;
                const auto path = effectResource(pvf_, object.path, field.values[0].get<std::string>());
                if (path.empty()) {
                    events.push_back({tick, "effect_diagnostic", "unresolved object effect: " + object.path, root.id});
                    continue;
                }
                Effect child = root;
                child.id = nextEffectId(); child.animation = path;
                child.sourceObject.clear(); child.resourceSource = object.path; child.sourceOffset = field.offset;
                child.damageEnabled = false; child.phase += ":object-layer";
                if (field.values.size() > 1 && field.values[1].is_number_integer()) child.layer += field.values[1].get<int>();
                child.playback.clear(); child.animationClock.reset(); child.clockBound = false; child.frameEvents.reset();
                effects.push_back(std::move(child));
            }
        }
        return;
    }
    // Copy before appending: vector growth must not invalidate a live root.
    const size_t last = effects.size();
    for (size_t index = first; index < last; ++index) {
        const auto root = effects[index];
        const auto plan = root.sourceObject.empty() ? animationEffectPlan(pvf_, assets_, root.animation)
                                                    : objectEffectPlan(pvf_, assets_, root.sourceObject);
        for (const auto &d : plan.diagnostics)
            events.push_back({tick, "effect_diagnostic", d.dump(), root.id});
        for (const auto &track : plan.tracks) {
            if (track.primary) {
                effects[index].resourceSource = track.source;
                effects[index].sourceOffset = track.sourceOffset;
                continue;
            }
            Effect child = root;
            child.id = nextEffectId();
            child.animation = track.animation;
            child.sourceObject.clear();
            child.resourceSource = track.source;
            child.sourceOffset = track.sourceOffset;
            child.born = root.born + track.begin;
            child.expires = std::min(root.expires, root.born + track.end);
            if (child.born >= child.expires) continue;
            child.layer += track.layer;
            child.damageEnabled = false;
            child.loop = false;
            child.hits.clear(); child.counts.clear();
            child.phase = root.skill == 64 ? "gorecross:normal-layer" : root.phase + ":source-layer";
            if (!child.attached && track.begin > 0) {
                const auto travel = root.trajectoryMs ? std::min(track.begin, root.trajectoryMs) : track.begin;
                child.x = child.px = root.x + root.speed * root.dir * travel / 1000.0;
                child.trajectoryStartX = child.x;
                if (root.trajectoryMs) child.trajectoryMs = std::max(0, root.trajectoryMs - track.begin);
            }
            effects.push_back(std::move(child));
        }
    }
}
void World::addEffect(const std::string &p, int skill, double x, double y, int duration, double speed) {
    if (!pvf_.has(p))
        return;
    Effect e;
    e.id = nextEffectId();
    e.skill = skill;
    e.animation = p;
    e.x = e.px = x;
    e.y = e.py = y;
    e.dir = player.dir;
    e.born = nowMs();
    e.expires = e.born + duration;
    e.speed = speed;
    e.interval = 100000;
    effects.push_back(e);
}
void World::synchronizeCharacterEffectHosts() {
    struct Binding {
        std::string key, path; int layer; bool body;
        bool independentSource = false, loop = false, inheritBodyRate = false;
    };
    std::vector<Binding> bindings;
    const auto &look = characterAppearance();
    const auto *body = appearanceBodyMotion(look, actorAni());
    const bool active = animationClockPolicy_ && !player.dead && player.life == ActorLife::Alive &&
        player.poseFrame < 0 && player.animationClock && body &&
        normalize(body->resource.path) == normalize(player.animationClockSource);
    std::shared_ptr<const Animation> bodyAnimation;
    if (active) {
        bodyAnimation = assets_.animation(body->resource.path);
        if (pvf_.has(body->resource.path + ".als")) bindings.push_back({"body", body->resource.path, 0, true});
        size_t ordinal = 0;
        for (const auto &layer : look.orderedLayers()) {
            const auto path = appearanceLayerMotion(layer, *body);
            const auto key = "equipment:" + layer.slot + ":" + layer.sourcePath + ":" + std::to_string(ordinal++);
            if (!path.empty() && pvf_.has(path + ".als"))
                bindings.push_back({key, path, layer.order - look.bodyOrder, false});
        }
        for (const auto &layer : player.skillAnimationLayers) {
            if (normalize(layer.bodyPath) != normalize(body->resource.path)) continue;
            const auto &path = layer.source.memberPath;
            if (!path.empty() && pvf_.has(path + ".als"))
                bindings.push_back({"skill-layer:" + path, path, layer.layer, false,
                    !layer.synchronizedToBody, layer.loop, layer.inheritBodyRate});
        }
    }
    const auto action = experimentalRuntime_ ? experimentalRuntime_->activeActionSequence() :
        basicAttacking() ? std::optional<uint64_t>(actionInstance_) : std::nullopt;
    // Retire before adding: descendants observe the expired host in the same
    // parent-before-child pass. Independent draw-only objects survive it.
    for (auto &host : effects) if (host.actorAnimationHost && nowMs() < host.expires) {
        const auto binding = std::find_if(bindings.begin(), bindings.end(), [&](const auto &candidate) {
            return candidate.key == host.actorHostKey && candidate.path == host.animation;
        });
        const bool reset = active && host.actorHostRootClock &&
            ((player.animationClock->rateRevision == host.actorHostRootClock->rateRevision &&
              player.animationClock->elapsedMs < host.actorHostRootClock->elapsedMs) ||
             player.animationClock->visit < host.actorHostRootClock->visit ||
             player.animationClock->policy != host.actorHostRootClock->policy);
        if (binding == bindings.end() || host.actorActionSequence != action || reset)
            host.expires = nowMs();
    }
    for (const auto &binding : bindings) {
        auto found = std::find_if(effects.begin(), effects.end(), [&](const auto &candidate) {
            return candidate.actorAnimationHost && nowMs() < candidate.expires &&
                candidate.actorHostKey == binding.key && candidate.animation == binding.path;
        });
        auto sampled = *player.animationClock;
        if (!binding.body) {
            const auto animation = assets_.animation(binding.path);
            if (binding.independentSource) {
                auto sourceClock = sampled;
                if(!binding.inheritBodyRate) {
                    sourceClock.ratePercent = 100; sourceClock.policy = ani_clock::ClockPolicy::SourceDelay100;
                    sourceClock.rateRevision = 1;
                }
                sampled = animation->followClock(*animation,sourceClock,binding.loop);
            } else sampled = animation->followClock(*bodyAnimation,sampled,sampled.loop,
                player.animationControllerDelays.get());
        }
        if (found == effects.end()) {
            if (effects.size() >= 4096) throw std::length_error("Character ALS host instance budget exhausted");
            Effect host;
            host.id = nextEffectId(); host.animation = binding.path;
            host.x = host.px = player.x; host.y = host.py = player.y; host.z = player.z; host.pz = player.pz;
            host.dir = player.dir; host.born = nowMs(); host.expires = std::numeric_limits<int64_t>::max();
            host.attached = true; host.parentId = 0; host.layer = binding.layer;
            host.loop = sampled.loop; host.damageEnabled = false; host.drawSelf = false; host.actorAnimationHost = true;
            host.actorHostKey = binding.key; host.actorActionSequence = action;
            host.actorHostRootClock = player.animationClock; host.actorHostClock = sampled;
            // Installation may already have crossed zero/short prefix frames.
            // Late equipment binding joins at the current frame, without
            // replaying an action's previous world-effect creation commands.
            host.actorHostFirstVisit = player.animationClock->elapsedMs <= 17 ? 1 : sampled.visit;
            host.phase = "character-als-host:" + binding.key;
            effects.push_back(std::move(host));
        } else {
            found->actorHostRootClock = player.animationClock; found->actorHostClock = sampled;
            found->layer = binding.layer;
            found->x = player.x; found->y = player.y; found->z = player.z; found->dir = player.dir;
        }
    }
}
void World::advanceEffectClocks() {
    if (!animationClockPolicy_&&std::none_of(effects.begin(),effects.end(),[](const auto &e){return !e.sourceTreePolicy.empty();})) return;
    synchronizeCharacterEffectHosts();
    // A bounded live-instance walk preserves parent-before-child order, also
    // for a child spawned on this tick. No vector references survive append.
    size_t processed = 0;
    for (size_t index = 0; index < effects.size(); ++index) {
        if (++processed > 4096) throw std::length_error("ANI effect instance budget exhausted");
        auto &effect = effects[index];
        if(!animationClockPolicy_&&effect.sourceTreePolicy.empty())continue;
        if (effect.alsParentId >= 0) {
            const auto parent = std::find_if(effects.begin(), effects.end(), [&](const auto &candidate) { return candidate.id == effect.alsParentId; });
            if (parent == effects.end() || nowMs() >= parent->expires) { effect.expires = nowMs(); continue; }
            effect.expires = std::min(effect.expires, parent->expires);
            if(effect.alsFollowParent) {
                effect.x=parent->x+parent->dir*effect.alsFollowOffset[0];
                effect.y=parent->y+effect.alsFollowOffset[1];effect.z=parent->z+effect.alsFollowOffset[2];effect.dir=parent->dir;
            } else if(effect.phase.rfind("female-gunner:",0)==0) {
                effect.x=parent->x;effect.y=parent->y;effect.z=parent->z;effect.dir=parent->dir;
            }
        }
        if (nowMs() < effect.born || nowMs() >= effect.expires) continue;
        // These legacy controller jumps have no recovered cursor setter.
        // Explicit fallback retains them, rather than ignoring their offset.
        if (effect.animationOffset || effect.clockOffsetFallback) {
            if (!effect.clockOffsetFallback) events.push_back({tick,"effect_diagnostic","explicit animation-offset instance retains legacy source clock",effect.id});
            effect.clockOffsetFallback=true;effect.animationClock.reset();effect.playback.clear();continue;
        }
        ani_clock::Advance advanced;
        const bool install = !effect.clockBound || effect.clockSource != effect.animation;
        if (install) {
            effect.pauseWithPlayer = effect.attached;
            if (!effect.actorAnimationHost) {
                const auto animation = assets_.animation(effect.animation);
                advanced = effect.playback.install(*animation, effect.loop, 100,
                    ani_clock::ClockPolicy::SourceDelay100, uint64_t(tick));
            }
            const auto path=normalize(effect.animation);
            const auto key = pvf_.identity()+":"+effect.sourceTreePolicy+":"+path;
            auto &plan = effectEventPlans_[key];
            if (!plan) plan = std::make_shared<EffectEventPlan>(animationEffectEvents(pvf_, assets_, path,effect.sourceTreePolicy));
            effect.frameEvents = plan;
            for (const auto &d : plan->diagnostics) events.push_back({tick, "effect_diagnostic", d.dump(), effect.id});
            effect.clockBound = true;
            effect.clockSource = effect.animation;
        } else if (!effect.actorAnimationHost && effect.playback.snapshot().lastTick < uint64_t(tick)) {
            advanced = effect.playback.advance(uint64_t(tick), effect.pauseWithPlayer && player.hitStopped);
        } else if (!effect.actorAnimationHost) advanced.snapshot = effect.playback.snapshot();
        if (effect.actorAnimationHost) {
            advanced.snapshot = *effect.actorHostClock;
            const auto &current = advanced.snapshot;
            // Snapshot.visit is the real owner cursor's event identity. Borrow
            // entered frames; never advance body/equipment a second time.
            uint64_t first = install ? effect.actorHostFirstVisit : effect.animationClock->visit + 1;
            if (!install && current.rateRevision != effect.animationClock->rateRevision) first = current.visit + 1;
            if (current.visit >= first) {
                if (current.visit - first >= 4096) throw std::length_error("Character ALS frame visit budget exhausted");
                const auto count = assets_.animation(effect.animation)->frames.size();
                for (auto visit = first; visit <= current.visit; ++visit) {
                    const auto backwards = current.visit - visit;
                    const auto frame = (current.frame + count - backwards % count) % count;
                    const auto loopsBack = (backwards + count - 1 - current.frame) / count;
                    const auto loop = current.loopCount >= loopsBack ? current.loopCount - loopsBack : 0;
                    advanced.visits.push_back({frame, visit, loop, 0, 0});
                }
            }
        }
        effect.animationClock = advanced.snapshot;
        const auto root = effect;
        if(root.alsParentId>=0 && root.phase.rfind("female-gunner:",0)==0) {
            const auto ani=assets_.animation(root.animation);
            for(const auto &visit:advanced.visits) {
                const auto &properties=ani->frames.at(visit.frame).properties;
                if(properties.contains("16")&&properties.at("16").is_string())
                    events.push_back({tick,"sound",properties.at("16").get<std::string>()});
            }
        }
        if (!root.frameEvents) continue;
        for (const auto &visit : advanced.visits) for (const auto &event : root.frameEvents->events) {
            if (size_t(event.frame) != visit.frame) continue;
            std::set<int> removed;
            // Ordinary draw-only is an independent world object. A repeated
            // uniqueName creates another instance; add/remove address only
            // the parent's attached ALS child binding.
            const bool drawOnly=event.kind==EffectEventKind::DrawOnly||event.kind==EffectEventKind::DrawOnlyFollowParent;
            if (!drawOnly)
                for (const auto &old : effects) if (old.alsParentId == root.id && old.alsInstance == event.instance) removed.insert(old.id);
            bool changed = true;
            while (changed) {
                changed = false;
                for (const auto &old : effects) if (removed.count(old.alsParentId) && removed.insert(old.id).second) changed = true;
            }
            for (auto &old : effects) if (removed.count(old.id)) old.expires = nowMs();
            events.push_back({tick, "als_event", Json{{"source",event.source},{"source_hash",event.sourceHash},
                {"offset",event.sourceOffset},{"source_order",event.sourceOrder},{"frame",event.frame},
                {"instance",event.instance},{"kind",event.kind == EffectEventKind::DrawOnlyFollowParent?"draw_only_follow_parent":event.kind == EffectEventKind::DrawOnly ? "draw_only" :
                    event.kind == EffectEventKind::Add ? "add" : "remove"},
                {"offset_xyz",{event.offsetX,event.offsetY,event.offsetZ}},
                {"visit",visit.visit},{"classification","inferred-live-parent-frame-dispatch"}}.dump(), root.id});
            if (event.kind == EffectEventKind::Remove) continue;
            if (root.alsDepth >= 12 || effects.size() >= 4096) {
                events.push_back({tick,"effect_diagnostic","ALS recursion/instance budget rejected",root.id});
                continue;
            }
            // Add time starts an independent source-rate100 clock. External
            // lifetime bounds the instance; ANI ended itself only holds pose.
            Effect child = root;
            child.id = nextEffectId(); child.animation = event.animation;
            child.alsFollowParent=false;child.alsFollowOffset={};
            // Image/auto-layer setters are separate source calls. Each
            // child explicitly selects its outer multiplier; ANI rate,
            // flip, pivot and world offsets remain source values.
            child.imageScale=root.autoLayerScale;child.autoLayerScale=root.autoLayerScale;
            if(root.sourceTreePolicy=="inferred-current1031-watercannon-tree-v1") {
                child.alsFollowParent=true;child.attached=false;child.parentId=-1;
                child.speed=child.vz=child.gravity=0;child.trajectoryMs=0;child.pauseWithPlayer=false;
            }
            child.born = nowMs(); child.px = child.x; child.py = child.y; child.pz = child.z;
            child.damageEnabled = false;
            child.loop = event.kind == EffectEventKind::Add && assets_.animation(event.animation)->globals.value("0",false);
            child.sourceObject.clear();
            child.groundRender = false;
            child.resourceSource = event.source; child.sourceOffset = event.sourceOffset;
            child.alsParentId = root.id; child.alsInstance = event.instance; child.alsDepth = root.alsDepth + 1;
            child.layer += event.layer; child.phase += ":als-live";
            child.playback.clear(); child.animationClock.reset(); child.clockBound = false; child.frameEvents.reset();
            child.hits.clear(); child.counts.clear(); child.animationOffset = 0;
            child.clockOffsetFallback=false;
            child.drawSelf = true; child.actorAnimationHost = false; child.actorHostKey.clear();
            child.actorActionSequence.reset(); child.actorHostRootClock.reset(); child.actorHostClock.reset();
            if (drawOnly) {
                child.x = child.px = root.x + root.dir * event.offsetX;
                child.y = child.py = root.y + event.offsetY;
                child.z = root.z + event.offsetZ; child.pz = child.z;
                child.attached = false; child.parentId = -1; child.alsParentId = -1;
                child.offsetX = child.offsetY = 0; child.speed = child.vz = child.gravity = 0;
                child.trajectoryMs = 0; child.trajectoryStartX = child.x; child.pauseWithPlayer = false;
                child.expires = nowMs() + std::max(1, assets_.animation(child.animation)->duration);
                child.phase = "als-draw-only:inferred-single-source-clip-lifetime";
                if(event.kind==EffectEventKind::DrawOnlyFollowParent) {
                    child.alsParentId=root.id;child.alsFollowParent=true;
                    child.alsFollowOffset={double(event.offsetX),double(event.offsetY),double(event.offsetZ)};
                    child.expires=std::min(child.expires,root.expires);
                    child.phase="source-watercannon:inferred-follow-tail-clip-or-parent-lifetime-v1";
                }
            }
            if(!drawOnly && !child.alsFollowParent&&!child.attached&&root.trajectoryMs>0) {
                child.trajectoryStartX=child.x;
                const auto travelled=std::clamp<int64_t>(nowMs()-root.born,0,root.trajectoryMs);
                child.trajectoryMs=root.trajectoryMs-int(travelled);
                if(!child.trajectoryMs)child.speed=0;
            }
            effects.push_back(std::move(child));
        }
    }
}
void World::tickOnce() {
    if (controller_) controller_->tick(int64_t(FixedStepClock::millisecondsAtTick(uint64_t(tick) + 1)));
    else simulateTick();
}
void World::simulateTick() {
    ++tick;
    auto ms = nowMs();
    advanceStatusEffects();
    const auto movementMs = int32_t(ms - int64_t(FixedStepClock::millisecondsAtTick(uint64_t(tick - 1))));
    player.px = player.x;
    player.py = player.y;
    player.pz = player.z;
    const bool wasPlayerHitStopped = player.hitStopped;
    if(player.dead||player.life!=ActorLife::Alive)clearSkillInputTransients();
    else if(bufferedDefaultSkill_&&(player.recovery!=0||ms<player.stunUntil||statusStunned(player.handle)||!ownsDefaultSkillBuffer()))
        bufferedDefaultSkill_.reset();
    advanceHitStop(player);
    for (auto &monster : monsters) advanceHitStop(monster);
    while (auto command = inputs_.popDue(uint64_t(tick))) input(command->payload);
    if (bufferedSkill_ >= 0 && !player.hitStopped) {
        const int next = bufferedSkill_;
        const bool command = bufferedSkillCommand_;
        bufferedSkill_ = -1;
        bufferedSkillCommand_ = false;
        if (ms <= bufferedSkillUntil_) activate(next, command);
    }
    if (wasPlayerHitStopped && !player.hitStopped && active_ >= 0 && skills[active_].id == 8) {
        // Triple Slash already accepts direction changes outside hitstop. Keep
        // a held turn received during the pause, without flipping frozen layers.
        const int direction = int(held_[1]) - int(held_[0]);
        if (direction) player.dir = direction;
    }
    for (auto &e : effects) {
        e.px = e.x;
        e.py = e.y;
        e.pz = e.z;
        if (e.attached && player.hitStopped) continue;
        if(e.gravity && ms>=e.born){e.z=std::max(0.0,e.z+e.vz/60.0);e.vz-=e.gravity/60.0;}
        if (identity_.jobId == 0 && e.skill == 58 && ms - e.born >= 1010) e.animationOffset = 9900;
        if (e.attached) {
            e.x = player.x + player.dir * e.offsetX;
            e.y = player.y + e.offsetY;
            e.z = player.z;
        } else if (ms >= e.born) {
            if (e.trajectoryMs > 0)
                e.x = e.trajectoryStartX + e.speed * e.dir * std::min<int64_t>(ms - e.born, e.trajectoryMs) / 1000.0;
            else e.x += e.speed * e.dir / 60.0;
        }
    }
    if (god) {
        player.hp = player.maxHp;
        player.mp = player.maxMp;
    }
    advanceLife(player);
    const bool ownedPickup=pickupAction_.has_value();
    // The experimental host requires consecutive ticks, including pickup.
    // Its blocked consumer preserves persistent modes while preventing attacks.
    if(experimentalRuntime_)experimentalAdapter_->advance(*experimentalRuntime_,uint64_t(tick));
    else if(!ownedPickup) {
    advanceBasicPlayback(player.dead || player.hitStopped || nowMs() < player.stunUntil || statusStunned(player.handle));
    bool attacking = active_ >= 0 || basicAttacking();
    if (!player.hitStopped && (player.z > 0 || player.vz > 0)) {
        // Native velocity/average-velocity integration; launch 430, gravity
        // 980 and the 60Hz caller remain explicitly reconstructed parameters.
        // CHR/provider mapping, native outer scheduling and landing are open.
        AxisMotion vertical{float(player.vz), -980, -1};
        player.z += advanceAxisMotion(vertical, movementMs);
        player.vz = vertical.velocity;
        if (player.z <= 0) {
            player.z = 0;
            player.vz = 0;
            if (active_ >= 0 && skills[active_].id == 16) {
                const auto source = pvf_.script("passiveobject/character/swordman/ashenforksub.obj");
                const auto staticData = skills[active_].sourceData->values("[static data]");
                const double required = staticData.empty() ? 50 : staticData[0].get<double>();
                if (skillPeakHeight_ >= required) {
                    const auto first = effects.size();
                    addEffect(skills[active_].effect, 16, player.x, player.y,
                              assets_.animation(skills[active_].effect)->duration);
                    effects.back().damageEnabled = false;
                    effects.back().layer = -100;
                    effects.back().groundRender = true;
                    effects.back().sourceObject = source.path;
                    effects.back().phase = "ashenfork:impact";
                    for (const auto &box : assets_.animation(skills[active_].effect)->frames.front().boxes)
                        if (box.type == 15) strike(box, 200);
                    for (const auto &ref : source.values("[etc motion]")) if (ref.is_string()) {
                        const auto path = effectResource(pvf_, source.path, ref.get<std::string>());
                        if (path.empty()) continue;
                        addEffect(path, 16, player.x, player.y, assets_.animation(path)->duration);
                        effects.back().damageEnabled = false;
                        effects.back().layer = path.find("dust") != std::string::npos ? -100 : 1;
                        effects.back().groundRender = path.find("dust") != std::string::npos;
                        effects.back().phase = "ashenfork:landing-layer";
                    }
                    expandEffectLayers(first);
                }
                finishPlayerAction();
            } else if (active_ < 0 && !attacking) {
                player.animation = "stay";
                player.animStart = ms;
            }
        }
    }
    if (!player.dead && !player.hitStopped && nowMs() >= player.stunUntil && !statusStunned(player.handle)) {
        if (active_ >= 0) {
            auto &s = skills[active_];
            auto &st = s.stages[stage_];
            int64_t elapsed = ms - stageStart_;
            auto a = assets_.animation(actorAni());
            const int duration = st.duration ? st.duration : a->duration;
            skillPeakHeight_ = std::max(skillPeakHeight_, player.z);
            if (s.id == 65 && stage_ == 0) {
                bool held = held_[6];
                for (size_t slot = 0; slot < bindings.size(); ++slot)
                    if (bindings[slot] == active_ && held_[20 + slot]) held = true;
                if(bindings[12]==active_&&held_[7])held=true;
                if (held) hopHeldMs_ = std::min(200, hopHeldMs_ + 17);
            }
            const double before = st.motion.distance(std::max<int64_t>(0,
                int64_t(FixedStepClock::millisecondsAtTick(uint64_t(tick - 1))) - stageStart_), duration, st.moveSpeed);
            const double after = st.motion.distance(elapsed, duration, st.moveSpeed);
            const double nx = player.x + (after - before) * player.dir;
            player.vx = st.motion.velocity(elapsed, duration, st.moveSpeed) * player.dir;
            if (canWalk(nx, player.y)) player.x = nx;
            if (s.id == 65 && stage_ == 1) {
                const double flight = 600; // Local ANI frame 4 contact marker.
                const double t = std::clamp(double(elapsed) / flight, 0.0, 1.0);
                const double smooth = t * t * (3 - 2 * t);
                const double candidate = hopStartX_ + player.dir * hopTravel_ * smooth;
                if (canWalk(candidate, player.y)) player.x = candidate;
                player.vx = player.dir * hopTravel_ * 6 * t * (1 - t) * 1000 / flight;
                player.z = 4 * hopHeight_ * t * (1 - t);
                player.vz = 0;
            }
            if (st.movement == MovementPolicy::AirControl && player.z > 0) airMovement();
            attackFrames(std::max<int64_t>(-1, elapsed - 17), elapsed);
            if (s.id == 64) updateGoreCross(int(a->frameAt(elapsed, false)));
            // Consume this tick's source frame/FX/boxes before committing the
            // requested next state. The 60US continuation proc accepts body
            // frame >=3; using it for 1031 is an explicit cross-version policy
            // (current 1031 clips each retain their five original DELAYs).
            if(s.id==8&&queued_&&stage_+1<int(s.stages.size())&&a->frameAt(elapsed,false)>=3) {
                events.push_back({tick,"skill_chain","inferred60us1031-tripleslash-frame3",stage_,stage_+1,3});
                queued_=false;startStage(stage_+1);
            } else if(s.id==65&&stage_==0&&elapsed>0&&[&] {
                bool held=held_[6]||(bindings[12]==active_&&held_[7]);
                for(size_t slot=0;slot<bindings.size();++slot)
                    if(bindings[slot]==active_&&held_[20+slot])held=true;
                return !held;
            }()) {
                events.push_back({tick,"skill_chain","source-hopsmash-command-release",0,1,hopHeldMs_});
                startStage(1);
            } else if (s.id == 1) {
                bool boundHeld = false;
                for (int n = 0; n < int(bindings.size()); n++)
                    if (bindings[n] == active_ && held_[20 + n]) boundHeld = true;
                if (!boundHeld && !held_[6] && !held_[4] && !held_[7])
                    finishPlayerAction();
            } else if (s.id == 16 && player.z > 0) {
            } else if (s.id == 64 && a->frameAt(elapsed, false) >= 10) {
                // CC60A4..CC6127: ordinary mode0 releases at body frame10;
                // the Berserker mode1 ANI-complete branch is not granted here.
                events.push_back({tick, "skill_exit", "gorecross:body-frame", 0, 0, 10});
                finishPlayerAction();
            } else if (!player.hitStopped && elapsed >= (st.duration ? st.duration
                                               : (s.id == 20 ? a->duration - a->frames[0].duration +
                                                                   std::max(1, s.casting)
                                                             : a->duration))) {
                if (stage_ + 1 < int(s.stages.size()) && (!s.continuation || queued_) &&
                    (s.id != 58 || captured_ >= 0)) {
                    queued_ = false;
                    startStage(stage_ + 1);
                } else
                    finishPlayerAction();
            }
        } else if (attacking) {
            if (player.animation == "jumpattack" && player.z > 0) airMovement();
            if(player.animation=="dashattack"&&dashAttackGlide_) {
                const auto movement=dashAttackGlide_->advance(movementMs);
                if(canWalk(player.x+movement[0],player.y))player.x+=movement[0];else dashAttackGlide_->blockX();
                if(canWalk(player.x,player.y+movement[1]))player.y+=movement[1];else dashAttackGlide_->blockY();
                player.vx=dashAttackGlide_->x.velocity;player.vy=dashAttackGlide_->y.velocity;
            }
            auto a = assets_.animation(actorAni());
            const double previousAge=basicLocalAge_;
            if(usesSourceGrowth() && !basicPlayback_.installed()) {
                const double rate=speedAttributes_ ? speedAttributes_->attackPerMille/1000.0 :
                    (baseAttributes_ ? baseAttributes_->value(ChrAttribute::AttackSpeed)/1000.0 : 1.0);
                basicLocalAge_+=std::max<int64_t>(0,ms-basicClockMs_)*rate;
            }
            int64_t elapsed = basicPlayback_.installed() ? int64_t(basicPlayback_.snapshot().elapsedMs) :
                usesSourceGrowth() ? int64_t(basicLocalAge_) : ms - player.animStart;
            attackFrames(usesSourceGrowth() ? (lastAttackFrame_<0 ? -1 : int64_t(previousAge)) : std::max<int64_t>(-1, elapsed - 17), elapsed);
            const auto &cancelFrames = characterSource().basicAttackCancelFrames;
            const bool ordinary = player.animation.rfind("attack", 0) == 0;
            const bool chainReady = ordinary && queued_ && player.z == 0 && combo_ >= 0 &&
                size_t(combo_) < cancelFrames.size() && int(basicPlayback_.installed() ? basicPlayback_.snapshot().frame :
                    a->frameAt(elapsed, false)) >= cancelFrames[combo_];
            const bool animationEnded = basicPlayback_.installed() ? basicPlayback_.snapshot().ended : elapsed >= a->duration;
            if (!player.hitStopped && (chainReady || animationEnded)) {
                if (chainReady) {
                    // Current native default: attackIndex indexes the cancel
                    // frame vector directly. Skill overrides, speed and the
                    // extra native +1A4 gate remain separate recovery work.
                    events.push_back({tick, "basic_chain", "native-default-frame", combo_, combo_ + 1, cancelFrames[combo_]});
                    ++combo_;
                    bufferedDefaultSkill_.reset();
                    objectAttackSerial_ = ids_.attacks.next();
                    const int direction = int(held_[1]) - int(held_[0]);
                    if (direction) player.dir = direction;
                    player.animation = "attack" + std::to_string(combo_ + 1);
                    player.animStart = ms;
                    basicLocalAge_=0;
                    player.poseFrame = 0;
                    installBasicPlayback();
                    lastAttackFrame_ = -1;
                    queued_ = false;
                    hits_.clear();
                    events.push_back({tick, "sound", "SM_ATK_0" + std::to_string(combo_ + 1)});
                    if (basicPlayback_.installed()) attackFrames(-1,0);
                } else {
                    finishPlayerAction();
                }
            }
        } else {
            int dx = int(held_[1]) - int(held_[0]), dy = int(held_[3]) - int(held_[2]);
            // Locomotion uses its own ANI clock, never a stale combat frame.
            player.poseFrame = -1;
            if (!dx)
                running_ = false;
            double speed = running_ ? runSpeed : walkSpeed;
            const double sourceMove=usesSourceGrowth() ? (speedAttributes_ ? speedAttributes_->movePerMille/1000.0 :
                baseAttributes_ ? baseAttributes_->value(ChrAttribute::MoveSpeed)/1000.0 : 1.0) : 1.0;
            speed*=sourceMove;
            const double dashX=running_&&speedAttributes_ ? speedAttributes_->dashXRatio : 1.0;
            const double dashY=running_&&speedAttributes_ ? speedAttributes_->dashYRatio : 1.0;
            double nx = player.x + dx * speed * dashX / 60, ny = player.y + dy * speed * dashY * 0.65 / 60;
            if (canWalk(nx, player.y))
                player.x = nx;
            if (canWalk(player.x, ny))
                player.y = ny;
            if (dx)
                player.dir = dx;
            player.vx = dx * speed * dashX;
            player.vy = dy * speed * dashY * 0.65;
            std::string next = player.z > 0 ? "jump" : dx || dy ? running_ ? "dash" : "move" : "stay";
            if (player.animation != next) {
                player.animation = next;
                player.animStart = ms;
            }
        }
    }
    } // Source experimental player updates above; retain shared world/monster lifecycle below.
    if(ownedPickup)advancePickupAction();
    advanceLocomotionPlayback();
    // Sample every attachment after the actor's movement for this tick. px/py
    // still preserve its preceding pose for render interpolation.
    for (auto &e : effects) if (e.attached) {
        e.x = player.x + player.dir * e.offsetX;
        e.y = player.y + e.offsetY;
        e.z = player.z;
        e.dir = player.dir;
    }
    for (auto &m : monsters) {
        m.px = m.x;
        m.py = m.y;
        m.pz = m.z;
        if (m.dead) { advanceLife(m); continue; }
        if (m.hitStopped) continue;
        if (!m.dead) recoverPosition(m);
        if (m.capturedBy >= 0) {
            m.hitReaction={};m.vx=m.vy=m.vz=0;
            if(experimentalAdapter_ && experimentalAdapter_->updateCapturedPose(m))continue;
            if(m.capturedBy>=0) {
                if(femaleGunnerWorld_ && femaleGunnerWorld_->updateCapturedPose(m))continue;
                m.x = player.x + player.dir * 65;
                m.y = player.y;
                m.z = 45;
                m.vz = 0;
                continue;
            }
        }
        if(!advanceMonsterHitReaction(m,movementMs)) {
        // Compatibility for historical saved actors without a reaction state.
        // New accepted hits use the 40JP state executor above.
        if (std::abs(m.vx) + std::abs(m.vy) > .1) {
            const double nx = m.x + m.vx / 60, ny = m.y + m.vy / 60;
            if (canWalk(nx, m.y)) m.x = nx; else m.vx = 0;
            if (canWalk(m.x, ny)) m.y = ny; else m.vy = 0;
            const double decay = m.recovery == 1 ? .93 : .86;
            m.vx *= decay; m.vy *= decay;
        } else m.vx = m.vy = 0;
        if (m.z > 0 || m.vz > 0) {
            AxisMotion vertical{float(m.vz), -980, -1};
            m.z += advanceAxisMotion(vertical, movementMs);
            m.vz = vertical.velocity;
            if (m.z <= 0) {
                m.z = m.vz = 0;
                if (!m.dead && m.recovery == 1) {
                    // Resolve the new MOB binding before publishing its state:
                    // animationPath still belongs to the airborne damage pose.
                    // Publishing first would treat it as a current-state override.
                    const auto motion = monsterMotion(m, "down");
                    m.recovery = 2; m.animation = "down"; m.animStart = ms;
                    m.animationPath = motion->valid() ? motion->base->path : "";
                    if (motion->valid())
                        m.animStart -= motion->base->duration - motion->base->frames.back().duration;
                    // Land on the last source down pose. Goblin/lugaru have
                    // 10000ms flight holds, not a 20-second grounded stun.
                    m.stunUntil = ms + (motion->valid() ?
                        std::clamp(motion->base->frames.back().duration, 150, 500) : 200);
                    if (!motion->valid()) events.push_back({tick, "monster_visual_issue", "Missing/invalid down motion", m.id});
                }
            }
        }
        }
        advanceLife(m);
        if (!m.dead && m.recovery >= 2 && ms >= m.stunUntil) {
            if (m.recovery == 2) {
                // Sit is the source crouched transition pose. Overturn is a
                // separate inverted/airborne entry, never a generic get-up.
                const auto motion = monsterMotion(m, "sit");
                m.recovery = 3;
                if (motion->valid()) {
                    m.animation = "sit"; m.animStart = ms;
                    m.animationPath = motion->base->path;
                }
                m.stunUntil = ms + (motion->valid() ? std::clamp(int(motion->duration), 100, 400) : 200);
                if (!motion->valid()) events.push_back({tick, "monster_visual_issue", "Missing/invalid sit recovery motion", m.id});
            } else { m.recovery = 0; m.animation = "stay"; m.animationPath.clear(); m.animStart = ms; }
        }
        if (m.recovery != 0 || m.hitReaction.state != 0) continue;
        if ((m.animation == "damage1" || m.animation == "damage2") && ms >= m.stunUntil) {
            m.animation = "stay"; m.animationPath.clear(); m.animStart = ms;
        }
        advanceMonsterSourceMovement(m,movementMs);
        if(actHost_ && (sourceActionActors_.count(m.handle) || actHost_->controlsMovement(m.handle)))
            continue; // Shared hit/grab recovery runs above; ACT replaces living AI.
        if(!explorationAllowsLegacyAi(m)) continue;
        if (m.dead || player.dead || !combat || freezeAi || (debugOverrides_.enabled && debugOverrides_.pauseAi) || ms < m.stunUntil || statusStunned(m.handle))
            continue;
        auto mob = pvf_.script(m.monsterPath);
        bool ranged = m.monsterPath.find("thrower") != std::string::npos;
        bool bull = m.monsterPath.find("/tau/") != std::string::npos;
        auto motion = [&](std::string tag) {
            return normalize(
                (std::filesystem::path(m.monsterPath).parent_path() / mob.text(tag)).generic_string());
        };
        if (m.animation == "attack1") {
            std::shared_ptr<const Animation> ani = assets_.animation(m.animationPath.empty() ? motion("[attack motion]") : m.animationPath);
            if (ranged && m.combatAttributes && !m.projectileDefinition) {
                auto prepared=prepareMonsterProjectile(m);
                if (!prepared.usable()) {
                    lastDamageTrace_=prepared.snapshot();
                    events.push_back({tick,"damage_blocked","source_projectile_inputs",m.id});
                    m.attackHit=true; m.animation="stay";m.animationPath.clear();m.animStart=ms;
                    continue;
                }
                m.projectileDefinition=std::make_shared<const MonsterProjectileDefinition>(std::move(prepared));
            }
            const auto *projectile=ranged && m.combatAttributes?m.projectileDefinition.get():nullptr;
            if (projectile) ani=projectile->throwMotion;
            int64_t elapsed = ms - m.animStart;
            int64_t headingContactMs=1190;
            if(bull && m.attackVariant==1 && usesSourceGrowth() && m.combatAttributes) {
                headingContactMs=0;
                for(const auto &frame:ani->frames) {
                    if(std::any_of(frame.boxes.begin(),frame.boxes.end(),[](const Box &box){return box.type==15;})) break;
                    headingContactMs+=frame.duration;
                }
            }
            if (bull && m.attackVariant == 1 && elapsed >= 300 && elapsed < headingContactMs) {
                // Heading trajectory is a controller calibration; animation/box timings stay original.
                MotionProfile charge{150,180};
                double dx=charge.velocity(elapsed-300,std::max<int64_t>(1,headingContactMs-300),330)*m.dir/60.0;
                if(usesSourceGrowth() && m.combatAttributes) {
                    // Inferred beta approach policy: do not run through a
                    // stationary target before the authored strike frame. The
                    // future strike's actual XYZ box only stops movement here;
                    // damage still waits for that source frame's real contact.
                    // This fixes the old charge calibration that overshot at
                    // every ordinary AI starting distance below 250 units.
                    bool reachable=false;
                    for(const auto &frame:ani->frames) {
                        bool strikeFrame=false;
                        for(const auto &box:frame.boxes) if(box.type==15) {
                            strikeFrame=true;
                            if(overlaps(m,box,player)) reachable=true;
                        }
                        if(strikeFrame) break;
                    }
                    if(reachable) dx=0;
                }
                if(canWalk(m.x+dx,m.y))m.x+=dx;
            }
            if (ranged && !m.attackHit && ani->frameAt(elapsed, false) >= (projectile?projectile->throwFrame:2)) {
                m.attackHit = true;
                Effect e;
                e.id = nextEffectId();
                e.skill = -1;
                e.hostile = true;
                e.hostileOwner=m.id;
                if(projectile) {
                    e.hostileAttack=projectile->attackPath;
                    e.hostileOwnerHandle=m.handle;
                    e.hostileStats=makeDamageCombatant(*m.combatAttributes,
                        DamageResolutionPolicy::inferredPveDamageV1(combatAttributes_->damageConstants));
                    e.attackInstance=ids_.attacks.next();
                    e.projectileSource=projectile->snapshot();
                    e.sourceObject=projectile->object.path;
                    e.resourceSource=projectile->motionParticle.path;
                    e.loop=projectile->loop;
                }
                e.animation = projectile?projectile->animation:"passiveobject/monster/goblin/animation/throwstone.ani";
                e.x = e.px = m.x + m.dir * (projectile?projectile->offsetX:20);
                e.y = e.py = m.y + (projectile?projectile->offsetY:0);
                e.z = projectile?projectile->offsetZ:60;
                e.dir = m.dir;
                e.speed = projectile?projectile->speed:250;
                e.born = ms;
                e.expires = ms + (projectile?projectile->lifetimeMs:1200);
                effects.push_back(e);
                events.push_back({tick, "sound", projectile?projectile->throwSound:"THROW_STONE", m.id});
                events.push_back({tick,"monster_projectile",e.sourceObject,m.id,e.id,projectile?projectile->objectId:0});
            }
            if (!ranged && !m.attackHit && !ani->frames.empty()) {
                for (auto &box : ani->frames[ani->frameAt(elapsed, false)].boxes)
                    if (box.type == 15 && overlaps(m, box, player)) {
                        m.attackHit = true;
                        hurtPlayer(m.boss ? 14 : 5,m.dir,&m);
                        break;
                    }
                // Tau Army Attack1 authors no type15 box. Explicit controller reach is
                // isolated here rather than manufacturing a box in its source ANI.
                if(bull && m.attackVariant==0 && !m.attackHit && elapsed>=520 && elapsed<700 &&
                   std::abs(player.x-m.x)<95 && std::abs(player.y-m.y)<34 && player.z<95 &&
                   (player.x-m.x)*m.dir>-20) {
                    m.attackHit=true;hurtPlayer(14,m.dir,&m);
                }
            }
            if (elapsed >= ani->duration) {
                m.animation = "stay";
                m.animationPath.clear();
                m.animStart = ms;
            }
            continue;
        }
        double dx = player.x - m.x, dy = player.y - m.y;
        m.dir = dx >= 0 ? 1 : -1;
        if (std::abs(dx) < (ranged ? 320 : bull ? 250 : 70) && std::abs(dy) < (ranged ? 30 : bull ? 35 : 24) && player.z < 80 &&
            ms >= m.nextAttack) {
            m.animation = "attack1";
            m.animStart = ms;
            m.attackHit = false;
            auto actions=mob.values("[attack motion]");
            m.attackVariant=bull&&actions.size()>1 ? (m.attackSerial++%2) : 0;
            m.projectileDefinition.reset();
            if(size_t(m.attackVariant)<actions.size() && actions[m.attackVariant].is_string())
                m.animationPath=normalize((std::filesystem::path(m.monsterPath).parent_path()/actions[m.attackVariant].get<std::string>()).generic_string());
            events.push_back({tick,"monster_attack",m.animationPath,m.id,0,m.attackVariant});
            m.nextAttack = ms + int(mob.number("[attack delay]", 1500));
        } else {
            const int level=m.combatAttributes?m.combatAttributes->level:m.sourceStats.value("level",1);
            const auto cacheKey=std::make_pair(m.monsterPath,level);
            auto cached=legacyMonsterMovementPlans_.find(cacheKey);
            if(cached==legacyMonsterMovementPlans_.end()) {
                auto plan=readMonsterSourceMovement(pvf_,mob,level,0,0);
                if(!plan.ready)events.push_back({tick,"monster_movement_issue",plan.evidence.dump(),m.id});
                cached=legacyMonsterMovementPlans_.emplace(cacheKey,std::move(plan)).first;
            }
            // Retain the existing attack reach, but use the same source-speed
            // and independent-axis stop consumer as source ACT monsters.
            const double stopX=ranged?180:50;
            const std::array<double,2> goal{std::abs(dx)>stopX?player.x-m.dir*stopX:m.x,
                std::abs(dy)>8?player.y-(dy>0?8:-8):m.y};
            const auto step=planMonsterMovement(cached->second,{m.x,m.y},goal,m.dir,movementMs,player.dir);
            const double oldX=m.x,oldY=m.y;
            if(canWalk(m.x+step.dx,m.y))m.x+=step.dx;
            if(canWalk(m.x,m.y+step.dy))m.y+=step.dy;
            const std::string next=std::abs(m.x-oldX)+std::abs(m.y-oldY)>1e-8?"move":"stay";
            if (m.animation != next) {
                m.animation = next;
                m.animationPath.clear();
                m.animStart = ms;
            }
        }
    }
    advanceEffectClocks();
    struct HostileHit {
        int direction,owner;
        std::string attack;
        EntityHandle ownerHandle;
        std::optional<DamageCombatant> frozenStats;
        uint64_t attackInstance;
    };
    std::vector<HostileHit> hostileHits;
    for (auto &e : effects) {
        if (ms < e.born || ms >= e.expires || !e.damageEnabled) continue;
        if (e.hostile) {
            Actor stone;
            stone.x = e.x;
            stone.y = e.y;
            stone.z = e.z;
            stone.dir = e.dir;
            bool contact=false;
            if (e.hostileStats) {
                auto animation=assets_.animation(e.animation);
                if (!animation->frames.empty())
                    for (const auto &box:animation->frames[e.animationClock ? e.animationClock->frame : animation->frameAt(ms-e.born,e.loop)].boxes)
                        if (box.type==15 && overlaps(stone,box,player)) { contact=true;break; }
            } else contact=overlaps(stone,Box{15,-5,-5,-5,10,10,10},player);
            if (contact) {
                e.expires = ms;
                hostileHits.push_back({e.dir,e.hostileOwner,e.hostileAttack,e.hostileOwnerHandle,e.hostileStats,e.attackInstance});
            }
            continue;
        }
        if (e.attached || (e.skill != 20 && e.skill != 64 && e.skill != 58 && e.skill != 65))
            continue;
        auto objectAni=assets_.animation(e.animation);
        bool pulse = e.skill == 58;
        if (pulse) {
            if (ms - e.born < e.firstPulse || ms - e.born >= e.pulseWindow || e.pulses >= e.maxPulses ||
                ms - e.born < e.firstPulse + e.pulses * e.interval) continue;
            ++e.pulses;
            events.push_back({tick, "pulse", "vaneslash", e.id, 0, e.pulses});
            // OBJ declares this normal-blend motion but not its controller
            // trigger. Synchronizing it with each accepted wave pulse is a
            // reconstruction; it must not expire before the first pulse.
            Effect normal = e;
            normal.id = nextEffectId();
            normal.animation = "passiveobject/character/swordman/animation/vaneslashnormal.ani";
            normal.born = ms; normal.expires = ms + assets_.animation(normal.animation)->duration;
            normal.px = normal.x; normal.py = normal.y; normal.animationOffset = 0;
            normal.damageEnabled = false; normal.loop = false; normal.layer = e.layer - 1;
            normal.phase = "vaneslash:pulse-normal-layer";
            normal.resourceSource = "passiveobject/character/swordman/vaneslash.obj";
            normal.sourceOffset = 67; normal.sourceObject.clear();
            normal.hits.clear(); normal.counts.clear();
            normal.playback.clear(); normal.animationClock.reset(); normal.clockBound=false; normal.frameEvents.reset();
            normal.alsParentId=-1; normal.alsDepth=0; normal.alsInstance.clear();
            pendingEffects_.push_back(std::move(normal));
        }
        // Objects share the accepted effect pulse cadence. Do not expose a
        // pre-pulse volume or an extra contact between periodic wave pulses.
        if(!objectAni->frames.empty())for(const auto &box:objectAni->frames[e.animationClock ? e.animationClock->frame : objectAni->frameAt(ms-e.born,e.loop)].boxes)
            if(box.type==15) {
                attackVolumes.push_back({(uint64_t(1)<<63)|uint64_t(e.id),e.x,e.y,e.z,e.dir,
                                         skillDamage(e.skill,1),box,uint64_t(e.pulses)});
                attackVolumes.back().skillId=e.skill;
                attackVolumes.back().skillPhase=e.skill==58 || e.skill==65?2:e.skill==64?1:0;
                if (usesSourceGrowth()) {
                    auto &volume=attackVolumes.back();
                    volume.sourceAttack=readAttackDamage(pvf_.script(attackResponse(volume.skillId,volume.skillPhase).source));
                    volume.sourceModifiers=damageSkillModifiers(volume.skillId,volume.skillPhase);
                }
            }
        for (auto &m : monsters) {
            if (m.dead || !explorationAllowsIncoming(m))
                continue;
            CombatBox contact;
            {
                Actor origin;
                origin.x = e.x;
                origin.y = e.y;
                origin.z = e.z;
                origin.dir = e.dir;
                bool hit = false;
                for (const auto &box : objectAni->frames[e.animationClock ? e.animationClock->frame : objectAni->frameAt(ms - e.born, e.loop)].boxes)
                    if (box.type == 15 && overlaps(origin, box, m, &contact)) {
                        hit = true;break;
                    }
                if (!hit)
                    continue;
            }
            auto it = e.hits.find(m.id);
            if (it != e.hits.end() && ms - it->second < e.interval)
                continue;
            e.hits[m.id] = ms;
            if (e.maxPulses && e.counts[m.id] >= e.maxPulses)
                continue;
            e.counts[m.id]++;
            damage(m, skillDamage(e.skill, e.skill == 58 ? 2 : e.skill == 64 || e.skill == 65 ? 1 : 0),
                   0, pulse ? "vaneslash:pulse" : e.skill == 64 ? "gorecross:blood" :
                   e.skill == 65 ? "hopsmash:impact" : "", e.skill,
                   e.skill == 58 || e.skill == 65 ? 2 : e.skill == 64 ? 1 : 0, e.dir,
                   // A projectile can overlap after its center has passed the
                   // victim: use incoming travel direction, never a reversed
                   // victim-minus-projectile-center vector. Stationary waves
                   // and explosions retain their radial ground-plane origin.
                   {std::abs(e.speed) > .01 ? m.x - e.dir * (e.speed > 0 ? 1 : -1) : e.x,
                    std::abs(e.speed) > .01 ? m.y : e.y, std::hypot(e.speed, e.vz)},false,
                   (uint64_t(1)<<63)|uint64_t(e.id),uint32_t(e.pulses),&contact);
        }
    }
    // Damage can interrupt a skill and erase attached effects. Apply only after
    // the iteration, so no references/iterators can be invalidated by idle().
    for (const auto &hit : hostileHits) {
        const Actor *attacker=nullptr;
        for(const auto &monster:monsters)
            if(monster.id==hit.owner && (!hit.ownerHandle || monster.handle==hit.ownerHandle)) attacker=&monster;
        hurtPlayer(8,hit.direction,attacker,hit.attack,hit.frozenStats?&*hit.frozenStats:nullptr,hit.ownerHandle,hit.attackInstance);
    }
    if (animationClockPolicy_||std::any_of(effects.begin(),effects.end(),[](const auto &e){return !e.sourceTreePolicy.empty();})) {
        bool changed = true;
        while (changed) {
            changed = false;
            for (auto &e : effects) if ((animationClockPolicy_||!e.sourceTreePolicy.empty())&&e.alsParentId >= 0 && ms < e.expires) {
                const auto parent = std::find_if(effects.begin(), effects.end(), [&](const auto &candidate) { return candidate.id == e.alsParentId; });
                if (parent == effects.end() || ms >= parent->expires) { e.expires = ms; changed = true; }
            }
        }
    }
    effects.erase(std::remove_if(effects.begin(), effects.end(), [&](auto &e) { return ms >= e.expires; }),
                  effects.end());
    effects.insert(effects.end(), pendingEffects_.begin(), pendingEffects_.end());
    pendingEffects_.clear();
    basicClockMs_=ms;
}
bool World::overlaps(const Actor &source, const Box &b, const Actor &target, CombatBox *contact) const {
    const auto attack = combatBox(b, source.x, source.y, source.z, source.dir);
    std::shared_ptr<Animation> animation;
    double elapsed = nowMs() - target.animStart;
    const bool loop = target.animation == "stay" || target.animation == "move";
    if (target.monsterPath.empty()) {
        animation = assets_.animation(target.animationPath.empty() ?
            characterSource().motionByStem(target.animation) : target.animationPath);
        if(&target==&player && usesSourceGrowth() && basicAttacking()) elapsed=basicLocalAge_;
    } else {
        const auto motion = monsterMotion(target, target.animation);
        if (!motion->valid()) return false;
        // Body collision samples the same selected base motion/time as the
        // visual plan. Effect/ALS sublayers do not manufacture body hurtboxes.
        animation = motion->base;
        elapsed = monsterMotionTime(*motion, elapsed, loop);
    }
    if (animation->frames.empty()) return false;
    const auto hurtFrame = target.animationClock && target.animationClockSource == animation->path ?
        target.animationClock->frame : animation->frameAt(int64_t(elapsed), false);
    for (const auto &h : animation->frames.at(hurtFrame).boxes)
        if (h.type == 14) {
            if (intersectCombatBoxes(attack, combatBox(h, target.x, target.y, target.z, target.dir), contact))
                return true;
        }
    return false;
}
void World::hurtPlayer(int value,int dir,const Actor *attacker,const std::string &attackPath,
    const DamageCombatant *frozenAttacker,EntityHandle frozenOwner,uint64_t attackInstance) {
    if (player.dead || invincible())
        return;
    if(usesSourceGrowth() && (frozenAttacker || (attacker && attacker->combatAttributes))) {
        if(!combatAttributes_) throw std::runtime_error("Source incoming damage needs prepared character combat attributes");
        const auto policy=DamageResolutionPolicy::inferredPveDamageV1(combatAttributes_->damageConstants);
        DamageRequest request; request.attacker=frozenAttacker?frozenOwner:attacker->handle; request.target=player.handle;
        request.attackInstance=attackInstance?attackInstance:ids_.attacks.next();
        request.attackerStats=frozenAttacker?*frozenAttacker:makeDamageCombatant(*attacker->combatAttributes,policy);
        request.targetStats=makeDamageCombatant(*combatAttributes_);
        if (frozenAttacker && attackPath.empty()) {
            events.push_back({tick,"damage_blocked","frozen_projectile_attack_source_missing",attacker?attacker->id:-1});return;
        }
        request.attack=readAttackDamage(pvf_.script(attackPath.empty()?monsterAttackPath(*attacker):attackPath),AttackStatusConsumer::StunHostV1);
        const auto resistance=evaluateCharacterStatusResistances(combatAttributes_->pureChr,characterSource(),
            combatAttributes_->equipmentSources,combatAttributes_->qualificationLevel);
        const auto result=resolveActorContact(request,resistance);
        lastDamageTrace_=result.snapshot();
        if(!result.usable()) { events.push_back({tick,"damage_blocked","source_incoming_inputs",attacker?attacker->id:-1});return; }
        if(attacker && attacker->monsterPath.find("/tau/")!=std::string::npos && attacker->attackVariant==1)
            lastDamageTrace_["controller_policy"]={{"id","inferred-source-heading-approach-v1"},{"classification","inferred_beta"},
                {"basis","Future source ANI type15 box stops approach; damage occurs only at its actual source frame"},
                {"movement_calibration",{{"windup_ms",300},{"peak_world_units_per_second",330},{"acceleration_ms",150},{"deceleration_ms",180}}},
                {"source_timing","First type15 frame boundary read from current ANI"},
                {"native_pc_trajectory","unverified"}};
        value=*result.hpDamage;
        if(result.missed) { events.push_back({tick,"player_miss",request.attack.source.path,attacker?attacker->id:-1});return; }
    } else value = std::max(1, value - std::max(0, equipmentDefense) / 20);
    bool blocked = active_ >= 0 && skills[active_].id == 1 && player.dir == -dir;
    if (blocked) {
        value = int(std::lround(value * (1 - skills[active_].parameter(2) / 100)));
        events.push_back({tick, "sound", "SM_GUARD"});
    }
    if (!(debugOverrides_.enabled && debugOverrides_.hpLock))
        player.hp = std::max(0, player.hp - value);
    events.push_back({tick, "player_hit", blocked ? "guard" : "hit", -1, 0, value});
    if (!blocked) {
        if(!experimentalRuntime_)events.push_back({tick, "sound", "R_SM_DMG"});
        if (!armor()) {
            // HP is already committed: a lethal hit must never preserve
            // physical movement even before beginDeath publishes dead/life.
            idle(true);
            player.animation = "damage1";
            player.animStart = nowMs();
            player.stunUntil = nowMs() + 250;
            guardUntil_ = nowMs() + 180;
        }
    }
    if (!player.hp) {
        beginDeath(player);
        idle();
        player.animation = "down";
        guardUntil_ = 0;
        if(!experimentalRuntime_)events.push_back({tick, "sound", "SM_DIE"});
    } else interruptStatusTarget(player);
}
int World::skillDamage(int id, int phase) const {
    // Attack-volume previews have no target. Actual beta source damage is
    // resolved per target immediately before the accepted HP write.
    return usesSourceGrowth()?0:legacySkillDamage(id,phase);
}
int World::legacySkillDamage(int id,int phase) const {
    const Skill *sk = nullptr;
    for (auto &s : skills)
        if (s.id == id)
            sk = &s;
    double pct = 100, fixed = 0;
    if (sk) {
        auto p = [&](int col) { return sk->parameter(col); };
        switch (id) {
        case 46:
            pct = p(0);
            fixed = p(3);
            break;
        case 5:
            pct = p(0);
            fixed = p(1);
            break;
        case 8:
            pct = p(phase == 2 ? 1 : 0);
            fixed = p(phase == 2 ? 4 : 3);
            break;
        case 11:
            pct = p(0);
            fixed = p(2);
            break;
        case 16:
            pct = p(0);
            break;
        case 17:
            pct = p(0);
            break;
        case 20:
            pct = p(2);
            fixed = p(0);
            break;
        case 58:
            pct = p(std::min(phase, 2));
            fixed = phase == 2 ? p(3) : 0;
            break;
        case 64:
            pct = p(phase ? 1 : 0);
            fixed = phase ? p(7) : 0;
            break;
        case 65:
            pct = p(0);
            break;
        case 77:
            pct = p(std::min(phase, 1));
            fixed = p(phase ? 4 : 3);
            break;
        default:
            break;
        }
    }
    // Combat-demo equipment power is explicit provisional data; full original stat pipeline requires
    // version-matched validation.
    static const double physical[] = {18, 17, 24, 22}, magical[] = {24, 22, 18, 20};
    bool magic = id == 5 || id == 20 || id == 58 || id == 77;
    double power = (magic ? magical[weapon % 4] : physical[weapon % 4]) + std::max(0, equipmentAttack);
    auto chr = pvf_.script("character/swordman/swordman.chr");
    double stat = chr.number(magic ? "[magical attack]" : "[physical attack]");
    double bonus = 0;
    for (auto &e : effects)
        if (e.skill == 25 && e.phase == "khazan:stay" && nowMs() >= e.born && nowMs() < e.expires &&
            !e.attached && std::abs(player.x - e.x) < 125 && std::abs(player.y - e.y) < 80)
            bonus = std::max(bonus, skills[7].parameter(magic ? 2 : 0));
    // Source level-property scales these mastery columns by 0.1 percent.
    const int magicColumn[] = {8, 9, 10, 9};
    const auto mastery = effectivePassive(passives[1 + weapon % 4]);
    power *= 1 + mastery.parameter(magic ? magicColumn[weapon % 4] : 0) / 1000.0;
    double value = (power * pct / 100 + fixed) * (1 + (stat + bonus) / 250);
    if (id == 0) {
        Skill basic = passives[0];
        basic.level = std::max(1, characterLevel);
        int col = player.animation == "dashattack" ? 1 : player.animation == "jumpattack" ? 2 : 0;
        value *= 1 + basic.parameter(col) / 1000.0;
    }
    return std::max(1, int(std::lround(value)));
}
Json World::statReport() const {
    Json list = Json::array();
    for (const auto &s : passives)
        list.push_back({{"source", s.source}, {"name", s.name}, {"level", s.level},
                        {"effect", s.key == "armormasterylight" ? "per-item armor mastery consumer pending" : "source base modifier"}});
    return {{"formula", usesSourceGrowth()?"inferred source PvE damage per attacker/target; historical snapshots retain legacy damage":"demo; training weapon power and 250 stat divisor; no PC parity claim"},
            {"last_damage",lastDamageTrace_},
            {"combat_pipeline",lastCombatPipelineTrace_.snapshot()},
            {"status_policy",StunStatusPolicy::inferredFlatChanceStunV1().snapshot()},
            {"player_status_stunned",statusStunned(player.handle)},
            {"status_instance_ids",statuses_.instanceWatermark()},
            {"rule_profile", usesSourceGrowth() ? "beta-foundation-v1" : "legacy-demo-v1"},
            {"source_actions",{{"configured",bool(actHost_)},{"diagnostics",actServiceDiagnostics_},
                {"policy","inferred-source-action-next-boundary-v1"},{"whole_monster_complete",false}}},
            {"base_attributes",baseAttributes_ ? baseAttributes_->snapshot() : Json()},
            {"source_speeds",speedAttributes_ ? speedAttributes_->snapshot() : Json()},
            {"equipment_resources",equipmentResources_ ? equipmentResources_->snapshot() : Json()},
            {"combat_attributes",combatAttributes_ ? combatAttributes_->snapshot() : Json()},
            {"learning_initialized",hasLearningLedger()},{"last_skill_learning",lastSkillLearningTrace_},
            {"test_skill_overlay",skillTestOverlay_.snapshot()},
            {"speed_consumers",{{"policy","inferred-source-speed-consumers-v1"},
                {"clock_mode",animationClockPolicy_ ? ani_clock::policyName(*animationClockPolicy_) : "ScaledLocalAge; ordinary/dash/jump attacks only; source delays unchanged"},
                {"movement","local 180/300 world-unit base times CHR/EQU move-permille; independent dash XY factors"},
                {"pending",{"cast-speed action selection","skill-specific speed consumers","source locomotion base"}}}},
            {"attribute_revision",attributeRevision_},{"last_attribute_change",lastAttributeChange_},
            {"last_equipment_change",lastEquipmentChange_},
            {"character_level", characterLevel}, {"weapon", weapon}, {"passives", list},
            {"armor", "source equipment HP/MP and speed consumers are active in beta; full defense and armor mastery pending"},
            {"unimplemented", {"equipment rolls", "defense", "critical", "element", "bleeding", "armor mastery per item"}}};
}
Json World::snapshot() const {
    Json j = {{"tick", tick}, {"character", identity_.json()},
              {"entity_handle", player.handle.json()}, {"action_instance", actionInstance_},
              {"pending_ticks", clock_.pendingTicks()},
              {"controller_coverage", controllers_.snapshot()},
              {"experimental_character", experimentalDiagnostics()},
              {"x", player.x},
              {"y", player.y},
              {"z", player.z},
              {"hp", player.hp},
              {"mp", player.mp},
              {"max_hp",player.maxHp},{"max_mp",player.maxMp},
              {"dead", player.dead}, {"direction", player.dir}, {"armor", armor()}, {"invincible", invincible()},
              {"combat", combat},
              {"animation", player.animation},
              {"pose_frame_override", player.poseFrame},
              {"last_attack_frame", lastAttackFrame_},
              {"gorecross", {{"phase", goreCrossPhase_}, {"event_layer", goreCrossEventEffect_},
                   {"last_event_frame", goreCrossEvents_.lastFrame()}, {"pending_event", goreCrossEvents_.pending()}}},
              {"player_animation_ms", player.animationClock ? double(player.animationClock->elapsedMs) :
                   usesSourceGrowth()&&basicAttacking() ? basicLocalAge_ : double(nowMs() - player.animStart)},
              {"animation_clock_policy", animationClockReport()},
              {"hit_stop_ticks", player.hitStopTicks}, {"hit_stopped", player.hitStopped},
              {"active", active_},
              {"stage", stage_},
              {"effects", effects.size()},
              {"effect_instances", Json::array()},
              {"blood_vigorous_level", bloodVigorousLevel},
              {"stats", statReport()},
              {"last_skill_cost", lastSkillCostTrace_},
              {"monsters", Json::array()}};
    if (player.animationClock) {
        const auto &s = *player.animationClock;
        j["animation_clock"] = {{"source", player.animationClockSource}, {"frame", s.frame}, {"next_frame", s.nextFrame},
            {"elapsed_ms", s.elapsedMs}, {"frame_start_ms", s.frameStartMs}, {"deadline_ms", s.nextDeadlineMs},
            {"local_ms", s.localMs}, {"span_ms", s.spanMs}, {"rate_percent", s.ratePercent},
            {"tick", s.lastTick}, {"visit", s.visit}, {"paused", s.paused}, {"ended", s.ended}};
    }
    for (const auto &e : effects)
        j["effect_instances"].push_back({{"id", e.id}, {"skill", e.skill}, {"animation", e.animation},
            {"phase", e.phase}, {"born", e.born}, {"expires", e.expires}, {"layer", e.layer},
            {"position", {e.x, e.y, e.z}}, {"damaging", e.damageEnabled},
            {"source", e.resourceSource}, {"source_offset", e.sourceOffset}});
    for (auto &m : monsters)
        j["monsters"].push_back({{"id", m.id}, {"entity_handle", m.handle.json()}, {"hp", m.hp}, {"max_hp",m.maxHp},{"source_stats",m.sourceStats}, {"x", m.x}, {"y", m.y}, {"z", m.z}, {"dead", m.dead},
                                 {"animation", m.animation}, {"recovery", m.recovery},
                                 {"animation_ms", nowMs() - m.animStart},
                                 {"hit_stop_ticks", m.hitStopTicks}, {"hit_stopped", m.hitStopped},
                                 {"captured_by", m.capturedBy}, {"stun_until", m.stunUntil}});
    j["skills"] = Json::array();
    for (int i = 0; i < int(skills.size()); i++)
        j["skills"].push_back({{"id", skills[i].id}, {"key", skills[i].identity().json()}, {"level", skills[i].level},
                               {"mp", skills[i].mp}, {"cooldown_ms", remainingCd(i)}});
    j["bindings"] = bindings;
    j["test_mode"] = {{"god", god}, {"free_cd", freeCd}, {"freeze_ai", freezeAi}};
    j["beta_overrides"] = debugOverrides_.json();
    return j;
}
Json World::eventLog() const {
    Json j = Json::array();
    for (auto &e : events)
        j.push_back({{"tick", e.tick},
                     {"kind", e.kind},
                     {"name", e.name},
                     {"source", e.source},
                     {"target", e.target},
                     {"value", e.value}});
    return j;
}
} // namespace dnf
