# 02 内容加载、版本切换与能力图

版本v1.1 · 2026-10-18 · 状态：设计待实施。

## 1. 当前基线和目标

Pvf具备read/script/paths，Assets具备blob/animation/pixels及多归档候选；main仍把PVF固定为client/Script.pvf。已有来源顺序保留能力应扩展到所有内容，而非为全量运行再造一份手工静态表。当前路径缓存只在单一进程资源上下文中成立，不足以作为跨版本磁盘缓存身份。

## 2. ContentProfile与启动

配置字段：profileId、pvfPath、pvfSha256、resourceRoots、archiveManifestHash、textEncoding、parserVersion、compatibilityProfileId、ruleProfileId、sourceEvidenceExeSha256。用户填写路径；实际hash由加载器计算，不相信人工填写值。

启动优先级：显式命令行参数覆盖profile，同目录默认profile次之；解析出effectiveProfile后记录来源和覆盖项。无有效配置时返回清晰诊断／配置入口，不能依赖进程当前目录搜索任意旧Script.pvf。相对路径相对配置文件目录解析。

初版切换必须结束当前内容会话并重建目录、缓存上下文、VM和实例；不在副本中热换PVF。内容指纹与磁盘位置分开，移动同一份资源不改变内容身份。saveDir默认按内容身份隔离，用户显式路径仍须校验存档身份。

## 3. 无损解析与字段选择

SourceDocument保存raw bytes、token序列、字段offset/ordinal、重复和嵌套scope、原字符串索引、解码编码和诊断。规范路径仅作检索键，原路径字面值保留。使用显式LE、有界读取和长度/解压上限，不信任损坏输入的count/offset。安全边界是解析器政策，不能冒称原生异常输入行为。

字段结果至少能表示Absent、ExplicitEmpty、Value、Ambiguous、Malformed。SKL模式覆盖仅对允许覆盖的参数生效，metadata保持其定义作用域；显式空覆盖不回退common。重复字段按已核对消费者解释；没有规则时保留全部候选并阻止依赖行为，不一律选首尾。

表格读取验证列宽、行数、类型及等级边界；level0表示未学习。显示用level property不直接定义实际伤害取整。资源预加载不自动成为效果播放列表。源路径预处理按对应格式约定，不跨格式泛化相对目录规则。

## 4. 语义编译和适配

采用两步：无损解析→带SourceRef的typed definition。语义编译器按资源类型输出所需能力及引用边。definition不可变，实例存可变数据。派生缓存含compiler版本与规则绑定身份，升级编译器自动失效。

适配记录字段：adapterId/version、匹配的格式/内容身份、源字段选择、行为类型、证据引用、分类、限制、失效条件。映射原生控制器不可从PVF表达的动作允许专用适配，源可直接表达的数值和路径不得重复固化进去。规则同时匹配多项且无明确优先级时拒绝歧义。

```text
compile(key, context):
    source = repository.readExact(key, context.profile)
    parsed = formatParser.parseLosslessly(source)
    if parsed.structurallyInvalid: return Blocked(parsed.diagnostics)
    typed = semanticCompiler.interpret(parsed, context.mode)
    for ambiguity in typed.ambiguities:
        rule = context.compatibility.findScopedResolution(ambiguity)
        if rule: applyWithEvidence(rule, ambiguity)
        else: markDependentBehaviorUnsupported(ambiguity)
    return freeze(typed, typed.dependencies, source.identity)
```

## 5. 资源与缓存

原始成员缓存按archive/member identity+hash；解码缓存按member hash+decoder version+frame/options；平台缓存再加renderer/texture format或audio sample参数。独立SDL renderer不共享GPU纹理。

同名多来源内容不同：必须根据已知归档优先级或精确引用选择；未知时报告候选。字节相同可合并解码但保留全部物理来源。禁止采用existence heuristic猜装备动作。损坏或缺失资源不能从另一个profile补齐。

启动先建立索引和必要定义，避免把全PVF及全IMG一次解码入内存。源hash核验可在索引建立/首次读取阶段进行并持久化完整清单；mtime/size只用于发现变化，不作为发布身份的最终证明。引用图预取场景必需资源，LRU淘汰只影响加载成本，不能影响逻辑与随机数。

## 6. 全量目录与依赖图

注册来源涵盖character、skill、equipment、stackable、monster、passiveobject、object、NPC、shop、quest、TWN、WDM、DGN、MAP、TIL、UI、ACT/AI、ANI/ALS/PTL和音频等实际输入。无注册表资源通过源引用定位，不编造ID。

DependencyEdge保存from/to、kind、sourceRef、requiredness、condition、compiler能力。区分必需玩法、可选表现、仅预加载和元数据。未知行为边默认不可当可选装饰。

能力项如action.capture、script.appendage、attack.periodic-hit、quest.collect-submit、dungeon.quest-variant、particle.emitter。输出Playable、PlayableWithInference、Blocked及原因路径。先求强连通分量再传播required阻断；合法循环引用不天然失败。递归生成行为在执行器另设预算。

评估按内容目标和当前模式，不因无关未实现UI使整包无法加载。入口UI和最终进入使用同一个EligibilityService，最后提交前复核角色状态。所有合法候选房间的必需依赖必须检查，不能通过本次抽中简单房间蒙混开放。

## 7. 版本兼容与来源冲突

格式兼容且行为已支持：新内容直接纳入目录。存在已知字段变体：采用绑定的adapter。新语义：保留数据并报告影响范围，进入待实现队列。

新UI/怪物包PVF ca756b…与当前d13ce…不同。采用前：核对交接manifest→比较实际源成员和字段→核对EXE消费者范围→建立适配证据→重新运行解析与消费测试。Qt预览、2070MOB目录和静态通过数量不构成当前内容运行验证。

具备第二个真实完整PVF时验证两配置切换；若仅有交接子集，则做成员差异／不兼容诊断，报告“第二完整版本未验证”，不得把同一文件改名冒充多版本支持。

## 8. 实施步骤与验收

P01：配置、身份、启动参数、隔离存档和缓存键。P02：全量目录、scope读取、依赖、语义适配注册和能力报告。所有数量以本次hash下扫描结果为准，不复制历史计数作运行断言。

验收：profile路径移动不改内容身份；实际改PVF后旧缓存失效；重复/空/缺失字段区别；未知指令定位到消费节点；同名资源冲突明确；循环依赖可解释；必需首领机制阻止开放、已分类可选装饰仅警告；替换兼容源数值无需修改C++即可改变运行结果。

## 9. 来源

[resources](../dnf-native-demo/include/dnf/resources.hpp)、[SKL读取](../dnf-native-demo/include/dnf/skill_data.hpp)、[装备动作](../dnf-native-demo/include/dnf/equipment_motion.hpp)、[来源研究](../dnf-result/README.md)、[新UI规范](../逆向部分结果参考/1031-UI渲染交接包/1031-UI渲染交接包/ui_lab_1031/docs/1031-UI层跨项目复刻规范.md)。
