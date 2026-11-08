#include "dnf/female_gunner_world.hpp"
#include "dnf/female_gunner_entities.hpp"
#include "dnf/female_gunner_modifiers.hpp"
#include "dnf/combat.hpp"
#include "dnf/collision.hpp"
#include "dnf/effect_plan.hpp"
#include "dnf/gunner_pixel_anchor.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *policy = "inferred-1031-female-gunner-entity-v1";
bool supportedInputChannel(const FemaleGunnerSkillCommand &command) {
    return command.key.jobId==5&&((command.family=="channel_flame"&&
        (command.key.skillId==13||command.key.skillId==36||command.key.skillId==107))||
        (command.family=="channel_projectile"&&command.key.skillId==12));
}
void requireFinite(double n, const char *label) {
    if (!std::isfinite(n)) throw std::invalid_argument(std::string("Female Gunner nonfinite ") + label);
}
void checkRef(Pvf &pvf, const SourceRef &source) {
    if (source.packageIdentity != pvf.identity() || source.memberPath.empty() || !pvf.has(source.memberPath) ||
        sha256(pvf.read(source.memberPath)) != source.memberSha256)
        throw std::invalid_argument("Female Gunner source binding changed: " + source.memberPath);
}
Json commandReceipt(const FemaleGunnerSkillCommand &c) {
    return {{"key",c.key.json()},{"source",c.skillSource.json()},{"level",c.level},{"family",c.family},{"role",c.effectRole},
        {"action",c.actionSequence},{"pulse",c.pulseId},{"stage",c.stage},
        {"object",c.objectSource?c.objectSource->json():Json()},{"animation",c.animationSource?c.animationSource->json():Json()},
        {"attack",c.attackSource?c.attackSource->json():Json()},{"count",c.count},{"lifetime_ms",c.lifetimeMs},
        {"interval_ms",c.intervalMs},{"delay_ms",c.releaseDelayMs},
        {"coordinate_trace",c.rawTables.value("coordinate_trace",Json())},
        {"basic_source_binding",c.rawTables.value("basic_source_binding",Json())},
        {"basic_particle_motion",c.rawTables.value("basic_particle_motion",Json())},
        {"basic_aim",c.rawTables.value("basic_aim",Json())},
        {"ammo_visual_binding",c.rawTables.value("ammo_visual_binding",Json())},
        {"visual_suppressed_for_shared_projectile",c.rawTables.value("visual_suppressed_for_shared_projectile",false)},
        {"diagnostics",c.diagnostics}};
}
struct SourcePixelPoint { double x=0,y=0;Json evidence; };
struct BasicBulletSource { Script particle,object;Json trace; };
// Source data is immutable for a content profile. Keep derived descriptors and
// pixel points with the actual World source owners, never in a process-global
// cache keyed by an address that a later profile could reuse. Cache mutation
// is independent of action publication: it has no simulation or reward state.
struct SourceWorkCache {
    const Pvf *pvfOwner;const Assets *assetsOwner;std::string packageIdentity;
    std::map<std::pair<int,int>,BasicBulletSource> descriptors;
    using PointKey=std::tuple<std::string,std::array<int,2>,bool,size_t,ani_render::RenderProfile>;
    std::map<PointKey,std::optional<SourcePixelPoint>> points;
    uint64_t descriptorRequests=0,descriptorHits=0,descriptorLoads=0;
    uint64_t pointRequests=0,pointHits=0,pixelDecodes=0,pixelsScanned=0;
    SourceWorkCache(const Pvf &pvf,const Assets &assets):pvfOwner(&pvf),assetsOwner(&assets),packageIdentity(pvf.identity()){}
    void requireOwners(const Pvf &pvf,const Assets &assets) const {
        if(pvfOwner!=&pvf||assetsOwner!=&assets||packageIdentity!=pvf.identity())
            throw std::invalid_argument("Female Gunner derived source cache owner changed");
    }
    Json snapshot() const {
        return {{"policy","owner-bound-profile-gunner-source-cache-v2"},{"enabled",true},
            {"point_cache_value","Immutable source pixel only; current pose is transformed after lookup"},
            {"point_key",{"path","variation","edge_or_center","selected_source_frame","render_profile"}},
            {"descriptor_requests",descriptorRequests},{"descriptor_hits",descriptorHits},{"descriptor_loads",descriptorLoads},
            {"point_requests",pointRequests},{"point_hits",pointHits},{"pixel_decodes",pixelDecodes},{"pixels_scanned",pixelsScanned},
            {"descriptor_entries",descriptors.size()},{"point_entries",points.size()},{"package_identity",packageIdentity},
            {"hot_replacement_supported",false},{"failure_policy","Cache empty visible results; preserve per-shot fallback diagnostics; exceptions are not cached"}};
    }
};
BasicBulletSource loadBasicBulletSource(Pvf &pvf,int subtype,int variant) {
    const auto settings=pvf.script("etc/gunnerdefaultguninfo.etc");
    const Field *strings=nullptr;bool selected=false,matched=false;
    for(const auto &field:settings.fields) {
        const auto tag=normalize(field.tag);
        if(tag=="[sub type]") {
            if(field.values.size()!=1||!field.values[0].is_number_integer())
                throw std::invalid_argument("Invalid GunnerDefaultGunInfo subtype");
            selected=field.values[0].get<int>()==subtype;
            if(selected&&matched)throw std::invalid_argument("Repeated GunnerDefaultGunInfo subtype");
            matched|=selected;
        } else if(selected&&tag=="[string]") {
            if(strings)throw std::invalid_argument("Ambiguous GunnerDefaultGunInfo string table");
            strings=&field;
        }
    }
    if(variant<0||variant>2)throw std::invalid_argument("Invalid source basic gun variant");
    const size_t slot=size_t(variant);
    if(!strings||strings->values.size()<=slot||!strings->values[slot].is_string())
        throw std::invalid_argument("Missing source basic gun particle binding");
    BasicBulletSource out;
    out.particle=pvf.script(effectResource(pvf,settings.path,strings->values[slot].get<std::string>()));
    const auto kind=out.particle.values("[object type]"),object=out.particle.values("[object]");
    if(kind!=Json::array({"[passive object]"})||object.size()!=2||!object[0].is_string()||
        !object[1].is_number_integer())throw std::invalid_argument("Invalid source basic gun passive-object descriptor");
    const auto registry=pvf.script("passiveobject/passiveobject.lst");
    if(registry.tokens.size()%2)throw std::invalid_argument("Malformed source passive-object registry");
    std::optional<size_t> registration;
    for(size_t i=0;i+1<registry.tokens.size();i+=2)if(registry.tokens[i].at("value")==object[1]) {
        if(registration)throw std::invalid_argument("Ambiguous source basic gun object registration");
        registration=i;
    }
    if(!registration||!registry.tokens[*registration+1].at("value").is_string())
        throw std::invalid_argument("Missing source basic gun object registration");
    out.object=pvf.script(effectResource(pvf,registry.path,registry.tokens[*registration+1].at("value").get<std::string>()));
    Json fields=Json::array();for(const auto &field:out.particle.fields)
        fields.push_back({{"tag",field.tag},{"values",field.values},{"byte_offset",field.offset}});
    out.trace={{"policy","1031-native-basic-gun-source-selection-v1"},{"classification","source_binding"},
        {"subtype",subtype},{"variant",variant==2?"jump":variant==1?"down":"up"},{"settings",makeSourceRef(pvf,settings.path).json()},
        {"string_slot",slot},{"string_field_byte_offset",strings->offset},{"literal",strings->values[slot]},
        {"particle",makeSourceRef(pvf,out.particle.path).json()},{"particle_fields",fields},
        {"registry",makeSourceRef(pvf,registry.path).json()},{"object_id",object[1]},
        {"registration",Json::array({registry.tokens[*registration],registry.tokens[*registration+1]})},
        {"object",makeSourceRef(pvf,out.object.path).json()},
        {"native_basis","BFE51F..BFE57A GunInfo string0/1/2 to PTL descriptor; PTL object ID to current registry"},
        {"native_jump_input_setter_verified",false}};
    return out;
}
const BasicBulletSource &basicBulletSource(Pvf &pvf,SourceWorkCache &cache,int subtype,int variant) {
    ++cache.descriptorRequests;const auto key=std::make_pair(subtype,variant);
    const auto found=cache.descriptors.find(key);
    if(found!=cache.descriptors.end()){++cache.descriptorHits;return found->second;}
    auto value=loadBasicBulletSource(pvf,subtype,variant);++cache.descriptorLoads;
    return cache.descriptors.emplace(key,std::move(value)).first->second;
}
std::optional<SourcePixelPoint> loadVisibleSourcePoint(Pvf &pvf,Assets &assets,SourceWorkCache &cache,const std::string &path,
    const std::array<int,2> &variation,bool rightEdge,size_t startingFrame=0) {
    const auto clip=assets.animation(path);
    for(size_t step=0;step<clip->frames.size();++step) {
        const auto index=(startingFrame+step)%clip->frames.size();const auto &frame=clip->frames[index];
        if(frame.image.empty())continue;
        const auto imagePath=appearanceImage(frame.image,variation);const auto image=assets.pixels(imagePath,frame.imageFrame);
        ++cache.pixelDecodes;cache.pixelsScanned+=uint64_t(image.width)*uint64_t(image.height);
        int left=image.width,right=-1,top=image.height,bottom=-1;
        for(int y=0;y<image.height;++y)for(int x=0;x<image.width;++x) {
            const auto at=(size_t(y)*image.width+x)*4;
            if(image.rgba[at+3]&&(image.rgba[at]||image.rgba[at+1]||image.rgba[at+2])) {
                left=std::min(left,x);right=std::max(right,x);top=std::min(top,y);bottom=std::max(bottom,y);
            }
        }
        if(right<left)continue;
        double x=(left+right+1)*.5,y=(top+bottom+1)*.5;
        if(rightEdge) {
            int low=image.height,high=-1;
            for(int row=0;row<image.height;++row) {
                const auto at=(size_t(row)*image.width+right)*4;
                if(image.rgba[at+3]&&(image.rgba[at]||image.rgba[at+1]||image.rgba[at+2])){low=std::min(low,row);high=std::max(high,row);}
            }
            x=right+.5;y=(low+high+1)*.5;
        }
        // Cache immutable source pixels. A sampled/interpolated pose belongs
        // to this request and must never be frozen into the source-work cache.
        SourcePixelPoint point;point.x=x;point.y=y;
        point.evidence={{"animation",makeSourceRef(pvf,path).json()},{"frame",index},{"image",imagePath},
            {"image_frame",frame.imageFrame},{"ani_xy",{frame.x,frame.y}},{"img_crop",{image.x,image.y,image.width,image.height}},
            {"nonblack_alpha_bounds",{left,top,right+1,bottom+1}},{"source_pixel",{x,y}}};return point;
    }
    return {};
}
std::optional<SourcePixelPoint> visibleSourcePoint(Pvf &pvf,Assets &assets,SourceWorkCache &cache,const std::string &path,
    const std::array<int,2> &variation,bool rightEdge,ani_render::RenderProfile profile,size_t startingFrame=0,
    const AniPose *sampledPose=nullptr) {
    ++cache.pointRequests;
    const auto start=sampledPose?sampledPose->frame:startingFrame;
    SourceWorkCache::PointKey key{normalize(path),variation,rightEdge,start,profile};
    const auto found=cache.points.find(key);
    std::optional<SourcePixelPoint> point;
    if(found!=cache.points.end()){++cache.pointHits;point=found->second;}
    else {point=loadVisibleSourcePoint(pvf,assets,cache,path,variation,rightEdge,start);cache.points.emplace(std::move(key),point);}
    if(!point)return point;
    const auto index=point->evidence.at("frame").get<size_t>();
    const auto pose=sampledPose&&sampledPose->frame==index?*sampledPose:assets.animation(path)->samplePose(0,false,int(index),profile);
    const auto &crop=point->evidence.at("img_crop");
    const auto local=inferredGunnerPixelPoint(pose,crop[0].get<int>(),crop[1].get<int>(),point->x,point->y,profile);
    point->x=local.x;point->y=local.y;point->evidence["local_point"]={local.x,local.y};
    point->evidence["source_transform"]={{"position",{pose.x,pose.y}},{"rate",{pose.scaleX,pose.scaleY}},
        {"rotation_radians",pose.rotationRadians},{"flip",pose.flip},{"profile",ani_render::profileName(profile)},
        {"sampled_source_frame",start},{"future_visible_fallback",index!=start},
        {"interpolated",pose.interpolated},{"local_time",pose.localTime},{"progress",pose.progress}};
    return point;
}
void anchorBasicBullet(Pvf &pvf,Assets &assets,SourceWorkCache &cache,const CharacterAppearance &appearance,
    const ExperimentalAttackFrame &frame,FemaleGunnerSkillCommand &bullet,ani_render::RenderProfile profile) {
    const auto *body=appearanceBodyMotion(appearance,frame.motion.source.memberPath);
    if(!body)throw std::invalid_argument("Basic bullet lacks exact CHR/appearance motion");
    const auto root=assets.animation(frame.motion.source.memberPath);
    const auto sourcePose=[&](const std::string &path,bool bodyLayer) {
        const auto clip=assets.animation(path);
        if(frame.animationClock) {
            const auto clock=bodyLayer?*frame.animationClock:clip->followClock(*root,*frame.animationClock,
                frame.animationClock->loop,frame.animationControllerDelays.get());
            return clip->samplePose(clock,profile);
        }
        return clip->samplePose(0,false,int(frame.sourceFrame),profile);
    };
    std::optional<SourcePixelPoint> muzzle;
    for(const auto &layer:appearance.orderedLayers())if(layer.slot=="[weapon]") {
        const auto path=appearanceLayerMotion(layer,*body);if(path.empty())continue;
        const auto pose=sourcePose(path,false);
        auto point=visibleSourcePoint(pvf,assets,cache,path,layer.variation,true,profile,pose.frame,&pose);
        if(point&&(!muzzle||point->x>muzzle->x)) {
            point->evidence["equipment"]=layer.sourcePath;point->evidence["lay"]=layer.animationScript;
            point->evidence["variation"]=layer.variation;muzzle=std::move(point);
        }
    }
    const bool weaponMuzzle=bool(muzzle);
    // Pixel inference is optional presentation evidence. A valid body action
    // must not fail its complete input transaction because the weapon frame
    // is deliberately blank. Preserve a source-based, diagnosed fallback.
    if(!muzzle) {
        const int variation=appearance.bodyVariation();
        const auto pose=sourcePose(frame.motion.source.memberPath,true);
        muzzle=visibleSourcePoint(pvf,assets,cache,frame.motion.source.memberPath,{variation,variation},true,profile,pose.frame,&pose);
        bullet.diagnostics.push_back({{"code","basic_weapon_muzzle_pixels_unavailable"},{"severity","warning"},
            {"body",frame.motion.source.json()},{"fallback",muzzle?"visible_body_edge":"source_body_origin"},
            {"classification","inferred"},{"native_socket_verified",false}});
        if(!muzzle)muzzle=SourcePixelPoint{0,0,{{"animation",frame.motion.source.json()},{"local_point",{0,0}},
            {"basis","Unmodified source body origin; no visible weapon/body candidate"}}};
    }
    const auto sprite=visibleSourcePoint(pvf,assets,cache,bullet.animationSource->memberPath,{0,0},false,profile);
    bullet.offsetX=muzzle->x-(sprite?sprite->x:0);bullet.offsetY=0;
    bullet.offsetZ=-muzzle->y+(sprite?sprite->y:0);
    bullet.rawTables["coordinate_trace"]={{"policy","inferred-1031-equipped-basic-muzzle-v1"},{"classification","inferred"},
        {"body",frame.motion.source.json()},{"weapon_muzzle",muzzle->evidence},{"bullet_sprite",sprite?sprite->evidence:Json()},
        {"render_profile",ani_render::profileName(profile)},{"render_profile_evidence",ani_render::profileEvidence(profile)},
        {"muzzle_basis",weaponMuzzle?"visible_equipped_weapon_edge":"diagnosed_source_body_fallback"},
        {"offset_xyz",{bullet.offsetX,bullet.offsetY,bullet.offsetZ}},
        {"basis","Actual equipped EQU/LAY active CHR motion selects visible weapon edge; align projectile visible center, including its own ANI XY and IMG crop, to that point"},
        {"source_pixels_preserved",true},{"native_spawn_setter_verified",false},
        {"unverified","Rightmost nonblack-alpha edge is an inferred muzzle, not a recovered native socket. First visible future frame is used when initial source weapon frame is transparent."}};
}
struct AmmoFlightSelection {
    std::optional<SourceRef> source;Json trace;
};
AmmoFlightSelection select1031AmmoFlight(Pvf &pvf,const FemaleGunnerSkillCommand &buff,int subtype) {
    AmmoFlightSelection selected;
    selected.trace={{"policy","inferred-host-1031-default-ammo-flight-selector-v1"},{"classification","inferred_beta"},
        {"skill",buff.key.json()},{"skill_source",buff.skillSource.json()},{"weapon_subtype",subtype},
        {"native_selector","0xAC9300"},{"native_caller","0xACB180 / 0xACB2EB..0xACB340"},
        {"native_parameters",{"ammo_kind","weapon_subtype","owner_actor_pointer"}},
        {"owner_override","upstream owner/override vector not reconstructed; explicitly assume absent"},
        {"native_override_branch",{{"condition","owner vtable+0x798(10) -> object vtable+0x20; nonempty +0x108/+0x10C vector; kind!=52"},
            {"suffix","Pistol_%d.ani / Musket_%d.ani / BowGun_%d.ani"},
            {"suffix_number_source","object+0x10 via 0x40B360; not a constant 31439"}}},
        {"unresolved_native_caller",{{"kind_source","source argument+0x38 protected helper -> projectile+0xDE0"},
            {"subtype_source","projectile+0xDD0 writer unresolved"},{"suppressed_modes",{6,9,64,104,72}},
            {"mode_semantics","projectile+0xDD8 upstream meaning unresolved; host limited to actual ordinary basic projectile"}}},
        {"visual_host_policy","Select one flight visual on ordinary entity; additive ammo damage shares its collision ANI and does not duplicate drawing"},
        {"original_dynamic_comparison","pending_user"}};
    if(pvf.identity()!="d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d") {
        selected.trace["result"]="unsupported_source_version_preserve_basic_visual";return selected;
    }
    struct Binding {int id;const char *skill;const char *prefix;};
    static const Binding bindings[]={{1,"skill/atgunner/flamebullet.skl","flame"},
        {2,"skill/atgunner/freezebullet.skl","freeze"},{30,"skill/atgunner/silverbullet.skl","silver"},
        {52,"skill/atgunner/armorbullet.skl","1_tan_normal"}};
    const Binding *binding=nullptr;
    for(const auto &candidate:bindings)if(buff.key==SkillKey{5,candidate.id}&&buff.family=="ammo_enchantment"&&
        normalize(buff.skillSource.memberPath)==candidate.skill)binding=&candidate;
    if(!binding){selected.trace["result"]="unmatched_live_skill_source_preserve_basic_visual";return selected;}
    checkRef(pvf,buff.skillSource);
    if(subtype<0||subtype>4){selected.trace["result"]="invalid_host_subtype_preserve_basic_visual";return selected;}
    if(subtype==3) {
        selected.trace["result"]="native_null_for_handcannon_preserve_basic_visual";
        selected.trace["native_null_basis"]="AC963E..AC964A and AC9722: subtype3 has no attribute flight ANI, including kind52";return selected;
    }
    std::string suffix=subtype==2?"musket.ani":subtype==4?"bowgun.ani":binding->id==52?".ani":"pistol.ani";
    const auto path=std::string("character/gunner/effect/animation/bullet/")+binding->prefix+suffix;
    selected.source=makeSourceRef(pvf,path);selected.trace["result"]="default_native_selector_with_inferred_host_binding";
    selected.trace["flight_animation"]=selected.source->json();
    selected.trace["native_path_basis"]="AC9331 root + AC9359/9382/93A6/93D6 kind prefix + AC950B..AC9580 subtype/default suffix";
    selected.trace["skill_directly_references_flight_ani"]=false;return selected;
}
FemaleGunnerSkillCommand flameSource(const FemaleGunnerSkillCommand &bullet,Pvf &pvf) {
    auto source=bullet;source.key={5,1};source.family="enchanted_bullet";
    source.skillSource=makeSourceRef(pvf,"skill/atgunner/flamebullet.skl");
    source.level=bullet.rawTables.at("flame_level");source.rawTables=bullet.rawTables.at("flame_source");
    source.preflightOnly=false;return source;
}
// Visit crossed source intervals, including zero-delay frames. Rendering
// cannot discard a short hit/sound frame between two simulation ticks.
template<class Visit> void visitSourceFrames(const Animation &animation,int64_t previous,int64_t age,bool loop,Visit visit) {
    if(animation.duration<=0||animation.frames.empty()||age<0)return;
    const auto first=loop?std::max<int64_t>(0,previous)/animation.duration:0;
    const auto last=loop?age/animation.duration:0;
    for(auto cycle=first;cycle<=last;++cycle) {
        int64_t start=cycle*animation.duration;
        for(size_t index=0;index<animation.frames.size();++index) {
            const auto end=start+animation.frames[index].duration;
            if(start<=age && (end>previous || (start==end&&start>previous)))
                visit(index,start,start>previous);
            start=end;
        }
    }
}
}

struct FemaleGunnerWorld::State {
    std::shared_ptr<SourceWorkCache> sourceCache;
    struct Entity {
        FemaleGunnerSkillCommand command;
        EntityHandle owner;
        EntityHandle boundTarget;
        uint64_t attackId = 0;
        int effectId = -1;
        int64_t born = 0, expires = 0, nextPulse = 0;
        uint32_t pulse = 0;
        double x = 0, y = 0, z = 0;
        std::optional<AttackDamageDefinition> attack;
        std::optional<DamageSkillModifiers> flameSpecialDamage;
        AttackResponse response;
        std::shared_ptr<const Animation> animation,visualAnimation;
        double visualOffsetX=0,visualOffsetY=0,visualOffsetZ=0;
        std::optional<SkillStatusApplication> status;
        std::optional<GunnerBasicParticle> basicParticle;
        double basicPitchDegrees=0;
        std::set<EntityHandle> hit;
        int64_t lastAge = -1;
    };
    struct Buff { FemaleGunnerSkillCommand command; int64_t expires = 0; };
    std::vector<Entity> entities;
    std::map<SkillKey, Buff> buffs;
    Json trace = Json::array();
    std::vector<Effect> preparedEffects;
    MonotonicIds attackIds, effectIds;
    bool prepared = false;
    uint64_t basicSequence = 0;
    int64_t gExpires = 0;
    int gSkill = 0;
    std::map<EntityHandle,std::pair<SkillKey,int64_t>> captures;
    void record(Json row) {
        if (trace.size() >= 192) trace.erase(trace.begin());
        row["policy"] = policy; row["classification"] = "inferred_beta"; trace.push_back(std::move(row));
    }
};
FemaleGunnerWorld::FemaleGunnerWorld(World &world) : world_(world), state_(std::make_unique<State>()) {
    state_->sourceCache=std::make_shared<SourceWorkCache>(world_.pvf_,world_.assets_);
}
FemaleGunnerWorld::FemaleGunnerWorld(World &world, std::unique_ptr<State> state) : world_(world), state_(std::move(state)) {}
FemaleGunnerWorld::~FemaleGunnerWorld() = default;

std::unique_ptr<FemaleGunnerWorld> FemaleGunnerWorld::prepare(
    const std::vector<FemaleGunnerSkillCommand> &commands, const ExperimentalActorState &actor, size_t reservedBodyAttacks,
    const std::vector<ExperimentalAttackFrame> &bodyFrames) const {
    state_->sourceCache->requireOwners(world_.pvf_,world_.assets_);
    auto staged = std::make_unique<State>(*state_);
    staged->preparedEffects = world_.effects;
    staged->attackIds = world_.ids_.attacks; staged->effectIds = world_.effectIds_;
    staged->prepared = true;
    std::set<std::string> validatedVisuals;
    auto allCommands=commands;
    std::map<std::pair<uint64_t,uint32_t>,AmmoFlightSelection> ammoFlightSelections;
    // A repeated channel stop must not expand into another end visual. Live
    // non-tail entities (or a root published in this batch) are the ownership
    // receipt; after they are retired, a surviving end tail cannot rearm it.
    // This needs no unbounded per-action tombstone table across a long room.
    std::set<std::pair<SkillKey,uint64_t>> pendingChannels,acceptedStops;
    for(const auto &command:commands)if(!command.preflightOnly&&command.kind!=FemaleGunnerCommandKind::Clear&&
        (command.family=="channel_flame"||command.family=="channel_projectile"))
        pendingChannels.insert({command.key,command.actionSequence});
    allCommands.erase(std::remove_if(allCommands.begin(),allCommands.end(),[&](const auto &command) {
        if(command.kind!=FemaleGunnerCommandKind::Clear||command.effectRole!="stop_channel"||!command.actionSequence||
           !supportedInputChannel(command))return false;
        checkRef(world_.pvf_,command.skillSource);
        const auto action=std::make_pair(command.key,command.actionSequence);
        const bool live=std::any_of(staged->entities.begin(),staged->entities.end(),[&](const auto &entity) {
            return entity.command.key==command.key&&entity.command.actionSequence==command.actionSequence&&
                entity.command.effectRole!="channel_visual_end"&&!entity.command.rawTables.value("channel_tail",false);
        });
        return (!live&&!pendingChannels.count(action))||!acceptedStops.insert(action).second;
    }),allCommands.end());
    allCommands.erase(std::remove_if(allCommands.begin(),allCommands.end(),[&](const FemaleGunnerSkillCommand &command) {
        if(command.preflightOnly||(command.family!="grab_ground_shoot"&&command.family!="grab_aerial_gatling"))return false;
        const bool captured=std::any_of(staged->captures.begin(),staged->captures.end(),[&](const auto &entry){return entry.second.first==command.key;});
        if(!captured)staged->record({{"event","grab_followup_rejected_no_capture"},{"skill",command.key.json()}});
        return !captured;
    }),allCommands.end());
    for(const auto &command:commands)if(!command.preflightOnly&&command.family=="mobile_basic_shoot") {
        const auto found=staged->buffs.find({5,15});
        if(found==staged->buffs.end()||!found->second.command.count)
            throw std::invalid_argument("Moving Shoot source ammunition is exhausted");
        if(!--found->second.command.count)staged->buffs.erase(found);
    }
    for(auto &command:allCommands)if(command.family=="g_transform") {
        const auto now=world_.nowMs();
        const bool live=staged->gSkill&&staged->gExpires>now;
        if(!live&&command.key.skillId!=79)
            throw std::invalid_argument("G-2/G-3 requires a live G-1 transform group");
        const auto table=command.rawTables.at("static_data");
        if(table.size()<3||!table[2].is_number())throw std::invalid_argument("G transform source extension is unavailable");
        const auto extension=table[2].get<int64_t>();
        command.lifetimeMs=live?staged->gExpires-now+extension:
            int64_t(skillLevelValue(command.rawTables.at("level_info"),command.level,1).value());
        if(command.lifetimeMs<=0||command.lifetimeMs>INT32_MAX)throw std::invalid_argument("G transform source duration out of bounds");
        command.rawTables["g_group_remaining_ms"]=command.lifetimeMs;
        command.rawTables["g_transform_lifetime_resolved"]=true;
        if(!command.preflightOnly) {
            for(auto &entity:staged->entities)if(entity.command.family=="g_transform") {
                entity.expires=now;
                for(auto &fx:staged->preparedEffects)if(fx.id==entity.effectId)fx.expires=now;
            }
            staged->gExpires=now+command.lifetimeMs;staged->gSkill=command.key.skillId;
            staged->record({{"event","g_transform_replaced"},{"skill",command.key.json()},
                {"expires",staged->gExpires},{"extension_ms",live?extension:0},
                {"basis","Source G-2/G-3 explain shared remaining time plus static[2] transform extension"}});
        }
    }
    size_t preflightEntities=staged->entities.size(),preflightEffects=staged->preparedEffects.size();
    auto preflightAttacks=staged->attackIds,preflightVisuals=staged->effectIds;
    for(const auto &frame:bodyFrames)if(!frame.skill&&frame.actionSequence!=staged->basicSequence&&
        ((world_.identity().jobId==5&&(normalize(frame.motion.tag)=="[attack motion]"||frame.sourceFamily=="female_gunner_basic_jump_shoot"))||
         (world_.identity().jobId==2&&frame.gunnerScheduledShot))) {
        staged->basicSequence=frame.actionSequence;
        if(actor.weaponSubtype<0||actor.weaponSubtype>4)continue;
        const auto &source=basicBulletSource(world_.pvf_,*staged->sourceCache,actor.weaponSubtype,
            frame.sourceFamily=="female_gunner_basic_jump_shoot"?2:frame.gunnerDownShot?1:0);
        const auto &object=source.object;const auto &path=object.path;
        const auto motion=object.values("[basic motion]"),attack=object.values("[attack info]");
        if(motion.size()!=1||!motion[0].is_string()||attack.size()!=1||!attack[0].is_string())
            throw std::invalid_argument("Female Gunner ordinary bullet object binding is incomplete");
        FemaleGunnerSkillCommand bullet;bullet.kind=FemaleGunnerCommandKind::Launch;bullet.key={world_.identity().jobId,0};
        bullet.skillSource=world_.experimentalRuntime_->plan().characterSource;bullet.motionSource=frame.motion.source;
        bullet.objectSource=makeSourceRef(world_.pvf_,path);
        bullet.animationSource=makeSourceRef(world_.pvf_,effectResource(world_.pvf_,path,motion[0].get<std::string>()));
        bullet.attackSource=makeSourceRef(world_.pvf_,effectResource(world_.pvf_,path,attack[0].get<std::string>()));
        bullet.actionSequence=frame.actionSequence;bullet.family="ordinary_bullet";bullet.effectRole="projectile";
        anchorBasicBullet(world_.pvf_,world_.assets_,*staged->sourceCache,world_.characterAppearance(),frame,bullet,world_.renderProfile());
        bullet.rawTables["basic_source_binding"]=source.trace;
        bullet.speed=1200;bullet.range=900;bullet.lifetimeMs=750;
        if(world_.identity().jobId==2) {
            const auto particle=readGunnerBasicParticle(world_.pvf_,source.particle);
            bullet.speed=particle.axisVelocity[0];bullet.range=0;bullet.lifetimeMs=particle.lifetimeMs;
            bullet.rawTables["basic_particle_motion"]=particle.snapshot();
            Json aim={{"policy","inferred-source-centerline-projection-v1"},{"pitch_degrees",particle.pitchDegrees},
                {"source_pitch_degrees",particle.pitchDegrees},{"target",Json()},{"native_BF9060_equality",false}};
            if(!actor.gunnerAimTarget.is_null()&&particle.axisVelocity[0]>0) {
                const auto &center=actor.gunnerAimTarget.at("center");
                const double ahead=(center[0].get<double>()-actor.x)*actor.direction-bullet.offsetX;
                if(ahead>0) {
                    const double pitch=std::atan2(center[2].get<double>()-actor.z-bullet.offsetZ,ahead)*180.0/std::acos(-1.0);
                    aim["policy"]="inferred-nearest-forward-source-hurtbox-aim-v1";aim["pitch_degrees"]=pitch;
                    aim["additional_aim_degrees"]=pitch-particle.pitchDegrees;aim["target"]=actor.gunnerAimTarget;
                    aim["basis"]="Current1031 BF9060 produces per-shot aim outputs in addition to source Up/Down angle; this host targets a real current MOB type14 box center without altering geometry";
                    aim["unverified"]="Native target priority, eligibility, coordinate socket, aim clamps, random cone and protection branches";
                }
            }
            bullet.rawTables["basic_aim"]=std::move(aim);
        }
        bullet.rawTables["basic_attack"]=true;bullet.rawTables["basic_motion"]=frame.motion.tag;
        bullet.evidence.push_back({{"policy","inferred-1031-gunner-basic-projectile-v1"},{"classification","inferred"},
            {"basis",world_.identity().jobId==2?
                "Current male GunInfo Up PTL selects registered OBJ/ANI/ATK, source equal-range axes and lifetime; equipped pixels infer origin, centerline host ignores unverified random rotation distribution":
                "Current GunnerDefaultGunInfo subtype and Up/Jump PTL selects the registered OBJ/ANI/ATK. Weapon/projectile pixels infer origin; female velocity remains reconstructed."}});
        const auto extra=world_.identity().jobId==5?femaleGunnerAdditionalBasicShots(world_.effectiveFemaleGunnerLevels(),
            world_.experimentalRuntime_->plan(),actor.weaponSubtype):FemaleGunnerShotCountModifier{};
        if(extra.extraShots>128)throw std::length_error("Female Gunner ordinary source shot count exceeds supported action budget");
        const auto totalShots=1+extra.extraShots;
        for(uint32_t shot=0;shot<totalShots;++shot) {
        bullet.pulseId=shot;
        const auto ordinaryMotion=world_.assets_.animation(frame.motion.source.memberPath);
        const auto ordinarySpan=ordinaryMotion->duration-(ordinaryMotion->frames.size()>1&&
            ordinaryMotion->frames.back().duration>=9999?ordinaryMotion->frames.back().duration:0);
        bullet.releaseDelayMs=int64_t(ordinarySpan)*shot/totalShots;
        bullet.rawTables["additional_shot_modifier"]=extra.trace;
        bullet.evidence.push_back({{"policy","inferred-1031-multiple-basic-shot-timing-v1"},{"classification","inferred"},
            {"source_shots",totalShots},{"shot",shot},{"delay_ms",bullet.releaseDelayMs},
            {"basis","Additional source musket shots use the active ordinary span before the controller-held terminal pose; native per-shot timing is unverified"}});
        const auto ordinaryIndex=allCommands.size();allCommands.push_back(bullet);
        std::vector<const FemaleGunnerSkillCommand*> liveAmmo;
        for(const auto &[ammoKey,ammoBuff]:staged->buffs)if(ammoBuff.command.family=="ammo_enchantment"&&ammoBuff.command.count)
            liveAmmo.push_back(&ammoBuff.command);
        if(liveAmmo.size()==1) {
            auto selected=select1031AmmoFlight(world_.pvf_,*liveAmmo.front(),actor.weaponSubtype);
            allCommands.at(ordinaryIndex).rawTables["ammo_visual_binding"]=selected.trace;
            ammoFlightSelections[{bullet.actionSequence,bullet.pulseId}]=std::move(selected);
        } else if(liveAmmo.size()>1) {
            allCommands.at(ordinaryIndex).rawTables["ammo_visual_binding"]={{"policy","inferred-host-1031-default-ammo-flight-selector-v1"},
                {"result","multiple_live_ammo_buffs_visual_priority_unresolved_preserve_basic_visual"},{"active_count",liveAmmo.size()}};
            allCommands.at(ordinaryIndex).diagnostics.push_back({{"code","ammo_visual_priority_unresolved"},
                {"message","Multiple live host ammo buffs; native projectile stores one kind, but upstream exclusivity/priority is unresolved"}});
        }
        for(auto &[key,buff]:staged->buffs)if(buff.command.family=="ammo_enchantment"&&buff.command.count) {
            if(key.skillId==1) {
                allCommands.at(ordinaryIndex).parameters=buff.command.parameters;
                allCommands.at(ordinaryIndex).rawTables["flame_source"]=buff.command.rawTables;
                allCommands.at(ordinaryIndex).rawTables["flame_level"]=buff.command.level;
                --buff.command.count;continue;
            }
            auto enchanted=bullet;enchanted.key=key;enchanted.skillSource=buff.command.skillSource;enchanted.level=buff.command.level;
            enchanted.family="enchanted_bullet";enchanted.parameters=buff.command.parameters;enchanted.rawTables=buff.command.rawTables;
            enchanted.rawTables["ammo_source"]=buff.command.snapshot();enchanted.rawTables["element"]=key.skillId==1?0:key.skillId==2?1:3;
            enchanted.rawTables["magical"]=key.skillId!=52;
            enchanted.rawTables["visual_suppressed_for_shared_projectile"]=true;
            enchanted.damage=buff.command.damage;enchanted.damage.percent=0;
            for(const auto &parameter:enchanted.parameters)if(parameter.at("label").get<std::string>().find("附加")!=std::string::npos&&
                parameter.at("label").get<std::string>().find("攻击力")!=std::string::npos){enchanted.damage.percent=parameter.at("value").get<float>();break;}
            enchanted.damage.replacesAttackCoefficients=true;
            allCommands.push_back(std::move(enchanted));--buff.command.count;
            staged->record({{"event","ammo_consumed"},{"key",key.json()},{"remaining",buff.command.count},{"action",frame.actionSequence}});
        }
        }
    }
    std::vector<FemaleGunnerSkillCommand> impactPreflight;
    for(const auto &bullet:allCommands)if(bullet.rawTables.contains("flame_source"))
        for(auto impact:femaleGunnerFlameImpactCommands(world_.pvf_,world_.assets_,flameSource(bullet,world_.pvf_))) {
            impact.preflightOnly=true;impactPreflight.push_back(std::move(impact));
        }
    allCommands.insert(allCommands.end(),impactPreflight.begin(),impactPreflight.end());
    for (const auto &command : expandFemaleGunnerEntities(world_.pvf_,world_.assets_,allCommands)) {
        const bool maleBasic=world_.identity().jobId==2&&command.key==SkillKey{2,0}&&command.family=="ordinary_bullet"&&
            command.rawTables.value("basic_attack",false);
        if ((!maleBasic&&command.key.jobId != 5) || command.key.jobId!=world_.identity().jobId || command.skillSource.memberPath.empty())
            throw std::invalid_argument("Female Gunner command has no exact source skill");
        checkRef(world_.pvf_, command.skillSource);
        for (const auto &ref : {command.motionSource, command.animationSource, command.attackSource, command.objectSource})
            if (ref) checkRef(world_.pvf_, *ref);
        for (const auto value : {command.x, command.y, command.z, command.offsetX, command.offsetY, command.offsetZ,
                                 command.speed, command.range}) requireFinite(value, "command operand");
        if (command.level < 1 || command.lifetimeMs < 0 || command.intervalMs < 0 || command.releaseDelayMs < 0 || command.count > 4096)
            throw std::invalid_argument("Female Gunner command is outside supported lifetime/count bounds");
        std::optional<AttackDamageDefinition> checkedAttack;
        std::optional<SkillStatusApplication> checkedStatus;
        std::shared_ptr<const Animation> checkedAnimation,checkedVisual;
        std::string visualPath;double visualOffsetX=0,visualOffsetZ=0;
        if (command.attackSource) {
            checkedAttack=readAttackDamage(world_.pvf_.script(command.attackSource->memberPath),AttackStatusConsumer::StunHostV1);
            if (!checkedAttack->usable()) throw std::invalid_argument("Female Gunner required ATK consumer is unavailable: "+checkedAttack->snapshot().dump());
            readAttackResponse(checkedAttack->source);
            if(!command.rawTables.value("basic_attack",false)) {
                checkedStatus=readFemaleGunnerSkillAttackStatuses(command,world_.experimentalRuntime_->plan());
                if(!checkedStatus->usable())throw std::invalid_argument("Female Gunner skill status setter is unusable: "+checkedStatus->snapshot().dump());
            }
            if(command.rawTables.contains("ammo_source")) {
                checkedAttack->element=command.rawTables.at("element");
                checkedAttack->type=command.rawTables.at("magical").get<bool>()?DamageAttackType::Magical:DamageAttackType::Physical;
            }
        }
        if (command.animationSource) {
            checkedAnimation=world_.assets_.animation(command.animationSource->memberPath);
            checkedVisual=checkedAnimation;visualPath=command.animationSource->memberPath;
            if (checkedAnimation->frames.empty() || checkedAnimation->duration <= 0)
                throw std::invalid_argument("Female Gunner entity animation has no positive source duration");
            const auto validateVisual=[&](const auto &self,const std::string &path,size_t depth)->void {
                if(depth>12)throw std::invalid_argument("Female Gunner ALS dependency depth exceeds supported limit");
                if(!validatedVisuals.insert(path).second)return;
                const auto visual=world_.assets_.animation(path);
                for(const auto &frame:visual->frames)if(!frame.image.empty())world_.assets_.pixels(frame.image,frame.imageFrame);
                const auto layers=animationEffectEvents(world_.pvf_,world_.assets_,path);
                for(const auto &event:layers.events)if(event.kind!=EffectEventKind::Remove)self(self,event.animation,depth+1);
            };
            if(!command.rawTables.value("body_motion_attack",false))validateVisual(validateVisual,command.animationSource->memberPath,0);
            if(command.family=="ordinary_bullet"&&command.rawTables.value("basic_attack",false)) {
                const auto selected=ammoFlightSelections.find({command.actionSequence,command.pulseId});
                if(selected!=ammoFlightSelections.end()&&selected->second.source) {
                    checkRef(world_.pvf_,*selected->second.source);
                    visualPath=selected->second.source->memberPath;checkedVisual=world_.assets_.animation(visualPath);
                    if(checkedVisual->frames.empty()||checkedVisual->duration<=0)
                        throw std::invalid_argument("1031 attribute flight visual has no positive source duration");
                    validateVisual(validateVisual,visualPath,0);
                    const auto point=visibleSourcePoint(world_.pvf_,world_.assets_,*staged->sourceCache,visualPath,{0,0},false,world_.renderProfile());
                    const auto &coordinate=command.rawTables.at("coordinate_trace");
                    const auto original=coordinate.at("bullet_sprite").is_null()?Json::array({0,0}):
                        coordinate.at("bullet_sprite").at("local_point");
                    visualOffsetX=original[0].get<double>()-(point?point->x:0);
                    visualOffsetZ=(point?point->y:0)-original[1].get<double>();
                }
            }
        }
        const bool damaging = command.kind == FemaleGunnerCommandKind::Strike || command.kind == FemaleGunnerCommandKind::Launch ||
                              command.kind == FemaleGunnerCommandKind::Spawn;
        if (damaging && (!checkedAttack || (!command.box && !checkedAnimation)))
            throw std::invalid_argument("Female Gunner damaging command lacks an executable source ATK/geometry");
        if (command.kind == FemaleGunnerCommandKind::Buff && command.lifetimeMs <= 0 && command.family != "ammo_enchantment")
            throw std::invalid_argument("Female Gunner buff has no evaluated source duration");
        if(command.releaseDelayMs>INT32_MAX||command.releaseDelayMs>INT64_MAX-world_.nowMs()||
            command.lifetimeMs>INT32_MAX||command.lifetimeMs>INT64_MAX-world_.nowMs()-command.releaseDelayMs)
            throw std::invalid_argument("Female Gunner source phase time bounds overflow before publication");
        if (command.preflightOnly) {
            if(damaging)preflightAttacks.next();
            if(checkedAnimation&&preflightVisuals.next()>INT32_MAX)throw std::overflow_error("Female Gunner preflight visual ID overflow");
            if(command.kind!=FemaleGunnerCommandKind::Buff&&command.kind!=FemaleGunnerCommandKind::Clear){
                ++preflightEntities;if(checkedAnimation)++preflightEffects;
                if(preflightEntities>512||preflightEffects>2048)throw std::length_error("Female Gunner complete source action exceeds entity capacity");
            }
            continue;
        }
        if (command.kind == FemaleGunnerCommandKind::Clear) {
            if(command.effectRole=="stop_channel") {
                if(!command.actionSequence||!supportedInputChannel(command))
                    throw std::invalid_argument("Unsupported or unowned female Gunner channel stop");
                const auto now=world_.nowMs();std::set<int> retiredVisuals;size_t retired=0;
                staged->entities.erase(std::remove_if(staged->entities.begin(),staged->entities.end(),[&](const auto &entity) {
                    const bool match=entity.command.key==command.key&&entity.command.actionSequence==command.actionSequence;
                    const bool stop=match&&(entity.command.followCaster||entity.born>=now);
                    if(stop){++retired;if(entity.effectId>=0)retiredVisuals.insert(entity.effectId);}
                    return stop;
                }),staged->entities.end());
                // Retire every already-created ALS descendant with its owning
                // channel visual. An unfired visual is removed before it can
                // dispatch a future sound/frame/attack event.
                bool changed=true;
                while(changed){changed=false;for(const auto &visual:staged->preparedEffects)
                    if(retiredVisuals.count(visual.alsParentId)&&retiredVisuals.insert(visual.id).second)changed=true;}
                staged->preparedEffects.erase(std::remove_if(staged->preparedEffects.begin(),staged->preparedEffects.end(),
                    [&](const auto &visual){return retiredVisuals.count(visual.id)>0;}),staged->preparedEffects.end());
                staged->record({{"event","channel_stopped"},{"skill",command.key.json()},
                    {"action",command.actionSequence},{"entities_retired",retired},{"visuals_retired",retiredVisuals.size()},
                    {"reason",command.rawTables.value("channel_stop",Json::object()).value("reason",std::string("unspecified"))},
                    {"already_fired_detached_projectiles","preserved"}});continue;
            }
            if(command.effectRole=="end_mode") {
                staged->buffs.erase(command.key);
                staged->record({{"event","mode_ended"},{"skill",command.key.json()}});continue;
            }
            const auto now=world_.nowMs();
            size_t detonated=0;
            for (auto &entity : staged->entities) if(entity.command.effectRole=="robot_attack" &&
                (entity.command.rawTables.value("behavior",std::string())=="seek_explode"||
                 entity.command.rawTables.value("behavior",std::string())=="timer_explode") && now<=entity.born &&
                (command.range<=0||std::hypot(entity.x-actor.x,entity.y-actor.y)<=command.range)) {
                const auto duration=entity.animation?entity.animation->duration:1;
                entity.born=entity.nextPulse=now;entity.expires=now+duration;entity.hit.clear();entity.lastAge=-1;
                entity.command.x=entity.x;entity.command.y=entity.y;entity.command.offsetX=0;entity.command.offsetY=0;
                entity.command.speed=0;entity.command.intervalMs=0;entity.pulse=0;
                for(auto &fx:staged->preparedEffects)if(fx.id==entity.effectId){fx.born=now;fx.expires=entity.expires;fx.playback.clear();fx.clockBound=false;fx.animationClock.reset();}
                for(auto &body:staged->entities)if(body.command.effectRole=="robot_body"&&body.command.key==entity.command.key&&
                    body.command.actionSequence==entity.command.actionSequence&&body.command.pulseId==entity.command.pulseId) {
                    body.expires=now;
                    for(auto &fx:staged->preparedEffects)if(fx.id==body.effectId)fx.expires=now;
                }
                ++detonated;
            }
            staged->record({{"event", "robot_detonation"}, {"skill", command.key.json()},{"count",detonated},
                {"basis","1031 robotsexplosion.skl limits ordinary detonation to nearby RX78/EZ8"}}); continue;
        }
        if (command.kind == FemaleGunnerCommandKind::Stage && !command.animationSource) {
            // The player renderer consumes the body motion exactly once.
            staged->record({{"event", "source_stage"}, {"command", commandReceipt(command)}}); continue;
        }
        if (command.kind == FemaleGunnerCommandKind::Buff) {
            if(command.lifetimeMs>INT32_MAX||command.lifetimeMs>INT64_MAX-world_.nowMs())throw std::invalid_argument("Female Gunner buff expiry overflow");
            const auto expiry=command.family=="ammo_enchantment" ? INT64_MAX : world_.nowMs()+command.lifetimeMs;
            staged->buffs[command.key] = {command, expiry};
            staged->record({{"event", "buff_applied"}, {"command", commandReceipt(command)}}); continue;
        }
        State::Entity entity; entity.command = command; entity.owner = world_.player.handle;
        if(command.rawTables.contains("flame_impact")) {
            const auto special=femaleGunnerFlameImpactCommands(world_.pvf_,world_.assets_,command,{"fort"});
            const auto ordinal=command.rawTables.at("flame_impact").at("ordinal").get<size_t>();
            if(ordinal>=special.size())throw std::invalid_argument("Flame source explosion ordinal is unavailable");
            entity.flameSpecialDamage=special[ordinal].damage;
        }
        if(command.releaseDelayMs>INT32_MAX||command.releaseDelayMs>INT64_MAX-world_.nowMs())throw std::invalid_argument("Female Gunner phase release overflow");
        entity.born = entity.nextPulse = world_.nowMs()+command.releaseDelayMs;
        const bool atContact=command.rawTables.value("world_contact_origin",false);
        entity.command.x = atContact?command.x:actor.x; entity.command.y = atContact?command.y:actor.y; entity.command.z = atContact?command.z:actor.z;
        entity.x = entity.command.x + actor.direction * command.offsetX; entity.y = entity.command.y + command.offsetY;
        entity.z = entity.command.z + command.offsetZ; entity.command.direction = actor.direction;
        if (checkedAttack) {
            entity.attack = std::move(checkedAttack);
            entity.response = world_.characterAttackResponse(entity.attack->source);
            entity.status=std::move(checkedStatus);
        } else if (damaging) throw std::invalid_argument("Female Gunner damaging entity has no source ATK");
        entity.animation = std::move(checkedAnimation);entity.visualAnimation=std::move(checkedVisual);
        if(command.rawTables.contains("basic_particle_motion")) {
            const auto &receipt=command.rawTables.at("basic_particle_motion");
            const auto source=world_.pvf_.script(receipt.at("source").at("member_path").get<std::string>());
            entity.basicParticle=readGunnerBasicParticle(world_.pvf_,source);
            if(entity.basicParticle->snapshot()!=receipt)throw std::invalid_argument("Basic PTL source motion receipt changed");
            entity.basicPitchDegrees=command.rawTables.at("basic_aim").at("pitch_degrees").get<double>();
            requireFinite(entity.basicPitchDegrees,"basic aim pitch");
        }
        entity.visualOffsetX=visualOffsetX;entity.visualOffsetZ=visualOffsetZ;
        if (damaging && !command.box && !entity.animation)
            throw std::invalid_argument("Female Gunner damaging entity has no source animation/explicit controller box");
        const auto life = command.lifetimeMs > 0 ? command.lifetimeMs : entity.animation ? entity.animation->duration : 1;
        if (life > INT32_MAX || life > INT64_MAX - entity.born)
            throw std::invalid_argument("Female Gunner entity expiry exceeds simulation bounds");
        entity.expires = entity.born + life;
        if(command.rawTables.value("action_bound_visual",false)) {
            if(command.kind!=FemaleGunnerCommandKind::Stage||command.attackSource||!command.actionSequence||
               !command.motionSource||!command.rawTables.contains("stage_visual_parent_motion"))
                throw std::invalid_argument("Invalid action-owned stage visual");
            // The body stage is the deadline. Independent non-loop source
            // animation may end and hold its own last pose until that stage
            // retires; its clock must never be stretched to the body cursor.
            entity.expires=INT64_MAX;
        }
        if(command.family=="g_transform"&&staged->gExpires>0)entity.expires=std::min(entity.expires,staged->gExpires);
        if (damaging) entity.attackId = staged->attackIds.next();
        if (entity.visualAnimation && !command.rawTables.value("body_motion_attack",false)&&
            !command.rawTables.value("visual_suppressed_for_shared_projectile",false)) {
            const auto id = staged->effectIds.next();
            if (id > INT32_MAX) throw std::overflow_error("Female Gunner visual ID exceeds renderer range");
            entity.effectId = int(id);
            Effect visual; visual.id = entity.effectId; visual.skill = command.key.skillId;
            visual.animation = visualPath; visual.born = entity.born; visual.expires = entity.expires;
            visual.x = visual.px = entity.x+actor.direction*entity.visualOffsetX; visual.y = visual.py = entity.y+entity.visualOffsetY; visual.z = entity.z+entity.visualOffsetZ;
            visual.dir = actor.direction; visual.damageEnabled = false; visual.layer = 1;
            visual.loop = command.rawTables.contains("visual_source_loop")?command.rawTables.at("visual_source_loop").get<bool>():life > entity.visualAnimation->duration;
            visual.layer=command.rawTables.value("visual_layer",1);
            visual.attached=command.rawTables.value("action_bound_visual",false);
            visual.phase = std::string("female-gunner:") + command.family;
            visual.resourceSource = command.objectSource ? command.objectSource->memberPath : command.skillSource.memberPath;
            // Position is owned here, so idle()/hit interruptions cannot erase
            // a detached projectile or a source-duration buff by attachment.
            visual.projectileSource = commandReceipt(command);
            if(visualPath!=command.animationSource->memberPath) {
                visual.projectileSource["ammo_visual_binding"]["collision_animation_preserved"]=command.animationSource->json();
                visual.projectileSource["ammo_visual_binding"]["visual_offset_xyz"]={entity.visualOffsetX,entity.visualOffsetY,entity.visualOffsetZ};
                visual.projectileSource["ammo_visual_binding"]["visual_alignment_classification"]="Inferred visible-center alignment to existing equipped muzzle; native attachment setters unresolved";
            }
            staged->preparedEffects.push_back(std::move(visual));
        }
        if (staged->entities.size() >= 512 || staged->preparedEffects.size() > 2048)
            throw std::invalid_argument("Female Gunner active entity/visual limit exceeded before publication");
        staged->record({{"event", "entity_prepared"}, {"command", commandReceipt(command)}, {"attack_instance", entity.attackId}});
        staged->entities.push_back(std::move(entity));
    }
    auto requiredIds = staged->attackIds;
    for (size_t i = 0; i < reservedBodyAttacks; ++i) requiredIds.next();
    return std::unique_ptr<FemaleGunnerWorld>(new FemaleGunnerWorld(world_, std::move(staged)));
}
void FemaleGunnerWorld::publish(std::unique_ptr<FemaleGunnerWorld> candidate) noexcept {
    if (!candidate || &candidate->world_ != &world_ || !candidate->state_->prepared) std::terminate();
    world_.effects.swap(candidate->state_->preparedEffects);
    world_.ids_.attacks.merge(candidate->state_->attackIds);
    world_.effectIds_.merge(candidate->state_->effectIds);
    candidate->state_->prepared = false; candidate->state_->preparedEffects.clear();
    state_.swap(candidate->state_);
}
void FemaleGunnerWorld::clear(const std::string &reason) noexcept {
    // Scene/character/reset callers already own removal of the visual vector.
    for(auto &target:world_.monsters)if(state_->captures.count(target.handle))target.capturedBy=-1;
    state_->captures.clear();state_->entities.clear(); state_->buffs.clear(); state_->preparedEffects.clear();state_->basicSequence=0;
    state_->gExpires=0;state_->gSkill=0;
}
void FemaleGunnerWorld::capture(Actor &target,SkillKey key) {
    if(target.dead||target.life!=ActorLife::Alive||!world_.explorationAllowsIncoming(target)||
        (world_.mapExplorationActive_&&!world_.explorationConsumers_.at(target.handle).captureAllowed))return;
    if(key.skillId!=6&&key.skillId!=14)return;
    if(!state_->captures.empty()&&!state_->captures.count(target.handle))return;
    target.capturedBy=0;target.vx=target.vy=target.vz=0;
    state_->captures[target.handle]={key,world_.nowMs()+1500};
    state_->record({{"event","grab_accepted"},{"target",target.handle.json()},{"skill",key.json()},
        {"policy","inferred-source-grab-stage-v1"}});
}
void FemaleGunnerWorld::applyActor(ExperimentalActorState &actor) const {
    if(world_.identity().jobId!=5)return;
    for(const auto &[key,buff]:state_->buffs)if(world_.nowMs()<buff.expires)actor.femaleGunnerBuffs.push_back(buff.command);
    if(!world_.experimentalRuntime_)return;
    const auto result=evaluateFemaleGunnerActorModifiers(actor.femaleGunnerBuffs,
        world_.effectiveFemaleGunnerLevels(),world_.experimentalRuntime_->plan(),actor.weaponSubtype);
    actor.movePerMille*=result.moveMultiplier;actor.attackPerMille*=result.attackMultiplier;
}
bool FemaleGunnerWorld::updateCapturedPose(Actor &target) {
    const auto found=state_->captures.find(target.handle);
    if(found==state_->captures.end())return false;
    target.x=world_.player.x+world_.player.dir*65;target.y=world_.player.y;
    target.z=found->second.first.skillId==6?0:70;target.vx=target.vy=target.vz=0;
    return true;
}
bool FemaleGunnerWorld::invulnerable() const {
    const auto found=state_->buffs.find({5,190});
    return found!=state_->buffs.end()&&world_.nowMs()<found->second.expires;
}
bool FemaleGunnerWorld::neutralReactionReady() const noexcept {
    return state_->entities.empty()&&state_->captures.empty()&&!state_->prepared;
}
bool FemaleGunnerWorld::skillProjectionReady() const noexcept {
    return neutralReactionReady()&&state_->buffs.empty();
}
std::unique_ptr<FemaleGunnerWorld> FemaleGunnerWorld::prepareNeutralDeath() const {
    if(!neutralReactionReady())throw std::invalid_argument("Female Gunner neutral death still gates entities/captures");
    auto candidate=std::make_unique<State>(*state_);
    candidate->buffs.clear();candidate->preparedEffects.clear();candidate->basicSequence=0;
    candidate->gExpires=0;candidate->gSkill=0;
    candidate->record({{"kind","prepared_neutral_owner_death"},{"retired_buffs",state_->buffs.size()}});
    return std::unique_ptr<FemaleGunnerWorld>(new FemaleGunnerWorld(world_,std::move(candidate)));
}
void FemaleGunnerWorld::publishNeutralDeath(std::shared_ptr<FemaleGunnerWorld> candidate) noexcept {
    if(!candidate||&candidate->world_!=&world_||!candidate->neutralReactionReady())std::terminate();
    state_.swap(candidate->state_);
}
void FemaleGunnerWorld::applyDefense(DamageRequest &request) const {
    if(!world_.experimentalRuntime_||world_.identity().jobId!=5)return;
    std::vector<FemaleGunnerSkillCommand> buffs;
    for(const auto &[key,buff]:state_->buffs)if(world_.nowMs()<buff.expires)buffs.push_back(buff.command);
    const auto result=evaluateFemaleGunnerActorModifiers(buffs,world_.effectiveFemaleGunnerLevels(),
        world_.experimentalRuntime_->plan(),-1);
    request.targetStats.physicalDefense+=float(result.physicalDefense);
    request.targetStats.magicalDefense+=float(result.magicalDefense);
    if(world_.combatAttributes_) {
        // Reuse the already selected primary-defense policy; immutable CHR/EQU
        // defense already contains their VIT/SPR, so add only the live passive.
        request.targetStats.physicalDefense+=float(float(result.vitality)*world_.combatAttributes_->vitalityDefenseFactor);
        request.targetStats.magicalDefense+=float(float(result.spirit)*world_.combatAttributes_->spiritDefenseFactor);
    }
    request.targetStats.evasionPercent+=float(result.evasionPercent);
    const bool magical=request.attack.type==DamageAttackType::Magical||
        (request.attack.type==DamageAttackType::Weapon&&request.weaponType==DamageAttackType::Magical);
    double reduction=magical?result.magicalDamageReductionPercent:result.physicalDamageReductionPercent;
    for(const auto &buff:buffs)if(buff.key.skillId==10)for(const auto &p:buff.parameters) {
        const auto label=p.at("label").get<std::string>();
        if(label.find(magical?"魔攻吸收率":"物攻吸收率")!=std::string::npos)reduction=std::max(reduction,p.at("value").get<double>());
    }
    request.skill.totalMultiplier*=float(std::clamp(1-reduction/100.0,0.0,1.0));
    request.targetStats.trace.push_back({{"policy","inferred-1031-female-gunner-defensive-skill-consumers-v1"},
        {"source_modifiers",result.snapshot()},{"absorbed_percent",reduction},{"native_confirmed",false}});
}
void FemaleGunnerWorld::applyAttack(DamageRequest &request,std::optional<SkillKey> key,const std::string &motion,const std::string &family) const {
    if(!world_.experimentalRuntime_||world_.identity().jobId!=5)return;
    std::vector<FemaleGunnerSkillCommand> buffs;
    for(const auto &[identity,buff]:state_->buffs)if(world_.nowMs()<buff.expires)buffs.push_back(buff.command);
    FemaleGunnerAttackContext context;context.attackSkill=key;context.basicMotion=motion;context.family=family;
    context.characterLevel=world_.characterLevel;
    context.airborne=world_.player.z>0;
    if(world_.combatAttributes_)for(const auto &e:world_.combatAttributes_->equipmentSources)if(normalize(e.equippedSlot)=="[weapon]") {
        const auto subtype=e.source.values("[sub type]");if(subtype.size()==1&&subtype[0].is_number_integer())context.weaponSubtype=subtype[0].get<int>();
    }
    if(const auto *target=static_cast<const World &>(world_).resolveActor(request.target))
        context.backAttack=(world_.player.x-target->x)*target->dir<0;
    applyFemaleGunnerAttackOperands(request,buffs,world_.effectiveFemaleGunnerLevels(),
        world_.experimentalRuntime_->plan(),context);
}
void FemaleGunnerWorld::advance() {
    const auto now = world_.nowMs();
    if ((world_.identity().jobId != 5&&world_.identity().jobId != 2) || world_.player.dead || world_.player.life != ActorLife::Alive) {
        for (const auto &entity : state_->entities) for (auto &fx : world_.effects)
            if (fx.id == entity.effectId) fx.expires = std::min(fx.expires, now);
        clear("owner_unavailable"); return;
    }
    for (auto it = state_->buffs.begin(); it != state_->buffs.end();)
        if (now >= it->second.expires || (it->second.command.family=="ammo_enchantment"&&!it->second.command.count))
            it = state_->buffs.erase(it); else ++it;
    if(world_.identity().jobId==5&&world_.baseAttributes_&&world_.experimentalRuntime_) {
        std::vector<FemaleGunnerSkillCommand> buffs;
        for(const auto &[key,buff]:state_->buffs)buffs.push_back(buff.command);
        const auto modifiers=evaluateFemaleGunnerActorModifiers(buffs,world_.effectiveFemaleGunnerLevels(),
            world_.experimentalRuntime_->plan(),-1);
        const float adjusted=float(world_.baseAttributes_->integer(ChrAttribute::HpMax))*float(modifiers.hpMaximumMultiplier);
        if(!std::isfinite(adjusted)||adjusted<1||double(adjusted)>INT32_MAX)throw std::overflow_error("Female Gunner source maximum HP overflow");
        world_.player.maxHp=int(adjusted);world_.player.hp=std::min(world_.player.hp,world_.player.maxHp);
    }
    if(now>=state_->gExpires){state_->gExpires=0;state_->gSkill=0;}
    // Exact stage ownership retires appearance without touching detached
    // shots, other skills or the existing sustained-channel stop protocol.
    std::set<int> retiredStageVisuals;
    const auto liveAction=world_.experimentalRuntime_->activeActionSequence();
    for(auto &entity:state_->entities)if(entity.command.rawTables.value("action_bound_visual",false)) {
        // begin() creates a distinct monotonic action for every exact source
        // motion stage. The checked receipt keeps that motion's SourceRef;
        // matching this token cannot retain it across another stage.
        if(!liveAction||*liveAction!=entity.command.actionSequence) {
            entity.expires=now;if(entity.effectId>=0)retiredStageVisuals.insert(entity.effectId);
        } else if(world_.player.hitStopped) {
            // Attached visual source clocks pause in the existing effect
            // host. Avoid dispatching its source frame sounds from wall time.
            continue;
        }
    }
    bool moreStageChildren=true;
    while(moreStageChildren){moreStageChildren=false;for(const auto &effect:world_.effects)
        if(retiredStageVisuals.count(effect.alsParentId)&&retiredStageVisuals.insert(effect.id).second)moreStageChildren=true;}
    for(auto &effect:world_.effects)if(retiredStageVisuals.count(effect.id))effect.expires=std::min(effect.expires,now);
    for(auto it=state_->captures.begin();it!=state_->captures.end();) {
        auto *target=world_.resolveActor(it->first);
        const auto action=world_.experimentalRuntime_->activeActionSequence();
        if(!target||target->dead||now>=it->second.second||!action) {
            if(target){target->capturedBy=-1;target->recovery=1;target->vz=0;}
            it=state_->captures.erase(it);
        } else {target->z=it->second.first.skillId==6?0:70;++it;}
    }
    // A source robot body owns pursuit/proximity; its matched delayed attack
    // follows that body and is activated once. Death/scene retirement removes
    // the same handle-owned group instead of leaking a future explosion.
    for(auto &body:state_->entities)if((body.command.effectRole=="robot_body"||body.command.effectRole=="mine_body")&&now>=body.born&&now<body.expires) {
        if(body.command.followCaster) {body.x=world_.player.x+world_.player.dir*body.command.offsetX;body.y=world_.player.y+body.command.offsetY;body.z=world_.player.z+body.command.offsetZ;}
        const auto behavior=body.command.rawTables.value("behavior",std::string());
        Actor *nearest=nullptr;double best=std::numeric_limits<double>::max();
        for(auto &target:world_.monsters)if(!target.dead&&target.life==ActorLife::Alive&&world_.explorationAllowsIncoming(target)) {
            const double d=std::hypot(target.x-body.x,target.y-body.y);if(d<best){best=d;nearest=&target;}
        }
        if(behavior=="seek_explode"&&nearest&&best>30) {
            const double step=std::min(best,150.0/60.0);
            const double x=body.x+(nearest->x-body.x)*step/best,y=body.y+(nearest->y-body.y)*step/best;
            if(world_.canWalk(x,y)){body.x=x;body.y=y;body.command.x=x-body.command.direction*body.command.offsetX;body.command.y=y-body.command.offsetY;}
        }
        const bool trigger=(behavior=="seek_explode"&&best<=45)||(behavior=="proximity"&&best<=90);
        for(auto &attack:state_->entities)if(attack.command.actionSequence==body.command.actionSequence&&
            attack.command.key==body.command.key&&attack.command.pulseId==body.command.pulseId&&
            (attack.command.effectRole=="robot_attack"||attack.command.effectRole=="explosion")) {
            if(now<=attack.born) {
                attack.x=body.x;attack.y=body.y;attack.command.x=body.x-attack.command.direction*attack.command.offsetX;attack.command.y=body.y-attack.command.offsetY;
                if(trigger){const auto life=attack.expires-attack.born;attack.born=attack.nextPulse=now;attack.expires=now+life;body.expires=now;}
                for(auto &fx:world_.effects)if(fx.id==attack.effectId){fx.x=fx.px=attack.x;fx.y=fx.py=attack.y;fx.born=attack.born;fx.expires=attack.expires;}
            }
        }
    }
    std::vector<FemaleGunnerSkillCommand> contactSpawns;
    for (auto &entity : state_->entities) {
        if (now < entity.born || entity.owner != world_.player.handle) continue;
        if(entity.command.rawTables.value("action_bound_visual",false)) {
            if(now>=entity.expires||world_.player.hitStopped)continue;
            // The attached effect host shifts birth by the exact paused
            // milliseconds. Share that origin for source sound intervals;
            // never delay events by sampling last tick's cursor here.
            const auto visual=std::find_if(world_.effects.begin(),world_.effects.end(),[&](const auto &fx){return fx.id==entity.effectId;});
            if(visual!=world_.effects.end())entity.born=visual->born;
        }
        const auto age=std::min(now,entity.expires-1)-entity.born;
        if(age<0 || age<=entity.lastAge)continue;
        const auto previousAge=entity.lastAge;
        entity.lastAge=age;
        const auto &command = entity.command;
        const auto previousX=entity.x,previousY=entity.y,previousZ=entity.z;
        if (command.followCaster) {
            entity.x = world_.player.x + world_.player.dir * command.offsetX;
            entity.y = world_.player.y + command.offsetY; entity.z = world_.player.z + command.offsetZ;
        } else if(entity.basicParticle) {
            const auto delta=entity.basicParticle->displacement(int32_t(age));
            const double pitch=entity.basicPitchDegrees*std::acos(-1.0)/180.0;
            entity.x=command.x+command.direction*(command.offsetX+delta[0]*std::cos(pitch)-delta[2]*std::sin(pitch));
            entity.y=command.y+command.offsetY+delta[1];
            entity.z=command.z+command.offsetZ+delta[0]*std::sin(pitch)+delta[2]*std::cos(pitch);
        } else {
            const double distance = command.speed * double(age) / 1000.0;
            entity.x = command.x + command.direction * command.offsetX + command.direction * distance;
            if (command.range > 0 && std::abs(distance) > command.range) { entity.expires = now; continue; }
        }
        if(command.rawTables.value("behavior",std::string())=="arc") {
            const double elapsed=double(age)/1000.0;
            entity.z=std::max(0.0,command.z+command.offsetZ+300*elapsed-500*elapsed*elapsed);
        }
        if(command.rawTables.value("behavior",std::string())=="attach_target") {
            std::vector<std::pair<double,EntityHandle>> eligible;
            const auto range=command.rawTables.value("target_range",1000.0);
            for(auto &target:world_.monsters)if(!target.dead&&target.life==ActorLife::Alive&&world_.explorationAllowsIncoming(target)) {
                const auto distance=std::hypot(target.x-world_.player.x,target.y-world_.player.y);
                if(distance<=range)eligible.push_back({distance,target.handle});
            }
            std::sort(eligible.begin(),eligible.end());
            const bool valid=std::any_of(eligible.begin(),eligible.end(),[&](const auto &entry){return entry.second==entity.boundTarget;});
            if(!valid) {
                entity.boundTarget=eligible.empty()?EntityHandle{}:eligible[command.rawTables.value("ordinal",0u)%eligible.size()].second;
                entity.nextPulse=std::max(entity.nextPulse,now);
            }
            if(const auto *target=world_.resolveActor(entity.boundTarget)) {
                entity.x=target->x+(entity.attack?0:command.offsetX);entity.y=target->y+(entity.attack?0:command.offsetY);
                entity.z=target->z+(entity.attack?0:command.offsetZ);
            }
        }
        if(entity.visualAnimation&&!command.rawTables.value("body_motion_attack",false)&&
            !command.rawTables.value("visual_suppressed_for_shared_projectile",false)) {
            const bool sourceLoop=command.rawTables.contains("visual_source_loop")?
                command.rawTables.at("visual_source_loop").get<bool>():entity.expires-entity.born>entity.visualAnimation->duration;
            visitSourceFrames(*entity.visualAnimation,previousAge,age,sourceLoop,[&](size_t index,int64_t,bool entered) {
                const auto &frame=entity.visualAnimation->frames[index];
                if(entered&&frame.properties.contains("16")&&frame.properties.at("16").is_string())
                    world_.events.push_back({world_.tick,"sound",frame.properties.at("16").get<std::string>()});
            });
        }
        for (auto &visual : world_.effects) if (visual.id == entity.effectId) {
            visual.x = entity.x+command.direction*entity.visualOffsetX; visual.y = entity.y+entity.visualOffsetY; visual.z = entity.z+entity.visualOffsetZ;
        }
        if (!entity.attack || entity.born+age < entity.nextPulse) continue;
        if(command.rawTables.value("behavior",std::string())=="attach_target"&&!entity.boundTarget)continue;
        if (command.intervalMs > 0 && command.count && entity.pulse >= command.count) continue;
        do {
        if (command.intervalMs > 0) {
            entity.hit.clear(); entity.nextPulse += command.intervalMs; ++entity.pulse;
        } else if (!entity.pulse) entity.pulse = 1;
        Actor origin; origin.x = entity.x; origin.y = entity.y; origin.z = entity.z; origin.dir = command.direction;
        std::vector<Box> boxes;
        if (command.box) boxes.push_back(*command.box);
        else if (entity.animation) {
            visitSourceFrames(*entity.animation,previousAge,age,entity.expires-entity.born>entity.animation->duration,[&](size_t frame,int64_t,bool) {
                for(const auto &box:entity.animation->frames[frame].boxes)if(box.type==15)boxes.push_back(box);
            });
        }
        // Swept samples share one attack/pulse/target ledger.
        const auto steps=std::clamp(int(std::ceil(std::hypot(entity.x-previousX,entity.y-previousY)/12)),1,128);
        for(int sample=1;sample<=steps;++sample)for (const auto &box : boxes) {
            const double fraction=double(sample)/steps;
            origin.x=previousX+(entity.x-previousX)*fraction;origin.y=previousY+(entity.y-previousY)*fraction;
            origin.z=previousZ+(entity.z-previousZ)*fraction;
            AttackVolume volume; volume.serial = entity.attackId; volume.pulse = entity.pulse;
            volume.x = origin.x; volume.y = origin.y; volume.z = origin.z; volume.direction = origin.dir;
            volume.box = box; volume.skillId = command.key.skillId; volume.sourceAttack = entity.attack;
            volume.sourceModifiers = command.damage;
            volume.sourceFortModifiers=entity.flameSpecialDamage;
            volume.sourceMotionTag=command.rawTables.value("basic_motion",std::string());volume.sourceAttackFamily=command.family;
            const auto type = world_.experimentalRuntime_->configuration().weaponTypePolicy();
            if (type != "blocked") volume.sourceWeaponType = type == "magical" ? DamageAttackType::Magical : DamageAttackType::Physical;
            world_.attackVolumes.push_back(volume);
            for (auto &target : world_.monsters) {
                if(entity.boundTarget&&target.handle!=entity.boundTarget)continue;
                if((command.family=="grab_ground_shoot"||command.family=="grab_aerial_gatling")&&!state_->captures.count(target.handle))continue;
                CombatBox contact;
                if (target.dead || target.life != ActorLife::Alive || entity.hit.count(target.handle) ||
                    !world_.explorationAllowsIncoming(target) || !world_.overlaps(origin, box, target, &contact)) continue;
                if (!world_.combatAttributes_ || !target.combatAttributes) continue;
                auto accepted = world_.prepareMonsterAcceptedHit(target, "female_gunner_source_entity");
                if (!accepted.ready) continue;
                DamageRequest request; request.attacker = entity.owner; request.target = target.handle;
                request.attackInstance = entity.attackId; request.hitIndex = entity.pulse;
                if(command.objectSource)bindDamageContactRange(request,world_.pvf_.script(command.objectSource->memberPath));
                if(command.family=="ordinary_bullet") {
                    request.contactRange=DamageContactRange::Ranged;
                    request.contactRangeSource={{"policy","inferred-ordinary-bullet-contact-range-v1"},{"classification","inferred_beta"},
                        {"basis","Actual native-registered GunnerDefaultGunInfo/PTL projectile entity, separately from body kick/strike"},
                        {"object",command.objectSource?command.objectSource->json():Json()}};
                }
                request.attackerStats = makeDamageCombatant(*world_.combatAttributes_);
                const auto damagePolicy = DamageResolutionPolicy::inferredPveDamageV1(world_.combatAttributes_->damageConstants);
                request.targetStats = makeDamageCombatant(*target.combatAttributes, damagePolicy);
                request.attack = *entity.attack; request.skill = *volume.sourceModifiers; request.weaponType = volume.sourceWeaponType;
                if(entity.flameSpecialDamage) {
                    bool special=request.targetStats.targetCategory==DamageTargetCategory::Fort;
                    const auto source=world_.pvf_.script(target.monsterPath);
                    for(const auto &category:source.values("[category]"))if(category.is_string()) {
                        const auto value=normalize(category.get<std::string>());
                        special|=value=="plant"||value=="[plant]"||value=="insect"||value=="[insect]";
                    }
                    for(const auto &field:source.fields)special|=normalize(field.tag)=="[plant]"||normalize(field.tag)=="[insect]";
                    if(special)request.skill=*entity.flameSpecialDamage;
                }
                applyAttack(request,command.key.skillId?std::optional<SkillKey>(command.key):std::nullopt,volume.sourceMotionTag,command.family);
                const auto result = world_.resolveActorContact(request, makeMonsterStatusResistances(*target.combatAttributes),entity.status?&*entity.status:nullptr);
                world_.lastDamageTrace_ = result.snapshot();
                if (!result.usable()) {
                    state_->record({{"event", "entity_contact_rejected"}, {"result", result.snapshot()}}); continue;
                }
                entity.hit.insert(target.handle);
                if (result.missed) { world_.events.push_back({world_.tick, "miss", entity.attack->source.path, 0, target.id}); continue; }
                if(command.rawTables.contains("flame_source")) {
                    for(auto impact:femaleGunnerFlameImpactCommands(world_.pvf_,world_.assets_,flameSource(command,world_.pvf_))) {
                        impact.x=target.x;impact.y=target.y;impact.z=0;impact.rawTables["world_contact_origin"]=true;
                        contactSpawns.push_back(std::move(impact));
                    }
                }
                const int damage = *result.hpDamage,acceptedHpLoss=std::min(target.hp,damage); target.hp = std::max(0, target.hp-damage);
                const auto &response = entity.response;
                target.lastImpact = monsterDeathImpulse(target.x-origin.x, target.y-origin.y, origin.dir, std::abs(command.speed),
                    damage, target.maxHp, response.push, response.lift);
                target.hitFlashUntil = now+80;
                if (!target.hp) world_.beginDeath(target);
                world_.requestHitStop(target, response.hitPause, response.source);
                if (command.followCaster) world_.requestHitStop(world_.player, response.hitPause, response.source);
                if (!target.dead && !response.noReaction) {
                    world_.applyResponse(target, response, origin.dir);
                    world_.applyMonsterHurtMotion(target,response);
                    world_.interruptStatusTarget(target);
                }
                world_.events.push_back({world_.tick, "hit", "female_gunner_source_entity", 0, target.id, damage});
                world_.publishMonsterHitFeedback(target,response,origin.dir,damage,false,&contact,result.critical);
                world_.publishMonsterAcceptedHit(std::move(accepted),acceptedHpLoss);
            }
        }
        } while(command.intervalMs>0 && entity.born+age>=entity.nextPulse && (!command.count||entity.pulse<command.count));
    }
    state_->entities.erase(std::remove_if(state_->entities.begin(), state_->entities.end(), [&](const State::Entity &entity) {
        if(now>=entity.expires||entity.owner!=world_.player.handle)for(auto &fx:world_.effects)if(fx.id==entity.effectId)fx.expires=std::min(fx.expires,now);
        return now >= entity.expires || entity.owner != world_.player.handle;
    }), state_->entities.end());
    if(!contactSpawns.empty()) {
        ExperimentalActorState actor;actor.x=world_.player.x;actor.y=world_.player.y;actor.z=world_.player.z;actor.direction=world_.player.dir;
        try {auto prepared=prepare(contactSpawns,actor,0);publish(std::move(prepared));}
        catch(const std::exception &error){state_->record({{"event","impact_entity_rejected"},{"message",error.what()},
            {"policy","bounded-impact-publication-after-accepted-contact-v1"}});}
    }
}
Json FemaleGunnerWorld::snapshot() const {
    Json entities = Json::array(), buffs = Json::array();
    for (const auto &entity : state_->entities) entities.push_back({{"command", commandReceipt(entity.command)},
        {"owner", entity.owner.json()}, {"attack_instance", entity.attackId}, {"pulse", entity.pulse},
        {"expires", entity.expires}, {"position", {entity.x, entity.y, entity.z}}, {"accepted_targets", entity.hit.size()},
        {"collision_animation",entity.command.animationSource?entity.command.animationSource->json():Json()},
        {"visual_animation",entity.visualAnimation?entity.visualAnimation->path:std::string()},
        {"visual_offset_xyz",{entity.visualOffsetX,entity.visualOffsetY,entity.visualOffsetZ}}});
    for (const auto &[key, buff] : state_->buffs) buffs.push_back({{"command", commandReceipt(buff.command)}, {"expires", buff.expires}});
    return {{"policy", policy}, {"classification", "inferred_beta"}, {"entities", entities}, {"buffs", buffs}, {"trace", state_->trace},
        {"source_work_cache",state_->sourceCache->snapshot()},
        {"g_group",{{"skill",state_->gSkill},{"expires",state_->gExpires}}},
        {"restore_policy", "cancel-transient-actions-input-and-effect-instances-v1"}};
}
Json World::femaleGunnerDiagnostics() const {
    return femaleGunnerWorld_ ? femaleGunnerWorld_->snapshot() : Json();
}
} // namespace dnf
