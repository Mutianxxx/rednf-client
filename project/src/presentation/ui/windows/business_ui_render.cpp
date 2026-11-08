#include "dnf/business_ui_render.hpp"
namespace dnf {
std::string businessUiPlain(std::string s) {
    // PVF tagged dialogue is rich text. Keep its text and explicit newlines;
    // colour/speaker markup remains preserved in the immutable source.
    std::string out;bool tag=false;
    for(size_t i=0;i<s.size();++i){if(s[i]=='<'){tag=true;continue;}if(tag){if(s[i]=='>')tag=false;continue;}
        if(s[i]=='\\'&&i+1<s.size()&&s[i+1]=='n'){out+='\n';++i;}else if(s[i]!='\r')out+=s[i];}
    return out;
}
std::vector<std::string> businessUiLines(Renderer &r,const std::string &value,int width,int size) {
    auto s=businessUiPlain(value);std::vector<std::string> out;std::string line;
    for(size_t i=0;i<s.size();){const unsigned char ch=s[i];size_t n=ch<0x80?1:ch<0xe0?2:ch<0xf0?3:4;n=std::min(n,s.size()-i);
        if(ch=='\n'){out.push_back(line);line.clear();++i;continue;}
        const auto glyph=s.substr(i,n);if(!line.empty()&&r.textWidth(line+glyph,size)>width){out.push_back(line);line.clear();}line+=glyph;i+=n;
    }
    if(!line.empty()||out.empty())out.push_back(line);return out;
}
int businessUiTextPages(Renderer &r,const std::string &text,int x,int y,int width,int lines,int page,int mx,int my,bool click,int size) {
    const auto wrapped=businessUiLines(r,text,width,size);page=BusinessUiPage::clamp(page,int(wrapped.size()),lines);
    for(int i:BusinessUiPage::indices(page,int(wrapped.size()),lines))r.text(wrapped[i],float(x),float(y+(i-page*lines)*(size+5)),size);
    const auto pages=BusinessUiPage::pages(int(wrapped.size()),lines);
    if(pages>1){const int yy=y+lines*(size+5)+2;
        if(r.button("<",x,yy,30,23,mx,my,click,page>0))--page;
        r.text(std::to_string(page+1)+" / "+std::to_string(pages),float(x+40),float(yy+4),12);
        if(r.button(">",x+width-30,yy,30,23,mx,my,click,page+1<pages))++page;
    }
    return page;
}
std::string businessUiFitted(Renderer &r,std::string s,int width,int size) {
    s=businessUiPlain(s);if(r.textWidth(s,size)<=width)return s;
    while(!s.empty()&&r.textWidth(s+"…",size)>width){size_t n=s.size()-1;while(n&&(uint8_t(s[n])&0xc0)==0x80)--n;s.erase(n);}return s+"…";
}
void businessUiImage(Renderer &r,const BusinessUiLayout &layout,const std::string &name,int x,int y) {
    const auto &c=layout.require(name,"[image]");if(c.strings.empty()||c.integers.empty())throw std::runtime_error("UI image missing source");
    auto p=layout.position(c);r.sprite(c.strings[0],c.integers[0],x+p[0],y+p[1]);
}
void businessUiBoard(Renderer &r,Assets &assets,const BusinessUiControl &c,int x,int y) {
    if(c.type!="[board image]"||c.strings.size()!=1||c.integers.size()!=11)throw std::runtime_error("UI unsupported board binding");
    // Source board parameters are width, height, then nine frame IDs.
    std::array<Pixels,9> metrics;for(int i=0;i<9;++i)metrics[i]=assets.pixels(c.strings[0],c.integers[i+2]);
    const int left=std::max(1,metrics[0].logicalWidth),right=std::max(1,metrics[2].logicalWidth),top=std::max(1,metrics[0].logicalHeight),bottom=std::max(1,metrics[6].logicalHeight);
    const int widths[]={left,c.integers[0]-left-right,right},heights[]={top,c.integers[1]-top-bottom,bottom};
    int yy=y;for(int row=0;row<3;++row){int xx=x;for(int col=0;col<3;++col){const int i=row*3+col;const auto &p=metrics[i];
        if(widths[col]>0&&heights[row]>0)r.sprite(c.strings[0],c.integers[i+2],xx,yy,1,double(widths[col])/std::max(1,p.logicalWidth),0,255,0,true,double(heights[row])/std::max(1,p.logicalHeight));
        xx+=widths[col];}yy+=heights[row];}
}
} // namespace dnf
