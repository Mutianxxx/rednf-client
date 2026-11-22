#include "dnf/drop_presentation.hpp"
#include "dnf/content_profile.hpp"
namespace dnf {
void keyDropTextureBorderBlack(Pixels &pixels) {
    const int w = pixels.width, h = pixels.height;
    if (w <= 0 || h <= 0 || pixels.rgba.size() < size_t(w) * size_t(h) * 4)
        return;
    auto nearBlack = [&](int x, int y) {
        const auto *p = &pixels.rgba[(size_t(y) * size_t(w) + size_t(x)) * 4];
        return p[3] > 0 && p[0] <= 8 && p[1] <= 8 && p[2] <= 8;
    };
    std::vector<uint8_t> seen(size_t(w) * size_t(h), 0);
    std::vector<std::array<int, 2>> stack;
    auto seed = [&](int x, int y) {
        if (x < 0 || y < 0 || x >= w || y >= h) return;
        const size_t at = size_t(y) * size_t(w) + size_t(x);
        if (seen[at] || !nearBlack(x, y)) return;
        seen[at] = 1;
        stack.push_back({x, y});
    };
    for (int x = 0; x < w; ++x) { seed(x, 0); seed(x, h - 1); }
    for (int y = 0; y < h; ++y) { seed(0, y); seed(w - 1, y); }
    while (!stack.empty()) {
        const auto [x, y] = stack.back();
        stack.pop_back();
        pixels.rgba[(size_t(y) * size_t(w) + size_t(x)) * 4 + 3] = 0;
        seed(x - 1, y); seed(x + 1, y); seed(x, y - 1); seed(x, y + 1);
    }
}
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
