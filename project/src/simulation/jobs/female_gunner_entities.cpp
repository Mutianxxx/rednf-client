#include "dnf/female_gunner_entities.hpp"
#include "dnf/female_gunner_timing.hpp"
#include "dnf/effect_plan.hpp"
#include "dnf/experimental_character.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <filesystem>
#include <set>

namespace dnf {
namespace {
std::optional<double> operand(const FemaleGunnerSkillCommand &c,const std::string &text) {
    for(const auto &p:c.parameters)if(p.at("label").get<std::string>().find(text)!=std::string::npos)
        return p.at("value").get<double>();
    return {};
}
SourceRef reference(Pvf &p,const Json &row) {
    const auto out=makeSourceRef(p,row.at("member_path").get<std::string>());
    if(out.packageIdentity!=row.at("package_identity")||out.memberSha256!=row.at("member_sha256"))
        throw std::invalid_argument("Female Gunner object graph source changed");
    return out;
}
std::optional<SourceRef> binding(Pvf &p,const Json &object,const char *category,
    std::initializer_list<const char *> preferred) {
    const auto &rows=object.at(category);
    for(const auto name:preferred)for(const auto &row:rows)
        if(row.at("binding")==name)return reference(p,row.at("source"));
    return {};
}
std::optional<Json> objectAt(const FemaleGunnerSkillCommand &c,size_t index) {
    // Descriptor insertion order is recorded in evidence.objects; map order
    // in object_bindings is intentionally not treated as controller order.
    if(c.evidence.empty()||!c.rawTables.contains("object_bindings"))return {};
    for(const auto &ev:c.evidence)if(ev.contains("descriptor")) {
        const auto &objects=ev.at("descriptor").at("objects");
        if(index>=objects.size())return {};
        const auto member=objects[index].at("member_path");
        for(const auto &row:c.rawTables.at("object_bindings"))if(row.at("source").at("member_path")==member)return row;
    }
    return {};
}
Json explicitObject(Pvf &p,const FemaleGunnerSkillCommand &command,const std::string &stem) {
    const std::string path="passiveobject/character/gunner/"+stem+".obj";
    const auto source=p.script(path);Json row={{"source",makeSourceRef(p,path).json()},{"animations",Json::array()},{"attacks",Json::array()},{"particles",Json::array()}};
    for(const auto &f:source.fields){const auto tag=normalize(f.tag);const bool ani=tag=="[basic motion]"||tag=="[etc motion]"||tag.find(" motion]")!=std::string::npos;
        const bool atk=tag=="[attack info]"||tag=="[etc attack info]";
        if(!ani&&!atk)continue;
        for(size_t i=0;i<f.values.size();++i){const auto &v=f.values[i];if(!v.is_string()||v.get<std::string>().empty())continue;
            const auto member=normalize((std::filesystem::path(path).parent_path()/v.get<std::string>()).lexically_normal().generic_string());
            if(!p.has(member))throw std::runtime_error("Required female gunner explicit child missing: "+member);
            row[ani?"animations":"attacks"].push_back({{"binding",tag+"#"+std::to_string(i)},{"source",makeSourceRef(p,member).json()}});
        }
    }
    row["association"]={{"classification","inferred"},{"policy","inferred-1031-gunner-child-dispatch-v1"},
        {"parent_skill",command.skillSource.json()},{"basis","Explicit same-version OBJ child registration; native object creation call remains unverified"}};
    return row;
}
FemaleGunnerSkillCommand phase(Pvf &p,Assets &a,const FemaleGunnerSkillCommand &c,const Json &o,
    const std::string &role,std::initializer_list<const char *> ani,std::initializer_list<const char *> atk,bool damage) {
    auto out=c;out.effectRole=role;out.objectSource=reference(p,o.at("source"));
    out.animationSource=binding(p,o,"animations",ani);out.attackSource=damage?binding(p,o,"attacks",atk):std::nullopt;
    out.kind=damage?FemaleGunnerCommandKind::Strike:FemaleGunnerCommandKind::Stage;
    out.box.reset();out.count=1;out.intervalMs=0;out.speed=0;out.followCaster=false;out.offsetX=out.offsetY=out.offsetZ=0;
    if(!out.animationSource)throw std::invalid_argument("Required female Gunner phase has no authored animation: "+role+" "+out.objectSource->memberPath);
    const auto animation=a.animation(out.animationSource->memberPath);
    if(damage&&!out.attackSource)throw std::invalid_argument("Required female Gunner phase has no authored ATK: "+role+" "+out.objectSource->memberPath);
    out.rawTables["phase_role"]=role;
    out.evidence.push_back({{"policy","inferred-1031-gunner-object-phases-v2"},{"classification","inferred"},
        {"role",role},{"object",out.objectSource->json()},{"basis","Exact owning OBJ/MOB ordered animation and ATK slots; phase scheduling reconstructed"}});
    if(o.contains("association"))out.evidence.push_back(o.at("association"));
    out.lifetimeMs=std::max(1,animation->duration);return out;
}
std::optional<double> exactOperand(const FemaleGunnerSkillCommand &c,const std::string &label) {
    for(const auto &p:c.parameters)if(p.at("label")==label)return p.at("value").get<double>();return {};
}
int64_t milliseconds(const FemaleGunnerSkillCommand &c,const std::string &label,int64_t fallback) {
    const auto v=operand(c,label);if(!v)return fallback;
    if(!std::isfinite(*v)||*v<0||*v>2147483)throw std::runtime_error("Female gunner phase duration out of range");return int64_t(std::llround(*v*1000));
}
uint32_t sourceCount(const FemaleGunnerSkillCommand &c,const std::string &label,uint32_t fallback) {
    const auto v=operand(c,label);if(!v)return fallback;if(*v<1||*v>4096)throw std::runtime_error("Female gunner phase count out of range");return uint32_t(*v);
}
void coefficients(FemaleGunnerSkillCommand &c,const std::string &text,bool required=true) {
    Json selected=Json::array();std::string line;
    for(const auto &p:c.parameters){const auto label=p.at("label").get<std::string>();
        if(label.find(text)==std::string::npos||label.find("增加")!=std::string::npos||label.find("减少")!=std::string::npos)continue;
        if(!line.empty()&&line!=p.at("line"))continue;line=p.at("line");selected.push_back(p);}
    if(selected.empty()){if(required)throw std::runtime_error("Required female gunner phase coefficient missing: "+text+" skill "+std::to_string(c.key.skillId));return;}
    c.damage.percent=0;c.damage.independentPercent=0;c.damage.fixedDamage=0;c.damage.replacesAttackCoefficients=true;
    for(const auto &p:selected){const int selector=p.at("selector");if(selector==-2||selector==-4||selector==-5||selector==-6)c.damage.independentPercent+=p.at("raw_value").get<float>();
        else if(p.at("unit")=="percent")c.damage.percent+=p.at("value").get<float>();else c.damage.independentPercent+=p.at("raw_value").get<float>();}
    c.damage.sources.push_back({{"policy","inferred-source-phase-coefficients-v1"},{"classification","inferred"},{"phase",c.effectRole},{"source_operands",selected},
        {"basis","One matching current SKL display line; independent selector uses raw value, without double applying its display scale"}});
}
void radius(FemaleGunnerSkillCommand &c,double fallback,const std::string &label="") {
    double r=label.empty()?operand(c,"爆炸范围").value_or(operand(c,"命中范围").value_or(operand(c,"攻击范围").value_or(fallback))):operand(c,label).value_or(fallback);
    r=std::clamp(r,1.0,1200.0);c.box=Box{15,-int(std::ceil(r)),-30,0,int(std::ceil(2*r)),60,int(std::ceil(r))};
    c.evidence.push_back({{"policy","inferred-source-radius-contact-volume-v1"},{"radius_pixels",r},{"classification","inferred"},
        {"basis",label.empty()?"SKL radius when authored; otherwise centralized controller fallback":"SKL radius label: "+label}});
}
void ensureGeometry(FemaleGunnerSkillCommand &c,Assets &a) {
    if(!c.attackSource||c.box)return;
    if(c.animationSource)for(const auto &f:a.animation(c.animationSource->memberPath)->frames)for(const auto &b:f.boxes)if(b.type==15)return;
    // Several native projectile objects receive hit boxes from compiled code.
    // Keep this isolated inference explicit instead of using a waiting ANI.
    c.box=Box{15,-8,-12,0,32,24,64};
    c.evidence.push_back({{"policy","inferred-projectile-contact-volume-v1"},{"classification","inferred"},
        {"basis","Selected attacking OBJ has ATK but ANI has no type-15 boxes; native dynamic extent unavailable"},{"dimensions",{32,24,64}}});
}
void repeated(FemaleGunnerSkillCommand &c,int64_t life,int64_t interval,uint32_t count) {
    c.lifetimeMs=std::max<int64_t>(1,life);c.intervalMs=std::max<int64_t>(1,interval);c.count=std::max(uint32_t(1),count);
}
struct SourceImageAnchor { double x=0,y=0,width=0;Json evidence; };
SourceImageAnchor imageAnchor(Pvf &p,Assets &a,const std::string &path,bool rightmost) {
    const auto clip=a.animation(path);
    for(size_t index=0;index<clip->frames.size();++index) {
        const auto &frame=clip->frames[index];if(frame.image.empty())continue;
        const auto image=a.pixels(frame.image,frame.imageFrame);
        int left=image.width,right=-1,top=image.height,bottom=-1;
        for(int y=0;y<image.height;++y)for(int x=0;x<image.width;++x) {
            const auto at=(size_t(y)*image.width+x)*4;
            if(!image.rgba[at+3]||!(image.rgba[at]||image.rgba[at+1]||image.rgba[at+2]))continue;
            left=std::min(left,x);right=std::max(right,x);top=std::min(top,y);bottom=std::max(bottom,y);
        }
        if(right<left)continue;
        const auto pose=clip->samplePose(0,false,int(index));
        if(pose.scaleX!=1||pose.scaleY!=1||pose.rotationRadians!=0||pose.flip!=0)
            throw std::invalid_argument("Source muzzle inference cannot consume transformed weapon/image: "+path);
        double x=(left+right+1)*.5,y=(top+bottom+1)*.5;
        if(rightmost) {
            int low=image.height,high=-1;
            for(int yy=0;yy<image.height;++yy) {
                const auto at=(size_t(yy)*image.width+right)*4;
                if(image.rgba[at+3]&&(image.rgba[at]||image.rgba[at+1]||image.rgba[at+2])){low=std::min(low,yy);high=std::max(high,yy);}
            }
            x=right+.5;y=(low+high+1)*.5;
        }
        SourceImageAnchor out;out.x=frame.x+image.x+x;out.y=frame.y+image.y+y;out.width=right-left+1;
        out.evidence={{"animation",makeSourceRef(p,path).json()},{"frame",index},{"image",frame.image},
            {"image_frame",frame.imageFrame},{"ani_xy",{frame.x,frame.y}},{"img_crop",{image.x,image.y,image.width,image.height}},
            {"nonblack_alpha_bounds",{left,top,right+1,bottom+1}},{"selected_local_point",{out.x,out.y}},
            {"selection",rightmost?"rightmost nonblack nontransparent source column midpoint":"first visible source frame bounds midpoint"}};
        return out;
    }
    throw std::invalid_argument("Required current-PVF muzzle/image source has no visible pixels: "+path);
}
void muzzleAnchor(FemaleGunnerSkillCommand &c,Pvf &p,Assets &a,const std::string &weapon,
                  const std::string &ignition="") {
    const auto endpoint=imageAnchor(p,a,weapon,true);SourceImageAnchor flash;
    if(!ignition.empty())flash=imageAnchor(p,a,ignition,false);
    c.offsetX=endpoint.x-flash.x;c.offsetY=0;c.offsetZ=-endpoint.y+flash.y;
    c.evidence.push_back({{"policy","inferred-1031-source-weapon-muzzle-v1"},{"classification","inferred"},
        {"weapon_endpoint",endpoint.evidence},{"ignition_reference",ignition.empty()?Json():flash.evidence},
        {"offset_xyz",{c.offsetX,c.offsetY,c.offsetZ}},
        {"basis",ignition.empty()?"Flame ANI/boxes use a local muzzle origin; align it to the selected weapon source endpoint":
            "LaserFire first ignition is left of its beam origin; align that authored ignition midpoint with the selected weapon endpoint"},
        {"unverified_conditions","Compiled1031 spawn setter and exact barrel aperture remain unverified; initial source weapon pose is sampled once; no global character/effect Z compensation"}});
}
FemaleGunnerSkillCommand flameVisual(Pvf &p,Assets &a,const FemaleGunnerSkillCommand &command,const std::string &part) {
    const auto folder=normalize(std::filesystem::path(command.skillSource.memberPath).stem().string());
    const auto prefix="character/gunner/effect/animation/subweapon/"+folder+"/";
    auto visual=command;visual.kind=FemaleGunnerCommandKind::Stage;visual.effectRole="channel_visual_"+part;
    visual.objectSource.reset();visual.animationSource=makeSourceRef(p,prefix+"atfire_"+part+".ani");
    const auto animation=a.animation(visual.animationSource->memberPath);
    visual.attackSource.reset();visual.box.reset();visual.speed=visual.range=0;visual.count=1;visual.intervalMs=0;
    visual.followCaster=true;visual.lifetimeMs=animation->duration;visual.rawTables["body_motion_attack"]=false;
    visual.rawTables["channel_tail"]=(part=="end");
    muzzleAnchor(visual,p,a,prefix+"atfrontrapid2a.ani");
    visual.evidence.push_back({{"policy","inferred-1031-channel-flame-visual-phases-v1"},{"classification","inferred"},
        {"skill_source",command.skillSource.json()},{"animation_source",visual.animationSource->json()},
        {"basis","Selected current SKL stem has authored AT fire_start/loop/end clips; OBJ basic ANI is image-free collision geometry"},
        {"damage_policy","Visual-only; source OBJ/ATK remains the single damage consumer"},
        {"timing_policy","Authored start clip then loop during the source channel deadline; stop replaces pending clips with one source-duration end"},
        {"native_confirmed",false}});
    return visual;
}
std::vector<FemaleGunnerSkillCommand> heavyStageVisuals(Pvf &p,Assets &a,const FemaleGunnerSkillCommand &receipt) {
    if(!(receipt.key==SkillKey{5,71})||receipt.family!="charged_pull_projectile"||!receipt.motionSource||
       (!receipt.actionSequence&&!receipt.preflightOnly))
        throw std::invalid_argument("Heavy visual receipt requires an exact owned X1 source stage");
    const auto motion=makeSourceRef(p,receipt.motionSource->memberPath);
    if(motion.memberSha256!=receipt.motionSource->memberSha256||motion.packageIdentity!=receipt.motionSource->packageIdentity)
        throw std::invalid_argument("Heavy visual CHR source changed");
    const auto body=normalize(motion.memberPath);
    std::vector<std::string> clips;
    if(body=="character/gunner/atanimation/extruderready.ani")
        clips={"bodyready1","bodyready2","ballready1","ballready2","ballready3","ballready4","ballready5","glowready"};
    else if(body=="character/gunner/atanimation/extrudercharge.ani")
        clips={"bodycharge","glowcharge"};
    else if(body=="character/gunner/atanimation/extrudershoot.ani")
        clips={"bodyshoot1","bodyshoot2","glowshoot1","glowshoot2","glowshoot3","glowshoot4","glowshoot5","glowshoot6"};
    else throw std::invalid_argument("X1 visual receipt does not identify a supported current CHR stage");
    std::vector<FemaleGunnerSkillCommand> result;
    for(const auto &clip:clips) {
        const std::string path="character/gunner/effect/animation/extruder/"+clip+".ani";
        auto visual=receipt;visual.kind=FemaleGunnerCommandKind::Stage;visual.effectRole="x1_stage_visual_"+clip;
        visual.animationSource=makeSourceRef(p,path);visual.objectSource.reset();visual.attackSource.reset();visual.box.reset();
        visual.count=1;visual.intervalMs=0;visual.releaseDelayMs=0;visual.speed=visual.range=0;
        visual.offsetX=visual.offsetY=visual.offsetZ=0;visual.followCaster=true;
        const auto animation=a.animation(path);visual.lifetimeMs=animation->duration;
        visual.rawTables["body_motion_attack"]=false;
        visual.rawTables["action_bound_visual"]=true;
        visual.rawTables["stage_visual_parent_motion"]=motion.json();
        visual.rawTables["visual_source_loop"]=animation->globals.value("0",false);
        visual.rawTables["visual_layer"]=clip.rfind("body",0)==0?1:2;
        visual.evidence.push_back({{"policy","inferred-1031-x1-stage-appearance-v1"},{"classification","inferred"},
            {"native_confirmed",false},{"body_source",motion.json()},{"visual_source",visual.animationSource->json()},
            {"basis","Exact current female CHR ExtruderReady/Charge/Shoot stage selects matching source Extruder body/ball/glow role; compiled attachment call and relative order are unverified"},
            {"clock_policy","Independent immutable source ANI delays and loop; never borrow or rescale the body cursor"},
            {"lifecycle_policy","Only the exact live body-stage action owns these visuals; stage replacement, interruption, death and scene change retire them"},
            {"coordinate_policy","Source ANI XY and IMG crop are preserved at actor XYZ; no blanket Z adjustment"},
            {"damage_policy","Visual-only; source projectile and explosion remain the sole ATK consumers"}});
        result.push_back(std::move(visual));
    }
    return result;
}

}
std::optional<FemaleGunnerSkillCommand> femaleGunnerHeavyStageVisualReceipt(
    const FemaleGunnerSkillCommand &command,const SourceRef &motion,size_t stage) {
    if(!(command.key==SkillKey{5,71})||command.family!="charged_pull_projectile")return {};
    auto receipt=command;receipt.kind=FemaleGunnerCommandKind::Stage;receipt.effectRole="heavy_stage_visuals";
    receipt.motionSource=motion;receipt.stage=stage;receipt.animationSource.reset();receipt.attackSource.reset();
    receipt.objectSource.reset();receipt.box.reset();receipt.speed=receipt.range=0;receipt.count=1;receipt.intervalMs=0;
    receipt.releaseDelayMs=0;receipt.followCaster=true;return receipt;
}
int64_t femaleGunnerGTransformBaseDurationMs(const FemaleGunnerSkillCommand &c) {
    if(c.family!="g_transform"||c.key.skillId!=79)return 0;
    const auto seconds=exactOperand(c,"持续时间");
    if(!seconds||!std::isfinite(*seconds)||*seconds<=0||*seconds>2147483)
        throw std::invalid_argument("G1 requires its exact positive source duration");
    return int64_t(std::llround(*seconds*1000));
}
int64_t femaleGunnerGTransformExtensionMs(const FemaleGunnerSkillCommand &c) {
    if(c.family!="g_transform")return 0;
    const auto seconds=exactOperand(c,c.key.skillId==81?"改装时延迟持续时间":"改装时延长持续时间");
    if(!seconds||!std::isfinite(*seconds)||*seconds<0||*seconds>2147483)
        throw std::invalid_argument("G transformation requires its exact source extension");
    return int64_t(std::llround(*seconds*1000));
}
std::vector<FemaleGunnerSkillCommand> femaleGunnerFlameImpactCommands(Pvf &p,Assets &a,
    const FemaleGunnerSkillCommand &c,const std::vector<std::string> &targetCategories) {
    if(c.key.jobId!=5||c.key.skillId!=1||c.family!="enchanted_bullet")return {};
    bool special=false;
    for(const auto &category:targetCategories){const auto value=normalize(category);
        if(value=="plant"||value=="[plant]"||value=="insect"||value=="[insect]"||value=="fort"||value=="[fort]"||value=="building"||value=="[building]")special=true;}
    const auto object=explicitObject(p,c,"flamebulletfireexplosion");
    auto explosion=phase(p,a,c,object,"flame_ammo_explosion",{"[basic motion]#0"},{"[attack info]#0"},true);
    explosion.range=0;explosion.releaseDelayMs=0;
    coefficients(explosion,"附加魔法攻击力");
    if(special){auto bonus=explosion;coefficients(bonus,"植物");explosion.damage.percent+=bonus.damage.percent;
        explosion.damage.fixedDamage+=bonus.damage.fixedDamage;explosion.damage.independentPercent+=bonus.damage.independentPercent;
        explosion.damage.sources.push_back({{"policy","inferred-flame-category-addition-v1"},{"classification","inferred"},
            {"basis","Current source explanation increases attack for plant/insect/fort; add its separately authored category operand"},{"bonus",bonus.damage.snapshot()}});}
    const auto cap=sourceCount(c,"火焰爆炸的次数上限",0);
    if(!cap)throw std::invalid_argument("Flame ammo requires its source explosion count");
    const auto second=exactOperand(c,"第二次爆炸的攻击力比率");
    if(cap>1&&(!second||!std::isfinite(*second)||*second<0||*second>10000))
        throw std::invalid_argument("Flame ammo requires its source second-explosion ratio");
    std::vector<FemaleGunnerSkillCommand> out;
    for(uint32_t i=0;i<cap;++i){auto hit=explosion;hit.pulseId=i;hit.releaseDelayMs=int64_t(i)*explosion.lifetimeMs;
        if(i){hit.damage.percent*=float(*second/100);hit.damage.fixedDamage*=float(*second/100);hit.damage.independentPercent*=float(*second/100);}
        hit.rawTables["flame_impact"]={{"ordinal",i},{"explosion_limit",cap},{"special_category",special},{"target_categories",targetCategories},
            {"second_explosion_ratio_percent",second?Json(*second):Json()}};
        hit.evidence.push_back({{"policy","inferred-1031-flame-ammo-impact-v1"},{"classification","inferred"},
            {"basis","Source requires contact explosion, source limit, category coefficient and second-explosion ratio; later copies use that ratio and source ANI duration for scheduling"},
            {"native_unverified","Exact contact origin, inter-explosion timing and reinforced third-explosion scaling"}});
        ensureGeometry(hit,a);out.push_back(std::move(hit));}
    return out;
}
std::vector<FemaleGunnerSkillCommand> expandFemaleGunnerEntities(Pvf &p,Assets &a,const std::vector<FemaleGunnerSkillCommand> &input) {
    std::vector<FemaleGunnerSkillCommand> output;
    auto publish=[&](FemaleGunnerSkillCommand c){ensureGeometry(c,a);output.push_back(std::move(c));if(output.size()>512)throw std::length_error("Female Gunner phase budget exceeded before publication");};
    auto projectiles=[&](FemaleGunnerSkillCommand c,int64_t life,int64_t gap,uint32_t count){
        if(count>512)throw std::length_error("Female gunner projectile count exceeds phase transaction capacity");
        for(uint32_t i=0;i<count;++i){auto bullet=c;bullet.count=1;bullet.intervalMs=0;bullet.followCaster=false;
            bullet.releaseDelayMs+=int64_t(i)*std::max<int64_t>(1,gap);bullet.lifetimeMs=std::max<int64_t>(1,life);
            bullet.rawTables["emission_ordinal"]=i;bullet.rawTables["emission_count"]=count;publish(std::move(bullet));}
    };
    for(const auto &sourceCommand:input) {
        auto command=sourceCommand;
        if(command.effectRole=="heavy_stage_visuals") {
            for(auto &visual:heavyStageVisuals(p,a,command))publish(std::move(visual));
            continue;
        }
        if(command.preflightOnly&&command.key==SkillKey{5,71}&&command.family=="charged_pull_projectile") {
            CharacterCatalog catalog(p);const auto chr=catalog.at(5);
            for(size_t index=0;index<3;++index) {
                const auto body=makeSourceRef(p,chr.motion("[etc motion]",37+index));
                auto receipt=femaleGunnerHeavyStageVisualReceipt(command,body,index);
                for(auto &visual:heavyStageVisuals(p,a,*receipt))publish(std::move(visual));
            }
        }
        if(command.family=="g_transform") {
            const auto base=femaleGunnerGTransformBaseDurationMs(command),extension=femaleGunnerGTransformExtensionMs(command);
            command.rawTables["g_transform_member_duration_ms"]=base;
            command.rawTables["g_transform_extension_ms"]=extension;
            if(!command.rawTables.value("g_transform_lifetime_resolved",false)&&base>0)command.lifetimeMs=base;
        }
        const auto root=objectAt(command,0),child=objectAt(command,1);const auto &f=command.family;
        if(command.kind==FemaleGunnerCommandKind::Buff||command.kind==FemaleGunnerCommandKind::Clear){
            publish(command);
            if(command.kind==FemaleGunnerCommandKind::Clear&&command.effectRole=="stop_channel"&&f=="channel_flame") {
                auto end=flameVisual(p,a,command,"end");end.releaseDelayMs=0;publish(std::move(end));
            }
            continue;
        }
        // Adapter body stages may inherit the transformed skill's descriptor.
        // Their body/CHR attacks are consumed there, not re-expanded as the
        // descriptor's passive-object projectile when no effect ANI is set.
        if(command.kind==FemaleGunnerCommandKind::Stage&&!command.animationSource){publish(command);continue;}
        if(!root) {
            auto c=command;
            if(f=="radial_multishot") {
                CharacterCatalog catalog(p);const auto chr=catalog.at(5);auto motion=chr.motion("[etc motion]",15);auto attack=chr.attackInfo("[etc attack info]",9);
                c.animationSource=makeSourceRef(p,motion);c.attackSource=makeSourceRef(p,attack);c.kind=FemaleGunnerCommandKind::Strike;c.effectRole="radial_shot";
                c.rawTables["body_motion_attack"]=true;
                // Older callers can still provide an evaluated SKL command
                // without its runtime receipt. Resolve it through the same
                // source controller contract; never invent80ms or use bleed
                // duration as a shooting deadline.
                if(!c.rawTables.contains("controller_timing")) {
                    FemaleGunnerStage bodyStage;bodyStage.motionSlot=15;bodyStage.holdForCommandLifetime=true;
                    applyFemaleGunnerStageTiming(c,buildFemaleGunnerStageTiming(c,bodyStage,*a.animation(motion)));
                }
                if(c.count<1||c.count>512||c.intervalMs<1||c.lifetimeMs!=int64_t(c.count)*c.intervalMs)
                    throw std::invalid_argument("RandomShoot entity lacks its resolved source pulse timeline");
                radius(c,180);c.evidence.push_back({{"classification","inferred"},{"policy","inferred-chr-radial-pulses-v1"},{"basis","Exact CHR etc motion15/ATK9 with SKL count; radial reconstructed volume, player body stage remains independently animated"}});
                publish(c);
                // This short authored muzzle ANI is not a20-frame body layer.
                // It has its own source timeline. Its connection to each SKL
                // shot pulse is an explicit controller inference, not a fake
                // CHR/ALS/preload reference or an extra damaging attack.
                const auto muzzlePath="character/gunner/effect/animation/shooteffect/at"+
                    normalize(std::filesystem::path(c.skillSource.memberPath).stem().string())+"fire.ani";
                const auto muzzleSource=makeSourceRef(p,muzzlePath);
                const auto muzzleAnimation=a.animation(muzzlePath);
                if(muzzleAnimation->frames.empty()||muzzleAnimation->duration<=0)
                    throw std::invalid_argument("RandomShoot source pulse visual has no positive source timeline");
                for(uint32_t pulse=0;pulse<c.count;++pulse) {
                    auto visual=c;visual.kind=FemaleGunnerCommandKind::Stage;visual.effectRole="radial_muzzle";
                    visual.animationSource=muzzleSource;visual.attackSource.reset();visual.box.reset();
                    visual.count=1;visual.intervalMs=0;visual.followCaster=true;visual.speed=visual.range=0;
                    visual.offsetX=visual.offsetY=visual.offsetZ=0;
                    visual.pulseId=pulse;visual.releaseDelayMs+=int64_t(pulse)*c.intervalMs;
                    visual.lifetimeMs=muzzleAnimation->duration;visual.rawTables["body_motion_attack"]=false;
                    visual.rawTables["radial_visual_pulse"]={{"ordinal",pulse},{"count",c.count},{"interval_ms",c.intervalMs}};
                    visual.evidence.push_back({{"policy","inferred-1031-randomshoot-pulse-visual-v1"},{"classification","inferred"},
                        {"skill_source",c.skillSource.json()},{"animation_source",muzzleSource.json()},
                        {"basis","Current same-stem AT RandomShoot fire ANI; independent source timeline attached to the evaluated SKL shot pulses"},
                        {"timing","One source-duration visual per command pulse at ordinal times source interval; body controller delays are not copied"},
                        {"unverified_conditions","Compiled1031 fire attachment/initial phase/facing changes and overlapping muzzle lifetimes require original dynamic comparison"}});
                    publish(std::move(visual));
                }
                continue;
            }else if(c.kind==FemaleGunnerCommandKind::Launch&&(!c.animationSource||!c.attackSource))c.kind=FemaleGunnerCommandKind::Stage;
            publish(std::move(c));continue;
        }
        if(f=="robot_summon") {
            auto body=phase(p,a,command,*root,"robot_body",{"[waiting motion]#0"},{},false);body.lifetimeMs=std::max<int64_t>(1,command.lifetimeMs);
            const bool chase=command.key.skillId==27, timer=command.key.skillId==28||command.key.skillId==105;
            body.rawTables["behavior"]=chase?"seek_explode":timer?"timer_explode":"turret";
            body.pulseId=0;
            if(!child)throw std::runtime_error("Robot source child missing");
            auto attack=phase(p,a,command,*child,"robot_attack",{"[basic motion]#0","[etc motion]#0"},{"[attack info]#0"},true);
            attack.rawTables["behavior"]=body.rawTables["behavior"];attack.pulseId=body.pulseId;
            if(chase||timer){attack.releaseDelayMs+=body.lifetimeMs;radius(attack,100);coefficients(attack,"魔法攻击力");}
            else {
                const auto rate=operand(command,"每秒发射子弹数");const auto gap=rate&&*rate>0?std::max<int64_t>(1,int64_t(1000/ *rate)):500;
                body.intervalMs=gap;attack.speed=1200;attack.range=900;repeated(attack,body.lifetimeMs,gap,uint32_t(std::max<int64_t>(1,body.lifetimeMs/gap)));
                coefficients(attack,command.key.skillId==63?"机枪魔法攻击力":command.key.skillId==106?"激光魔法攻击力":"子弹魔法攻击力");
            }
            publish(body);
            if(!chase&&!timer)projectiles(attack,750,attack.intervalMs,attack.count);else publish(attack);
            if(command.key.skillId==63) {
                auto missileObject=explicitObject(p,command,"tempestermissile");auto missile=phase(p,a,command,missileObject,"robot_attack",{"[etc motion]#4","[basic motion]#0"},{"[attack info]#0"},true);
                missile.pulseId=1;missile.speed=650;missile.range=900;coefficients(missile,"导弹魔法攻击力");projectiles(missile,1300,1500,uint32_t(std::max<int64_t>(1,body.lifetimeMs/1500)));
                auto expObject=explicitObject(p,command,"tempesterexplosion");auto exp=phase(p,a,command,expObject,"robot_attack",{"[basic motion]#0"},{"[attack info]#0"},true);exp.releaseDelayMs+=body.lifetimeMs;exp.pulseId=2;radius(exp,100);coefficients(exp,"自爆魔法攻击力");publish(exp);
            }
            if(command.key.skillId==105) {
                auto rx=explicitObject(p,command,"rx78explosion");const auto n=sourceCount(command,"生成追击者数量",3);
                for(uint32_t i=0;i<n;++i){auto spawnedBody=phase(p,a,command,*root,"robot_body",{"[etc motion]#0","[waiting motion]#0"},{},false);spawnedBody.objectSource=makeSourceRef(p,"monster/gunner/robot/rx78.mob");
                    const auto mob=p.script(spawnedBody.objectSource->memberPath);auto wait=mob.values("[waiting motion]");spawnedBody.animationSource=makeSourceRef(p,normalize((std::filesystem::path(spawnedBody.objectSource->memberPath).parent_path()/wait[0].get<std::string>()).lexically_normal().generic_string()));
                    spawnedBody.releaseDelayMs+=body.lifetimeMs;spawnedBody.lifetimeMs=3000;spawnedBody.offsetY=(double(i)-double(n-1)/2)*25;spawnedBody.pulseId=i+1;spawnedBody.rawTables["behavior"]="seek_explode";
                    auto exp=phase(p,a,command,rx,"robot_attack",{"[basic motion]#0"},{"[attack info]#0"},true);exp.pulseId=i+1;exp.offsetY=spawnedBody.offsetY;exp.releaseDelayMs=spawnedBody.releaseDelayMs+spawnedBody.lifetimeMs;radius(exp,100);publish(spawnedBody);publish(exp);}
            }
            continue;
        }
        if(f=="robot_airdrop") {
            auto carrier=phase(p,a,command,*root,"airdrop_carrier",{"[basic motion]#0"},{},false);carrier.lifetimeMs=std::max<int64_t>(1000,command.lifetimeMs);publish(carrier);
            if(!child)throw std::runtime_error("Airdrop robot body missing");auto expObject=explicitObject(p,command,"rx78explosion");const auto n=command.count;
            for(uint32_t i=0;i<n;++i){auto body=phase(p,a,command,*child,"robot_body",{"[etc motion]#1","[waiting motion]#0"},{},false);body.releaseDelayMs+=int64_t(i)*100;body.lifetimeMs=3000;
                body.pulseId=i;body.rawTables["behavior"]="seek_explode";body.offsetX=100+(i%6)*40;body.offsetY=(int(i%5)-2)*25;
                auto explosion=phase(p,a,command,expObject,"robot_attack",{"[basic motion]#0"},{"[attack info]#0"},true);explosion.pulseId=i;explosion.offsetX=body.offsetX;explosion.offsetY=body.offsetY;
                explosion.releaseDelayMs=body.releaseDelayMs+body.lifetimeMs;radius(explosion,100);coefficients(explosion,"追击者魔法攻击力");publish(body);publish(explosion);}
            continue;
        }
        if(f=="factory_summon") {
            auto factory=phase(p,a,command,*root,"factory_body",{"[etc motion]#0"},{},false);factory.lifetimeMs=std::max<int64_t>(1,command.lifetimeMs);publish(factory);
            const auto n=sourceCount(command,"拦截机生产数量上限",6);const auto gap=milliseconds(command,"攻击时间间隔",750);auto bulletObject=explicitObject(p,command,"sparrowbullet");
            if(!child)throw std::runtime_error("Factory interceptor source missing");
            for(uint32_t i=0;i<n;++i){auto body=phase(p,a,command,*child,"robot_body",{"[etc motion]#1"},{},false);body.lifetimeMs=factory.lifetimeMs;body.pulseId=i+1;body.offsetX=80+(i%3)*35;body.offsetY=(int(i%3)-1)*28;body.rawTables["behavior"]="turret";publish(body);
                auto attack=phase(p,a,command,bulletObject,"robot_attack",{"[etc motion]#0"},{"[attack info]#0"},true);attack.pulseId=i+1;attack.offsetX=body.offsetX;attack.offsetY=body.offsetY;attack.speed=1000;attack.range=operand(command,"攻击范围").value_or(800);
                coefficients(attack,"枪弹魔法攻击力");projectiles(attack,800,gap,uint32_t(std::max<int64_t>(1,factory.lifetimeMs/gap)));}
            auto explosion=phase(p,a,command,*root,"factory_explosion",{"[etc motion]#6"},{"[attack info]#0"},true);explosion.releaseDelayMs+=factory.lifetimeMs;coefficients(explosion,"工厂爆炸魔法攻击力");radius(explosion,140);publish(explosion);continue;
        }
        if(f=="g_transform") {
            const auto life=command.lifetimeMs>0?command.lifetimeMs:10000;
            const uint32_t members=command.key.skillId==80?3:command.key.skillId==81?6:1;
            for(uint32_t i=0;i<members;++i){auto body=phase(p,a,command,*root,"robot_body",{"[etc motion]#0"},{},false);
                body.followCaster=command.key.skillId!=81;body.lifetimeMs=life;body.pulseId=command.key.skillId==81?i+1:0;
                body.rawTables["behavior"]=command.key.skillId==81?"attach_target":"turret";
                body.rawTables["ordinal"]=i;body.rawTables["member_count"]=members;
                body.rawTables["target_range"]=operand(command,"捕食者攻击范围").value_or(1000);
                if(members>1){body.offsetX=(i%2?1:-1)*(35+15*(i/2));body.offsetY=(double(i)-double(members-1)/2)*18;body.offsetZ=30;}
                publish(body);}
            if(command.key.skillId==79){if(!child)throw std::runtime_error("G1 bullet child missing");auto bullet=phase(p,a,command,*child,"robot_attack",{"[basic motion]#0"},{"[attack info]#0"},true);bullet.offsetX=50;bullet.speed=900;bullet.range=800;
                const auto gap=std::max<int64_t>(1,command.intervalMs);projectiles(bullet,850,gap,uint32_t(std::max<int64_t>(1,life/gap)));
            }else if(command.key.skillId==80){auto spark=phase(p,a,command,*root,"robot_attack",{"[etc motion]#8"},{"[etc attack info]#0"},true);spark.followCaster=true;coefficients(spark,"静电魔法攻击力");radius(spark,120);
                const auto gap=milliseconds(command,"静电多段攻击间隔",1000);repeated(spark,life,gap,uint32_t(std::max<int64_t>(1,life/gap)));publish(spark);
                auto wave=phase(p,a,command,*root,"robot_attack",{"[etc motion]#4"},{"[attack info]#0"},true);wave.followCaster=true;wave.pulseId=1;coefficients(wave,"电波魔法攻击力");radius(wave,180);const auto recharge=milliseconds(command,"充电冷却时间",1500);repeated(wave,life,recharge,uint32_t(std::max<int64_t>(1,life/recharge)));publish(wave);
            }else {for(uint32_t i=0;i<6;++i){auto beam=phase(p,a,command,*root,"robot_attack",{"[etc motion]#3"},{"[attack info]#0"},true);
                beam.pulseId=i+1;beam.followCaster=false;beam.rawTables["behavior"]="attach_target";beam.rawTables["ordinal"]=i;beam.rawTables["member_count"]=6;
                beam.rawTables["target_range"]=operand(command,"捕食者攻击范围").value_or(1000);
                beam.box=Box{15,-20,-12,0,40,24,100};beam.evidence.push_back({{"policy","inferred-g3-attached-contact-volume-v1"},{"classification","inferred"},
                    {"basis","Source acquisition range selects targets, not a damage radius; six source-described members use local target-bound reconstructed contact volume"},{"dimensions",{40,24,100}}});
                const auto gap=std::max<int64_t>(1,command.intervalMs);repeated(beam,life,gap,uint32_t(std::max<int64_t>(1,life/gap)));publish(beam);}}
            continue;
        }
        if(f=="grenade"||f=="cluster_bomb"||f=="targeted_bomb"||f=="projectile_field"||f=="proximity_mine"||f=="remote_bomb") {
            const bool mine=f=="proximity_mine"||f=="remote_bomb";const auto n=f=="cluster_bomb"?std::max<uint32_t>(1,command.count):uint32_t(1);
            for(uint32_t i=0;i<n;++i) {
                auto flight=phase(p,a,command,*root,mine?"mine_body":"thrown_body",{"[basic motion]#0"},{},false);
                flight.pulseId=i;flight.speed=mine?0:450;flight.lifetimeMs=mine?std::max<int64_t>(1000,command.lifetimeMs):milliseconds(command,"最短飞行时间",600);
                flight.rawTables["behavior"]=mine?"proximity":"arc";flight.offsetY=(double(i)-double(n-1)/2)*22;
                FemaleGunnerSkillCommand explosion;
                if(f=="grenade")explosion=phase(p,a,command,*root,"explosion",{"[etc motion]#3"},{"[etc attack info]#0"},true);
                else if(f=="proximity_mine")explosion=phase(p,a,command,*root,"explosion",{"[etc motion]#4"},{"[etc attack info]#0"},true);
                else if(f=="remote_bomb"&&command.key.skillId==77)explosion=phase(p,a,command,*root,"explosion",{"[etc motion]#6"},{"[attack info]#0"},true);
                else if(f=="remote_bomb")explosion=phase(p,a,command,*root,"explosion",{"[basic motion]#0"},{"[attack info]#0"},true);
                else if(f=="targeted_bomb")explosion=phase(p,a,command,*root,"explosion",{"[etc motion]#0"},{"[etc attack info]#0"},true);
                else if(f=="cluster_bomb"){if(!child)throw std::runtime_error("Cluster bomb subobject missing");explosion=phase(p,a,command,*child,"explosion",{"[etc motion]#1"},{"[attack info]#0"},true);}
                else {if(!child)throw std::runtime_error("Field explosion object missing");explosion=phase(p,a,command,*child,"explosion",{"[basic motion]#0"},{"[attack info]#0"},true);}
                explosion.pulseId=i;explosion.releaseDelayMs+=flight.lifetimeMs;explosion.offsetX=mine?0:flight.speed*flight.lifetimeMs/1000.0;explosion.offsetY=flight.offsetY;
                explosion.rawTables["behavior"]=flight.rawTables["behavior"];radius(explosion,100);coefficients(explosion,f=="targeted_bomb"?"爆炸物理攻击力":f=="projectile_field"?"魔法攻击力":"攻击力");
                publish(flight);publish(explosion);
                if(f=="projectile_field"){auto field=phase(p,a,command,*root,"field",{"[etc motion]#0"},{"[attack info]#0"},true);field.offsetX=explosion.offsetX;field.releaseDelayMs=explosion.releaseDelayMs+explosion.lifetimeMs;
                    const auto gap=std::max<int64_t>(100,command.intervalMs);repeated(field,std::max<int64_t>(1,command.lifetimeMs),gap,uint32_t(std::max<int64_t>(1,command.lifetimeMs/gap)));coefficients(field,"电磁地带魔法攻击力");radius(field,120,"电磁地带范围");publish(field);}
                if(f=="cluster_bomb"&&command.key.skillId==108){auto magma=phase(p,a,command,*child,"magma_field",{"[etc motion]#7"},{"[etc attack info]#0"},true);magma.pulseId=i;magma.offsetX=explosion.offsetX;magma.offsetY=flight.offsetY;magma.releaseDelayMs=explosion.releaseDelayMs;
                    repeated(magma,3000,500,6);radius(magma,90);publish(magma);}
            }
            continue;
        }
        if(f=="awakening_g0") {
            const auto gatlingCount=sourceCount(command,"格林机枪发射数",30),lockCount=sourceCount(command,"锁定限制次数",5);const auto lockLife=milliseconds(command,"锁定限制时间",7000);
            auto appear=phase(p,a,command,*root,"awakening_appear",{"[etc motion]#5"},{},false);publish(appear);
            for(const char *slot:{"[etc motion]#6","[etc motion]#7","[etc motion]#8","[etc motion]#9"}){auto layer=phase(p,a,command,*root,"awakening_appear_layer",{slot},{},false);layer.lifetimeMs=appear.lifetimeMs;publish(layer);}
            auto body=phase(p,a,command,*root,"awakening_body",{"[etc motion]#1"},{},false);body.releaseDelayMs+=appear.lifetimeMs;body.lifetimeMs=lockLife;publish(body);
            for(const char *slot:{"[etc motion]#2","[etc motion]#3","[etc motion]#4"}){auto layer=phase(p,a,command,*root,"awakening_body_layer",{slot},{},false);layer.releaseDelayMs=body.releaseDelayMs;layer.lifetimeMs=body.lifetimeMs;publish(layer);}
            auto gatling=phase(p,a,command,*root,"awakening_gatling",{"[etc motion]#29"},{"[attack info]#0"},true);gatling.releaseDelayMs=body.releaseDelayMs;gatling.offsetX=200;coefficients(gatling,"格林机枪魔法攻击力");radius(gatling,60);
            repeated(gatling,lockLife,std::max<int64_t>(1,lockLife/gatlingCount),gatlingCount);publish(gatling);
            auto missileObject=explicitObject(p,command,"g0missile"),laserObject=explicitObject(p,command,"g0laser");
            for(uint32_t i=0;i<lockCount;++i){auto missile=phase(p,a,command,missileObject,"awakening_missile",{"[etc motion]#3"},{"[attack info]#0"},true);missile.pulseId=i;missile.releaseDelayMs=body.releaseDelayMs+int64_t(i)*lockLife/lockCount;missile.offsetX=220;coefficients(missile,"导弹锁定攻击时魔法攻击力");radius(missile,100);publish(missile);
                auto laser=phase(p,a,command,laserObject,"awakening_laser",{"[etc motion]#0"},{"[attack info]#0"},true);laser.pulseId=i;laser.releaseDelayMs=body.releaseDelayMs+lockLife+int64_t(i)*200;laser.offsetX=220;coefficients(laser,"激光锁定攻击时魔法攻击力");radius(laser,140);publish(laser);}
            auto disappear=phase(p,a,command,*root,"awakening_disappear",{"[etc motion]#68"},{},false);disappear.releaseDelayMs=body.releaseDelayMs+lockLife+int64_t(lockCount)*200;publish(disappear);continue;
        }
        if(f=="awakening_particle_cannon") {
            const bool fullCharge=command.rawTables.value("particle_full_charge",false);
            auto appear=phase(p,a,command,*root,"cannon_appear",{"[etc motion]#3"},{},false);
            const auto visual=[&](const char *slot,const char *role,int64_t delay,std::optional<int64_t> life={}) {
                auto layer=phase(p,a,command,*root,role,{slot},{},false);layer.releaseDelayMs=delay;
                if(life)layer.lifetimeMs=*life;
                layer.rawTables["visual_source_loop"]=a.animation(layer.animationSource->memberPath)->globals.value("0",false);
                layer.rawTables["particle_visual_branch"]=fullCharge?"full_candidate":"normal";
                layer.evidence.push_back({{"policy","inferred-1031-particle-cannon-visual-phases-v1"},{"classification","inferred"},
                    {"native_confirmed",false},{"owning_obj",root->at("source")},{"ordered_slot",slot},
                    {"basis","Current owning OBJ slot selects source SubBody/Gauge/fire/full layer; native stage placement and attachment order remain unverified"},
                    {"clock_policy","Independent source ANI delays and authored loop; source XY/crop preserved without shared body cursor"},
                    {"input_capability","Normal input currently selects the normal branch. Full source visuals are explicit candidate commands; native rapid ATTACK charge threshold is unimplemented"},
                    {"damage_policy","Visual-only, with no additional ATK or contact instance"}});
                publish(std::move(layer));
            };
            auto sub=phase(p,a,command,*root,"cannon_sublaser",{"[etc motion]#43"},{"[etc attack info]#0"},true);sub.releaseDelayMs+=appear.lifetimeMs;coefficients(sub,"小束激光物理攻击力");sub.box=Box{15,0,-25,0,640,50,120};
            sub.rawTables["visual_source_loop"]=a.animation(sub.animationSource->memberPath)->globals.value("0",false);
            auto main=fullCharge?phase(p,a,command,*root,"cannon_main",{"[etc motion]#70"},{"[etc attack info]#2"},true):
                phase(p,a,command,*root,"cannon_main",{"[etc motion]#58"},{"[etc attack info]#1"},true);
            main.releaseDelayMs=sub.releaseDelayMs+sub.lifetimeMs;coefficients(main,fullCharge?"主炮最大蓄电时物理攻击力":"主炮基本物理攻击力");main.box=Box{15,0,-35,0,800,70,160};repeated(main,command.lifetimeMs,std::max<int64_t>(1,command.intervalMs),command.count);
            main.rawTables["visual_source_loop"]=a.animation(main.animationSource->memberPath)->globals.value("0",false);
            main.evidence.push_back({{"policy","inferred-source-cannon-beam-volume-v1"},{"classification","inferred"},{"basis","Selected attack-bearing laser tile and native dynamic beam extents unavailable; reconstructed horizontal contact volume"},{"dimensions",{800,70,160}}});
            const auto mainEnd=main.releaseDelayMs+main.lifetimeMs;
            appear.lifetimeMs=mainEnd-command.releaseDelayMs;
            appear.rawTables["visual_source_loop"]=a.animation(appear.animationSource->memberPath)->globals.value("0",false);
            appear.evidence.push_back({{"policy","inferred-particle-body-final-pose-until-main-exit-v1"},{"classification","inferred"},
                {"basis","Source Body1 contains the normal machine image; preserve its independent non-loop rise and final pose throughout the owning cannon main phase"}});
            publish(appear);publish(sub);publish(main);
            for(const char *slot:{"[etc motion]#4","[etc motion]#5","[etc motion]#6","[etc motion]#7"})
                visual(slot,"cannon_body_layer",command.releaseDelayMs,mainEnd-command.releaseDelayMs);
            // Repeated SubBody registrations carry no recovered distinct
            // native placement. Publish one exact source track, retaining the
            // eight ordered registrations in raw OBJ evidence instead of
            // inventing eight coincident guns.
            visual("[etc motion]#30","cannon_sub_body",command.releaseDelayMs);
            visual("[etc motion]#40","cannon_sub_roll",sub.releaseDelayMs,sub.lifetimeMs);
            visual("[etc motion]#41","cannon_sub_fire",sub.releaseDelayMs);
            visual("[etc motion]#42","cannon_sub_electric",sub.releaseDelayMs,sub.lifetimeMs);
            visual("[etc motion]#46","cannon_gauge_ready",command.releaseDelayMs,main.releaseDelayMs-command.releaseDelayMs);
            visual(fullCharge?"[etc motion]#52":"[etc motion]#49","cannon_gauge_shot",main.releaseDelayMs,main.lifetimeMs);
            visual("[etc motion]#53","cannon_main_fire",main.releaseDelayMs);
            visual("[etc motion]#54","cannon_main_fire_glow",main.releaseDelayMs);
            if(fullCharge) {
                visual("[etc motion]#50","cannon_gauge_full",main.releaseDelayMs);
                visual("[etc motion]#51","cannon_gauge_full_glow",main.releaseDelayMs);
                for(const char *slot:{"[etc motion]#71","[etc motion]#78","[etc motion]#79","[etc motion]#80","[etc motion]#81",
                    "[etc motion]#82","[etc motion]#87","[etc motion]#88","[etc motion]#89","[etc motion]#90",
                    "[etc motion]#91","[etc motion]#92","[etc motion]#93","[etc motion]#94","[etc motion]#95"})
                    visual(slot,"cannon_full_visual",main.releaseDelayMs,main.lifetimeMs);
                visual("[etc motion]#74","cannon_full_disappear",mainEnd);
                visual("[etc motion]#75","cannon_full_glow_disappear",mainEnd);
            } else {
                visual("[etc motion]#59","cannon_main_glow",main.releaseDelayMs,main.lifetimeMs);
                visual("[etc motion]#66","cannon_main_electric",main.releaseDelayMs,main.lifetimeMs);
                visual("[etc motion]#62","cannon_main_disappear",mainEnd);
                visual("[etc motion]#63","cannon_main_glow_disappear",mainEnd);
            }
            auto muzzle=phase(p,a,command,*root,"cannon_main_muzzle",{"[etc motion]#55"},{},false);muzzle.releaseDelayMs=main.releaseDelayMs;muzzle.lifetimeMs=main.lifetimeMs;
            muzzle.rawTables["visual_source_loop"]=a.animation(muzzle.animationSource->memberPath)->globals.value("0",false);publish(muzzle);
            visual("[etc motion]#56","cannon_muzzle_disappear",mainEnd);
            auto last=phase(p,a,command,*root,"cannon_last",{"[etc motion]#99"},{"[etc attack info]#5"},true);last.releaseDelayMs=main.releaseDelayMs+main.lifetimeMs;last.damage=main.damage;last.box=main.box;publish(last);continue;
        }
        if(f=="awakening_emp") {
            auto impact=phase(p,a,command,*root,"emp_impact",{"[basic motion]#0"},{"[attack info]#0"},true);impact.offsetX=200;coefficients(impact,"机动装置落下物理攻击力");radius(impact,180);publish(impact);
            auto field=phase(p,a,command,*root,"emp_field",{"[etc motion]#26"},{"[attack info]#0"},true);field.offsetX=impact.offsetX;field.releaseDelayMs=impact.lifetimeMs;coefficients(field,"电磁场魔法攻击力");radius(field,240);repeated(field,5000,500,10);publish(field);
            if(!child)throw std::runtime_error("EMP explosion object missing");auto explosion=phase(p,a,command,*child,"emp_explosion",{"[basic motion]#0"},{"[attack info]#0"},true);explosion.offsetX=impact.offsetX;explosion.releaseDelayMs=field.releaseDelayMs+field.lifetimeMs;coefficients(explosion,"机动装置爆炸物理攻击力");radius(explosion,240);publish(explosion);continue;
        }
        if(f=="targeted_sniping") {
            auto scope=phase(p,a,command,*root,"scope",{"[basic motion]#0"},{},false);scope.lifetimeMs=std::max<int64_t>(1,command.lifetimeMs);publish(scope);
            if(!child)throw std::runtime_error("Sniping hit object missing");auto attack=phase(p,a,command,*child,"snipe",{"[basic motion]#0"},{"[attack info]#0"},true);attack.offsetX=200;radius(attack,40);
            repeated(attack,command.lifetimeMs,std::max<int64_t>(1,command.intervalMs),command.count);publish(attack);continue;
        }
        if(f=="charged_pull_projectile") {
            auto projectile=phase(p,a,command,*root,"charged_pull_ball",{"[etc motion]#0"},{"[attack info]#0"},true);projectile.speed=450;projectile.range=600;projectile.lifetimeMs=1200;publish(projectile);
            auto explosion=phase(p,a,command,*root,"explosion",{"[etc motion]#14"},{"[etc attack info]#0"},true);explosion.releaseDelayMs=projectile.lifetimeMs;explosion.offsetX=540;radius(explosion,160);publish(explosion);continue;
        }
        if(f=="returning_gunhawk") {
            for(int i=0;i<3;++i){auto attack=phase(p,a,command,*root,"returning_gunhawk",{"[etc motion]#0"},{"[attack info]#0"},true);coefficients(attack,"第"+std::to_string(i+1)+"次物理攻击力");attack.speed=i%2?-450:450;attack.offsetX=i%2?450:0;attack.pulseId=uint32_t(i);attack.releaseDelayMs+=i*1000;attack.range=600;repeated(attack,1000,100,10);publish(attack);}continue;
        }
        if(f=="heavy_projectile"&&command.key.skillId==39) {
            auto beam=phase(p,a,command,*root,"laser_beam",{"[etc motion]#0"},{"[attack info]#0"},true);
            muzzleAnchor(beam,p,a,"character/gunner/effect/animation/subweapon/laserrifleeffect/atfrontonce2b.ani",
                beam.animationSource->memberPath);
            double extent=0;
            for(const auto &frame:a.animation(beam.animationSource->memberPath)->frames)
                for(const auto &box:frame.boxes)if(box.type==15)extent=std::max(extent,double(box.x)+box.w);
            if(extent<=0)throw std::invalid_argument("LaserFire source lacks forward attack extent");
            beam.evidence.push_back({{"policy","inferred-1031-source-laser-composition-v1"},{"classification","inferred"},
                {"basis","Owning OBJ etc motion0 LaserFire contains the attack frames; etc motion1 LaserTile is visual-only"},
                {"source_forward_extent",extent},{"damage_policy","Use original frame-specific LaserFire type15 boxes; no invented beam box"}});
            publish(beam);
            auto tile=phase(p,a,command,*root,"laser_tile",{"[etc motion]#1"},{},false);
            tile.offsetX=beam.offsetX;tile.offsetY=beam.offsetY;tile.offsetZ=beam.offsetZ;
            const auto image=imageAnchor(p,a,tile.animationSource->memberPath,false);
            const auto count=size_t(std::ceil(extent/image.width));
            if(count>256)throw std::invalid_argument("Laser source tile composition exceeds phase capacity");
            tile.evidence.push_back({{"policy","inferred-1031-source-laser-composition-v1"},{"classification","inferred"},
                {"source_tile",image.evidence},{"source_forward_extent",extent},{"tile_count",count},
                {"basis","Repeat authored tile visible width along the exact LaserFire forward source extent, sharing birth and source frame clock; final tile may overrun by less than one tile"},
                {"native_confirmed",false}});
            for(size_t i=0;i<count;++i){auto segment=tile;segment.offsetX+=i*image.width;segment.pulseId=uint32_t(i);publish(std::move(segment));}
            auto end=phase(p,a,command,*root,"laser_end",{"[etc motion]#2"},{},false);
            end.offsetX=beam.offsetX+extent;end.offsetY=beam.offsetY;end.offsetZ=beam.offsetZ;publish(std::move(end));continue;
        }
        if(f=="heavy_projectile"&&command.key.skillId==40) {
            auto missile=phase(p,a,command,*root,"steyr_projectile",{"[basic motion]#0"},{"[attack info]#0"},true);missile.speed=1200;missile.range=600;missile.lifetimeMs=500;coefficients(missile,"攻击力",false);publish(missile);
            auto expObject=explicitObject(p,command,"atsteyrfireexplosion");auto explosion=phase(p,a,command,expObject,"explosion",{"[basic motion]#0"},{"[attack info]#0"},true);explosion.releaseDelayMs+=missile.lifetimeMs;explosion.offsetX=600;radius(explosion,100);coefficients(explosion,"爆炸",false);publish(explosion);continue;
        }
        auto attack=command;
        // Correctly bind objects with an empty basic ANI to their explicit
        // attacking etc motion, never to the first unrelated effect array.
        if(!attack.animationSource||!attack.attackSource)attack=phase(p,a,command,*root,"projectile",{"[basic motion]#0","[etc motion]#0"},{"[attack info]#0","[etc attack info]#0"},true);
        if(f=="channel_flame") {
            attack.speed=0;attack.followCaster=true;attack.effectRole="channel_contact";
            attack.intervalMs=std::max<int64_t>(100,attack.intervalMs);
            auto start=flameVisual(p,a,command,"start"),loop=flameVisual(p,a,command,"loop"),end=flameVisual(p,a,command,"end");
            attack.offsetX=start.offsetX;attack.offsetY=start.offsetY;attack.offsetZ=start.offsetZ;
            attack.evidence.push_back({{"policy","inferred-1031-source-weapon-muzzle-v1"},{"classification","inferred"},
                {"basis","Share the source-weapon endpoint used by the visual start; retain the original OBJ collision ANI and ATK"},
                {"visual_reference",start.animationSource->json()},{"offset_xyz",{attack.offsetX,attack.offsetY,attack.offsetZ}},
                {"anchor_evidence",start.evidence.at(start.evidence.size()-2)}});
            publish(attack);
            const auto startDuration=std::min(start.lifetimeMs,attack.lifetimeMs);
            start.lifetimeMs=startDuration;publish(std::move(start));
            if(attack.lifetimeMs>startDuration){loop.releaseDelayMs+=startDuration;loop.lifetimeMs=attack.lifetimeMs-startDuration;publish(std::move(loop));}
            end.releaseDelayMs+=attack.lifetimeMs;publish(std::move(end));continue;
        }
        if(f=="channel_projectile"||f=="multishot"||f=="multishot_finisher"||f=="heavy_projectile"||f=="spread_shot"||f=="grab_ground_shoot"||f=="grab_aerial_gatling") {
            const auto n=std::max<uint32_t>(1,attack.count);const auto gap=attack.intervalMs>0?attack.intervalMs:100;
            for(uint32_t i=0;i<n;++i){auto bullet=attack;bullet.count=1;bullet.intervalMs=0;bullet.releaseDelayMs+=int64_t(i)*gap;bullet.effectRole="projectile";bullet.pulseId=i;
                bullet.lifetimeMs=bullet.speed>0?std::max<int64_t>(1,int64_t(1000*(bullet.range>0?bullet.range:900)/bullet.speed)):a.animation(bullet.animationSource->memberPath)->duration;publish(bullet);}
        }else publish(attack);
    }
    return output;
}
Json runFemaleGunnerEntityTests(Pvf &p,Assets &a) {
    CharacterCatalog catalog(p);const auto plan=loadExperimentalCharacterPlan(p,a,catalog,{5,0,0});
    Json rows=Json::array(),failures=Json::array();int checks=0;size_t active=0,damagingPhases=0,sourceGeometry=0,inferredGeometry=0;
    auto check=[&](bool okay,const std::string &name){++checks;if(!okay)throw std::runtime_error(name);};
    for(const auto &[key,row]:plan.skills)if(row.kind==SkillSourceKind::Active) {
        ++active;Json result={{"key",key.json()},{"name",row.name},{"levels",Json::array()}};
        try {
            const auto &descriptor=plan.femaleGunnerSkills.at(key);int maximum=1;
            for(const auto &v:row.data->values("[growtype maximum level]"))if(v.is_number_integer())maximum=std::max(maximum,v.get<int>());
            std::set<int> levels{1,maximum};
            for(const int level:levels){auto command=evaluateFemaleGunnerSkill(descriptor,*row.data,level,0);command.actionSequence=73;command.preflightOnly=true;
                const auto phases=expandFemaleGunnerEntities(p,a,{command});Json phaseRows=Json::array();check(!phases.empty(),"empty executable phase graph");
                if(command.family=="radial_multishot") {
                    const auto &attack=phases.front();
                    check(attack.effectRole=="radial_shot"&&attack.kind==FemaleGunnerCommandKind::Strike,
                        "RandomShoot requires one source ATK pulse host");
                    check(phases.size()==size_t(attack.count)+1,"RandomShoot omits or duplicates independent muzzle pulses");
                    for(size_t i=1;i<phases.size();++i) {
                        const auto &visual=phases[i];const auto animation=a.animation(visual.animationSource->memberPath);
                        check(visual.effectRole=="radial_muzzle"&&visual.kind==FemaleGunnerCommandKind::Stage&&
                            !visual.attackSource&&!visual.box&&visual.followCaster,"RandomShoot muzzle incorrectly produces extra damage");
                        check(visual.pulseId==i-1&&visual.releaseDelayMs==command.releaseDelayMs+int64_t(i-1)*attack.intervalMs&&
                            visual.lifetimeMs==animation->duration&&animation->frames.size()==5&&animation->duration==400,
                            "RandomShoot muzzle loses source five-frame timeline or command pulse schedule");
                        check(!visual.rawTables.value("body_motion_attack",true),"RandomShoot muzzle remains invisible as a body-only attack");
                    }
                }
                if(command.family=="g_transform") {
                    check(femaleGunnerGTransformExtensionMs(command)>0,"G transform lacks exact extension");
                    check((femaleGunnerGTransformBaseDurationMs(command)>0)==(key.skillId==79),"G2/G3 extension confused with base duration");
                    check(phases.front().rawTables.at("g_transform_extension_ms")==femaleGunnerGTransformExtensionMs(command),"G timing source metadata lost");
                }
                if(command.family=="channel_flame") {
                    size_t contacts=0,visible=0;
                    for(const auto &part:phases) {
                        if(part.attackSource){++contacts;check(part.effectRole=="channel_contact"&&!part.box,
                            "Flame must preserve its sole authored OBJ collision animation and ATK");}
                        if(part.effectRole.rfind("channel_visual_",0)==0) {
                            ++visible;bool pixels=false;
                            for(const auto &frame:a.animation(part.animationSource->memberPath)->frames)pixels|=!frame.image.empty();
                            check(pixels&&!part.attackSource&&!part.box&&part.kind==FemaleGunnerCommandKind::Stage,
                                "Flame start/loop/end require actual visible source frames without extra damage");
                            check(part.offsetX==phases.front().offsetX&&part.offsetZ==phases.front().offsetZ&&
                                part.offsetX>0&&part.offsetZ>0,"Flame contact and visual use one source weapon muzzle anchor");
                        }
                    }
                    check(contacts==1&&visible>=2,"Channel flame lacks its single contact and visible phase composition");
                    if(key.skillId==13) {
                        auto stop=stopFemaleGunnerChannel(command,"source_test");
                        const auto stopped=expandFemaleGunnerEntities(p,a,{stop});
                        check(stopped.size()==2&&stopped.front().kind==FemaleGunnerCommandKind::Clear&&
                            stopped.back().effectRole=="channel_visual_end"&&stopped.back().releaseDelayMs==0&&
                            !stopped.back().attackSource,"Flame stop must atomically replace the sustained contact with one visual-only source tail");
                    }
                }
                if(command.family=="heavy_projectile"&&key.skillId==39) {
                    size_t damage=0,tiles=0;double previous=-1;
                    for(const auto &part:phases) {
                        if(part.attackSource) {
                            ++damage;check(part.effectRole=="laser_beam"&&!part.box&&
                                part.animationSource->memberPath.find("/laserfire.ani")!=std::string::npos,
                                "Laser damage must use original LaserFire per-frame boxes instead of a guessed LaserTile volume");
                        }
                        if(part.effectRole=="laser_tile") {
                            ++tiles;check(!part.attackSource&&!part.box&&part.offsetX>previous,
                                "Laser tile composition must cover the source forward extent without creating extra attacks");previous=part.offsetX;
                        }
                    }
                    check(damage==1&&tiles>1,"Laser requires one source attack and multiple visible source-width tiles");
                }
                if(key.skillId==1) {
                    auto bullet=command;bullet.family="enchanted_bullet";
                    const auto normal=femaleGunnerFlameImpactCommands(p,a,bullet),special=femaleGunnerFlameImpactCommands(p,a,bullet,{"[plant]"});
                    check(normal.size()==sourceCount(command,"火焰爆炸的次数上限",0)&&normal.size()>1,"Flame impact loses source explosion limit");
                    check(special.size()==normal.size()&&special[0].damage.percent>normal[0].damage.percent,"Flame category operand has no consumer");
                    const auto ratio=exactOperand(command,"第二次爆炸的攻击力比率");
                    check(ratio&&std::abs(normal[1].damage.percent-normal[0].damage.percent* *ratio/100)<0.0001,"Flame second explosion ratio has no consumer");
                    for(const auto &impact:normal){check(impact.preflightOnly&&impact.actionSequence==73,"Flame impact loses transaction identity");
                        check(impact.animationSource&&impact.attackSource&&impact.speed==0&&impact.offsetX==0&&impact.offsetY==0,"Flame impact is not contact-bound stationary source phase");
                        check(readAttackDamage(p.script(impact.attackSource->memberPath),AttackStatusConsumer::StunHostV1).usable(),"Flame impact ATK is not executable");}
                }
                for(const auto &phase:phases){check(phase.preflightOnly,"phase lost preflightOnly");check(phase.actionSequence==73&&phase.key==key,"phase lost owner action identity");
                    check(phase.lifetimeMs>=0&&phase.releaseDelayMs>=0&&phase.intervalMs>=0&&phase.count<=4096,"invalid phase bounds");
                    const bool damage=phase.kind==FemaleGunnerCommandKind::Strike||phase.kind==FemaleGunnerCommandKind::Launch||phase.kind==FemaleGunnerCommandKind::Spawn;
                    bool hasSourceBox=false;if(phase.animationSource){const auto animation=a.animation(phase.animationSource->memberPath);
                        check(!animation->frames.empty()&&animation->duration>0,"phase ANI lacks positive duration");for(const auto &frame:animation->frames)for(const auto &box:frame.boxes)if(box.type==15)hasSourceBox=true;}
                    if(damage){++damagingPhases;check(phase.attackSource.has_value(),"damage phase lacks ATK");const auto atk=readAttackDamage(p.script(phase.attackSource->memberPath),AttackStatusConsumer::StunHostV1);
                        check(atk.usable(),"damage phase has unusable ATK: "+phase.attackSource->memberPath+" "+atk.snapshot().dump());check(phase.box.has_value()||hasSourceBox,"damage phase has no executable geometry");
                        if(hasSourceBox&&!phase.box)++sourceGeometry;else ++inferredGeometry;
                        check(phase.animationSource->memberPath.find("waitbody")==std::string::npos&&phase.animationSource->memberPath.find("/stay")==std::string::npos,"waiting ANI used as damaging phase");
                    }
                    if(phase.effectRole=="robot_body"||phase.effectRole=="thrown_body"||phase.effectRole=="mine_body")check(!phase.attackSource,"body/flight mistakenly carries damage ATK");
                    phaseRows.push_back({{"role",phase.effectRole},{"kind",femaleGunnerCommandKindName(phase.kind)},{"damage",damage},
                        {"object",phase.objectSource?Json(phase.objectSource->memberPath):Json()},{"animation",phase.animationSource?Json(phase.animationSource->memberPath):Json()},
                        {"attack",phase.attackSource?Json(phase.attackSource->memberPath):Json()},{"ani_type15",hasSourceBox},{"controller_box",phase.box.has_value()},
                        {"delay_ms",phase.releaseDelayMs},{"lifetime_ms",phase.lifetimeMs},{"interval_ms",phase.intervalMs},{"count",phase.count},{"pulse_id",phase.pulseId},
                        {"percent",phase.damage.percent},{"independent_percent",phase.damage.independentPercent}});
                }
                result["levels"].push_back({{"level",level},{"phases",phaseRows},{"phase_count",phases.size()}});
            }
        }catch(const std::exception &e){result["error"]=e.what();failures.push_back({{"key",key.json()},{"error",e.what()}});}
        rows.push_back(std::move(result));
    }
    return {{"status",failures.empty()?"passed":"failed"},{"checks",checks},{"active_skills",active},{"damaging_phases",damagingPhases},
        {"source_ani_geometry_phases",sourceGeometry},{"inferred_box_phases",inferredGeometry},{"skills",rows},{"failures",failures},
        {"scope","All current1031 female active source skills at level1 and largest authored branch ceiling; source phases, ATK usability, geometry, preflight and schedule bounds; native timing and visual comparison pending"}};
}
} // namespace dnf
