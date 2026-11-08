#include "dnf/renderer.hpp"
#include <stdexcept>

namespace dnf {
Json runLongUiTextTests(Renderer &renderer,const std::filesystem::path &output) {
    Json checks=Json::array();const auto check=[&](bool okay,const char *name){if(!okay)throw std::runtime_error(name);checks.push_back(name);};
    renderer.resize(800,600);renderer.ui();
    const auto framebuffer=[&] {
        std::vector<uint8_t> pixels(800*600*4);
        if(SDL_RenderReadPixels(renderer.raw(),nullptr,SDL_PIXELFORMAT_RGBA32,pixels.data(),800*4)!=0)
            throw std::runtime_error(SDL_GetError());
        return pixels;
    };
    const std::string prefix="副本准备失败：";
    std::string message=prefix;
    for(int i=0;i<1300;++i)message+="source-error-";
    const auto shortWidth=renderer.textWidth(prefix,16),longWidth=renderer.textWidth(message,16);
    check(longWidth>16384 && shortWidth<800,"Actual text layout reproduces a diagnostic wider than the reported GPU limit");
    renderer.begin();renderer.text(prefix,10,10,16);const auto shortPixels=framebuffer();
    renderer.begin();renderer.text(message,10,10,16);const auto longPixels=framebuffer();
    bool prefixEqual=true;size_t visible=0;
    for(int y=0;y<45;++y)for(int x=0;x<std::max(0,shortWidth-3);++x)for(int c=0;c<4;++c) {
        const auto i=(size_t(y)*800+size_t(x))*4+c;
        if(shortPixels[i]!=longPixels[i])prefixEqual=false;
        if(c==0 && longPixels[i]!=9)++visible;
    }
    check(prefixEqual && visible>0,"Long diagnostic keeps exact visible glyph/outline pixels of the original text prefix");
    const auto report=renderer.textTextureReport();
    check(report.at("tiled_entries").get<size_t>()>=1 && report.at("largest_logical_width").get<int>()>16384 &&
        report.at("maximum_uploaded_size")[0].get<int>()<=4096 && report.at("maximum_uploaded_size")[1].get<int>()<=4096,
        "Actual Renderer splits oversized text into driver-safe uploads while retaining full logical width");
    renderer.screenshot(output/"oversized-diagnostic.png");
    const auto cacheBefore=renderer.cachedTextures();renderer.text(message,10,10,16);
    check(renderer.cachedTextures()==cacheBefore && renderer.textTextureReport()==report,"Repeated long diagnostic reuses cached tiles");
    renderer.begin();renderer.text(message,float(4000),10,16,{200,210,220,150});renderer.present();
    check(renderer.errors.empty() && renderer.textWidth(prefix,16)==shortWidth && renderer.textWidth(message,16)==longWidth,
        "Clipping/modulation and repeated rendering preserve metrics without throwing a fatal texture error");
    return {{"status","passed"},{"count",checks.size()},{"checks",checks},{"textures",report},
        {"scope","Actual hidden SDL Renderer uploads/draws original over-limit diagnostic; frontend error readability remains user validation"}};
}
} // namespace dnf
