// Derived from attack_demo/src/main.cpp; regenerate with tools/prepare_renderer.py.
struct Texture {SDL_Texture* value=nullptr;int w=0,h=0,cropX=0,cropY=0,lw=0,lh=0;};
struct Canvas {
    Content& content;
    SDL_Window* window=nullptr;
    SDL_Renderer* renderer=nullptr;
    std::map<std::string,Texture> textures,texts;
    Json unsupported=Json::array();
    std::set<std::string> noted;
    double zoom=1;
    std::string rendererName;
    explicit Canvas(Content& c):content(c) {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"0");
        window=SDL_CreateWindow(u8"DNF · 技能战斗演示",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1200,820,SDL_WINDOW_RESIZABLE|SDL_WINDOW_ALLOW_HIGHDPI|(SDL_getenv("DNF_DEMO_HIDDEN")?SDL_WINDOW_HIDDEN:0));
        if(!window)throw std::runtime_error(SDL_GetError());
        renderer=SDL_CreateRenderer(window,-1,SDL_getenv("DNF_DEMO_HIDDEN")&&!SDL_getenv("DNF_DEMO_ACCELERATED")?SDL_RENDERER_SOFTWARE:SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        if(!renderer)renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);
        if(!renderer)throw std::runtime_error(SDL_GetError());
        SDL_RendererInfo rendererInfo{};SDL_GetRendererInfo(renderer,&rendererInfo);rendererName=rendererInfo.name?rendererInfo.name:"unknown";
        SDL_SetWindowMinimumSize(window,1050,720);SDL_RenderSetLogicalSize(renderer,1200,820);
        SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
        SDL_StopTextInput();
    }
    ~Canvas(){for(auto& e:textures)SDL_DestroyTexture(e.second.value);for(auto&e:texts)SDL_DestroyTexture(e.second.value);SDL_DestroyRenderer(renderer);SDL_DestroyWindow(window);}
    Texture& texture(const std::string& image,int frame,bool white=false) {
        std::string p=concrete(image);
        auto &subs=content.profile["image_substitutions"];
        if(subs.contains(normalize(image)))p=subs[normalize(image)].get<std::string>();
        std::string key=p+"#"+std::to_string(frame)+(white?"#white":"");
        auto found=textures.find(key);if(found!=textures.end())return found->second;
        auto pix=content.assets.pixels(p,frame);Texture out;
        if(white)for(size_t i=0;i<pix.rgba.size();i+=4)pix.rgba[i]=pix.rgba[i+1]=pix.rgba[i+2]=255;
        out.w=pix.width;out.h=pix.height;out.cropX=pix.x;out.cropY=pix.y;out.lw=pix.logicalWidth;out.lh=pix.logicalHeight;
        if(out.w&&out.h) {
            out.value=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA32,SDL_TEXTUREACCESS_STATIC,out.w,out.h);
            if(!out.value||SDL_UpdateTexture(out.value,nullptr,pix.rgba.data(),out.w*4))throw std::runtime_error(SDL_GetError());
        }
        return textures.emplace(key,out).first->second;
    }
    void rect(float x,float y,float w,float h,SDL_Color c,bool fill=true){SDL_SetRenderDrawColor(renderer,c.r,c.g,c.b,c.a);SDL_FRect r{x,y,w,h};if(fill)SDL_RenderFillRectF(renderer,&r);else SDL_RenderDrawRectF(renderer,&r);}
    void clearTextures(){for(auto&e:textures)SDL_DestroyTexture(e.second.value);textures.clear();}
    void text(const std::string& message,int x,int y,int size,SDL_Color color={235,230,210,255}) {
        if(texts.size()>1500){for(auto&e:texts)SDL_DestroyTexture(e.second.value);texts.clear();}
        std::string key=message+"#"+std::to_string(size);auto found=texts.find(key);
        if(found==texts.end()) {
            auto s=wide(message);HDC dc=CreateCompatibleDC(nullptr);
            HFONT font=CreateFontW(-size,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH,L"Microsoft YaHei");
            auto oldfont=SelectObject(dc,font);SIZE dim{};GetTextExtentPoint32W(dc,s.data(),int(s.size()),&dim);
            int w=dim.cx+4,h=size+10;
            BITMAPINFO bi{};bi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);bi.bmiHeader.biWidth=w;bi.bmiHeader.biHeight=-h;bi.bmiHeader.biPlanes=1;bi.bmiHeader.biBitCount=32;bi.bmiHeader.biCompression=BI_RGB;
            void* bits=nullptr;HBITMAP bitmap=CreateDIBSection(dc,&bi,DIB_RGB_COLORS,&bits,nullptr,0);auto oldbmp=SelectObject(dc,bitmap);
            memset(bits,0,size_t(w)*h*4);SetTextColor(dc,RGB(255,255,255));SetBkMode(dc,TRANSPARENT);TextOutW(dc,2,1,s.data(),int(s.size()));GdiFlush();
            Bytes rgba(size_t(w)*h*4);auto src=(uint8_t*)bits;
            for(size_t i=0;i<size_t(w)*h;++i){rgba[i*4]=rgba[i*4+1]=rgba[i*4+2]=255;rgba[i*4+3]=std::max({src[i*4],src[i*4+1],src[i*4+2]});}
            SelectObject(dc,oldbmp);SelectObject(dc,oldfont);DeleteObject(bitmap);DeleteObject(font);DeleteDC(dc);
            Texture out;out.w=w;out.h=h;out.value=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA32,SDL_TEXTUREACCESS_STATIC,w,h);SDL_UpdateTexture(out.value,nullptr,rgba.data(),w*4);SDL_SetTextureBlendMode(out.value,SDL_BLENDMODE_BLEND);
            found=texts.emplace(key,out).first;
        }
        auto&t=found->second;SDL_FRect dst{float(x),float(y),float(t.w),float(t.h)};
        SDL_SetTextureColorMod(t.value,0,0,0);dst.x+=1;dst.y+=1;SDL_RenderCopyF(renderer,t.value,nullptr,&dst);
        SDL_SetTextureColorMod(t.value,color.r,color.g,color.b);SDL_SetTextureAlphaMod(t.value,color.a);dst.x-=1;dst.y-=1;SDL_RenderCopyF(renderer,t.value,nullptr,&dst);
    }
    void sprite(const std::string& image,int frame,double x,double y,int facing=1,double ox=0,double oy=0,double sx=1,double sy=1,double radians=0,int blend=0,SDL_Color color={255,255,255,255},bool origin=true,bool white=false) {
        auto&t=texture(image,frame,white);if(!t.value)return;
        auto quad=imageQuad(x,y,ox*zoom,oy*zoom,(origin?t.cropX:0)*zoom,(origin?t.cropY:0)*zoom,t.w*zoom,t.h*zoom,facing,sx,sy,radiansToDegrees(radians));
        SDL_Vertex vertices[4];const SDL_FPoint uv[]={{0,0},{1,0},{1,1},{0,1}};
        for(int i=0;i<4;++i) vertices[i]={{float(quad[i].x),float(quad[i].y)},color,uv[i]};
        const int indices[]={0,1,2,0,2,3};
        SDL_SetTextureBlendMode(t.value,blend==1||blend==2?SDL_BLENDMODE_ADD:SDL_BLENDMODE_BLEND);
        if(SDL_RenderGeometry(renderer,t.value,vertices,4,indices,6))throw std::runtime_error(SDL_GetError());
    }
    void animation(const std::string& path,double ms,double x,double y,int face,bool loop=false,int overrideFrame=-1,const std::string& imageOverride="") {
        auto ani=content.assets.animation(path);auto pose=ani->samplePose(ms,loop,overrideFrame);
        if(!imageOverride.empty()&&!pose.image.empty())pose.image=imageOverride;
        if(pose.image.empty())return;
        auto byte=[](double v){return uint8_t(std::lround(std::clamp(v,0.0,255.0)));};
        SDL_Color color{byte(pose.rgba[0]),byte(pose.rgba[1]),byte(pose.rgba[2]),byte(pose.rgba[3])};
        if(pose.flip&1)pose.scaleX=-pose.scaleX;if(pose.flip&2)pose.scaleY=-pose.scaleY;
        if(!pose.unsupported.empty()&&noted.insert(path).second)unsupported.push_back({{"path",path},{"unconsumed",pose.unsupported}});
        sprite(pose.image,pose.imageFrame,x,y,face,pose.x,pose.y,pose.scaleX,pose.scaleY,pose.rotationRadians,pose.blend,color);
    }
    void screenshot(const fs::path& file) {
        int w,h;SDL_GetRendererOutputSize(renderer,&w,&h);Bytes pixels(size_t(w)*h*4);
        if(SDL_RenderReadPixels(renderer,nullptr,SDL_PIXELFORMAT_RGBA32,pixels.data(),w*4))throw std::runtime_error(SDL_GetError());
        fs::create_directories(file.parent_path());
        // stb's filename API uses narrow fopen on Windows; write through a Unicode filesystem path.
        std::ofstream stream(file,std::ios::binary);
        auto output=[](void* context,void* data,int size){((std::ofstream*)context)->write((const char*)data,size);};
        if(!stream||!stbi_write_png_to_func(output,&stream,w,h,4,pixels.data(),w*4))throw std::runtime_error("Screenshot write failed");
        stream.flush();if(!stream)throw std::runtime_error("Screenshot write failed");
    }
};

