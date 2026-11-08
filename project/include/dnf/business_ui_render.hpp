#pragma once
#include "business_ui_source.hpp"
#include "renderer.hpp"
namespace dnf {
std::string businessUiPlain(std::string);
std::vector<std::string> businessUiLines(Renderer &,const std::string &,int width,int size=13);
// Keeps all wrapped lines; returns the clamped page used for the next frame.
int businessUiTextPages(Renderer &,const std::string &,int x,int y,int width,int lines,int page,
                        int mx,int my,bool click,int size=13);
std::string businessUiFitted(Renderer &,std::string,int width,int size=13);
void businessUiImage(Renderer &,const BusinessUiLayout &,const std::string &,int x=0,int y=0);
void businessUiBoard(Renderer &,Assets &,const BusinessUiControl &,int x,int y);
} // namespace dnf
