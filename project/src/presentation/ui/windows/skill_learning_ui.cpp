#include "dnf/skill_learning_ui.hpp"
#include "dnf/skill_cost.hpp"
#include "dnf/experimental_character.hpp"
#include <iomanip>
#include <map>
#include <sstream>
#include <stdexcept>
namespace dnf {
namespace {
const char *learningKind(SkillSourceKind kind) {
    return kind==SkillSourceKind::Active?"active":kind==SkillSourceKind::Passive?"passive":"unknown";
}
std::string sourceNumber(std::optional<double> value,double divisor=1) {
    if(!value)return "—";
    std::ostringstream text;text<<std::setprecision(4)<<*value/divisor;return text.str();
}
}
void SkillLearningUi::reset() {
    page_=textPage_=0;passive_=tp_=false;selected_.reset();identity_.reset();view_=Json::object();
    metadataOwner_=nullptr;metadataSource_.clear();cachedRows_.clear();quoteContext_=Json();budget_=Json();budgetError_.clear();
    detailKey_.reset();detailResource_.clear();detailCommand_.clear();detailText_.clear();viewGroup_=-1;
    metadataBuilds_=quoteBuilds_=0;
}
SkillLearningUiAction SkillLearningUi::draw(Renderer &r,World &w,int normalLevel,bool testBranchActive,int mx,int my,bool click) {
    if(!identity_||!(*identity_==w.identity())){reset();identity_=w.identity();}
    SkillLearningUiAction action;const auto &source=sources_.layout("ui/skill/skillshopwindow.ui");
    businessUiImage(r,source,"10");businessUiImage(r,source,"24");businessUiImage(r,source,"8999");
    const auto &board=source.require("20");auto bp=source.position(board);businessUiBoard(r,assets_,board,bp[0],bp[1]);
    const bool testLearning=testBranchActive&&w.debugOverrides().enabled;
    r.text(testLearning?"技能学习 · 隔离测试":"技能学习",15,10,18);
    const auto keys=w.learningSkillKeys();const auto &catalog=w.characterCatalog();
    const auto &package=catalog.sourcePvf().identity();
    const bool metadataChanged=metadataOwner_!=&catalog||metadataSource_!=package||cachedRows_.size()!=keys.size()||
        !std::equal(keys.begin(),keys.end(),cachedRows_.begin(),[](auto key,const auto &row){return key==row.key;});
    size_t metadataReads=0;bool policiesChanged=false;
    if(metadataChanged) {
        std::vector<LearningRow> prepared;
        for(const auto key:keys) {
            LearningRow row;row.key=key;row.runtime=w.runtimeSkillPolicy(key);
            try {
                ++metadataReads;const auto &definition=catalog.skillDefinition(key);
                row.kind=definition.kind;row.sourcePath=definition.source.script.path;
                const auto name=definition.values("[name]");if(name.size()==1&&name[0].is_string())row.name=name[0].get<std::string>();
                row.tp=!definition.fieldsInScope("[special purchase cost]","common").empty();
                const auto icons=definition.fieldsInScope("[icon]","common");if(icons.size()==1){const auto &icon=icons.front()->field.values;
                    if(icon.size()>=2&&icon[0].is_string()&&icon[1].is_number_integer()){row.iconPath=icon[0];row.iconFrame=icon[1];}}
            }catch(const std::exception &error){row.error=error.what();row.kind=row.runtime.kind;}
            if(row.name.empty())row.name="技能 #"+std::to_string(key.skillId);
            prepared.push_back(std::move(row));
        }
        cachedRows_=std::move(prepared);metadataOwner_=&catalog;metadataSource_=package;++metadataBuilds_;
    }else for(auto &row:cachedRows_) {
        const auto policy=w.runtimeSkillPolicy(row.key);
        policiesChanged|=!(policy.key==row.runtime.key)||policy.kind!=row.runtime.kind||policy.implemented!=row.runtime.implemented||
            policy.passiveConsumerBound!=row.runtime.passiveConsumerBound||policy.maximumLevel!=row.runtime.maximumLevel;
        row.runtime=policy;
    }
    // Compare complete learning content as well as publication revisions: raw
    // import fixtures can replace a ledger/overlay while retaining a revision.
    // Only running cooldown values are irrelevant to learning qualification.
    auto normalLearning=w.skillState().snapshot(w.nowMs());
    for(auto &record:normalLearning.at("skills"))record.erase("remaining_cooldown_ms");
    const Json quoteContext={{"source",package},{"identity",w.identity().json()},
        {"normal_level",normalLevel},{"effective_level",w.characterLevel},{"test_learning",testLearning},
        {"debug",w.debugOverrides().enabled},{"preview",w.experimentalSkillPreviewEnabled()},
        {"projection_revision",w.skillRuntimeProjectionRevision()},{"overlay_revision",w.skillTestOverlay().revision},
        {"normal_ledger",std::move(normalLearning)},{"test_ledger",w.skillTestOverlay().snapshot()}};
    const bool quoteChanged=metadataChanged||policiesChanged||quoteContext_!=quoteContext;
    if(quoteChanged) {
        budgetError_.clear();budget_=Json();
        try {
            auto batch=w.quoteSkillLearningBatch(testLearning,normalLevel);budget_=batch.budget.json();
            std::map<SkillKey,SkillLearningQuote> quotes;for(auto &quote:batch.quotes)quotes.emplace(quote.key,std::move(quote));
            for(auto &row:cachedRows_){const auto found=quotes.find(row.key);
                if(found==quotes.end())throw std::logic_error("Learning batch omitted source key");row.quote=std::move(found->second);}
        }catch(const std::exception &error){
            budgetError_=error.what();
            for(auto &row:cachedRows_){row.quote={};row.quote.key=row.key;row.quote.message="技能点数或报价读取失败";row.quote.error=budgetError_;}
        }
        quoteContext_=quoteContext;detailKey_.reset();++quoteBuilds_;
    }
    view_["identity"]=w.identity().json();view_["test_learning"]=testLearning;
    view_["normal_level"]=normalLevel;view_["effective_level"]=w.characterLevel;
    if(quoteChanged){view_["budget"]=budget_;view_["budget_error"]=budgetError_;}
    // A cold/invalidated batch computes one shared service budget. Warm draw
    // uses the same revision-bound result, including jobs with zero consumers.
    for(const auto *id:{"2000","2001"}){auto p=source.position(id);
        const auto value=budgetError_.empty()?std::to_string(budget_.at(std::string(id)=="2000"?"remaining_sp":"remaining_tp").get<int64_t>()):"—";
        r.text(value,float(p[0]),float(p[1]),12);}
    const auto &radio=source.require("1");auto rp=source.position(radio);
    if(r.button(tp_?"SP 学习":"[SP 学习]",rp[0],rp[1],120,25,mx,my,click)){tp_=false;page_=0;selected_.reset();textPage_=0;}
    if(r.button(tp_?"[TP 学习]":"TP 学习",rp[0]+130,rp[1],120,25,mx,my,click)){tp_=true;page_=0;selected_.reset();textPage_=0;}
    if(r.button(passive_?"显示主动":"显示被动",rp[0]+270,rp[1],85,25,mx,my,click)){passive_=!passive_;page_=0;selected_.reset();textPage_=0;}
    std::vector<const LearningRow *> rows;
    for(const auto &row:cachedRows_) {
        const bool tp=row.quote.currency.empty()?row.tp:row.quote.currency=="TP";
        if(row.key.jobId!=w.identity().jobId||(row.kind==SkillSourceKind::Passive)!=passive_||tp!=tp_)continue;
        rows.push_back(&row);
    }
    // Reviewed consumers remain accessible before the larger source-only
    // diagnostic list. Stable ordering preserves each group's source order.
    if(w.isExperimentalCharacter())std::stable_partition(rows.begin(),rows.end(),[](const auto *row){return row->runtime.implemented;});
    const int viewGroup=int(tp_)+2*int(passive_);
    if(quoteChanged||viewGroup_!=viewGroup){view_["rows"]=Json::array();viewGroup_=viewGroup;
        for(const auto *row:rows)view_["rows"].push_back({{"key",row->key.json()},{"name",row->name},
            {"kind",learningKind(row->kind)},{"implemented",row->runtime.implemented},
            {"passive_consumer_bound",row->runtime.passiveConsumerBound},{"quote",row->quote.json()},
            {"source_path",row->sourcePath},{"source_error",row->error}});}
    const auto &pageSource=sources_.layout(tp_?"ui/skill/skillshoptppage.ui":"ui/skill/skillshopsppage.ui");
    const auto &area=pageSource.require(tp_?"200":"100","[control]");
    auto parent=source.position(tp_?"3":"2");auto areaPos=pageSource.position(area);
    const int left=parent[0]+areaPos[0]+9,top=parent[1]+areaPos[1];
    const int viewWidth=std::min(575,area.integers.at(0)),viewHeight=area.integers.at(1),columns=3,rowHeight=60;
    const int pageSize=columns*std::max(1,(viewHeight-28)/rowHeight),pages=BusinessUiPage::pages(int(rows.size()),pageSize);
    page_=BusinessUiPage::clamp(page_,int(rows.size()),pageSize);
    if(selected_&&std::none_of(rows.begin(),rows.end(),[&](const auto *row){return row->key==*selected_;}))selected_.reset();
    if(!selected_&&!rows.empty())selected_=rows[page_*pageSize]->key;
    const int cellWidth=viewWidth/columns;
    for(int index:BusinessUiPage::indices(page_,int(rows.size()),pageSize)){
        const auto &row=*rows[index];const auto &q=row.quote;int n=index-page_*pageSize,xx=left+(n%columns)*cellWidth,yy=top+(n/columns)*rowHeight;
        const bool selected=selected_&&*selected_==row.key;
        r.rect(float(xx),float(yy),float(cellWidth-6),53,selected?SDL_Color{96,74,36,235}:SDL_Color{24,27,31,235});
        if((row.runtime.implemented||testLearning)&&!row.iconPath.empty()&&row.iconFrame>=0)r.sprite(row.iconPath,row.iconFrame,xx+3,yy+4);
        const auto color=row.runtime.implemented?SDL_Color{240,230,205,255}:SDL_Color{145,145,145,255};
        r.text(businessUiFitted(r,row.name,cellWidth-45,12),float(xx+36),float(yy+5),12,color);
        r.text("Lv."+std::to_string(q.currentLevel)+" / "+std::to_string(q.purchaseMaximum),float(xx+36),float(yy+24),11,color);
        const bool hover=mx>=xx&&mx<xx+cellWidth-6&&my>=yy&&my<yy+53;
        if(hover){r.rect(float(xx),float(yy),float(cellWidth-6),53,{210,175,91,255},false);if(click){selected_=row.key;textPage_=0;}}
    }
    const int navigationY=top+viewHeight-25;
    view_["grid"]={{"left",left},{"top",top},{"cell_width",cellWidth},{"row_height",rowHeight},{"page_size",pageSize},
        {"width",viewWidth},{"navigation_y",navigationY}};
    if(r.button("上一页",left,navigationY,80,25,mx,my,click,page_>0))--page_;
    r.text(std::to_string(page_+1)+" / "+std::to_string(pages)+"   "+std::to_string(rows.size())+"项",float(left+95),float(navigationY+5),12);
    if(r.button("下一页",left+viewWidth-85,navigationY,80,25,mx,my,click,page_+1<pages))++page_;
    const LearningRow *selected=nullptr;for(const auto *row:rows)if(selected_&&row->key==*selected_)selected=row;
    const auto &explain=sources_.layout("ui/skill/skillshopexplain.ui");
    size_t detailReads=0;
    SkillLearningQuote selectedQuote;if(selected){selectedQuote=selected->quote;
        auto titlePos=explain.position("4011");
        r.text(businessUiFitted(r,selected->name,board.integers[0]-20,15),float(bp[0]+titlePos[0]+8),float(bp[1]+titlePos[1]),15);
        r.text("当前 Lv."+std::to_string(selectedQuote.currentLevel)+"  → "+std::to_string(selectedQuote.targetLevel),float(bp[0]+10),float(bp[1]+43),12);
        if(!detailKey_||!(*detailKey_==selected->key)){
          detailResource_="基础 MP — / CD —";detailCommand_="指令 ";
          detailText_="需要角色 Lv."+std::to_string(selectedQuote.requiredCharacterLevel)+"\\n下一级消耗 "+std::to_string(selectedQuote.cost)+" "+selectedQuote.currency+"\\n";
          if(selected->error.empty()){
          try {
            ++detailReads;const auto &def=catalog.skillDefinition(selected->key);const auto data=readSkillSourceData(def);
            if(selected->kind==SkillSourceKind::Active) {
                const auto costs=evaluateSkillCosts(data,std::max(1,std::max(selectedQuote.currentLevel,selectedQuote.targetLevel)),{},{},inferred1031SkillCostAbsencePolicy());
                detailResource_="基础 MP "+sourceNumber(costs.mp.value)+" / CD "+sourceNumber(costs.cooldown.value,1000)+"s";
            }
            for(const auto &v:data.values("[command]"))if(v.is_string())detailCommand_+=v.get<std::string>()+" ";
            detailText_+=def.source.script.text("[explain]")+"\\n"+def.source.script.text("[basic explain]");
          }catch(const std::exception &error){detailText_+="\\n来源说明读取失败："+std::string(error.what());}
          }
          detailText_+="\\n"+(selectedQuote.accepted()?"可以学习":selectedQuote.message);
          if(!selectedQuote.error.empty())detailText_+="\\n"+selectedQuote.error;
          if(!selected->error.empty())detailText_+="\\n"+selected->error;
          detailKey_=selected->key;
        }
        const auto &description=explain.require("4013");auto dp=explain.position(description);auto commandPos=explain.position("4012");
        r.text(businessUiFitted(r,detailResource_,178,11),float(bp[0]+8),float(bp[1]+85),11);
        r.text(businessUiFitted(r,detailCommand_,178,11),float(bp[0]+commandPos[0]),float(bp[1]+commandPos[1]),11,{104,213,237,255});
        const int detailLines=std::max(1,(std::min(description.integers.at(1),board.integers[1]-dp[1])-28)/17);
        textPage_=businessUiTextPages(r,detailText_,bp[0]+dp[0],bp[1]+dp[1],description.integers.at(0),detailLines,textPage_,mx,my,click,12);
    }else r.text("本页暂无已登记技能；未实现内容不会授予学习。",float(bp[0]+10),float(bp[1]+70),12);
    auto button=[&](const char *id,const std::string &label,bool enabled){const auto &c=source.require(id);auto pos=source.position(c);return r.button(label,pos[0],pos[1],68,27,mx,my,click,enabled);};
    const bool canBuy=selected&&selectedQuote.accepted()&&budgetError_.empty()&&!w.combat&&!w.player.dead&&w.player.hp>0&&w.activeSkill()<0&&
        (!w.experimentalRuntime()||!w.experimentalRuntime()->attacking())&&
        (!testBranchActive||testLearning)&&(!w.debugOverrides().enabled||testLearning)&&!w.experimentalSkillPreviewEnabled();
    if(button("1001","学习",canBuy)){action.purchase=selected->key;action.quote=selectedQuote;}
    if(button("1002","取消选择",selected!=nullptr))selected_.reset();
    action.close=button("1003","关闭",true);
    const auto &init=source.require("1000");if(r.button("清除测试覆盖",int(init.x)-40,int(init.y),110,25,mx,my,click,testBranchActive))action.resetTest=true;
    action.configure=r.button("配置快捷栏 F6",602,544,177,27,mx,my,click);
    if(testLearning&&w.identity().jobId==1) {
        action.openTestPreview=r.button("全源技能测试",405,544,177,27,mx,my,click,!w.combat&&!w.player.dead);
        view_["fighter_preview"]={{"all_source_skills_listed",true},{"automatic_mapping","sourceSkillActions only"},
            {"normal_learning_gates_unchanged",true}};
    }
    r.text(!budgetError_.empty()?businessUiFitted(r,"点数读取失败："+budgetError_,770,12):w.experimentalSkillPreviewEnabled()?
        "手动预览已启用；请到快捷栏返回已学模式后学习。":testLearning?"测试学习不写入正常成长账本":"选择技能查看条件，再点击学习。",15,580,12);
    view_["can_purchase"]=canBuy;
    view_["work"]={{"source_rows",cachedRows_.size()},{"metadata_reads_this_draw",metadataReads},
        {"quote_batch_requests_this_draw",quoteChanged?1:0},{"detail_reads_this_draw",detailReads},
        {"normal_snapshots_this_draw",1},{"test_overlay_snapshots_this_draw",1},
        {"metadata_builds",metadataBuilds_},{"quote_builds",quoteBuilds_}};
    return action;
}
Json SkillLearningUi::snapshot() const {return {{"page",page_},{"text_page",textPage_},{"passive",passive_},{"tp",tp_},
    {"selected",selected_?selected_->json():Json()},{"view",view_},{"source",sources_.snapshot()},
    {"layout_classification","source window envelope and scroll extents; reconstructed skill tile placement and transaction events"}};}
} // namespace dnf
