#include "dnf/drop_presentation.hpp"
#include "dnf/content_profile.hpp"
namespace dnf {
DropSprite prepareDropSprite(Assets &assets,const Script &item) {
    DropSprite result;result.evidence={{"source",item.path},{"sha256",sha256(item.rawBytes)},
        {"fields",Json::array()}};
    for(const auto &f:item.fields)if(f.tag=="[field image]"||f.tag=="[icon]")
        result.evidence["fields"].push_back({{"tag",f.tag},{"offset",f.offset},{"values",f.values}});
    for(const auto *tag:{"[field image]","[icon]"}) {
        const auto value=item.values(tag);
        if(value.size()<2||!value[0].is_string()||!value[1].is_number_integer()||value[0].get<std::string>().empty())continue;
        try {
            const auto image=normalize(value[0]);const auto index=value[1].get<int>();
            const auto px=assets.pixels(image,index);
            bool visible=false;
            for(size_t i=3;i<px.rgba.size();i+=4)if(px.rgba[i]){visible=true;break;}
            if(px.width<=0||px.height<=0||!visible)throw std::runtime_error("Drop sprite has no visible pixels");
            result.image=image;result.frame=index;result.evidence["selected_tag"]=tag;
            result.anchorX=px.x+px.width/2.0;result.anchorY=px.y+px.height;
            result.evidence["binding"]=std::string(tag)=="[field image]"?"authored-field-image":"inferred-same-item-icon-fallback";
            result.evidence["image"]={{"path",image},{"frame",index},{"crop_xy",{px.x,px.y}},
                {"crop_size",{px.width,px.height}},{"logical_size",{px.logicalWidth,px.logicalHeight}}};
            result.evidence["anchor"]={{"xy",{result.anchorX,result.anchorY}},
                {"policy","inferred-visible-crop-bottom-center-at-drop-ground-v1"},
                {"source_crop_unchanged",true},{"native_anchor_verified",false}};
            return result;
        }catch(const std::exception &error){result.diagnostics.push_back({{"tag",tag},{"error",error.what()}});}
    }
    result.diagnostics.push_back({{"kind","drop_has_no_renderable_source_image"},{"source",item.path}});
    return result;
}
DropSprite prepareGoldDropSprite(Pvf &pvf,Assets &assets) {
    // The reward ledger uses gold as a currency, not an inventory entry.
    // Current 1031 stackable/gold.stk has no [field image], but binds its own
    // coin icon. Retain that distinction instead of drawing an unrelated fx.
    try{return prepareDropSprite(assets,pvf.script("stackable/gold.stk"));}
    catch(const std::exception &error) {
        DropSprite result;result.diagnostics.push_back({{"kind","gold_source_failure"},
            {"source","stackable/gold.stk"},{"error",error.what()}});return result;
    }
}
} // namespace dnf
