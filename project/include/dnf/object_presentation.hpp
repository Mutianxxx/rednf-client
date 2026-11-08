#pragma once
#include "dnf/objects.hpp"
namespace dnf {
void compileObjectPresentation(Pvf &,Assets &,ObjectDefinition &);
void createObjectPresentation(ObjectInstance &,bool destroyed);
void advanceObjectPresentation(ObjectInstance &,int64_t deltaUs);
Json saveObjectPresentation(const ObjectInstance &);
void restoreObjectPresentation(ObjectInstance &,const Json &);
}
