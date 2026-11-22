#pragma once
#include "business_ui_render.hpp"
#include <optional>
namespace dnf {
struct SkillLearningUiAction {
    std::optional<SkillKey> purchase;
    SkillLearningQuote quote;
    bool close=false,configure=false,resetTest=false,openTestPreview=false;
};
class SkillLearningUi {
    struct LearningRow {
        SkillKey key;
        SkillSourceKind kind=SkillSourceKind::Unknown;
        RuntimeSkillPolicy runtime;
        SkillLearningQuote quote;
        std::string name,error,sourcePath,iconPath;
        int iconFrame=-1;
        bool tp=false;
    };
    BusinessUiSources sources_;
    Assets &assets_;
    int page_=0,textPage_=0;
    bool passive_=false,tp_=false;
    std::optional<SkillKey> selected_;
    std::optional<CharacterIdentity> identity_;
    Json view_=Json::object();
    // Values, never borrowed skill-definition pointers. The UI source is fixed
    // for this instance; identity/source owner and ordered keys invalidate it.
    const CharacterCatalog *metadataOwner_=nullptr;
    std::string metadataSource_;
    std::vector<LearningRow> cachedRows_;
    Json quoteContext_=Json(),budget_=Json();
    std::string budgetError_;
    std::optional<SkillKey> detailKey_;
    std::string detailResource_,detailCommand_,detailText_;
    int viewGroup_=-1;
    uint64_t metadataBuilds_=0,quoteBuilds_=0;
  public:
    SkillLearningUi(Pvf &pvf,Assets &assets):assets_(assets){sources_.bind(pvf);}
    void reset();
    SkillLearningUiAction draw(Renderer &,World &,int normalLevel,bool testBranchActive,int mx,int my,bool click);
    Json snapshot() const;
};
} // namespace dnf
