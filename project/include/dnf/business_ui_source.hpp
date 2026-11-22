#pragma once
#include "resources.hpp"
#include <map>

namespace dnf {
// Count-prefixed .ui records retain their nested options and parent identity.
// Anonymous -1 IDs are ordinal bindings, never globally unique names.
struct BusinessUiControl {
    std::string type, name, parent, parentKind;
    int parentState = -1;
    double x = 0, y = 0;
    size_t ordinal = 0, offset = 0;
    std::vector<std::string> strings;
    std::vector<int> integers;
    std::vector<Field> options;
    Json option(const std::string &tag) const;
    Json snapshot() const;
};
struct BusinessUiLayout {
    Script source;
    std::vector<BusinessUiControl> controls;
    std::vector<std::pair<std::string,std::string>> children; // path, parent ID
    const BusinessUiControl &require(const std::string &name, const std::string &type = "") const;
    std::array<int,2> position(const BusinessUiControl &) const;
    std::array<int,2> position(const std::string &name) const { return position(require(name)); }
    Json snapshot() const;
};
BusinessUiLayout readBusinessUiLayout(Script source);
struct BusinessUiGrid {
    int x = 0, y = 0, columns = 0, rows = 0, cellWidth = 0, cellHeight = 0, margin = 0;
    static BusinessUiGrid from(const BusinessUiLayout &,const std::string &name);
    int perPage() const { return columns * rows; }
    std::array<int,2> cell(int ordinal) const;
    int hit(int mx,int my) const;
};
// Pagination is shared by mouse click, mouse wheel, and diagnostic snapshots.
struct BusinessUiPage {
    static int pages(int count,int pageSize);
    static int clamp(int page,int count,int pageSize);
    static std::vector<int> indices(int page,int count,int pageSize);
};
class BusinessUiSources {
    Pvf *pvf_ = nullptr;
    std::map<std::string,BusinessUiLayout> layouts_;
    Script portraits_;
  public:
    void bind(Pvf &);
    bool bound() const { return pvf_ != nullptr; }
    const BusinessUiLayout &layout(const std::string &path) const;
    std::pair<std::string,int> portrait(int npc) const;
    Json snapshot() const;
};
Json runBusinessUiSourceTests(Pvf &);
} // namespace dnf
