# 核心伪代码与不变量

版本v1.1 · 2026-10-18 · 供后续AI实施参考。伪代码表达合同，不要求逐字复制函数名；所有recommended行为与已证实原生事件语义分开。模块正文提供更细状态和来源。

## 1. 来源加载与能力传播

```text
loadProfile(config, overrides):
    effective = resolvePathsRelativeToConfig(config, overrides)
    identity = fingerprintActualInputs(effective)
    repository = openReadOnly(identity)
    catalog = indexSourceRegistrations(repository)
    definitions = losslessParseThenSemanticCompile(catalog)
    graph = buildTypedDependencies(definitions)
    groups = stronglyConnectedComponents(graph)
    support = inspectLocalInstructionsAndResources(groups)
    repeat until unchanged:
        propagateBlockedRequiredDependencies(support, graph)
        propagateInferenceLabels(support, graph)
    preserveOptionalFailuresAsDiagnostics()
    return ContentContext(identity, definitions, support)
```

能力图循环本身不是失败。需要入口的所有合法候选都满足必需能力，未分类指令不能伪装装饰。源数值变更应经加载器进入定义，无须为每张图改C++。

## 2. 固定tick与帧内事件

```text
onElapsed(nanoseconds):
    accumulator += checkedMultiply(nanoseconds, 60)
    steps = 0
    while accumulator >= 1_000_000_000 and steps < platform.maxCatchupPerPump:
        simulateTick(tickIndex)
        accumulator -= 1_000_000_000
        tickIndex += 1
        steps += 1
    # 保留余量/积欠；让出到窗口事件泵，不丢弃模拟时间。

simulateTick(tick):
    consumeInputAndManagementAtBoundary(tick)
    expireTimersAndModifiers()
    reevaluateAndCommitActionRequests()
    advanceNativeDiscreteMotionOnceUsingOriginalTickContract()
    cursor = tick.begin
    while cursor < tick.end:
        next = findNextRequiredBoundary(cursor, tick.end)
        advanceOnlyDeclaredSubstepMotionAndEventClocks(cursor, next)
        resolveContactsUsingEachControllersDeclaredSamplingPolicy()
        dispatchAuthoredEventsInStableOrder(next)
        resolveAttackOpportunities()
        commitHitAndDeathTransitions()
        cursor = next
    applyDeferredEntityCommands()
    stageDomainEventsForQuestAndPersistence()
    publishReadOnlyPresentationSnapshot()
```

零时长事件必须推进事件游标；同刻事件链设置预算并报错，不能死循环。源ANI单pending事件消费者如有独立合同，应在相应执行器中保持，不用“遍历全部标签”替代。上面dispatch仅遍历该执行器已编译可执行的事件。已恢复的离散运动不因事件划分而拆成多个delta，子步积分和扫掠均须对应执行器显式支持。动画时钟的整数帧delay模式和局部年龄缩放模式互斥，避免倍率重复应用。

## 3. 技能提交与续段

```text
requestSkill(command):
    policy = resolveSkillAndController(command.key, actor.identity)
    if not policy.executable: reject(policy.reason)
    if command.continuation:
        action = findOwnedActiveAction(command.actionId)
        checkSameSkillAndLegalContinuation(action, command)
        enqueueContinuation(action, command)
    else:
        enqueueNewRequest(command)

commitNewRequest(request):
    quote = reevaluateCurrentEligibilityAndCosts(request)
    if not quote.valid: rejectWithoutMutation(quote)
    prepared = prepareRequiredResourcesAndInitialState(quote)
    if prepared.failed: rejectWithoutMutation(prepared)
    transaction = beginSimulationTransaction()
    transaction.consumeDueMpItemsAndOtherCosts(quote.commitPoint)
    transaction.recordCostEvent(prepared.actionId, quote.commitPoint)
    transaction.applyDueCooldownAndLinkedCooldowns()
    transaction.install(prepared.action)
    transaction.commit()

onLaterCostEvent(action, event):
    if action.committedEvents.contains(event.identity): return
    recheckRequiredRemainingResources()
    atomicallyApplyCostAndRecordEvent()
```

缓冲资格不持久有效；续段不重复支付新释放成本。持续消耗失败时执行行为定义的结束分支。提交后脚本失败的消耗与退款策略按提交点定义，不能以异常为由无限免费施法。

## 4. 属性计算与变化传播

```text
recompute(character, reason):
    base = growthAdapter.evaluate(identity, level, progressionHistory)
    mods = collectEquipmentSetPassiveAndBuffModifiers(character)
    stats, trace = statRules.evaluateOrdered(base, mods)
    assertFiniteAndWithinDeclaredBounds(stats)
    old = character.stats
    character.stats = stats
    if character.lifeState != Alive:
        preserveDeadHpAndLifeState()   # 仅显式复活服务可以改变死亡状态
        applyDeclaredMpCapacityPolicy()
    else if reason == NormalLevelUp:
        hp = clamp(stats.maxHp - (old.maxHp - hp), 0, stats.maxHp)
        mp = clamp(stats.maxMp - (old.maxMp - mp), 0, stats.maxMp)
    else if reason == DebugSetLevel:
        hp = clamp(hp, 0, stats.maxHp)
        mp = clamp(mp, 0, stats.maxMp)
    else:
        applyDeclaredCapacityChangePolicy(reason)
    invalidateAffectedDerivedCaches()
    publishStatTrace(trace)
```

正常升级HP处理为当前候选，不是原版已证。仅从基础和有效modifier重算，不在旧面板上累加。升级不自动复活死亡角色；死亡状态的HP应用交由明确复活规则，不能把上式单独套到死亡实体。

## 5. 命中机会与去重

```text
resolveContact(attack, target, contact):
    # pulse来自攻击时间线；不能在每次contact时自增。
    opportunity = (attack.id, attack.hitEpoch, target.lifeId, attack.currentPulse)
    if ledger.consumed(opportunity): return
    if not attack.targetIntervalAllows(target, now): return
    acceptance = hitRules.checkFactionStateProtectionAndGeometry(attack, target, contact)
    if acceptance.rejected:
        if acceptance.policyConsumesOpportunity: ledger.consume(opportunity)
        return
    context = makeContextUsingDeclaredSnapshotPolicy(attack, target, contact)
    result = damageRules.evaluate(context, attack.randomStream)
    atomically:
        ledger.consume(opportunity)
        attack.recordTargetInterval(target, now)
        applyHpMpAndStatus(result)
        applyReactionAndLocalHitstop(result)
        if transitionsAliveToDead(target): enqueueUniqueDeath(target.lifeId)
```

格挡/闪避/无敌是否消耗机会按对应行为合同登记；命中几何、接受命中和扣血是不同结果。视觉附层不能额外创建重复攻击。epoch只在真正reset命中表事件推进。

## 6. 副本入场

```text
prepareEntry(request):
    gate = eligibility.check(request, character, allLegalCandidates)
    if not gate.allowed: return gate.reason
    prepared = preloadAndGenerateLayoutWithScopedRandomStream(request)
    if prepared.failed: return failureWithoutConsumingEntryCost()
    submitPersistentCommand(EnterDungeon(request.id, prepared))

commitEntry(command):
    recheckEligibilityAndStateRevision(command)
    atomicallyCommitEntryCostAndRunSnapshot(command.layout, command.randomState)
    publishSceneTransitionUsingCommittedRun()
```

选择/悬停/取消不扣资源。重复确认使用相同入场请求身份；提交后渲染失败仍按同一run恢复，不重新抽取地图/掉落。读档使用保存的布局，不用当前生成器重跑旧seed。

## 7. 持久命令与故障一致性

```text
executePersistent(command):
    assertSingleWriterAndSaveLock()
    if state.committedCommands.contains(command.id): return storedResult(command.id)
    working = clone(currentInMemoryAuthoritativeState)
    # 合并尚未落盘的世界进展、RNG、pending和批次；不是复制过时磁盘lastCommit。
    validate(command, working)
    changes = evaluate(command, working.randomStreams)
    apply(working, changes)
    working.recordCommandResult(command.id, changes.result)
    working.acknowledgeIncludedEvents(changes.eventIds)
    working.generation += 1
    envelope = freezeCommitEnvelope(working, command.id)
    writeValidateFlushAndAtomicallyReplace(envelope)
    state = working                    # 只在耐久提交后发布
    emitPresentation(changes)
```

失败保持调用前内存state和原RNG，保留原envelope暂停依赖命令；同进程重试直接写原envelope，不能换新身份或重新按墙钟seed抽奖。崩溃后整体恢复最后耐久代。高频战斗在内存推进，检查点统一捕获世界和pending；不会每tick写磁盘。已持久化交易与当前副本世界必须同代，不能回退角色但保留已清怪房间，反之亦然。

## 8. 对象payload消费

```text
consumeObjectEvent(event):
    commandId = stableCommandIdFrom(event.id)
    changes = routeByTypedPayload(event)    # Drop/Trap/Spawn/Sound/Quest分开
    if changes.affectPersistentState:
        executePersistent(commandIncludingAck(commandId, changes, event.id))
    else:
        executeTransientEventWithRuntimeDedupe(changes)
        acknowledgeAtDeclaredCheckpoint(event.id)
```

不调用recordKill来伪造物件奖励。恢复未ack持久事件可重投，但消费者同一事务账本防重；物件身份由run/room/map/字段offset/record ordinal组成。

## 9. 恢复与双窗口管理

```text
restore(snapshot):
    validateSchemaContentAndRuleIdentity(snapshot)
    staged = decodeWithoutPublishing(snapshot)
    allocateAllEntitiesAndStableHandleMap(staged)
    rebindOwnersTargetsCapturesAndAttachments(staged)
    restoreRelativeTimesRandomStatesAndPendingEvents(staged)
    runDeclaredRestoreHooksWithoutRegrantingRewards(staged)
    validateInvariantsThenPublish(staged)

routeSdl(event):
    if event.windowId == debugWindow:
        if event.close: hideDebugWindow()
        else: debugUi.handle(event)       # 仅submit DebugCommand
    else if event.windowId == gameWindow:
        if event.focusLost: clearHeldKeysAndInputSequences()
        else: gameInput.handle(event)
    updateApplicationFocusAcrossBothWindows()
    if neitherWindowHasFocus: pauseWithFreshWallClockBaselineOnResume()

managementBoundary():
    for command in debugQueue.ordered:
        recheckTargetAndDeduplicate(command.id)
        applyOrScheduleRuleChange(command)
    # 暂停时可以执行此管理入口，不增加sim tick/AI/CD。
```

恢复失败保留原档和诊断，不发布半构造世界。瞬态取消必须登记清理所有权；不能遗漏抓取另一方、无敌或脚本appendage。
